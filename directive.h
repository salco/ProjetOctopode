/**
  * @file       TTask.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef DIRECTIVE_H
#define DIRECTIVE_H

#include "source/Task/TTask.h"

class Directive : public TTask
{
protected:
    virtual void task(void);

public:
    Directive();
    virtual~Directive();

};
#endif // DIRECTIVE_H