/*
 * CommunicationNeuronale.h
 *
 *  Created on: Mar 10, 2015
 *      Author: salco
 */

#ifndef COMMUNICATIONNEURONALE_H_
#define COMMUNICATIONNEURONALE_H_

#include "mbed.h"
//#include <SPI.h>



class ComModulesSPI : public SPI
{
    int m_regPortUse; // set in the init
    int m_regPortLost;// flag 1 si lost
    char m_demuxPos;
    
public:
    ComModulesSPI(PinName mosi, PinName miso, PinName sclk, PinName _unused=NC);
    virtual ~ComModulesSPI();
    
    bool initCom(void);

    bool next_demux(void);
    bool back_demux(void);


    bool isValide(char portID);
    bool tryComPort(char portID);//just faire le sync et crc pour voire si lautre est la
    
    virtual int write(int value);
    bool send(char portID, char type,char *flag,char *data);
    bool send(char portID, char type,int *flag,char *data);
    bool send(char portID, char type,char *flag,int *data);
    bool send(char portID, char type,int *flag,int *data);
};

#endif /* COMMUNICATIONNEURONALE_H_ */