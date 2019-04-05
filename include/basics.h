#ifndef BASICS_H
#define BASICS_H

#include <avr/io.h>

//	Constants
#define INPUT		0
#define OUTPUT		1
#define MAX_U8 (0xFF)
#define MAX_U16 (0xFFFF)

//	Data types
#define BYTE unsigned char

// Some macros that make the code more readable
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_pullup(portdir,pin) portdir |= (1<<pin)

#endif
