 /******************************************************************************
 * Module: APPLICATION
 *
 * File Name: Application.c
 *
 * Description: Project main Source File
 *
 * Author: Mostafa Mahmoud
 *
 * Group: 71
 *******************************************************************************/

#include <avr/io.h>              /* To use the SREG register */
#include "lcd.h"
#include "ultrasonic_sensor.h"
#include "Macros.h"              /* To use SET_BIT(REG,BIT) MACRO */


int main(void)
{
	uint16 distance = 0;

	SET_BIT(SREG,PIN7_ID);      /* Enable I-Bit (Global Interrput Enable) */

	/* Initialize both the LCD and ULTRASONIC drivers */
	LCD_init();
	Ultrasonic_init();

	/* Display that FIXED string on LCD screen */
	LCD_displayString("DISTANCE =    CM");

	while(1)
	{
		distance = Ultrasonic_readDistance();

		/* Cursor Moved to (ROW 0, COLUMN 11) to write the distance on the LCD */
		LCD_moveCursor(0, 11);

		/* Display the dutyCycle on LCD screen */
		LCD_integerToString(distance);

		if (distance < 100)
		{
			/* In case the digital value is two or one digits ,Print space in the next digit place */
			LCD_displayCharacter(' ');
		}
	}
}
