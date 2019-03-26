#include "bullet.h"

void bullet_tick(Bullet *b) {
  if (b->Lifetime < 1) {
    return;
  }
  b->Lifetime--;
  if (b->Lifetime % R_DROP_DELAY == 0) {
    pos_sub_radius(&(b->Pos), 1);
  }
  pos_sub_angle(&(b->Pos), A_VEL);
}

Sprite bullet_to_sprite(Bullet *b) {
  Led l;
  if (b->Lifetime > 0) {
    l = led(30, 255, 255, 255);
  } else {
    l = led(0, 0, 0, 0);
  }
  return sprite(b->Pos, l);
}

Bullet bullet(Position start) {
  Bullet b = {.Pos = start, .Lifetime = LIFETIME};
  return b;
}