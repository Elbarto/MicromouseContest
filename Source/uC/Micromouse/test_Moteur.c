/*
 * test_I2C.c
 *
 * Created: 12/03/2016 16:44:14
 *  Author: jolan barbancon
 */ 
#include "Global.h"

#ifdef TEST_MOTEUR

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "I2C_Slave.h"
#include "Moteur.h"

uint16_t command = 0;
uint8_t togAss = 0;

uint8_t ondata(uint8_t* data_recv, uint8_t s_data, uint8_t* data_transm);
void Err();

int main(void)
{
	sei();
	SET(DDRC,PORTC0); //Makes PORTC0 as Output
	SET(DDRC,PORTC1);
	
	//Test PWM
	PWM_Init(0x0FFF);
	PWM_SetDutyCycleA(0x03FF);
	PWM_SetDutyCycleB(0x0BFF);
	
	//Test frequency meters
	Counter_INIT();
	
	I2C_Init(0x12,5,ondata);
	while(1) //infinite loop
	{
		if(togAss) ControlLoop((int) command, (int) command);
		else _delay_ms(1000); //1 second delay
		
		TOG(PORTC,PORTC0);
	}
}

uint8_t ondata(uint8_t* data_recv, uint8_t s_data, uint8_t* data_transm)
{
	if(s_data < 1) Err();
	else
	{
		uint8_t cmd = data_recv[0];
	
		switch (cmd){
			//Set Duty_cycle A, TOG PORTC1 when receive command
			case 0x1A:
				if(s_data < 3) Err();
				else PWM_SetDutyCycleA(((uint16_t)data_recv[1] << 8) | data_recv[2]);//Convert two uint8_t in one uint16_t	
				break;
				
			//Set Duty_cycle B
			case 0x1B:
				if(s_data < 3) Err();
				else PWM_SetDutyCycleB(((uint16_t)data_recv[1] << 8) | data_recv[2]);//Convert two uint8_t in one uint16_t
				break;
			
			case 0xF0:
				if(s_data < 3) Err();
				else PWM_SetTop(((uint16_t)data_recv[1] << 8) | data_recv[2]);//Convert two uint8_t in one uint16_t
				break;
				
			case 0xF1:
				if(s_data < 3) Err();
				else togAss = !togAss;
				break;

			case 0xF2:
				if(s_data < 3) Err();
				else command = ((uint16_t)data_recv[1] << 8) | data_recv[2];//Convert two uint8_t in one uint16_t
				break;
			
			default:
				break;
		}
	}

	int motor_frequency = (int) GetFrequency(1);
	uint8_t q = motor_frequency/255;
	uint8_t r = motor_frequency%255;
	
	//return the current frequency measure on T0, equal to 255*q + r
	data_transm[0] = q;
	data_transm[1] = r;
	return 2;
}

void Err()
{
	//SET(PORTC,PORTC1);
}

#endif