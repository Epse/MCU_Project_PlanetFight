#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "include/basics.h"

void setUp()
{
  // global enable interrupt
  SREG |= _BV(7);
  //dag stef
}

int main(void)
{
  setUp();

  while (1)
  {
    //Dit is de hoofdlus
  }
}
