#ifndef LED_H
#define LED_H
#include <stdint.h>

typedef struct Led {
  uint8_t intensity;
  uint8_t blue;
  uint8_t green;
  uint8_t red;
} Led;

Led led(uint8_t i, uint8_t b, uint8_t g, uint8_t r);

#endif
