#ifndef _Z_EN_REEBA_H_
#define _Z_EN_REEBA_H_

#include <ultra64.h>
#include <global.h>

struct EnReeba;

typedef struct EnReeba {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ char unk_14C[0x134];
    /* 0x0280 */ s16 unk_280; 
    /* 0x0282 */ char unk_282[0x5A];
} EnReeba; // size = 0x02DC

extern const ActorInit En_Reeba_InitVars;

#endif
