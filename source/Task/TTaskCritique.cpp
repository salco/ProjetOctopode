
#include "TTaskCritique.h"

TTaskCritique::TTaskCritique(int priority):TTask(priority)
{
    //m_CtrlBridge = m_CtrlBridge->getInstance();

    m_CtrlBridge->initCom();
    m_ListDesModules = m_CtrlBridge->findModule(0,0,0,0); //get all modules

    tymy=true;
}

TTaskCritique::~TTaskCritique()
{

//    return;
}

void TTaskCritique::forceShutDown(bool offON)
{
    DigitalOut pinA(PA_13);
    DigitalOut pinB(PA_14);

    if(offON) {
        pinA=1;
        pinB=0;
    } else {
        pinA=0;
        pinB=1;
    }
}

void TTaskCritique::criticalTreatment(char adresse)
{
    //ici on debug et on traite le problemme//
        forceShutDown(tymy);
    tymy = !tymy;
}

void TTaskCritique::task(void)
{
    debug("\n\rPeanut");
    //pas sur que c'Est tout ce qui doit etre ici mais je vois pas quoi d'autre pour le moment.
    string flag,data;

    flag.append(1,0);//0x02);
    for(int i=0; i<m_ListDesModules.length(); ++i)
    {
     flag.clear();
     flag.append(1,6);  
     data.clear(); 
    debug("\n\r result: %d",m_CtrlBridge->send(m_ListDesModules.at(i),flag,data));
    if(flag[0]== 0x02)
     criticalTreatment(m_ListDesModules.at(i));
    }

}