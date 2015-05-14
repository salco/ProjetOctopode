
#ifndef OSNAP_H
#define OSNAP_H

//#define NONE 0


struct osnapModule_t{
    unsigned char addrModule; //osnapRegisterA
    
    union{
        unsigned char getByte;
        struct
        {
            unsigned char typeFormat  : 1;
            unsigned char linkToReaction : 3;
            unsigned char addrPeripherique : 4;
        };
    }osnapRegisterB;
    
    union{
        unsigned char getByte;
        struct
        {
            unsigned char positionSpatiale : 6;
            unsigned char typeFormat : 2;
        };
    }osnapRegisterC;
    
    union{
        unsigned char getByte;
        struct
        {
            unsigned char sousType  : 6;
            unsigned char type : 2;
        };
    }osnapRegisterD;
    
};
typedef enum {
    NON_DETERMINER = 0,
    DIGITALE = 1,
    ANALOGIQUE=2
} TypeDeFormat;

typedef enum {
    //NONE =0,
    CAPTEUR = 1,
    ACTIONEUR = 2,
    MEMOIRE = 3
} typeModue;

typedef enum {
    //NONE =0,
    PROXIMITEE = 1,
    DISTANCE = 2,
    ULTRASONIQUE = 3,
    TEMPERATURE =4,
} sousType_Capteur;

typedef enum {
    //NONE =0,

} sousType_Actionneur;

typedef enum {
    //NONE =0,

} sousType_Memoire;

typedef enum {
    //NONE =0,

} positionSpatial;

#endif // OSNAP_H //