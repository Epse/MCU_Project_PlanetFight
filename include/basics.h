/*
 * dwenguinoBoard.h
 *
 *  Created on: Jan 19, 2016
 *      Author: Tom Neutens
 */

#ifndef DWENGUINO_BOARD_H_
#define DWENGUINO_BOARD_H_

#include <avr/io.h>

//	Constants
#define FALSE	    0
#define TRUE		!FALSE
#define HIGH		1
#define LOW			0
#define INPUT		0
#define OUTPUT		1
#define MAX_U8 (0xFF)
#define MAX_U16 (0xFFFF)

//	Data types
#define BYTE unsigned char

//	Pin assingments

//	LEDs

#define LEDS_DIR		DDRA
#define LEDS			PORTA

//	LCD display
#define LCD_DATA			PORTA
#define LCD_DATA_DIR		DDRA

#define LCD_BACKLIGHT_ON	PORTE |= 1<<3
#define LCD_BACKLIGHT_OFF	PORTE &= ~(1<<3)
#define LCD_BACKLIGHT_OUT	DDRE |= 1<<3
#define LCD_BACKLIGHT_IN	DDRE &= ~(1<<3)

#define LCD_RW_HIGH			PORTE |= 1<<1
#define LCD_RW_LOW			PORTE &= ~(1<<1)
//#define LCD_RW_IN			DDRE |= (1 << PE1)
#define LCD_RW_OUT			DDRE |= 1<<1

#define LCD_RS_HIGH			PORTE |= 1<<0
#define LCD_RS_LOW			PORTE &= ~(1<<0)
//#define LCD_RS_IN			DDRE |= (1 << PE0)
#define LCD_RS_OUT			DDRE |= 1<<0

#define LCD_EN_HIGH			PORTE |= 1<<2
#define LCD_EN_LOW			PORTE &= ~(1<<2)
//#define LCD_EN_IN			DDRE |= (1 << PE2)
#define LCD_EN_OUT			DDRE |= 1<<2


//	Servo connectors
#define SERVO1	PORTC0
#define SERVO2	PORTC1

// Some macros that make the code more readable
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

#endif	//DWENGUINO_BOARD_H_