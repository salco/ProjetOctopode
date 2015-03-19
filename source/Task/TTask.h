/**
  * @file       TTask.h
  * @brief      Cette classe est le modele des 3 taches de controle.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef TTASK_H
#define TTASK_H

#include "mouvement.h"
#include "CtrlBridge.h"

class TTask
{
    private:
    int m_priorityCount;//m_countCycle;
    int m_priority;//m_cycleSet;
    //bool startSignal;
    
    protected:
    static TTask *ptrThis;
    
    public:
    TTask(int priority=0){m_priority=priority; m_priorityCount=0;}
    virtual ~TTask(){
        }
    
    virtual void exec(void){
        if(m_priorityCount >= m_priority)
        { 
            m_priorityCount=0;
            this->task();
        }
        else
         m_priorityCount++;
        }
        
    //virtual void signalStart(void);
    virtual void task(void) = 0;
    
    void setPriority(int value){m_priority = value;}
    int getPriority() { return m_priority;}
    
};
#endif // TTASK_H