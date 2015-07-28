//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

#include "mbed.h"
//#include "OSNAPprotocoleDefine.h"
//#include "mouvement.h"
#include "debug.h"
#include "settingDebug.h"

#include "source/Task/TTaskCritique.h"
#include "source/Task/TTaskAlerte.h"
#include "source/Task/TTaskGeneral.h"

DigitalOut myled(LED1, 0);
DigitalIn mybutton(USER_BUTTON);
DigitalOut pinA(PA_13);
DigitalOut pinB(PA_14);

int main()
{
wait(3);
//////////
// Boot //
//////////

    #ifdef DBG_MAIN_INIT
    debug("\n\rInit taskCritique ...");
    #endif
     TTaskCritique taskCritique(40);
    #ifdef DBG_MAIN_INIT 
    debug(" end");
    #endif
    
    //#ifdef DBG_MAIN_INIT
    //debug("\n\rInit taskAlerte ...");
    //#endif
    // TTaskCritique taskAlerte(20);// un-use because i dont know what to do with.
    //#ifdef DBG_MAIN_INIT 
    //debug(" end");
    //#endif
    
    #ifdef DBG_MAIN_INIT
    debug("\n\rInit taskGeneral ...");
    #endif
     TTaskCritique taskGeneral(20);
    #ifdef DBG_MAIN_INIT 
    debug(" end");
    #endif

    while(1) {

        #if taskCritique
        taskCritique.exec();
        #endif
        
        #if taskAlerte
        taskAlerte.exec();
        #endif
        
        #if taskGeneral
        taskGeneral.exec();
        #endif
        
        /*if (mybutton == 0) { // Button is pressed
            debug("Hello debug world");
            wait(2);
            
            myled = !myled;
            wait(1);
        }*/

    }
    
}