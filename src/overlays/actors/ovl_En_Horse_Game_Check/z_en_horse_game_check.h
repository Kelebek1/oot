#ifndef _Z_EN_HORSE_GAME_CHECK_H_
#define _Z_EN_HORSE_GAME_CHECK_H_

#include <ultra64.h>
#include <global.h>

struct EnHorseGameCheck;

typedef void (*EnHorseGameCheckActionFunc)(struct EnHorseGameCheck*, GlobalContext*);
typedef s32 (*EnHorseGameCheckFuncs)(struct EnHorseGameCheck*, GlobalContext*);

typedef struct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C[3];
} EnHorseGameCheckStruct1;

typedef struct EnHorseGameCheck {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ s32 unk_14C;
    /* 0x0150 */ EnHorseGameCheckStruct1 unk_150;
    /* 0x0168 */ char unk_168[0x4];
    /* 0x016C */ EnHorse* unk_16C;
    /* 0x0170 */ s32 unk_170;
    /* 0x0174 */ s32 unk_174;
    /* 0x0178 */ s32 unk_178;
    /* 0x017C */ s32 unk_17C;
    /* 0x0180 */ s32 unk_180;
    /* 0x0184 */ char unk_184[0x14];
    /* 0x0198 */ s32 unk_198;
    /* 0x019C */ s32 unk_19C;
    /* 0x01A0 */ s32 unk_1A0;
} EnHorseGameCheck; // size = 0x01A4

extern const ActorInit En_Horse_Game_Check_InitVars;

#endif
