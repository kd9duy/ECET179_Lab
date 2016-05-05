/*
 * ECET179Lab7Step5.c
 *
 * Created: 2016/2/25 5:19:43
 *  Author: Yizhou Zhang
 */ 

/*
Input: None
Output: Serial connection to the computer (Software: CoolTerm)
*/

/*
Purpose of the program: Build a clock that displays day, hour, miniute, second
*/

#include <avr/io.h>
#include <stdio.h>  //necessary for serial communication
#include "serial.c"  //serial communication
#define F_CPU 16000000L  //defines CPU speed, for delay functions
#include <util/delay.h> //delay function

int main(void)
{
	init_UART(); //initialize serial communication
	
	uint8_t seconds = 0;  //defines variable to record and display second
	uint8_t miniutes = 0;  //defines variable to record and display miniute
	uint8_t hours = 0;  //defines variable to record and display hour
	uint8_t days = 0;  //defines variable to record and display day
	
	
    while(1)
    {
        //TODO:: Please write your application code 
		do 
		{
			do 
			{
				do 
				{
					_delay_ms(1000); //count 1 second, make it 5 milliseconds for faster testing
					seconds = seconds + 1;  //increase seconds value
					printf("Current time is Day%d, %d : %d : %d \n\r", days, hours, miniutes, seconds); //display time
				} while (seconds <60);  //once jump out of seconds increasing loop, 60s (1min) have passed, go to increase miniutes and reset seconds
				
				seconds = 0; //reset seconds value
				miniutes = miniutes + 1;  //increase miniutes
			} while (miniutes < 60);  //once jump out of miniutes increasing loop, 60min (1h) have passed, go to increase hours and reset miniutes
			
			miniutes = 0;  //reset miniutes value
			hours = hours + 1;  //increase hours
		} while (hours < 24);  //once jump out of hours increasing loop, 24h (1day) have passed, go to increase days and reset hours
		
		hours = 0;
		days = days + 1;
    }  //upper limit of how many days is not defined in lab manual. because days is a unsigned 8 bit integer, the maximum day will be 255, and then roll back to 0
}  

