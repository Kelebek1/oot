#ifndef _Z_EN_FD_H_
#define _Z_EN_FD_H_

#include <ultra64.h>
#include <global.h>

struct EnFd;

typedef void (*EnFdActionFunc)(struct EnFd*, GlobalContext*);

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01[2];
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Color_RGBA8 unk_0C;
    /* 0x10 */ char unk_10[0x4];
    /* 0x14 */ Vec3f unk_14;
    /* 0x20 */ Vec3f unk_20;
    /* 0x2C */ Vec3f unk_2C;

} EnFdStruct1; // size = 0x38

typedef struct EnFd {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ EnFdActionFunc actionFunc;
    /* 0x0194 */ ColliderJntSph collider;
    /* 0x01B4 */ ColliderJntSphItem colliderItems[12];
    /* 0x04B4 */ s8 unk_4B4;
    /* 0x04B6 */ s16 unk_4B6;
    /* 0x04B8 */ u16 unk_4B8;
    /* 0x04BA */ s16 unk_4BA;
    /* 0x04BC */ s16 unk_4BC;
    /* 0x04BE */ s16 unk_4BE;
    /* 0x04C0 */ s16 unk_4C0;
    /* 0x04C2 */ s16 unk_4C2;
    /* 0x04C4 */ s16 unk_4C4;
    /* 0x04C8 */ f32 unk_4C8;
    /* 0x04CC */ f32 unk_4CC;
    /* 0x04D0 */ Vec3f unk_4D0;
    /* 0x04DC */ Vec3s limbDrawTable[27];
    /* 0x057E */ Vec3s transitionDrawTable[27];
    /* 0x0620 */ EnFdStruct1 unk_620[200];
} EnFd; // size = 0x31E0

extern const ActorInit En_Fd_InitVars;

#endif
