#ifndef Z_EN_FLOORMAS_H
#define Z_EN_FLOORMAS_H

#include <libultraship/libultra.h>
#include "global.h"

typedef struct EnFloormas EnFloormas;

typedef void (*EnFloormasActionFunc)(EnFloormas* this, PlayState* play);

struct EnFloormas{
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ EnFloormasActionFunc actionFunc;
    /* 0x0194 */ s16 actionTimer;
    /* 0x0196 */ s16 actionTarget;
    /* 0x0198 */ s16 zOffset;
    /* 0x019A */ s16 smActionTimer;
    /* 0x019C */ Vec3s jointTable[25];
    /* 0x0232 */ Vec3s morphTable[25];
    /* 0x02C8 */ ColliderCylinder collider;
    //ipi: Extra field to count the number of charges made in a row
                 u8 chargeCounter;
}; // size = 0x0314

#endif
