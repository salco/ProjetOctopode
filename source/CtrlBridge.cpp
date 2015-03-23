
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
            flag = Request_Init_Info;
            adresse = m_Memory.getAdressDispo(0x80);
            data.clear();
            portUse = spiLowSpeed.send(i,adresse,&flag,&data);

            if( portUse ) {
                m_regPortUse|=(1<< i);

                templateModule->regA = adresse;
                templateModule->regB = (spiLowSpeed.get_demux()<<4)+(data[0]&0x0F);
                templateModule->regC = data[1];
                templateModule->regD = data[2];

                switch(templateModule->regD >>6) {
                    case 1://Capteur
                        m_Memory.addCapteur(*templateModule);
                        break;

                    case 2://Actionneur
                        m_Memory.addActioneur(*templateModule);
                        break;


                    case 3://Memoire
                        m_Memory.addMemoire(*templateModule);
                        break;

                    default:
                        break;
                }

                if(flag[0] != CONTIEN_AUTRE_MODULE)
                    portUse=false;

            }
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

bool CtrlBridge::use( const unsigned char &adresse,string &flag, string &data)
{
    bool result = false;
    Module moduleRequested;
    if(m_Memory.isAdresseValide(adresse,moduleRequested)) {

        if(adresse&0x80)spiLowSpeed.send(moduleRequested.regB>>4,adresse,&flag,&data);
        else spiHighSpeed.send(moduleRequested.regB>>4,adresse,&flag,&data);
        result = true;
    }

    return result;
}

string CtrlBridge::findModule(const char &peripheriqueID, const char &type, const char &sousType, const char &posSpatial)
{
    debug(DEBUF_FINDMODULE, "\n\rFindModule::Debut");
    string result;
    int maxSize;
    Module moduleScan;
    bool goodModule;

    debug(DEBUF_FINDMODULE, "\n\r -Debut scan Actioneur");
    maxSize = m_Memory.getSizeActioneur();
    goodModule = true;
    moduleScan= m_Memory.firstActioneur();

    for(int i=0; i < maxSize; i++) {
        if((peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)) goodModule =false;
        else if((type != 0) && (type != moduleScan.regD>>6)) goodModule =false;
        else if((sousType != 0) && (sousType != (moduleScan.regD & 0x3F))) goodModule =false;
        else if((posSpatial != 0) && (sousType != (moduleScan.regC & 0x3F))) goodModule =false;

        if(goodModule)
            result.append(1,moduleScan.regA);
        if((goodModule)&&(peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)) goodModule =false;

        moduleScan= m_Memory.nextActioneur();
    }
    debug(DEBUF_FINDMODULE, "\n\r -Fin scan Actioneur");
    debug(DEBUF_FINDMODULE, "\n\r -Result size: %i",result.size());
    debug(DEBUF_FINDMODULE, "\n\r -Debut scan Capteur");

    maxSize = m_Memory.getSizeCapteur();
    goodModule = true;
    moduleScan= m_Memory.firstCapteur();

    for(int i=0; i < maxSize; i++) {
        if((peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)) goodModule =false;
        else if((type != 0) && (type != moduleScan.regD>>6)) goodModule =false;
        else if((sousType != 0) && (sousType != (moduleScan.regD & 0x3F))) goodModule =false;
        else if((posSpatial != 0) && (sousType != (moduleScan.regC & 0x3F))) goodModule =false;

        if(goodModule)
            result.append(1,moduleScan.regA);
        if((goodModule)&&(peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)) goodModule =false;

        moduleScan= m_Memory.nextCapteur();
    }
    debug(DEBUF_FINDMODULE, "\n\r -Fin scan Capteur");
    debug(DEBUF_FINDMODULE, "\n\r -Result size: %i",result.size());
    debug(DEBUF_FINDMODULE, "\n\r -Debut scan Memoire");

    maxSize = m_Memory.getSizeMemoire();
    goodModule = true;
    moduleScan= m_Memory.firstMemoire();

    for(int i=0; i < maxSize; i++) {
        if((peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)) goodModule =false;
        else if((type != 0) && (type != moduleScan.regD>>6)) goodModule =false;
        else if((sousType != 0) && (sousType != (moduleScan.regD & 0x3F))) goodModule =false;
        else if((posSpatial != 0) && (sousType != (moduleScan.regC & 0x3F))) goodModule =false;

        if(goodModule)
            result.append(1,moduleScan.regA);
        if((goodModule)&&(peripheriqueID != 0) && (peripheriqueID != moduleScan.regB>>4)) goodModule =false;

        moduleScan= m_Memory.nextMemoire();
    }
    debug(DEBUF_FINDMODULE, "\n\r -Fin scan Memoire");
    debug(DEBUF_FINDMODULE, "\n\r -Result size: %i",result.size());
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