/*
 * homemadeSequence.cpp
 *
 *  Created on: Mar 03, 2015
 *      Author: salco
 */
#include "homemadeSequence.h"
homemadeSequence::homemadeSequence()
{
m_SequenceChosen=0;
m_idFrame=0;
}
homemadeSequence::~homemadeSequence()
{

}
unsigned char* homemadeSequence::get_frame(/*char idSequence,char idOperation,*/char idLeg)
{
    m_posLeg[0] = 0;
    m_posLeg[1] = 0;
    m_posLeg[2] = 0;
    m_posLeg[3] = 0;

    switch(m_SequenceChosen) {
        case 1:// 01 - Calibration(milieu) //
            if(m_idFrame == 1) {//if(idOperation == 1) {
                m_posLeg[0] = 150;
                m_posLeg[1] = 150;
                m_posLeg[2] = 150;
                m_posLeg[3] = 150;
            }
            break;

        case 2:// 02 - Debout              //
            seqUpDown(true,m_idFrame,idLeg);//seqUpDown(true,idOperation,idLeg);
            break;
        case 3:// 03 - Coucher             //
            seqUpDown(false,m_idFrame,idLeg);//seqUpDown(false,idOperation,idLeg);
            break;
        case 4:// 04 - Tourne Gauche       //
            break;
        case 5:// 05 - Tourne Droite       //
            break;
        case 6:// 06 - Marche              //
            break;
        case 7:// 07 - Recule              //
            break;
        case 8:// 07 - Repositioner        //
            break;
        case 9:// 09 - Crabe  Gauche       //
            break;
        case 10:// 10 - Crabe  Droite       //
            break;
    }
    return m_posLeg;
}

void homemadeSequence::seqUpDown(bool downUP,char idOperation,char idLeg)
{
    if((idOperation<10)&&(idOperation>0)) {
        switch(idLeg) {
            case 1:
                m_posLeg[0] = 140;
                break;
            case 2:
                m_posLeg[0] = 165;
                break;
            case 3:
                m_posLeg[0] = 160;
                break;
            case 6:
                m_posLeg[0] = 133;
                break;
            case 7:
                m_posLeg[0] = 170;
                break;
            default:
                m_posLeg[0] = 150;
                break;
        }
        if(idOperation == 1) {
            if(idLeg<5) {
                m_posLeg[1] = 80;
                m_posLeg[2] = 210;
                m_posLeg[3] = 160;
            } else {
                m_posLeg[1] = 220;
                m_posLeg[2] = 90;
                m_posLeg[3] = 114;
            }

        } else {
            if(!downUP) {
                if(idOperation == 9) {
                    if(idLeg<5) {
                        m_posLeg[1] = 80;
                        m_posLeg[2] = 100;
                        m_posLeg[3] = 150;
                    } else {
                        m_posLeg[1] = 220;
                        m_posLeg[2] = 200;
                        m_posLeg[3] = 150;
                    }
                }
                idOperation = 10 - idOperation;
            }

            switch(idOperation) {
                    /*case 1:

                        break;*/
                case 2:
                    if(idLeg<5) {
                        m_posLeg[1] = 80;
                        m_posLeg[2] = 220;
                        m_posLeg[3] = 170;
                    } else {
                        m_posLeg[1] = 220;
                        m_posLeg[2] = 80;
                        m_posLeg[3] = 130;
                    }
                    break;
                case 3:
                    if(idLeg<5) {
                        m_posLeg[1] = 90;
                        m_posLeg[2] = 220;
                        m_posLeg[3] = 160;
                    } else {
                        m_posLeg[1] = 200;
                        m_posLeg[2] = 200;
                        m_posLeg[3] = 140;
                    }
                    break;
                case 4:
                    if(idLeg<5) {
                        m_posLeg[1] = 106;
                        m_posLeg[2] = 220;
                        m_posLeg[3] = 150;
                    } else {
                        m_posLeg[1] = 195;
                        m_posLeg[2] = 80;
                        m_posLeg[3] = 150;
                    }
                    break;
                case 5:
                    if(idLeg<5) {
                        m_posLeg[1] = 128;
                        m_posLeg[2] = 220;
                        m_posLeg[3] = 128;
                    } else {
                        m_posLeg[1] = 172;
                        m_posLeg[2] = 80;
                        m_posLeg[3] = 173;
                    }
                    break;
                case 6:
                    if(idLeg<5) {
                        m_posLeg[1] = 144;
                        m_posLeg[2] = 205;
                        m_posLeg[3] = 130;
                    } else {
                        m_posLeg[1] = 156;
                        m_posLeg[2] = 95;
                        m_posLeg[3] = 170;
                    }
                    break;
                case 7:
                    if(idLeg<5) {
                        m_posLeg[1] = 144;
                        m_posLeg[2] = 211;
                        m_posLeg[3] = 123;
                    } else {
                        m_posLeg[1] = 156;
                        m_posLeg[2] = 89;
                        m_posLeg[3] = 177;
                    }
                    break;
                case 8:
                    if(idLeg<5) {
                        m_posLeg[1] = 172;
                        m_posLeg[2] = 185;
                        m_posLeg[3] = 124;
                    } else {
                        m_posLeg[1] = 128;
                        m_posLeg[2] = 115;
                        m_posLeg[3] = 176;
                    }
                    break;
                case 9:
                    if(idLeg<5) {
                        m_posLeg[1] = 194;
                        m_posLeg[2] = 166;
                        m_posLeg[3] = 118;
                    } else {
                        m_posLeg[1] = 106;
                        m_posLeg[2] = 134;
                        m_posLeg[3] = 182;
                    }
                    break;
            }
        }
    }
}
void homemadeSequence::seqTurn(bool leftRIGHT,char idOperation,char idLeg)
{}
void homemadeSequence::seqWalk(bool backFRONT,char idOperation,char idLeg)
{}
void homemadeSequence::seqRepositioner(char idOperation,char idLeg)
{}
void homemadeSequence::seqCrabe(bool leftRIGHT,char idOperation,char idLeg)
{}
bool homemadeSequence::next_frame(void)
{
    bool temp=true;
    m_idFrame++;
    unsigned char* tmpTable = get_frame(m_idFrame+1);
    
    if((tmpTable[0]==0) && (tmpTable[1]==0) && (tmpTable[2]==0) && (tmpTable[3]==0)) {
        temp=false;
        m_idFrame--;//get_frame(m_idFrame);
    }/* else
        m_idFrame++;*/

    return temp;
}
bool homemadeSequence::prev_frame(void)
{
    bool temp=true;
    m_idFrame--;
    unsigned char* tmpTable = get_frame(1);
    
    if((tmpTable[0]==0) && (tmpTable[1]==0) && (tmpTable[2]==0) && (tmpTable[3]==0)) {
        temp=false;
        m_idFrame++;//get_frame(m_idFrame);
    } /*else
        m_idFrame--;*/

    return temp;
}