#ifndef _Z_EN_FW_H_
#define _Z_EN_FW_H_

#include <ultra64.h>
#include <global.h>

struct EnFw;

typedef void (*EnFwActionFunc)(struct EnFw*, GlobalContext*);

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
} EnFwStruct1; // size = 0x38

typedef struct EnFw {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ EnFwActionFunc actionFunc;
    /* 0x0194 */ ColliderJntSph collider;
    /* 0x01B4 */ ColliderJntSphItem colliderItems[1];
    /* 0x01F4 */ Vec3f unk_1F4;
    /* 0x0200 */ u8 unk_200;
    /* 0x0202 */ s16 unk_202;
    /* 0x0204 */ s16 unk_204;
    /* 0x0206 */ s16 unk_206;
    /* 0x0208 */ s16 unk_208;
    /* 0x020A */ s16 unk_20A;
    /* 0x020C */ char unk_20C[0x2];
    /* 0x020E */ s16 unk_20E;
    /* 0x0210 */ s16 unk_210;
    /* 0x0212 */ s16 unk_212;
    /* 0x0214 */ s16 unk_214;
    /* 0x0218 */ f32 unk_218;
    /* 0x021C */ Vec3s limbDrawTable[11];
    /* 0x025E */ Vec3s transitionDrawTable[11];
    /* 0x02A0 */ EnFwStruct1 unk_2A0[20];
} EnFw; // size = 0x0700

extern const ActorInit En_Fw_InitVars;

#endif
