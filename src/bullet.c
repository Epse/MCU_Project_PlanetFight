#include "bullet.h"

void bullet_tick(Bullet *b) {
  if (b->Lifetime < 1) { // Bullet is dead, don't care anymore
    return;
  }
  b->Lifetime--;
  if (b->Lifetime % R_DROP_DELAY == 0) { // Every n ticks, drop 1 block
    pos_sub_radius(&(b->Pos), 1);
  }
  if (b->Left) { // If the bullet was shot to the left
    pos_add_angle(&(b->Pos), A_VEL); // Move to the left
  } else {
    pos_sub_angle(&(b->Pos), A_VEL); // Else, move right
  }
}

// Create a bullet at a players position, shot to the left or right
Bullet bullet_shot(Position playerPosition, char leftright) {
  if (leftright == 'L') {
    // Add some offset, to prevent this bullet killing the own player
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
