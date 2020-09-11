#ifndef _Z_BOSS_GANON_H_
#define _Z_BOSS_GANON_H_

#include <ultra64.h>
#include <global.h>

struct BossGanon;

typedef void (*EnBossGannonActionFunc)(struct BossGanon*, GlobalContext*);

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ Color_RGBA8_n unk_28;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
} BossGanonEffects; // size = 0x4C

typedef struct BossGanon {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ s32 unk_14C;
    /* 0x0150 */ SkelAnime skelAnime;
    /* 0x0194 */ EnBossGannonActionFunc actionFunc;
    /* 0x0198 */ u8 unk_198;
    /* 0x0199 */ u8 unk_199;
    /* 0x019A */ u8 unk_19A;
    /* 0x019C */ s16 unk_19C;
    /* 0x019E */ u8 unk_19E;
    /* 0x019E */ u8 unk_19F;
    /* 0x01A0 */ s8 unk_1A0;
    /* 0x01A2 */ s16 unk_1A2;
    /* 0x01A4 */ s16 unk_1A4;
    /* 0x01A6 */ s16 unk_1A6;
    /* 0x01A8 */ s16 unk_1A8;
    /* 0x01AA */ s16 unk_1AA;
    /* 0x01AC */ s16 unk_1AC;
    /* 0x01AE */ s16 unk_1AE;
    /* 0x01B0 */ char unk_1B0[0x6];
    /* 0x01B6 */ s16 unk_1B6[5];
    /* 0x01C0 */ u8 unk_1C0;
    /* 0x01C2 */ s16 unk_1C2;
    /* 0x01C4 */ s16 unk_1C4;
    /* 0x01C8 */ f32 unk_1C8;
    /* 0x01CC */ f32 unk_1CC;
    /* 0x01D0 */ f32 unk_1D0;
    /* 0x01E0 */ f32 unk_1D4[3];
    /* 0x01E0 */ f32 unk_1E0;
    /* 0x01E4 */ f32 unk_1E4;
    /* 0x01E8 */ f32 unk_1E8;
    /* 0x01EC */ char unk_1EC[0x4];
    /* 0x01F0 */ Vec3f unk_1F0;
    /* 0x01FC */ Vec3f unk_1FC;
    /* 0x0208 */ Vec3f unk_208;
    /* 0x0214 */ Vec3f unk_214;
    /* 0x0220 */ Vec3f unk_220;
    /* 0x022C */ Vec3f unk_22C;
    /* 0x0238 */ Vec3f unk_238;
    /* 0x0244 */ char unk_244[0x10];
    /* 0x0254 */ f32 unk_254;
    /* 0x0258 */ f32 unk_258;
    /* 0x025C */ u8 unk_25C;
    /* 0x0260 */ Vec3f unk_260;
    /* 0x026C */ s16 unk_26C;
    /* 0x0270 */ f32 unk_270;
    /* 0x0274 */ u8 unk_274;
    /* 0x0278 */ Vec3f unk_278;
    /* 0x0284 */ f32 unk_284;
    /* 0x0288 */ f32 unk_288;
    /* 0x028C */ f32 unk_28C;
    /* 0x0290 */ f32 unk_290;
    /* 0x0294 */ f32 unk_294[15];
    /* 0x02D0 */ f32 unk_2D0;
    /* 0x02D4 */ s16 unk_2D4;
    /* 0x02D8 */ Vec3f unk_2D8;
    /* 0x02E4 */ u8 unk_2E4;
    /* 0x02E6 */ s16 unk_2E6;
    /* 0x02E8 */ s16 unk_2E8;
    /* 0x02EC */ Vec3f unk_2EC[15];
    /* 0x03A0 */ char unk_3A0[0x24];
    /* 0x03C4 */ Vec3f unk_3C4[15];
    /* 0x0478 */ char unk_478[0x24];
    /* 0x049C */ f32 unk_49C[18];
    /* 0x04E4 */ s16 unk_4E4[18]; // maybe 4E2
    /* 0x0508 */ f32 unk_508;
    /* 0x050C */ f32 unk_50C;
    /* 0x0510 */ f32 unk_510;
    /* 0x0514 */ f32 unk_514;
    /* 0x0518 */ char unk_518[0xF8];
    /* 0x0610 */ ColliderCylinder collider;
    /* 0x065C */ char unk_65C[0x10];
    /* 0x066C */ u8 unk_66C;
    /* 0x066E */ s16 unk_66E;
    /* 0x0670 */ f32 unk_670;
    /* 0x0674 */ u32 unk_674;
    /* 0x0678 */ s16 unk_678;
    /* 0x067A */ s16 unk_67A;
    /* 0x067C */ char unk_67C[0x4];
    /* 0x0680 */ Vec3f unk_680;
    /* 0x068C */ Vec3f unk_68C;
    /* 0x0698 */ char unk_698[0xC];
    /* 0x06A4 */ Vec3f unk_6A4;
    /* 0x06B0 */ Vec3f unk_6B0;
    /* 0x06BC */ Vec3f unk_6BC;
    /* 0x06C8 */ char unk_6C8[0xC];
    /* 0x06D4 */ Vec3f unk_6D4;
    /* 0x06E0 */ char unk_6E0[0xC];
    /* 0x06EC */ f32 unk_6EC;
    /* 0x06F0 */ f32 unk_6F0;
    /* 0x06F4 */ f32 unk_6F4;
    /* 0x06F8 */ char unk_6F8[0xC];
    /* 0x0704 */ f32 unk_704;
    /* 0x0708 */ char unk_708[0x4];
    /* 0x070C */ f32 unk_70C;
    /* 0x0710 */ f32 unk_710;
    /* 0x0714 */ f32 unk_714;
    /* 0x0718 */ s16 organFadeTimer;
    /* 0x071A */ u8 unk_71A;
    /* 0x071B */ u8 unk_71B;
} BossGanon; // size = 0x071C

extern const ActorInit Boss_Ganon_InitVars;

#endif
