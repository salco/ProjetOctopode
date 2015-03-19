/**
  * @file       TTask.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef CTRLBRIDGE_H
#define CTRLBRIDGE_H

#define SPI_HIGH_MISO PB_14
#define SPI_HIGH_MOSI PB_15
#define SPI_HIGH_SCK  PB_14
#define SPI_HIGH_CS PC_15
#define SPI_HIGH_DEMUXA PC_0
#define SPI_HIGH_DEMUXB PC_1
#define SPI_HIGH_DEMUXC PC_2
#define SPI_HIGH_DEMUXD PC_3

#define SPI_LOW_MISO PA_6
#define SPI_LOW_MOSI PA_7
#define SPI_LOW_SCK PA_5
#define SPI_LOW_CS PC_14
#define SPI_LOW_DEMUXA PC_4
#define SPI_LOW_DEMUXB PC_5
#define SPI_LOW_DEMUXC PC_6
#define SPI_LOW_DEMUXD PC_7

#include "mbed.h"
#include "ComSpi.h" //utiliser pour comuniquer avec les module
#include "MemRegistre.h" //enregistrer les info

class CtrlBridge
{
    static CtrlBridge *uniqueInstance;
    //pc = new Serial(SERIAL_TX, SERIAL_RX);
    //ssc32= new Serial(PA_9, PA_10);
    int m_regPortUse; // set in the init
    int m_regPortLost;// flag 1 si lost

    bool initCom(void);

    bool isValide(char portID);
    bool tryComPort(char portID);//just faire le sync et crc pour voire si lautre est la
    /**
    * @brief Constructeur priver appler par la fonction getInstance()
    */
    CtrlBridge();
    ~CtrlBridge();
private:
Serial pc;
Serial ssc32;
public:
    /**
    * @brief Methode permetant une seul instance de la classe
    * @return Retourne l'unique instance de la classe
    */
    static CtrlBridge *getInstance();
    ComSpi spiLowSpeed, spiHighSpeed;   
 
};
#endif // CTRLBRIDGE_H