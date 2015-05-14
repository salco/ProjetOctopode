/*
 * mouvement.h
 *
 *  Created on: Mar 02, 2015
 *      Author: salco
 */

/*
 * Theraphosa Salconi
 *
 * Jambes[coxa/fermur/tibia/tars]+numeroMoteur:
 *
 * Arr-D: [0,1,2,3]
 * Arr-G: [16,17,18,19]
 * Arr-Mil-D: [4,5,6,7]
 * Arr-Mil-G: [20,21,22,23]
 * Avv-Mil-D: [8,9,10,11]
 * Avv-Mil-G: [24,25,26,27]
 * Avv-D: [12,13,14,15]
 * Avv-G: [28,29,30,31]
 *
 */
#ifndef MOUVEMENT_H_
#define MOUVEMENT_H_


#define DEBUG_MOUVEMENT 0/*1*/
#define DEBUG_EXEC 0/*1*/
#define DEBUG_SENDSEQ 0/*1*/

#include "mbed.h"
//#include <string>
#include "debug.h"
//#include <stdio.h>
#include "Patte.h"
#include "homemadeSequence.h"


class Faculter_motrice
{
    Serial* m_com;
    homemadeSequence* m_seq;
    Timer delaisNextSeq;

    Patte *m_arr_D;
    char m_SequenceID_arr_D;
    Patte *m_arr_mil_D;
    char m_SequenceID_arr_mil_D;
    Patte *m_arr_G;
    char m_SequenceID_arr_G;
    Patte *m_arr_mil_G;
    char m_SequenceID_arr_mil_G;
    Patte *m_avv_D;
    char m_SequenceID_avv_D;
    Patte *m_avv_mil_D;
    char m_SequenceID_avv_mil_D;
    Patte *m_avv_G;
    char m_SequenceID_avv_G;
    Patte *m_avv_mil_G;
    char m_SequenceID_avv_mil_G;
    
// Flag //
    bool m_ForceStop; // use when you want pause the motion
    bool m_CriticalStop; // use to turn off all legs
    bool m_SeqChange;

//  //
// char m_SequenceChosen;
// A enlever au plus vite car sa prend beaucoup d'espace //

   void sendSequence(void);
public:
#ifdef DEBUG
    char get_idSeq(void){return m_seq->get_Sequence();}
#endif
    Faculter_motrice(Serial* com);
    virtual ~Faculter_motrice();
    
    bool isSeqComplet(void){return m_ForceStop;}
    void exec(void);
    void stop(void) {
        m_ForceStop= true;
    }
    void resume(void) {
        m_ForceStop=false;
        m_CriticalStop=false;
        delaisNextSeq.start();
    }
    void crit_stop(void);
    
    void moveLeft (void) {
        m_ForceStop=false;
        m_seq->set_Sequence(9);
        delaisNextSeq.start();
    }
    void moveRight(void){
        m_ForceStop=false;
        m_seq->set_Sequence(10);
        delaisNextSeq.start();
    }
    void moveUp   (void){
        m_ForceStop=false;
        m_seq->set_Sequence(2);
        delaisNextSeq.start();
    }
    void moveDown (void){
        m_ForceStop=false;
        m_seq->set_Sequence(3);
        delaisNextSeq.start();
    }
    void moveFront(void){
        m_ForceStop=false;
        m_seq->set_Sequence(6);
        delaisNextSeq.start();
    }
    void moveBack (void){
        m_ForceStop=false;
        m_seq->set_Sequence(7);
        delaisNextSeq.start();
    }
    void turnLeft (void){
        m_ForceStop=false;
        m_seq->set_Sequence(4);
        delaisNextSeq.start();
    }
    void trunRight(void){
        m_ForceStop=false;
        m_seq->set_Sequence(5);
        delaisNextSeq.start();
    }
    void calibre  (){
        m_ForceStop=false;
        m_seq->set_Sequence(11);
        delaisNextSeq.start();
    }
    void repositioner(char idLeg){
        m_ForceStop=false;
        m_seq->set_leg(idLeg);
        m_seq->set_Sequence(8);
        delaisNextSeq.start();
    }



};
extern Faculter_motrice *ptrFaculterMotrice;
#endif /* MOUVEMENT_H_ */