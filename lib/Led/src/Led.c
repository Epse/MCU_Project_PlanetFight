#include "Led.h"

Led led(uint8_t i, uint8_t b, uint8_t g, uint8_t r) {
  Led var = {.intensity = i, .blue = b, .green = g, .red = r};
  return var;
}
