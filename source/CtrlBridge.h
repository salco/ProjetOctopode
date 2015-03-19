/**
  * @file       TTask.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef CTRLBRIDGE_H
#define CTRLBRIDGE_H

#include "ComSpi.h" //utiliser pour comuniquer avec les module
#include "MemRegistre.h" //enregistrer les info

class CtrlBridge
{
    int m_regPortUse; // set in the init
    int m_regPortLost;// flag 1 si lost

    bool initCom(void);

    bool isValide(char portID);
    bool tryComPort(char portID);//just faire le sync et crc pour voire si lautre est la
};
#endif // CTRLBRIDGE_H