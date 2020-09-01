#ifndef _Z_EN_IN_H_
#define _Z_EN_IN_H_

#include <ultra64.h>
#include <global.h>

struct EnIn;

typedef void (*EnInActionFunc)(struct EnIn*, GlobalContext*);

typedef struct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} EnInStruct1;

typedef struct EnIn {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ EnInActionFunc actionFunc;
    /* 0x0194 */ ColliderCylinder collider;
    /* 0x01E0 */ f32 unk_1E0;
    /* 0x01E2 */ s8 unk_1E4;
    /* 0x01E6 */ s16 unk_1E6;
    /* 0x01E8 */ s16 unk_1E8;
    /* 0x01EA */ s16 unk_1EA;
    /* 0x01EC */ s16 unk_1EC;
    /* 0x01EE */ s16 unk_1EE;
    /* 0x01F0 */ s16 unk_1F0;
    /* 0x01F2 */ s16 unk_1F2;
    /* 0x01F4 */ char unk_1F4[0x4];
    /* 0x01F8 */ s16 unk_1F8;
    /* 0x01FA */ s16 unk_1FA;
    /* 0x01FC */ s16 unk_1FC;
    /* 0x01FE */ Vec3s limbDrawTable[20];
    /* 0x0276 */ Vec3s transitionDrawTable[20];
    /* 0x02F0 */ Vec3f unk_2F0;
    /* 0x02FC */ Vec3f unk_2FC;
    /* 0x0308 */ struct_80034A14_arg1 unk_308;
    /* 0x0330 */ EnInStruct1 unk_330[5];
} EnIn; // size = 0x03A8

extern const ActorInit En_In_InitVars;

#endif
