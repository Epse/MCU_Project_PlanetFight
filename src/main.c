#include <stdint.h>
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
RGBI buf[16][16];

void setUp()
{
  // global enable interrupt
  SREG |= _BV(7);
  ledInit();
  leds[0].intensity = 5;
  leds[1].intensity = 5;
  leds[0].red = 100;
  leds[0].blue = 100;
  leds[0].green = 0;
  leds[1].red = 100;
  leds[1].blue = 0;
  leds[1].green = 0;
}

int main(void)
{
  setUp();

  uint8_t i = 0;
  uint8_t j = 150;
  uint8_t k = 200;

  while (1)
  {
    ledDraw(ledCount, leds);
    leds[0].blue = i;
    leds[1].blue = ~i;
    leds[0].green = ~j;
    leds[1].green = j;
    leds[0].red = k;
    leds[1].red = ~k;
    i++;
    j++;
    k++;
    _delay_ms(5);
  }
}
