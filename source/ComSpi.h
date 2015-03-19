/**
  * @file       TTask.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef COMSPI_H
#define COMSPI_H
// faire un debug pour la com spi
#define SYNC 84 //0b01010100
#define PFB0 0
#define PFB1 1
#define PFB2 2
#define PFB3 3
#define NOACK 0
#define TXACK 1
#define RXACK 2
#define RXNAK 3
#define NDB00 0
#define NDB01 1
#define NDB02 2


#include "mbed.h"

class ComSpi : public SPI
{
    bool demuxIsUse;
    char m_demuxPos;
    PinName m_demuxA;
    PinName m_demuxB;
    PinName m_demuxC;
    PinName m_demuxD;
    PinName m_demuxEnable;
    
 void change_demux(void);
public:
    ComSpi(PinName mosi, PinName miso, PinName sclk, PinName _unused=NC);
    ComSpi(PinName mosi, PinName miso, PinName sclk, PinName demuxA, PinName demuxB, PinName demuxC, PinName demuxD, PinName demuxEnable);
    virtual ~ComSpi();



    bool next_demux(void);
    bool back_demux(void);




    virtual int write(int value);
    bool send(char portID, char adresseModule,char *flag,char *data);
    bool send(char portID, char adresseModule,int *flag,char *data);
    bool send(char portID, char adresseModule,char *flag,int *data);
    bool send(char portID, char adresseModule,int *flag,int *data);
};
#endif // COMSPI_H