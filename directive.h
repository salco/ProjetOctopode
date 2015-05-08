/**
  * @file       TTask.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef DIRECTIVE_H
#define DIRECTIVE_H

#define DEBUG_DIRECTIVE_TEST 1

#include "mbed.h"
#include "debug.h"
#include "source/Task/TTask.h"
#include "Motrice/mouvement.h"

class Directive : public TTask
{
    CtrlBridge* m_CtrlBridge;
    Faculter_motrice *ctrDesPattes;
    /*Serial*/RawSerial *ssc32;
    char c;
protected:
    virtual void task(void);

public:
    Directive();
    virtual~Directive();

};
#endif // DIRECTIVE_H