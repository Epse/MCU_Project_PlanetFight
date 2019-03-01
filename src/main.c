#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "include/basics.h"
#include "include/leddriver.h"

struct Led leds[2];
uint8_t ledCount = 2;

void setUp()
{
  // global enable interrupt
  SREG |= _BV(7);
  ledInit();
  leds[1].intensity = 30;
  leds[2].intensity = 30;
  leds[1].red = 250;
  leds[1].blue = 0;
  leds[1].green = 0;
  leds[2].red = 250;
  leds[2].blue = 0;
  leds[2].green = 0;
}

int main(void)
{
  setUp();

  while (1)
  {
    ledDraw(&leds, ledCount);
    _delay_ms(100);
  }
}
