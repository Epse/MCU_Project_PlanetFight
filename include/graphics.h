#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>
#include <Position.h>
#include <Sprite.h>
#include "leddriver.h"
#include "basics.h"



typedef struct GraphicsSettings {
  uint16_t rotationTime; // Time between zero points
  uint8_t ledCount;
  //uint16_t delta; // How exact do we have to match an angle
} GraphicsSettings;

void set_up_graphics();

// Ledarray, length 16;
Led* get_leds();

GraphicsSettings graphics_settings();

// time is time since last full rotation
void draw(Sprite *objects, uint8_t count, uint16_t time, GraphicsSettings *set);

void set_earth_leds(Led topEarth, Led bottomEarth);

#endif
