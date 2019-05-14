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

// nodig om indexen op te slaan die uit moeten
typedef struct Queue_int
{
  int front;
  uint16_t data[16];
  uint8_t count;
}Queue_int;

// normal queue
Queue_item queue_item();

Queue queue();

Queue_item next(Queue *queue);

uint16_t next_timing(Queue queue);

void enqueue(Queue *queue, Queue_item item);

void sort(Queue *queue);

//int queue
Queue_int queue_int();
uint16_t dequeue_int(Queue_int *queue);
void enqueue_int(Queue_int *queue, uint16_t integer);

#endif
