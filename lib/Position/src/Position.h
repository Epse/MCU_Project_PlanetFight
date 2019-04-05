#ifndef POSITION_H
#define POSITION_H

#include <stdint.h>

#define R_LIMIT 15
#define A_LIMIT 1023

// Error codes
#define INVALID_R 1
#define INVALID_A 2

typedef struct Position {
  uint16_t angle;
  uint8_t radius; // Dees gaat tot aan een limiet
} Position;

Position pos_unsafe(uint16_t angle, uint8_t radius);
uint8_t pos(Position *dest, uint16_t angle, uint8_t radius);

uint8_t pos_add_radius(Position *a, uint8_t r);
uint8_t pos_add_angle(Position *p, uint16_t a);
uint8_t pos_sub_radius(Position *p, uint8_t r);
uint8_t pos_sub_angle(Position *p, uint16_t a);
uint8_t pos_adsub_radius(Position *p, int16_t r);

uint8_t pos_equal(Position *a, Position *b);

#endif
