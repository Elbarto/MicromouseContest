#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif

#include <avr/io.h>
#include <stdlib.h>
#include <util/twi.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Global.h"
#include "I2C_Slave.h"

/*
------ global variables -----
*/

 //buffer to store received bytes
uint8_t r_index = 0;
uint8_t* recv_buff;

//buffer so store bytes to send
uint8_t t_index = 0;
uint8_t* tran_buff;
	
//Def of callback
uint8_t (*callBack)(uint8_t*,uint8_t,uint8_t*);//Data receive buffer, size receive, data to send buffer / Return size of data to send

//variable to indicate if something went horribly wrong
uint8_t reset = 0;

uint8_t transmit_size = 0;
uint8_t max_size_buff = 0;

/*
-----------------------------
*/


//Init the I2C/TWI COM
void I2C_Init(uint8_t addr,uint8_t sizeBuff, uint8_t (*func)(uint8_t*,uint8_t,uint8_t*))
{
	callBack = func;
	recv_buff = calloc(sizeBuff,sizeof(*recv_buff));
	tran_buff = calloc(sizeBuff,sizeof(*tran_buff));
	max_size_buff = sizeBuff;
	
	TWAR = addr<<1;//Set the slave address
	/*Setup TWI COM
		-TWEN Enable TWI
		-TWEA Enable the send of ACK bytes when receive addr, general call or data bytes
		-TWIE Enable interrupt request, request are made when TWINT is set to 1 (sei() must be enable for this)
		-TWINT Set an TWI interrupt to mean the init is done ?
	*/
	TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWEN); 
}

//Stop/disconnect the device from the bus line
void I2C_Stop()
{
	TWCR &= ~((1<<TWIE) | (1<<TWEA) | (1<<TWEN) );
}


//Occurred when TWI Interrupt meaning software has to process data. TWINT must be set to 1 for TWI operation continue
ISR(TWI_vect){
	switch(TW_STATUS){	
		
		//--------------Slave as Receiver--------------------
		case 0x60://SLave addr and W has been received
			TWACK; //Send a ACK bit to mean it's ready to receive byte
			r_index = 0; //Set receive data buffer index
			break;
		
		case 0x80:  //a byte was received, store it and setup the buffer to receive another
			recv_buff[r_index] = TWDR;
			r_index++;
			if(r_index < max_size_buff) TWACK;
			else TWNACK;
			
			break;	
			
		case 0x68://adressed as slave while in master mode should never happen, better reset; Je n'ai pas vraiment compris...
			reset = 1;
			break;
			
		case 0x88://Previously addressed with SLA+W, data has been received and NACK has been returned
			break;
					
		case 0xA0: //Stop or rep start, reset state machine
			//Callback information receive
			transmit_size = (*callBack)(recv_buff,r_index,tran_buff);
			TWACK;
			break;
		//--------------Slave as Transmitter--------------------
		case 0xA8:  //SLA+R received, prep for transmission and load first data
			if(transmit_size){
				t_index=1;
				TWDR = tran_buff[0];
				TWACK;
			}
			else{
				TWDR = 0x00;
				TWNACK;
			}
			break;
		
		case 0xB8:  //data transmitted and ACK received from master, send next byte
			if(!transmit_size){
				TWDR = 0x00;
				TWNACK;
			}
			else{
				TWDR = tran_buff[t_index];
				t_index++;
				if(t_index >= transmit_size){ //If it's the last byte, send NACK to say the end
					TWNACK;
					transmit_size = 0;
				}
				else TWACK;
			}
			break;
		
		case 0xC8: //last byte send and acked by master
			//last bytes should not be acked, ignore till start/stop
			//reset=1;
			break;
		
		case 0xC0: //byte send and NACK receive from Master, meaning he doesn't expect more byte
			TWACK;
			transmit_size = 0;
			break;
		
		//--------------------- bus error---------------------------------
		//illegal start or stop received, reset the I2C hardware
		case 0x00:
			TWRESET;
			break;
	}
}