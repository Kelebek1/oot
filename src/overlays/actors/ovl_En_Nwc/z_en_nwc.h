#ifndef _Z_EN_NWC_H_
#define _Z_EN_NWC_H_

#include <ultra64.h>
#include <global.h>

struct EnNwc;

typedef void (*EnNwcActionFunc)(struct EnNwc*, GlobalContext*);

typedef struct {
    s8 unk_00;
    u8 unk_01;
    f32 unk_04;
    Vec3f unk_08;
    char unk_14[0x8];
    Vec3f unk_1C;
    char unk_28[0x4];
    f32 unk_2C;
    Vec3s unk_30;
    u16 unk_36;
    CollisionPoly* unk_38;
    char unk_3C[0x20];
} EnNwcStruct1; // size = 0x5C

typedef void (*EnNwcFunc)(EnNwcStruct1*, struct EnNwc*, GlobalContext*);

typedef struct EnNwc {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ ColliderJntSph collider;
    /* 0x016C */ u8 unk_16C;
    /* 0x0170 */ EnNwcStruct1 unk_170[16];
    /* 0x0730 */ EnNwcActionFunc actionFunc;
} EnNwc; // size = 0x0734

extern const ActorInit En_Nwc_InitVars;

#endif
