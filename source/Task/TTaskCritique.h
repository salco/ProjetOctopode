/**
  * @file       TTaskCritique.h
  * @brief      Cette classe controle tout ce qui ce relie au Flag Critique et a la gestion prioritaire.
  * @author     Salco
  * @version    2.00
  * @date       11 mars 2015
  */
#ifndef TTASKCRITIQUE_H
#define TTASKCRITIQUE_H

#include "Task/TTask.h"
#include "debug.h"
#include "settingDebug.h"

class TTaskCritique : public TTask
{
    //string m_ListDesModules;
    bool tymy;
    /*
    * Fonction permetant de fermer et ouvrire l'alimentation du robot
    */
    void forceShutDown(bool offON);
    void criticalTreatment(char adresse);
    //protected:
    //CtrlBridge* m_CtrlBridge;
    virtual void task(void);
    
    public:
    /*
    * Constructeur de la class
    */
    TTaskCritique(int priority=0);
    /*
    * Destructeur de la class
    */
    virtual ~TTaskCritique();
};
#endif // TTASKCRITIQUE_H