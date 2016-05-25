/*
 * test_I2C.c
 *
 * Created: 12/03/2016 16:44:14
 *  Author: jolan barbancon
 */ 
#include "Global.h"

#ifdef TEST_I2C

#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "I2C_Slave.h"


uint8_t ondata(uint8_t* data_recv, uint8_t s_data, uint8_t* data_transm);

int main(void)
{
	SET(DDRC,PORTC0); //Makes PORTC0 as Output
	SET(DDRC,PORTC1); //Makes PORTC0 as Output

	sei();			//Enable Interrupt
	I2C_Init(0x12,5,ondata);
	while(1) //infinite loop
	{
		TOG(PORTC,PORTC0);//Turns ON PORTC0 LEDs
		_delay_ms(1000); //1 second delay
	}
}

uint8_t ondata(uint8_t* data_recv, uint8_t s_data, uint8_t* data_transm)
{
	//When receive data tog PORTC1
	TOG(PORTC,PORTC1);
	
	uint8_t i;
	for(i = 0; i < s_data; i++)
	{
		data_transm[i] = (data_recv[i]+i)%255;
	}
	return s_data;
}

#endif