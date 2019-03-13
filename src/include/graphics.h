#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>

typedef struct RGBI {
  uint8_t R; // Red
  uint8_t G; // Green
  uint8_t B; // Blue
  uint8_t I; // Intensity (the last 5 bits are used )
} RGBI;

#endif
