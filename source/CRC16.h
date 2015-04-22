#ifndef CRC16_H
#define CRC16_H
#include <stdio.h> 
#include <stddef.h> 
#include <stdint.h> 

uint16_t CRC16_BUYPASS(const char *data, size_t len);
unsigned short calculateCRC16(const char *data_p, unsigned short length);

#endif