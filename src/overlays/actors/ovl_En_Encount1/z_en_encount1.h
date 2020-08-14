#ifndef _Z_EN_ENCOUNT1_H_
#define _Z_EN_ENCOUNT1_H_

#include <ultra64.h>
#include <global.h>

struct EnEncount1;

typedef void (*EnEncount1ActionFunc)(struct EnEncount1*, GlobalContext*);

typedef struct EnEncount1 {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ EnEncount1ActionFunc actionFunc;
    /* 0x0150 */ s16 unk_150;
    /* 0x0152 */ s16 unk_152;
    /* 0x0154 */ s16 unk_154;
    /* 0x0156 */ s16 unk_156;
    /* 0x0158 */ s16 unk_158;
    /* 0x015A */ s16 unk_15A;
    /* 0x015C */ s16 unk_15C; 
    /* 0x015E */ s16 unk_15E;
    /* 0x0160 */ s16 unk_160;
    /* 0x0162 */ s16 unk_162;
    /* 0x0164 */ s16 unk_164;
    /* 0x0166 */ u8 unk_166;
    /* 0x0168 */ f32 unk_168;
    /* 0x016C */ EnReeba* unk_16C;
} EnEncount1; // size = 0x0170

extern const ActorInit En_Encount1_InitVars;

#endif
