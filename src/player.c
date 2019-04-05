#include "player.h"

Player player(uint8_t id) {
  Position p;
  uint16_t angle = id * (A_LIMIT / 2);
  if (angle > A_LIMIT) {
    angle = 0;
  }
  uint8_t err = pos(&p, angle, R_LIMIT / 2);
  if (err) {
    // TODO: Handle error
  }
  Player player = {.Id = id, .Pos = p, .Velocity = 0, .Health = START_HEALTH};
  return player;
}

void player_tick(Player *p) {
  uint8_t err = pos_adsub_radius(&(p->Pos), p->Velocity);
  if (err) {
    // TODO: Handle error
  }
}

void player_move(Player *p, char updown) {
  if (updown == 'U') {
    p->Velocity = P_MOVEMENT_SPEED;
  } else if (updown == 'D') {
    p->Velocity = -P_MOVEMENT_SPEED;
  } else {
    p->Velocity = 0;
  }
}

Sprite player_to_sprite(Player *p) {
  Led l = led(30, 255 * p->Id, 0, 255 - (255*p->Id));
  return sprite(p->Pos, l);
}

void player_shot(Player *p) {
  if (p->Health > BULLET_DAMAGE) {
    p->Health -= BULLET_DAMAGE;
  } else {
    p->Health = 0;
  }
}
