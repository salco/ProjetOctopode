/**
  * @file       TTaskGen.h
  * @brief      Cette classe controle tout ce qui ce relie au Flag Critique et a la gestion prioritaire.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef TTASKGEN_H
#define TTASKGEN_H

#include "Task/TTask.h"
#include "././directive.h"

class TTaskGen : public TTask
{
    // Directive * m_userTask;

protected:
    virtual void task(void);

public:
    TTaskGen(int priority=0);
    virtual ~TTaskGen();
};

#endif // TTASKGEN_H