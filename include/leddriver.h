#ifndef LEDDRIVER_H
#define LEDDRIVER_H
#include <stdint.h>
#include <Led.h>
#include <util/delay.h>
#include <avr/io.h>
#include "basics.h"

void led_init();

void led_draw(uint8_t count, struct Led *led);
void led_clear(uint8_t count);

#endif
