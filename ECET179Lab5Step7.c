/*
 * ECET179Lab5Step7.c
 *
 * Created: 2016/2/11 21:25:16
 *  Author: Yizhou Zhang
 */ 


#include <avr/io.h>
#include <stdio.h>

#define F_CPU 16000000L  //essential for delay.h
#include <util/delay.h>

int main(void)
{
	DDRA = 0x00; //configure Port A as input, all pins are connected to toggle switches
	DDRC = 0xFF; //configure Port C as output, all pins are connected to LEDs
	
	PORTA = 0xFF; //turn on pull-up resistors of Port A
	PORTC = 0x00; //turn off all LEDs connected to Port C
    
	while(1)
    {
        //TODO:: Please write your application code 
		if (PINA == 0x01)
		{
			PORTC = 0x01; //if the condition is satisfied, toggle LED0 from initial state
			_delay_ms(500);  //wait 500ms
			PORTC = 0x00; //toggle the LED0 again
			_delay_ms(500); //wait 500ms
		}
		else if (PINA == 0x02)
		{
			PORTC = 0x40; //if the condition is satisfied, turn on LED7
			_delay_ms(500);  //wait 500ms
			PORTC = 0x00; //turn off LED7
			_delay_ms(500); //wait 500ms
		}						
    }
}