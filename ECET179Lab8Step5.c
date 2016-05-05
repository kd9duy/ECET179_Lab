/*
 * ECET179Lab8Step5.c
 *
 * Created: 2/29/2016 2:38:04 PM
 *  Author: YizhouZhang
 */ 

/*
Purpose of the program:
	create a program based on a switch/case structure to allow the provided GUI to control six outputs on the microcontroller.
*/

/*
Input: GUI provided by ECET179, input will be ASCII A-F for turn on, a-f for turn off.
Output: PORTA, control 6 relays to control 6 zone of lights. In this lab, We will use the LEDs on the Switch&Light board
*/

/*
Logic AND / OR reference
x & 1 = x  anything &1 stays the same
x | 0 = x  anything |1 stays the same
x & 0 = 0  anything &0 will be 0
x | 1 = 1  anything &1 will be 1
*/


#include <avr/io.h>
#include <stdio.h>  //essential for USART0 communication
#include "serial.c"  //for serial communication, declear in case of debugging with terminal

#define F_CPU 16000000  //define CPU frequency for Delay function
#include <util/delay.h>  //delay function


int main(void)
{
	char input;  //variable to store command from PC
	uint8_t output = 0x00;  //variable to store output command
	
	DDRA = 0xFF; //configure PORTA as output
	
	init_UART();  //initialize serial communication to the computer/terminal
	
    while(1)
    {
        //TODO:: Please write your application code 
		scanf("%c", &input);  //get command from PC, store as an ADCII character
		switch (input)
		{
			case 'A':
			output = output | 0x80; //turn on channel 1 1000 0000
			break;
			
			case 'B':
			output = output | 0x40; //turn on channel 2, 0100 0000
			break;
			
			case 'C':
			output = output | 0x20 ;  //turn on channel 3, 0010 0000 
			break;		
			
			case 'D':
			output = output | 0x10;  //turn on channel 4, 0001 0000
			break;
			
			case 'E':
			output = output | 0x08;  //turn on channel 5, 0000 1000
			break;
			
			case 'F':
			output = output | 0x04;  //turn on channel 6, 0000 0100
			break;
			
			case 'a':
			output = output & 0x7F;  //turn off channel 1, 0111 1111
			break;
			
			case 'b':
			output = output & 0xBF;  //turn off channel 2, 1011 1111
			break;
			
			case 'c':
			output = output & 0xDF;  //turn off channel 3, 1101 1111
			break;
			
			case 'd':
			output = output & 0xEF;  //turn off channel 4, 1110 1111
			break;
			
			case 'e':
			output = output & 0xF7;  //turn off channel 5, 1111 0111
			break;
			
			case 'f':
			output = output & 0xFB;  //turn off channel 6, 1111 1011
			break;
			
			default:
			break;
		}
		PORTA = output;  //turn on/off the specfic lights
    }
}