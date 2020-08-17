#ifndef _Z_EN_FIRE_ROCK_H_
#define _Z_EN_FIRE_ROCK_H_

#include <ultra64.h>
#include <global.h>

struct EnFireRock;

typedef void (*EnFireRockActionFunc)(struct EnFireRock*, GlobalContext*);

typedef struct {
	Actor actor;
	char unk_14C[0xC];
	s16 unk_158;
} EnFireRockFakeActor;

typedef struct EnFireRock {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ f32 unk_14C;
    /* 0x0150 */ f32 unk_150;
    /* 0x0154 */ f32 unk_154;
    /* 0x0158 */ f32 unk_158;
    /* 0x015C */ f32 unk_15C;
    /* 0x0160 */ f32 unk_160;
    /* 0x0164 */ char unk_164[0x4];
    /* 0x0168 */ EnFireRockActionFunc actionFunc;
    /* 0x016C */ f32 unk_16C;
    /* 0x0170 */ f32 unk_170;
    /* 0x0174 */ f32 unk_174;
    /* 0x0178 */ f32 unk_178;
    /* 0x017C */ f32 unk_17C;
    /* 0x0180 */ char unk_180[0x4];
    /* 0x0184 */ f32 unk_184;
    /* 0x0188 */ s16 unk_188;
    /* 0x018A */ s16 unk_18A;
    /* 0x018C */ s16 unk_18C;
    /* 0x018E */ u8 unk_18E;
    /* 0x0190 */ Actor* unk_190;
    /* 0x0194 */ ColliderCylinder collider;
} EnFireRock; // size = 0x01E0

extern const ActorInit En_Fire_Rock_InitVars;

#endif
