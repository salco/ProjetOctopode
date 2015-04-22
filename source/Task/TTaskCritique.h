/**
  * @file       TTaskCritiqueiquet.h
  * @brief      Cette classe controle tout ce qui ce relie au Flag Critique et a la gestion prioritaire.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef TTASKCRITIQUE_H
#define TTASKCRITIQUE_H

#include "Task/TTask.h"

class TTaskCritique : public TTask
{
    string m_ListDesModules;
    bool tymy;
    
    void forceShutDown(bool offON);
    void criticalTreatment(char adresse);
    protected:
    CtrlBridge* m_CtrlBridge;
    virtual void task(void);
    
    public:
    TTaskCritique(int priority=0);
    virtual ~TTaskCritique();
};
#endif // TTASKCRITIQUE_H