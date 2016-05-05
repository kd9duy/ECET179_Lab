/*
 * ECET179Lab15Step3.c
 *
 * Created: 4/22/2016 1:56:29 PM
 *  Author: YizhouZhang
 */ 


#include <avr/io.h>
#include <stdio.h>


// the SET_BIT and CLR_BIT declarations must be above the include statement for the sync_serial library!!
#define	SET_BIT(x,y)	x = x | (1<<y)
#define CLR_BIT(x,y)	x = x & ~(1<<y)

// IO assignments for the kaypad
#define DAV	( PINC & 0x10 )
#define KEYPAD	( PINC & 0x0F )


#include "serial.c"
#include "keypad.c"
#include "sync_serial_lib.c"



int main(void)
{
	uint16_t value;
	uint16_t digital;

	DDRB = 0x3F;		// set all 6-bits for output
	PORTB = 0x04;		// start with chip select bit high

	DDRC = 0x00;		// IO for the Keypad - DAV is on Port C Bit 4
	PORTC = 0x1F;		// IO for the keypad - Key value is on Port C bits 0 to 3

	init_UART();


	// these two lines are required due to the design of the sync serial board
	SET_BIT(PORTB, 0);
	CLR_BIT(PORTB, 1);

	
	printf("Sync Serial example program...\n\r");


	while(1)
	{

		//printf("\n\rEnter a four digit number on the keypad using leading 0's when needed!");

		//value = get_four_digit_keypad();	// get the value that will ultimately become the desired frequency

		//printf("\n\rThe value entered was %u\n\r", value);


		send_ML2036( 0x1579 );	// output a test value


	}

}
