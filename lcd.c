/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the AVR LCD driver - 8bit Mode
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#include<util/delay.h>
#include "lcd.h"
#include "gpio.h"


void LCD_sendCommand(uint8 command)
{
	/*The delays are set according to AC characteristics diagram from data sheet
	* we also increased the time of delay from microseconds to milliseconds for
	 * better performance on simulation and the hardware we use as its not best quality */
	GPIO_writePin(LCD_RS_PORT, LCD_RS_PIN, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(LCD_DATABUS_PORT, command);
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, LOGIC_LOW);
	_delay_ms(1);

}

void LCD_displayCharacter(uint8 character)
{
	GPIO_writePin(LCD_RS_PORT, LCD_RS_PIN, LOGIC_HIGH);		/* Data Mode RS=1 */
		_delay_ms(1);
		GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, LOGIC_HIGH);		/* Enable LCD E=1 */
		_delay_ms(1);
		GPIO_writePort(LCD_DATABUS_PORT, character);
		_delay_ms(1);
		GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, LOGIC_LOW);
		_delay_ms(1);
}

void LCD_init()
{
	GPIO_setupPortDirection(LCD_DATABUS_PORT, PORT_OUTPUT);
	GPIO_setupPinDirection(LCD_RS_PORT, LCD_RS_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_EN_PORT, LCD_EN_PIN, PIN_OUTPUT);
	_delay_ms(20);		/* LCD Power ON delay always > 15ms */
	LCD_sendCommand(LCD_2LINES_8BIT_MODE);
	LCD_sendCommand(LCD_CURSOR_ON_BLINK_OFF);
	LCD_sendCommand(LCD_CLEAR);

}
void LCD_displayString(const uint8 *string)
{
	uint8 index=0;
	while(string[index] != '\0')
	{
		LCD_displayCharacter(string[index]);
		index++;
	}

}
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR);			/*SENIDNG CLEAR COMMAND ON DATABUS*/
}
