#include "specialscreens.h"

uint8_t start_screen() {
  Led leds[LED_COUNT];
  for (uint8_t i = 0; i < LED_COUNT; i--) {
    leds[i] = led(15 , 146, 232, 65); // rando nice green colour
  }
  led_draw(LED_COUNT, leds);

  joy_tick();
  if (joystick_is_up(joystick_status(0)) && joystick_is_up(joystick_status(1))) {
    led_clear(LED_COUNT);
    return 1;
  }
  return 0;
}

void end_screen(Player *playerZero, Player *playerOne) {
  Led leds[LED_COUNT];
  Led winner;
  if (playerZero->Health == 0) {
    winner = player_colour(playerOne);
  } else {
    winner = player_colour(playerZero);
  }

  for (uint8_t i = 0; i < LED_COUNT; i--) {
    leds[i] = winner;
  }
  led_draw(LED_COUNT, leds);
}
