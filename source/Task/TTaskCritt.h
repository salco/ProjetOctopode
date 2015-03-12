/**
  * @file       TTaskCritt.h
  * @brief      Cette classe controle tout ce qui ce relie au Flag Critique et a la gestion prioritaire.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef TTASKCRITT_H
#define TTASKCRITT_H

#include "Task/TTask.h"

class TTaskCritt : public TTask
{
    protected:
    virtual void task(void);
    
    public:
    TTaskCritt(int priority=0);
    virtual ~TTaskCritt();
};
#endif // TTASKCRITT_H