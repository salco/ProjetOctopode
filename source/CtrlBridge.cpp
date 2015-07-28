
#include "CtrlBridge.h"

CtrlBridge *CtrlBridge::uniqueInstance;

/**
 * @brief Constructeur priver appler par la fonction getInstance()
 */
CtrlBridge::CtrlBridge()
    : m_Memory(), ssc32(PA_9, PA_10),
      spiLowSpeed (SPI_LOW_MOSI, SPI_LOW_MISO, SPI_LOW_SCK, SPI_LOW_DEMUXA, SPI_LOW_DEMUXB, SPI_LOW_DEMUXC, SPI_LOW_DEMUXD, SPI_LOW_CS),
      spiHighSpeed(SPI_HIGH_MOSI, SPI_HIGH_MISO, SPI_HIGH_SCK, SPI_HIGH_DEMUXA, SPI_HIGH_DEMUXB, SPI_HIGH_DEMUXC, SPI_HIGH_DEMUXD, SPI_HIGH_CS),
      pc(SERIAL_TX, SERIAL_RX)
{
    //faire en sorte d'init SPI speed ici
    m_regPortUse=0;
    m_regPortLost=0;
    spiLowSpeed.format(8,0);
    spiLowSpeed.frequency(10000/**/);
}

CtrlBridge::~CtrlBridge()
{
}

/**
 * @brief Methode permetant une seul instance de la classe
 * @return Retourne l'unique instance de la classe
 */
CtrlBridge *CtrlBridge::getInstance()
{
    if(!uniqueInstance) {
        uniqueInstance = new CtrlBridge();
    }
    return uniqueInstance;
}

bool CtrlBridge::initCom(void)
{
    //char positionInitial;
    bool portUse;
    unsigned char adresse;
    string flag;
    string data;
    Module* templateModule ;
    templateModule= new Module;

    debug(DEBUG_INITMODULE, "\n\rInit::debut");
    //flag.clear();
    //flag.append(1,Request_Init_Info);
    //positionInitial = spiLowSpeed.next_demux();
    for(char i=0; i != 15; i++) {
        debug(DEBUG_INITMODULE, "\n\r  -Debut de boucle :%d ", i);
        //flag = Request_Init_Info;
        //portUse = spiLowSpeed.send(i,0,&flag,&data);
        //if( portUse ) {
        //  m_regPortUse|=(1<< i);

        do {
             debug(DEBUG_INITMODULE," IN");
            flag = Request_Init_Info;
            adresse = m_Memory.getAdressDispo(0x80);//80 parce que cest le conecteur droit
            debug(DEBUG_INITMODULE, "\n\r    -addresse use :%d", adresse);
            data.clear();
            data.append(4,1);
            portUse = spiLowSpeed.send(i,adresse,&flag,&data);
            debug(DEBUG_INITMODULE, "\n\r    -Port use result :%d", portUse);
            
            if((flag.empty()) && (data.empty()))// data vide
                portUse=false;
            
            if( portUse ) {
                 debug(DEBUG_INITMODULE,         "\n\r         -flag get: ");
                 for (unsigned j=0; j<flag.length(); j++) debug(DEBUG_INITMODULE, "%02X,",flag.at(j));
                 debug(DEBUG_INITMODULE,         "\n\r         -data get: ");
                 for (unsigned j=0; j<data.length(); j++) debug(DEBUG_INITMODULE, "%02X,",data.at(j));
                
                
                m_regPortUse|=(1<< i);
                debug(DEBUG_INITMODULE, "\n\r      -Port use :%d", m_regPortUse);
                
                templateModule->regA = adresse;
                debug(DEBUG_INITMODULE, "\n\r      -Adrr use :%d", adresse);
                
                templateModule->regB = (spiLowSpeed.get_demux()<<4)+(data[0]&0x0F);
                templateModule->regB |=  data[0];
                debug(DEBUG_INITMODULE, "\n\r      -regB use :%02X", templateModule->regB);
                
                templateModule->regC = data[1];
                debug(DEBUG_INITMODULE, "\n\r      -regC use :%02X", templateModule->regC);
                
                templateModule->regD = data[2];
                debug(DEBUG_INITMODULE, "\n\r      -regD use :%02X", templateModule->regD);
    
                switch(templateModule->regD >>6) {
                    case 1://Capteur
                        debug(DEBUG_INITMODULE, "\n\r        -Add Capteur");
                        m_Memory.addCapteur(*templateModule);
                        break;

                    case 2://Actionneur
                        debug(DEBUG_INITMODULE, "\n\r        -Add Actionneur");
                        m_Memory.addActioneur(*templateModule);
                        break;


                    case 3://Memoire
                        debug(DEBUG_INITMODULE, "\n\r        -Add Memoire");
                        m_Memory.addMemoire(*templateModule);
                        break;

                    default:
                        break;
                }

                if(flag[0] == SLAVE_NO_MORE_EMPTY_ADDR_MODULE)
                    portUse=false;

            }
             debug(DEBUG_INITMODULE," OUT");
        } while(portUse);
        debug(DEBUG_INITMODULE, "\n\r  -Fin de boucle :%d", i);
    }

    if(templateModule)
        delete templateModule;

    debug(DEBUG_INITMODULE, "\n\rInit::Fin");
    return true;
}

