
#include "directive.h"

Directive::Directive():TTask(0)//on veux que cette tache sois exec toute les fois que TTaskGen sexecute.
{
    c=0;
    ssc32 = new /*Serial*/RawSerial(PA_9, PA_10);
    //ctrDesPattes = new Faculter_motrice(ssc32/*pc*/);
    //m_CtrlBridge = m_CtrlBridge->getInstance();
    //a enlever de commentaire//m_ListDesModules = m_CtrlBridge->findModule(0,1,0,0);
    
     // Serial pc(USBTX, USBRX);
 
    //ssc32->set_flow_control(0);
    ssc32->putc('G');//printf("Hello World\n");
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
    string flag,data,savedData;
    DigitalOut myled(LED1);
    DigitalIn mybutton(USER_BUTTON);

    
    //wait(1);// a enlever plus tard pour gain de vitesse//
    ////////////////
// Inspection //
////////////////

    savedData.clear();

   /* for(int i=0; i<m_ListDesModules.length(); ++i) {
        flag.clear();
        data.clear();
        debug("\n\r result: %d",m_CtrlBridge->send(m_ListDesModules.at(i),flag,data));
        if(data[0]!= 0x00)
            savedData.append(data);
    }*/
    int buttonCount;
    for(buttonCount =0; mybutton == 0; buttonCount++){
        debug(DEBUG_DIRECTIVE_TEST,"\n\r %02i",buttonCount+1);
        wait(1);
        myled = 1;
        wait_ms(500);
        myled = 0;
        }
debug(DEBUG_DIRECTIVE_TEST,"\n\rResult : %02i",buttonCount);

//////////////////////////////
// Traitement du Labyrinthe //
//////////////////////////////

    switch(buttonCount){
        case 2:
            ctrDesPattes->calibre(1);
            ctrDesPattes->exec();
        break;
        
        case 6:
            ctrDesPattes->stop();
            ctrDesPattes->exec();
            ctrDesPattes->resume();
        break;
        
        case 3:
            ctrDesPattes->moveUp();
            ctrDesPattes->exec();
        break;
                
        case 4:
            ctrDesPattes->moveDown();
            ctrDesPattes->exec();
        break;  

        case 5:
            //ctrDesPattes->stop();
            //ctrDesPattes->exec();
            ctrDesPattes->resume();
        break;
        
        case 1:
            //ctrDesPattes->stop();
            ctrDesPattes->exec();
            //ctrDesPattes->resume();
        break;
        
        case 7:
            ctrDesPattes->moveLeft();
            ctrDesPattes->exec();           
        default:
        break;
        }
        
   /* if(savedData.size() != 0)
    {
          ctrDesPattes->exec();
    }*/
    /*    if (c == 'g') {
            ctrDesPattes->calibre();
            c=0;
        }
        if(c == 'h') {
            pc->printf(" ID seq: %i \n\r",ctrDesPattes->get_idSeq());
            c=0;
        }*/
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