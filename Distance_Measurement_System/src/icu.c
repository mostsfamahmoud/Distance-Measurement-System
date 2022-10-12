 /******************************************************************************
 * Module: ICU (Input Capture Unit)
 *
 * File Name: icu.c
 *
 * Description: Source file for the AVR ICU driver
 *
 * Author: Mostafa Mahmoud
 *
 * Group: 71
 *******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>       /* For ICU ISR */
#include "icu.h"
#include "Macros.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application
   Volatile --> Prevent Compiler Optimization on g_callBackPtr
   Static   --> To limit the scope of this global pointer from SW scope to File Scope
                To prevent sharing this resource with unwanted Modules
*/
volatile static void(*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_CAPT_vect) /* Interrupt Definition --> Timer/Counter1 Capture Events */
{
	if (g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* Call Back Notification */

		/* Another method to call the function using pointer to function:
		      g_callBackPtr();
		 */
	}
}

/*******************************************************************************
 *                           Functions Definitions                             *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_ConfigType * Config_Ptr)
{
	/* Configure ICP1/PD6 as i/p pin */
	CLEAR_BIT(DDRD,PD6);

	/* Timer1 always operates in Normal Mode */
	TCCR1A = (1 << FOC1A) | (1 << FOC1B);

	/* Insert the required edge type in ICES1 bit in TCCR1B Register */
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge) << ICES1);

	/* Insert the required clock value in the first three bits (CS10, CS11 and CS12)of TCCR1B Register */
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);

	TCNT1 = 0; /* Initial Value for Timer1 */

	ICR1 = 0;  /* Initial Value for the input capture register */

	/* Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
	SET_BIT(TIMSK, TICIE1);
}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr2Func)(void))
{
	g_callBackPtr = a_ptr2Func;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType)
{
	/* Insert the required edge type in ICES1 bit in TCCR1B Register */
	TCCR1B = (TCCR1B & 0xBF) | (a_edgeType << ICES1);
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	CLEAR_BIT(TIMSK, TICIE1);
}


