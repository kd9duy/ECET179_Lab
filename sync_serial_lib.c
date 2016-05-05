/****************************************************************

	ECET 17900 - Introduction to Digital Systems

	Sync_serial_lib.c

	Name:	Jeffrey J. Richardson
	Date:	April 15, 2012

	Description:
		(fill this in)



*******************************************************************/

void send_MAX512(uint8_t, uint8_t);
void send_ML2036(uint16_t);


/*******************************************************************************************************

	Function:	send MAX512

	Description:

		This function takes two 8-bit values and sends them to the MAX512 DAC.

		The first value sent is the control byte.  The second byte is the data.

		Both values are sent MSB first


********************************************************************************************************/
void send_MAX512(uint8_t control, uint8_t value)
{
	uint8_t mask;
	uint8_t i;


	CLR_BIT(PORTB, 2);					// drive the chip select low

	mask = 0x80;						// start with MSB
	
	for ( i = 0; i < 8; i++)			// going to send 8-bits
	{
		if ( ( control & mask ) != 0 )	// check the bit to see if it is high?
		{
			SET_BIT( PORTB, 3 );		//set the output port bit
		}
		else
		{
			CLR_BIT( PORTB, 3 );		// clear the output port bit
		}
	
		SET_BIT( PORTB, 5);				// set the clock port bit
	
		mask = mask >> 1;				// move to the next bit and create a sm delay
	
		CLR_BIT(PORTB, 5);				// clear the clock port bit
	}



	mask = 0x80;						// reset to start with MSB
	
	for ( i = 0; i < 8; i++)			// going to send 8-bits
	{
		if ( ( value & mask ) != 0 )	// check the bit to see if it is high?
		{
			SET_BIT( PORTB, 3 );		//set the output port bit
		}
		else
		{
			CLR_BIT( PORTB, 3 );		// clear the output port bit
		}
	
		SET_BIT( PORTB, 5);				// set the clock port bit
	
		mask = mask >> 1;				// move to the next bit and create a sm delay
	
		CLR_BIT(PORTB, 5);				// clear the clock port bit
	}


	SET_BIT(PORTB, 2);					// bring the chip select line back high


}


/*******************************************************************************************************

	Function:	send ML2036

	Description:
		
		This function takes a 16-bit value and transfer it to the ML2036 sine wave generator IC

		This requires 16-bits of data to be sent LSB first.


********************************************************************************************************/
void send_ML2036(uint16_t digital_value)
{

	// create the function here.  
    uint16_t mask;
    uint16_t i;
    
    CLR_BIT(PORTB, 2);
    
    mask = 0x0001;
    
    for (i = 0; i < 16; i++)
    {
        if ( (digital_value & mask) != 0 )
        {
            SET_BIT(PORTB, 3);
        }
        else
        {
            CLR_BIT(PORTB, 3);
        }
        
        SET_BIT(PORTB, 5);
        
        mask = mask << 1;
        
        CLR_BIT(PORTB, 5);
    }
	SET_BIT(PORTB, 2);
}

