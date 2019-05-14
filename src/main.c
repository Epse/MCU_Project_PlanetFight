#define DEBUG

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
#include "Sprite.h"

#ifdef DEBUG
#include "selftest.h"
// Will be false when in debug mode
uint8_t normal_run = 0xFF;
#endif

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
  set_up_graphics();
  set_up_snelheidssensor();

  // Set the Center button to Input
  DDRC &= ~_BV(PC7);
  // Enable pullup
  PORTC |= _BV(PC7);

  #ifdef DEBUG
  // If center button pressed (during boot)
  if (~PINC & _BV(PC7)) {
    // disable interrupts
    SREG &= ~_BV(7);
    // Go to self-test
    // Reset the MCU to end it
    self_test_loop();
  }
  #endif



  // Start motor ed.

  set_up_motordriver();
  _delay_ms(15010);//wacht 15 seconden -- opstartprocedure schijf
  rotatie_snelheid(28); // 30 procent van de snelheid
  clearLCD();
}

int main(void)
{
  setup();

  Led test [16];
  for (size_t i = 0; i < sizeof(test); i++) {
    test[i] = led(31, 255, 255, 255);
  }
  //led_draw(16, test);
  #ifdef DEBUG
  uint8_t center_pressed_for = 0;
  #endif
  // testcode: maak sprite
  Position position_p1 = pos_unsafe(16000, 5);
  Led led_p1 = led(31, 255, 0, 255);
  sprite(position_p1, led_p1);
  //led_draw(5, &led_p1);
  //GraphicsSettings set = graphics_settings(300);
  Sprite sprite1 = sprite(position_p1, led_p1);

  led_draw(1,&led_p1);

  while (1)
  {
    //clearLCD();

    //set_rotation_time(<sth>);
    //render(<time_since_zero>)
    /*
    #ifdef DEBUG
    // If the center button is pressed..
    if ((~PINC) & _BV(7)) {
      center_pressed_for++;
    } else {
      if (center_pressed_for >= 20) { // If it has been pressed long enough
        normal_run = !normal_run; // Toggle between normal and debug
        if (normal_run) {
          TIMSK0 = _BV(OCIE0A); // This is a hack, disabling the interrupt in engine.c
        } else {
          TIMSK0 = 0;
        }
      } else if (center_pressed_for && !normal_run) {
      // If the button had been pressed, but is now released
      // and we are not normally running
      tick();
      }
      center_pressed_for = 0;
    }

    if (normal_run) {
      printStringToLCD("NORMAL", 0, 0);
    } else {
      printStringToLCD("DEBUG", 0, 0);
    }
    #endif
    */
	// Tick if required to do so
	//maybe_tick();
    // Remove this when render works
    //draw(&sprite1, 0, 0, &set);
    refresh_graphics();
    //_delay_ms(100);
    //testcode Graphics
    //printUIntToLCD(get_rotation_time(), 0, 5);
    //printUIntToLCD(get_time(), 1, 5);
    // clearLCD();
    // printIntToLCD(OCR1A,1,0);
    // printIntToLCD(OCR1B,1,5);
  }
}
