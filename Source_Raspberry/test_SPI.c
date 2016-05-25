#include <wiringPi.h>
#include <stdio.h>
#include "SPI.h"

#ifdef DEBUG
#undef DEBUG
#endif
#define DEBUG 1

#define CHANNEL 0
#define BUSSPEED 50000

/*
	Fonctionne de paire avec le programme test_SPI.c du µC.
	Envoie un nombre et attend en retour le nombre + 1
*/

int main (void)
{

	int fd = SPI_Init(CHANNEL, BUSSPEED);
	delay (500);

	unsigned char data[10];
	unsigned int i;
	printf("Entrez un caractere à envoyer :\n");
	fflush(stdin);
	scanf("%c",data);
	printf("Va envoyer %d\n",(int) data[0]);
	//ata[0] = (unsigned char) i;

	//Envoie la valeur
	SPI_RWData(CHANNEL, data, 1);
	delay (500); //Attend le traitement

	//recupere la nouvelle valeur
	data[0] = '\n';
	SPI_RWData(CHANNEL, data, 1);

	printf("Valeur retourné : %d\n",data[0]);

	return 0 ;
}