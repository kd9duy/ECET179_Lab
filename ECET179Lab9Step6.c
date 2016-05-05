/*
 * ECET179Lab9Step6.c
 *
 * Created: 3/24/2016 4:59:15 PM
 *  Author: YizhouZhang
 */ 



/*
Input: Pushbuttons on Light&Switch Board -> Port C -> Microcontroller
Output: UART0 -> USB Poart -> Terminal Program on PC, CoolTerm
		UART3 -> TX pin of the board -> MP3 model receiving pin
		UART2 -> TX pin of the board -> LCD model receiving pin
		
*/

/*
Purpose of the program: 1.control the MP3 board to play songs, Play/Pause, Stop, Previous, Next functions
						2.display the command and the file name on LCD
						3.use the pushbuttons on the Switch&Light board to input command
*/

#include <avr/io.h>
#include <stdio.h>
#define F_CPU 16000000L
#include "util/delay.h"
#include "serial.c"
#include "serial_LCD.c"
#include "MP3.c"


int main(void)
{
	
	/*Serial Communication setup*/
	init_UART();  //initialize the UART
	init_LCD_UART();  //initialize UART3 for LCD communication
	init_MP3_UART();  //initialize UART2 for MP3 Module output
	
	/*Port pins setup*/
	DDRC = 0x00;  //set port C as input
	PORTC = 0xFF;  //turn on the pull-up resistors

	printf("LCD Test Program\n\r");  //initial message to be displayed on CoolTerm, the terminal program on PC
	
	/*LCD operation*/
	put_command_LCD(0x0E);  //turn on LCD
	put_command_LCD(0x01);  //clear and home the LCD
	put_string_LCD("LCD Test Message!?");  //display a message
	_delay_ms(500);  //display the previous message for a while, then display the next one, VERY IMPORTANT
	put_command_LCD(0x80 | 0x40);  //move cursor to the second line
	_delay_ms(200);  //give LCD enough time to receive command  
	put_string_LCD("Programmed by zhan1086");
	
	/*Veriables defination*/\unsigned char buffer[25];  //buffer is for storing the file name, which is to be used by putstring_MP3 function
	unsigned char track_number = 1;  //for storing the number in a file name
	unsigned char filename[25];  //another buffer for storing file name w/out MP3 commands
	
    while(1)  //main program
    {
        //TODO:: Please write your application code 
		while (PINC == 0)  //wait for the pushbuttons
		{		
		}
		
		put_command_LCD(0x01);  //clear and home the LCD screen for new messages
		if (PINC == 0x01) //Pushbutton0 -> Play/Pause
		{
			putstring_MP3("PC P\r");  //send command to MP3
			  
			put_string_LCD("Play / Pause");  //display the command on LCD
			_delay_ms(200);	  //give LCD enough time to receive data
			
			put_command_LCD(0x80 | 0x40);  //move cursor to the second line
			_delay_ms(200);  //give time for LCD to receive command
			sprintf(filename, "Track%04d.mp3", track_number);//generate a filename
			put_string_LCD(filename);  //display filename on LCD
		}
		
		else if (PINC == 0x02)  //Pushbutton1 -> Stop
		{
			putstring_MP3("PC S\r");  //send STOP command to MP3
			
			put_string_LCD("Stop");  //display the command on LCD
			_delay_ms(200);		//give LCD enough time to receive data	
		}
		
		else if (PINC == 0x04)  //Pushbotton2 -> Next song
		{
			if (track_number < 44)  //check if track number is valid or not
			{
				track_number = track_number + 1;
			}
			
			sprintf(buffer, "PC F /Track%04d.mp3\r", track_number);  //generate complete MP3 command
			putstring_MP3(buffer);  //send command to MP3
			
			put_string_LCD("Next\n\r");  //display the command on LCD
			_delay_ms(200);  //give LCD enough time to receive data
			
			put_command_LCD(0x80 | 0x40);  //move cursor to the second line
			_delay_ms(200);  //give time for LCD to receive command
			sprintf(filename, "Track%04d.mp3", track_number);  //generate a filename
			put_string_LCD(filename);  //display filename on LCD
		}
		
		else if (PINC == 0x08)  //Pushbutton3 -> Previous song
		{
			if (track_number > 1)  //check if track number is valid or not
			{
				track_number = track_number - 1;
			}

			sprintf(buffer, "PC F /Track%04d.mp3\r", track_number);  //generate complete MP3 command
			putstring_MP3(buffer);  //send command to MP3
			
			put_string_LCD("Previous\n\r");
			_delay_ms(200);  //give LCD enough time to receive data
			
			put_command_LCD(0x80 | 0x40);  //move cursor to the second line
			_delay_ms(200);  //give time for LCD to receive command
			sprintf(filename, "Track%04d.mp3", track_number);  //generate a filename
			put_string_LCD(filename);  //display filename on LCD
		}
	}
}
