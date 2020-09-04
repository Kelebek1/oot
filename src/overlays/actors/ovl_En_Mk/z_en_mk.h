#ifndef _Z_EN_MK_H_
#define _Z_EN_MK_H_

#include <ultra64.h>
#include <global.h>

struct EnMk;

typedef void (*EnMkActionFunc)(struct EnMk*, GlobalContext*);

typedef struct EnMk {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ ColliderCylinder collider;
    /* 0x0198 */ SkelAnime skelAnime;
    /* 0x01DC */ Vec3s limbDrawTable[13];
    /* 0x022A */ Vec3s transitionDrawTable[13];
    /* 0x0278 */ Vec3s unk_278;
    /* 0x027E */ u16 unk_27E;
    /* 0x0280 */ s16 unk_280;
    /* 0x0282 */ u16 unk_282;
    /* 0x0284 */ EnMkActionFunc actionFunc;
} EnMk; // size = 0x0288

extern const ActorInit En_Mk_InitVars;

#endif
