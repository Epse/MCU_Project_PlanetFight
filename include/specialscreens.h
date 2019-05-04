#ifndef SPECIALCREENS_H
#define SPECIALCREENS_H

#include <stdint.h>
#include <Led.h>
#include <Joystick.h>
#include "graphics.h"
#include "player.h"

uint8_t start_screen();

void end_screen(Player playerZero, Player playerOne);

#endif
