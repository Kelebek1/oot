#ifndef _Z_BOSS_FD_H_
#define _Z_BOSS_FD_H_

#include <ultra64.h>
#include <global.h>

struct BossFd;

typedef void (*BossFdActionFunc)(struct BossFd*, GlobalContext*);

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ char unk_0C[0x18];
    /* 0x24 */ u8 unk_24;
    /* 0x25 */ char unk_25[0x1];
    /* 0x26 */ Color_RGBA8_n unk_26;
    ///* 0x29 */ char unk_29[0x1];

    /* 0x2A */ s16 unk_2A;
    /* 0x2C */ s16 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
} BossFdStruct1; // size = 0x3C

typedef struct BossFd {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime1;
    /* 0x0190 */ SkelAnime skelAnime2;
    /* 0x01D4 */ SkelAnime skelAnime3;

    /* 0x0218 */ BossFdActionFunc actionFunc;

    /* 0x021E */ s16 unk_21E;
    /* 0x0228 */ s16 unk_228;

    /* 0x0230 */ s16 unk_230;
    /* 0x02D5 */ s8 unk_2D5;

    /* 0x078C */ Vec3f unk_078C[100];
    /* 0x0C3C */ char unk_0C3C[0x1C8];
    /* 0x0E04 */ Vec3f unk_0E04[100];

    /* 0x12B4 */ char unk_12B4[0x11C];
    /* 0x13D0 */ s16 unk_1402;
    /* 0x1402 */ s16 unk_1402;

    /* 0x1490 */ ColliderJntSph collider1;
    /* 0x14B0 */ ColliderJntSphItem colliderItems[19];
    /* 0x1970 */ BossFdStruct1 unk_1970[180];
} BossFd; // size = 0x43A0

extern const ActorInit Boss_Fd_InitVars;

#endif
