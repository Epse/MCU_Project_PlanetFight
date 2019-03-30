#include "Joystick.h"

JoyStatus statJoyOne;
JoyStatus statJoyTwo;
JoyStatus risenOne;
JoyStatus risenTwo;

void joyInit() {
  DDRD &= 0b00001111;
  PORTD |= 0b11110000;
  DDRE &= 0b11110000;
  PORTE |= 0b00001111;
}

void readOne() {
  uint8_t stat = ~PORTE & 0b00001111;
  stat = stat >> 4;
  // Silly thing to detect the difference
  risenOne = (statJoyOne ^ stat) & stat;
  statJoyOne = (JoyStatus) stat;
}

void readTwo() {
  uint8_t stat = ~PORTD;
  stat &= 0b00001111;
  risenTwo = (statJoyTwo ^ stat) & stat;
  statJoyTwo = (JoyStatus) stat;
}

void joyTick() {
  readOne();
  readTwo();
}

JoyStatus joystick_risen(uint8_t id) {
  if (id == 0) {
    return risenOne;
  }
  if (id == 1) {
    return risenTwo;
  }
  return 0;
}

JoyStatus joystick_status(uint8_t id) {
  if (id == 0) {
    return statJoyOne;
  }
  if (id == 1) {
    return statJoyTwo;
  }
  return 0;
}

uint8_t joystick_is_up(JoyStatus s) {
  return s &= _BV(3);
}

uint8_t joystick_is_down(JoyStatus s) {
  return s &= _BV(1);
}

uint8_t joystick_is_left(JoyStatus s) {
  return s &= _BV(0);
}

uint8_t joystick_is_right(JoyStatus s) {
  return s &= _BV(2);
}
