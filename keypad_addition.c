uint16_t get_four_digit_keypad(void);


/*************************************************************************

	This function will read four key strokes on the keypad and combine them
	to produce a decimal number between 0000 and 9999

**************************************************************************/
uint16_t get_four_digit_keypad(void)
{
	uint8_t ones, tens, hundreds, thousands; 

	thousands = get_BCD_key();
	hundreds = get_BCD_key();
	tens = get_BCD_key();
	ones = get_BCD_key();


	return ( ((int) thousands * 1000) + ((int) hundreds * 100) + ( tens * 10 ) + ones );


}
