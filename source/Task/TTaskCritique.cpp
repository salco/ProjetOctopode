
#include "TTaskCritique.h"

TTaskCritique::TTaskCritique(int priority):TTask(priority)
{
   // m_userTask= new Directive();
   m_CtrlBridge = m_CtrlBridge->getInstance();
   //mybutton(USER_BUTTON);
}

TTaskCritique::~TTaskCritique()
{
   /* if(m_userTask) {
        delete m_userTask;
    }*/
    return;
}
void TTaskCritique::task(void)
{
    //m_userTask->start();

        m_CtrlBridge->pc.printf("\n\r Press any key to continue.\n\r");
        m_CtrlBridge->pc.getc();
        m_CtrlBridge->initCom();
        
}