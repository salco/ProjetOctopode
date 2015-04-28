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
                                           
unsigned char table_seqCrabe[33][8][3] =  { { /* 0*/{  0,  0,  0}, /* 4*/{125, 184, 156}, /* 8*/{132, 215, 147}, /*12*/{  0,   0,  0},
                                             /*16*/{203,101,128}, /*20*/{  0,   0,   0}, /*24*/{176,  87, 163}, /*28*/{191, 103,133} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{111, 185, 156}, /* 8*/{  0,   0,   0}, /*12*/{  0,   0,  0},
                                             /*16*/{209, 99,140}, /*20*/{  0,   0,   0}, /*24*/{  0,   0,   0}, /*28*/{196, 105,142} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{103, 192, 155}, /* 8*/{  0,   0,   0}, /*12*/{  0,   0,  0},
                                             /*16*/{203,108,137}, /*20*/{  0,   0,   0}, /*24*/{170,  88, 159}, /*28*/{191, 112,141} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{ 98, 199, 158}, /* 8*/{  0,   0,   0}, /*12*/{  0,   0,  0},
                                             /*16*/{196,114,137}, /*20*/{  0,   0,   0}, /*24*/{  0,   0,   0}, /*28*/{184, 118,142} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{  0,   0,   0}, /* 8*/{  0,   0,   0}, /*12*/{  0,   0,  0},
                                             /*16*/{182,115,144}, /*20*/{  0,   0,   0}, /*24*/{169,  83, 164}, /*28*/{172, 118,142} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{102, 201, 170}, /* 8*/{  0,   0,   0}, /*12*/{  0,   0,  0},
                                             /*16*/{152,137,139}, /*20*/{  0,   0,   0}, /*24*/{169,  78, 155}, /*28*/{146, 137,142} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{102, 207, 179}, /* 8*/{  0,   0,   0}, /*12*/{  0,   0,  0},
                                             /*16*/{  0,  0,  0}, /*20*/{  0,   0,   0}, /*24*/{181,  76, 137}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{ 94, 213, 183}, /* 8*/{  0,   0,   0}, /*12*/{  0,   0,  0},
                                             /*16*/{  0,  0,  0}, /*20*/{  0,   0,   0}, /*24*/{181,  77, 131}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{106, 216, 175}, /* 8*/{  0,   0,   0}, /*12*/{  0,   0,  0},
                                             /*16*/{  0,  0,  0}, /*20*/{  0,   0,   0}, /*24*/{208,  75, 116}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{129, 217, 165}, /* 8*/{  0,   0,   0}, /*12*/{  0,   0,  0},
                                             /*16*/{  0,  0,  0}, /*20*/{  0,   0,   0}, /*24*/{225,  75, 109}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{129, 221, 156}, /* 8*/{  0,   0,   0}, /*12*/{  0,   0,  0},
                                             /*16*/{  0,  0,  0}, /*20*/{161, 117, 148}, /*24*/{211,  85, 120}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{153,159,157}, /* 4*/{141, 210, 152}, /* 8*/{  0,   0,   0}, /*12*/{149, 158,159},
                                             /*16*/{  0,  0,  0}, /*20*/{172,  92, 165}, /*24*/{211,  90, 127}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{121,180,156}, /* 4*/{139, 217, 134}, /* 8*/{  0,   0,   0}, /*12*/{121, 180,156},
                                             /*16*/{  0,  0,  0}, /*20*/{  0,   0,   0}, /*24*/{215,  93, 140}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{113,176,156}, /* 4*/{  0,   0,   0}, /* 8*/{  0,   0,   0}, /*12*/{107, 182,156},
                                             /*16*/{  0,  0,  0}, /*20*/{168,  94, 157}, /*24*/{209, 101, 142}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{105,183,155}, /* 4*/{  0,   0,   0}, /* 8*/{  0,   0,   0}, /*12*/{100, 187,150},
                                             /*16*/{  0,  0,  0}, /*20*/{  0,   0,   0}, /*24*/{202, 106, 142}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{100,191,158}, /* 4*/{  0,   0,   0}, /* 8*/{  0,   0,   0}, /*12*/{ 96, 193,155},
                                             /*16*/{  0,  0,  0}, /*20*/{167,  86, 166}, /*24*/{187, 109, 144}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{103,193,170}, /* 4*/{  0,   0,   0}, /* 8*/{  0,   0,   0}, /*12*/{ 99, 197,170},
                                             /*16*/{  0,  0,  0}, /*20*/{166,  87, 150}, /*24*/{154, 133, 140}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{103,200,177}, /* 4*/{  0,   0,   0}, /* 8*/{  0,   0,   0}, /*12*/{ 99, 201,177},
                                             /*16*/{  0,  0,  0}, /*20*/{177,  80, 145}, /*24*/{  0,   0,   0}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{ 96,205,182}, /* 4*/{  0,   0,   0}, /* 8*/{  0,   0,   0}, /*12*/{ 91, 208,176},
                                             /*16*/{  0,  0,  0}, /*20*/{177,  87, 130}, /*24*/{  0,   0,   0}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{108,216,171}, /* 4*/{  0,   0,   0}, /* 8*/{  0,   0,   0}, /*12*/{102, 210,173},
                                             /*16*/{  0,  0,  0}, /*20*/{192,  92, 123}, /*24*/{  0,   0,   0}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{108,216,171}, /* 4*/{  0,   0,   0}, /* 8*/{  0,   0,   0}, /*12*/{102, 210,173},
                                             /*16*/{  0,  0,  0}, /*20*/{218,  79, 120}, /*24*/{  0,   0,   0}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{129,219,151}, /* 4*/{  0,   0,   0}, /* 8*/{  0,   0,   0}, /*12*/{125, 213,157},
                                             /*16*/{162,115,150}, /*20*/{206,  93, 118}, /*24*/{  0,   0,   0}, /*28*/{154, 116,150} },
                                           { /* 0*/{140,209,142}, /* 4*/{  0,   0,   0}, /* 8*/{145, 161, 157}, /*12*/{135, 215,145},
                                             /*16*/{170, 93,167}, /*20*/{206,  97, 127}, /*24*/{  0,   0,   0}, /*28*/{163,  93,168} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{  0,   0,   0}, /* 8*/{115, 182, 158}, /*12*/{  0,   0,  0},
                                             /*16*/{  0,  0,  0}, /*20*/{212,  97, 142}, /*24*/{  0,   0,   0}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{  0,   0,   0}, /* 8*/{101, 183, 156}, /*12*/{  0,   0,  0},
                                             /*16*/{167, 93,159}, /*20*/{205, 107, 142}, /*24*/{  0,   0,   0}, /*28*/{160,  96,160} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{  0,   0,   0}, /* 8*/{ 94, 190, 154}, /*12*/{  0,   0,  0},
                                             /*16*/{  0,  0,  0}, /*20*/{197, 113, 144}, /*24*/{  0,   0,   0}, /*28*/{  0,   0,  0} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{  0,   0,   0}, /* 8*/{ 89, 197, 158}, /*12*/{  0,   0,  0},
                                             /*16*/{167, 86,167}, /*20*/{182, 115, 142}, /*24*/{  0,   0,   0}, /*28*/{161,  88,162} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{  0,   0,   0}, /* 8*/{ 92, 200, 171}, /*12*/{  0,   0,  0},
                                             /*16*/{166, 86,156}, /*20*/{153, 136, 142}, /*24*/{  0,   0,   0}, /*28*/{166,  86,156} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{  0,   0,   0}, /* 8*/{ 92, 205, 175}, /*12*/{  0,   0,  0},
                                             /*16*/{177, 82,133}, /*20*/{  0,   0,   0}, /*24*/{  0,   0,   0}, /*28*/{169,  82,143} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{  0,   0,   0}, /* 8*/{ 82, 215, 177}, /*12*/{  0,   0,  0},
                                             /*16*/{177, 85,126}, /*20*/{  0,   0,   0}, /*24*/{  0,   0,   0}, /*28*/{169,  84,135} },  
                                           { /* 0*/{  0,  0,  0}, /* 4*/{  0,   0,   0}, /* 8*/{ 96, 214, 176}, /*12*/{  0,   0,  0},
                                             /*16*/{191,101,113}, /*20*/{  0,   0,   0}, /*24*/{  0,   0,   0}, /*28*/{190,  86,124} },
                                           { /* 0*/{  0,  0,  0}, /* 4*/{  0,   0,   0}, /* 8*/{120, 213, 158}, /*12*/{  0,   0,  0},
                                             /*16*/{213, 83,124}, /*20*/{  0,   0,   0}, /*24*/{  0,   0,   0}, /*28*/{202,  88,121} },            
                                           { /* 0*/{  0,  0,  0}, /* 4*/{  0,   0,   0}, /* 8*/{120, 217, 154}, /*12*/{  0,   0,  0},
                                             /*16*/{203, 95,110}, /*20*/{  0,   0,   0}, /*24*/{165, 109, 152}, /*28*/{191, 101,120} }};                                                                                   
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