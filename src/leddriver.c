#include "leddriver.h"

// LED_CLK_PIN: PB1
// LED_DTA_PIN: PB2
// LED_PORT: PORTB

// Stupidly write data, blocking
static inline void bitbang(uint8_t data) {
  SPDR = data;
  while (!(SPSR & _BV(SPIF)));
}

static inline void write_led(Led led)
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
  // Set clock and data to output
  DDRB |= _BV(PB2) | _BV(PB1);
  // Enable SPI, Master and clock to /2
  SPCR = _BV(SPE) | _BV(MSTR);
  SPSR |= _BV(SPI2X);
}

// LED's are driven by sending 32 0-bits, then a frame per LED in order
// then 32 1-bits
void led_draw(uint8_t count, Led *leds)
{
  for (uint8_t i = 0; i < 4; i++) {
    bitbang(0);
  }

  for (int i = 0; i < count; i++) {
    write_led(leds[i]);
  }

  // This could be skipped to save time but whatever
  for (uint8_t i = 0; i < count; i++) {
    bitbang(0);
  }
}

void write_zero_led() {
  bitbang(0b11100000);
  bitbang(0);
  bitbang(0);
  bitbang(0);
}

void led_clear(uint8_t count)
{
  for (; count > 0; count--) {
    write_zero_led();
  }

  for (uint8_t i = 0; i < 4; i++) {
    bitbang(0);
  }
}
