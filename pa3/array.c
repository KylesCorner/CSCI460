/*
 * Author: Kyle Krstulich
 * 3/6/25
 *
 * This is a thread safe circular queue
 *
 */
#include "array.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int circleQueue_init(circleQueue *q) {

  q->rear = -1;
  q->front = -1;
  q->count = 0;
  pthread_mutex_init(&q->lock, NULL);
  pthread_cond_init(&q->not_empty, NULL);
  pthread_cond_init(&q->not_full, NULL);

  for (int i = 0; i < QUEUE_SIZE; i++) {
    q->data[i] = NULL;
  }
  return 0;
}
int circleQueue_enqueue(circleQueue *q, char *value) {

  pthread_mutex_lock(&q->lock);

  // queue is full
  while ((q->rear + 1) % QUEUE_SIZE == q->front) {
    pthread_cond_wait(&q->not_full, &q->lock);
  }
  if ((q->rear + 1) % QUEUE_SIZE == q->front) {
    fprintf(stderr, "Queue overflow!\n");
    // print error code
    return -1;
  }
  // queue is empty
  if (q->front == -1) {
    q->front++;
  }

  // increment rear counter
  q->rear = (q->rear + 1) % QUEUE_SIZE;
  q->data[q->rear] = strdup(value);

  q->count++;

  pthread_cond_signal(&q->not_empty);
  pthread_mutex_unlock(&q->lock);

  return 0;
}

char *circleQueue_dequeue(circleQueue *q) {

  pthread_mutex_lock(&q->lock);

  while (q->front == -1) {
    pthread_cond_wait(&q->not_empty, &q->lock);
  }
  // queue is already empty
  if (q->front == -1) {
    fprintf(stderr, "Queue Underflow!\n");
    return "";
  }

  char *temp = q->data[q->front];
  free(q->data[q->front]);
  q->data[q->front] = 0;

  if (q->front == q->rear) {
    // queue is now empty
    q->front = -1;
    q->rear = -1;
  } else {
    // increment front counter
    q->front = (q->front + 1) % QUEUE_SIZE;
  }

  q->count--;

  pthread_cond_signal(&q->not_full);
  pthread_mutex_unlock(&q->lock);

  return temp;
}
char *circleQueue_peek(circleQueue *q, int index) {
  pthread_mutex_lock(&q->lock);

  // Check if the index is valid
  if (index < 0 || index >= q->count) {
    fprintf(stderr, "Index out of bounds!\n");
    pthread_mutex_unlock(&q->lock);
    return NULL; // Return NULL if the index is invalid
  }

  // Calculate the actual position of the item in the circular queue
  int actual_index = (q->front + index) % QUEUE_SIZE;

  char *temp =
      q->data[actual_index]; // Retrieve the string at the calculated position

  pthread_mutex_unlock(&q->lock);

  return temp; // Return the string at the given index
}

void circleQueue_free(circleQueue *q) {
  pthread_mutex_lock(&q->lock);
  // Free the strings in the queue
  for (int i = 0; i < QUEUE_SIZE; i++) {
    if (q->data[i] != NULL) {
      free(q->data[i]); // Free each string pointer
    }
  }
  // destroy sephamores and mutex
  pthread_mutex_unlock(&q->lock);
  pthread_cond_destroy(&q->not_full);
  pthread_cond_destroy(&q->not_empty);
  pthread_mutex_destroy(&q->lock);
}

void circleQueue_print(circleQueue *q) {

  pthread_mutex_lock(&q->lock);
  printf("[");
  for (int i = 0; i < QUEUE_SIZE; i++) {
    printf("%s, ", q->data[i]);
  }
  printf("]\n");
  printf("Front=%d Rear=%d Count=%d\n", q->front, q->rear, q->count);
  pthread_mutex_unlock(&q->lock);
}
