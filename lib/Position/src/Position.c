#include "Position.h"

uint8_t validate_pos(Position *a) {
  if (a->radius > R_LIMIT) {
    return INVALID_R;
  }
  if (a->angle > A_LIMIT) {
    return INVALID_A;
  }
  return 0;
}

Position pos_unsafe(uint16_t angle, uint8_t radius) {
  Position pos = {.angle = angle, .radius = radius};
  return pos;
}

uint8_t pos(Position *dest, uint16_t angle, uint8_t radius) {
  if (radius > R_LIMIT) {
    return INVALID_R;
  }
  if (angle > A_LIMIT) {
    return INVALID_A;
  }

  dest->angle = angle;
  dest->radius = radius;
  return 0;
}

uint8_t add_radius(uint8_t a, uint8_t b) {
  a += b;
  if (a > R_LIMIT) {
    return R_LIMIT;
  }
  return a;
}

uint8_t pos_add_radius(Position *a, uint8_t r) {
  if (r > R_LIMIT) {
    return INVALID_R;
  }
  uint8_t res = validate_pos(a);
  if (res) {
    return res;
  }

  a->radius = add_radius(a->radius, r);
  return 0;
}

uint16_t add_angle(uint16_t a, uint16_t b) {
  a += b;
  return a % (A_LIMIT + 1);
}

uint8_t pos_add_angle(Position *p, uint16_t a) {
  if (a > A_LIMIT) {
    return INVALID_A;
  }
  uint8_t res = validate_pos(p);
  if (res) {
    return res;
  }

  p->angle = add_angle(p->angle, a);
  return 0;
}
