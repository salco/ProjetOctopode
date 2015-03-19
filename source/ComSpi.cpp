
#include "ComSpi.h"

ComSpi::ComSpi(PinName mosi, PinName miso, PinName sclk, PinName _unused) : SPI(mosi,miso,sclk,_unused)
{
    // m_com = new SPI(mosi,miso,sclk,_unused);
    //m_regPortUse=0;
    //m_regPortLost=0;
    m_demuxPos=0;
    demuxIsUse=false;
}

ComSpi::ComSpi(PinName mosi, PinName miso, PinName sclk, PinName demuxA, PinName demuxB, PinName demuxC, PinName demuxD, PinName demuxEnable)
    : SPI(mosi,miso,sclk,NC), m_demuxA(demuxA), m_demuxB(demuxB), m_demuxC(demuxC), m_demuxD(demuxD), m_demuxEnable(demuxEnable)
{
    m_demuxPos=0;
    demuxIsUse=true;
}

ComSpi::~ComSpi()
{
    //if(m_com)
    // delete(m_com);
}
void ComSpi::change_demux(void)
{
    if(demuxIsUse) {
    DigitalOut pinDemuxA(m_demuxA);
    DigitalOut pinDemuxB(m_demuxB);
    DigitalOut pinDemuxC(m_demuxC);
    DigitalOut pinDemuxD(m_demuxD);
    DigitalOut pinDemuxEnable(m_demuxEnable);

    pinDemuxEnable=0;

    if(m_demuxPos & 1) pinDemuxA=1; //0b0001
    else pinDemuxA=0;
    if(m_demuxPos & 2) pinDemuxB=1; //0b0010
    else pinDemuxB=0;
    if(m_demuxPos & 4) pinDemuxC=1; //0b0100
    else pinDemuxC=0;
    if(m_demuxPos & 8) pinDemuxD=1; //0b1000
    else pinDemuxD=0;

    pinDemuxEnable=1;
    }
}
int ComSpi::write(int value)
{
    int a;
    a= SPI::write(value);
    return a;
}
char ComSpi::next_demux(void)
{
    char result = (char)-1;

    if(demuxIsUse) {
        (m_demuxPos == 15)? m_demuxPos=0:m_demuxPos++;
        change_demux();
        result = m_demuxPos;
        result = true;
    }
    return result;
}
char ComSpi::back_demux(void)
{
    char result = (char)-1;
    
    if(demuxIsUse) {
        (m_demuxPos == 0)? m_demuxPos=15:m_demuxPos--;
        change_demux();
        
        result = true;
    }
    return result;
}
bool ComSpi::send(char portID, char adresseModule,char *flag,char *data)
{
    bool result=false;
    int valueSend = SYNC;
    int valueReceive=0;
    //int CRC
    
    if(portID =! -1){
        m_demuxPos = portID;
        change_demux();
        }

    valueReceive=write(valueSend);
    if(valueReceive == valueSend) {
        valueSend=(adresseModule<<8);

        if(*flag != 0) valueSend+= (PFB1 << 6);
        else valueSend+= (PFB0 << 6);

        valueSend+= (NOACK << 4);

        if(*data != 0) valueSend+= (NDB01 );
        else valueSend+= (NDB00 );

        valueReceive=write(valueSend);
        if(valueReceive>>8 == adresseModule) {
            //fini la sycronisation et la on envoie les data


            if(*flag != 0) valueSend = *flag;
            else valueSend=0;

            if(*data != 0) valueSend= (valueSend<<4)+(*data);

            valueReceive=write(valueSend);
            if((*flag != 0) && (*data != 0)) *flag = valueReceive>>8;
            else if(*flag != 0) *flag = valueReceive;
            else if(*data != 0) *data = valueReceive;
            
            //Create CRC
            //Send CRC
            //Compare
            result=true;
        }
    }
    return result;
}