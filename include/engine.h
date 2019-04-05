#ifndef ENGINE_H
#define ENGINE_H
#include <stdint.h>
#include <Position.h>
#include <Led.h>
#include <Sprite.h>
#include <Joystick.h>
#include "player.h"
#include "bullet.h"
#include "graphics.h"

#define MAX_BULLETS 20

// Updates basically everything and draws to screen
// Should be called at a very constant pace
// returns true if game not finished
uint8_t tick(uint16_t time_since_zero);

void engine_setup(uint16_t time_per_rotation);

#endif
