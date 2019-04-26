#include "selftest.h"

void self_test_loop() {
  // Test shit
  printStringToLCD("Self-Test Mode", 0, 0);
  _delay_ms(1000);
  clearLCD();
  // Test LED's
  printStringToLCD("LED Test", 0, 0);
  led_clear(18);
  Led leds[18];
  for (uint8_t i = 18; i > 0; i--) {
    leds[i] = led(30, 0xFF, 0xFF, 0xFF);
  }
  printCharToLCD('W', 1, 0);
  led_draw(18, &leds);
  _delay_ms(1000);

  for (uint8_t i = 18; i > 0; i--) {
    leds[i] = led(30, 0xFF, 0, 0);
  }
  printCharToLCD('B', 1, 0);
  led_draw(18, &leds);
  _delay_ms(1000);

  for (uint8_t i = 18; i > 0; i--) {
    leds[i] = led(30, 0, 0xFF, 0);
  }
  printCharToLCD('G', 1, 0);
  led_draw(18, &leds);
  _delay_ms(1000);

  for (uint8_t i = 18; i > 0; i--) {
    leds[i] = led(30, 0, 0, 0xFF);
  }
  printCharToLCD('R', 1, 0);
  led_draw(18, &leds);
  _delay_ms(1000);

  led_clear(18);
  clearLCD();

  // Test Joysticks
  printStringToLCD("Joystick test", 0, 0);
  _delay_ms(500);
  for (uint8_t j = 0; j < 2; j++) {
    clearLCD();
    printCharToLCD('J', 0, 0);
    appendUIntToLCD(j);

    // Up
    printCharToLCD('U', 0, 2);
    joy_tick();
    while (!joystick_is_up(joystick_status(j))) {
      printCharToLCD('?', 1, 0);
      joy_tick();
      _delay_ms(50);
    }
    printCharToLCD('V', 1, 0);
    _delay_ms(500);

    // Down
    printCharToLCD('D', 0, 2);
    joy_tick();
    while (!joystick_is_down(joystick_status(j))) {
      printCharToLCD('?', 1, 0);
      joy_tick();
      _delay_ms(50);
    }
    printCharToLCD('V', 1, 0);
    _delay_ms(500);

    // Left
    printCharToLCD('L', 0, 2);
    joy_tick();
    while (!joystick_is_left(joystick_status(j))) {
      printCharToLCD('?', 1, 0);
      joy_tick();
      _delay_ms(50);
    }
    printCharToLCD('V', 1, 0);
    _delay_ms(500);

    // Right
    printCharToLCD('R', 0, 2);
    joy_tick();
    while (!joystick_is_right(joystick_status(j))) {
      printCharToLCD('?', 1, 0);
      joy_tick();
      _delay_ms(50);
    }
    printCharToLCD('V', 1, 0);
    _delay_ms(500);

  }

  // Test Motor Driver
  // TODO: test motor driver
  // Test rotation sensor
  // TODO: test rotation sensor

  clearLCD();
  printStringToLCD("Done", 0, 0);
  while(1) {
    _delay_ms(1000);
  }
}
