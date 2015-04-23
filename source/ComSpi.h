/**
  * @file       TTask.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef COMSPI_H
#define COMSPI_H

#define DEBUG_SEND 0
#define DEBUG_COMPACT 1
#define DEBUG_SLIM 1
#define MAXTABLE 20 

#include "mbed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "debug.h"
#include "CRC16.h"
#include "ComSpiDefine.h"
#include "OSNAPprotocoleDefine.h"



    
        

struct module_t{
    struct osnapModule_t basicInfo ;
    unsigned char flagIN ;//ici l'utilisation de unsigned char au lieu de char* nous limite a la possibiliter de lire que le 1er byte dinfo, va faloire les modifier dans le future
    unsigned char dataIN ;
    unsigned char flagOUT ;
    unsigned char dataOUT ;
    struct module_t *next;
    };



////////////////////////////////////////////////////////////    
class ComSpi : public SPI
{
    
    union{
    unsigned int getBytes;
    struct
    {
        unsigned char syncReceive  : 1;
        unsigned char addrReceive  : 1;
        unsigned char optionReceive: 1;
        unsigned char flagReceive  : 1;
        unsigned char dataReceive  : 1;
        unsigned char crcReceive   : 1;
        unsigned char finishFlag   : 1;
        unsigned char flagNeed     : 1;
    };
}flagSPI;

string sneekpeek;
    
    bool demuxIsUse;
    char m_demuxPos;
    PinName m_demuxA;
    PinName m_demuxB;
    PinName m_demuxC;
    PinName m_demuxD;
    PinName m_demuxEnable;
    
    struct module_t *chainedListFirst;  
    struct module_t *chainedListLast;
    
    //char result; // variable tempo qui emagasine le resultat, je crois que sa allege le process mais augmente la memoire
    unsigned char bufferSend[MAXTABLE],bufferReceive[MAXTABLE];
    unsigned char counterData, counterTotale;
    
 void change_demux(void);
public:
    ComSpi(PinName mosi, PinName miso, PinName sclk, PinName _unused=NC);
    ComSpi(PinName mosi, PinName miso, PinName sclk, PinName demuxA, PinName demuxB, PinName demuxC, PinName demuxD, PinName demuxEnable);
    virtual ~ComSpi();


 // renvois la position qu'il est rendu ( -1 == pas de demux ou problem)
    char next_demux(void);
    char back_demux(void);
    char get_demux(void);

    //fonction ajouter du C
    char initComSpi(void);// renvoi le premier char a metre dans le buffer SPI// ps: jaime pas trop le nom pt chercher une meilleur formulation
    struct module_t* createModule(void);
    char receiveSPI(char byte); //renvoi le prochain char a metre dans le buffer
    struct module_t* searchAddr(unsigned char addresse);
    char commIsfinish(void);
    char completeCommSend(void);
    /////

    virtual int write(int value);
    bool send(char portID,unsigned char adresseModule,string *flag,string *data);
   /* bool send(char portID, char adresseModule,char *flag,char *data);
    bool send(char portID, char adresseModule,int *flag,char *data);
    bool send(char portID, char adresseModule,char *flag,int *data);
    bool send(char portID, char adresseModule,int *flag,int *data);*/
};
#endif // COMSPI_H