
#ifndef OSNAP_H
#define OSNAP_H

//#define NONE 0

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