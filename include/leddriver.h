#ifndef LEDDRIVER_H
#define LEDDRIVER_H
#include <stdint.h>
void ledInit();

typedef struct Led {
  uint8_t intensity;
  uint8_t blue;
  uint8_t green;
  uint8_t red;
} Led;

void ledDraw(uint8_t count, struct Led *led);
void ledClear(uint8_t count);
Led led(uint8_t i, uint8_t b, uint8_t g, uint8_t r);

#endif
