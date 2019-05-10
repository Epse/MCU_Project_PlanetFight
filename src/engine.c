#include "engine.h"

Player playerZero;
Player playerOne;
Bullet bullets[MAX_BULLETS];
GraphicsSettings set;

uint8_t gameState; // 0 is not yet started, 1 is running, 2 is game over.

uint8_t should_tick = 0;

void maybe_tick() {
	if (should_tick) {
		should_tick = 0;
		tick();
	}
}

static inline Led playerHealthLed(Player *p) {
  return led(20, 0, p->Health, 255-p->Health);
}

void render(uint16_t time) {
	if (gameState != 1 ) {
		return; // The other game states do their own simple rendering in tick()
	}
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

static void add_bullet(Bullet b) {
  for (uint8_t i = MAX_BULLETS; i > 0; i--) {
    if (bullets[i].Lifetime == 0) {
      bullets[i] = b;
      return;
    }
  }
  // TODO: for now the amount of bullets on screen will act as a "cooldown"
  // Maybe eventually we might want to add a way of dumping the oldest bullet
}

static inline void input_dispatch(Player *player, uint8_t index) {
	JoyStatus s = joystick_status(index);

  if (joystick_is_up(s)) {
    player_move(player, 'U');
  } else if (joystick_is_down(s)) {
    player_move(player, 'D');
  } else {
    player_move(player, 'N');
  }

	s = joystick_risen(index);
  if (joystick_is_right(s)) {
    add_bullet(bullet_shot(player->Pos, 'R'));
  } else if (joystick_is_right(s)) {
    add_bullet(bullet_shot(player->Pos, 'L'));
  }
}

static inline void handle_input() {
	input_dispatch(&playerZero, 0);
	input_dispatch(&playerOne, 1);
}

void tick() {
	if (gameState != 1) {
		if (gameState == 0) {
			gameState = start_screen() ? 1 : 0;
		}
		else {
			end_screen(&playerZero, &playerOne);
		}
	}
  if (set.rotationTime == 0) {
    return; // Not initialized yet
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
		gameState++;
  }
}

void engine_setup() {
  // Just basically init the players lol
  playerZero = player(0);
  playerOne = player(1);
  GraphicsSettings s = {.rotationTime = 0, .delta = 5};
  set = s;

  // Set up TC0 for ticking
  // in CTC mode, max value 255 (which gives 30Hz update rate)
  // this is kinda fast, but I can't go slower.
  TCCR0A = _BV(WGM01);
  TCCR0B = _BV(CS02) | _BV(CS00);
  OCR0A = 0xFF;
  TIMSK0 = _BV(OCIE0A);

}

void set_rotation_time(uint16_t time) {
  set.rotationTime = time;
}

ISR(TIMER0_COMPA_vect) {
	should_tick = 1;
}
