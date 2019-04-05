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

// Construct a Position, returns an error code
// when radius or angle is invalid
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

// Helper function to add radia together,
// clamps them to the correct limit
uint8_t add_radius(uint8_t a, uint8_t b) {
  a += b;
  if (a > R_LIMIT) {
    return R_LIMIT;
  }
  return a;
}

// Subtract radia, clamping to 0
uint8_t sub_radius(uint8_t a, uint8_t b) {
  if (b > a) {
    return 0;
  }
  return a - b;
}

// Add a value onto the radius
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

uint8_t pos_sub_radius(Position *p, uint8_t r) {
  uint8_t res = validate_pos(p);
  if (res) {
    return res;
  }
  if (r > R_LIMIT) {
    return INVALID_R;
  }
  p->radius = sub_radius(p->radius, r);
  return 0;
}

uint16_t add_angle(uint16_t a, uint16_t b) {
  a += b;
  return a % (A_LIMIT + 1);
}

uint16_t sub_angle(uint16_t a, uint16_t b) {
  if (b > a) {
    return 0;
  }
  return b-a;
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

uint8_t pos_sub_angle(Position *p, uint16_t a) {
  if (a > A_LIMIT) {
    return INVALID_A;
  }
  uint8_t res = validate_pos(p);
  if (res) {
    return res;
  }
  p->angle = sub_angle(p->angle, a);
  return 0;
}

// Add a signed value onto the radius
// Does some funky typecasting
uint8_t pos_adsub_radius(Position *p, int16_t r) {
  if (r > R_LIMIT || r < -R_LIMIT) {
    return INVALID_R;
  }
  uint8_t res = validate_pos(p);
  if (res) {
    return res;
  }
  int16_t newr =  (int16_t)p->radius + r;
  if (newr < 0) {
    newr = 0;
  }
  if (newr > R_LIMIT) {
    newr = R_LIMIT;
  }
  p->radius = (uint8_t)newr;
  return 0;
}

// Equality test
uint8_t pos_equal(Position *a, Position *b) {
  return a->angle == b->angle && a->radius == b->radius;
}
