#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>
#include <Position.h>
#include <Sprite.h>
#include "leddriver.h"
#include "basics.h"

#define LED_COUNT 16

typedef struct GraphicsSettings {
  uint16_t rotationTime; // Time between zero points
  uint16_t delta; // How exact do we have to match an angle
} GraphicsSettings;

// time is time since last full rotation
void draw(Sprite *objects, uint8_t count, uint16_t time, GraphicsSettings *set);

void set_earth_leds(Led topEarth, Led bottomEarth);

#endif
