#include "player.h"

Player player(uint8_t id) {
  if (id == 0) {
    Position position = pos_unsafe(900, 4);
    Player player = {.Id = id, .Pos = position, .Velocity = 0,
      .Health = START_HEALTH, .Lifetime = 0};
    return player;
  }
  else {
    Position position = pos_unsafe(2700, 4);
    Player player = {.Id = id, .Pos = position, .Velocity = 0,
      .Health = START_HEALTH, .Lifetime = 0};
    return player;
  }
  Position p;
  uint16_t angle = id * (A_LIMIT / 2);
  if (angle > A_LIMIT) {
    angle = 0;
  }
  uint8_t err = pos(&p, angle, R_LIMIT / 2);
  if (err) {
    // TODO: Handle error
  }
  Player player = {.Id = id, .Pos = p, .Velocity = 0,
    .Health = START_HEALTH, .Lifetime = 0};
  return player;
}

void player_tick(Player *p) {
  uint8_t err = pos_adsub_radius(&(p->Pos), p->Velocity);
  p->Lifetime++;

  if (p->Lifetime % AUTO_DROP_DELAY == 0) {
    // If already at the bottom, take health away
    if (p->Pos.radius == 0) {
      p->Health--;
    } else {
      err = pos_sub_radius(&(p->Pos), 1);
    }
  }

  if (err) {
    // TODO: Handle error
  }
}

void player_move(Player *p, char updown) {
  if (updown == 'U') {
    if (p->Pos.radius == R_LIMIT) {
      p->Health--; // If you are already at the top, die stupid bitch
    }
    p->Velocity = P_MOVEMENT_SPEED;
  } else if (updown == 'D') {
    if (p->Pos.radius == 0) {
      p->Health--; // Verder naar beneden? lol ga maar mooi dood
    }
    p->Velocity = -P_MOVEMENT_SPEED;
  } else {
    p->Velocity = 0;
  }
}

Sprite player_to_sprite(Player *p) {
  Led l = led(31, 255, 255,255);//led(30, 255 * p->Id, 0, 255 - (255*p->Id));
  return sprite(p->Pos, l);
}

Led player_colour(Player *p) {
	return led(30, 255 * p->Id, 0, 255 - (255*p->Id));
}

void player_shot(Player *p) {
  if (p->Health > BULLET_DAMAGE) {
    p->Health -= BULLET_DAMAGE;
  } else {
    p->Health = 0;
  }
}
