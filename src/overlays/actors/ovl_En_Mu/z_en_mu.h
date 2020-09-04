#ifndef _Z_EN_MU_H_
#define _Z_EN_MU_H_

#include <ultra64.h>
#include <global.h>

struct EnMu;

typedef void (*EnMuActionFunc)(struct EnMu*, GlobalContext*);

typedef struct EnMu {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ EnMuActionFunc actionFunc;
    /* 0x0194 */ ColliderCylinder collider;
    /* 0x01E0 */ struct_80034A14_arg1 unk_1E0;
    ///* 0x01E2 */ char unk_1E2[0x26];
    /* 0x0208 */ u16 unk_208;
    /* 0x020A */ s16 unk_20A[16];
    /* 0x022A */ s16 unk_22A[16];
} EnMu; // size = 0x024C

extern const ActorInit En_Mu_InitVars;

#endif
