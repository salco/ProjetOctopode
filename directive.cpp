
#include "directive.h"

Directive::Directive():TTask(0)//on veux que cette tache sois exec toute les fois que TTaskGen sexecute.
{
    c=0;
    pc = new Serial(SERIAL_TX, SERIAL_RX);
    ssc32= new Serial(PA_9, PA_10);

    ctrDesPattes = new Faculter_motrice(/*ssc32*/pc);
}
Directive::~Directive()
{
    if(pc)
        delete pc;
    if(ssc32)
        delete ssc32;
    if(ctrDesPattes)
        delete ctrDesPattes;
}
void Directive::task(void)//ALL CODE HERE//
{

   wait(1);// a enlever plus tard pour gain de vitesse//
    ////////////////
// Inspection //
////////////////

    if(pc->readable()) {
        c=pc->getc();//pc.scanf ("%79s",str);
        pc->printf("AK %c\n",c);//pc.printf("AK %s\n",str);// pc.printf("This program is %d .\n", i);
    }

//////////////////////////////
// Traitement du Labyrinthe //
//////////////////////////////
    if (c == 'g') {
        ctrDesPattes->calibre();
        c=0;
    }
    if(c == 'h') {
        pc->printf(" ID seq: %i \n\r",ctrDesPattes->get_idSeq());
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



}