bool CtrlBridge::tryComPort(char portID)
{
    if(portID <=  (char)-1)portID=0;
    if(portID > 15)portID=15;
    string flag;
    flag.clear();
    string data;
    data.clear();
    return  spiLowSpeed.send(portID,0,&flag,&data);
}

bool CtrlBridge::send( const unsigned char &adresse,string &flag, string &data)
{
    debug(DEBUF_SEND, "\n\rSend::Debut");
    bool result = false;
    Module moduleRequested;
    if(m_Memory.isAdresseValide(adresse,moduleRequested)) {

        if(adresse&0x80)
        {
            debug(DEBUF_SEND, "\n\rPointeur SPI: %d",&spiLowSpeed);
            //debug(DEBUF_SEND, "\n\rPointeur SPI: %p",spiLowSpeed);
            result = spiLowSpeed.send(moduleRequested.regB>>4,adresse,&flag,&data);
            }
        else
            result = spiHighSpeed.send(moduleRequested.regB>>4,adresse,&flag,&data);
        //result = true;
    }
    debug(DEBUF_SEND, "\n\rSend::Fin");
    return result;
}

string CtrlBridge::findModule(const char &peripheriqueID, const char &type, const char &sousType, const char &posSpatial)
{
    debug(DEBUF_FINDMODULE, "\n\rFindModule::Debut");
    string result;
    int maxSize;
    Module moduleScan;
    bool goodModule;
    
    debug(DEBUF_FINDMODULE, "\n\r  -peripheriqueID: %02X",peripheriqueID);
    debug(DEBUF_FINDMODULE, "\n\r  -type:           %02X",type);
    debug(DEBUF_FINDMODULE, "\n\r  -sousType:       %02X",sousType);
    debug(DEBUF_FINDMODULE, "\n\r  -posSpatial:     %02X",posSpatial);

    debug(DEBUF_FINDMODULE, "\n\r -Debut scan Actioneur");
    maxSize = m_Memory.getSizeActioneur();
    debug(DEBUF_FINDMODULE, "\n\r  -MaxSize: %02d",maxSize);
    goodModule = true;
    moduleScan= m_Memory.firstActioneur();

    for(int i=0; i < maxSize; i++) {
        if((peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -peripheriqueID: %02d   == moduleScan.regB>>4: %02d",peripheriqueID,moduleScan.regB>>4);
             }
        else if((type != 0) && (type != moduleScan.regD>>6)){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -type: %02d   == moduleScan.regD>>6: %02d",type,moduleScan.regD>>6);
             }
        else if((sousType != 0) && (sousType != (moduleScan.regD & 0x3F))){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -sousType: %02d   == (moduleScan.regD & 0x3F): %02d",sousType,(moduleScan.regD & 0x3F));
             }
        else if((posSpatial != 0) && (posSpatial != (moduleScan.regC & 0x3F))){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -posSpatial: %02d   == (moduleScan.regC & 0x3F): %02d",posSpatial,(moduleScan.regC & 0x3F));
             }

        if(goodModule){
            result.append(1,moduleScan.regA);
            debug(DEBUF_FINDMODULE, "\n\r  -Find one!");
            }
        if((goodModule)&&(peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)) goodModule =false;

        moduleScan= m_Memory.nextActioneur();
    }
    debug(DEBUF_FINDMODULE, "\n\r -Fin scan Actioneur");
    //debug(DEBUF_FINDMODULE, "\n\r -Result size: %0i",result.size());
    debug(DEBUF_FINDMODULE, "\n\r -Debut scan Capteur");

    maxSize = m_Memory.getSizeCapteur();
    debug(DEBUF_FINDMODULE, "\n\r  -MaxSize: %02d",maxSize);
    
    moduleScan= m_Memory.firstCapteur();

    for(int i=0; i < maxSize; i++) {
        goodModule = true;
        debug(DEBUF_FINDMODULE, "\n\r  -adresse: %02x",moduleScan.regA);
        debug(DEBUF_FINDMODULE, "\n\r  -peripheriqueID: %02d   == moduleScan.regB>>4: %02d",peripheriqueID,moduleScan.regB>>4);
        debug(DEBUF_FINDMODULE, "\n\r  -type: %02d   == moduleScan.regD>>6: %02d",type,moduleScan.regD>>6);
        debug(DEBUF_FINDMODULE, "\n\r  -sousType: %02d   == (moduleScan.regD & 0x3F): %02d",sousType,(moduleScan.regD & 0x3F));
        debug(DEBUF_FINDMODULE, "\n\r  -posSpatial: %02d   == (moduleScan.regC & 0x3F): %02d",posSpatial,(moduleScan.regC & 0x3F));
        
        if((peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -false");
             }
        else if((type != 0) && (type != moduleScan.regD>>6)){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -false");
             }
        else if((sousType != 0) && (sousType != (moduleScan.regD & 0x3F))){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -false");
             }
        else if((posSpatial != 0) && (posSpatial != (moduleScan.regC & 0x3F))){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -false");
             }

        if(goodModule){
            result.append(1,moduleScan.regA);
            debug(DEBUF_FINDMODULE, "\n\r  -Find one!");
            }
        if((goodModule)&&(peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)) goodModule =false;

        moduleScan= m_Memory.nextCapteur();
    }
    debug(DEBUF_FINDMODULE, "\n\r -Fin scan Capteur");
    //debug(DEBUF_FINDMODULE, "\n\r -Result size: %0i",result.size());
    debug(DEBUF_FINDMODULE, "\n\r -Debut scan Memoire");

    maxSize = m_Memory.getSizeMemoire();
    debug(DEBUF_FINDMODULE, "\n\r  -MaxSize: %02d",maxSize);
    goodModule = true;
    moduleScan= m_Memory.firstMemoire();

    for(int i=0; i < maxSize; i++) {
        if((peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -peripheriqueID: %02d   == moduleScan.regB>>4: %02d",peripheriqueID,moduleScan.regB>>4);
             }
        else if((type != 0) && (type != moduleScan.regD>>6)){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -type: %02d   == moduleScan.regD>>6: %02d",type,moduleScan.regD>>6);
             }
        else if((sousType != 0) && (sousType != (moduleScan.regD & 0x3F))){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -sousType: %02d   == (moduleScan.regD & 0x3F): %02d",sousType,(moduleScan.regD & 0x3F));
             }
        else if((posSpatial != 0) && (posSpatial != (moduleScan.regC & 0x3F))){
             goodModule =false;
             debug(DEBUF_FINDMODULE, "\n\r  -posSpatial: %02d   == (moduleScan.regC & 0x3F): %02d",posSpatial,(moduleScan.regC & 0x3F));
             }

        if(goodModule){
            result.append(1,moduleScan.regA);
            debug(DEBUF_FINDMODULE, "\n\r  -Find one!");
            }
        if((goodModule)&&(peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)) goodModule =false;

        moduleScan= m_Memory.nextMemoire();
    }
    debug(DEBUF_FINDMODULE, "\n\r -Fin scan Memoire");
   // debug(DEBUF_FINDMODULE, "\n\r -Result size: %0i",result.size());
    debug(DEBUF_FINDMODULE, "\n\rFindModule::Fin");
    return result;
}

int CtrlBridge::size(const char &peripheriqueID, const char &type, const char &sousType, const char &posSpatial)
{
    int result;
    string templateString;

    templateString = findModule(peripheriqueID,type,sousType,posSpatial);
    result = templateString.size()-1;//pas sure si on met -1
    return result;
}