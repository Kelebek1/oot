#ifndef _Z_BOSS_TW_H_
#define _Z_BOSS_TW_H_

#include <ultra64.h>
#include <global.h>

struct BossTw;

typedef void (*BossTwActionFunc)(struct BossTw*, GlobalContext*);

typedef struct BossTw {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ BossTwActionFunc actionFunc;
    /* 0x0150 */ s16 unk_150;
    /* 0x0152 */ s16 unk_152;
    /* 0x0154 */ char unk_154[0x2];
    /* 0x0156 */ s16 unk_156;
    /* 0x0158 */ s16 unk_158;
    /* 0x015A */ s16 unk_15A;
    /* 0x015C */ s16 unk_15C;
    /* 0x015E */ char unk_15E[0x1A];
    /* 0x0178 */ s16 unk_178[5];
    /* 0x0182 */ char unk_182[0x2];
    /* 0x0184 */ f32 unk_184;
    /* 0x0188 */ f32 unk_188;
    /* 0x018C */ f32 unk_18C;
    /* 0x0190 */ f32 unk_190;
    /* 0x0194 */ f32 unk_194;
    /* 0x0198 */ f32 unk_198;
    /* 0x019C */ f32 unk_19C;
    /* 0x01A0 */ f32 unk_1A0;
    /* 0x01A4 */ char unk_1A4[0x4];
    /* 0x01A8 */ f32 unk_1A8;
    /* 0x01AC */ f32 unk_1AC;
    /* 0x01B0 */ f32 unk_1B0;
    /* 0x01B4 */ f32 unk_1B4;
    /* 0x01B8 */ f32 unk_1B8;
    /* 0x01BC */ f32 unk_1BC;
    /* 0x01C0 */ f32 unk_1C0;
    /* 0x01C4 */ f32 unk_1C4;
    /* 0x01C8 */ f32 unk_1C8;
    /* 0x01DC */ char unk_1CC[0x8];
    /* 0x01D4 */ f32 unk_1D4;
    /* 0x01D8 */ f32 unk_1D8;
    /* 0x01DC */ f32 unk_1DC;
    /* 0x01E0 */ f32 unk_1E0;
    /* 0x01E4 */ f32 unk_1E4;
    /* 0x01E8 */ Vec3f unk_1E8[50];
    /* 0x0440 */ char unk_440[0x4];
    /* 0x0444 */ Vec3f unk_444;
    /* 0x0450 */ Vec3f unk_450;
    /* 0x045C */ Vec3f unk_45C;
    /* 0x0468 */ Vec3f unk_468;
    /* 0x0474 */ Vec3f unk_474;
    /* 0x0480 */ Vec3f unk_480;
    /* 0x048C */ Vec3f unk_48C;
    /* 0x0498 */ char unk_498[0x24];
    /* 0x04BC */ f32 unk_4BC;
    /* 0x04C0 */ f32 unk_4C0;
    /* 0x04C4 */ f32 unk_4C4;
    /* 0x04C8 */ char unk_4C8[0x4];
    /* 0x04CC */ s16 unk_4CC;
    /* 0x04D0 */ f32 unk_4D0;
    /* 0x04D4 */ f32 unk_4D4;
    /* 0x04D8 */ f32 unk_4D8;
    /* 0x04DC */ char unk_4DC[0x4];
    /* 0x04E0 */ f32 unk_4E0;
    /* 0x04E4 */ char unk_4E4[0x4];
    /* 0x04E8 */ f32 unk_4E8;
    /* 0x04EC */ f32 unk_4EC;
    /* 0x04F0 */ char unk_4F0[0x8];
    /* 0x04F8 */ f32 unk_4F8;
    /* 0x04FC */ char unk_4FC[0x10];
    /* 0x050C */ f32 unk_50C;
    /* 0x0510 */ f32 unk_510;
    /* 0x0514 */ f32 unk_514;
    /* 0x0518 */ f32 unk_518;
    /* 0x051C */ f32 unk_51C;
    /* 0x0520 */ f32 unk_520;
    /* 0x0524 */ char unk_524[0x8];
    /* 0x052C */ f32 unk_52C;
    /* 0x0530 */ char unk_530[0xC];
    /* 0x053C */ f32 unk_53C;
    /* 0x0540 */ f32 unk_540;
    /* 0x0544 */ char unk_544[0x4];
    /* 0x0548 */ f32 unk_548;
    /* 0x054C */ char unk_54C[0x18];
    /* 0x0564 */ u8 unk_564;
    /* 0x0568 */ SkelAnime skelAnime;
    /* 0x05AC */ ColliderCylinder collider;
    /* 0x05F8 */ u8 unk_5F8;
    /* 0x05FA */ char unk_5F9[0xBC];
} BossTw; // size = 0x06B4

extern const ActorInit Boss_Tw_InitVars;

#endif
