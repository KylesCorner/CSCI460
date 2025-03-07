/*
 *
 */

#include "array.h"
#include <stdio.h>

#define NUM_THREADS 6
#define NUM_WRITES 100

void singleton_test(circleQueue *my_queue) {

  // ------------------------------------------
  // Enqueue Test
  // ------------------------------------------

  printf("----- Before enqueue test -----\n");
  circleQueue_print(my_queue);
  for (int i = 1; i <= QUEUE_SIZE; i++) {
    if (circleQueue_enqueue(my_queue, i)) {
      printf("Error on i=%d\n", i);
    }
  }
  printf("----- After enqueue test -----\n");
  circleQueue_print(my_queue);

  // ------------------------------------------
  // Dequeue Test
  // ------------------------------------------

  for (int i = 0; i < QUEUE_SIZE / 2; i++) {
    circleQueue_dequeue(my_queue);
  }
  printf(" ---- After dequeue test -----\n");
  circleQueue_print(my_queue);

  // ------------------------------------------
  // Peek Test
  // ------------------------------------------

  printf("Peek test: \n");
  for (int i = 0; i < QUEUE_SIZE; i++) {
    if (circleQueue_peek(my_queue, i) == my_queue->data[i]) {
      printf("Passed!\n");
    } else {
      printf("Failed! on i=%d\n", i);
    }
  }

  // ------------------------------------------
  // Free Test
  // ------------------------------------------

  circleQueue_free(my_queue);
  printf("Free test passed!\n");
  printf(" ----- Singleton Tests done! -----\n");
}

void *produce(void *arg) {

  circleQueue *q = (circleQueue *)arg;

  for (int i = 1; i <= NUM_WRITES; i++) {
    int value = i % QUEUE_SIZE;
    circleQueue_enqueue(q, value);
  }

  return NULL;
}

void *consume(void *arg) {

  circleQueue *q = (circleQueue *)arg;

  for (int i = 0; i < NUM_WRITES; i++) {
    int value = circleQueue_dequeue(q);
  }

  return NULL;
}
void thread_test(circleQueue *q) {

  pthread_t thread_ids[NUM_THREADS];


  //create writer threads
  for (int i = 0; i < NUM_THREADS/2; i++){
    pthread_create(&thread_ids[i], NULL, produce, q);
    printf("Producer thread created id=%ld\n", thread_ids[i]);
  }

  //create reader threads
  for (int i = NUM_THREADS/2; i < NUM_THREADS; i++){
    pthread_create(&thread_ids[i], NULL, consume, q);
    printf("Consumer thread created id=%ld\n", thread_ids[i]);
  }
  
  //wait for threads to finish
  for (int i = 0; i < NUM_THREADS; i++){
    pthread_join(thread_ids[i], NULL);
  }


  circleQueue_free(q);
}

int main() {
  circleQueue my_queue;
  circleQueue_init(&my_queue);
  singleton_test(&my_queue);

  circleQueue_init(&my_queue);
  thread_test(&my_queue);
  printf(" ----- After Multi-tread test. Queue should be empty. -----\n");
  circleQueue_print(&my_queue);


  pthread_exit(NULL);
}
