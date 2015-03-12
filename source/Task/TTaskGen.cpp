
#include "TTaskGen.h"

TTaskGen::TTaskGen(int priority):TTask(priority)
{
   // m_userTask= new Directive();
}

TTaskGen::~TTaskGen()
{
   /* if(m_userTask) {
        delete m_userTask;
    }*/
    return;
}
void TTaskGen::task(void)
{
    //m_userTask->start();
}