/**
  * @file       TTask.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef COMSPI_H
#define COMSPI_H

#define DEBUG_SEND 1

#include "mbed.h"
#include <string>
#include "debug.h"
#include "ComSpiDefine.h"

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


 // renvois la position qu'il est rendu ( -1 == pas de demux ou problem)
    char next_demux(void);
    char back_demux(void);
    char get_demux(void);




    virtual int write(int value);
    bool send(char portID, char adresseModule,string *flag,string *data);
   /* bool send(char portID, char adresseModule,char *flag,char *data);
    bool send(char portID, char adresseModule,int *flag,char *data);
    bool send(char portID, char adresseModule,char *flag,int *data);
    bool send(char portID, char adresseModule,int *flag,int *data);*/
};
#endif // COMSPI_H