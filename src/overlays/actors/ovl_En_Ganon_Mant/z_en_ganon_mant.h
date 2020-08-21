#ifndef _Z_EN_GANON_MANT_H_
#define _Z_EN_GANON_MANT_H_

#include <ultra64.h>
#include <global.h>

struct EnGanonMant;

typedef struct {
    /* 0x000 */ Vec3f unk_000;
    /* 0x00C */ Vec3f unk_00C[12];
    /* 0x09C */ Vec3f unk_09C[12];
    /* 0x12C */ Vec3f unk_12C[12];
    /* 0x00C */ s8 unk_1BC[12];
} EnGanonMantStruct2; // size = 0x1C8

typedef struct EnGanonMant {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ EnGanonMantStruct2 unk_014C[12];
    /* 0x16B0 */ f32 unk_16AC;
    /* 0x16B0 */ f32 unk_16B0;
    /* 0x16B4 */ f32 unk_16B4;
    /* 0x16B8 */ f32 unk_16B8;
    /* 0x16BC */ f32 unk_16BC;
    /* 0x16C0 */ f32 unk_16C0;
    /* 0x16C4 */ f32 unk_16C4;
    /* 0x16C8 */ f32 unk_16C8;
    /* 0x16CC */ f32 unk_16CC;
    /* 0x16D0 */ f32 unk_16D0;
    /* 0x16D4 */ Vec3f unk_16D4;
    /* 0x16E0 */ Vec3f unk_16E0;
    /* 0x16EC */ Vec3f unk_16EC;
    /* 0x16F8 */ Vec3f unk_16F8;
    /* 0x1704 */ u8 unk_1704;
    /* 0x1705 */ u8 unk_1705;
    /* 0x1706 */ u8 unk_1706;
} EnGanonMant; // size = 0x1708

extern const ActorInit En_Ganon_Mant_InitVars;

#endif
