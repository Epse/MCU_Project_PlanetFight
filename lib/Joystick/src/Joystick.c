#include "Joystick.h"

JoyStatus statJoyOne;
JoyStatus statJoyTwo;
JoyStatus risenOne;
JoyStatus risenTwo;

void joy_init() {
  DDRD &= 0b11110000;
  PORTD |= 0b00001111;
  DDRE &= 0b00001111;
  PORTE |= 0b11110000;
}

void readOne() {
  // All these casts are to force 8-bit operations
  uint8_t stat = (uint8_t)(~PINE) & (uint8_t)0b11110000;
  stat = (uint8_t) stat >> 4;
  // Silly thing to detect the difference
  risenOne = ((uint8_t)statJoyOne ^ (uint8_t)stat) & (uint8_t)stat;
  statJoyOne = (JoyStatus) stat;
}

void readTwo() {
  uint8_t stat = (uint8_t)~PIND;
  stat &= (uint8_t)0b00001111;
  risenTwo = ((uint8_t)statJoyTwo ^ stat) & (uint8_t)stat;
  statJoyTwo = (JoyStatus) stat;
}

void joy_tick() {
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
  return s &= (uint8_t)_BV(3);
}

uint8_t joystick_is_down(JoyStatus s) {
  return s &= (uint8_t)_BV(1);
}

uint8_t joystick_is_left(JoyStatus s) {
  return s &= (uint8_t)_BV(0);
}

uint8_t joystick_is_right(JoyStatus s) {
  return s &= (uint8_t)_BV(2);
}
