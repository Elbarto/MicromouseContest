#ifndef SPI_H
#define SPI_H

#ifndef DEBUG
#define DEBUG 0
#endif

int SPI_Init(int Channel, int BusSpeed);
int SPI_RWData(int Channel, unsigned char* buffer, int DataLen);


#endif
