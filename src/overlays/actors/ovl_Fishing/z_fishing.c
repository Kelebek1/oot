/*
 * File: z_fishing.c
 * Overlay: ovl_Fishing
 * Description: Fishing Pond man and Fish
 */

#include "z_fishing.h"

#define FLAGS 0x00000010

#define THIS ((Fishing*)thisx)

void Fishing_Init(Actor* thisx, GlobalContext* globalCtx);
void Fishing_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Fishing_Update(Actor* thisx, GlobalContext* globalCtx);
void Fishing_Draw(Actor* thisx, GlobalContext* globalCtx);

typedef struct {
    /* 0x00 */ char unk_00[0x24];
    /* 0x24 */u8   unk_24;
    /* 0x25 */char unk_25[0x1B];
} FishingStruct1; // size = 0x40

typedef struct {
    /* 0x00 */char unk_00[0x30];
    /* 0x30 */u8   unk_30;
    /* 0x31 */char unk_31[0xB];
} FishingStruct2; // size = 0x3C

typedef struct {
    /* 0x00 */s8 unk_00;
    /* 0x01 */s8 unk_01;
    /* 0x02 */s16 unk_02;
    /* 0x04 */Vec3f unk_04;
    ///* 0x08 */f32 unk_08;
    ///* 0x0C */f32 unk_0C;
    /* 0x10 */Vec3f unk_10;
    ///* 0x14 */f32 unk_14;
    ///* 0x18 */f32 unk_18;
    /* 0x1C */char unk_1C[0x20];
    /* 0x3C */s16 unk_3C;
    /* 0x3E */s16 unk_3E;
    /* 0x40 */s16 unk_40;
    /* 0x42 */char unk_42[0x6];
} FishingStruct3; // size = 0x48


extern AnimationHeader  D_0600007C;
extern SkeletonHeader   D_060029C0;
extern AnimationHeader  D_0600453C;
extern SkeletonHeader   D_060085F8;
extern AnimationHeader  D_0600CFE0;
extern SkeletonHeader   D_06011058;

static Fishing*         D_80B7E070;
static u8               D_80B7E074;
static u8               D_80B7E075;
static u8               D_80B7E076;
static u8               D_80B7E077;
static f32              D_80B7E078;
static u8               D_80B7E07C;
static u8               D_80B7E07D;
static s8               D_80B7E07E;
static s16              D_80B7E080;
static u16              D_80B7E084;
static s16              D_80B7E086;
static s8               D_80B7E088;
static s16              D_80B7E0A4;
static s16              D_80B7E0A6;
static Fishing*         D_80B7E0A8;
static s16              D_80B7E0AC;
static s16              D_80B7E0AE;
static s16              D_80B7E0B0;
static s16              D_80B7E0B2;
static u8               D_80B7E0B6;
static Vec3f            D_80B7E0B8;
static Vec3f            D_80B7E0DC;
static s16              D_80B7E116;
static u8               D_80B7E118;
static f32              D_80B7E11C;
static s16              D_80B7E120;
static s16              D_80B7E122;
static u8               D_80B7E124;
static f32              D_80B7E144;
static f32              D_80B7E148;
static Vec3f            D_80B7E168[0xC8];
static Vec3f            D_80B7EAC8[0xC8];
static Vec3f            D_80B7F428[0xC8];
static s32              D_80B7FDA8;
static s16              D_80B7FEA0;
static Vec3f            D_80B7FEA8;
static Vec3f            D_80B7FEB8;
static s32              D_80B7FEC4;
static f32              D_80B7FEC8;
static f32              D_80B7FED0;
static FishingStruct2   D_80B7FEF8[0x8C];
static FishingStruct3   D_80B81FC8[0x3C];
static Vec3f            D_80B830A8;
static FishingStruct1   D_80B830B8[0x82];

const ActorInit Fishing_InitVars = {
    ACTOR_FISHING,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_FISH,
    sizeof(Fishing),
    (ActorFunc)Fishing_Init,
    (ActorFunc)Fishing_Destroy,
    (ActorFunc)Fishing_Update,
    (ActorFunc)Fishing_Draw,
};

f32 D_80B7A650 = 0.0f;
u16 D_80B7A684 = 0x00;
u8  D_80B7A688 = 0x00;
s16 D_80B7A694 = 0x00;
f32 D_80B7A69C = 0.0f;
f32 D_80B7A6BC = 0.0f;
f32 D_80B7A6C0 = 0.0f;
s8 D_80B7A6CC = 0;


ColliderJntSphItemInit D_80B7A6D8[12] = {
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    }
};

ColliderJntSphInit D_80B7A888 =
{
    { COLTYPE_UNK10, 0x10, 0x08, 0x09, 0x10, COLSHAPE_JNTSPH },
    12, D_80B7A6D8,
};

f32 D_80B7A898 = 0;
f32 D_80B7A670 = 0;
u16 D_80B7A678 = 0;
s8  D_80B7A67C = 0;
s16 D_80B7A6C8 = 0;

typedef struct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s32 unk_08;
    f32 unk_0C;
} FishingStruct10; // size = 0x10;

FishingStruct10 D_80B7AD40[] = {
    {0x0000, 0x029A, 0xFFD3, 0x0162, 0x26000000, 0.10000000149f}, 
    {0x0000, 0x02A9, 0xFFD3, 0x00F0, 0x24000000, 0.10000000149f}, 
    {0x0000, 0x029E, 0xFFD3, 0x005A, 0x29000000, 0.0500000007451f}, 
    {0x0000, 0x0267, 0xFFD3, 0xFE3E, 0x23000000, 0.20000000298f}, 
    {0x0000, 0x01F4, 0xFFD3, 0xFE5C, 0x27000000, 0.10000000149f}, 
    {0x0000, 0x01A4, 0xFFD3, 0xFDDA, 0x2C000000, 0.0500000007451f}, 
    {0x0000, 0xFEF8, 0xFFD3, 0xFD80, 0x28000000, 0.10000000149f}, 
    {0x0000, 0xFE2A, 0xFFD3, 0xFDE4, 0x22000000, 0.20000000298f}, 
    {0x0000, 0xFDD3, 0xFFD3, 0xFE52, 0x36000000, 0.00999999977648f}, 
    {0x0000, 0xFEFC, 0xFFC4, 0xFEB6, 0x2F000000, 0.0500000007451f}, 
    {0x0000, 0xFE0C, 0xFFC4, 0x014A, 0x2A000000, 0.0599999986589f}, 
    {0x0000, 0x01AC, 0xFFD8, 0xFEE5, 0x21000000, 0.20000000298f}, 
    {0x0000, 0x0199, 0xFFBA, 0xFF1A, 0x39000000, 0.0f}, 
    {0x0000, 0x01C2, 0xFFBD, 0xFED4, 0x3F000000, 0.0f}, 
    {0x0000, 0xFF78, 0xFFBF, 0xFF3C, 0x47000000, 0.0f}, 
    {0x0100, 0xFDCF, 0xFFDD, 0xFDDD, 0x2D000000, 0.0f}, 
    {0x0100, 0x029B, 0xFFDD, 0x013D, 0x2B000000, 0.0f}
};

InitChainEntry D_80B7AE50[] = {
    ICHAIN_U8(unk_1F, 5, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 0, ICHAIN_STOP),
};



#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B699A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B69A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B69A60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B69B84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B69C2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B69D88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B69ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6A008.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6A138.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6A22C.s")

//#define A

void func_80B7825C(Actor*, GlobalContext*);
void func_80B7A278(Actor*, GlobalContext*);
void func_80B6A22C(Fishing*, GlobalContext*);

