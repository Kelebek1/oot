#ifndef _Z_EN_GE1_H_
#define _Z_EN_GE1_H_

#include <ultra64.h>
#include <global.h>

struct EnGe1;

typedef void (*EnGe1ActionFunc)(struct EnGe1*, GlobalContext*);

typedef struct EnGe1 {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ ColliderCylinder collider;
    /* 0x0198 */ SkelAnime skelAnime;
    /* 0x01DC */ Vec3s limbDrawTable[16];
    /* 0x023C */ Vec3s transitionDrawTable[16];
    /* 0x029C */ Vec3s unk_29C;
    /* 0x02A2 */ Vec3s unk_2A2;
    /* 0x02A8 */ s16 unk_2A8;
    /* 0x02AA */ s16 unk_2AA;
    /* 0x02AC */ u16 unk_2AC;
    /* 0x02AE */ u8 unk_2AE;
    /* 0x02AF */ u8 unk_2AF;
    /* 0x02B0 */ AnimationHeader* unk_2B0;
    /* 0x02B4 */ EnGe1ActionFunc actionFunc;
    /* 0x02B8 */ void (*unk_2B8)(struct EnGe1*);
} EnGe1; // size = 0x02BC

extern const ActorInit En_Ge1_InitVars;

#endif
