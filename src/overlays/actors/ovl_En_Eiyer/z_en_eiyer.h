#ifndef _Z_EN_EIYER_H_
#define _Z_EN_EIYER_H_

#include <ultra64.h>
#include <global.h>

struct EnEiyer;

typedef void (*EnEiyerActionFunc)(struct EnEiyer*, GlobalContext*);

typedef struct EnEiyer {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ EnEiyerActionFunc actionFunc;
    /* 0x0194 */ s16 unk_194;
    /* 0x0196 */ s16 unk_196;
    /* 0x0198 */ Vec3s limbDrawTable[19];
    /* 0x020A */ Vec3s transitionDrawTable[19];
    /* 0x027C */ Vec3f unk_27C;
    /* 0x0288 */ ColliderCylinder collider;


} EnEiyer; // size = 0x02D4

extern const ActorInit En_Eiyer_InitVars;

#endif
