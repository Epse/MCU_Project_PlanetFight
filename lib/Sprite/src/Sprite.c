#include "Sprite.h"

Sprite sprite(Position pos, Led led) {
  Sprite sprite = {.pos = pos, .led = led};
  return sprite;
}
