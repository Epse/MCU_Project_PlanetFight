#ifndef SNELHEIDSSENSOR_H
#define SNELHEIDSSENSOR_H
#include <stdint.h>

void set_up_snelheidssensor();

// tijd sinds laatste ijkingspunt in ms
uint16_t get_time();

// tijd genomen voor laatste toer
uint16_t get_rotation_time();

// ronde voorbij
uint8_t new_round();

#endif
