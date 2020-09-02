#ifndef _Z_EN_JSJUTAN_H_
#define _Z_EN_JSJUTAN_H_

#include <ultra64.h>
#include <global.h>

struct EnJsjutan;

typedef struct EnJsjutan {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x0164 */ u8 unk_164;
    /* 0x0168 */ f32 unk_168;
    /* 0x016C */ f32 unk_16C;
    /* 0x0170 */ f32 unk_170;
    /* 0x0174 */ u8 unk_174;
    /* 0x0175 */ u8 unk_175;
} EnJsjutan; // size = 0x0178

extern const ActorInit En_Jsjutan_InitVars;

#endif
