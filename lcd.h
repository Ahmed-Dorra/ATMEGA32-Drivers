/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: header file for the AVR LCD driver - 8bit Mode
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Static configurations of LCD */
#define	LCD_RS_PORT					PORTC_ID
#define	LCD_RS_PIN					PIN6_ID

#define	LCD_EN_PORT					PORTC_ID
#define	LCD_EN_PIN					PIN7_ID

#define	LCD_DATABUS_PORT			PORTD_ID

/*LCD COMMANDS*/
#define LCD_2LINES_8BIT_MODE			   0x38
#define LCD_2LINES_4BIT_MODE		  	 0x28
#define LCD_CLEAR						         0x01
#define	LCD_GO_HOME						       0x02
#define LCD_CURSOR_OFF					     0x0C
#define LCD_CURSOR_ON_BLINK_OFF			 0x0E
#define LCD_CURSOR_ON_BLINK_ON			 0x0F
#define LCD_SET_CURSOR_POSITION			 0x80


/*******************************************************************************
 *------->>>>>>>>>>        Functions Prototypes             <<<<<<------------  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1- Setup the LCD pins directions using GPIO driver.
 * 2- Setup the LCD Data Mode 4-bits or 8-bits.
 */

void LCD_init(void);


/*
 * Description :
 * Sending commands to the screen
 */
void LCD_sendCommand(uint8 command);



/*
 * Description :
 * Displaying any string on the screen
 */
void LCD_displayString(const uint8 *string);



/*
 * Description :
 * Display the required Character on the screen
 */
void LCD_displayCharacter(uint8 character);

/*
 * Description :
 * A command to clear the screen
 */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
