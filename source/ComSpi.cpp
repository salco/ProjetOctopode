
#include "ComSpi.h"

ComSpi::ComSpi(PinName mosi, PinName miso, PinName sclk, PinName _unused) : SPI(mosi,miso,sclk,_unused)
{
    // m_com = new SPI(mosi,miso,sclk,_unused);
    //m_regPortUse=0;
    //m_regPortLost=0;
    m_demuxPos=0;
    demuxIsUse=false;
    chainedListFirst = 0;
    chainedListLast = 0;
    flagSPI.getBytes = 0;
    //result = 0;
    counterData = 0;
    counterTotale = 0;
    /*for(int i=0;i<MAXTABLE;i++)
    {
        bufferSend[i] = 0;
        bufferReceive[i] = 0;
    }
    bufferSend[0] = SYNC;*/
}

struct module_t* ComSpi::createModule(void) {
    if(chainedListFirst == 0) {
        chainedListFirst = new module_t ;
        chainedListLast = chainedListFirst;
    } else {
        chainedListLast->next = new module_t;
        chainedListLast = chainedListLast->next;
    }
    chainedListLast->next = 0;
    return chainedListLast;
}

ComSpi::ComSpi(PinName mosi, PinName miso, PinName sclk, PinName demuxA, PinName demuxB, PinName demuxC, PinName demuxD, PinName demuxEnable)
    : SPI(mosi,miso,sclk), m_demuxA(demuxA), m_demuxB(demuxB), m_demuxC(demuxC), m_demuxD(demuxD), m_demuxEnable(demuxEnable)
{
    m_demuxPos=0;
    demuxIsUse=true;
    format(8,0);//16,0); //recente modification
}

ComSpi::~ComSpi()
{
    //pt deleter les pointeur mais sa ser pas vrm a grand chause
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
        DigitalOut pinDemuxEnable(m_demuxEnable);//,1);
//wait(1);
        pinDemuxEnable=0;
//wait(1);
        if(m_demuxPos & 1) pinDemuxA=1; //0b0001
        else pinDemuxA=0;
        if(m_demuxPos & 2) pinDemuxB=1; //0b0010
        else pinDemuxB=0;
        if(m_demuxPos & 4) pinDemuxC=1; //0b0100
        else pinDemuxC=0;
        if(m_demuxPos & 8) pinDemuxD=1; //0b1000
        else pinDemuxD=0;
//wait(1);
       // pinDemuxEnable=1;
        //wait(1);
    }
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
unsigned char spiCurrentState;
int ComSpi::write(int value)
{
     DigitalOut pinDemuxEnable(m_demuxEnable);
    //DigitalOut pinDemuxEnable(m_demuxEnable,0);
    int a;
     pinDemuxEnable=1;
     /*   switch(spiCurrentState)
    {
        case 0:
        a= SPI::write(0x12);
        spiCurrentState++;
        break;
        default:
        a= SPI::write(0xF5);
        spiCurrentState =0;
        break;
    }*/
     wait_us(5);
    a= SPI::write(value);
    wait_us(5);
     pinDemuxEnable=0;
     sneekpeek.append(1,value);
     wait_us(1000);
    return a;
}


