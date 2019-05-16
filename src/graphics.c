#include <avr/interrupt.h>
#include "graphics.h"
#include "snelheidssensor.h"
#include "Queue.h"

// 360 deg = 3600 (2^15)

Led leds[16];

// Queue voor ledjes die aan moeten
Queue queue_on;

// nul led en nul item
Led off_led;
uint8_t draw_token = 1;

// array voor indexen die uit moeten
Queue_int queue_int_off;

// opslag voor volgende sprites
Queue_sprite queue_sprites;

// Opzoektabel, afwijking graden tov ijkpunt in functie van straal_1
uint16_t straal_afwijking[12] = { 0, 554, 1108, 1662, 2215, 2769, 277, 831, 1385, 1938, 2492, 3046};

void set_up_graphics() {
  TIMSK1 |= _BV(OCIE1A);
  TIMSK1 |= _BV(OCIE1B);

  // globale uit-led
  off_led = led(0, 0, 0, 0);

  // zet initieel alle leds uit
  for (int i = 0; i < 16; i++) {
    leds[i] = off_led;
  }

  // dummy waarden in timecompare register
  OCR1A = 1000;
  OCR1B = OCR1A + 100;

  // initialiseer globale queues
  queue_on = queue();
  queue_int_off = queue_int();
  queue_sprites = queue_sprite();
}

// functie voor engine
void draw(Sprite *objects, uint8_t count){
  if (draw_token) {
    for (int i = 0; i < count; i++) {
      enqueue_sprite(&queue_sprites, objects[i]);
    }
    draw_token = 0;
  }
}

int p = 0;
uint16_t get_timing(Position pos){
  uint16_t angle = pos.angle;
  uint16_t straal = pos.radius;
  // compensatie plaats sensor 188
  angle = angle > 240? angle - 240 : angle + 3600 - 240;

  // compensatie plaats gaatje
  uint16_t afwijking = straal_afwijking[straal];
  angle = afwijking < angle? angle - afwijking : angle + 3600 - afwijking;

  float prct = (float)angle/ 3600;
  uint16_t timing = (uint16_t)(prct * get_rotation_time());
  if (timing == 0) {
    p++;
    printIntToLCD(p,1,2);
  }
  return timing;
}

// Bepaal index led ahv aantal graden
uint8_t get_segment(uint16_t degrees){
  return (uint8_t)(degrees/225);
}

Queue_item sprite_to_item(Sprite *sprite){
  uint16_t timing = get_timing(sprite->pos);
  uint8_t index = get_segment(sprite->pos.angle);
  return queue_item(index, timing, sprite->led);
}

int straal_1 = 1;
int straal_2 = 2;
uint16_t angle_1 = 225;
uint16_t angle_2 = 225;
uint8_t activity_signalled = 0;
int inactivity_counter = 100;


void refresh_graphics() {
  // herbereken timings
  if (new_round()) {
    // reset de queue

    Queue next_queue_on = queue();
    // vertaal sprites naar nieuwe queue
    while (queue_sprites.count != 0) {
      Sprite sprite = dequeue_sprite(&queue_sprites);
      Queue_item item = sprite_to_item(&sprite);
      enqueue(&next_queue_on, item);
    }
    draw_token = 1;

    sort(&next_queue_on);
    // printIntToLCD(next_queue_on.data[next_queue_on.front].timing, 0, 5);
    // printIntToLCD(next_queue_on.data[1].timing, 1, 5);

    aggregate(&next_queue_on);
    //
    // printIntToLCD(next_queue_on.data[next_queue_on.front].timing, 0, 10);
    // printIntToLCD(next_queue_on.data[1].timing, 1, 10);

    uint16_t tc_value = TCNT1;
    set_front(&next_queue_on, tc_value);

    // while (queue_int_off.count > 0) {
    //   uint16_t index = dequeue_int(&queue_int_off);
    //   leds[index] = led(0, 0, 0, 0);
    // }

    TIMSK1 &= ~_BV(OCIE1A);
    queue_on = next_queue_on;
    OCR1A = next_timing(queue_on);
    TIMSK1 |= _BV(OCIE1A);



    if (activity_signalled) {
      activity_signalled = 0;
      inactivity_counter = 100;
    } else {
      inactivity_counter--;
      if (inactivity_counter == 0) {
        inactivity_counter = 100;
        // zet alle leds uit
        TIMSK1 &= ~_BV(OCIE1A);
        for (int i = 0; i < 16; i++) {
          leds[i] = led(0, 0, 0, 0);
        }
        TIMSK1 |= _BV(OCIE1A);
      }
    }
  }
  led_draw(16, leds);
}

ISR(TIMER1_COMPA_vect){
  if (1) {
    if (queue_on.count != 0) {
      Queue_item items = next(&queue_on);
      while (items.count > 0) {
        Led_and_index obj = dequeue_led_and_index(&items);
        leds[obj.index] = obj.led;
        enqueue_int(&queue_int_off, obj.index);
      }
      // led uit binnen 150 slagen
      int nextB = OCR1A + 100;
      if (nextB > get_rotation_time() - 10) {
        while (queue_int_off.count > 0) {
          uint16_t index = dequeue_int(&queue_int_off);
          leds[index] = led(0, 0, 0, 0);
        }
      }
      else{
        OCR1B = nextB;
      }
    }
  }
}

ISR(TIMER1_COMPB_vect){
  while (queue_int_off.count > 0) {
    uint16_t index = dequeue_int(&queue_int_off);
    leds[index] = led(0, 0, 0, 0);
  }
  uint16_t next = next_timing(queue_on);
  OCR1A = next;
  activity_signalled = 1;
}
