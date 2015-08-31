//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

#include "mbed.h"
//#include "OSNAPprotocoleDefine.h"
//#include "mouvement.h"
#include "debug.h"
#include "settingDebug.h"
#include "AnsiGraphicalConsole.h"

#include "source/Task/TTaskCritique.h"
#include "source/Task/TTaskAlerte.h"
#include "source/Task/TTaskGeneral.h"


//#include <fcntl.h>
//#include <io.h>
//#include <stdio.h>
//#include <iostream>


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
    // TTaskAlerte taskAlerte(20);// un-use because i dont know what to do with.
    //#ifdef DBG_MAIN_INIT 
    //debug(" end");
    //#endif
    
    #ifdef DBG_MAIN_INIT
    debug("\n\rInit taskGeneral ...");
    #endif
     TTaskGeneral taskGeneral(20);
    #ifdef DBG_MAIN_INIT 
    debug(" end");
    #endif
    
    

    while(1) {
     

        #if taskCritique
            #ifdef DBG_MAIN_FLAG
            debug("/n/r IN taskCritique");
            #endif
        
        taskCritique.exec();
        
            #ifdef DBG_MAIN_FLAG
            debug("  Out taskCritique");
            #endif
        #endif
        
        #if taskAlerte
            #ifdef DBG_MAIN_FLAG
            debug("/n/r IN taskAlerte");
            #endif
            
        taskAlerte.exec();
        
            #ifdef DBG_MAIN_FLAG
            debug("  Out taskAlerte");
            #endif        
        #endif
        
        #if taskGeneral
            #ifdef DBG_MAIN_FLAG
            debug("/n/r IN taskGeneral");
            #endif
            
        taskGeneral.exec();

            #ifdef DBG_MAIN_FLAG
            debug("  Out taskGeneral");
            #endif          
        #endif
        
        /*if (mybutton == 0) { // Button is pressed
            debug("Hello debug world");
            wait(2);
            
            myled = !myled;
            wait(1);
        }*/

    }
    
}