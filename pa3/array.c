/*
 * Author: Kyle Krstulich
 * 3/6/25
 *
 * This is a thread safe circular queue
 *
 */
#include "array.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int circleQueue_init(circleQueue *q) {

  q->rear = -1;
  q->front = -1;
  pthread_mutex_init(&q->lock, NULL);
  pthread_cond_init(&q->not_empty, NULL);
  pthread_cond_init(&q->not_full, NULL);

  for (int i = 0; i < QUEUE_SIZE; i++) {
    if ((q->data[i] = 0)) {
      fprintf(stderr, "Unable to create array\n");
      return -1;
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}
int circleQueue_enqueue(circleQueue *q, int value) {

  pthread_mutex_lock(&q->lock);
  while ((q->rear + 1) % QUEUE_SIZE == q->front) {
    pthread_cond_wait(&q->not_full, &q->lock);
  }

  // queue is full
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
  q->data[q->rear] = value;

  pthread_cond_signal(&q->not_empty);
  pthread_mutex_unlock(&q->lock);

  return 0;
}

int circleQueue_dequeue(circleQueue *q) {

  pthread_mutex_lock(&q->lock);
  while (q->front == -1) {
    pthread_cond_wait(&q->not_empty, &q->lock);
  }

  // queue is already empty
  if (q->front == -1) {
    fprintf(stderr, "Queue Underflow!\n");
    return -1;
  }

  int temp = q->data[q->front];
  q->data[q->front] = 0;

  if (q->front == q->rear) {
    // queue is now empty
    q->front = -1;
    q->rear = -1;
  } else {
    // increment front counter
    q->front = (q->front + 1) % QUEUE_SIZE;
  }
  pthread_cond_signal(&q->not_full);
  pthread_mutex_unlock(&q->lock);

  return temp;
}

int circleQueue_peek(circleQueue *q, int index) {

  pthread_mutex_lock(&q->lock);
  if (index > QUEUE_SIZE || index < 0) {
    fprintf(stderr, "Index out of bounds!");
  }

  int temp = q->data[index];
  pthread_mutex_unlock(&q->lock);
  return temp;
}

void circleQueue_free(circleQueue *q) {
  pthread_mutex_destroy(&q->lock);
  pthread_cond_destroy(&q->not_empty);
  pthread_cond_destroy(&q->not_full);
}

void circleQueue_print(circleQueue *q) {

  pthread_mutex_lock(&q->lock);
  printf("[");
  for (int i = 0; i < QUEUE_SIZE; i++) {
    printf("%d, ", q->data[i]);
  }
  printf("]\n");
  printf("Front=%d Rear=%d\n", q->front, q->rear);
  pthread_mutex_unlock(&q->lock);
}
