/***********************************************************************************
	Analog to Digital.C
	
	set to be 8 bit resolution, therefore total steps = 2^8 - 1 = 255
    internal reference voltage source is turned off, external reference voltage REF is used. REF = 5V in ECET179Lab12
    
		
************************************************************************************/

uint8_t read_ADC(void);
void init_ADC(void);

uint8_t read_ADC_channel(uint8_t);


void init_ADC(void)
{
                                // setup the Analog to Digital Converter
	ADMUX = 0x40;		// start by selecting the voltage reference - Avcc, external reference voltage
	ADMUX = ADMUX | 0x00;   // Select the default ADC channel - channel 0 in this case
	ADMUX = ADMUX | 0x20;	// set for Left Justified - Only using 8 bit of resolution. Controlled by bit 5 of ADMUX, ADLAR
	
	ADCSRA = 0x07;	// select the ADC clock frequency - Clock / 128. controlled by bit2:0 of ADCSRA
	ADCSRA = ADCSRA | 0x80;	// enable the ADC. Controlled by bit7 ADEN

}

	
uint8_t read_ADC(void)
{
	uint8_t value;			// 8-bit value to hold the result
	
	ADMUX = ADMUX & 0xE0;		// clear the channel data

	ADCSRA = ADCSRA | 0x40;	// start a conversion. Controlled by bit6 ADSC
	
	while( (ADCSRA & 0x10) == 0 )	// wait for conversion to be completed. i.e. wait for bit 4 ADIF to be 0. ADIF = 1 once complete
	{
	}
	
	value = ADCH;		// get the upper 8-bits
	ADCSRA = ADCSRA | 0x10;	// clear the conversion flag. bit4 ADIF is set when an ADC conversion completes and the data Registers are updated, is cleared by writing a logical 1 to the flag
	
	return value;			// send back the 8-bit result
}


// uncomment this when ready to complete this portion of the lab

// this version allows the user to select which channel on Port C to convert
//	
uint8_t read_ADC_channel(uint8_t channel)
{
	uint8_t value;			// 8-bit value to hold the result
	
	ADMUX = ADMUX & 0xE0;		// clear the channel data
	
	ADMUX = ADMUX | channel;	// add the channel data here!

	ADCSRA = ADCSRA | 0x40;	// start a conversion
	
	while( (ADCSRA & 0x10) == 0 )	// wait for conversion to be completed, wait for bit 4 ADIF to be 0. ADIF = 1 once complet
	{
	}
	
	value = ADCH;		// get the upper 8-bits
	ADCSRA = ADCSRA | 0x10;	// clear the conversion flag
	
	return value;			// send back the 8-bit result
}
