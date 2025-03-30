#ifndef MULTI_LOOKUP_H
#define MULTI_LOOKUP_H

// Max constants for program limits
#include "array.h"
#include <bits/pthreadtypes.h>
#define ARRAY_SIZE 10 // Number of elements in the shared array
#define MAX_REQUESTER_THREADS                                                  \
  10 // Maximum number of concurrent requester threads
#define MAX_RESOLVER_THREADS 10 // Maximum number of concurrent resolver threads
#define MAX_THREADS 20          // resolver + requester threads
#define MAX_INPUT_FILES 100     // Maximum number of input files
#define MAX_NAME_LENGTH                                                        \
  255 // Maximum length of a hostname (including null terminator)
#define MAX_IP_LENGTH                                                          \
  INET6_ADDRSTRLEN // Maximum size of the IP address string (for both IPv4 and
                   // IPv6)

// Structure to hold hostname data
typedef struct {
  char hostname[MAX_NAME_LENGTH]; // Hostname string
} hostname_entry_t;

typedef struct {
  circleQueue *buffer;
  pthread_mutex_t requester_finished_lock;
  pthread_mutex_t requester_log_lock;
  pthread_mutex_t requester_active_lock;
  pthread_mutex_t resolver_log_lock;
  pthread_mutex_t file_index_lock;
  pthread_mutex_t file_lock;
  int num_requesters;
  int num_active_requesters;
  int num_resolvers;
  int num_data_files;
  int num_threads;
  int requester_finished;
  int file_index;
  // char *requester_log;
  // char *resolver_log;
  char **data_files;

} thread_args_t;

// Function prototypes

// Requester thread function
void *requester(void *arg);

// Resolver thread function
void *resolver(void *arg);

#endif // MULTI_LOOKUP_H
