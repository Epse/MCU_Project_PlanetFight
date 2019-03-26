#ifndef BULLET_H
#define BULLET_H
#include <stdint.h>
#include <Position.h>
#include <Sprite.h>

// How many degrees to increase per tick
#define A_VEL 1
// How many ticks between 1 radius decrease
#define R_DROP_DELAY 5
// How many ticks a bullet lives
#define LIFETIME 200

typedef struct Bullet {
  Position Pos;
  uint8_t Lifetime;
} Bullet;

void bullet_tick(Bullet *b);
Sprite bullet_to_sprite(Bullet *b);

Bullet bullet(Position start);

#endif
