#ifndef PLAYER_H
#define PLAYER_H
#include <stdint.h>
#include <Position.h>
#include <Sprite.h>

#define START_HEALTH 200
#define BULLET_DAMAGE 10

typedef struct Player {
  uint8_t Id;
  Position Pos;
  int16_t Velocity;
  uint8_t Health;
} Player;

void player_tick(Player *p);
void player_shot(Player *p);
Sprite player_to_sprite(Player *p);

Player player(uint8_t id);

#endif
