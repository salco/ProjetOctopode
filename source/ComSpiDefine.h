#ifdef COMSPI_H
#define COMSPI_H

// faire un debug pour la com spi
#define SYNC 84 //0b01010100

typedef enum {
    NOACK = 0,
    TXACK = 1,
    RXACK = 2,
    RXNAK = 3
} ACKvalue;

typedef enum {
    NDB00 = 0,
    NDB01 = 1,
    NDB02 = 2
} NDBvalue;

typedef enum {
    PFB0 = 0,
    PFB1 = 1,
    PFB2 = 2,
    PFB3  =3
} PFBvalue;
typedef enum {
    Request_Init_Info = 1,
    CONTIEN_AUTRE_MODULE = 2

} FLAGName;

#endif // COMSPI_H