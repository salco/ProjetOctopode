/**
  * @file       TTaskGeneral.h
  * @brief      Cette classe controle tout ce qui ce relie au Flag Critique et a la gestion prioritaire.
  * @author     Salco
  * @version    2.00
  * @date       11 june 2015
  */
#ifndef TTASKGENERAL_H
#define TTASKGENERAL_H

#include "Task/TTask.h"
#include "settingDebug.h"
#include "././directive.h"

class TTaskGeneral : public TTask
{
     Directive * m_userTask;

protected:
    virtual void task(void);

public:
    TTaskGeneral(int priority=0);
    virtual ~TTaskGeneral();
};

#endif // TTASKGENERAL_H