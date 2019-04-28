#include "leddriver.h"

// LED_CLK_PIN: PB1
// LED_DTA_PIN: PB2
// LED_PORT: PORTB

void bitbang(uint8_t data) {
  SPDR = data;
  // SPIF = end of transmition flag, sets after shifting one byte
  while (!(SPSR & _BV(SPIF)))
    ;
}

void write_led(struct Led led)
{
  // LED Frame structure:
  // 111IIIII BBBBBBBB GGGGGGGG RRRRRRRR with I intensity

  // Write 3 1-bits and intensity
  bitbang(led.intensity | 0b11100000);
  bitbang(led.blue);
  bitbang(led.green);
  bitbang(led.red);
}

void led_init()
{
  // Don't disable SPI for power reduction
  PRR0 &= ~_BV(PRSPI);
  // Set clock and data to output
  DDRB |= _BV(PB2) | _BV(PB1);
  // Enable SPI, Master and clock to /64 (32)// To ensure correct sampling of the clock signal, the frequency of the SPI clock should never exceed fosc/4
  SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPR1)|_BV(DORD);
  //SPSR |= _BV(SPI2X);
}

// LED's are driven by sending 32 0-bits, then a frame per LED in order
// then 32 1-bits
void led_draw(uint8_t count, struct Led *leds)
{
  // Apparently this doesn't need the init sequence wut
  for (uint8_t i = 0; i < 4; i++) {
    bitbang(0);
  }

  for (uint8_t i = 0; i < count; i++) {
    write_led(leds[i]);
  }

  for (uint8_t i = 0; i < count; i++) {
    bitbang(0);
  }
}

void led_clear(uint8_t count)
{
  for (; count > 0; count--) {
    bitbang(0b11100000);
    bitbang(0);
    bitbang(0);
    bitbang(0);
  }

  for (uint8_t i = 0; i < 4; i++) {
    bitbang(0);
  }
}
