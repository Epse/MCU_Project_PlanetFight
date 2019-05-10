#include "Queue.h"
#include "stddef.h"

Queue_item queue_item(){
  Queue_item queue_item = { .index = 0, .led = NULL, .timing = 0 };
  return queue_item;
}

Queue queue(){
  Queue queue = { .front = -1, .data = NULL, .count = 0 };
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
    for (int i = 0; i < queue->count; ++i)
        {
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

uint16_t next_timing(Queue queue){
  uint8_t current_index = queue.front;
  return queue.data[current_index].timing;
}
