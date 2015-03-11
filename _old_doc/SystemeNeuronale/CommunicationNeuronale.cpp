/*
 * CommunicationNeuronale.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: salco
 */
#include "CommunicationNeuronale.h"
ComModulesSPI::ComModulesSPI(PinName mosi, PinName miso, PinName sclk, PinName _unused) : SPI(mosi,miso,sclk,_unused)
{
    // m_com = new SPI(mosi,miso,sclk,_unused);
    m_regPortUse=0;
    m_regPortLost=0;
    m_demuxPos=0;
}
ComModulesSPI::~ComModulesSPI()
{
    //if(m_com)
    // delete(m_com);
}
int ComModulesSPI::write(int value)
{
  int a;
  a= SPI::write(value);
return a;
}