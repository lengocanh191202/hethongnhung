#include "LCD_I2C.h"
#include "setup.h"
#include "I2C.h"

/* Truyen du lieu qua I2C */
void LCD_WriteI2C(uint8_t Address, uint8_t *Data, int size)
{
	I2C_Start ();
	I2C_Address (Address);
	for (int i = 0; i < size; i++) {
		I2C_Write (*Data++);
	}
	I2C_Stop ();
}

/* Truyen du lieu vao LCD */
static void LCD_Write(LCD_Name* LCD, uint8_t Data, uint8_t Mode)
{
	char Data_H;
	char Data_L;
	uint8_t Data_I2C[4];
	Data_H = Data & 0xF0; 						//4 bit cao
	Data_L = (Data<<4) & 0xF0; 				//4 bit thap
	
	if(LCD->BACKLIGHT)
	{
		Data_H |= LCD_BACKLIGHT; 
		Data_L |= LCD_BACKLIGHT; 
	}
	
	if(Mode == LCD_DATA)
	{
		Data_H |= LCD_RS;
		Data_L |= LCD_RS;
	}
	else if(Mode == LCD_COMMAND)
	{
		Data_H &= ~LCD_RS;
		Data_L &= ~LCD_RS;
	}
	
	Data_I2C[0] = Data_H | LCD_EN;
	DelayMs(3);
	Data_I2C[1] = Data_H;
	Data_I2C[2] = Data_L | LCD_EN;
	DelayMs(3);
	Data_I2C[3] = Data_L;
	LCD_WriteI2C(SLAVE_ADDRESS_LCD, (uint8_t *) Data_I2C, 4);
}


void LCD_Init(LCD_Name* LCD, uint8_t Address, uint8_t Colums, uint8_t Rows)
{
	LCD->ADDRESS = Address;
	LCD->COLUMS = Colums;
	LCD->ROWS = Rows;
	
	LCD->FUNCTIONSET = LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS; //Chon che do 4 bit, 2 dong và 5x8 dots
	LCD->DISPLAYCTRL = LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF; //Bat man hinh, tat hien thi con tro va tat blink
	LCD->CURSORSHIFT = LCD_CURSORSHIFT | LCD_CURSORMOVE | LCD_MOVERIGHT; //Dat con tro o che do dich sang phai
	LCD->BACKLIGHT = LCD_BACKLIGHT;

	DelayMs(30);  								
	LCD_Write(LCD, 0x30, LCD_COMMAND);
  DelayMs(5);
	LCD_Write(LCD, 0x30, LCD_COMMAND);
	DelayMs(1);
	LCD_Write(LCD, 0x30, LCD_COMMAND);
	DelayMs(1);
	LCD_Write(LCD, 0x20, LCD_COMMAND);
	DelayMs(1);
	
	LCD_Write(LCD, LCD->FUNCTIONSET, LCD_COMMAND);
	LCD_Write(LCD, LCD->DISPLAYCTRL, LCD_COMMAND);
	LCD_Write(LCD, LCD->CURSORSHIFT, LCD_COMMAND);
	
	LCD_Write(LCD, LCD_CLEARDISPLAY, LCD_COMMAND);
	LCD_Write(LCD, LCD_RETURNHOME, LCD_COMMAND);
}

void LCD_Cursor(LCD_Name* LCD, uint8_t Xpos, uint8_t Ypos)
{
	uint8_t DRAM_ADDRESS = 0x00;
	if(Xpos >= LCD->COLUMS)
	{
		Xpos = LCD->COLUMS - 1;
	}
	if(Ypos >= LCD->ROWS)
	{
		Ypos = LCD->ROWS - 1;
	}
	
	if(Ypos == 0)
	{
		DRAM_ADDRESS = 0x00 + Xpos;
	}
	else if(Ypos == 1)
	{
		DRAM_ADDRESS = 0x40 + Xpos;
	}
	
	LCD_Write(LCD, LCD_SETDDRAMADDR | DRAM_ADDRESS, LCD_COMMAND);
}

void LCD_WriteChar(LCD_Name* LCD, char character)
{
	LCD_Write(LCD, character, LCD_DATA);
}

void LCD_WriteString(LCD_Name* LCD, char *String)
{
	while(*String) LCD_WriteChar(LCD, *String++);
}

void LCD_Clear(LCD_Name* LCD)
{
	LCD_Write(LCD, LCD_CLEARDISPLAY, LCD_COMMAND);
	DelayMs(3);
}
