/**
  * @file       TTaskAlert.h
  * @brief      Cette classe controle tout ce qui ce relie au Flag Critique et a la gestion prioritaire.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef TTASKALERT_H
#define TTASKALERT_H

#include "Task/TTask.h"
class TTaskAlert : public TTask
{
    protected:
    virtual void task(void);
    
    public:
    TTaskAlert(int priority=0);
    virtual ~TTaskAlert();
};
#endif // TTASKALERT_H