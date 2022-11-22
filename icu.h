/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: header file for the AVR ICU driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#ifndef ICU_H_
#define ICU_H_

#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef enum
{
FALLING, RISING
}ICU_edgeSelect;

typedef enum
{
	NONE, FCPU, FCPU_8, FCPU_64, FCPU_256, FCPU_1024, EXT_T1_FALLING, EXT_T1_RISING
}ICU_clockSelect;


typedef struct
{
	ICU_edgeSelect edge;
	ICU_clockSelect clock;
}ICU_config;

/*******************************************************************************
 *------->>>>>>>>>>        Functions Prototypes             <<<<<<------------  *
 *******************************************************************************/

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_config *config_ptr );


/*
 * Description: Function to set the Call Back function address.(passed by application)
 */
void ICU_SetCallBack(void (*ptr)(void));


/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_deInit(void);


/*
 * Description: Function to get the Timer1 Value when the input is captured
 *  The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue();


/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_clearTimerValue(void);

/*
 * Description: Function to set the required edge detection.so if we want to change the
 * type of edge we are capturing during program we can do so separately without
 * having to modify the structure the calling init function over and over again
 */
void Icu_setEdgeDetectionType(const ICU_edgeSelect a_edge);

#endif /* ICU_H_ */