#ifdef A
void Fishing_Init(Actor* thisx, GlobalContext* globalCtx) {
    Fishing* this = THIS;
    FishingStruct3* fish1;
    FishingStruct10* fish2;
    s32 tmp;
    f32 tmpf;
    s16 i;

    Actor_ProcessInitChain(&this->actor, D_80B7AE50);
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    if (KREG(5) != 0) {
        D_80B7E075 = 1;
    } else {
        D_80B7E075 = gSaveContext.linkAge;
    }
    if (this->actor.params < 0x64) {
        D_80B7E074 = 0;
        D_80B7E070 = this;
        Collider_InitJntSph(globalCtx, &D_80B7E070->unk_230);
        Collider_SetJntSph(globalCtx, &D_80B7E070->unk_230, &this->actor, &D_80B7A888, &this->unk_250);
        this->actor.params = 1;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060085F8, &D_0600453C, NULL, NULL, 0);
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_0600453C, 0.0f);
        this->actor.update = func_80B7825C;
        this->actor.draw = func_80B7A278;
        this->actor.shape.rot.y = -0x6000;
        this->actor.posRot.pos.x = 160.0f;
        this->actor.posRot.pos.y = -2.0f;
        this->actor.posRot.pos.z = 1208.0f;
        Actor_SetScale(&this->actor, 0.011f);
        this->actor.posRot2.pos = this->actor.posRot.pos;
        this->actor.posRot2.pos.y += 75.0f;
        this->actor.flags |= 9;
        
        if (D_80B7E075 != 1) {
            if (gSaveContext.unk_EC0 & 0x1000) {
                D_80B7A688 = 0;
            } else {
                D_80B7A688 = 1;
            }
        } else {
            D_80B7A688 = 2;
        }
        D_80B7A684 = 0x14;
        globalCtx->unk_11E10 = D_80B830B8;
        D_8011FB40 = 1;
        D_80B7E0AC = 0;
        D_80B7E0A6 = 10;
        Audio_SetBGM(0x100100FF);
        if (D_80B7E075 == 1) {
            tmp = gSaveContext.unk_EC0 & 0x7F;
            if (tmp) {
                D_80B7E078 = tmp;
            } else {
                D_80B7E078 = 40.0f;
            }
        } else {
            tmp = gSaveContext.unk_EC0 & 0x7F000000;
            if (tmp) {
                D_80B7E078 = tmp >> 0x18;
            } else {
                D_80B7E078 = 45.0f;
            }
        }
        tmp = (gSaveContext.unk_EC0 & 0xFF0000) >> 0x10;
        D_80B7E07D = tmp;
        if ((tmp & 7) == 7) {
            globalCtx->unk_11D30[0] = 0x5A;
            D_80B7E076 = 1;
        } else {
            globalCtx->unk_11D30[0] = 0x28;
            D_80B7E076 = 0;
        }
        if (((D_80B7E07D & 7) == 6) || KREG(3)) {
            D_80B7E077 = 0x64;
            if (KREG(3) != 0) {
                KREG(3) = 0;
                gSaveContext.unk_EC0 &= 0xFF00FFFF;
                gSaveContext.unk_EC0 |= 0x60000;
            }
        } else {
            D_80B7E077 = 0;
        }
        
        for (i = 0; i < 0x82; i++) {
            D_80B830B8[i].unk_24 = 0;
        }

        for (i = 0; i < 0x8C; i++) {
            D_80B7FEF8[i].unk_30 = 0;
        }

        D_80B830A8.x = 0.7f;
        D_80B830A8.y = 2.3f;
        D_80B830A8.z = 4.6f;

        for (i = 0; i < 0x3C; i++) {
            fish1 = &D_80B81FC8[i];
            fish1->unk_00 = 1;
            if (i < 0x15) {
                tmpf = sinf(D_80B830A8.x) * 720.0f;
                fish1->unk_04.x = tmpf;
                fish1->unk_10.x = tmpf;
                tmpf = cosf(D_80B830A8.x) * 720.0f;
                fish1->unk_04.z = tmpf;
                fish1->unk_10.z = tmpf;
            } else if (i < 0x29) {
                tmpf = sinf(D_80B830A8.y) * 720.0f;
                fish1->unk_04.x = tmpf;
                fish1->unk_10.x = tmpf;
                tmpf = cosf(D_80B830A8.y) * 720.0f;
                fish1->unk_04.z = tmpf;
                fish1->unk_10.z = tmpf;
            } else {
                tmpf = sinf(D_80B830A8.z) * 720.0f;
                fish1->unk_04.x = tmpf;
                fish1->unk_10.x = tmpf;
                tmpf = cosf(D_80B830A8.z) * 720.0f;
                fish1->unk_04.z = tmpf;
                fish1->unk_10.z = tmpf;
            }
            

            fish1->unk_08 = -35.0f;
            fish1->unk_14 = -35.0f;
            
            fish1->unk_02 = Math_Rand_ZeroFloat(100.0f);

            fish1->unk_3C = 0;
            fish1->unk_3E = 0;
            fish1->unk_40 = 0;

            if ((D_80B7E075 != 1) && 
               ((((i >= 0xF) && (i < 0x14)) || ((i >= 0x23) && (i < 0x28))) || 
                 ((i >= 0x37) && (i < 0x3C)))) {
                    fish1->unk_00 = 0;
            }
        }

        func_80B6A22C(this, globalCtx);

        Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_KANBAN, 
            53.0f, -17.0f, 982.0f, 0, 0, 0, 0x300);
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_FISHING, 
            0.0f, 0.0f, 0.0f, 0, 0, 0, 0xC8);

        
        if ((KREG(1) == 1) || ((D_80B7E07D & 3) == 3)) {
            if (D_80B7E075 != 1) {
                tmp = 0x10;
                
            } else {
                tmp = 0x11;
            }
        } else {
            tmp = 0xF;
        }
        for (i = 0; i < tmp; i++) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xFE, 
                D_80B7AD40[i].unk_02, 
                D_80B7AD40[i].unk_04, 
                D_80B7AD40[i].unk_06, 
                0, Math_Rand_ZeroFloat(65536.0f), 0, i + 100);
        }
    } else {
        if ((this->actor.params < 0x73) || (this->actor.params == 0xC8)) {
            SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060029C0, &D_0600007C, NULL, NULL, 0);
            SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_0600007C, 0.0f);
        } else {
            SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06011058, &D_0600CFE0, NULL, NULL, 0);
            SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_0600CFE0, 0.0f);
        }
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        if (this->actor.params == 0xC8) {
            this->unk_158 = 0x64;
            Actor_ChangeType(globalCtx, &globalCtx->actorCtx, &this->actor, 6);
            this->actor.unk_1F = 0;
            this->actor.flags |= 9;
            this->unk_21C = Lights_Insert(globalCtx, &globalCtx->lightCtx, &this->unk_220);
            return;
        }
        this->unk_158 = 10;
        this->unk_15A = 10;
        // Very wrong
        // this->unk_150 = D_80B7A6D8[this->actor.params].body.toucher.flags;
        // this->unk_1A8 = D_80B7A6D8[this->actor.params].body.bumper.effect;
        // this->unk_1AC = D_80B7A6D8[this->actor.params].body.bumper.flags;

        this->unk_1AC += Math_Rand_ZeroFloat(4.99999f);
        if (this->unk_1AC >= 65.0f) {
            if (Math_Rand_ZeroOne() < 0.05f) {
                this->unk_1AC = this->unk_1AC + Math_Rand_ZeroFloat(7.99999f);
            }
        }
        if (KREG(6) != 0) {
            this->unk_1AC = KREG(6) + 80.0f;
        }
        if (D_80B7E075 == 1) {
            this->unk_1AC *= 0.73f;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/Fishing_Init.s")
#endif
#undef A

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/Fishing_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6AF28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6B674.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6C134.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6C2EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6C3E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6C960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6CAF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6D054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6D354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6D688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6DF30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B6E9E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B70A2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B70CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B70ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B71278.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B71438.s")

#define A

void func_80B71278(Fishing*, s32);
void func_80B71438(Fishing*, GlobalContext*);
s32 func_80B70A2C(Fishing*, GlobalContext*, s32);
void func_80B70CF0(Fishing*, GlobalContext*);
s16 func_80B69B84(f32*, f32, s16, s16);
// func_80B69ED0(&this->actor.projectedPos, (FishingStruct1*)globalCtx->unk_11E10, &spC4, (this->unk_1AC * 0.005f) + 0.15f);
void func_80B69ED0(Vec3f*, FishingStruct1*, Vec3f*, f32);
void func_80B6A008(Fishing*, FishingStruct1*, Vec3f*, f32, s32);
void func_80B69C2C(Vec3f*, FishingStruct1*, Vec3f*, f32, f32, s32, s32);
void func_80B70ED4(Fishing*, Input*);

#ifdef A
void Fishing_Update(Actor* thisx, GlobalContext* globalCtx) {
    Fishing* this = THIS;
    FishingStruct3* fish1;
    Player* player;
    Input* cont;
    s16 sp134 = 10;
    f32 sp124;
    Vec3f sp118;
    s16 spFC;
    s16 spFE;
    Vec3f spC4;
    Vec3f spB8;
    

    s16 i;
    u16 j;
    u8 tmp8;
    s32 tmp1;
    s16 tmp14;
    s16 tmp15;
    s16 tmp16;
    s16 tmp17;
    s16 tmp18;
    s16 tmp19;
    s16 tmp20;
    f32 tmpf1;
    f32 tmpf2;
    f32 tmpf3;
    f32 tmpf4;
    f32 tmpf5;
    f32 tmpf6;
    f32* tmpfp1;
    f32* tmpfp2;
    f32* tmpfp3;
    


    this->actor.uncullZoneForward = 700.0f;
    this->actor.uncullZoneScale = 50.0f;

    if (this->unk_150 == 0) {
        sp118.x = (PLAYER->actor.speedXZ * 0.15f) + 0.25f;
    } else {
        sp118.x = (PLAYER->actor.speedXZ * 0.3f) + 0.25f;
    }

    if (((D_80B7E0B0 != 0) || (D_80B7FEC4 != 0)) || 
        ((PLAYER->actor.posRot.pos.z > 1150.0f) && (this->unk_158 != 0x64))) {
        this->actor.flags &= -2;
    } else {
        this->actor.flags |= 1;
        if (D_80B7A694 != 0) {
            if (D_80B7E0B2 == 0) {
                this->actor.posRot2.pos = D_80B7E0B8;
            } else {
                if (D_80B7E0B2 == 1) {
                    D_80B7A6CC = 1;
                    D_80B7FED0 = 0.0f;
                    D_80B7E088 = 2;
                }
            }
        }
        this->actor.posRot2.pos = this->actor.posRot.pos;
    }

    this->unk_15C++;
    for (i = 0; i < 4; i++) {
        if (this->unk_17A[i]) {
            this->unk_17A[i]--;
        }
    }

    if (this->unk_1A4) {
        this->unk_1A4--;
    }
    if (this->unk_1A2) {
        this->unk_1A2--;
    }
    if (this->unk_1A0) {
        this->unk_1A0--;
    }
    if (this->unk_151) {
        this->unk_151--;
    }

    player = PLAYER;
    Math_SmoothScaleMaxF(&this->unk_198, this->unk_190, 1.0f, 0.2f);
    if (this->unk_158 == 6) {
        Math_SmoothScaleMaxF(&this->unk_19C, this->unk_194, 0.2f, 200.0f);
    } else {
        tmpf1 = 1.0f;
        tmpf2 = 1.0f;
        if (globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 < this->actor.posRot.pos.y) {
            tmpf1 = (KREG(64) * 0.1f) + 1.5f;
            tmpf2 = 3.0f;
        }
        Math_SmoothScaleMaxF(&this->unk_19C, this->unk_194 * tmpf1, 1.0f, 500.0f * tmpf2);
    }
    Math_SmoothScaleMaxS(&this->unk_170, 0, 5, 0x1F4);
    if (this->unk_150 == 0) {
        Actor_SetScale(&this->actor, (this->unk_1AC * 15.0f) * 0.00001f);
        this->unk_18C += this->unk_198;
        this->unk_16C = this->unk_16E + (s16)(cosf(this->unk_18C) * this->unk_19C);
        this->unk_176 = this->unk_16E + (s16)((cosf(this->unk_18C + -1.2f) * this->unk_19C) * 1.6f);
    } else {
        Actor_SetScale(&this->actor, (this->unk_1AC * 65.0f) * 0.000001f);
        this->actor.scale.x = this->actor.scale.z * 1.1f;
        this->actor.scale.y = this->actor.scale.z * 1.1f;
        this->unk_18C += (this->unk_198 * 0.8f);
        
        for (i = 0; i < 3; i++) {
            tmpf1 = cosf(this->unk_18C + (i * 2.1f)) * this->unk_19C;
            this->unk_1CC[i] = this->unk_16E + (s16)(tmpf1 + tmpf1);
        }
        tmpf1 = this->unk_19C * cosf(this->unk_18C + 0.4f);
        this->unk_16C = (s16)((tmpf1 + tmpf1) * 0.6f);
    }

    tmpf1 = this->unk_1B4.x - this->actor.posRot.pos.x;
    tmpf2 = this->unk_1B4.y - this->actor.posRot.pos.y;
    tmpf3 = this->unk_1B4.z - this->actor.posRot.pos.z;
    spFC = atan2s(tmpf3, tmpf1);
    tmpf6 = (f32)(tmpf1 * tmpf1) + (tmpf3 * tmpf3);
    tmpf1 = sqrtf(tmpf6);
    spFE = atan2s(tmpf1, tmpf2);
    sp124 = sqrtf(tmpf6 + (f32)(tmpf2 * tmpf2));

    if ((this->unk_1A0 != 0) && (this->unk_158 != 2) && 
       (this->unk_158 != 3) && (this->unk_158 != 4)) {
            if (this->unk_15C & 0x40) {
                spFC += 0x4000;
            } else {
                spFC -= 0x4000;
            }
            if ((this->unk_15C + 0x20) & 0x40) {
                spFE += 0x2000;
            } else {
                spFE -= 0x2000;
            }
    }
    
    switch (this->unk_158) {
        case 0x64:
            func_80B71438(this, globalCtx);
            this->actor.uncullZoneForward = 500.0f;
            this->actor.uncullZoneScale = 300.0f;
            Lights_InitType0PositionalLight(&this->unk_220, (s16)this->actor.posRot.pos.y + 0, (s16)this->actor.posRot.pos.y + 20.0f, (s16)this->actor.posRot.pos.z - 50.0f, 0xFF, 0xFF, 0xFF, 0xFF);
            this->unk_1AC = D_80B7E078;
            tmpf1 = Math_Sins((((((((globalCtx->gameplayFrames * 4) + globalCtx->gameplayFrames) * 4) - globalCtx->gameplayFrames) * 4) - globalCtx->gameplayFrames) * 4)) * 1;
            tmpf2 = Math_Sins((((((((globalCtx->gameplayFrames * 8) - globalCtx->gameplayFrames) * 4) + globalCtx->gameplayFrames) * 4) - globalCtx->gameplayFrames) * 2)) * 2;
            this->actor.posRot.pos.x = 130.0f;
            this->actor.posRot.pos.y = 55.0f + tmpf1;
            this->actor.shape.rot.y = -0x8000;
            this->actor.posRot.pos.z = 1300.0f + tmpf2;
            if ((this->actor.projectedPos.z < 200.0f) && (this->actor.projectedPos.z > 0.0f)) {
                spC4.x = Math_Rand_CenteredFloat(5.0f) + 130.0f;
                spC4.y = 40.0f;
                spC4.z = Math_Rand_CenteredFloat(5.0f) + 1280.0f;
                func_80B6A008(NULL, (FishingStruct1*)globalCtx->unk_11E10, &spC4, Math_Rand_ZeroFloat(0.02f) + 0.03f, 1);
            }
            Math_SmoothScaleMaxS(&this->unk_172, (Math_Sins(this->unk_15C * 2048) * 2500.0f) + 2500.0f, 2, 0x7D0);
            Math_SmoothScaleMaxS(&this->unk_174, Math_Sins((this->unk_15C * 5) * 512) * 1500.0f, 2, 0x7D0);
            this->unk_190 = 0.3f;
            this->unk_194 = 333.33334f;
            return;
        case 10:
            this->unk_1B4 = this->actor.initPosRot.pos;
            Math_SmoothScaleMaxF(&this->actor.speedXZ, 2.0f, 1.0f, 0.5f);
            Math_SmoothScaleMaxF(&this->unk_1B0, 4096.0f, 1.0f, 256.0f);
            if (sp124 < 40.0f) {
                this->unk_158 = 0xB;
                this->unk_190 = 0.4f;
                this->unk_194 = 500.0f;
            }
            func_80B70ED4(this, &globalCtx->state.input[0]);
            if (this->actor.xzDistFromLink < (250.0f * sp118.x)) {
                this->unk_158 = 0;
                this->unk_1A4 = 0x3E8;
                this->unk_1A2 = 0xC8;
                this->unk_17A[1] = 0x32;
                this->unk_15A = this->unk_158;
            }
            break;
        case 11:
            this->unk_1B4 = this->actor.initPosRot.pos;
            Math_SmoothScaleMaxF(&this->actor.speedXZ, 0.0f, 1.0f, 0.05f);
            Math_SmoothScaleMaxF(&this->unk_1B0, 0.0f, 1.0f, 256.0f);
            if (sp124 >= 40.0f ) {
                this->unk_158 = 0xA;
                this->unk_190 = 1.0f;
                this->unk_194 = 2000.0f;
            }
            func_80B70ED4(this, &globalCtx->state.input[0]);
            if (this->actor.xzDistFromLink < (250.0f * sp118.x)) {
                this->unk_158 = 0;
                this->unk_1A4 = 0x3E8;
                this->unk_1A2 = 0xC8;
                this->unk_17A[1] = 0x32;
                this->unk_15A = this->unk_158;
            }
            if (!func_8010BDBC(&globalCtx->msgCtx)) {
                if ((gSaveContext.dayTime >= 0xC000) && (gSaveContext.dayTime < 0xC01C)) {
                    this->unk_158 = 7;
                    this->unk_17A[3] = (s32)Math_Rand_ZeroFloat(150.0f) + 0xC8;
                }
                if ((gSaveContext.dayTime >= 0x3AAA) && (gSaveContext.dayTime < 0x3AC6)) {
                    this->unk_158 = 7;
                    this->unk_17A[3] = (s32)Math_Rand_ZeroFloat(150.0f) + 0xC8;
                }
            }
            if (KREG(15)) {
                KREG(15) = 0;
                this->unk_158 = 7;
                this->unk_17A[3] = (s32)Math_Rand_ZeroFloat(150.0f) + 0x7D0;
            }
            break;
        case 0:
            Math_SmoothScaleMaxF(&this->actor.speedXZ, 1.0f, 1.0f, 0.05f);
            Math_SmoothScaleMaxF(&this->unk_1B0, 0.0f, 1.0f, 256.0f);
            if (this->unk_17A == 0) {
                if (this->unk_1A4 == 0) {
                    this->unk_15A = 0xA;
                    this->unk_158 = this->unk_15A;
                } else {
                    this->unk_158 = 1;
                    this->unk_17A[0] = (s32)Math_Rand_ZeroFloat(30.0f) + 10;
                    this->unk_1B4.x = Math_Rand_CenteredFloat(300);
                    this->unk_1B4.y = (globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 - 50.0f) - Math_Rand_ZeroFloat(50.0f);
                    this->unk_1B4.z = Math_Rand_CenteredFloat(300.0f);
                    this->unk_190 = 1.0f;
                    this->unk_194 = 2000.0f;
                }
            }
            if (D_80B7E0B6 == 2) {
                func_80B70ED4(this, &globalCtx->state.input[0]);
            } else {
                this->actor.flags &= -2;
            }
            break;
        case 1:
            if (this->unk_150 == 1) {
                this->unk_158 = -1;
                this->unk_1A4 = 0x4E20;
                this->unk_1A2 = 0x4E20;
                this->unk_1B4.x = 0.0f;
                this->unk_1B4.y = -140.0f;
                this->unk_1B4.z = 0;
            } else {
                Math_SmoothScaleMaxF(&this->unk_1B0, 4096.0f, 1.0f, 256.0f);
                if ((this->actor.xzDistFromLink < (250.0f * sp118.x)) || this->unk_17A[1]) {
                    Math_SmoothScaleMaxF(&this->unk_1B0, 8192.0f, 1.0f, 768.0f);
                    Math_SmoothScaleMaxF(&this->actor.speedXZ, 4.2f, 1.0f, 0.75f);
                    this->unk_17A[0] = 0x14;
                    this->unk_190 = 1.2f;
                    this->unk_194 = 4000.0f;
                } else {
                    this->unk_190 = 1.0f;
                    this->unk_194 = 2000.0f;
                    Math_SmoothScaleMaxF(&this->actor.speedXZ, 1.5f, 1.0f, 0.1f);
                }
                if ((this->unk_17A[0] == 0) || (sp124 < 50.0f)) {
                    this->unk_158 = 0;
                    this->unk_190 = 1.0f;
                    this->unk_194 = 500.0f;
                    this->unk_17A[0] = (s16)Math_Rand_ZeroFloat(30.0f) + 3;
                }
                if (D_80B7E0B6 == 2) {
                    func_80B70ED4(this, &globalCtx->state.input[0]);
                } else {
                    this->actor.flags &= -2;
                }
            }
            break;
        case -1:
            Math_SmoothScaleMaxS(&this->unk_166, 0, 0x14, 0x20);
            if ((this->actor.xzDistFromLink < (250.0f * sp118.x)) || this->unk_17A[1]) {
                Math_SmoothScaleMaxF(&this->actor.speedXZ, 3.0f, 1.0f, 0.75f);
                this->unk_190 = 1.0f;
                this->unk_17A[0] = 0x14;
                this->unk_194 = 4000.0f;
                Math_SmoothScaleMaxF(&this->unk_1B0, 4096.0f, 1.0f, 256.0f);
                if ((globalCtx->gameplayFrames & 0x1F) == 0) {
                    this->unk_1B4.x = Math_Rand_CenteredFloat(600.0f);
                    this->unk_1B4.y = -120.0f;
                    this->unk_1B4.z = Math_Rand_CenteredFloat(600.0f);
                }
            } else {
                if (sp124 > 50.0f) {
                    this->unk_190 = 0.8f;
                    this->unk_194 = 1500.0f;
                    Math_SmoothScaleMaxF(&this->actor.speedXZ, 1.0f, 1.0f, 0.1f);
                    Math_SmoothScaleMaxF(&this->unk_1B0, 2048.0f, 1.0f, 128.0f);
                } else {
                    this->unk_190 = 0.4f;
                    this->unk_194 = 500.0f;
                    Math_SmoothDownscaleMaxF(&this->actor.speedXZ, 1.0f, 0.02f);
                    Math_SmoothScaleMaxF(&this->unk_1B0, 0.0f, 1.0f, 256.0f);
                }
            }
            if (this->unk_1A4 == 0) {
                this->unk_158 = 10;
                this->unk_15A = 10;
            } else {
                if (KREG(2) || (((this->unk_1A4 & 0x7FF) == 0) && (this->unk_1A4 < 0x3A98))) {
                    KREG(2) = 0;
                    this->actor.shape.rot.x = 0;
                    this->unk_158 = -2;
                    this->actor.posRot.rot.x = this->actor.shape.rot.x;
                    this->unk_1B4.y = globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 + 10.0f;
                    this->unk_1B4.x = Math_Rand_ZeroFloat(50.0f);
                    this->unk_1B4.z = Math_Rand_ZeroFloat(50.0f);
                }
            }
            this->actor.flags &= -2;
            break;
        case -2:
            if ((this->actor.xzDistFromLink < (250.0f * sp118.x)) || this->unk_17A[1]) {
                this->unk_158 = -1;
                this->unk_1B4.y = -120.0f;
            } else {
                this->unk_190 = 0.6f;
                this->unk_194 = 1000.0f;
                Math_SmoothScaleMaxS(&this->unk_166, -0x1000, 0x14, 0x100);
                if (this->actor.posRot.pos.y < (globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 - 20.0f)) {
                    Math_SmoothScaleMaxF(&this->actor.speedXZ, 0.5f, 1.0f, 0.1f);
                } else {
                    Math_SmoothDownscaleMaxF(&this->actor.speedXZ, 1.0f, 0.01f);
                    if ((this->actor.speedXZ == 0.0f) || ((globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 - 5.0f) < this->actor.posRot.pos.y)) {
                        this->unk_1B4.x = Math_Rand_ZeroFloat(300.0f);
                        this->unk_1B4.z = Math_Rand_ZeroFloat(300.0f);
                        this->unk_1B4.y = this->actor.groundY + 10.0f;
                        this->unk_158 = -0x19;
                        this->unk_1B0 = 0.0f;
                        spB8 = this->unk_1C0;
                        spB8.y = globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02;
                        func_80B69C2C(&this->actor.projectedPos, (FishingStruct1*)globalCtx->unk_11E10, &spB8, 10.0f, 300.0f, 0x96, 0x5A);
                        func_80B69C2C(&this->actor.projectedPos, (FishingStruct1*)globalCtx->unk_11E10, &spB8, 30.0f, 400.0f, 0x96, 0x5A);
                        Audio_PlayActorSound2(&this->actor, NA_SE_PL_CATCH_BOOMERANG);
                        return;
                    }
                }
                Math_SmoothScaleMaxF(&this->unk_1B0, 2048.0f, 1.0f, 128.0f);
                this->actor.flags &= -2;
            }
            break;
        case -25:
            if ((this->actor.xzDistFromLink < (250.0f * sp118.x)) || this->unk_17A[1]) {
                this->unk_158 = -1;
                this->unk_1B4.y = -120.0f;
            } else {
                Math_SmoothScaleMaxS(&this->unk_166, 0x1000, 0x14, 0x6A);
                if (sp124 > 40.0f) {
                    this->unk_190 = 0.7f;
                    this->unk_194 = 1200.0f;
                    Math_SmoothScaleMaxF(&this->actor.speedXZ, 0.5f, 1.0f, 0.01f);
                    Math_SmoothScaleMaxF(&this->unk_1B0, 2048.0f, 1.0f, 128.0f);
                } else {
                    this->unk_158 = -1;
                }
            }
            break;
        case 2:
            if ((D_80B7E118 + this->actor.params) & 1) {
                spC4.z = 10.0f;
            } else {
                spC4.z = -10.0f;
            }
            spC4.x = 0.0f;
            spC4.y = 0.0f;
            Matrix_RotateY(D_80B7E0DC.y, 0);
            Matrix_MultVec3f(&spC4, &spB8);
            this->unk_1B4.x = D_80B7E0B8.x + spB8.x;
            this->unk_1B4.z = D_80B7E0B8.z + spB8.z;
            if (D_80B7E0B6 == 2) {
                this->unk_1B4.y = D_80B7E0B8.y;
            } else {
                if (this->unk_150 == 0) {
                    this->unk_1B4.y = D_80B7E0B8.y - 15.0f;
                } else {
                    this->unk_1B4.y = D_80B7E0B8.y - 5.0f;
                }
            }
            if (this->unk_1B4.y <= this->actor.groundY) {
                this->unk_1B4.y = this->actor.groundY + 3.0f;
            }
            if (D_80B7E0B6 != 2) {
                if (this->unk_1B4.y < this->actor.posRot.pos.y) {
                    Math_SmoothScaleMaxF(&this->actor.posRot.pos.y, this->unk_1B4.y, 0.1f, (this->actor.posRot.pos.y - this->unk_1B4.y) * 0.1f);
                }
            }
            Math_SmoothScaleMaxF(&this->unk_1B0, 8192.0f, 1.0f, (KREG(16) * 128) + 384.0f);
            cont = &globalCtx->state.input[0];
            if (!CHECK_PAD(cont->press, A_BUTTON)) {
                this->unk_1A8 += 0.005f;
            }
            if (D_80B7E120) {
                if (D_80B7E120 == 1) {
                    this->unk_1A8 += 0.01f;
                } else {
                    this->unk_1A8 += 0.05f;
                }
                D_80B7E120 = 0;
            }
            if (CHECK_PAD(cont->press, B_BUTTON)) {
                this->unk_1A8 += 0.008f;
            }
            if (sp124 < ((this->unk_1AC * 0.5f) + 20.0f)) {
                if (this->unk_15E == 0) {
                    this->unk_190 = 1.0f;
                    this->unk_194 = 500.0f;
                    this->unk_17A[0] = (s32)Math_Rand_ZeroFloat(10.0f) + 2;
                }
                Math_SmoothScaleMaxF(&this->actor.speedXZ, -0.2f, 1.0f, 0.1f);
                this->unk_15E = 1;
            } else {
                if (this->unk_15E) {
                    this->unk_190 = 1.0f;
                    this->unk_1B0 = 0.0f;
                    this->unk_194 = 3000.0f;
                }
                Math_SmoothScaleMaxF(&this->actor.speedXZ, 3.0f, 1.0f, 0.15f);
                this->unk_15E = 0;
            }
            if (this->unk_1AC >= 60.0f) {
                tmpf1 = 0.3f;
            } else if (this->unk_1AC >= 45.0f) {
                tmpf1 = 0.6f;
            } else {
                tmpf1 = 1.0f;
            }
            if ((gSaveContext.dayTime >= 0xB555) && (gSaveContext.dayTime < 0xCAAB)) {
                tmpf1 *= 1.75f;
            } else if ((gSaveContext.dayTime >= 0x3555) && (gSaveContext.dayTime < 0x4AAB)) {
                tmpf1 *= 1.5f;
            } else if (D_80B7E076) {
                tmpf1 *= 1.5f;
            } else {
                if ((u8)D_80B7A650 != 0) {
                    tmpf1 *= 3.0f;
                }
            }
            tmpf1 *= 0.03f;
            if (D_80B7E0B6 == 2) {
                tmpf1 *= 5.0f;
            }
            if (this->unk_17A[0] != 1) {
                sp118.z = tmpf2;
                sp118.y = tmpf1;
                if (Math_Rand_ZeroOne() < tmpf1) {
                    sp118.z = tmpf2;
                    if ((Math_Rand_ZeroOne() < (this->unk_1A8 * tmpf2)) || ((this->unk_150 + 1) == KREG(69))) {
                        if (this->unk_150 == 0) {
                            this->unk_158 = 3;
                            this->unk_190 = 1.2f;
                            this->unk_194 = 5000.0f;
                            this->unk_17A[0] = (s32)Math_Rand_ZeroFloat(10.0f);
                        } else {
                            this->unk_158 = -3;
                            this->unk_190 = 1.0f;
                            this->unk_17A[0] = 0x28;
                            this->unk_194 = 3000.0f;
                        }
                        if (D_80B7E0B6 == 2) {
                            this->unk_188 = Math_Rand_ZeroFloat(1.5f) + 3.0f;
                        } else {
                            this->unk_188 = Math_Rand_ZeroFloat(1.5f) + 4.5f;
                        }
                    }
                }
            }
            if (!((D_80B7A694 == 3) && this->unk_17A[2]) || (sqrtf((this->actor.posRot.pos.x * this->actor.posRot.pos.x) + (this->actor.posRot.pos.z * this->actor.posRot.pos.z)) > 800.0f)) {
                this->unk_158 = this->unk_15A;
                this->unk_17A[1] = (s32)Math_Rand_ZeroFloat(30.0f) + 0x32;
                this->unk_17A[0] = (s32)Math_Rand_ZeroFloat(10.0f) + 5;
                this->unk_1B0 = 0.0f;
                this->unk_190 = 1.0f;
                this->unk_194 = 2000.0f;
            }
            if (this->actor.xzDistFromLink < (100.0f * sp118.x)) {
                this->unk_158 = 0;
                this->unk_1A4 = 0x3E8;
                this->unk_1A2 = 0xC8;
                this->unk_17A[1] = 0x32;
                this->unk_15A = this->unk_158;
            }
            break;
        case 3:
            this->unk_151 = 6;
            sp134 = 2;
            if (((s32)player->actor.posRot.pos.x + D_80B7E118) & 1) {
                spC4.x = 30.0f;
            } else {
                spC4.x = -30.0f;
            }
            spC4.z = 30.0f;
            spC4.y = 0.0f;
            Matrix_RotateY(D_80B7E0DC.y, 0);
            Matrix_MultVec3f(&spC4, &spB8);
            this->unk_1B4.x = D_80B7E0B8.x + spB8.x;
            this->unk_1B4.z = D_80B7E0B8.z + spB8.z;
            this->unk_1B4.y = D_80B7E0B8.y - 10.0f;
            this->unk_1B0 = 4096.0f;
            Math_SmoothScaleMaxF(&this->actor.speedXZ, this->unk_188 * 0.8f, 1.0f, 1.0f);
            if (!((D_80B7A694 == 3) && !((globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 + 5.0f) < D_80B7E0B8.y)) || (sqrtf((D_80B7E0B8.x * D_80B7E0B8.x) + (D_80B7E0B8.z * D_80B7E0B8.z)) > 800.0f)) {
                this->unk_17A[0] = 0;
                this->unk_190 = 1.0f;
                this->unk_158 = this->unk_15A;
                this->unk_194 = 2000.0f;
            } else if ((this->unk_17A[0] == 0) || (sp124 < 30.0f)) {
                this->unk_158 = 4;
                this->unk_1B4 = D_80B7E0B8;
                this->unk_1B0 = 16384.0f;
                this->unk_190 = 1.2f;
                this->unk_17A[0] = 0x14;
                this->unk_194 = 5000.0f;
            }
            break;
        case 4:
            Math_SmoothScaleMaxF(&this->unk_1B0, 16384.0f, 1.0f, 4096.0f);
            Math_SmoothScaleMaxS(&this->unk_170, 0x4E20, 4, 0x1388);
            this->unk_151 = 0x32;
            sp134 = 2;
            this->unk_1B4 = D_80B7E0B8;
            Math_SmoothScaleMaxF(&this->actor.speedXZ, this->unk_188, 1.0f, 1.0f);
            if (!((D_80B7A694 == 3) && (this->unk_17A[0] != 0)) || 
                 ((globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 + 5.0f) < D_80B7E0B8.y) || 
                  (sqrtf((D_80B7E0B8.x * D_80B7E0B8.x) + (D_80B7E0B8.z * D_80B7E0B8.z)) > 800.0f)) {
                this->unk_17A[0] = 0;
                this->unk_190 = 1.0f;
                this->unk_158 = this->unk_15A;
                this->unk_194 = 2000.0f;
            } else {
                if (sp124 < 10.0f) {
                    if (func_80B70A2C(this, globalCtx, 0)) {
                        func_80B71278(this, 0);
                    }
                    this->unk_158 = 5;
                    this->unk_190 = 1.2f;
                    this->unk_17A[1] = 0x96;
                    this->unk_17A[0] = 0;
                    this->unk_17A[2] = 0;
                    this->unk_17A[3] = 0x78;
                    this->unk_194 = 5000.0f;
                    D_80B7A694 = 4;
                    D_80B7E0A8 = this;
                    D_80B7A69C = (500.0f - Math_Rand_ZeroFloat(400.0f));
                    if (D_80B7E0B6 == 2) {
                        if (70.0f < this->unk_1AC) {
                            tmp16 = (s16)Math_Rand_ZeroFloat(20.0f) + 10;
                        } else if (60.0f < this->unk_1AC) {
                            tmp16 = (s16)Math_Rand_ZeroFloat(30.0f) + 0x14;
                        } else if (50.0f < this->unk_1AC) {
                            tmp16 = (s16)Math_Rand_ZeroFloat(30.0f) + 0x1E;
                        } else {
                            tmp16 = (s16)Math_Rand_ZeroFloat(40.0f) + 0x28;
                        }
                        D_80B7E122 = tmp16;
                        D_80B7E0A4 = tmp16;
                        func_800A9F6C(0.0f, 0x3C, tmp16 * 3, 0xA);
                    } else {
                        if (70.0f < this->unk_1AC) {
                            tmp16 = (s16)Math_Rand_ZeroFloat(5.0f) + 0xA;
                        } else if (60.0f < this->unk_1AC) {
                            tmp16 = (s16)Math_Rand_ZeroFloat(5.0f) + 0xF;
                        } else if (50.0f < this->unk_1AC) {
                            tmp16 = (s16)Math_Rand_ZeroFloat(5.0f) + 0x11;
                        } else {
                            tmp16 = (s16)Math_Rand_ZeroFloat(5.0f) + 0x19;
                        }
                        D_80B7E122 = tmp16;
                        D_80B7E0A4 = tmp16;
                        func_800A9F6C(0.0f, 0xB4, tmp16 * 3, 0xA);
                    }
                    D_80B7E124 = 0;
                    D_80B7E116 = 0x64;
                    D_80B7E080 = 0;
                }
            }
            break;
        case -3:
            this->unk_151 = 0x32;
            this->unk_1B4 = D_80B7E0B8;
            Math_SmoothScaleMaxF(&this->actor.speedXZ, 2.0f, 1.0f, 1.0f);
            if (!((D_80B7A694 == 3) && (this->unk_17A[0] != 0)) || 
                 ((globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 + 5.0f) < D_80B7E0B8.y) || 
                  (sqrtf((D_80B7E0B8.x * D_80B7E0B8.x) + (D_80B7E0B8.z * D_80B7E0B8.z)) > 800.0f)) {
                this->unk_17A[0] = 0;
                this->unk_190 = 1.0f;
                this->unk_158 = this->unk_15A;
                this->unk_194 = 2000.0f;
            } else {
                if (sp124 < 10.0f) {
                    if (((globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 + 5.0f) - 10.0f) < D_80B7E0B8.y) {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EV_JUMP_OUT_WATER);
                        func_80078884(NA_SE_PL_CATCH_BOOMERANG);
                    }
                    func_80B70A2C(this, globalCtx, 0);
                    this->unk_158 = 5;
                    this->unk_190 = 1.2f;
                    this->unk_17A[1] = 0x96;
                    this->unk_17A[0] = 0;
                    this->unk_17A[2] = 0;
                    this->unk_17A[3] = 0x78;
                    this->unk_194 = 5000.0f;
                    D_80B7A694 = 4;
                    D_80B7E0A8 = this;
                    if (D_80B7E0B6 == 2) {
                        D_80B7E122 = 0x1E;
                        D_80B7E0A4 = 0x64;
                        func_800A9F6C(0.0f, 0x3C, 0x5A, 0xA);
                    } else {
                        D_80B7E122 = 0x1E;
                        D_80B7E0A4 = 0x28;
                        func_800A9F6C(0.0f, 0xB4, 0x5A, 0xA);
                    }
                    D_80B7E124 = 0;
                    D_80B7E116 = 0x64;
                    D_80B7E080 = 0;
                }
            }
            break;
        case 5:
            this->actor.uncullZoneForward = 1200.0f;
            this->actor.uncullZoneScale = 200.0f;
            D_80B7E080++;
            osSyncPrintf("HIT FISH %dcm\n", (u8)this->unk_1AC);
            Math_SmoothScaleMaxS(&this->unk_170, 0x2AF8, 4, 0xBB8);
            D_80B7E0A8 = this;
            Math_SmoothScaleMaxS(&player->actor.shape.rot.y, (this->actor.yawTowardsLink + 0x8000), 5, 0x500);
            if (!D_80B7E124 && (D_80B7FEA0 < 0x14) && !(D_80B7E0AE & 3)) {
                D_80B7FEA0++;
            }
            
            if (D_80B7E122 && !D_80B7E124) {
                if ((globalCtx->state.input[0].rel.in.y < -0x32) && (D_80B7A6C8 < -0x27) ||
                    CHECK_PAD(globalCtx->state.input[0].press, A_BUTTON)) {

                    if (globalCtx->state.input[0].rel.in.y < -0x32) {
                        tmpf1 = 40.0f - ((this->unk_1AC - 30.0f) * 1.333333f);
                        if (tmpf1 > 0.0f) {
                            this->unk_152 = (u8)tmpf1;
                            this->unk_154 = (this->actor.yawTowardsLink - this->actor.shape.rot.y);
                            this->unk_156 = 1;
                        }
                    }
                    this->unk_198 = 1.7f;
                    this->unk_19C = 7000.0f;
                    D_80B7E124 = 1;
                    Audio_SetBGM(0x81A);
                    D_80B7E0A6 = 0;
                    if (this->unk_150 == 1) {
                        tmpf1 = (this->unk_1AC * 3.0f) + 120.0f;
                    } else {
                        tmpf1 = (this->unk_1AC + this->unk_1AC) + 120.0f;
                    }
                    if (255.0f < tmpf1) {
                        tmpf1 = 255.0f;
                    }
                    func_800A9F6C(0.0f, tmpf1, 0x78, 5);
                    D_80B7E0A4 = 0x28;
                    D_80B7FDA8 = 0xA;
                    func_80078884(0x184A);
                }
            }

            cont = &globalCtx->state.input[0];
            if (this->actor.posRot.pos.y < globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02) {
                if (this->unk_17A[1] >= 0x1F) {
                    tmp1 = 7;
                } else {
                    tmp1 = 0xF;
                }
                if ((!(this->unk_15C & tmp1)) && (Math_Rand_ZeroOne() < 0.75f) && !D_80B7E0A4) {
                    if (70.0f <= this->unk_1AC) {
                        tmpf1 = 255.0f;
                    } else if (60.0f <= this->unk_1AC) {
                        tmpf1 = 230.0f;
                    } else if (50.0f <= this->unk_1AC) {
                        tmpf1 = 200.0f;
                    } else if (40.0f <= this->unk_1AC) {
                        tmpf1 = 170.0f;
                    } else {
                        tmpf1 = 140.0f;
                    }
                    if (tmp1 == 0xF) {
                        tmpf1 *= 0.75f;
                    }
                    func_800A9F6C(0.0f, tmpf1, (s16)Math_Rand_ZeroFloat(5.0f) + 0xA, 5);
                }
                if (this->unk_17A[1] >= 0x1F) {
                    if (this->unk_17A[0] == 0) {
                        spC4.x = 0.0f;
                        spC4.y = 0.0f;
                        spC4.z = 200.0f;
                        
                        for (j = 0; j < 100; j++) {
                            Matrix_RotateY(Math_Rand_CenteredFloat(2.3561945f) + (((this->actor.yawTowardsLink + 0x8000) / 32768.0f) * M_PI), 0);
                            Matrix_MultVec3f(&spC4, &spB8);
                            this->unk_1B4.x = this->actor.posRot.pos.x + spB8.x;
                            this->unk_1B4.z = this->actor.posRot.pos.z + spB8.z;
                            if (((this->unk_1B4.x * this->unk_1B4.x) + (this->unk_1B4.z * this->unk_1B4.z)) < 562500.0f) {
                                break;
                            }
                        }
                        if ((Math_Rand_ZeroOne() > 0.1f) && (this->unk_17A[3] == 0)) {
                            if (60.0f <= this->unk_1AC) {
                                tmp8 = 0xFF;
                            } else if (50.0f <= this->unk_1AC) {
                                tmp8 = 0xC8;
                            } else {
                                tmp8 = 0xB4;
                            }
                            func_800A9F6C(0.0f, tmp8, 0x5A, 2);
                            this->unk_17A[0] = 0x14;
                            this->unk_17A[1] = 0x64;
                            this->unk_17A[2] = 0x14;
                            this->unk_17A[3] = 0x64;
                            this->unk_1B4.y = 300.0f;
                            D_80B7E0A4 = 0x28;
                            D_80B7E116 = (s32)Math_Rand_ZeroFloat(30.0f) + 0x14;
                        } else {
                            this->unk_17A[2] = 0;
                            this->unk_17A[0] = (s32)Math_Rand_ZeroFloat(10.0f) + 3;
                            this->unk_1B4.y = -70.0f - Math_Rand_ZeroFloat(150.0f);
                        }
                    }
                    if (this->unk_17A[2]) {
                        D_80B7E11C = 0.0f;
                        this->unk_190 = 1.6f;
                        this->unk_194 = 6000.0f;
                        Math_SmoothScaleMaxF(&this->actor.speedXZ, 7.5f, 1.0f, 1.0f);
                        Math_SmoothScaleMaxS(&this->unk_170, 0x4E20, 2, 0xFA0);
                    } else {
                        if ((D_80B7E124 == 0) && (D_80B7E0B6 == 2)) {
                            this->unk_190 = 1.0f;
                            this->unk_194 = 2000.0f;
                            Math_SmoothScaleMaxF(&this->actor.speedXZ, 3.0f, 1.0f, 0.2f);
                        } else {
                            this->unk_190 = 1.4f;
                            this->unk_194 = 5000.0f;
                            Math_SmoothScaleMaxF(&this->actor.speedXZ, 5.0f, 1.0f, 0.5f);
                        }
                        if (this->unk_150 == 0) {
                            D_80B7E11C = 1.0f - (this->unk_1AC * 0.00899f);
                        } else {
                            D_80B7E11C = 1.0f - ((this->unk_1AC * 0.00899f) * 1.4f);
                        }
                    }
                } else {
                    if ((this->unk_17A[1] & 0xF) == 0) {
                        if (CHECK_PAD(cont->press, A_BUTTON)) {
                            if (!(this->unk_1AC >= 60.0f) || (D_80B7E080 >= 0x7D0)) {
                                this->unk_154 = this->actor.yawTowardsLink - this->actor.shape.rot.y;
                                this->unk_152 = (s32)Math_Rand_ZeroFloat(30.0f) + 0xF;
                            }
                        }
                    }
                    this->unk_190 = 1.0f;
                    this->unk_194 = 4500.0f;
                    if (this->unk_150 == 0) {
                        D_80B7E11C = 1.3f - (this->unk_1AC * 0.00899f);
                    } else {
                        D_80B7E11C = 1.3f - ((this->unk_1AC * 0.00899f) * 1.4f);
                    }
                    Math_SmoothScaleMaxF(&this->actor.speedXZ, 2.0f, 1.0f, 0.5f);
                    if (this->unk_17A[1] == 0) {
                        this->unk_152 = (u8)0U;
                        if (D_80B7E080 < 0x7D0) {
                            this->unk_17A[1] = (s16) ((s32) Math_Rand_ZeroFloat(50.0f) + 0x32);
                        } else if (D_80B7E080 < 0xBB8) {
                            this->unk_17A[1] = (s32)Math_Rand_ZeroFloat(20.0f) + 0x1E;
                        } else {
                            this->unk_17A[1] = (s32)Math_Rand_ZeroFloat(10.0f) + 0x19;
                        }
                    }
                }
            }
            if (D_80B7E074 != 0) {
                D_80B7E11C = 0.0f;
            }
            if (!(D_80B7E124 == 0) || (D_80B7E0B6 != 2)) {
                if (this->actor.speedXZ < 3.0f) {
                    if (D_80B7E0AE & 8) {
                        tmpf1 = -0.8f;
                    } else {
                        tmpf1 = -0.75f;
                    }
                } else {
                    if (D_80B7E0AE & 4) {
                        tmpf1 = -0.9f;
                    } else {
                        tmpf1 = -0.85f;
                    }
                }
                Math_SmoothScaleMaxF(&D_80B7A6C0, 35.0f, 0.1f, 3.5f);
                Math_SmoothScaleMaxF(&D_80B7A6BC, tmpf1, 0.3f, 0.1f);
            }
            D_80B7E168[0xC7] = this->unk_1C0;
            spC4.x = D_80B7E168[0xC7].x - D_80B7E168[0xC6].x;
            spC4.y = D_80B7E168[0xC7].y - D_80B7E168[0xC6].y;
            spC4.z = D_80B7E168[0xC7].z - D_80B7E168[0xC6].z;
            if ((((spC4.x * spC4.x) + (spC4.y * spC4.y)) + (spC4.z * spC4.z)) > 400.0f) {
                tmpf1 = this->actor.speedXZ * 1.5f;
                Math_SmoothScaleMaxF(&this->actor.posRot.pos.x, D_80B7E168[0xC6].x, 0.2f, tmpf1 + tmpf1);
                tmpf1 = this->actor.speedXZ * 1.5f;
                Math_SmoothScaleMaxF(&this->actor.posRot.pos.y, D_80B7E168[0xC6].y, 0.2f, ((tmpf1 + tmpf1) * 5.0f) * 0.1f);
                tmpf1 = this->actor.speedXZ * 1.5f;
                Math_SmoothScaleMaxF(&this->actor.posRot.pos.z, D_80B7E168[0xC6].z, 0.2f, tmpf1 + tmpf1);
            }
            if (CHECK_PAD(cont->press, A_BUTTON) || (cont->rel.in.y < -0x1E)) {
                if (D_80B7E116 < 0x64) {
                    D_80B7E116++;
                }
            } else if (D_80B7E116) {
                D_80B7E116--;
            }

            if ((!(D_80B7A694 >= 3) || 
                  (D_80B7E074 && !(D_80B7E080 < 0x33)) ||
                  !(D_80B7E080 < 0x1770) ||
                  (!D_80B7E122 && !D_80B7E124) || 
                  !D_80B7E116) 
                ||
                  (!(D_80B7E0AE & 0x7F) &&
                  (Math_Rand_ZeroOne() < 0.05f) && 
                  (D_80B7E0B6 != 2) && 
                  (KREG(69) == 0))) {
                

                D_80B7A67C = 0x14;
                if ((D_80B7E122 == 0) && (D_80B7E124 == 0)) {
                    D_80B7E086 = 0x4081;
                    if (((D_80B7E075 == 1) && (gSaveContext.unk_EC0 & 0x400)) ||
                        ((D_80B7E075 != 1) && (gSaveContext.unk_EC0 & 0x800))) {
                        D_80B7A67C = 0;
                    }
                } else {
                    D_80B7E086 = 0x4082;
                    func_800A9F6C(0.0f, 1, 3, 1);
                    Audio_SetBGM(0x100A00FF);
                }
                this->unk_15A = 0;
                this->unk_1A4 = 0x2710;
                this->unk_1A2 = 0x1F4;
                this->unk_17A[1] = 0x32;
                this->unk_17A[0] = 0;
                this->unk_190 = 1.0f;
                this->unk_158 = this->unk_15A;
                this->unk_194 = 3000.0f;
                if (D_80B7A694 == 4) {
                    D_80B7A694 = 3;
                }
                D_80B7E0A6 = 0x32;
                D_80B7E11C = 0.5f;
                this->unk_152 = 0;
            } else {
                if (this->actor.xzDistFromLink < (KREG(59) + 50.0f)) {
                    this->unk_158 = 6;
                    this->unk_17A[0] = 0x64;
                    player->stickFlameTimer = 3;
                    func_800A9F6C(0.0f, 1, 3, 1);
                    D_80B7E084++;
                    func_80064520(globalCtx, &globalCtx->csCtx);
                    D_80B7A6CC = 0x64;
                    D_80B7FEC8 = 45.0f;
                    D_80B7A694 = 5;
                    this->unk_190 = 1.0f;
                    this->unk_194 = 500.0f;
                    this->unk_19C = 5000.0f;
                    if (this->actor.posRot.pos.y <= globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02) {
                        func_80B71278(this, 1);
                        func_80B70A2C(this, globalCtx, 1);
                    }
                }
            }
            //break;
        case 6:
            tmpfp1 = &this->actor.posRot.pos.x;
            tmpfp2 = &this->actor.posRot.pos.y;
            tmpfp3 = &this->actor.posRot.pos.z;
            Math_SmoothScaleMaxS(&this->unk_170, 0x2AF8, 2, 0xFA0);
            Math_SmoothScaleMaxF(&D_80B7FEC8, 15.0f, 0.05f, 0.75f);
            spC4.x = D_80B7FEC8;
            if (D_80B7E075 != 1) {
                spC4.y = 30.0f;
                spC4.z = 55.0f;
            } else {
                spC4.y = 10.0f;
                spC4.z = 50.0f;
            }
            Matrix_RotateY((player->actor.shape.rot.y / 32768.0f) * 3.1415927f, 0);
            Matrix_MultVec3f(&spC4, &D_80B7FEA8);
            D_80B7FEA8.x += player->actor.posRot.pos.x;
            D_80B7FEA8.y += player->actor.posRot.pos.y;
            D_80B7FEA8.z += player->actor.posRot.pos.z;
            D_80B7FEB8 = player->actor.posRot.pos;
            if (D_80B7E075 != 1) {
                D_80B7FEB8.y += 40.0f;
            } else {
                D_80B7FEB8.y += 25.0f;
            }
            if (this->unk_17A[0] == 0x5A) {
                Audio_SetBGM(0x924);
                D_80B7A67C = 0x28;
                if (this->unk_150 == 0) {
                    D_80B7A678 = (u16)this->unk_1AC;
                    if (D_80B7A678 >= 0x4B) {
                        D_80B7E086 = 0x409F;
                    } else if (D_80B7A678 >= 0x32) {
                        D_80B7E086 = 0x4091;
                    } else {
                        D_80B7E086 = 0x4083;
                    }
                } else {
                    D_80B7A678 = (u16)(this->unk_1AC + this->unk_1AC);
                    D_80B7E086 = 0x4099;
                }
                this->unk_1D5 = 0;
            }
            this->unk_160 = -0x4000;
            this->unk_16E = 0;
            this->actor.shape.rot.y = player->actor.shape.rot.y + 0x5000;
            this->unk_164 = this->unk_16E;
            this->unk_162 = this->unk_16E;
            this->actor.shape.rot.z = this->unk_16E;
            this->actor.shape.rot.x = this->unk_16E;
            spC4.x = 4.0f;
            spC4.y = -10.0f;
            spC4.z = 5.0f;
            Matrix_MultVec3f(&spC4, &spB8);
            Math_SmoothScaleMaxF(tmpfp1, player->unk_9BC.x + spB8.x, 1.0f, 6.0f);
            Math_SmoothScaleMaxF(tmpfp2, player->unk_9BC.y + spB8.y, 1.0f, 6.0f);
            Math_SmoothScaleMaxF(tmpfp3, player->unk_9BC.z + spB8.z, 1.0f, 6.0f);
            D_80B7E144 = 188.0f;
            if (this->unk_17A[0] < 0x33) {
                switch (this->unk_1D5) {
                    case 0:
                        if ((func_8010BDBC(&globalCtx->msgCtx) == 4) || (func_8010BDBC(&globalCtx->msgCtx) == 0)) {
                            if (func_80106BC8(globalCtx) != 0) {
                                func_80106CCC(globalCtx);
                                tmpf1 = D_80B7A670;
                                if (globalCtx->msgCtx.choiceIndex == 0) {
                                    if (tmpf1 == 0.0f) {
                                        D_80B7A670 = this->unk_1AC;
                                        D_80B7E07C = this->unk_150;
                                        D_80B7E07E = D_80B7E0B6;
                                        Actor_Kill(&this->actor);
                                    } else if ((this->unk_150 == 0) && (D_80B7E07C == 0) && ((s16)this->unk_1AC < (s16)D_80B7A670)) {
                                        this->unk_1D5 = 1;
                                        this->unk_17A[0] = 0x3C;
                                        func_8010B680(globalCtx, 0x4098, 0);
                                    } else {
                                        D_80B7A670 = this->unk_1AC;
                                        D_80B7E07C = this->unk_150;
                                        D_80B7E07E = D_80B7E0B6;
                                        this->unk_1AC = tmpf1;
                                        this->unk_150 = D_80B7E07C;
                                    }
                                }
                                if (this->unk_1D5 == 0) {
                                    D_80B7A694 = 0;
                                }
                            }
                        }
                        break;
                    case 1:
                        if ((func_8010BDBC(&globalCtx->msgCtx) == 4) || (func_8010BDBC(&globalCtx->msgCtx) == 0)) {
                            if (func_80106BC8(globalCtx) != 0) {
                                func_80106CCC(globalCtx);
                                if (globalCtx->msgCtx.choiceIndex != 0) {
                                    tmpf1 = D_80B7A670;
                                    D_80B7A670 = this->unk_1AC;
                                    D_80B7E07E = D_80B7E0B6;
                                    this->unk_1AC = tmpf1;
                                    this->unk_150 = D_80B7E07C;
                                }
                                D_80B7A694 = 0;
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
            if (D_80B7A694 == 0) {
                if (this->actor.update != NULL) {
                    this->unk_15A = 0;
                    this->unk_1A4 = 0x2710;
                    this->unk_1A2 = 0x1F4;
                    this->unk_17A[1] = 0x32;
                    this->unk_17A[0] = 0;
                    this->unk_190 = 1.0f;
                    this->unk_158 = this->unk_15A;
                    this->unk_194 = 2000.0f;
                    SkelAnime_Free(&this->skelAnime, globalCtx);
                    if (this->unk_150 == 0) {
                        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060029C0, &D_0600007C, 0, 0, 0);
                        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_0600007C, 0.0f);
                    } else {
                        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06011058, &D_0600CFE0, 0, 0, 0);
                        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_0600CFE0, 0.0f);
                    }
                }
                D_80B7E148 = 520.0f;
                D_80B7E144 = 195.0f;
                Audio_SetBGM(0x100A00FF);
                D_80B7E0A6 = 0x14;
                D_80B7A6CC = 3;
            }
            break;
        case 7:
            this->unk_151 = 0x32;
            sp134 = 5;
            this->unk_1B0 = 12288.0f;
            if (this->actor.params < 0x68) {
                fish1 = &D_80B81FC8[(this->actor.params - 0x1C1C)];
                this->unk_1B4 = fish1->unk_04;
                D_80B7A898 = 1.0f;
            } else if (this->actor.params < 0x6C) {
                fish1 = &D_80B81FC8[(this->actor.params - 0x179C)];
                this->unk_1B4 = fish1->unk_04;
                D_80B7A898 = 2.0f;
            } else {
                fish1 = &D_80B81FC8[(this->actor.params - 0x131C)];
                this->unk_1B4 = fish1->unk_04;
                D_80B7A898 = 3.0f;
            }
            Math_SmoothScaleMaxF(&this->actor.speedXZ, 5.0f, 1.0f, 1.0f);
            if (sp124 < 20.0f) {
                Math_SmoothScaleMaxS(&this->unk_170, 0x4E20, 2, 0xFA0);
                if (this->unk_17A[2] == 0) {
                    if (func_80B70A2C(this, globalCtx, 0) != 0) {
                        func_80B71278(this, (u8)Math_Rand_ZeroFloat(1.99f));
                        this->unk_17A[2] = (s32)Math_Rand_ZeroFloat(20.0f) + 0x14;
                    }
                }
            }
            if (this->unk_17A[3] == 0) {
                this->unk_158 = 0xA;
                this->unk_15A = 0xA;
            } else {
                func_80B70ED4(this, &globalCtx->state.input[0]);
                if (this->actor.xzDistFromLink < (100.0f * sp118.x)) {
                    this->unk_158 = 0;
                    this->unk_1A4 = 0x1F4;
                    this->unk_1A2 = 0xC8;
                    this->unk_17A[1] = 0x32;
                    this->unk_15A = this->unk_158;
                }
            }
            break;
    }

    Math_SmoothScaleMaxS(&this->unk_172, (Math_Sins(this->unk_15C * 0x10000000) * 5000.0f) + 5000.0f, 2, 0x7D0);
    if (this->unk_158 != 6) {
        if (globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 < this->actor.posRot.pos.y) {
            this->unk_190 = 1.5f;
            this->unk_194 = 5000.0f;
            Math_SmoothScaleMaxS(&this->unk_16E, 0, 5, 0x7D0);
            tmp19 = 3;
            tmp17 = 3;
            tmp20 = 3;
            tmp18 = 0x2000;
            tmp16 = 0x2000;
            this->unk_17A[2] = 0;
            this->unk_184 -= 1.0f;
        } else {
            Math_SmoothDownscaleMaxF(&this->unk_184, 1.0f, 2.0f);
            if ((this->unk_158 != -1) && (this->unk_158 != -2) && (this->unk_158 != -0x19)) {
                this->unk_166 = 0;
            }
            this->unk_16A = 0;
            this->unk_168 = this->unk_16A;
            tmp19 = 4;
            tmp17 = 4;
            tmp20 = 4;
            tmp18 = 0x2000;
            tmp16 = 0x2000;
            tmp15 = func_80B69B84(&this->actor.posRot.rot.y, spFC, sp134, (s16)this->unk_1B0) * 0.3f;
            Math_SmoothScaleMaxS(&this->actor.posRot.rot.x, spFE, sp134, this->unk_1B0 * 0.5f);
            if (tmp15 >= 0x1F41) {
                tmp15 = 0x1F40;
            } else if (tmp15 < -0x1F40) {
                tmp15 = -0x1F40;
            }
            if (this->actor.speedXZ >= 3.2f) {
                Math_SmoothScaleMaxS(&this->unk_16E, tmp15, 2, 0x4E20);
            } else {
                Math_SmoothScaleMaxS(&this->unk_16E, tmp15, 3, 0xBB8);
            }
            func_8002D908(&this->actor);
        }
        func_8002D7EC(&this->actor);
        this->actor.posRot.pos.y += this->unk_184 * 1.5f;
        if (this->unk_152 != 0) {
            this->unk_152--;
            this->unk_168 = this->unk_154;
            if (this->unk_156 != 0) {
                tmp17 = 5;
                tmp16 = 0x4000;
            } else {
                tmp17 = 0xA;
                tmp16 = 0x800;
            }
            this->unk_166 = -0x500 - this->actor.shape.rot.x;
            tmp19 = 5;
            tmp18 = 0x4000;
        } else {
            this->unk_156 = 0;
        }
        Math_SmoothScaleMaxS(&this->unk_160, this->unk_166, tmp19, tmp18);
        Math_SmoothScaleMaxS(&this->unk_162, this->unk_168, tmp17, tmp16);
        Math_SmoothScaleMaxS(&this->unk_164, this->unk_16A, tmp20, 0x2000);
        if (this->actor.speedXZ <= 0.5f) {
            Math_SmoothScaleMaxS(&this->actor.shape.rot.x, 0, 0xA, this->unk_178);
            Math_SmoothScaleMaxS(&this->unk_178, 0x500, 1, 0x20);
        } else {
            Math_SmoothScaleMaxS(&this->actor.shape.rot.x, -this->actor.posRot.rot.x, 0xA, 0x1000);
            this->unk_178 = 0;
        }
        this->actor.shape.rot.y = this->actor.posRot.rot.y;
        if ((this->unk_158 != -1) && (this->unk_158 != -2) && (this->unk_158 != -0x19)) {
            if (!(globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 < this->actor.posRot.pos.y) && 
               (this->actor.pos4.y <= globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02)) {
                func_80B70A2C(this, globalCtx, 1);
                func_80B71278(this, 1);
                this->unk_184 = this->actor.velocity.y;
                this->actor.velocity.y = 0.0f;
                this->unk_16A = Math_Rand_CenteredFloat(32768.0f);
            } else {
                if ((this->actor.posRot.pos.y < globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02) && (globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 <= this->actor.pos4.y)){
                    if (this->unk_184 < -5.0f) {
                        this->unk_184 = -5.0f;
                    }
                    this->actor.posRot.rot.x = (u16)-0xFA0;
                    func_80B70A2C(this, globalCtx, 1);
                    this->unk_1D2 = 0x14;
                    func_80B71278(this, 0);
                }
            }
        }
        if ((this->actor.posRot.pos.y < globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02) &&
           ((globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 - 10.0f) < this->actor.posRot.pos.y) &&
           ((this->unk_15C & 1) == 0) &&
           (this->actor.speedXZ > 0.0f)) {
            spC4 = this->actor.posRot.pos;
            func_80B69C2C(&this->actor.projectedPos, (FishingStruct1*)globalCtx->unk_11E10, &spC4, 80.0f, 500.0f, 0x96, 0x5A);
        }
        if ((this->actor.speedXZ > 0.0f) || (this->unk_158 == 5)) {
            tmpf1 = this->actor.velocity.y;
            this->actor.posRot.pos.y -= this->unk_1AC * 0.1f;
            this->actor.velocity.y = -1.0f;
            this->actor.pos4.y -= this->unk_1AC * 0.1f;
            func_8002E4B4(globalCtx, &this->actor, 30.0f, 30.0f, 100.0f, 0x45);
            this->actor.posRot.pos.y += this->unk_1AC * 0.1f;
            this->actor.pos4.y += this->unk_1AC * 0.1f;
            this->actor.velocity.y = tmpf1;
            if (this->actor.bgCheckFlags & 8) {
                this->unk_1A0 = 0x14;
            }
            if (this->actor.bgCheckFlags & 1) {
                if (globalCtx->colCtx.stat.colHeader->waterBoxes->unk_02 < this->actor.posRot.pos.y) {
                    this->unk_184 = Math_Rand_ZeroFloat(3.0f) + 3.0f;
                    this->actor.velocity.x = this->actor.posRot.pos.x * -0.003f;
                    this->actor.velocity.z = this->actor.posRot.pos.z * -0.003f;
                    Audio_PlayActorSound2(&this->actor, NA_SE_EV_FISH_LEAP);
                    func_80B70CF0(this, globalCtx);
                    if (Math_Rand_ZeroOne() < 0.5f) {
                        this->unk_16A = 0x4000;
                    } else {
                        this->unk_16A = -0x4000;
                    }
                    if (Math_Rand_ZeroOne() < 0.5f) {
                        this->unk_166 = 0;
                    } else {
                        this->unk_166 = (s32)Math_Rand_CenteredFloat(32.0f) + 0x8000;
                    }
                    this->unk_190 = 1.0f;
                    this->unk_168 = (s32)Math_Rand_CenteredFloat(16384.0f);
                    this->unk_194 = 5000.0f;
                    this->unk_19C = 5000.0f;
                } else {
                    this->unk_184 = 0.0f;
                    if ((this->unk_158 == 5) && ((this->unk_15C & 1) == 0)) {
                        spC4.x = Math_Rand_CenteredFloat(10.0f) + this->actor.posRot.pos.x;
                        spC4.z = Math_Rand_CenteredFloat(10.0f) + this->actor.posRot.pos.z;
                        spC4.y = this->actor.groundY + 5.0f;
                        func_80B69ED0(&this->actor.projectedPos, (FishingStruct1*)globalCtx->unk_11E10, &spC4, (this->unk_1AC * 0.005f) + 0.15f);
                    }
                }
            }
        }
    }
    if (this->unk_1D2 != 0) {
        this->unk_1D2--;
        tmpf1 = (this->unk_1AC * 0.075f) + 10.0f;
        for (i = 0; i < 2; i++) {
            spC4.x = Math_Rand_CenteredFloat(tmpf1) + this->actor.posRot.pos.x;
            spC4.y = Math_Rand_CenteredFloat(tmpf1) + this->actor.posRot.pos.y;
            spC4.z = Math_Rand_CenteredFloat(tmpf1) + this->actor.posRot.pos.z;
            func_80B6A008(&this->actor.projectedPos, (FishingStruct1*)globalCtx->unk_11E10, &spC4, Math_Rand_ZeroFloat(0.035f) + 0.04f, 0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/Fishing_Update.s")
#endif
#undef A

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B75BAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B75CE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B75D20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B75DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/Fishing_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B76028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B760D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B761B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B76474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B768FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B771CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B77404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B7825C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B7A10C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B7A140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Fishing/func_80B7A278.s")
