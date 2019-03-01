#include <stdint.h>
#include <util/delay.h>
#include "include/leddriver.h"
#include "include/basics.h"

// Wait 2 microseconds between pulses
#define LED_CLK_WAIT 2

// LED_CLK_PIN: 0
// LED_DTA_PIN: 1
// LED_PORT: PORTF


void pulseClock()
{
  output_high(PORTF, 0);
  _delay_ms(LED_CLK_WAIT);
  output_low(PORTF, 0);
  _delay_ms(LED_CLK_WAIT);
}

void bitBang(uint8_t bits, uint8_t i) {
  for (; i > 0; i--) {
    if (bits & 0b10000000) {
      output_high(PORTF, 1);
    } else {
      output_low(PORTF, 1);
    }
    pulseClock();
    bits = bits << 1;
  }
}

void writeLed(struct Led led)
{
  // LED Frame structure:
  // 111IIIII BBBBBBBB GGGGGGGG RRRRRRRR with I intensity
  // Write 3 1-bits
  for (uint8_t i = 0; i < 3; i++) {
    output_high(PORTF, 1);
    pulseClock();
  }
  // We only use the last 3 bits of intensity
  uint8_t intensity = led.intensity << 3;
  bitBang(intensity, 5);
}

void ledInit()
{
  // Set clock and data to output
  set_output(PORTF, 0);
  set_output(PORTF, 1);
  output_low(PORTF, 0);
  output_low(PORTF, 1);
}

// LED's are driven by sending 32 0-bits, then a frame per LED in order
// then 32 1-bits
void ledDraw(struct Led *leds, uint8_t count)
{
  // START FRAME
  // send 32 0-bits
  output_low(PORTF, 1);
  for (uint8_t i = 0; i < 32; i++) {
    pulseClock();
  }

  // LED FRAMES
  for (int i = 0; i < count; i++) {
    writeLed(leds[i]);
  }

  // END FRAMES
  // send 32 1-bits
  output_high(PORTF, 1);
  for (uint8_t i = 0; i < 32; i++) {
    pulseClock();
  }
}
