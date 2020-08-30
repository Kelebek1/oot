#ifndef _Z_EN_HORSE_NORMAL_H_
#define _Z_EN_HORSE_NORMAL_H_

#include <ultra64.h>
#include <global.h>

struct EnHorseNormal;

typedef void (*EnHorseNormalActionFunc)(struct EnHorseNormal*, GlobalContext*);

typedef struct EnHorseNormal {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ s32 unk_14C;
    /* 0x0150 */ s32 unk_150;
    /* 0x0154 */ PSkinAwb skin;
    /* 0x01E4 */ u16 unk_1E4;
    /* 0x01E8 */ Vec3f unk_1E8;
    /* 0x01F4 */ Vec3f unk_1F4;
    /* 0x0200 */ s32 unk_200;
    /* 0x0204 */ Vec3f unk_204;
    /* 0x0210 */ char unk_210[0x8];
    /* 0x0218 */ f32 unk_218;
    /* 0x021C */ s16 unk_21C;
    /* 0x021E */ s16 unk_21E;
    /* 0x0220 */ f32 unk_220;
    /* 0x0224 */ char unk_224[0x4];
    /* 0x0228 */ ColliderCylinder collider1;
    /* 0x0274 */ ColliderJntSph colliderSphere;
    /* 0x0294 */ ColliderJntSphItem colliderSphereItems[1];
    /* 0x02D4 */ ColliderCylinder collider3;
    /* 0x0320 */ char unk_320[0x4];
    /* 0x0324 */ s32 unk_324;
} EnHorseNormal; // size = 0x0328

extern const ActorInit En_Horse_Normal_InitVars;

#endif
