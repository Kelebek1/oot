#ifndef _Z_EN_KO_H_
#define _Z_EN_KO_H_

#include <ultra64.h>
#include <global.h>

struct EnKo;

typedef void (*EnKoActionFunc)(struct EnKo*, GlobalContext*);

typedef struct EnKo {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ EnKoActionFunc actionFunc;
    /* 0x0194 */ s8 unk_194;
    /* 0x0195 */ s8 unk_195;
    /* 0x0196 */ s8 unk_196;
    /* 0x0197 */ s8 unk_197;
    /* 0x0198 */ ColliderCylinder collider;
    /* 0x01E4 */ Path* unk_1E4;
    /* 0x01E8 */ struct_80034A14_arg1 unk_1E8;
    /* 0x0210 */ u8 unk_210;
    /* 0x0212 */ s16 unk_212;
    /* 0x0214 */ s16 unk_214;
    /* 0x0216 */ s16 unk_216;
    /* 0x0218 */ f32 unk_218;
    /* 0x021C */ f32 unk_21C;
    /* 0x0220 */ f32 unk_220;
    /* 0x0224 */ Vec3s limbDrawTable[16];
    /* 0x0284 */ Vec3s transitionDrawTable[16];
    /* 0x02E4 */ s16 unk_2E4[16];
    /* 0x0304 */ s16 unk_304[16];
} EnKo; // size = 0x0324

extern const ActorInit En_Ko_InitVars;

#endif
