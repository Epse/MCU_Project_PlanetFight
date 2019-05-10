#ifndef QUEUE_H
#define QUEUE_H
#include <stdint.h>
#include "leddriver.h"

typedef struct Queue_item
{
  uint16_t index, timing;
  Led led;
}Queue_item;


typedef struct Queue
{
  int front;
  Queue_item data[20];
  uint8_t count;
}Queue;

Queue_item queue_item();

Queue queue();

Queue_item next(Queue *queue);

uint16_t next_timing(Queue queue);

void enqueue(Queue *queue, Queue_item item);

void sort(Queue *queue);

#endif
