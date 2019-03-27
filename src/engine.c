#include "engine.h"

Player playerZero;
Player playerOne;
Bullet bullets[MAX_BULLETS];
GraphicsSettings set;

void render(uint16_t time) {
  // Count visible bullets
  // I know I now have to iterate over the bullets twice..
  // I'm sorry for my sins
  uint8_t count = 2;
  for (uint8_t i = MAX_BULLETS; i > 0; i--) {
    if (bullets[i].Lifetime > 0) {
      count++;
    }
  }
  Sprite sprites[count];
  sprites[0] = player_to_sprite(&playerOne);
  sprites[1] = player_to_sprite(&playerZero);
  for (uint8_t i = 2; i < count; i++) {
    sprites[i] = bullet_to_sprite(&(bullets[i]));
  }
  draw(sprites, count, time, &set);
}

uint8_t tick(uint16_t time_since_zero) {
  // Handle player inputs
  // TODO: interact with joysticks
  // Tick everything
  player_tick(&playerZero);
  player_tick(&playerOne);
  for (uint8_t i = MAX_BULLETS; i > 0; i--) {
    bullet_tick(&(bullets[i]));
  }
  // Check for collisions
  for (uint8_t i = MAX_BULLETS; i > 0; i--) {
    if (bullets[i].Lifetime == 0) {
      continue;
    }
    if (pos_equal(&(bullets[i].Pos), &(playerZero.Pos))) {
      bullets[i].Lifetime = 0;
      player_shot(&playerZero);
    } else if (pos_equal(&(bullets[i].Pos), &(playerOne.Pos))) {
      bullets[i].Lifetime = 0;
      player_shot(&playerOne);
    }
  }
  // Render
  render(time_since_zero);
  // Check for game end
  if (playerZero.Health == 0 || playerOne.Health == 0) {
    // TODO: Handle game end
    return 0;
  }
  return 1;
}

void setUp(uint16_t time) {
  // Just basically init the players lol
  playerZero = player(0);
  playerOne = player(1);
  GraphicsSettings s = {.rotationTime = time, .ledCount = 16, .delta = 5};
  set = s;
}

void setRotationTime(uint16_t time) {
  set.rotationTime = time;
}
