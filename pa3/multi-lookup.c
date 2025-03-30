#include "multi-lookup.h"
#include "array.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

FILE *requester_log, *resolver_log;
int total_files_servied = 0;
int total_hostnames_resolved = 0;
// FIX: Invalid read of size 1

void *requester_thread(void *arg) {
  printf("Requester!\n");
  int serviced = 0;
  pthread_t thread_id = pthread_self();
  thread_args_t *args = (thread_args_t *)arg;
  char **filenames = args->data_files;

  for (int i = 0; filenames[i] != NULL; i++) {
    FILE *input_file = fopen(filenames[i], "r");
    if (!input_file) {
      fprintf(stderr, "Invalid file %s\n", filenames[i]);
      continue;
    }

    char hostname[MAX_NAME_LENGTH];
    while (fgets(hostname, MAX_NAME_LENGTH, input_file)) {
      hostname[strcspn(hostname, "\n")] = 0; // Remove newline

      circleQueue_enqueue(args->buffer, hostname);

      pthread_mutex_lock(&args->requester_log_lock);
      fprintf(requester_log, "%s\n", hostname);
      pthread_mutex_unlock(&args->requester_log_lock);
    }
    fclose(input_file);
  }

  pthread_mutex_lock(&args->requester_active_lock);
  args->num_active_requesters--;
  pthread_mutex_unlock(&args->requester_active_lock);

  printf("thread %lx serviced %d files\n", thread_id, serviced);
  pthread_cond_broadcast(&args->buffer->not_empty);
  return NULL;
}

void *resolver_thread(void *arg) {
  printf("Resolver!\n");
  thread_args_t *args = (thread_args_t *)arg;
  pthread_t thread_id = pthread_self();
  int num_resolved = 0;

  while (1) {
    pthread_mutex_lock(&args->buffer->lock);
    while (args->buffer->count == 0) {
      pthread_mutex_lock(&args->requester_active_lock);
      if (args->num_active_requesters == 0) {
        pthread_mutex_unlock(&args->requester_active_lock);
        pthread_mutex_unlock(&args->buffer->lock);
        printf("thread %lx resolved %d hostnames\n", thread_id, num_resolved);
        return NULL;
      }
      pthread_mutex_unlock(&args->requester_active_lock);
      pthread_cond_wait(&args->buffer->not_empty, &args->buffer->lock);
    }
    pthread_mutex_unlock(&args->buffer->lock);

    char *hostname = circleQueue_dequeue(args->buffer);
    char ip_address[MAX_IP_LENGTH] = "192.168.0.1";

    pthread_mutex_lock(&args->resolver_log_lock);
    fprintf(resolver_log, "%s, %s\n", hostname, ip_address);
    pthread_mutex_unlock(&args->resolver_log_lock);

    num_resolved++;
  }

  return NULL;
}

int main(int argc, char *argv[]) {
  // Parse arguments and initialize synchronization primitives
  if (argc < 5) {
    fprintf(stderr,
            "Usage: %s <# requesters> <# resolvers> <requester log> <resolver "
            "log> <file1> <file2> ...\n",
            argv[0]);
    return EXIT_FAILURE;
  }
  // Shared buffer and args
  thread_args_t args;
  circleQueue buffer;

  // Parse command line arguments
  args.num_requesters = atoi(argv[1]);
  args.num_resolvers = atoi(argv[2]);
  args.num_threads = args.num_requesters + args.num_resolvers;
  args.num_active_requesters = args.num_requesters;

  if (args.num_requesters > MAX_REQUESTER_THREADS ||
      args.num_resolvers > MAX_RESOLVER_THREADS ||
      (argc - 5) > MAX_INPUT_FILES) {
    fprintf(stderr, "Error: Exceeded maximum limits.\n");
    return EXIT_FAILURE;
  }

  // args.requester_log = argv[3];
  // args.resolver_log = argv[4];

  requester_log= fopen(argv[3], "w");
  resolver_log = fopen(argv[4], "w");

  if (!requester_log || !resolver_log) {
    fprintf(stderr, "Error opening log files.\n");
    return EXIT_FAILURE;
  }

  args.file_index = 0;
  args.requester_finished = 0;
  args.num_data_files = argc - 5;
  args.data_files = &argv[5];
  args.buffer = &buffer;

  struct timeval start_time, end_time;
  gettimeofday(&start_time, NULL);

  // init shared buffer and mutex
  circleQueue_init(&buffer);
  pthread_mutex_init(&args.requester_finished_lock, NULL);
  pthread_mutex_init(&args.file_index_lock, NULL);
  pthread_mutex_init(&args.requester_active_lock, NULL);
  pthread_mutex_init(&args.resolver_log_lock, NULL);
  pthread_mutex_init(&args.requester_log_lock, NULL);

  pthread_t requesters[args.num_requesters], resolvers[args.num_resolvers];

  for (int i = 0; i < args.num_requesters; i++) {
    pthread_create(&requesters[i], NULL, requester_thread, &args);
  }

  for (int i = 0; i < args.num_resolvers; i++) {
    pthread_create(&resolvers[i], NULL, resolver_thread, &args);
  }
  for (int i = 0; i < args.num_requesters; i++) {
    pthread_join(requesters[i], NULL);
  }
  for (int i = 0; i < args.num_resolvers; i++) {
    pthread_join(resolvers[i], NULL);
  }

  gettimeofday(&end_time, NULL);
  double elapsed = (end_time.tv_sec - start_time.tv_sec) +
                   (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
  printf("./multi-lookup: total time is %.6f seconds\n", elapsed);

  // Clean up
  circleQueue_free(&buffer);

  fclose(requester_log);
  fclose(resolver_log);
  return EXIT_SUCCESS;
}
