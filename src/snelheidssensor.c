#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "dwenguinoBoard.h"
#include "dwenguinoLCD.h"
#include "snelheidssensor.h"

//Pin ICP1 : PD4

void set_up_snelheidssensor()
{
// global enable interrupt
SREG |= _BV(7);

//1. clockselect 0 1 1 => prescaler 64
TCCR1B |= _BV(CS11)|_BV(CS10);
TCCR1B &= ~_BV(CS12);

//Input capture interrupt enable
TIMSK1 = _BV(ICIE1);

//input capture Noise canceler enable & input capture edge select(rising edge)
TCCR1B |= _BV(ICNC1)|_BV(ICES1);

// not disable TCNT1
PRR0 &= ~_BV(PRTIM1);

//port PD4 (ICP1) op Input met pullup
DDRD &= ~_BV(DDD4);
PORTD |= _BV(PORTD4);
//TIFR1 = _BV(ICF1);

//Overflowvlag
TIMSK1 |= _BV(TOIE1);
}

volatile uint16_t ijkpunt = 0;
volatile uint16_t old_ijkpunt = 0;
volatile uint16_t time_span; // bereken volgende rotation_time
volatile uint16_t rotation_time; // rare eenheid
volatile uint8_t new_round_flag = 0;

// tijd sinds ijkpunt
uint16_t get_time()
{
  int TCNT_value = TCNT1 >> 3;
  int time;
  if ( TCNT_value > ijkpunt) {
    time = TCNT_value - ijkpunt;
  } else {
    time = 16384; //2^16 >> 3
    time += TCNT_value;
    time -= ijkpunt;
  }
  return time;
}

uint16_t get_rotation_time()
{
  return rotation_time << 2;
}


int round_count = 0;
//boolean, om nieuwe berekeningen te doen
uint8_t new_round()
{
  if (round_count == 4) {
    round_count = 0;
    if (new_round_flag != 0) {
      new_round_flag = 0;
      round_count++;
      if (round_count >= 1) {
        round_count = 0;
        return 1;
      }
      else {
        return 0;
      }
    }
    else{
      return 0;
    }
  }
  round_count++;
}

// ijkingspunt voor graphics
ISR(TIMER1_CAPT_vect){
  // bitshift to fit in integer
  ijkpunt = ICR1 >> 2;
  if (ijkpunt != 0) {
    time_span += ijkpunt;// - old_ijkpunt;
    //old_ijkpunt = ijkpunt;
    rotation_time = time_span;
    time_span = 0;
    TCNT1 = 0;
    new_round_flag = 1;
  }
}

ISR(TIMER1_OVF_vect){
  time_span += 16384; //2^16 >> 2
}
