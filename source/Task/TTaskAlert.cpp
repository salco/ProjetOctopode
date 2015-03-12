
#include "TTaskAlert.h"

TTaskAlert::TTaskAlert(int priority):TTask(priority)
{
   // m_userTask= new Directive();
}

TTaskAlert::~TTaskAlert()
{
   /* if(m_userTask) {
        delete m_userTask;
    }*/
    return;
}
void TTaskAlert::task(void)
{
    //m_userTask->start();
}