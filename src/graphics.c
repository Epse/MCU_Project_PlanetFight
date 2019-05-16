#include <avr/interrupt.h>
#include "graphics.h"
#include "snelheidssensor.h"
#include "Queue.h"

// 360 deg = 3600 (2^15)

volatile Led leds[16];
uint8_t leds_changed = 0;

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



uint16_t rot_time = 0;
uint16_t get_correct_rotation_time(){
  uint16_t potential_rot_time = get_rotation_time();
  if (potential_rot_time > 1024) {
    rot_time = potential_rot_time;
  }
  return rot_time;
}

uint16_t get_timing(Position pos, uint16_t rotation_time){
  uint16_t angle = pos.angle;
  uint16_t straal = pos.radius;
  clearLCD();

  // compensatie plaats sensor 188
  angle = angle > 260? angle - 260 : angle + 3600 - 260;

  // compensatie plaats gaatje
  uint16_t afwijking = straal_afwijking[straal];
  angle = afwijking < angle? angle - afwijking : angle + 3600 - afwijking;


  float prct = (float)angle/ 3600;
  uint16_t timing = (uint16_t)(prct * rotation_time);
  if (timing < 1290 && timing > 700) {
    timing = 800;
  }
  printUIntToLCD(rotation_time,0,10);

  //printIntToLCD(timing,1,2);
  return timing;
}

// Bepaal index led ahv aantal graden
uint8_t get_segment(uint16_t degrees){
  return (uint8_t)(degrees/225);
}

Queue_item sprite_to_item(Sprite *sprite, uint16_t rotation_time){
  uint16_t timing = get_timing(sprite->pos, rotation_time);
  uint8_t index = get_segment(sprite->pos.angle);
  return queue_item(index, timing, sprite->led);
}

uint8_t activity_signalled = 0;
int inactivity_counter = 100;

void refresh_graphics() {
  // herbereken timings
  if (new_round()) {
    // reset de queue

    Queue next_queue_on = queue();
    // vertaal sprites naar nieuwe queue
    uint16_t rotation_time = get_correct_rotation_time();
    while (queue_sprites.count != 0) {
      Sprite sprite = dequeue_sprite(&queue_sprites);
      Queue_item item = sprite_to_item(&sprite, rotation_time);
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


    while (queue_int_off.count > 0) {
      uint16_t index = dequeue_int(&queue_int_off);
      leds[index] = led(0, 0, 0, 0);
    }


    uint16_t gevaar_uno = TCNT1;
    //TIMSK1 &= ~_BV(OCIE1A);
    queue_on = next_queue_on;
    //TIMSK1 |= _BV(OCIE1A);
    uint16_t gevaar_dos = TCNT1;

    printIntToLCD(gevaar_uno,0,2);
    printIntToLCD(gevaar_dos,1,2);

    //OCR1A = next_timing(queue_on);

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
  if (leds_changed != 0) {
    led_draw(16, leds);
  }
}



ISR(TIMER1_COMPA_vect){
  if (queue_on.count != 0) {
    Queue_item items = next(&queue_on);
    while (items.count > 0) {
      Led_and_index obj = dequeue_led_and_index(&items);
      leds[obj.index] = obj.led;
      enqueue_int(&queue_int_off, obj.index);
    }
    // led uit binnen 150 slagen
    int nextB = OCR1A + 100;
    if (nextB + 10 > get_correct_rotation_time()) {
      OCR1B = nextB - get_correct_rotation_time();
    }
    else{
      OCR1B = nextB;
    }
    leds_changed = 1;
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
  leds_changed = 1;
  printUIntToLCD(OCR1B,1,10);
}
