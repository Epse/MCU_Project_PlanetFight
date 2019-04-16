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

// Will be false when in debug mode
uint8_t normal_run = 0xFF;
uint16_t tick_count = 0;

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
  // in CTC mode, max value 255 (which gives 30Hz update rate)
  // this is kinda fast, but I can't go slower.
  TCCR0A = _BV(WGM01);
  TCCR0B = _BV(CS02) | _BV(CS00);
  OCR0A = 0xFF;
  TIMSK0 = _BV(OCIE0A);

  // Set the Center button to Input
  DDRC &= ~_BV(PC7);
  // Enable pullup
  PORTC |= _BV(PC7);
}

void tick_interrupt() {
  //set_rotation_time(<sth>);
  tick();
  tick_count++;
}

int main(void)
{
  setup();
  uint8_t center_pressed_for = 0;
  while (1)
  {
    clearLCD();
    //set_rotation_time(<sth>);
    //render(<time_since_zero>)

    // If the center button is pressed..
    if ((~PINC) & _BV(7)) {
      center_pressed_for++;
    } else {
      if (center_pressed_for >= 20) { // If it has been pressed long enough
        normal_run = !normal_run; // Toggle between normal and debug
        if (normal_run) {
          TIMSK0 = _BV(OCIE0A);
        } else {
          TIMSK0 = 0;
        }
      } else if (center_pressed_for && !normal_run) {
      // If the button had been pressed, but is now released
      // and we are not normally running
        tick_interrupt(); // Manually tick
      }
      center_pressed_for = 0;
    }

    if (normal_run) {
      printStringToLCD("NORMAL", 0, 0);
    } else {
      printStringToLCD("DEBUG", 0, 0);
    }

    printUIntToLCD(tick_count, 1, 0);

    // Remove this when render works
    _delay_ms(50);
  }
}

ISR(TIMER0_COMPA_vect) {
  tick_interrupt();
}
