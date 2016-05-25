#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <wiringPiI2C.h>
#include "I2C.h"


/*
   Contients les fonctions permettant à la raspberry de communiquer en I2C.
   Les pins de communication I2C de la raspberry sont : SDA = 3 et SCL = 5
*/


//Initialise la communication I2C avec l'appareil en AddrId
int I2C_Init(int AddrId)
{
   int fd;
   if( fd = wiringPiI2CSetup(0x12) )
      printf("I2C communication initialisé avec succés.\n");
   else
      fprintf(stderr,"I2C Init Error.  Errno is: ",strerror(errno));

   return fd; //Linux file handler, used by other function.
}

int I2C_Write(int fd, uint8_t* buffer, int len)  
{
   int ret = write(fd,buffer,len);
   if(ret != len) 
   {
      printf("Error, I2C transmission failed\n");
      return 0;
   }

   return 1;
}

int I2C_Read(int fd, uint8_t* buffer, int len)
{
   int ret = read(fd, buffer, len);
   if(ret != len)
   {
      printf("Error, I2C reception failed\n");
      return 0;
   }

   return 1;
}


