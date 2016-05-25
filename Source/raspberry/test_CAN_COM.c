#include <wiringPi.h>
#include <stdio.h>
#include "I2C.h"

#ifdef DEBUG
#undef DEBUG
#endif
#define DEBUG 1

#define CHANNEL 0
#define BUSSPEED 50000

/*
	Test la communication avec le CAN
	I/O pin 11 sur CONVST du CAN
	Une conversion commence sur front descendant du CONVST
*/

int main (void)
{
	//Init les port I/O
	wiringPiSetup () ;
  	pinMode (0, OUTPUT);//Pin 11
	digitalWrite (0, HIGH);//Met CONVST du CAN a 1


  	//Init la COM SPI
	int fd = SPI_Init(CHANNEL, BUSSPEED);
	delay (100);

	//prepare la reception de la conversion
	unsigned char data[10];
	unsigned int i;
	printf("Appuyer sur Entrez pour demarer une conversion:\n");
	fflush(stdin);
	getchar();

	digitalWrite (0, LOW); //Commence la conversion
	delay(1);//Attend la fin de la conversion, dure normalement 7,5uS

	//Lit les data retourné par le CAN
	SPI_RWData(CHANNEL, data, 1);
	delay (500); //Attend le traitement

	printf("Valeur retourné : %d\n",data[0]);

	return 0 ;
}

