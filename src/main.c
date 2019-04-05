#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <Position.h>
#include "basics.h"
#include "graphics.h"
#include "leddriver.h"
#include <Joystick.h>
#include "dwenguinoBoard.h"
#include "dwenguinoLCD.h"

void setUp()
{
  // global enable interrupt
  SREG |= _BV(7);
  ledInit();
  joyInit();
  initBoard();
  initLCD();
  clearLCD();
  backlightOn();
}

int main(void)
{
  setUp();
  while (1)
  {
    clearLCD();
    joyTick();
    _delay_ms(50);
  }
}
