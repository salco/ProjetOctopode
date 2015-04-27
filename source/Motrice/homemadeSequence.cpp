/*
 * homemadeSequence.cpp
 *
 *  Created on: Mar 03, 2015
 *      Author: salco
 */
#include "homemadeSequence.h"
unsigned char table_seqUp[9][2][3] =     { { {80 , 210, 160}, {220, 90 , 114} },
                                           { {80 , 220, 170}, {220, 80 , 130} },
                                           { {90 , 220, 160}, {200, 80 , 140} },
                                           { {106, 220, 150}, {194, 80 , 150} },
                                           { {128, 220, 127}, {172, 80 , 173} },
                                           { {144, 205, 130}, {156, 95 , 170} },
                                           { {144, 210, 123}, {156, 89 , 177} },
                                           { {172, 185, 124}, {128, 115, 176} },
                                           { {194, 166, 118}, {106, 134, 182} } };
                                           
unsigned char table_seqDown[9][2][3] =   { { {172, 185, 124}, {128, 115, 176} },
                                           { {172, 185, 124}, {128, 115, 176} },
                                           { {144, 210, 123}, {156, 89 , 177} },
                                           { {144, 205, 130}, {156, 95 , 170} },
                                           { {128, 220, 127}, {172, 80 , 173} },
                                           { {106, 220, 150}, {194, 80 , 150} },
                                           { {90 , 220, 160}, {200, 80 , 140} },
                                           { {80 , 220, 170}, {220, 80 , 130} },
                                           { {80 , 100, 150}, {220, 200, 150} } };//fin de la seq il met ses patte sur sa tete**
/*unsigned char table_seqUpDown[9][8][4] = { { {140, 80, 210, 160}, {165, 80, 210, 160}, {160, 80, 210, 160}, {150, 80, 210, 160},
                                             {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} },
                                           { {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4},
                                             {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} },
                                           { {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4},
                                             {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} },
                                           { {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4},
                                             {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} },
                                           { {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4},
                                             {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} },
                                           { {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4},
                                             {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} },
                                           { {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4},
                                             {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} },
                                           { {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4},
                                             {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} },
                                           { {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4},
                                             {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} } };*/
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
    debug(DEBUG_HOMEMADE_GETFRAME,"\n\r    In Get Frame");
    m_posLeg[0] = 0;
    m_posLeg[1] = 0;
    m_posLeg[2] = 0;
    m_posLeg[3] = 0;
    debug(DEBUG_HOMEMADE_GETFRAME,"\n\r    idLeg: %i",idLeg);
    debug(DEBUG_HOMEMADE_GETFRAME,"\n\r    m_SequenceChosen: %i",m_SequenceChosen);
    debug(DEBUG_HOMEMADE_GETFRAME,"\n\r    m_idFrame: %i",m_idFrame);
    switch(m_SequenceChosen) {
        case 1:// 01 - Calibration(milieu) //
            if(m_idFrame == 1) {//if(idOperation == 1) {
                m_posLeg[0] = 150;
                m_posLeg[1] = 150;
                m_posLeg[2] = 150;
                m_posLeg[3] = 150;
            } else {
                m_posLeg[0] = 0;
                m_posLeg[1] = 0;
                m_posLeg[2] = 0;
                m_posLeg[3] = 0;
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
    debug(DEBUG_HOMEMADE_GETFRAME,"\n\r    posLeg: [0]:%i, [1]:%i, [2]:%i, [3]:%i,",m_posLeg[0],m_posLeg[1],m_posLeg[2],m_posLeg[3]);
    debug(DEBUG_HOMEMADE_GETFRAME,"\n\r    Out Get Frame");
    return m_posLeg;
}

void homemadeSequence::seqUpDown(bool downUP,char idOperation,char idLeg)
{
    if((idOperation<10)&&(idOperation>0)) {
        switch(idLeg) { //moving hips
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
         if(downUP)
         {
            if(idLeg<5)
                for(int i=1; i <= 3; i++) m_posLeg[i]=table_seqUp[idOperation-1][0][i-1];
            else
                for(int i=1; i <= 3; i++) m_posLeg[i]=table_seqUp[idOperation-1][1][i-1];
         }
         else
         {
            if(idLeg<5)
                for(int i=1; i <= 3; i++) m_posLeg[i]=table_seqDown[idOperation-1][0][i-1];
            else
                for(int i=1; i <= 3; i++) m_posLeg[i]=table_seqDown[idOperation-1][1][i-1];
         }
        /*if(idOperation == 1) {
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
                    case 1:

                        break;
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
                default:
                    m_posLeg[0] = 0;
                    m_posLeg[1] = 0;
                    m_posLeg[2] = 0;
                    m_posLeg[3] = 0;
                    break;
            }
        }*/
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
    debug(DEBUG_HOMEMADE_NEXTFRAME,"\n\r    in Next Frame");
    bool temp=false;
    debug(DEBUG_HOMEMADE_NEXTFRAME,"\n\r    m_idframe == %d",m_idFrame);

    //if(m_idFrame > 1){
    m_idFrame++;
    unsigned char* tmpTable = get_frame(1);

    if((tmpTable[0]!=0) && (tmpTable[1]!=0) && (tmpTable[2]!=0) && (tmpTable[3]!=0)) //{
        temp=true;
    //m_idFrame++;//get_frame(m_idFrame);
    //}
    else
        m_idFrame--;

    //}
    //}
    debug(DEBUG_HOMEMADE_NEXTFRAME,"\n\r    m_idframe == %d",m_idFrame);
    debug(DEBUG_HOMEMADE_NEXTFRAME,"\n\r    out Next Frame");
    return temp;
}
bool homemadeSequence::prev_frame(void)   //true == prev is ok
{
    //false == impossible
    debug(DEBUG_HOMEMADE_PREVFRAME,"\n\r    in Prev Frame");
    bool temp=false;
    debug(DEBUG_HOMEMADE_PREVFRAME,"\n\r    m_idframe == %d",m_idFrame);

    if(m_idFrame > 1) {
        m_idFrame--;
        unsigned char* tmpTable = get_frame(1);

        if((tmpTable[0]!=0) && (tmpTable[1]!=0) && (tmpTable[2]!=0) && (tmpTable[3]!=0)) //{
            temp=true;
        //m_idFrame++;//get_frame(m_idFrame);
        //}
        else
            m_idFrame++;

        //}
    }
    debug(DEBUG_HOMEMADE_PREVFRAME,"\n\r    m_idframe == %d",m_idFrame);
    debug(DEBUG_HOMEMADE_PREVFRAME,"\n\r    out Prev Frame");
    return temp;
}