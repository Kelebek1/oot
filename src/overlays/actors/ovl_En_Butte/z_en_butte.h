#ifndef _Z_EN_BUTTE_H_
#define _Z_EN_BUTTE_H_

#include <ultra64.h>
#include <global.h>

struct EnButte;

typedef void (*EnButteActionFunc)(struct EnButte*, GlobalContext*);

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec3f a;
    /* 0x10 */ s16 d;
} EnButteStruct1; // size = 0x14

typedef struct EnButte {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ ColliderJntSph collider;
    /* 0x016C */ ColliderJntSphItem colliderItems[1];
    /* 0x01AC */ SkelAnime skelAnime;
    /* 0x01F0 */ Vec3s limbDrawTable[8];
    /* 0x0220 */ Vec3s transitionDrawTable[8];
    /* 0x0250 */ EnButteActionFunc actionFunc;
    /* 0x0254 */ s16 unk_254;
    /* 0x0256 */ u8 unk_256;
    /* 0x0257 */ u8 unk_257;
    /* 0x0258 */ u8 unk_258;
    /* 0x025A */ s16 unk_25A;
    /* 0x025C */ s16 unk_25C;
    /* 0x025E */ s16 unk_25E;
    /* 0x0260 */ s16 unk_260;
    /* 0x0264 */ f32 unk_264;
} EnButte; // size = 0x0268

extern const ActorInit En_Butte_InitVars;

#endif
