/*
 * test_Blinck.c
 *
 * Created: 03/03/2016 22:18:25
 * Author : jolanbarbancon
 */ 

#include "Global.h"

#ifdef TEST_BLINCK

	#include <avr/io.h>
	#include <util/delay.h>

	int main(void)
	{
		SET(DDRC,PORTC0); //Makes PORTC0 as Output
		while(1) //infinite loop
		{
			TOG(PORTC,PORTC0); //Turns ON All LEDs
			_delay_ms(1000); //1 second delay
		}
	}

#endif