
#include "TTaskAlerte.h"

TTaskAlerte::TTaskAlerte(int priority):TTask(priority)
{
   // m_userTask= new Directive();
}

TTaskAlerte::~TTaskAlerte()
{
   /* if(m_userTask) {
        delete m_userTask;
    }*/
    return;
}
void TTaskAlerte::task(void)
{
    //m_userTask->start();
}