#ifndef PLAYER_H
#define PLAYER_H
#include <stdint.h>
#include <Position.h>
#include <Sprite.h>

#define START_HEALTH 200
#define BULLET_DAMAGE 10
#define P_MOVEMENT_SPEED 1
#define AUTO_DROP_DELAY 30

typedef struct Player {
  uint8_t Id;
  Position Pos;
  int16_t Velocity;
  uint8_t Health;
  uint16_t Lifetime;
} Player;

// Update the player,
// which moves him along at his required velocity
void player_tick(Player *p);

// Player p has been shot, update his health
void player_shot(Player *p);
Sprite player_to_sprite(Player *p);

// Update the player's velocity, move in desired direction
// give it "U" if up, "D" if down
void player_move(Player *p, char updown);

Player player(uint8_t id);

#endif
