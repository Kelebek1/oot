#ifndef _Z_BOSS_TW_H_
#define _Z_BOSS_TW_H_

#include <ultra64.h>
#include <global.h>

struct BossTw;

typedef void (*BossTwActionFunc)(struct BossTw*, GlobalContext*);

typedef struct BossTw {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ BossTwActionFunc actionFunc;
    /* 0x017A */ s16 unk_17A;
    /* 0x01AC */ f32 unk_1AC;
    /* 0x01D4 */ f32 unk_1D4;
    /* 0x01D8 */ f32 unk_1D8;
    /* 0x01DC */ f32 unk_1DC;
    /* 0x01E0 */ f32 unk_1E0;
    /* 0x01E4 */ f32 unk_1E4;
    /* 0x0564 */ s8 unk_564;
    /* 0x0568 */ SkelAnime skelAnime;
    /* 0x05AC */ ColliderCylinder collider;
    /* 0x05C8 */ s8 unk_5C8;
} BossTw; // size = 0x06B4

extern const ActorInit Boss_Tw_InitVars;

#endif
