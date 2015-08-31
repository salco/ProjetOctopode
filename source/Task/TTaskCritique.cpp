
#include "TTaskCritique.h"

TTaskCritique::TTaskCritique(int priority):TTask(priority)
{
    debug(DEBUG_INIT_TASKCRITT, "\n\r Debut init");
    //m_CtrlBridge = m_CtrlBridge->getInstance();
    
    
    m_CtrlBridge->initCom();
    /*#ifdef*/#ifndef DGB_FORCE_INIT
    //m_CtrlBridge->initCom();
    //#else
    do{
    //m_CtrlBridge->initCom();
    m_ListDesModules = m_CtrlBridge->findModule(0,0,0,0); //get all modules
    
        if(m_ListDesModules.size() != 11) //its a patch we need to delete it.
        {
            debug(DEBUG_INIT_TASKCRITT, "\n\r Init Fail");
            forceShutDown(false);
            wait(1);
            m_CtrlBridge->clearALL();
            forceShutDown(true);
        }
    }while(m_ListDesModules.size() != 11);
    #endif
    tymy=true;
    debug(DEBUG_INIT_TASKCRITT, "\n\r Init Reussi");
}

TTaskCritique::~TTaskCritique()
{

//    return;
}

void TTaskCritique::forceShutDown(bool offON)
{
    DigitalOut pinA(PB_8);
    DigitalOut pinB(PB_9);

    if(offON) {
        pinA=1;
        wait(1);
        pinB=0;
    } else {
        pinA=0;
        wait(1);
        pinB=1;
    }
}

void TTaskCritique::criticalTreatment(char adresse)
{
    debug("jello");
    //ici on debug et on traite le problemme//
        forceShutDown(tymy);
    tymy = !tymy;
}

void TTaskCritique::task(void)
{
    
    
    //pas sur que c'Est tout ce qui doit etre ici mais je vois pas quoi d'autre pour le moment.
    string flag,data;

    flag.append(1,0);//0x02);
    for(int i=0; i<m_ListDesModules.length(); ++i)
    {
     wait_us(300);
     flag.clear();
     flag.append(1,7);  
     data.clear(); 
    debug(DEBUG_TASKCRITT,"\n\r result: %d",m_CtrlBridge->send(m_ListDesModules.at(i),flag,data));
    if(flag[0]== 0x02)
     criticalTreatment(m_ListDesModules.at(i));
    }

}