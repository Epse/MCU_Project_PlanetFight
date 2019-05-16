#include "Queue.h"
#include "Sprite.h"


Queue queue(){
  Queue queue = { .front = -1, .count = 0 };
  return queue;
}

void enqueue(Queue *queue, Queue_item item){
  queue->front++;
  queue->data[queue->front] = item;
  queue->count++;
}

Queue_item next(Queue *queue){
  Queue_item item = queue->data[queue->front];
  queue->front--;
  if (queue->front == -1 && queue->count != 0) {
    queue->front = queue->count - 1;
  }
  return item;
}

void sort(Queue *queue){
  if (queue->count > 1) {
    Queue_item swap;
    for (int i = 0; i < queue->count; ++i){
      for (int j = i + 1; j < queue->count; ++j)
      {
        if (queue->data[i].timing < queue->data[j].timing)
        {
            swap = queue->data[i];
            queue->data[i] = queue->data[j];
            queue->data[j] = swap;
        }
      }
    }
  }
}

void aggregate(Queue *sorted_queue){
  if (sorted_queue->count > 1) {
    int shifts = 0;
    Queue_item *current = &sorted_queue->data[0];
    Queue_item *next;
    for (int i = 1; i < sorted_queue->count; i++) {
      next = &sorted_queue->data[i];
      // aggregeren?
      if (current->timing - 200 < next->timing) {
        enqueue_led_and_index(current, next->leds_and_indexes[0]);
        shifts++;
        printIntToLCD(shifts, 1, 10);
      }
      else {
        if (shifts != 0){
          sorted_queue->data[i - shifts] = *next;
        }
        current = next;
      }
    }
    sorted_queue->count -= shifts;
    sorted_queue->front -= shifts;
  }
}

void set_front(Queue *queue, uint16_t timing){
  int i = 0;
  int front = queue->front;
  while (i < queue->count && queue->data[front].timing < timing + 50) {
    i++;
    front--;
  }
  if (front != -1) {
    queue->front = front;
  }
}

uint16_t next_timing(Queue queue){
  uint8_t current_index = queue.front;
  return queue.data[current_index].timing;
}

Queue_item queue_item(uint8_t index, uint16_t timing, Led led){
  Led_and_index led_and_index = {.led = led, .index = index};
  Queue_item queue_item = { .timing = timing, .count = 1, .front = 0};
  queue_item.leds_and_indexes[0] = led_and_index;
  return queue_item;
}

Led_and_index dequeue_led_and_index(Queue_item *queue_item){
  Led_and_index obj = queue_item->leds_and_indexes[queue_item->front];
  queue_item->front--;
  queue_item->count--;
  return obj;
}

void enqueue_led_and_index(Queue_item *item, Led_and_index led_and_index){
  item->leds_and_indexes[item->front] = led_and_index;
  item->front++;
  item->count++;
}

//int queue
Queue_int queue_int(){
  Queue_int queue_int = { .front = -1, .count = 0 };
  return queue_int;
}

uint16_t dequeue_int(Queue_int *queue){
  uint16_t integer = queue->data[queue->front];
  queue->front--;
  queue->count--;
  return integer;
}

void enqueue_int(Queue_int *queue, uint16_t integer){
  queue->front++;
  queue->data[queue->front] = integer;
  queue->count++;
}

//sprite queue
Queue_sprite queue_sprite() {
  Queue_sprite queue_sprite = { .front = -1, .count = 0 };
  return queue_sprite;
}

Sprite dequeue_sprite(Queue_sprite *queue){
  Sprite sprite = queue->data[queue->front];
  queue->front--;
  queue->count--;
  return sprite;
}

void enqueue_sprite(Queue_sprite *queue, Sprite sprite){
  if (queue->count < 10) {
    queue->front++;
    queue->data[queue->front] = sprite;
    queue->count++;
  }
}
