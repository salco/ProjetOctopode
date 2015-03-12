
#include "mbed.h"
//#include "mouvement.h"

//#include "Concience/InstinctPrimaire.h"
#include "Task/TTaskGen.h"
#include "Motrice/mouvement.h"
//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

Serial pc(SERIAL_TX, SERIAL_RX);
Serial ssc32(PA_9, PA_10);

DigitalOut myled(LED1);
//char str [80];
char c;
int main()
{
    //  int i = 1;

    //pc.printf("Hello World !\n");
    //pc.scanf ("%79s",str);
    //         string test="allo";
    //    pc.printf(test.c_str());

//////////
// Boot //
//////////
    c=0;
    Faculter_motrice ctrDesPattes(&/*ssc32*/pc);

    while(1) {
        wait(1);
////////////////
// Inspection //
////////////////
        if(pc.readable()) {
            c=pc.getc();//pc.scanf ("%79s",str);
            pc.printf("AK %c\n",c);//pc.printf("AK %s\n",str);// pc.printf("This program is %d .\n", i);
        }
//////////////////////////////
// Traitement du Labyrinthe //
//////////////////////////////
        if (c == 'g') {
            ctrDesPattes.calibre();
            c=0;
        }
        if(c == 'h')
        {
            pc.printf(" ID seq: %i \n\r",ctrDesPattes.get_idSeq());
            c=0;
        }
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





        myled = !myled;
    }
}
