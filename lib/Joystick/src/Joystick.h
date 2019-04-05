#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <avr/io.h>
#include <stdint.h>

// Joystick 0 is connected with PORTE,
// Joystick 1 with PORTD

typedef uint8_t JoyStatus;

void joyInit();
void joyTick();

uint8_t joystick_is_up(JoyStatus s);
uint8_t joystick_is_down(JoyStatus s);
uint8_t joystick_is_left(JoyStatus s);
uint8_t joystick_is_right(JoyStatus s);

JoyStatus joystick_risen(uint8_t id);
JoyStatus joystick_status(uint8_t id);

#endif
