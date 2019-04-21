#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "dwenguinoBoard.h"
#include "dwenguinoLCD.h"

//Pin ICP1 : PD4

unsigned int last_value = 0;
unsigned int new_value = 0;

void set_up_snelheidssensor()
{
  initBoard();
  initLCD();
  clearLCD();
  backlightOn();

// global enable interrupt
SREG |= _BV(7);

//1. clockselect 0 1 0 => prescaler 8
TCCR1B |= _BV(CS11);
TCCR1B &= ~(_BV(CS10)|_BV(CS12));

//Input capture interrupt enable
TIMSK1 = _BV(ICIE1);

//input capture Noise canceler enable & input capture edge select(rising edge)
TCCR1B |= _BV(ICNC1)|_BV(ICES1);

// not disable TCNT1
PRR0 &= ~_BV(PRTIM1);

// ledjes op output
DDRA = 0b11111111;
PORTA = 0b00010000;

//port PD4 (ICP1) op Input met pullup
DDRD &= ~_BV(DDD4);
PORTD |= _BV(PORTD4);
//TIFR1 = _BV(ICF1);


//Overflowvlag
TIMSK1 |= _BV(TOIE1);
}


// DEZE INTERRUPT IS IJKINGSPUNT VOOR COMPONENT DIE LEDJES AANSTUURT
ISR(TIMER1_CAPT_vect){
  new_value = ICR1;
  //PORTA = 0b11111111;

  printIntToLCD(last_value-new_value, 0, 5);
  last_value = new_value;
}


ISR(TIMER1_OVF_vect){
  PORTA ^= 0b11111111;
}


ISR(TIMER1_COMPA_vect ){
  //PORTA ^= 0b11111111;
}
