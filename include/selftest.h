#ifndef SELFTEST_H
#define SELFTEST_H

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "dwenguinoBoard.h"
#include "dwenguinoLCD.h"
#include <Led.h>
#include "leddriver.h"
#include <Joystick.h>

// This allows testing of physical configuration
void self_test_loop();

#endif
