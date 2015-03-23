/**
  * @file       TTask.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef CTRLBRIDGE_H
#define CTRLBRIDGE_H

#define DEBUG_INITMODULE 1
#define DEBUF_FINDMODULE 1

#define SPI_HIGH_MISO PB_14
#define SPI_HIGH_MOSI PB_15
#define SPI_HIGH_SCK  PB_13
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
#include <string>
#include "OSNAPprotocoleDefine.h"
//#include <algorithm>    // std::for_each
#include "debug.h"
#include "ComSpi.h" //utiliser pour comuniquer avec les module
#include "MemRegistre.h" //enregistrer les info
#include "Module.h"
class CtrlBridge
{
    static CtrlBridge *uniqueInstance;
    //pc = new Serial(SERIAL_TX, SERIAL_RX);
    //ssc32= new Serial(PA_9, PA_10);
    int m_regPortUse; // set in the init
    int m_regPortLost;// flag 1 si lost
    MemRegistre m_Memory;

    /**
    * @brief Constructeur priver appler par la fonction getInstance()
    */
    CtrlBridge();
    ~CtrlBridge();

private:
    Serial ssc32;
    ComSpi spiLowSpeed, spiHighSpeed;

public:
    Serial pc;

    bool use( const unsigned char &adresse, string &flag, string &data);

    /*string findModule(const typeModue &t);
    string findModule(const sousType_Actionneur &st);
    string findModule(const sousType_Memoire &st);
    string findModule(const sousType_Capteur &st);
    string findModule(const positionSpatial &p);
    
    string findModule(const typeModue &t, const sousType_Actionneur &st);
    string findModule(const typeModue &t, const sousType_Memoire &st);
    string findModule(const typeModue &t, const sousType_Capteur &st);
    string findModule(const typeModue &t, const positionSpatial &p);*/ //complex pour le moment on le fera en temps voulue
    
    string findModule(const char &peripheriqueID, const char &type, const char &sousType, const char &posSpatial);
    
    int size(const char &peripheriqueID, const char &type, const char &sousType, const char &posSpatial);
    /**
    * @brief Methode permetant une seul instance de la classe
    * @return Retourne l'unique instance de la classe
    */
    static CtrlBridge *getInstance();

    bool initCom(void);

    bool isValide(char portID) {
        return (m_regPortUse & (1<<portID))?true:false;
    };
    bool tryComPort(char portID);//just faire le sync et crc pour voire si lautre est la

    //fonction quelquonque pour communiquer avec les module
    //fonction quelquonque pour faire des recherche dans les module dispo
    //autre fonction pour jouer avec MemRegistre

};
#endif // CTRLBRIDGE_H