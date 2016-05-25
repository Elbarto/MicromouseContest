#include <wiringPi.h>
#include <stdio.h>
#include "I2C.h"

#ifdef DEBUG
#undef DEBUG
#endif
#define DEBUG 1

#define AddrCom 0x12

/*
	Fonctionne de paire avec le programme test_I2C.c du µC Atmega.
	Envoie un nombre et attend en retour le nombre + 1
*/

int main (void)
{

	int fd = I2C_Init(AddrCom);
	delay (500);

	uint8_t data[1];
	int temp = 0;
	printf("Entrez un entier 0-255 à envoyer :\n");
	scanf("%d",&temp);

	data[0] = (uint8_t) temp;
	I2C_Write(fd, data, 1);
	delay (500);

	I2C_Read(fd, data, 1);

	int result = data[0];
	printf("Valeur retourné : %d\n",result);

	return 0 ;
}