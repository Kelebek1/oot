#ifndef _Z_EN_FISH_H_
#define _Z_EN_FISH_H_

#include <ultra64.h>
#include <global.h>

struct EnFish;

typedef void (*EnFishActionFunc)(struct EnFish*, GlobalContext*);

typedef struct EnFish {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ ColliderJntSph collider;
    /* 0x016C */ ColliderJntSphItem colliderItems[1];
    /* 0x01AC */ SkelAnime skelAnime;
    /* 0x01F0 */ Vec3s limbDrawTable[7];
    /* 0x021A */ Vec3s transitionDrawTable[7];
    /* 0x0244 */ EnFishActionFunc actionFunc;
    /* 0x0248 */ s16 unk_248;
    /* 0x024A */ s16 unk_24A;
    /* 0x024C */ s16 unk_24C;
    /* 0x024E */ s16 unk_24E;
    /* 0x0250 */ s32 unk_250;
} EnFish; // size = 0x0254

extern const ActorInit En_Fish_InitVars;

#endif
