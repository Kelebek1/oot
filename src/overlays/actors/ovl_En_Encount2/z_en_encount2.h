#ifndef _Z_EN_ENCOUNT2_H_
#define _Z_EN_ENCOUNT2_H_

#include <ultra64.h>
#include <global.h>

struct EnEncount2;

typedef void (*EnEncount2ActionFunc)(struct EnEncount2*, GlobalContext*);

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ u8 unk_10;
    /* 0x15 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ Vec3f unk_20;
} EnEncount2Struct1; // size = 0x2C

typedef struct EnEncount2 {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ EnEncount2ActionFunc actionFunc;
    /* 0x0150 */ char unk_150[0x4];
    /* 0x0154 */ s16 unk_154;
    /* 0x0156 */ s16 unk_156;
    /* 0x0158 */ s16 unk_158;
    /* 0x015A */ s16 unk_15A;
    /* 0x015C */ s16 unk_15C;
    /* 0x015E */ s16 unk_15E;
    /* 0x0160 */ f32 unk_160;
    /* 0x0164 */ char unk_164[0x4];
    /* 0x0168 */ f32 unk_168;
    /* 0x016C */ char unk_16C[0x4];
    /* 0x0170 */ f32 unk_170;
    /* 0x0174 */ char unk_174[0x4];
    /* 0x0178 */ s16 unk_178;
    /* 0x017C */ f32 unk_17C;
    /* 0x0180 */ s32 unk_180;
    /* 0x0184 */ u32 unk_184;
    /* 0x0188 */ EnEncount2Struct1 unk_188[50];

} EnEncount2; // size = 0x0A20

extern const ActorInit En_Encount2_InitVars;

#endif
