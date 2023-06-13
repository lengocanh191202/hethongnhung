#ifndef __LCD_I2C_H
#define __LCD_I2C_H

#include "stm32f10x.h"                  // Device header

#define SLAVE_ADDRESS_LCD 0x4E

#define LCD_EN 0x04  // Enable bit
#define LCD_RW 0x02  // Read/Write bit
#define LCD_RS 0x01  // Register select bit

#define LCD_COMMAND 			0x00
#define LCD_DATA 				0x01

// Commands
#define LCD_CLEARDISPLAY 		0x01
#define LCD_RETURNHOME 			0x02

#define LCD_ENTRYMODESET 		0x04
#define LCD_DISPLAYCONTROL 	0x08
#define LCD_CURSORSHIFT 		0x10
#define LCD_FUNCTIONSET 		0x20
#define LCD_SETCGRAMADDR 		0x40
#define LCD_SETDDRAMADDR	 	0x80

// Flags for display entry mode
#define LCD_ENTRYRIGHT 			0x00
#define LCD_ENTRYLEFT 			0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// Flags for display on/off control
#define LCD_DISPLAYON 			0x04
#define LCD_DISPLAYOFF 			0x00
#define LCD_CURSORON 			  0x02
#define LCD_CURSOROFF 			0x00
#define LCD_BLINKON 			  0x01
#define LCD_BLINKOFF 			  0x00

// Flags for display/cursor shift
#define LCD_DISPLAYMOVE 		0x08
#define LCD_CURSORMOVE 			0x00
#define LCD_MOVERIGHT 			0x04
#define LCD_MOVELEFT 			  0x00

// Flags for function set
#define LCD_8BITMODE 			0x10
#define LCD_4BITMODE 			0x00
#define LCD_2LINE 				0x08
#define LCD_1LINE 				0x00
#define LCD_5x10DOTS 			0x04
#define LCD_5x8DOTS 			0x00

#define LCD_BACKLIGHT 		0x08
#define LCD_NOBACKLIGHT 	0x00

typedef struct
{
	uint8_t ADDRESS;
	uint8_t COLUMS;
	uint8_t ROWS;
	uint8_t ENTRYMODE;
	uint8_t DISPLAYCTRL;
	uint8_t CURSORSHIFT;
	uint8_t FUNCTIONSET;
	uint8_t BACKLIGHT;
} LCD_Name;

void LCD_Init(LCD_Name* LCD, uint8_t Address, uint8_t Colums, uint8_t Rows);
void LCD_Cursor(LCD_Name* LCD, uint8_t Xpos, uint8_t YPos);
void LCD_WriteChar(LCD_Name* LCD, char character);
void LCD_WriteString(LCD_Name* LCD, char *String);
void LCD_Clear(LCD_Name* LCD);
#endif
