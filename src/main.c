#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <Position.h>
#include "basics.h"
#include "graphics.h"
#include "leddriver.h"

void setUp()
{
  // global enable interrupt
  SREG |= _BV(7);
  ledInit();
}

void render() {
  Sprite things[1];
  Position p;
  if (pos(&p, 0, 15)) {
    return; // We gave too high a radius
  }

  Led l = led(10, 100, 100, 100);
  things[0] = sprite(p, l);

  GraphicsSettings set = {.delta = 5, .ledCount = 16, .rotationTime = 8};

  draw(things, 1, 0, &set);
}

int main(void)
{
  setUp();
  while (1)
  {
    _delay_ms(5);
  }
}
