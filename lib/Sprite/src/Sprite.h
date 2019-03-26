#ifndef SPRITE_H
#define SPRITE_H
#include <Position.h>
#include <Led.h>

typedef struct Sprite {
  Position pos;
  Led led;
} Sprite;

Sprite sprite(Position pos, Led led);

#endif
