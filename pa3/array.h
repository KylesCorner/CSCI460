#ifndef ARRAY_H
#define ARRAY_H

#define QUEUE_SIZE 10

#include <pthread.h>
#include <semaphore.h>


typedef struct{
  char* data[QUEUE_SIZE];
  int rear;
  int front;
  int count;
  pthread_mutex_t lock;
  pthread_cond_t not_empty;
  pthread_cond_t not_full;
}circleQueue;

int circleQueue_init(circleQueue *q);
int circleQueue_enqueue(circleQueue *q, char* value);
char* circleQueue_dequeue(circleQueue *q);
char* circleQueue_peek(circleQueue *q, int index);
void circleQueue_free(circleQueue *q);
void circleQueue_print(circleQueue *q);

#endif
