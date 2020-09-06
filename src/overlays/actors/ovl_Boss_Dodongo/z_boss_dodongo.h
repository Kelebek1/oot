#ifndef _Z_BOSS_DODONGO_H_
#define _Z_BOSS_DODONGO_H_

#include <ultra64.h>
#include <global.h>

struct BossDodongo;

typedef void (*BossDodongoActionFunc)(struct BossDodongo*, GlobalContext*);

typedef struct {
    /* 0x0000 */ Vec3f a;
    /* 0x000C */ Vec3f b;
    /* 0x0018 */ Vec3f c;
    /* 0x0024 */ u8 unk_24;
    /* 0x0025 */ u8 unk_25;
    /* 0x0026 */ u8 unk_26;
    /* 0x0027 */ u8 unk_27;
    /* 0x0028 */ u8 unk_28;
    /* 0x002A */ s16 unk_2A;
    /* 0x002C */ f32 unk_2C;
} BossDodongoEffect; // size = 0x30

typedef struct BossDodongo {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ BossDodongoActionFunc actionFunc;
    /* 0x0194 */ s16 unk_194;
    /* 0x0196 */ s16 unk_196;
    /* 0x0198 */ s16 unk_198;
    /* 0x019A */ s16 unk_19A;
    /* 0x019C */ s16 unk_19C;
    /* 0x019E */ s16 unk_19E;
    /* 0x01A0 */ s16 unk_1A0;
    /* 0x01A2 */ s16 unk_1A2;
    /* 0x01A4 */ s16 unk_1A4;
    /* 0x01A6 */ s16 unk_1A6;
    /* 0x01A8 */ s16 unk_1A8;
    /* 0x01AA */ s16 unk_1AA;
    /* 0x01AC */ s16 unk_1AC;
    /* 0x01AE */ s16 unk_1AE;
    /* 0x01B0 */ s16 unk_1B0;
    /* 0x01B2 */ char unk_1B2[0x2];
    /* 0x01B4 */ s16 unk_1B4;
    /* 0x01B6 */ s16 unk_1B6;
    /* 0x01B8 */ s16 unk_1B8;
    /* 0x01BA */ s16 unk_1BA;
    /* 0x01BC */ s16 unk_1BC;
    /* 0x01BE */ s16 unk_1BE;
    /* 0x01C0 */ s16 unk_1C0;
    /* 0x01C2 */ s16 unk_1C2;
    /* 0x01C4 */ s16 unk_1C4;
    /* 0x01C6 */ s16 unk_1C6;
    /* 0x01C8 */ s16 unk_1C8;
    /* 0x01CA */ char unk_1CA[0x2];
    /* 0x01CC */ s16 unk_1CC;
    /* 0x01CE */ char unk_1CE[0xC];
    /* 0x01DA */ s16 unk_1DA;
    /* 0x01DC */ s16 unk_1DC;
    /* 0x01DE */ s16 unk_1DE;
    /* 0x01E0 */ char unk_1E0[0x2];
    /* 0x01E2 */ s8 unk_1E2;
    /* 0x01E4 */ f32 unk_1E4;
    /* 0x01E8 */ f32 unk_1E8;
    /* 0x01EC */ f32 unk_1EC;
    /* 0x01F0 */ char unk_1F0[0x8];
    /* 0x01F8 */ f32 unk_1F8;
    /* 0x01FC */ f32 unk_1FC;
    /* 0x0208 */ f32 unk_200;
    /* 0x0204 */ f32 unk_204;
    /* 0x0208 */ f32 unk_208;
    /* 0x020C */ f32 unk_20C;
    /* 0x0210 */ f32 unk_210;
    /* 0x0214 */ f32 unk_214;
    /* 0x0218 */ f32 unk_218;
    /* 0x021C */ f32 unk_21C;
    /* 0x0220 */ f32 unk_220;
    /* 0x0224 */ f32 unk_224;
    /* 0x0228 */ f32 unk_228;
    /* 0x022C */ f32 unk_22C;
    /* 0x0230 */ f32 unk_230;
    /* 0x0234 */ f32 unk_234;
    /* 0x0238 */ f32 unk_238;
    /* 0x023c */ f32 unk_23C;
    /* 0x0240 */ f32 unk_240;
    /* 0x0244 */ f32 unk_244;
    /* 0x0248 */ char unk_248[0x14];
    /* 0x025C */ f32 unk_25C[50];
    /* 0x0324 */ f32 unk_324[50];
    /* 0x03EC */ Vec3f unk_3EC;
    /* 0x03F8 */ Vec3f unk_3F8;
    /* 0x0404 */ Vec3f unk_404;
    /* 0x0410 */ Vec3f unk_410;
    /* 0x041C */ Vec3f unk_41C;
    /* 0x0428 */ Vec3f unk_428;
    /* 0x0434 */ Vec3f unk_434;
    /* 0x0440 */ ColliderJntSph unk_440;
    /* 0x0460 */ ColliderJntSphItem unk_460[19];
    /* 0x0920 */ BossDodongoEffect unk_920[80];
} BossDodongo; // size = 0x1820

extern const ActorInit Boss_Dodongo_InitVars;

#endif
