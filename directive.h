/**
  * @file       TTask.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef DIRECTIVE_H
#define DIRECTIVE_H

#include "mbed.h"
#include "source/Task/TTask.h"
#include "Motrice/mouvement.h"

class Directive : public TTask
{

    Faculter_motrice *ctrDesPattes;
    char c;
protected:
    virtual void task(void);

public:
    Directive();
    virtual~Directive();

};
#endif // DIRECTIVE_H