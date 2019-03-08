#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "include/leddriver.h"
#include "include/basics.h"

// LED_CLK_PIN: PB1
// LED_DTA_PIN: PB2
// LED_PORT: PORTB

void bitBang(uint8_t data) {
  SPDR = data;
  while (!(SPSR & _BV(SPIF)))
    ;
}

void writeLed(struct Led led)
{
  // LED Frame structure:
  // 111IIIII BBBBBBBB GGGGGGGG RRRRRRRR with I intensity

  // Write 3 1-bits and intensity
  bitBang(led.intensity | 0b11100000);
  bitBang(led.blue);
  bitBang(led.green);
  bitBang(led.red);
}

void ledInit()
{
  // Set clock and data to output
  DDRB |= _BV(PB2) | _BV(PB1);
  // Enable SPI, Master and clock to /64
  SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1);
}

// LED's are driven by sending 32 0-bits, then a frame per LED in order
// then 32 1-bits
void ledDraw(struct Led *leds, uint8_t count)
{
  // Apparently this doesn't need the init sequence wut
  //for (uint8_t i = 0; i < 4; i++) {
  //  bitBang(255);
  //}

  for (uint8_t i = 0; i < count; i++) {
    writeLed(leds[i]);
  }

  for (uint8_t i = 0; i < 4; i++) {
    bitBang(0);
  }
}
