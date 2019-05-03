#include "graphics.h"

uint8_t close_enough(uint16_t realAngle, uint16_t angle, GraphicsSettings *set) {
  if (realAngle > angle) {
    return realAngle - angle <= set->delta;
  } else {
    return angle - realAngle <= set->delta;
  }
}

void draw(Sprite *objects, uint8_t count, uint16_t time, GraphicsSettings *set) {
  // TODO: Fill this in
  led_draw(set->ledCount, leds);
}
