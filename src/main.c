#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "include/basics.h"
#include "include/leddriver.h"
#include "include/graphics.h"

// X_RES could be changed by switching leds faster
#define X_RES 16
#define Y_RES 16

struct Led leds[2];
uint8_t ledCount = 2;

// Coordinate structure is buf[x][y]
struct RGBI buf[16][16];

void setUp()
{
  // global enable interrupt
  SREG |= _BV(7);
  ledInit();
  leds[0].intensity = 15;
  leds[1].intensity = 15;
  leds[0].red = 250;
  leds[0].blue = 100;
  leds[0].green = 0;
  leds[1].red = 250;
  leds[1].blue = 0;
  leds[1].green = 0;
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
