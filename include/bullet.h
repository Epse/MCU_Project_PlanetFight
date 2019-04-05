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
// How much of a radius between player and new bullet
#define BULLET_OFFSET 5

typedef struct Bullet {
  Position Pos;
  uint8_t Lifetime;
  uint8_t Left; // Make true if move left
} Bullet;

// Update the referenced bullet,
// decreases life and proceeds along it's path
void bullet_tick(Bullet *b);
Sprite bullet_to_sprite(Bullet *b);

// Create a bullet, shot by a player at playerPosition,
// in the correct direction
// 'L' for left, 'R' for right
Bullet bullet_shot(Position playerPosition, char direction);

Bullet bullet(Position *start, uint8_t left);

#endif
