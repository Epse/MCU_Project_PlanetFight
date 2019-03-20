#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "leddriver.h"
#include "basics.h"

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
  SPCR = _BV(SPE) | _BV(MSTR);
  SPSR |= _BV(SPI2X);
}

// LED's are driven by sending 32 0-bits, then a frame per LED in order
// then 32 1-bits
void ledDraw(uint8_t count, struct Led *leds)
{
  // Apparently this doesn't need the init sequence wut
  for (uint8_t i = 0; i < 4; i++) {
    bitBang(0);
  }

  for (uint8_t i = 0; i < count; i++) {
    writeLed(leds[i]);
  }

  for (uint8_t i = 0; i < count; i++) {
    bitBang(0);
  }
}

Led led(uint8_t i, uint8_t b, uint8_t g, uint8_t r) {
  Led var = {.intensity = i, .blue = b, .green = g, .red = r};
  return var;
}

void ledClear(uint8_t count)
{
  for (; count > 0; count--) {
    bitBang(0b11100000);
    bitBang(0);
    bitBang(0);
    bitBang(0);
  }

  for (uint8_t i = 0; i < 4; i++) {
    bitBang(0);
  }
}
