#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include "I2C.h"

#ifdef DEBUG
#undef DEBUG
#endif
#define DEBUG 1

#define AddrCom 0x12

/*
	Fonctionne de paire avec le programme test_Moteur.c du µC.
*/

int main (void)
{

	int fd = I2C_Init(AddrCom);
	delay(500);
	int data = 0, keep = 1, cmd = 0;
	uint8_t buffer[10];
	uint16_t hex_value = 0;

	while(keep)
	{
		printf("0 : Set PWM_A duty_cycle \n1 : Set PWM_B duty_cycle \n2 : Set PWM Frequency\n3 : Toggle Asservissement\n4 : Set Command\n5 : Quit\n");
		scanf("%d",&cmd);
		printf("Enter a 16 bit Hexadecimal value like FFAA :\n");
		scanf("%hx",&hex_value);

		buffer[1] = (uint8_t)(hex_value>>8);
		buffer[2] = (uint8_t)hex_value;
		printf("%x and %x\n",buffer[1],buffer[2]);

		switch(cmd){
			case 0:
				buffer[0] = 0x1A;
				if(!I2C_Write(fd, buffer, 3)) printf("Error, transaction failed.\n");
				break;

			case 1:
				buffer[0] = 0x1B;
				if(!I2C_Write(fd, buffer, 3)) printf("Error, transaction failed.\n");
				break;

			case 2:
				buffer[0] = 0xF0;
				if(!I2C_Write(fd, buffer, 3)) printf("Error, transaction failed.\n");
				break;

			case 3:
				buffer[0] = 0xF1;
				if(!I2C_Write(fd, buffer, 3)) printf("Error, transaction failed.\n");
				break;

			case 4:
				buffer[0] = 0xF2;
				if(!I2C_Write(fd, buffer, 3)) printf("Error, transaction failed.\n");
				break;

			case 5:
				keep = 0;
				break;

			default:
				keep = 0;
				break;
		}

		if(keep)
		{
			delay (10);

			if (!I2C_Read(fd, buffer, 2))
				printf("Erro while readin I2C result.\n");
		    else {
		      printf("Returned value : %d et %d\n",buffer[0],buffer[1]);
		    }
		}

	}

	return 0 ;
}