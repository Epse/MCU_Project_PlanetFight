#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>

typedef struct RGBI {
  uint8_t R; // Red
  uint8_t G; // Green
  uint8_t B; // Blue
  uint8_t I; // Intensity (the last 5 bits are used )
} RGBI;

RGBI newRGBI(uint8_t I, uint8_t B, uint8_t G, uint8_t R);

#endif
