
#include "CtrlBridge.h"

CtrlBridge *CtrlBridge::uniqueInstance;

/**
 * @brief Constructeur priver appler par la fonction getInstance()
 */
CtrlBridge::CtrlBridge() 
: pc(SERIAL_TX, SERIAL_RX), ssc32(PA_9, PA_10),
spiLowSpeed (SPI_LOW_MOSI, SPI_LOW_MISO, SPI_LOW_SCK, SPI_LOW_DEMUXA, SPI_LOW_DEMUXB, SPI_LOW_DEMUXC, SPI_LOW_DEMUXD, SPI_LOW_CS),
spiHighSpeed(SPI_HIGH_MOSI, SPI_HIGH_MISO, SPI_HIGH_SCK, SPI_HIGH_DEMUXA, SPI_HIGH_DEMUXB, SPI_HIGH_DEMUXC, SPI_HIGH_DEMUXD, SPI_HIGH_CS)
{
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
    if(!uniqueInstance){
        uniqueInstance = new CtrlBridge();
    }
    return uniqueInstance;
}

bool CtrlBridge::initCom(void)
{
    
    return true;
    }