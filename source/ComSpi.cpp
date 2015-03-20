
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
    : SPI(mosi,miso,sclk), m_demuxA(demuxA), m_demuxB(demuxB), m_demuxC(demuxC), m_demuxD(demuxD), m_demuxEnable(demuxEnable)
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
    }
    return result;
}
char ComSpi::back_demux(void)
{
    char result = (char)-1;

    if(demuxIsUse) {
        (m_demuxPos == 0)? m_demuxPos=15:m_demuxPos--;
        change_demux();

        result = m_demuxPos;
    }
    return result;
}

char ComSpi::get_demux(void)
{
    char result = (char)-1;
    if(demuxIsUse)
        result=m_demuxPos;
    return   result ;
}

bool ComSpi::send(char portID, char adresseModule,string *flag,string *data)
{
    bool result=false;
    string formatedDataSend;
    string formatedDataReceive;
    //int valueReceive=0;
    //int CRC

    debug(DEBUG_SEND, "\n\r   -Debut du send. ");

    debug(DEBUG_SEND, "\n\r    -Debut set demux. ");
    if(portID > 0xFF) { //(char)-1) {
        m_demuxPos = portID;
        change_demux();
    }
    debug(DEBUG_SEND, "\n\r    -Fin set demux. ");

    // Sync //
    debug(DEBUG_SEND, "\n\r    -Debut Sync. ");
    formatedDataSend.append(1,SYNC);
    debug(DEBUG_SEND, "\n\r    -Fin Sync. ");

    // Address //
    debug(DEBUG_SEND, "\n\r    -Debut Address. ");
    formatedDataSend.append(1,adresseModule);
    debug(DEBUG_SEND, "\n\r    -Fin Address. ");

    // PFB //
    debug(DEBUG_SEND, "\n\r    -Debut PFB. ");
    switch(flag->size()) {
        case 1:
            formatedDataSend.append(1,1<<6);
            break;

        case 2:
            formatedDataSend.append(1,2<<6);
            break;

        case 3:
            formatedDataSend.append(1,3<<6);
            break;

        default:
            formatedDataSend.append(1,0<<6);
            break;
    }
    debug(DEBUG_SEND, "\n\r    -Fin PFB. ");

    // gestion ACK/NAK
    debug(DEBUG_SEND, "\n\r    -Debut ACK/NAK. ");
    formatedDataSend.at(formatedDataSend.length()-1) |= (NOACK << 4);
    debug(DEBUG_SEND, "\n\r    -Fin ACK/NAK. ");

    // NDB //
    debug(DEBUG_SEND, "\n\r    -Debut NDB. ");
    switch(data->size()) {
        case 1:
            formatedDataSend.at(formatedDataSend.length()-1) |= 1;
            break;

        case 2:
            formatedDataSend.at(formatedDataSend.length()-1) |= 2;
            break;

        case 3:
            formatedDataSend.at(formatedDataSend.length()-1) |= 3;
            break;

        default:
            formatedDataSend.at(formatedDataSend.length()-1) |= 0;
            break;
    }
    debug(DEBUG_SEND, "\n\r    -Fin NDB. ");

    // flag //
    debug(DEBUG_SEND, "\n\r    -Debut flag. ");
    if(flag->size() != 0) {
        formatedDataSend.append(*flag);
    }
    debug(DEBUG_SEND, "\n\r    -Fin flag. ");

    // data //
    debug(DEBUG_SEND, "\n\r    -Debut data. ");
    if(data->size() != 0) {
        formatedDataSend.append(*flag);
    }
    debug(DEBUG_SEND, "\n\r    -Fin data. ");

    // CRC //
    //Create CRC
    //Send CRC
    //Compare

    int tempValue=0;
    //Send Data
    debug(DEBUG_SEND, "\n\r    -Debut Send Data. ");
    debug(DEBUG_SEND, "\n\r     -Send: ");
    for (unsigned i=0; i<formatedDataSend.length(); ++i) {
        debug(DEBUG_SEND, "%i,",formatedDataSend.at(i));
    }

    tempValue = (formatedDataSend[0]<<8)+formatedDataSend[1];
    tempValue=write(tempValue);

    debug(DEBUG_SEND, "\n\r    -Fin Send Data. ");

        // Envoie si liker //
        debug(DEBUG_SEND, "\n\r    -Debut Traitement de l'information. ");
        debug(DEBUG_SEND, "\n\r     -Receive: ");
    if(tempValue == (formatedDataSend[0]<<8)+formatedDataSend[1]) {// tempValue ==(Sync+(PFB+ACK+NDB))
        formatedDataReceive.append(1,formatedDataSend[0]);
        formatedDataReceive.append(1,formatedDataSend[1]);

        for (unsigned i=2; i<formatedDataSend.length(); ++i) {
            tempValue = formatedDataSend[i];
            i++;
            if(i<formatedDataSend.length()) {
                tempValue = (tempValue<<8) + formatedDataSend[i];
            }
            tempValue=write(tempValue);
            formatedDataReceive.append(1,tempValue>>8);
            formatedDataReceive.append(1,tempValue&0xFF);
        }



        // Traitement de l'information //
        //debug(DEBUG_SEND, "\n\r    -Debut Traitement de l'information. ");
        //debug(DEBUG_SEND, "\n\r     -Send: ");
        for (unsigned i=0; i<formatedDataReceive.length(); ++i) {
            debug(DEBUG_SEND, "%i,",formatedDataReceive.at(i));
        }

        tempValue=formatedDataReceive[2];
        string::iterator it=formatedDataReceive.begin()+3;

        // flag //
        flag->clear();
        switch(tempValue>>6) {
            case 1:
                flag->append(1,*it);
                it++;
                break;

            case 2:
                flag->append(1,*it);
                it++;
                flag->append(1,*it);
                it++;
                break;

            case 3:
                flag->append(1,*it);
                it++;
                flag->append(1,*it);
                it++;
                flag->append(1,*it);
                it++;
                break;

                /*default:
                    formatedDataSend.append(1,0<<6);
                    break;*/
        }

        // ACK/NAK
        //

        // NDB //
        data->clear();
        switch(tempValue&0xFF) {
            case 1:
                data->append(1,*it);
                it++;
                break;

            case 2:
                data->append(1,*it);
                it++;
                data->append(1,*it);
                it++;
                break;

            case 3:
                data->append(1,*it);
                it++;
                data->append(1,*it);
                it++;
                data->append(1,*it);
                it++;
                break;

                /*default:

                    break;*/
        }

        // CRC //
        //

        result=true;
    }
    
    debug(DEBUG_SEND, "\n\r    -Fin Traitement de l'information. ");
    debug(DEBUG_SEND, "\n\r   -Fin du send. ");
    return result;
}