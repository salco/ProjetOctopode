/**
  * @file       TTaskAlerte.h
  * @brief      Cette classe controle tout ce qui ce relie au Flag Critique et a la gestion prioritaire.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef TTASKALERTE_H
#define TTASKALERTE_H

#include "Task/TTask.h"

class TTaskAlerte : public TTask
{
    protected:
    virtual void task(void);
    
    public:
    TTaskAlerte(int priority=0);
    virtual ~TTaskAlerte();
};
#endif // TTASKALERTE_H