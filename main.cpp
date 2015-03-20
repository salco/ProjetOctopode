
#include "mbed.h"
//#include "mouvement.h"
#include "debug.h"
//#include "Concience/InstinctPrimaire.h"
#include "source/Task/TTaskCritique.h"
#include "source/Task/TTaskAlerte.h"
#include "source/Task/TTaskGeneral.h"


//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------



DigitalOut myled(LED1);
//char str [80];
DigitalIn mybutton(USER_BUTTON);
int main()
{
    //  int i = 1;

    //pc.printf("Hello World !\n");
    //pc.scanf ("%79s",str);
    //         string test="allo";
    //    pc.printf(test.c_str());

    TTaskCritique taskCritique(1);
   // TTaskAlerte taskAlerte(20);
   // TTaskGeneral  taskGeneral(40);
//////////
// Boot //
//////////


    while(1) {


        
        //taskAlerte.exec();
        //taskGeneral.exec();
        if (mybutton == 0) { // Button is pressed
            debug("Hello debug world");
            taskCritique.exec();

            myled = !myled;
        }
        wait(1);
    }

    /*if(taskCritt)
        delete taskCritt;
    if(taskAlert)
        delete taskAlert;
    if(taskGen)
        delete taskGen;*/
}
