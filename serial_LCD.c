/*******************************

	ECET 17900 - Introduction to Digital Systems

	Serial functions required to utilize STDIO with the Atmel microcontrollers through WinAVR

	Name:	Jeffrey J. Richardson
	Date:	October 29, 2011

	Description:
		(fill this in)



********************************/

void init_LCD_UART(void);
void putchar_LCD(unsigned char ch);
void put_command_LCD(unsigned char command);
void put_string_LCD(unsigned char*str);

//static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, uart_getch, _FDEV_SETUP_RW);	/* Assign I/O stream to UART */


void init_LCD_UART(void)
{

	UCSR3A = 0x00;			
	UCSR3B = 0x18;			// enable UART TX and RX
	UCSR3C = 0x06;			// set the UART for N, 8, 1
	UBRR3L = 103;			// set BAUD Rate for 9600 with 16MHz clock
	UBRR3H = 0;

	stdout = &mystdout;		// define the output stream
	stdin = &mystdout;		// define the input stream	

}


// the following function sends a single character out of the serial port
void putchar_LCD(unsigned char ch)
{

    while ( (UCSR3A & (1 << UDRE3)) == 0 )		// wait until there is room in the transmit buffer
	{
	}

    UDR3 = ch;									// load the character into the UART data register
}

void put_command_LCD(unsigned char command)  //sends a command to the LCD
{
	putchar_LCD(0xFE);  //send the command indicator to the LCD
	putchar_LCD(command);  //send the command indicator to the LCD
	_delay_ms(5);  //delay so the LCD can respond
}

void put_string_LCD(unsigned char *str)  //sends a string of ASCII characters to the LCD
{
	while (*str != 0)
	{
		putchar_LCD(*str);
		str++; 
	}
}