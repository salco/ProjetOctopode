/*
 * homemadeSequence.h
 *
 *  Created on: Mar 03, 2015
 *      Author: salco
 */

#ifndef HOMEMADESEQUENCE_H_
#define HOMEMADESEQUENCE_H_
class homemadeSequence
{
    //////////////////////////////
    // 00 - Nothing             //
    // 01 - Calibration(milieu) //
    // 02 - Debout              //
    // 03 - Coucher             //
    // 04 - Tourne Gauche       //
    // 05 - Tourne Droite       //
    // 06 - Marche              //
    // 07 - Recule              //
    // 08 - Repositioner        //
    // 09 - Crabe  Gauche       //
    // 10 - Crabe  Droite       //
    //////////////////////////////
    char m_SequenceChosen;
    char m_idFrame;

    unsigned char m_posLeg[4];

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
    }
    char get_Sequence(void) {
        return m_SequenceChosen;
    }
    unsigned char* get_frame(/*char idSequence,*/char idOperation,char idLeg);
    unsigned char* get_frame(/*char idSequence,char idOperation,*/char idLeg);
    bool next_frame(void); //return true if you are not at the end
    bool prev_frame(void); //return true if you are not at the begining
};
#endif /* HOMEMADESEQUENCE_H_ */