/*
 * homemadeSequence.h
 *
 *  Created on: Mar 03, 2015
 *      Author: salco
 */

#ifndef HOMEMADESEQUENCE_H_
#define HOMEMADESEQUENCE_H_

#define DEBUG_HOMEMADE_GETFRAME 1
#define DEBUG_HOMEMADE_NEXTFRAME 0
#define DEBUG_HOMEMADE_PREVFRAME 0
#define DELAITESTE 1000

#include "debug.h"
#include "mbed.h"

class homemadeSequence
{
    //////////////////////////////
    // 00 - Nothing             //
    //X01 - Calibration(milieu) //
    //X02 - Debout              //
    //X03 - Coucher             //
    //X04 - Tourne Gauche       //
    //X05 - Tourne Droite       //
    // 06 - Marche              //
    // 07 - Recule              //
    // 08 - Repositioner        //
    // 09 - Crabe  Gauche       //
    // 10 - Crabe  Droite       //
    // 11 - recalibration legs  //
    //////////////////////////////
    char m_SequenceChosen;
    char m_idFrame;
    
    Timer delaisNextSeq;
    int delaisNeed;
    unsigned char m_posLeg[4];
    unsigned char timeSequence[8];
    char m_idLegUse; // pour seqRepositioner

    void seqUpDown(bool downUP,char idOperation,char idLeg);
    void seqTurn(bool leftRIGHT,char idOperation,char idLeg);
    void seqWalk(bool backFRONT,char idOperation,char idLeg);
    void seqRepositioner(char idOperation,char idLeg);
    void seqCrabe(bool leftRIGHT,char idOperation,char idLeg);

public:
    homemadeSequence();
    ~homemadeSequence();
    void set_Sequence(char idSequence) {
        m_SequenceChosen = idSequence;
        m_idFrame = 1;
        delaisNextSeq.reset();
        delaisNeed=-1;
    }
    char get_Sequence(void) {
        return m_SequenceChosen;
    }
    void set_leg(char idLeg){m_idLegUse = idLeg;}
   unsigned char get_Time(char idLeg){
        unsigned char result = timeSequence[idLeg-1];
        return (result==255)? DELAITESTE:result;
        }
    unsigned char* get_frame(/*char idSequence,*/char idOperation,char idLeg);
    unsigned char* get_frame(/*char idSequence,char idOperation,*/char idLeg);
    void set_frameID(char position) {m_idFrame = position;};
    bool next_frame(void); //return true if you are not at the end
    bool prev_frame(void); //return true if you are not at the begining
};
#endif /* HOMEMADESEQUENCE_H_ */