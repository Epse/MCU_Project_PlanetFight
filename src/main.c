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

void setup()
{
  // global enable interrupt
  SREG |= _BV(7);
  led_init();
  joy_init();
  initBoard();
  initLCD();
  clearLCD();
  backlightOn();
  engine_setup();

  // Set up TC0 for ticking
  // in CTC mode, max value 255 (which gives 60Hz update rate)
  TCCR0A = _BV(WGM01);
  TCCR1A = _BV(CS02) | _BV(CS00);
  OCR0A = 0xFF;
  TIMSK0 = _BV(OCIE0A);
}

void tick_interrupt() {
  //set_rotation_time(<sth>);
  tick();
}

int main(void)
{
  setup();
  while (1)
  {
    //set_rotation_time(<sth>);
    //render(<time_since_zero>)
  }
}

ISR(TIMER0_COMPA_vect) {
  tick_interrupt();
}
