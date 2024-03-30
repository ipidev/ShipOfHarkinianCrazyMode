#ifndef Z_EN_VASE_H
#define Z_EN_VASE_H

#include <libultraship/libultra.h>
#include "global.h"

struct EnVase;

typedef struct EnVase {
    //ipi: Make this unused actor into an ice block instead
    /* 0x0000 */ DynaPolyActor dyna;
                 u8 timer;
                 u8 phase;
} EnVase; // size = 0x014C

#endif
