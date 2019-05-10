// #include "Queue.h"
//
// Queue Queue(int size){
//   Queue queue = { .front = -1, .data = null, .is_empty = 1 };
// }
//
// void enqueue(Queue queue, Queue_item item){
//   queue.front++;
//   queue.data[front] = item;
//   queue.is_empty = 0;
// }
//
// Queue_item dequeue(Queue queue){
//   Queue_item item = queue.front;
//   front--;
//   if (front == -1) {
//     queue.is_empty = 1;
//   }
// }
//
// void sort(Queue queue){
//   uint8_t unsorted = 1;
//   Queue_item swap;
//     for (int i = 0; i <= queue.front; ++i)
//         {
//             for (int j = i + 1; j <= queue.front; ++j)
//             {
//                 if (queue.data[i].timing < queue.data[j].timing)
//                 {
//                     swap = queue.data[i];
//                     queue.data[i] = queue.data[j];
//                     queue.data[j] = swap;
//                 }
//             }
//         }
// }
