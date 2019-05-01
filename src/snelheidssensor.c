/*#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "dwenguinoBoard.h"
#include "dwenguinoLCD.h"
#include "snelheidssensor.h"

//#include <stdint.h>

//#include <Position.h>
#include "basics.h"

#include "leddriver.h"*/

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <Position.h>
#include "basics.h"
#include "graphics.h"
#include "engine.h"
#include "leddriver.h"
#include <Joystick.h>
#include "dwenguinoBoard.h"
#include "dwenguinoLCD.h"
#include "snelheidssensor.h"
#include "Motordriver.h"




//Pin ICP1 : PD4

unsigned int last_value = 0;
unsigned int new_value = 0;
Led leds[3];//led(100,50,0,0);

void set_up_snelheidssensor()
{
  int b = 255;
  int g = 255;
  int r = 0;
  for (int i = 0; i < sizeof(leds); i++) {
    leds[i] = led(255,b,g,r);
  }

  initBoard();
  initLCD();
  clearLCD();
  backlightOn();

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



long rotationTimeX; // rare eenheid
long rotationTimeMs; // miliseconden
// DEZE INTERRUPT IS IJKINGSPUNT VOOR COMPONENT DIE LEDJES AANSTUURT
ISR(TIMER1_CAPT_vect){
  new_value = ICR1;
  //PORTA = 0b11111111;
  rotationTimeX += new_value/10 - last_value/10;
  //rotationTimeMs = rotationTimeX * 0.04;
  //clearLCD();
  //printUIntToLCD(rotationTimeX, 0, 10);
  last_value = new_value;
  rotationTimeX = 0;
  //led_draw(3, leds);
  //_delay_us(20);
  //led_clear(3);
}


ISR(TIMER1_OVF_vect){
  //PORTA ^= 0b11111111;
  rotationTimeX += 6554; // 2^16/10
}


/*ISR(TIMER1_COMPA_vect ){
  //PORTA ^= 0b11111111;
}*/
