#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>
#include <Position.h>
#include <Sprite.h>
#include "leddriver.h"
#include "basics.h"

void set_up_graphics();

//void refresh_graphics();

// time is time since last full rotation
void draw(Sprite *objects, uint8_t count);

#endif
