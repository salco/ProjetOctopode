
#include "TTaskCritique.h"

TTaskCritique::TTaskCritique(int priority):TTask(priority)
{
   // m_userTask= new Directive();
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
}