bool ComSpi::send(char portID,unsigned char adresseModule,string *flag,string *data)
{
    bool result=false;
    string formatedDataSend;
    string formatedDataReceive;//DEBUG_COMPACT
    char settingMaster = 0;
    char settingSlave = 0;

    debug(DEBUG_SEND| DEBUG_COMPACT, "\n\r   -Debut du send. ");

    debug(DEBUG_SEND, "\n\r    -Debut set demux. ");

    if(portID < 1) portID = 0;
    else if(portID > 16) portID = 16;
    debug(DEBUG_SEND, "\n\r     -Change PORT. ");
    m_demuxPos = portID;
    change_demux();

    debug(DEBUG_SEND, "\n\r    -Fin set demux. ");

    // Sync //
    debug(DEBUG_SEND, "\n\r    -Debut Sync. ");
    formatedDataSend.append(1,SYNC);
    debug(DEBUG_COMPACT, "\n\r    -SYNC ADDED: %02X ",formatedDataSend[0]);
    debug(DEBUG_SEND, "\n\r    -Fin Sync. ");

    // Address //
    debug(DEBUG_SEND, "\n\r    -Debut Address. ");
    formatedDataSend.append(1,adresseModule);
    debug(DEBUG_COMPACT, "\n\r    -ADDR ADDED: %02X, %02X ",formatedDataSend[0],formatedDataSend[1]);
    debug(DEBUG_SEND, "\n\r    -Fin Address. ");

    // PFB //
    debug(DEBUG_SEND, "\n\r    -Debut PFB. ");
   // if(flag != 0)
   // {
    switch(flag->size()) {
        case 1:
            if(flag->at(0) == 0) formatedDataSend.append(1,0<<6); //0 byte
            else          formatedDataSend.append(1,1<<6); //1 byte
            break;

        case 2:
            formatedDataSend.append(1,2<<6); //2 byte
            break;

        case 3:
            formatedDataSend.append(1,3<<6); //3 byte
            break;

        default:
            formatedDataSend.append(1,0<<6); //cas impossible //0 byte
            break;
    }
    //}
    debug(DEBUG_COMPACT, "\n\r    -PFB ADDED: %02X, %02X, %02X ",formatedDataSend[0],formatedDataSend[1],formatedDataSend[2]);
    debug(DEBUG_SEND, "\n\r    -Fin PFB. ");

    // gestion ACK/NAK
    debug(DEBUG_SEND, "\n\r    -Debut ACK/NAK. ");
    formatedDataSend.at(formatedDataSend.length()-1) |= (NOACK << 4);
    debug(DEBUG_COMPACT, "\n\r    -ACK ADDED: %02X, %02X, %02X ",formatedDataSend[0],formatedDataSend[1],formatedDataSend[2]);
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
    //debug(DEBUG_COMPACT, "\n\r    -NDB ADDED: %02X, %02X, %02X ",formatedDataSend[0],formatedDataSend[1],formatedDataSend[2]);
    debug(DEBUG_SEND, "\n\r    -Fin NDB. ");

    settingMaster = formatedDataSend[formatedDataSend.length()-1];
   
    // flag //
    debug(DEBUG_SEND, "\n\r    -Debut flag. ");
    if(flag->size() != 0) {
        formatedDataSend.append(*flag);
        //debug(DEBUG_COMPACT, "\n\r    -FLAG ADDED: %02X, %02X, %02X, %02X ",formatedDataSend[0],formatedDataSend[1],formatedDataSend[2],formatedDataSend[3]);
    }
    debug(DEBUG_SEND, "\n\r    -Fin flag. ");

//ici tu envoi deja ton premier stuf


 debug(DEBUG_SLIM, "\n\r    -settingMaster : %X , %i, %X ",settingMaster, (2+(settingMaster>>6)),formatedDataSend[(2+(settingMaster>>6))] );



    for(int retryLoop=0; (retryLoop<3) && (!result); retryLoop++) {

        debug(DEBUG_SEND|DEBUG_COMPACT, "\n\r      -Tentative: %d \n\r",retryLoop);
        formatedDataReceive.clear();
        settingSlave =0;
        counterTotale =0;
        sneekpeek.clear();
        //Send Data
//        debug(DEBUG_SEND, "\n\r    -Debut Send Data. ");
//        debug(DEBUG_SEND|DEBUG_COMPACT, "\n\r     -Send: ");
//        for (unsigned i=0; i<formatedDataSend.length(); ++i) debug(DEBUG_SEND |DEBUG_COMPACT, "%02X,",formatedDataSend.at(i));

        //int twoBytesArray;
        //twoBytesArray = (formatedDataSend[0]<<8)|(formatedDataSend[1]);
        //twoBytesArray=write(twoBytesArray);

        for(int i = 0; (i < formatedDataSend.length()) && (i<=(2+(settingMaster>>6))); ++i) {
            formatedDataReceive.append(1,write(formatedDataSend[i]));//debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM, "\n\r -A:%i ",i);
            debug(DEBUG_SEND |DEBUG_COMPACT, " %02X,",formatedDataSend.at(i));
        }

        if(formatedDataReceive[0] == SYNC) {
            debug(DEBUG_COMPACT, "\n\r    -Receve transmission. ");
            //!!!!!!!! Problem ici write dans un mais pas lautre
             wait_us(3000);
            if(retryLoop == 0) {
                formatedDataSend.append(1,0);//2,0); cest une patch tempo parce que je trouve pas ou il manque la donner
                }
            formatedDataReceive.append(1,write(0));
           // debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM, "\n\r -B: ");
            
            settingSlave = formatedDataReceive[formatedDataReceive.length()-1];
            debug(DEBUG_COMPACT, "\n\r       -settingSlave %02X",settingSlave);
            if(retryLoop == 0) {
                /*switch(formatedDataReceive[formatedDataSend.length()-1] >> 6) {
                    case 1:
                        formatedDataSend.append(1,0); //1 byte
                        break;

                    case 2:
                        formatedDataSend.append(2,0); //2 byte
                        break;

                    case 3:
                        formatedDataSend.append(3,0); //3 byte
                        break;

                        //default:
                        //    formatedDataSend.append(1,0<<6); //0 byte
                        //    break;
                }*/
                formatedDataSend.append(settingSlave>>6,0);
            }

            int bufferFlag = 0;

            for(int i = (settingMaster>>6); i != 0; i--) { //ici on remplie le buffer des data du flag
                // je considere avec erreur que il nexiste pas de flag plus grand que 2 bytes (facilite le code de depart)
                //!!! Pt metre fonct stein qui tronc de debut a fin pour remplacer les linge dessous.
                bufferFlag = bufferFlag<<8;
                bufferFlag += formatedDataSend[2+i];
            }

            counterTotale = ((2+(settingMaster>>6))+1);
            counterTotale = counterTotale+(settingSlave>>6)+abs((settingMaster & 0x0F) - (settingSlave & 0x0F));
        debug( "\n\r    -size : %02X",counterTotale);
        
            switch(bufferFlag) { //plus facile pour savoir ce que tu doit tatenre a recevoire
                case 1://Request Init Info
                    if(retryLoop == 0) {
                        
                        formatedDataSend.append(settingSlave & 0x0F,0);
                        //chek pour comment avoir un address
                    }
                    //verifier si la fonction fait ce quil edt suposer
                    for(int i = ((2+(settingMaster>>6))+1); i < formatedDataSend.length()-1; ++i) {
                        formatedDataReceive.append(1,write(formatedDataSend[i]));
                        //debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM, "\n\r -C:%i ",i);
                    }
                    //templatePtr =searchAddr(0);
                    // 1 byte flag + 3 byte de data
                    //bufferSend[4] = (1<<6) + 3;//[2+(bufferReceive[2]>>6)+1] = (1<<6);


                    //if((templatePtr->next)==0)
                    //    bufferSend[5] = 0b101;//bufferReceive[2+(bufferReceive[2]>>6)+1+bufferReceive[2+(bufferReceive[2]>>6)+1]] = 0b101;
                    //else
                    //    bufferSend[5] = 0b10;

                    //bufferSend[6] = templatePtr->basicInfo.osnapRegisterB.getByte;
                    //bufferSend[7] = templatePtr->basicInfo.osnapRegisterC.getByte;
                    //bufferSend[8] = templatePtr->basicInfo.osnapRegisterD.getByte;
                    break;

                case 2: //Slave contient un/des autre(s) module(s) sans adresses
                    break;

                case 3: //Flag Critique
                    break;

                case 4: //Flag Alerte
                    break;

                case 5: //Slave ne contient plus de module sans adresse
                    break;

                case 6: //Master request address update
                    break;

                default: //Get update (normale)
                    //if(retryLoop == 0) {
                    //    formatedDataSend.append(abs((settingMaster & 0x0F) - (settingSlave & 0x0F)),0);//je considere que cest fait apres avoire ajouter les data a nous
                    //    }
                    break;
            }
            //counterTotale = 2+(bufferReceive[2]>>6)+1;
            //counterTotale = counterTotale+(bufferSend[counterTotale]>>6)+abs((bufferReceive[2] & 0x5F) - (bufferSend[counterTotale] & 0x5F));
           // if(retryLoop == 0) {
               debug( "\n\r    -size : %02X ,  %02X",formatedDataSend.size(),counterTotale);
               // if(formatedDataSend.size()<counterTotale){
                 //   formatedDataSend.append(counterTotale-formatedDataSend.size(),0);
                //}
            //}   



            // Envoie le reste si liker //
            // DATA //
            unsigned short templateValue=0;
            if(retryLoop == 0) {
            // CRC //
            debug(DEBUG_SEND, "\n\r    -Debut CRC16. ");
            //CRC16* templateCRC;
            //templateCRC = new CRC16();
            //!!!utiliser string cest plus simple
            
            
            //char templateTable[formatedDataSend.length()+1];
            //for (unsigned i=0; i<formatedDataSend.length()+1; ++i) templateTable[i]=0;
            //for (unsigned i=0; i<formatedDataSend.length(); ++i) templateTable[i]=formatedDataSend[i];
            //debug(DEBUG_SEND, "\n\r     - envoi au crc: %02X,%02X,%02X,%02X,%02X,%02X ",templateTable[0],templateTable[1],templateTable[2],templateTable[3],templateTable[4],templateTable[5],templateTable[6]);

           // templateValue = /*templateCRC->*/calculateCRC16(templateTable,formatedDataSend.size()-1); //atention pt un probleme de sortie du range
            //templateValue = /*templateCRC->calculateCRC16*/CRC16_BUYPASS(formatedDataSend.c_str(),formatedDataSend.size()); //atention pt un probleme de sortie du range
            templateValue =CRC16_BUYPASS(sneekpeek.c_str(),sneekpeek.size()); //patch
            
            formatedDataSend.append(1,templateValue>>8);
            formatedDataSend.append(1,templateValue & 0xFF);
            }
            formatedDataReceive.append(1,write(formatedDataSend[formatedDataSend.size()-2]));//templateValue>>8));
            //debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM, "\n\r -D: ");
            formatedDataReceive.append(1,write(formatedDataSend[formatedDataSend.size()-1]));//(templateValue & 0xFF));
            //debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM, "\n\r -E: ");
            
            
             
            ///////////////////////

            //avant faut calculer les dernier byte grace a la version 2.0
            /*for(int i = 0; i < formatedDataSend.length(); ++i) {
                formatedDataReceive.append(1,write(formatedDataSend[i]));
            }*/

            // verification du CRC slave
            // CRC //
            templateValue = CRC16_BUYPASS(formatedDataReceive.c_str(),formatedDataReceive.size()-2);// utiliser les data de setting slave
            
            if(((templateValue>>8)==(formatedDataReceive.at( formatedDataReceive.length()-2))) &&
                 ((templateValue&0xFF)==(formatedDataReceive.at( formatedDataReceive.length()-1))))
            {
                result=true;
                }
                else
                {
                    result=false;
                    }
            //templateValue=((formatedDataReceive.at( formatedDataReceive.length()-2)) << 8);
            //templateValue|=formatedDataReceive.at(formatedDataReceive.length()-1);

           // for (unsigned i=0; i<formatedDataReceive.length()-2; ++i) {
           //     templateValue-=formatedDataReceive[i];
           // }
           // debug(DEBUG_SEND, "\n\r    -CRC==0? value: %i. ", templateValue);
           // (templateValue==0)? result=true:result=false;
        }
                debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM, "\n\r     -Send   : ");
        for (unsigned i=0; i<formatedDataSend.length(); i++) debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM, "%02X,",formatedDataSend.at(i));
        debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM,         "\n\r     -Reveive: ");
        for (unsigned i=0; i<formatedDataReceive.length(); i++) debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM, "%02X,",formatedDataReceive.at(i));
        debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM,         "\n\r     -Sneekpe: ");
        /*for (unsigned i=0; i<sneekpeek.length(); i++)*/ debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM, "%04X,",CRC16_BUYPASS(formatedDataReceive.c_str(),formatedDataReceive.size()-2));//sneekpeek.at(i));
                                                          debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM, "\n\r-Sneekpe: %04X,",CRC16_BUYPASS(formatedDataSend.c_str(),formatedDataSend.size()-2));//sneekpeek.at(i));
                                                          debug(DEBUG_SEND|DEBUG_COMPACT|DEBUG_SLIM, "\n\r-Sneekpe: %04X,",CRC16_BUYPASS(sneekpeek.c_str(),sneekpeek.size()-2));//sneekpeek.at(i));
                                                          
    }//templateValue = /*templateCRC->*/calculateCRC16(formatedDataSend.c_str(),formatedDataSend.size()-1);sneekpeek
