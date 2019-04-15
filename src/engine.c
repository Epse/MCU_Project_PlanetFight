#include "engine.h"

Player playerZero;
Player playerOne;
Bullet bullets[MAX_BULLETS];
GraphicsSettings set;

Led playerHealthLed(Player *p) {
  return led(20, 0, p->Health, 255-p->Health);
}

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

  set_earth_leds(playerHealthLed(&playerZero), playerHealthLed(&playerOne));

  draw(sprites, count, time, &set);
}

void add_bullet(Bullet b) {
  for (uint8_t i = MAX_BULLETS; i > 0; i--) {
    if (bullets[i].Lifetime == 0) {
      bullets[i] = b;
      return;
    }
  }
  // TODO: for now the amount of bullets on screen will act as a "cooldown"
  // Maybe eventually we might want to add a way of dumping the oldest bullet
}

// TODO: clean up
void handle_input() {
  JoyStatus zero = joystick_status(0);
  JoyStatus one = joystick_status(1);
  if (joystick_is_up(zero)) {
    player_move(&playerZero, 'U');
  } else if (joystick_is_down(zero)) {
    player_move(&playerOne, 'D');
  } else {
    player_move(&playerOne, 'N');
  }
  if (joystick_is_up(zero)) {
    player_move(&playerZero, 'U');
  } else if (joystick_is_down(zero)) {
    player_move(&playerOne, 'D');
  } else {
    player_move(&playerOne, 'N');
  }
  zero = joystick_risen(0);
  one = joystick_risen(1);
  if (joystick_is_right(zero)) {
    add_bullet(bullet_shot(playerZero.Pos, 'R'));
  } else if (joystick_is_right(zero)) {
    add_bullet(bullet_shot(playerZero.Pos, 'L'));
  }
  if (joystick_is_right(one)) {
    add_bullet(bullet_shot(playerOne.Pos, 'R'));
  } else if (joystick_is_right(one)) {
    add_bullet(bullet_shot(playerOne.Pos, 'L'));
  }
}

uint8_t tick() {
  if (set.rotationTime == 0) {
    return 1; // Not initialized yet
  }
  // Handle player inputs
  joy_tick();
  handle_input();
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
  // Check for game end
  if (playerZero.Health == 0 || playerOne.Health == 0) {
    // TODO: Handle game end
    return 0;
  }
  return 1;
}

void engine_setup() {
  // Just basically init the players lol
  playerZero = player(0);
  playerOne = player(1);
  GraphicsSettings s = {.rotationTime = 0, .ledCount = 16, .delta = 5};
  set = s;
}

void set_rotation_time(uint16_t time) {
  set.rotationTime = time;
}
