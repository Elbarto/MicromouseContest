#include <stdio.h>
#include <errno.h>
#include <wiringPiSPI.h>
#include "SPI.h"

/*
	Contient les fonctions nécessaire à la communication SPI en tant que Master
	Les pin sur la raspberry pi sont : 
		MISO = 21 MasterInSlaveOut
		MOSI = 19 MasterOutSlaveIn
		SCK = 23 Clock
		SS0/CE0 = 24 SlaveSelect
*/

//BusSpeed in Hz

int SPI_Init(int Channel, int BusSpeed)
{
	int fd;
	if(fd = wiringPiSPISetup(Channel, BusSpeed))
		printf("SPI communication initialisé avec succés.\n");
	else
	    fprintf(stderr,"I2C Init Error.  Errno is: ",strerror(errno));

    return fd;
}

int SPI_RWData(int Channel, unsigned char* buffer, int DataLen)
{
	int res;

	if(res = wiringPiSPIDataRW(Channel, buffer, DataLen))
	{
		if(DEBUG) printf("SPI Read/Write of %d Byte transaction succed\n",DataLen);
		return 1;
	}

	if(DEBUG) fprintf(stderr,"SPI Read/Write transaction Error.  Errno is: ",strerror(errno));

	return 0;
}