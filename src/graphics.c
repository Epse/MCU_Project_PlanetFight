#include "graphics.h"

Led *topEarth;
Led *bottomEarth;

uint8_t close_enough(uint16_t realAngle, uint16_t angle, GraphicsSettings *set) {
  if (realAngle > angle) {
    return realAngle - angle <= set->delta;
  } else {
    return angle - realAngle <= set->delta;
  }
}

void set_earth_leds(Led top, Led bottom) {
  topEarth = &top;
  bottomEarth = &bottom;
}

// Mja dees is nie zo generiek
// ma afhankelijk van de schijf
// Jammer dan
uint8_t radius_lookup(uint8_t index) {
  // Dit is voor als de schijf rechtsom draait
  uint8_t lut[16] = {
    15, 0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7
  };

  return lut[index];
}

void draw(Sprite *objects, uint8_t count, uint16_t time, GraphicsSettings *set) {
  uint16_t angle = (time * A_LIMIT)/set->rotationTime;
  uint8_t offset = A_LIMIT / (set->ledCount-2);
  Led leds[set->ledCount];

  for (uint8_t i = 0; i < set->ledCount - 2; i++) {
    for (uint8_t j = 0; j < count; j++) {

      uint8_t radius = radius_lookup(i);

      if (close_enough(angle + offset*i, objects[j].pos.angle, set)
        && close_enough(radius, objects[j].pos.radius, set)) {
        leds[i] = objects[j].led;
      }
    }
  }
  leds[set->ledCount - 2] = *topEarth;
  leds[set->ledCount - 1] = *bottomEarth;
  led_draw(set->ledCount, leds);
}
