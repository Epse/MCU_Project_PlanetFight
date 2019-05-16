#ifndef QUEUE_H
#define QUEUE_H
#include <stdint.h>
#include "leddriver.h"
#include "Sprite.h"

typedef struct Led_and_index{
  uint8_t index;
  Led led;
}Led_and_index;

typedef struct Queue_item
{
  uint16_t timing;
  Led_and_index leds_and_indexes[10];
  uint16_t count;
  uint8_t front;
}Queue_item;

typedef struct Queue
{
  int front;
  Queue_item data[10];
  uint8_t count;
}Queue;

// nodig om indexen op te slaan die uit moeten
typedef struct Queue_int
{
  int front;
  uint16_t data[16];
  uint8_t count;
}Queue_int;

typedef struct Queue_sprite
{
  int front;
  Sprite data[10];
  uint8_t count;
} Queue_sprite;




// hoofd queue
Queue queue();
Queue_item next(Queue *queue);
uint16_t next_timing(Queue queue);
void enqueue(Queue *queue, Queue_item item);
void sort(Queue *queue);
void aggregate(Queue *sorted_queue);
void set_front(Queue *queue, uint16_t timing);

// queue item kan meerdere index-led paren bevatten - functies om deze op te vragen nodig
Queue_item queue_item(uint8_t index, uint16_t timing, Led led);
Led_and_index dequeue_led_and_index(Queue_item *queue_item);

//int queue
Queue_int queue_int();
uint16_t dequeue_int(Queue_int *queue);
void enqueue_int(Queue_int *queue, uint16_t integer);

//sprite queue
Queue_sprite queue_sprite();
Sprite dequeue_sprite(Queue_sprite *queue);
void enqueue_sprite(Queue_sprite *queue, Sprite sprite);

#endif
