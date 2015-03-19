
#include "mbed.h"
//#include "mouvement.h"

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

int main()
{
    //  int i = 1;

    //pc.printf("Hello World !\n");
    //pc.scanf ("%79s",str);
    //         string test="allo";
    //    pc.printf(test.c_str());

    TTaskCritique taskCritique(10);
    TTaskAlerte taskAlerte(20);
    TTaskGeneral  taskGeneral(40);
//////////
// Boot //
//////////


    while(1) {
        

        taskCritique.exec();
        taskAlerte.exec();
        taskGeneral.exec();




        myled = !myled;
    }
    
    /*if(taskCritt)
        delete taskCritt;
    if(taskAlert)
        delete taskAlert;
    if(taskGen)
        delete taskGen;*/
}
