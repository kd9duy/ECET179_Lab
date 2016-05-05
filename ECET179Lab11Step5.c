/*
 * ECET179Lab11Step5.c
 *
 * Created: 4/1/2016 12:55:08 AM
 *  Author: YizhouZhang
 */ 

 /*
*Function of Program: a game of gussing a 2-digit number
*Input: keypad -> PortC
*Output: UART3 -> LCD
*		 UART0 -> CoolTerm
*
 */
#include <avr/io.h>
#include <stdio.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "serial.c"
#include "serial_LCD.c"

#define DAV (PINC & 0x10) //signal indicating if the keypad is ready
#define KEYPAD (PINC & 0x0f) //masking out the unused pins

#include "keypad.c"  //driver of the keypad

/*shortcuts for LCD operation*/
#define LCDON 0x0E
#define LCDCLEAR 0x01
#define LCDto2LINE (0x80 | 0x40)

int main(void)
{
	init_UART();  //initialize communication to CoolTerm
	init_LCD_UART();  //initialize communication to LCD
	
	uint8_t random_number;
	uint8_t useranswer;
	
	DDRA = 0xFF;  //initialize PortA as output
	DDRC = 0x00;  //initialize PortC as input
	PORTC = 0xFF;  //turn on pull up resistors
	
	put_command_LCD(LCDON); //turn on LCD
	_delay_ms(50);
	put_command_LCD(LCDCLEAR); //clear LCD display
	_delay_ms(50);
	
    while(1)
    {
        //TODO:: Please write your application code
		random_number = random() % 100;	 //generate a random 2-digit number
		printf("the number is %u\n\r", random_number);  //show the answer on CoolTerm for debugging
		
		do 
		{
			put_command_LCD(LCDCLEAR);  //clear display
			_delay_ms(50);
			put_string_LCD("Guess a 2 digit number.");  //instructing user to enter number
			_delay_ms(50);
			useranswer = get_two_digit_keypad();  //getting the number from user
			put_command_LCD(LCDto2LINE);  //move to the second line
			_delay_ms(50);
			put_string_LCD("is answer correct?");  //notify user that the answer is received
			_delay_ms(3000);
			if (useranswer > random_number)
			{
				put_command_LCD(LCDCLEAR);  //clear display
				_delay_ms(50);
				put_string_LCD("Too High!");  //tell user the gussed answer is higher than real answer
				_delay_ms(3000);
			}
			else if (useranswer < random_number)
			{
				put_command_LCD(LCDCLEAR);  //clear display
				_delay_ms(50);
				put_string_LCD("Too Low!");  //tell user the gussed anwer is lower than real answer
				_delay_ms(3000);
			}
			else
			{
				put_command_LCD(LCDCLEAR);  //clear display
				put_string_LCD("Congratulations! ");  //tell user that the answer is correct
				_delay_ms(4000);  //display message for 4s to cheer up the user, then startover
			}
		} while (useranswer != random_number);  //keep looping until user got the correct answer, then automatically startover
		 
    }
}
