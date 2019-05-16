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
  initBoard();
  initLCD();
  clearLCD();
  backlightOn();
  joy_init();
  engine_setup();
  set_up_snelheidssensor();
  set_up_graphics();



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
  for (size_t i = 0; i < 16; i++) {
    test[i] = led(31, 255, 255, 255);
  }
  //led_draw(16, test);
  #ifdef DEBUG
  uint8_t center_pressed_for = 0;
  #endif
  // testcode: maak sprites
  Sprite sprites[10];

  for (int i = 0; i < 10; i++){
    Position position = pos_unsafe( i * 100, i + 1);
    Led ledje = led(31, 255, 255, 0);
    sprites[i] = sprite(position, ledje);
  }

  int x = 0;
  while (1)
  {
    //clearLCD();

    //set_rotation_time(<sth>);
    //render(<time_since_zero>)

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

    // if (normal_run) {
    //   printStringToLCD("NORMAL", 0, 0);
    // } else {
    //   printStringToLCD("DEBUG", 0, 0);
    // }
    #endif

  	//Tick if required to do so
  	//maybe_tick();
    // Remove this when render works
    x++;
    if (x == 100){
      for (int i = 0; i < 6; i++) {
        sprites[i].pos.angle += 1;
        if (sprites[i].pos.angle > 3600) {
          sprites[i].pos.angle = 0;
        }
      }
      x = 0;
    }
    //render();

    draw(sprites, 2);
    refresh_graphics();
  }
}
