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

// delta is the amount of ms since last tick
// returns true if game not finished
uint8_t tick(uint16_t time_since_zero);

void setUp(uint16_t time_per_rotation);

#endif
