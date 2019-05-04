#ifndef SPECIALCREENS_H
#define SPECIALCREENS_H

#include <stdint.h>
#include <Led.h>
#include <Joystick.h>
#include "graphics.h"
#include "player.h"

// Returns 1 when start condition is met
uint8_t start_screen();

void end_screen(Player *playerZero, Player *playerOne);

#endif
