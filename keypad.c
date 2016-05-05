/* These three prototypes are not necessary since the function */
/* definitions appear before main() - based on the position of the */
/* #include keypad.c statement */

uint8_t read_keypad(void);
uint8_t get_BCD_key(void);
uint8_t get_two_digit_keypad(void);

/*************************************************************************

	This function will make sure the last key is released before waiting
	for a new key to be pressed on the keypad.

	In order for this function to work, DAV must be #define in the main.
	Also, the IO ports must be configured properly!!!


**************************************************************************/
uint8_t read_keypad(void)
{
	uint8_t value;

	while ( DAV != 0 )		// make sure the last key has been released
	{
	}

	while ( DAV == 0 )		// wait until a key is pressed
	{
	}

	value = KEYPAD;				// read only the key data

	return value;
}

/*************************************************************************

	This function will read values from the keypad and only return a value
	if it is a BCD number.  If the value is not BCD, then it will be ignored
	and the user must enter another value.  This will be repeated until a
	valid BCD value is entered.

**************************************************************************/
uint8_t get_BCD_key(void)
{
	uint8_t key;

	do
	{
		key = read_keypad();		// get a value from the keypad

	} while ( key > 9 );			// continue to run the loop until a valid BCD

	return key;
}

/*************************************************************************
	This function will read two key strokes on the keypad and combine them
	to produce a decimal number between 00 and 99
**************************************************************************/
uint8_t get_two_digit_keypad(void)
{
	uint8_t ones, tens;

	tens = get_BCD_key();
	ones = get_BCD_key();

	return ( ( tens * 10 ) + ones );
}
