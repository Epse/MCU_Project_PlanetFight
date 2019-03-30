#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <Position.h>
#include "basics.h"
#include "graphics.h"
#include "leddriver.h"
#include <Joystick.h>

void setUp()
{
  // global enable interrupt
  SREG |= _BV(7);
  ledInit();
  joyInit();
}

int main(void)
{
  setUp();
  while (1)
  {
    _delay_ms(5);
  }
}
