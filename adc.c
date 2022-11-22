/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the AVR ADC driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/


#include "avr/io.h"
#include "Relavent_Macros.h"
#include "adc.h"


void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/*00000 to choose channel 0 as initialization*/
	ADMUX &= 0xE0;

	/* Inserting the reference volt chosen** NOTE that the value
	 * inserted in register ADMUX is a 2bit value which should be inserted at
	 * first 2 bits of the register and thats why we did the shift left by 6 */
	ADMUX = ( (ADMUX & 0x3F) | ((Config_Ptr->ref_volt) << 6) );

	/* Inserting the mode (trigger source) chosen in SFIOR register
	 * usually  we use the free mode */
	SFIOR = ( (SFIOR & 0x1F) | ((Config_Ptr->trigger_source) << 5) );

	/* Inserting the Prescaler chosen */
	ADCSRA = ( (ADCSRA & 0xF8) | (Config_Ptr->prescaler) );

	/*Disabling interrupt as we use pooling*/
	CLEAR_BIT(ADCSRA,ADIE);

	/*To make the converted data right adjusted*/
	CLEAR_BIT(ADMUX,ADLAR);

	/*Enabling ADC module*/
	SET_BIT(ADCSRA,ADEN);
}

uint16 ADC_readChannel(uint8 channel)
{
	/*Inserting the channel number in the ADMUX register*/
	ADMUX = ((ADMUX & 0xE0) | (channel & 0x07));

	/* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA,ADSC);

	/* Wait for conversion to complete, ADIF becomes '1' */
	while(!(BIT_IS_SET(ADCSRA,ADIF)));

	/* Clear ADIF by write '1' to it -- note that this bit is cleared automatically
	 * by hardware in case its inside ISR -- when we use interrupt not pooling*/
	SET_BIT(ADCSRA,ADIF);

	/*returning the digital value converted */
	return ADC;
}
