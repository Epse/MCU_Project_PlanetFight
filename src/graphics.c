#include <avr/interrupt.h>
#include "graphics.h"
#include "snelheidssensor.h"
#include "Queue.h"

// 360 deg = 32768 (2^15)

Led leds[16];

// Queue voor ledjes die aan moeten
Queue queue_on;
Queue queue_off;

//returns zero led
Led off_led(){
  return led(0, 0, 0, 0);
}

void set_up_graphics() {
  // enable interrupt comparematch A and B

  for (int i = 0; i < sizeof(leds); i++) {
    leds[i] = off_led();
  }

  OCR1A = 1000;
  OCR1B = OCR1A + 100;

  queue_on = queue();
  queue_off = queue();

  //temp hardcoded values
  Queue_item Q_item1 = queue_item();
  Queue_item Q_item1_off = queue_item();

  Q_item1.led = led(30, 255, 255, 0);
  Q_item1.index = 5;
  Q_item1.timing = 89;

  Q_item1_off.led = led(0, 0, 0, 0);
  Q_item1_off.index = 5;
  Q_item1_off.timing = 289;

  enqueue(&queue_on, Q_item1);
  enqueue(&queue_off, Q_item1_off);
}

Led* get_leds(){
  return leds;
}



// GraphicsSettings graphics_settings(uint16_t ledCount)
// {
//   GraphicsSettings graphics_settings = {.rotationTime = get_rotation_time(), .ledCount = 16};
//   return graphics_settings;
// }

// uint8_t close_enough(uint16_t realAngle, uint16_t angle, GraphicsSettings *set) {
//   uint16_t x;
//   if (realAngle > angle) {
//     x = realAngle - angle;
//     return  x <= set->delta;
//   } else {
//     x = angle - realAngle;
//     return  x<= set->delta;
//   }
// }

uint16_t calc_real_angle(GraphicsSettings *set){
  float time = (float)get_time();
  float part = get_time()/(float)set->rotationTime;
  return (uint16_t)(32768 * part);
}

uint8_t nextA_flag = 0;
uint8_t nextB_flag = 0;

void refresh_graphics() {
  // calculate timing
  // if (nextA_flag) {
  //   OCR1A = next_timing(queue_on);
  //   printUIntToLCD(OCR1A,0,0);
  //   nextA_flag = 0;
  // }
  // if (nextB_flag) {
  //   OCR1B = next_timing(queue_off);
  //       printUIntToLCD(OCR1B,1,0);
  //   nextB_flag = 0;
  // }

  if (new_round()) {


    uint32_t angle = 200 * 1000;
    uint32_t prct = angle/3600;
    uint16_t timing = (uint16_t)(prct * (uint32_t)get_rotation_time()/1000);
    // float angle = (float)200;
    // float prct = angle/3600;
    // uint16_t timing = (int)(prct * get_rotation_time());

    printStringToLCD("hoi",1,0);
    printIntToLCD(timing,0,0);

    queue_on.data[0].timing = timing;
    queue_off.data[0].timing = timing + 100;
  }
    led_draw(16, leds);


    if (nextA_flag) {
      uint16_t next = next_timing(queue_on);
      OCR1A = next;
      nextA_flag = 0;
      printIntToLCD(next,0,5);

    }
    if (nextB_flag) {
      uint16_t next = next_timing(queue_off);
      OCR1B = next;
      nextB_flag = 0;
      printIntToLCD(next,1,5);
    }

}

// void draw(Sprite *objects, uint8_t count, uint16_t time, GraphicsSettings *set) {
//
//   // correct setting rotationtime
//   set->rotationTime = get_rotation_time();
//
//   // check if sprite in angle range
//   uint16_t real_angle = calc_real_angle(set);
//   Position *position = &objects->pos;
//
//   //printIntToLCD(close_enough(real_angle, position->angle, set),0,0);
//
//   if (close_enough(real_angle, position->angle, set)) {
//
//
//     led_draw(4, &objects->led);
//   }
//   else{
//
//
//     led_clear(16);
//   }
// }




ISR(TIMER1_COMPA_vect){
  if (!nextA_flag) {
    Queue_item item = next(&queue_on);
    leds[item.index] = item.led;
    nextA_flag = 1;
  }
}

ISR(TIMER1_COMPB_vect){
  if (!nextB_flag) {
  Queue_item item = next(&queue_off);
    leds[item.index] = item.led;
    nextB_flag = 1;
  }
}
