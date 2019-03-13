#ifndef LEDDRIVER_H
#define LEDDRIVER_H
#include <stdint.h>
void ledInit();

struct Led {
  uint8_t intensity;
  uint8_t blue;
  uint8_t green;
  uint8_t red;
};

void ledDraw(uint8_t count, struct Led *led);
void ledClear(uint8_t count);
#endif
