/*
 * I2C_Slave.h
 *
 * Created: 12/03/2016 16:42:34
 *  Author: jolanbarbancon
 */ 

/*
IMPORTANT INFORMATION
	- Do not forget the pull-up resistor (typ. 4.7K)
	- CPU Clock as slave must be at least 16* the SCL clock 
	- Pin used :
		SDA : 27
		SCL : 28
*/


#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

//----------Define mode of Operation--------

/*TWCR register can
	- SET or CLR the (N)ACK byte
*/
//Setup I2C to send ACK, Meaning we succeed to receive the bytes and are ready to receive more.
#define TWACK (TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA)|(1<<TWIE))

//setup the I2C to send NACK, when master meaning the end of reception as master, when slave meaning he receive last byte or that he can't receive more bytes
#define TWNACK (TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWIE))

//reset the I2C hardware (used when the bus is in a illegal state)
#define TWRESET (TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO)|(1<<TWEA)|(1<<TWIE))
//---------------------------------


//Prototype
void I2C_Init(uint8_t addr,uint8_t sizeBuff, uint8_t (*func)(uint8_t*,uint8_t,uint8_t*));
void I2C_Stop();




#endif /* I2C_SLAVE_H_ */