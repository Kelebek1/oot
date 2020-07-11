#ifndef _Z_BG_PO_SYOKUDAI_H_
#define _Z_BG_PO_SYOKUDAI_H_

#include <ultra64.h>
#include <global.h>

struct BgPoSyokudai;

typedef struct BgPoSyokudai {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ u8 unk_14C;
    /* 0x014C */ u8 unk_14D;
    /* 0x014E */ s16 unk_14E;
    /* 0x0150 */ z_Light* unk_150;
    /* 0x0154 */ LightInfoPositional unk_154;
    /* 0x0164 */ ColliderCylinder unk_164;
} BgPoSyokudai; // size = 0x01B0

extern const ActorInit Bg_Po_Syokudai_InitVars;

#endif
