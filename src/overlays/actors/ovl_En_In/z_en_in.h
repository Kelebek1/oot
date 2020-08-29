#ifndef _Z_EN_IN_H_
#define _Z_EN_IN_H_

#include <ultra64.h>
#include <global.h>

struct EnIn;

typedef struct EnIn {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ char unk_14C[0x94];
    /* 0x01E0 */ f32 unk_1E0;
    /* 0x01E2 */ char unk_1E4[0x2];
    /* 0x01E6 */ s16 unk_1E6;
    /* 0x01E8 */ char unk_1E8[0x1C0];
} EnIn; // size = 0x03A8

extern const ActorInit En_In_InitVars;

#endif
