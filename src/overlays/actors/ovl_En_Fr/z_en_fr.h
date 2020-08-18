#ifndef _Z_EN_FR_H_
#define _Z_EN_FR_H_

#include <ultra64.h>
#include <global.h>

struct EnFr;

typedef void (*EnFrActionFunc)(struct EnFr*, GlobalContext*);

typedef struct EnFr {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime1;
    /* 0x0190 */ Vec3s limbDrawTable1[24];
    /* 0x0220 */ Vec3s transitionDrawTable1[24];
    /* 0x02B0 */ SkelAnime skelAnime2;
    /* 0x02F4 */ Vec3s limbDrawTable2[8];
    /* 0x0324 */ Vec3s transitionDrawTable2[8];
    /* 0x0354 */ EnFrActionFunc actionFunc;
    /* 0x0358 */ z_Light* unk_358;
    /* 0x035C */ LightInfoPositional unk_35C;
    /* 0x036A */ s8 unk_36A;
    /* 0x036C */ s32 unk_36C;
    /* 0x0370 */ s32 unk_370;
    /* 0x0374 */ void (*unk_374)(struct EnFr*);
    /* 0x0378 */ u8 unk_378;
    /* 0x0379 */ u8 unk_379;
    /* 0x037A */ u8 unk_37A;
    /* 0x037B */ u8 unk_37B;
    /* 0x037C */ u8 unk_37C;
    /* 0x037D */ u8 unk_37D;
    /* 0x037E */ u8 unk_37E;
    /* 0x037F */ u8 unk_37F;
    /* 0x0380 */ u8 unk_380;
    /* 0x0381 */ u8 unk_381;
    /* 0x0382 */ u8 unk_382;
    /* 0x0383 */ u8 unk_383;
    /* 0x0384 */ char unk_384[0x2];
    /* 0x0386 */ s16 unk_386;
    /* 0x0388 */ s32 unk_388;
    /* 0x038C */ Vec3f unk_38C;
    /* 0x0398 */ f32 unk_398;
    /* 0x039C */ f32 unk_39C;
    /* 0x03A0 */ f32 unk_3A0;
    /* 0x03A4 */ Actor* unk_3A4; // Guess
    /* 0x03A8 */ u8 unk_3A8;
    /* 0x03AA */ s16 unk_3AA;
    /* 0x03AC */ Vec3f unk_3AC;
    /* 0x03B8 */ Vec3f unk_3B8;
} EnFr; // size = 0x03C4

extern const ActorInit En_Fr_InitVars;

#endif
