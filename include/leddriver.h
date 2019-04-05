#ifndef LEDDRIVER_H
#define LEDDRIVER_H
#include <stdint.h>
#include <Led.h>
void ledInit();

void ledDraw(uint8_t count, struct Led *led);
void ledClear(uint8_t count);

#endif
