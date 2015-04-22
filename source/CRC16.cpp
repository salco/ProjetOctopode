#include "CRC16.h"

/*
 * FUNCTION: calcCRC calculates a 2-byte CRC on serial data using
 * CRC-CCITT 16-bit standard maintained by the ITU
 * ARGUMENTS: queue_ptr is pointer to queue holding are a to be CRCed
 * queue_size is offset into buffer where to stop CRC calculation
 * RETURNS: 2-byte CRC
 */

#define POLY 0x8005//0x8408
/*
//                                      16   12   5
// this is the CCITT CRC 16 polynomial X  + X  + X  + 1.
// This works out to be 0x1021, but the way the algorithm works
// lets us use 0x8408 (the reverse of the bit pattern).  The high
// bit is always assumed to be set, thus we only use 16 bits to
// represent the 17 bit value.
*/


uint16_t CRC16_BUYPASS(const char *data, size_t len) { 
  uint16_t crc = 0x0000; 
  size_t j; 
  int i; 
  for (j=len; j>0; j--) { 
    crc ^= (uint16_t)(*data++) << 8; 
    for (i=0; i<8; i++) { 
      if (crc & 0x8000) crc = (crc<<1) ^ 0x8005; 
      else crc <<= 1; 
    } 
  } 
  return (crc); 
} 

/*int main() { 
  uint8_t test[9]  = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39}; 
  uint8_t tgil[29] = {0x00,0x0B,0x01,0x0E,0x01,0xC6,0x00,0x00,0x00,0x00, 
                      0x00,0x00,0x33,0x31,0x30,0x31,0x34,0x31,0x30,0x30, 
                      0x41,0x00,0x00,0x04,0x24,0x14,0x16,0x06,0x49}; 
  uint16_t crc; 
  crc = CRC16_BUYPASS(test, 9); 
  //printf("Rocksoft check value: 0x%04X, test ", crc); 
  //if (crc==0xFEE8) printf("passed.\n"); else printf("failed!\n"); 
  crc = CRC16_BUYPASS(tgil, 29); 
  //printf("CRC gil's data: 0x%04X\n", crc); 
  return 0; 
} */

unsigned short calculateCRC16(const char *data_p, unsigned short length)
{
    unsigned char i;
    unsigned int data;
    unsigned int crc = 0xffff;

    if (length == 0)
    return (~crc);

    do
    {
        for (i=0, data=(unsigned int)0xff & *data_p++;
        i < 8;
        i++, data >>= 1)
        {
            if ((crc & 0x0001) ^ (data & 0x0001))
            crc = (crc >> 1) ^ POLY;
            else  crc >>= 1;
        }
    } while (--length);

    crc = ~crc;
    data = crc;
    crc = (crc << 8) | (data >> 8 & 0xff);

    return (crc);
}