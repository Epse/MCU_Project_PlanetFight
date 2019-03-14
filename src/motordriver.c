#include <avr/io.h>
#include "include/motordriver.h"

void motorInit() {
  // Set TIMER0 to phase accurate PWM
  TCCR0A = _BV(WGM00);
  TCCR0B = _BV(WGM02);
  // Falling edge on counter match (So counter limit is the pulse width)
  TCCR0A |= _BV(COM0A1);
  // Set OC01 to output
  DDRB |= _BV(DDB7);
  // Set pulse width to 50%
  OCR0A = 128;
}

void motorOn() {
  // Turn Timer/Counter 0 on and let it run at fck without prescaler
  TCCR0B |= _BV(CS02) | _BV(CS01);
  // TODO: write init sequence for driver
  // Actually, scratch that, TODO all the things
  // How do we get correct PWM frequency?
}

void motorOff() {
  // Disable all CS bits
  TCCR0B &= 0b11111000;
}

void motorPower(uint8_t power) {
  OCR0A = power;
}
