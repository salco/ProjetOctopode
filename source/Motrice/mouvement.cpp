/*
 * mouvement.cpp
 *
 *  Created on: Mar 02, 2015
 *      Author: salco
 */
#include "mouvement.h"

Faculter_motrice *ptrFaculterMotrice;

Faculter_motrice::Faculter_motrice(Serial* com):m_com(com)
{
    m_seq = new homemadeSequence();

    m_arr_D     = new Patte(1,0,1,2,3);
    m_arr_mil_D = new Patte(2,4,5,6,7);
    m_arr_G     = new Patte(3,16,17,18,19);
    m_arr_mil_G = new Patte(4,20,21,22,23);
    m_avv_D     = new Patte(5,12,13,14,15);
    m_avv_mil_D = new Patte(6,8,9,10,11);
    m_avv_G     = new Patte(7,28,29,30,31);
    m_avv_mil_G = new Patte(8,24,25,26,27);

    m_SequenceID_arr_D     =0;
    m_SequenceID_arr_mil_D =0;
    m_SequenceID_arr_G     =0;
    m_SequenceID_arr_mil_G =0;
    m_SequenceID_avv_D     =0;
    m_SequenceID_avv_mil_D =0;
    m_SequenceID_avv_G     =0;
    m_SequenceID_avv_mil_G =0;

    m_ForceStop    = false;
    m_CriticalStop = false;
}
Faculter_motrice::~Faculter_motrice()
{
    if(m_seq)
        delete m_seq;
    if (m_arr_D)
        delete m_arr_D;
    if (m_arr_mil_D)
        delete m_arr_mil_D;
    if (m_arr_G)
        delete m_arr_G;
    if (m_arr_mil_G)
        delete m_arr_mil_G;

    if (m_avv_D)
        delete m_avv_D;
    if (m_avv_mil_D)
        delete m_avv_mil_D;
    if (m_avv_G)
        delete m_avv_G;
    if (m_avv_mil_G)
        delete m_avv_mil_G;
    return;
}
void Faculter_motrice::exec(void)
{
#ifdef DEBUG
    m_com->printf("Flag in exec [%i  :: %i ] \n\r",m_ForceStop,m_seq->get_Sequence());
#endif
    if((!m_ForceStop)&&(m_seq->get_Sequence() != 0)) {
        unsigned char* tempLeg;



        switch(m_seq->get_Sequence()) {
            case 1:
                tempLeg=m_seq->get_frame(m_arr_D->id());
                m_arr_D->move(tempLeg[0],tempLeg[1],tempLeg[2],tempLeg[3]);
                //...//
                if(m_seq->next_frame() == false) {
                    m_ForceStop=true;
#ifdef DEBUG
                    m_com->printf("    Flag next impossible \n\r",m_ForceStop,m_seq->get_Sequence());
#endif
                }
                #ifdef DEBUG
                else
                    m_com->printf("    Flag next possible \n\r",m_ForceStop,m_seq->get_Sequence());
#endif
                break;
        }
        //char buffer[50];
        //scanf(buffer,"%s T%d\n\r",m_arr_D->toString(),DELAITESTE);
        m_com->printf("%s T%d\n\r",m_arr_D->toString(),DELAITESTE);

        /*
                    tempLeg=m_seq->get_frame(m_arr_D->id());
        m_com->printf("This program is %d .\n", tempLeg[0]);*/
    }
#ifdef DEBUG
    m_com->printf("Flag out exec [%i  :: %i ] \n\r",m_ForceStop,m_seq->get_Sequence());
#endif
}
/*void Faculter_motrice::moveLeft (void)
{
    m_seq->set_Sequence(9);
}
void Faculter_motrice::moveRight(void)
{

}
void Faculter_motrice::moveUp   (void)
{

}
void Faculter_motrice::moveDown (void)
{

}
void Faculter_motrice::moveFront(void)
{

}
void Faculter_motrice::moveBack (void)
{

}
void Faculter_motrice::turnLeft (void)
{

}
void Faculter_motrice::trunRight(void)
{

}*/
void Faculter_motrice::crit_stop(void)
{
    m_com->printf("#0L #1L #2L #3L #4L #5L #6L #7L #8L #9L #10L #11L #12L #13L #14L #15L #16L #17L #18L #19L #20L #21L #22L #23L #24L #25L #26L #27L #28L #29L #30L #31L #32L\n\r");
    m_ForceStop=true;
    m_CriticalStop=true;
}