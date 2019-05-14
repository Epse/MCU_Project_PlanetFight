#include <avr/interrupt.h>
#include "graphics.h"
#include "snelheidssensor.h"
#include "Queue.h"

// 360 deg = 3600 (2^15)

Led leds[16];

// Queue voor ledjes die aan moeten
Queue queue_on;

// array voor indexen die uit moeten
Queue_int queue_int_off;

// Opzoektabel, afwijking graden tov ijkpunt in functie van straal_1
uint16_t straal_1_afwijking[12] = { 0, 554, 1108, 1662, 2215, 2769, 277, 831, 1385, 1938, 2492, 3046};

// Bepaal index led ahv aantal graden
uint16_t get_segment(uint16_t degrees){
  return degrees/225;
}

//returns zero led
Led off_led;


void set_up_graphics() {


  // globale uit-led
  off_led = led(0, 0, 0, 0);

  for (int i = 0; i < sizeof(leds); i++) {
    leds[i] = off_led;
  }

  OCR1A = 1000;
  OCR1B = OCR1A + 100;

  queue_on = queue();

  //temp hardcoded values
  Queue_item Q_item1 = queue_item();
  Queue_item Q_item2 = queue_item();

  Q_item1.led = led(30, 255, 255, 0);
  Q_item1.index = 5;
  Q_item1.timing = 89;

  Q_item2.led = led(30, 255, 0, 255);
  Q_item2.index = 5;
  Q_item2.timing = 1000;

  enqueue(&queue_on, Q_item1);
  enqueue(&queue_on, Q_item2);
}

Led* get_leds(){
  return leds;
}

uint16_t calc_real_angle_1(GraphicsSettings *set){
  float time = (float)get_time();
  float part = get_time()/(float)set->rotationTime;
  return (uint16_t)(32768 * part);
}

uint16_t get_timing(uint16_t angle_1, uint8_t straal_1){
  // compensatie plaats sensor 188
  angle_1 = angle_1 > 240? angle_1 - 240 : angle_1 + 3600 - 240;

  // compensatie plaats gaatje
  uint16_t afwijking = straal_1_afwijking[straal_1];
  angle_1 = afwijking < angle_1? angle_1 - afwijking : angle_1 + 3600 - afwijking;

  float prct = (float)angle_1/ 3600;
  return (int)(prct * get_rotation_time());
}

uint8_t nextA_flag = 0;
uint8_t nextB_flag = 0;


int straal_1 = 1;
int straal_2 = 2;
uint16_t angle_1 = 225;
uint16_t angle_2 = 225;
uint8_t activity_signalled = 0;
int inactivity_counter = 5;
void refresh_graphics() {
  //
  if (new_round()) {
    angle_1+= 30;
    angle_2+=30;
    if(angle_1 >= 3600){
      angle_1 = 0;
      straal_1++;
      if (straal_1 == 11) {
        straal_1 = 1;
      }
    }
    if(angle_2 >= 3600){
      angle_2 = 0;
      straal_2++;
      if (straal_2 == 11) {
        straal_2 = 1;
      }
    }



    uint16_t timing_1 = get_timing(angle_1, straal_1);
    uint16_t timing_2 = get_timing(angle_2, straal_2);

    queue_on.data[0].timing = timing_1;
    //queue_off.data[0].timing_1 = timing_1 + 100;
    queue_on.data[0].index = get_segment(angle_1);
    //queue_off.data[0].index = get_segment(angle_1);
    queue_on.data[1].timing = timing_2;
    queue_on.data[1].index = get_segment(angle_2);

    sort(&queue_on);

    if (activity_signalled) {
      activity_signalled = 0;
    } else {
      inactivity_counter--;
      if (inactivity_counter == 0) {
        inactivity_counter = 5;
        led_clear(16);
        nextA_flag = 1;
        nextB_flag = 1;
      }
    }


  }
  led_draw(16, leds);

  if (nextA_flag) {
    uint16_t next = next_timing(queue_on);
    OCR1A = next;
    nextA_flag = 0;
  }

  // if (nextB_flag) {
  //   uint16_t next = next_timing_1(queue_off);
  //   OCR1B = next;
  //   nextB_flag = 0;
  //   activity_signalled = 1;
  // }
}


ISR(TIMER1_COMPA_vect){
  if (!nextA_flag) {
    Queue_item item = next(&queue_on);
    leds[item.index] = item.led;
    nextA_flag = 1;
    // led uit binnen 100 slagen
    OCR1B = OCR1A + 100;
    enqueue_int(&queue_int_off, item.index);
  }
}

ISR(TIMER1_COMPB_vect){

  while (queue_int_off.count > 0) {
    uint16_t index = dequeue_int(&queue_int_off);
    leds[index] = off_led;
  }


  // if (!nextB_flag) {
  // Queue_item item = next(&queue_off);
  //   leds[item.index] = item.led;
  //   nextB_flag = 1;
  // }
}
