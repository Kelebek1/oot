#ifndef _Z_EN_DH_H_
#define _Z_EN_DH_H_

#include <ultra64.h>
#include <global.h>

struct EnDh;

typedef struct EnDh {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ char unk_190[0xC0];
    /* 0x0250 */ u8 unk_250;
    /* 0x0251 */ char unk_251[0xA];
    /* 0x025B */ u8 unk_25B;
    /* 0x025C */ char unk_25C[0x2];
    /* 0x025E */ s16 unk_25E;
    /* 0x0260 */ char unk_260[0xB8];
    /* 0x0318 */ f32 unk_318;
} EnDh; // size = 0x0324

extern const ActorInit En_Dh_InitVars;

#endif
