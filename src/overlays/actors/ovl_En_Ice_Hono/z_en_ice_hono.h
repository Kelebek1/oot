#ifndef _Z_EN_ICE_HONO_H_
#define _Z_EN_ICE_HONO_H_

#include <ultra64.h>
#include <global.h>

struct EnIceHono;

typedef void (*EnIceHonoActionFunc)(struct EnIceHono*, GlobalContext*);

typedef struct EnIceHono {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ EnIceHonoActionFunc actionFunc;
    /* 0x0150 */ s16 unk_150;
    /* 0x0152 */ s16 unk_152;
    /* 0x0154 */ s16 unk_154;
    /* 0x0156 */ s16 unk_156;
    /* 0x0158 */ f32 unk_158;
    /* 0x015C */ ColliderCylinder collider;
    /* 0x01A8 */ z_Light* unk_1A8;
    /* 0x01AC */ LightInfoPositional unk_1AC;
} EnIceHono; // size = 0x01BC

extern const ActorInit En_Ice_Hono_InitVars;

#endif
