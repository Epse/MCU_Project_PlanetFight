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

// Will be false when in debug mode
uint8_t normal_run = 0xFF;
// At 30Hz, this will overflow after about 36 minutes.
// I think we can use this for anything, if necessary
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
  set_up_snelheidssensor();
  set_up_motordriver();
  _delay_ms(15010);//wacht 15 seconden -- opstartprocedure schijf
  rotatie_snelheid(27); // 30 procent van de snelheidS


  void led_init();
  //Led Test[1] = led(100,50,0,0);
  Led leds[2];
  int b = 0;
  int g = 0;
  int r = 0;
  for (int i = 0; i < sizeof(leds); i++) {
    if (i<5) {
     b = 255;
     g = 255;
    }
    else{
      b = 0;
      r+=20;
    }
    leds[i] = led(255,b,g,r);
  }


   led_draw(3, leds);
   _delay_ms(2000);
   led_clear(3);
    _delay_ms(500);
/*
  led_draw(1, leds);
  _delay_ms(2000);
  led_clear(5);*/
  /*Test.green = 50;
  led_draw(4, &Test);
  _delay_ms(2000);
  void led_clear(uint8_t count);
  _delay_ms(2000);
  Test.green = 0;
  Test.red=0;
  Test.blue = 50;
  led_draw(8, &Test);*/

  while (1)
  {
    //clearLCD();
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
      //printStringToLCD("NORMAL", 0, 0);
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
