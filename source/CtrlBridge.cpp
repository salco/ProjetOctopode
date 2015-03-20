
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
        flag = Request_Init_Info;
        portUse = spiLowSpeed.send(i,0,&flag,&data);

        if( portUse ) {
            m_regPortUse|=(1<< i);
           
            do {
                
                templateModule->regA = m_Memory.getAdressDispo();
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

                if(flag[0] != Contien_AUTRE_MODULE)
                    portUse=false;
            } while(portUse); 
        }
        debug(DEBUG_INITMODULE, "\n\r  -Fin de boucle :%d", i);
    }

    if(templateModule)
    delete templateModule;
    
    debug(DEBUG_INITMODULE, "\n\rInit::Fin");
    return true;
}