#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>
#include <Position.h>
#include <Sprite.h>
#include "leddriver.h"
#include "basics.h"

#define LED_COUNT 16

void set_up_graphics();

// Ledarray, length 16;
Led* get_leds();

// time is time since last full rotation
void draw(Sprite *objects, uint8_t count);

#endif
