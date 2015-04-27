/*
 * Patte.h
 *
 *  Created on: Mar 03, 2015
 *      Author: salco
 */
#ifndef PATTE_H_
#define PATTE_H_

#define NBR_SERVO 32
#define DEFAULTPOSITION 150
#define DEFAULTMAX 225
#define DEFAULTMIN 75

//#include <string>
#include <stdio.h>

struct servo_t {
    char iD; //use for ssc-32
    // all value down is a pulse value between 750-2250 //
    unsigned char basePose;
    unsigned char max;
    unsigned char min;
    // mabey change curr for a integer to get more precision and less space //
    unsigned char curr;
};

class Patte
{
    // number related to the SSC-32 //
    /*char m_numServo_Coxa;
    char m_numServo_Femur;
    char m_numServo_Tibia;
    char m_numServo_Tars;*/
    char m_id;
    servo_t m_Coxa;
    servo_t m_Femur;
    servo_t m_Tibia;
    servo_t m_Tars;
    char buffer [50];
    
public:
    Patte(char patteId,char coxaId,char femurId,char tibiaId,char tarsId) {
        m_id = patteId;

        m_Coxa.iD  = coxaId;
        m_Coxa.max = DEFAULTMAX;
        m_Coxa.min = DEFAULTMIN;
        m_Coxa.curr= DEFAULTPOSITION;

        m_Femur.iD  = femurId;
        m_Femur.max = DEFAULTMAX;
        m_Femur.min = DEFAULTMIN;
        m_Femur.curr= DEFAULTPOSITION;

        m_Tibia.iD  = tibiaId;
        m_Tibia.max = DEFAULTMAX;
        m_Tibia.min = DEFAULTMIN;
        m_Tibia.curr= DEFAULTPOSITION;

        m_Tars.iD  = tarsId;
        m_Tars.max = DEFAULTMAX;
        m_Tars.min = DEFAULTMIN;
        m_Tars.curr= DEFAULTPOSITION;
    }
    virtual ~Patte(){}
    char id(void) {
        return m_id;
    }
    const char* toString(void){
       
       sprintf (buffer,"#%d P%d0 #%d P%d0 #%d P%d0 #%d P%d0",m_Coxa.iD,m_Coxa.curr,m_Femur.iD,m_Femur.curr,m_Tibia.iD,m_Tibia.curr,m_Tars.iD,m_Tars.curr);
       return buffer;
        }
    //setting Coxa //
    void set_Id_Coxa(char id) {
        m_Coxa.iD = id;
    }
    void set_PulseMax_Coxa(unsigned char value) {
        m_Coxa.max = value;
    }
    void set_PulseMin_Coxa(unsigned char value) {
        m_Coxa.min = value;
    }
    void set_DefaultPulse_Coxa(unsigned char value) {
        m_Coxa.basePose = value;
    }
    char get_Id_Coxa(void) {
        return m_Coxa.iD;
    }
    unsigned char get_PulseMax_Coxa(void) {
        return m_Coxa.max;
    }
    unsigned char get_PulseMin_Coxa(void) {
        return m_Coxa.min;
    }
    unsigned char get_DefaultPulse_Coxa(void) {
        return m_Coxa.basePose;
    }
    unsigned char get_CurrentPulse_Coxa(void) {
        return m_Coxa.curr;
    }
    //setting Femur //
    void set_Id_Femur(char id) {
        m_Femur.iD = id;
    }
    void set_PulseMax_Femur(unsigned char value) {
        m_Femur.max = value;
    }
    void set_PulseMin_Femur(unsigned char value) {
        m_Femur.min = value;
    }
    void set_DefaultPulse_Femur(unsigned char value) {
        m_Femur.basePose = value;
    }
    char get_Id_Femur(void) {
        return m_Femur.iD;
    }
    unsigned char get_PulseMax_Femur(void) {
        return m_Femur.max;
    }
    unsigned char get_PulseMin_Femur(void) {
        return m_Femur.min;
    }
    unsigned char get_DefaultPulse_Femur(void) {
        return m_Femur.basePose;
    }
    unsigned char get_CurrentPulse_Femur(void) {
        return m_Femur.curr;
    }
    //setting Tibia //
    void set_Id_Tibia(char id) {
        m_Tibia.iD = id;
    }
    void set_PulseMax_Tibia(unsigned char value) {
        m_Tibia.max = value;
    }
    void set_PulseMin_Tibia(unsigned char value) {
        m_Tibia.min = value;
    }
    void set_DefaultPulse_Tibia(unsigned char value) {
        m_Tibia.basePose = value;
    }
    char get_Id_Tibia(void) {
        return m_Tibia.iD;
    }
    unsigned char get_PulseMax_Tibia(void) {
        return m_Tibia.max;
    }
    unsigned char get_PulseMin_Tibia(void) {
        return m_Tibia.min;
    }
    unsigned char get_DefaultPulse_Tibia(void) {
        return m_Tibia.basePose;
    }
    unsigned char get_CurrentPulse_Tibia(void) {
        return m_Tibia.curr;
    }
    //setting Tars //
    void set_Id_Tars(char id) {
        m_Tars.iD = id;
    }
    void set_PulseMax_Tars(unsigned char value) {
        m_Tars.max = value;
    }
    void set_PulseMin_Tars(unsigned char value) {
        m_Tars.min = value;
    }
    void set_DefaultPulse_Tars(unsigned char value) {
        m_Tars.basePose = value;
    }
    char get_Id_Tars(void) {
        return m_Tars.iD;
    }
    unsigned char get_PulseMax_Tars(void) {
        return m_Tars.max;
    }
    unsigned char get_PulseMin_Tars(void) {
        return m_Tars.min;
    }
    unsigned char get_DefaultPulse_Tars(void) {
        return m_Tars.basePose;
    }
    unsigned char get_CurrentPulse_Tars(void) {
        return m_Tars.curr;
    }
    //setting All-in-one //
    void set_Id(char coxaId,char femurId,char tibiaId,char tarsId) {
        m_Coxa.iD = coxaId;
        m_Femur.iD= femurId;
        m_Tibia.iD= tibiaId;
        m_Tars.iD = tarsId;
    }
    void set_PulseMax(unsigned char coxaValue,unsigned char femurValue,
                      unsigned char tibiaValue,unsigned char tarsValue) {
        m_Coxa.max = coxaValue;
        m_Femur.max= femurValue;
        m_Tibia.max= tibiaValue;
        m_Tars.max = tarsValue;
    }
    void set_PulseMin(unsigned char coxaValue,unsigned char femurValue,
                      unsigned char tibiaValue,unsigned char tarsValue) {
        m_Coxa.min = coxaValue;
        m_Femur.min= femurValue;
        m_Tibia.min= tibiaValue;
        m_Tars.min = tarsValue;
    }
    void set_DefaultPulse(unsigned char coxaValue,unsigned char femurValue,
                          unsigned char tibiaValue,unsigned char tarsValue) {
        m_Coxa.basePose = coxaValue;
        m_Femur.basePose= femurValue;
        m_Tibia.basePose= tibiaValue;
        m_Tars.basePose = tarsValue;
    }
    //////////
    // Move //
    //////////
    void move_Coxa(unsigned char value) {
        if((value >= m_Coxa.min)&&(value <= m_Coxa.max ))
            m_Coxa.curr = value;
    }
    void move_Femur(unsigned char value) {
        if((value >= m_Femur.min)&&(value <= m_Femur.max ))
            m_Femur.curr = value;
    }
    void move_Tibia(unsigned char value) {
        if((value >= m_Tibia.min)&&(value <= m_Tibia.max ))
            m_Tibia.curr = value;
    }
    void move_Tars(unsigned char value) {
        if((value >= m_Tars.min)&&(value <= m_Tars.max ))
            m_Tars.curr = value;
    }
    void move(unsigned char coxaValue,unsigned char femurValue,
              unsigned char tibiaValue,unsigned char tarsValue) {//noob proof
        if((coxaValue >= m_Coxa.min)&&(coxaValue <= m_Coxa.max ))
            m_Coxa.curr = coxaValue;
        if((femurValue >= m_Femur.min)&&(femurValue <= m_Femur.max ))
            m_Femur.curr = femurValue;
        if((tibiaValue >= m_Tibia.min)&&(tibiaValue <= m_Tibia.max ))
            m_Tibia.curr = tibiaValue;
        if((tarsValue >= m_Tars.min)&&(tarsValue <= m_Tars.max ))
            m_Tars.curr = tarsValue;
    }
};
#endif /* PATTE_H_ */