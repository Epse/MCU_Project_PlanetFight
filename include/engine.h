#ifndef ENGINE_H
#define ENGINE_H
#include <avr/interrupt.h>
#include <stdint.h>
#include <Position.h>
#include <Led.h>
#include <Sprite.h>
#include <Joystick.h>
#include "player.h"
#include "bullet.h"
#include "graphics.h"
#include "specialscreens.h"

#define MAX_BULLETS 5

void tick();
// Might tick, might not.
// Ticks if required
void maybe_tick();
// Update the LED status,
// to be called as fast as possible.
// Preferably update the rotation_time beforehand
void render();

void engine_setup();

void maybe_tick();

#endif
