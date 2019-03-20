#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>
#include <Position.h>
#include "leddriver.h"

typedef struct Sprite {
  Position pos;
  Led led;
} Sprite;

Sprite sprite(Position pos, Led led);

typedef struct GraphicsSettings {
  uint16_t rotationTime; // Time between zero points
  uint8_t ledCount;
  uint16_t delta; // How exact do we have to match an angle
} GraphicsSettings;

// time is time since last full rotation
void draw(Sprite *objects, uint8_t count, uint16_t time, GraphicsSettings *set);

void setEarthLeds(Led *topEarth, Led *bottomEarth);

#endif
