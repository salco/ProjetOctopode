
#include "directive.h"

Directive::Directive():TTask(0)//on veux que cette tache sois exec toute les fois que TTaskGen sexecute.
{
    c=0;
    ssc32 = new /*Serial*//*Raw*/Serial/*(USBTX, USBRX);*/(PB_6, PB_7);//(PA_9, PA_10);
    ctrDesPattes = new Faculter_motrice(ssc32/*pc*/);
    //m_CtrlBridge = m_CtrlBridge->getInstance();
    //a enlever de commentaire//m_ListDesModules = m_CtrlBridge->findModule(0,1,0,0);

    //Serial pc(USBTX, USBRX);

    //ssc32->set_flow_control(0);
    debug("\n\r directive Init");//printf("Hello World\n");
    m_ListDesModules = m_CtrlBridge->findModule(0,CAPTEUR,DISTANCE,0);
    m_ListDesModules.append(m_CtrlBridge->findModule(0,CAPTEUR,PROXIMITEE,0));
    
    m_capteurUltrasonic= m_CtrlBridge->findModule(0,CAPTEUR,ULTRASONIQUE,0x27/*0b100111*/);
    m_capteurIR= m_CtrlBridge->findModule(0,CAPTEUR,DISTANCE,0x27/*0b100111*/);
    m_capteurProximiter= m_CtrlBridge->findModule(0,CAPTEUR,PROXIMITEE,0x0E/*0b001110*/);
}
Directive::~Directive()
{

    if(ctrDesPattes)
        delete ctrDesPattes;
    if(ssc32)
        delete ssc32;
}
void Directive::task(void)//ALL CODE HERE//
{
    debug(DEBUG_DIRECTIVE_TEST,"\n\rIn task directive");
    //pas sur que c'Est tout ce qui doit etre ici mais je vois pas quoi d'autre pour le moment.
    string flag,data;

    ////////////////
    // Inspection //
    ////////////////
    flag.append(1,0);//0x02);
    for(int i=0; i<m_ListDesModules.length(); ++i)
    {
     wait_us(300);
     flag.clear();
     flag.append(1,7);  
     data.clear(); 
    debug("\n\r result: %d",m_CtrlBridge->send(m_ListDesModules.at(i),flag,data));
    
    debug("\n\r flag: %d",flag[0]);
    debug("\n\r data: %x",data[0]);
    
    }
    //////////////////////////////
    // Traitement du Labyrinthe //
    //////////////////////////////
    
    ///////////////
// Mouvement //
///////////////
    //  ctrDesPattes.exec();
////////////////////
// Update memoire //
////////////////////

////////////
// Autre? //
////////////
    debug(DEBUG_DIRECTIVE_TEST,"\n\rOut task directive");
}