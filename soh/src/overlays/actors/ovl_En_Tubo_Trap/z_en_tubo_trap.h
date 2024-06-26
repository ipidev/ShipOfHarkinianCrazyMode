#ifndef Z_EN_TUBO_TRAP_H
#define Z_EN_TUBO_TRAP_H

#include <libultraship/libultra.h>
#include "global.h"

struct EnTuboTrap;

typedef void (*EnTuboTrapActionFunc)(struct EnTuboTrap*, PlayState*);

typedef struct EnTuboTrap {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ EnTuboTrapActionFunc actionFunc;
    /* 0x0150 */ f32 targetY;
    /* 0x0154 */ Vec3f originPos;
    /* 0x0160 */ ColliderCylinder collider;
    //ipi: Extra flag to count the number of children
                 u8 shotsLeft;
} EnTuboTrap; // size = 0x01AC

#endif
