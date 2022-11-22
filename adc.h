/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the AVR ADC driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include"std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAX_VOLT			5			/* REFERENCE VOLT */
#define ADC_MAX_DIGITAL_VALUE	1023  		/*10 bit ADC */

typedef enum
{
	PRESCALER_2 = 1 , PRESCALER_4, PRESCALER_8, PRESCALER_16, PRESCALER_32,
	PRESCALER_64, PRESCALER_128
}ADC_Prescaler;

typedef enum
{
	AREF, AVCC, INTTERNAL_VREF = 3
}ADC_ReferenceVolatge;

typedef enum
{
	FREE, ANALOG_COMP, EXTERNAL_INTERRUPT, TMR0_COMP,
	TMR0_OVF, TMR1_COMPB, TMR1_OVF, TMR1_CAPTURE_EVENT
}ADC_TriggerSource;

typedef struct{
ADC_ReferenceVolatge ref_volt;
ADC_Prescaler prescaler;
ADC_TriggerSource trigger_source;
}ADC_ConfigType;




/*******************************************************************************
 *------->>>>>>>>>>        Functions Prototypes             <<<<<<------------  *
*******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver with the desired
 * reference voltage and prescaler
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);



/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and start the conversion to digital value then returning the digital value
 */
uint16 ADC_readChannel(uint8 channel);


#endif /* ADC_H_ */
