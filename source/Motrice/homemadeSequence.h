/*
 * homemadeSequence.h
 *
 *  Created on: Mar 03, 2015
 *      Author: salco
 */

#ifndef HOMEMADESEQUENCE_H_
#define HOMEMADESEQUENCE_H_

#define DEBUG_HOMEMADE_GETFRAME 0
#define DEBUG_HOMEMADE_GETTIME 0
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
    // 08 - Repositioner  legs  //
    // 09 - Crabe  Gauche       // Dont use Crabe because it's really anoying
    // 10 - Crabe  Droite       // Dont use Crabe because it's really anoying
    // 11 - Position naturel    //
    //////////////////////////////
    char m_SequenceChosen;
    char m_idFrame;
    
    //Timer delaisNextSeq;//move to movement.h
    int delaisNeed;
    unsigned char m_posLeg[4];
    unsigned char timeSequence[8];
    char m_idLegUse; // pour seqRepositioner

    /*
    * Fonction contenant les sequences pour faire monter et decendre le robot
    */
    void seqUpDown(bool downUP,char idOperation,char idLeg);
     /*
    * Fonction contenant les sequences pour faire tourner le robot
    */
    void seqTurn(bool leftRIGHT,char idOperation,char idLeg);
     /*
    * Fonction contenant les sequences pour faire marcher et reculer le robot
    */
    void seqWalk(bool backFRONT,char idOperation,char idLeg);
     /*
    * Fonction contenant les sequences pour faire Repositioner le robot
    */
    void seqRepositioner(char idOperation,char idLeg);
    /*
    * Fonction contenant les sequences pour faire marcher en crabe le robot
    */
    void seqCrabe(bool leftRIGHT,char idOperation,char idLeg);
    /*
    * Fonction contenant les sequences pour positioner en default le robot
    */
    void defaultPosition(char idLeg);
    
    /*
    * Fonction remise a la valeur par defaut le Délais entre les sequences
    */
    int patchDelais(char idMode);
    
public:
/*
    * Constructeur de la class
    */
    homemadeSequence();
    /*
    * Destructeur de la class
    */
    ~homemadeSequence();
    /*
    * set_Sequence
    */
    void set_Sequence(char idSequence) {
        m_SequenceChosen = idSequence;
        m_idFrame = 1;
        
        //delaisNeed=patchDelais(idSequence);
    }
    char get_Sequence(void) {
        return m_SequenceChosen;
    }
    void set_leg(char idLeg){m_idLegUse = idLeg;}
    int get_msTime(char idLeg){
        int result = timeSequence[idLeg-1];
        
        debug(DEBUG_HOMEMADE_GETTIME,"\n\r idLeg:%i \n\r timeSequence:%i\n\r delais:%i",idLeg,result,delaisNeed);
        return (result==255)? DELAITESTE/2:result*10;
        }
    int get_delaisNeed_Ms(){return delaisNeed;}
    unsigned char* get_frame(/*char idSequence,*/char idOperation,char idLeg);
    unsigned char* get_frame(/*char idSequence,char idOperation,*/char idLeg);
    unsigned char get_frame(){return m_idFrame;}
    void set_frameID(char position) {m_idFrame = position;};
    bool next_frame(void); //return true if you are not at the end
    bool prev_frame(void); //return true if you are not at the begining
};
#endif /* HOMEMADESEQUENCE_H_ */