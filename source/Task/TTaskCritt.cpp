
#include "TTaskCritt.h"

TTaskCritt::TTaskCritt(int priority):TTask(priority)
{
   // m_userTask= new Directive();
}

TTaskCritt::~TTaskCritt()
{
   /* if(m_userTask) {
        delete m_userTask;
    }*/
    return;
}
void TTaskCritt::task(void)
{
    //m_userTask->start();
}