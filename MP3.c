/*******************************

	ECET 17900 - Introduction to Digital Systems

	Serial functions required to send data through UART1 to the MP3 Player Module
	
	Name:	Jeffrey J. Richardson
	
	Date:	March 2015

	Description:
		(should be filled in by the students)



********************************/

void init_MP3_UART(void);

void putstring_MP3(unsigned char *str);


void init_MP3_UART(void)
{

	UCSR2A = 0x00;			
	UCSR2B = 0x18;			// enable UART TX and RX
	UCSR2C = 0x06;			// set the UART for N, 8, 1
	UBRR2L = 103;			// set BAUD Rate for 9600 with 16MHz clock
	UBRR2H = 0;

}


// the following function sends a single character out of the serial port
void putchar_MP3(unsigned char ch)
{

    while ( (UCSR2A & (1 << UDRE2)) == 0 )		// wait until there is room in the transmit buffer
	{
	}

    UDR2 = ch;									// load the character into the UART data register
}

void putstring_MP3(unsigned char *str)
{
	while(*str != 0)
	{
		putchar_MP3(*str++);
	}
}