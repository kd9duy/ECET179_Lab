/*
 * ECET179Lab13Step7.c
 *
 * Created: 4/12/2016 1:00:07 PM
 *  Author: YizhouZhang
 */ 


#include <avr/io.h>
#include <stdio.h>
#include "serial.c"
#include "ADC_student.c"

#define F_CPU 16000000UL
#include <util\delay.h>

int main(void)
{
	init_UART();  //initialize serial communication to CoolTerm
	init_ADC();  //initialize ADC
	
	uint8_t ADC_0;  //reading from ADC0
	uint8_t ADC_1;  //reading from ADC1
	uint8_t ADC_2;  //reading from ADC2
	
	uint8_t i;
	uint8_t j;
	uint8_t k;
	
	DDRB = 0b11110000;  //T0A T1B T1A T2A
	DDRG = 0b00100000;  //T0B
	//DDRC = 0x00;  //configure PortC as input
	//PORTC = 0xFF;  //turn on pull-up resisotrs of PortC
	//DDRE = DDRE | 0b00111000;  //T3C T3B T3A
	
	//channel0
	//TCCR0A = 0x00;  //clear registers
	//TCCR0B = 0x00;  //clear registers
	TCCR0A = TCCR0A | 0b11110000;  //clear OC0A on compare match
	TCCR0A = TCCR0A | 0b00000011;  //set WGM01& WGM00 to configure FAST PWM
	TCCR0B = TCCR0B & 0x11110111;  //clear WGM02 to configure FAST PWM
	TCCR0B = TCCR0B | 0x00000001;  //no prescaling
	
	//channel2
	//TCCR2A = 0x00;  //clear registers
	//TCCR2B = 0x00;  //clear registers
	TCCR2A = TCCR2A | 0b11110000;  //clear OC0A on compare match
	TCCR2A = TCCR2A | 0b00000011;  //set WGM01& WGM00 to configure FAST PWM
	TCCR2B = TCCR2B & 0x11110111;  //clear WGM02 to configure FAST PWM
	TCCR2B = TCCR2B | 0x00000001;  //no prescaling
	
	
	while(1)
	{
		//TODO:: Please write your application code
		do 
		{
			do 
			{
				do 
				{
					OCR0A = i;
					i++;
					//printf("i = %d\n\r",i);
				} while (i < 255);
				OCR0B = j;
				j++;
				//printf("j = %d\r\n",j);
			} while (j < 254);
			OCR2A = k;
			k++;
			//printf("k = %d\n\r",k);
		} while (k<254);
		k = 0;
		j = 0;
		i = 0;
	}
}