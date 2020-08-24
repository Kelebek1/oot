#ifndef _Z_EN_GM_H_
#define _Z_EN_GM_H_

#include <ultra64.h>
#include <global.h>

struct EnGm;

typedef void (*EnGmActionFunc)(struct EnGm*, GlobalContext*);

typedef struct EnGm {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ Vec3s limbDrawTable[18];
    /* 0x01FC */ Vec3s transitionDrawTable[18];
    /* 0x0268 */ EnGmActionFunc unk_268;
    /* 0x026C */ EnGmActionFunc unk_26C;
    /* 0x0270 */ ColliderCylinder collider;
    /* 0x02BC */ s8 unk_2BC;
    /* 0x02BE */ s16 unk_2BE;
    /* 0x02C0 */ s16 unk_2C0;
    /* 0x02C2 */ u8 unk_2C2;
    /* 0x02C4 */ Vec3f unk_2C4;

} EnGm; // size = 0x02D0

extern const ActorInit En_Gm_InitVars;

#endif
