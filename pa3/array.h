#ifndef ARRAY_H
#define ARRAY_H

#define QUEUE_SIZE 10

#include <pthread.h>
#include <semaphore.h>


typedef struct{
  int data[QUEUE_SIZE];
  int rear;
  int front;
  int count;
  pthread_mutex_t lock;
  sem_t empty;
  sem_t full;
}circleQueue;

int circleQueue_init(circleQueue *q);
int circleQueue_enqueue(circleQueue *q, int value);
int circleQueue_dequeue(circleQueue *q);
int circleQueue_peek(circleQueue *q, int index);
void circleQueue_free(circleQueue *q);
void circleQueue_print(circleQueue *q);

#endif
