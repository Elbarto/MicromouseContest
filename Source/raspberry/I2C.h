#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#ifndef DEBUG
#define DEBUG 0
#endif

int I2C_Init(int AddrId);
int I2C_Read(int fd, uint8_t* buffer, int len);
int I2C_Write(int fd, uint8_t* buffer, int len);

#endif
