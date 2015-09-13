
#include "TTaskGeneral.h"

TTaskGeneral::TTaskGeneral(int priority):TTask(priority)
{
    m_userTask= new Directive();
}

TTaskGeneral::~TTaskGeneral()
{
    if(m_userTask) {
        delete m_userTask;
    }
    return;
}
void TTaskGeneral::task(void)
{
    
    
    m_userTask->exec();
}