/*
 * ECET179lab12Step4.c
 *
 * Created: 4/4/2016 2:29:08 PM
 *  Author: YizhouZhang
 */ 

/*
Purpose of program: a temperature monitoring system, which measures temperature every 100ms and send it out the serial port in a comma separated format
Input: LM34 -> ADC0 -> microcontroller
Output: temperature value -> UART0 -> CoolTerm, the terminal program on PC
*/

/*
Note: typical slop of the LM34 is 10mV/F, according to datasheet
	  Internal ADC reference voltage is turned off, external reference voltage REF = 5V is used. (Defined in ACD_student.c)
	  Minimum temperature that can be measured by LM34 is -50 Fahrenheit, as specified by datasheet
*/

#include <avr/io.h>
#include <stdio.h>
#include "serial.c"
#include "ADC_student.c";

#define F_CPU 16000000UL
#include <util/delay.h>

#define RESOLUTION 19.6  //8-bit resolution in ADC_student.c, resolution = Reference voltage / (2^8 - 1) = 19.6mV/step, when ReferenceVoltage = 5V
#define MINTEMP 5  //specified in LM34 datasheet, in Fahrenheit
#define GAIN 10  //10mv/F, specified in datasheet

int main(void)
{
	init_ADC();  //initialize ADC
	init_UART();  //initialize UART0, communication to PC
	
	uint8_t sensor_reading;  //raw data from ADC
	uint8_t temperature;  //signed integer, because temperature can be - or +
	uint16_t voltageMV;  //result of converting ADC result to voltage
	
	while(1)
	{
		//TODO:: Please write your application code
		sensor_reading = read_ADC_channel(0);  //reading ADC result
		voltageMV = sensor_reading * RESOLUTION;  //converting ADC result to voltage
		temperature = voltageMV / GAIN + MINTEMP;  //convert voltage to temperature in F
		
		printf("%d,\r", temperature);  //%d for signed decimal integer
		_delay_ms(100);
	}
}