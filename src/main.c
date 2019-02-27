#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "include/basics.h"

void setUp()
{
  // global enable interrupt
  SREG |= _BV(7);
}

int main(void)
{
  setUp();

  while (1)
  {

  }
}