///////////////////////
//    // old //
//
//    // data //
//    debug(DEBUG_SEND, "\n\r    -Debut data. ");
//    if(data->size() != 0) {
//        formatedDataSend.append(*data);
//        debug(DEBUG_COMPACT, "\n\r    -DATA ADDED: %02X, %02X, %02X, %02X, %02X ",formatedDataSend[0],formatedDataSend[1],formatedDataSend[2],formatedDataSend[3],formatedDataSend[4]);
//    }
//    debug(DEBUG_SEND, "\n\r    -Fin data. ");
//
//    // CRC //
//    debug(DEBUG_SEND, "\n\r    -Debut CRC16. ");
//    //CRC16* templateCRC;
//    //templateCRC = new CRC16();
//    unsigned short templateValue;
//    char templateTable[34];
//    for (unsigned i=0; i<34; ++i) templateTable[i]=0;
//    for (unsigned i=0; i<formatedDataSend.length(); ++i) templateTable[i]=formatedDataSend[i];
//    debug(DEBUG_SEND, "\n\r     - envoi au crc: %02X,%02X,%02X,%02X,%02X,%02X ",templateTable[0],templateTable[1],templateTable[2],templateTable[3],templateTable[4],templateTable[5],templateTable[6]);
//
//    templateValue = /*templateCRC->*/calculateCRC16(templateTable,formatedDataSend.size()-1); //atention pt un probleme de sortie du range
//
//    formatedDataSend.append(1,templateValue>>8);
//    formatedDataSend.append(1,templateValue & 0xFF);
//
//    // if(templateCRC)
//    //    delete templateCRC;
//    debug(DEBUG_COMPACT, "\n\r    -DATA ADDED: %02X, %02X, %02X, %02X, %02X, %02X, %02X ",formatedDataSend[0],formatedDataSend[1],formatedDataSend[2],formatedDataSend[3],formatedDataSend[4],formatedDataSend[5],formatedDataSend[6]);
//    debug(DEBUG_SEND, "\n\r    -Fin CRC16. ");
//
//    //Send Data
//    debug(DEBUG_SEND, "\n\r    -Debut Send Data. ");
//    debug(DEBUG_SEND|DEBUG_COMPACT, "\n\r     -Send: ");
//    for (unsigned i=0; i<formatedDataSend.length(); ++i) debug(DEBUG_SEND |DEBUG_COMPACT, "%02X,",formatedDataSend.at(i));
//
//    int twoBytesArray;
//   twoBytesArray = (formatedDataSend[0]<<8)|(formatedDataSend[1]);
//
//    for(int i=0; (i<3) && (!result); i++) {
//        debug(DEBUG_SEND|DEBUG_COMPACT, "\n\r      -Tentative: %d",i);
//
//        twoBytesArray=write(twoBytesArray);
//
//        if(twoBytesArray>>8 == SYNC) {// twoBytesArray ==(Sync)//+(PFB+ACK+NDB))
//            // Envoie le reste si liker si liker //
//            debug(DEBUG_SEND|DEBUG_COMPACT, "\n\r    -Debut Traitement de l'information. ");
//            debug(DEBUG_SEND|DEBUG_COMPACT, "\n\r     -Receive: %02X",twoBytesArray);
//
//            formatedDataReceive.clear();
//            formatedDataReceive.append(1,twoBytesArray>>8);
//            formatedDataReceive.append(1,twoBytesArray & 0xFF);
//
//    for (unsigned i=2; i<formatedDataSend.length(); ++i) {
//        twoBytesArray = formatedDataSend[i];
//        i++;
//        if(i<formatedDataSend.length())
//            twoBytesArray = (twoBytesArray<<8) + formatedDataSend[i];
//
//        twoBytesArray=write(twoBytesArray);
//        formatedDataReceive.append(1,twoBytesArray>>8);
//        formatedDataReceive.append(1,twoBytesArray&0xFF);
//    }
//
//    // CRC //
//    unsigned short templateValue=1;
//    templateValue=formatedDataReceive.at(formatedDataReceive.length()-2) << 8;
//    templateValue|=formatedDataReceive.at(formatedDataReceive.length()-1);
//
//    for (unsigned i=0; i<formatedDataReceive.length()-2; ++i) {
//        templateValue-=formatedDataReceive[i];
//    }
//    debug(DEBUG_SEND, "\n\r    -CRC==0? value: %i. ", templateValue);
//    (templateValue==0)? result=true:result=false;
//}
//}
//debug(DEBUG_SEND, "\n\r    -Fin Send Data. ");
//


        

    if(result) {
        // Traitement de l'information //
        debug(DEBUG_SEND, "\n\r    -Debut Traitement de l'information. ");
        debug(DEBUG_SEND, "\n\r     -Receive: ");
        for (unsigned i=0; i<formatedDataReceive.length(); ++i)debug(DEBUG_SEND|DEBUG_COMPACT, "%02X,",formatedDataReceive.at(i));

        // flag //
        flag->clear();
        if((settingSlave>>6) != 0)
        {
        //string str = formatedDataReceive.substr( ((2+(settingMaster>>6))+1+1),(settingSlave>>6)); 
        flag->append(formatedDataReceive.substr( ((2+(settingMaster>>6))+1+1),(settingSlave>>6)));// = &str;
        
        //debug(DEBUG_SLIM,         "\n\r         -flag get: ");
        //for (unsigned i=0; i<str.length(); i++) debug(DEBUG_SLIM, "%02X,",str.at(i));
        }
        //twoBytesArray=formatedDataReceive[2];
        //!!!!! wtf is that cest claire que sa pete la com
        /*string::iterator it=formatedDataReceive.begin()+3;

        switch(settingSlave>>6) {
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
                break;*/

                /*default:
                    formatedDataSend.append(1,0<<6);
                    break;*/
       // }

        // ACK/NAK
        //

        // NDB //
        data->clear();
        if((settingSlave&0x0F) != 0)
        {
        //string str = formatedDataReceive.substr( ((2+(settingMaster>>6))+1+(settingSlave>>6)+1),(settingSlave&0x0F)); 
        data->append(formatedDataReceive.substr( ((2+(settingMaster>>6))+1+(settingSlave>>6)+1),(settingSlave&0x0F)));
        
        //debug(DEBUG_SLIM,         "\n\r         -data get: ");
        //for (unsigned i=0; i<str.length(); i++) debug(DEBUG_SLIM, "%02X,",str.at(i));
        }
        //!!!!! same shit faut rebild la chose en bas
       /* switch(settingSlave&0xFF) {
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
                break;*/

                /*default:

                    break;*/
        //}
    }

    debug(DEBUG_SEND, "\n\r    -Fin Traitement de l'information. ");
    debug(DEBUG_SEND|DEBUG_COMPACT, "\n\r   -Fin du send. ");
    return result;
}