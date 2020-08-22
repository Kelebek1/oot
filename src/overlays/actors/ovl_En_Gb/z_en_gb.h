#ifndef _Z_EN_GB_H_
#define _Z_EN_GB_H_

#include <ultra64.h>
#include <global.h>

struct EnGb;

typedef void (*EnGbActionFunc)(struct EnGb*, GlobalContext*);

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ Vec3f unk_08;
    /* 0x14 */ Vec3f unk_14;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
} EnGbStruct1; // size 0x2C

typedef struct EnGb {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x0164 */ SkelAnime skelAnime;
    /* 0x01A8 */ Vec3s limbDrawTable[12];
    /* 0x01F0 */ Vec3s transitionDrawTable[12];
    /* 0x0238 */ EnGbActionFunc actionFunc;
    /* 0x023C */ ColliderCylinder collider1;
    /* 0x0288 */ ColliderCylinder colliders[3];
    /* 0x036C */ z_Light* light;
    /* 0x0370 */ LightInfoPositional lightInfo;
    /* 0x037E */ u16 unk_37E;
    /* 0x0380 */ s16 unk_380;
    /* 0x0382 */ s16 unk_382;
    /* 0x0384 */ Color_RGBA8_n unk_384;
    /* 0x0388 */ EnGbStruct1 unk_388[4];
} EnGb; // size = 0x0438

extern const ActorInit En_Gb_InitVars;

#endif
