#include "bullet.h"

void bullet_tick(Bullet *b) {
  if (b->Lifetime < 1) {
    return;
  }
  b->Lifetime--;
  if (b->Lifetime % R_DROP_DELAY == 0) {
    pos_sub_radius(&(b->Pos), 1);
  }
  if (b->Left) {
    pos_add_angle(&(b->Pos), A_VEL);
  } else {
    pos_sub_angle(&(b->Pos), A_VEL);
  }
}

Bullet bullet_shot(Position playerPosition, char leftright) {
  if (leftright == 'L') {
    // This should be safe because argument by value
    pos_add_angle(&playerPosition, BULLET_OFFSET);
  } else { // If an invalid direction was passed, assume right
    pos_sub_angle(&playerPosition, BULLET_OFFSET);
  }
  return bullet(&playerPosition, leftright == 'L');
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

Bullet bullet(Position *start, uint8_t left) {
  Bullet b = {.Pos = *start, .Lifetime = LIFETIME, .Left = left};
  return b;
}
