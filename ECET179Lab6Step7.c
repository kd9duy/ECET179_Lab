/*
 * ECET179Lab6Step7.c
 *
 * Created: 2016/2/19 3:12:02
 *  Author: Yizhou Zhang
 */ 

/*
Physical Connections
PORTA -> LEDs 0-7
PORTC <- Toggle Switches 0-7
*/

/*
Purpose of the program: use printf function to add a software delay to the toggle switches.
Delay Time is determined by measuring the bouncing time of a toggle switch, and choose a value slightly larger than the measured maximum bounce time.
*/


#include <avr/io.h>
#include <stdio.h>
#include "serial.c"

/*
#define F_CPU 16000000L
#include <util/delay.h>
*/  //only used when delay function is needed


int main(void)
{
	DDRA = 0xFF;  //set port A as output
	DDRC = 0x00;  //set port C as input
	PORTA = 0x00; //clear output
	PORTC = 0xFF; //turn on pull-up resistors
	
	init_UART();  //initialize serial connections
	
	uint8_t value = 0; //set counter value to 0. number will be output in binary on 8 LEDs, so 8 bit unsigned integer is enough
	uint8_t DelayTime_ms = 2;  //set delay time to satisfy debounce need

	printf("ECET179_Lab6_Step7 DeBouncing with Software by setting delay time - Yizhou Zhang \n\r");
	printf("The delay time should be at least %d ms \n\r", DelayTime_ms);
	
	
	while(1)
	{
		//TODO:: Please write your application code
		PORTA = value;  //output counter value to LEDs
		
		while (PINC == 0)  //wait for a push button to be pressed
		{
		}
		printf("%d - 1\n\r", value); //delay to debounce, by printing current counter value. -1 represents contacting debounce
		
		value = value + 1;  //increment counter value
		
		while (PINC != 0)  //wait for the push button to be released
		{
		}
		printf("%d - 2\n\r",value); //delay to debounce, by printing current counter value. -2 represents releasing debounce
	}
}