#ifndef _Z_OBJ_SYOKUDAI_H_
#define _Z_OBJ_SYOKUDAI_H_

#include <ultra64.h>
#include <global.h>

struct ObjSyokudai;

typedef struct ObjSyokudai {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ char unk_14C[0x98];
    /* 0x01E4 */ s16 unk_1E4;
    /* 0x01E6 */ char unk_1E6[0x18];
} ObjSyokudai; // size = 0x01FC

extern const ActorInit Obj_Syokudai_InitVars;

#endif
