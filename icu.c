/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: Source file for the AVR ICU driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#include "icu.h"
#include "avr/io.h"
#include <avr/interrupt.h>

static volatile void (*g_callBack_ptr)(void) = NULL_PTR;

/*******************************************************************************
 *>>>>>>>>>>>>>>>             Interrupt Service Routines     <<<<<<<<<<<<<<<<< *
 *******************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	(*g_callBack_ptr)();
}


/*******************************************************************************
 *>>>>>>>>>>>>>>>            Function Definitions             <<<<<<<<<<<<<<<<< *
 *******************************************************************************/

void ICU_init(const ICU_config *config_ptr )
{
	/* Timer1 always operates in Normal Mode */
	TCCR1A = 0x0C;

	/*  insert the required edge type in ICES1 bit in TCCR1B Register */
	TCCR1B = ( (TCCR1B & ~(1<<ICES1) ) | ((config_ptr->edge) << 6) );

	/*
	 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
	 * of TCCR1B Register
	 */
	TCCR1B = ( (TCCR1B & 0xF8 ) | (config_ptr->clock) );

	/* Initial Value for Timer1 */
	TCNT1 =0;

	/* Initial Value for the input capture register */
	ICR1 =0;

	/* Configure ICP1/PD6 as i/p pin -- thats where we receive the edge
	 * from an external device  */
	DDRD &= ~(1<<PD6);

	/* Enable the Input Capture interrupt to generate an interrupt
	 * when edge is detected on ICP1/PD6 pin */
	TIMSK |= (1<<TICIE1);
}

void ICU_SetCallBack(void (*ptr)(void))
{
	/* Save the address of the Call back function in a global variable
	 *  (the address of function that will be passed to ICU by the application
	 *  so that when icu capture edge it inform the application by calling this function) */
	g_callBack_ptr = ptr;
}

void ICU_deInit(void)
{
	/* Clear All Timer1 Registers -- reseting to initial values which are zeros*/
	TCNT1 =0;
	ICR1 =0;
	TCCR1B = 0;
	TCCR1A =0;
	TIMSK &= ~(1<<TICIE1);
}

uint16 Icu_getInputCaptureValue()
{
	return ICR1;
}


void Icu_clearTimerValue(void)
{
	TCNT1 =0;
}


void Icu_setEdgeDetectionType(const ICU_edgeSelect a_edge)
{
	TCCR1B = ( (TCCR1B & ~(1<<ICES1) ) | (a_edge << 6) );
}
