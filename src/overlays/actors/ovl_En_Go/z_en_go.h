#ifndef _Z_EN_GO_H_
#define _Z_EN_GO_H_

#include <ultra64.h>
#include <global.h>

struct EnGo;

typedef void (*EnGoActionFunc)(struct EnGo*, GlobalContext*);

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ char unk_0C[0x8];
    /* 0x14 */ Vec3f unk_14;
    /* 0x20 */ Vec3f unk_20;
    /* 0x2C */ Vec3f unk_2C;
} EnGoStruct1; // size = 0x38

typedef struct EnGo {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ EnGoActionFunc actionFunc;
    /* 0x0194 */ ColliderCylinder collider;
    /* 0x01E0 */ struct_80034A14_arg1 unk_1E0;
    /* 0x0208 */ char unk_208[0x4]; // Likely part of struct above
    /* 0x020C */ s16 unk_20C;
    /* 0x020E */ s16 unk_20E;
    /* 0x0210 */ s16 unk_210;
    /* 0x0212 */ s16 unk_212;
    /* 0x0214 */ s16 unk_214;
    /* 0x0216 */ s16 unk_216;
    /* 0x0218 */ s16 unk_218;
    /* 0x021A */ s16 unk_21A;
    /* 0x021C */ s16 unk_21C;
    /* 0x021E */ s16 unk_21E;
    /* 0x0220 */ s16 unk_220[18];
    /* 0x0244 */ s16 unk_244[18];
    /* 0x0268 */ EnGoStruct1 unk_268[20];
} EnGo; // size = 0x06C8

extern const ActorInit En_Go_InitVars;

#endif
