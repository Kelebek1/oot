#include "z_boss_tw.h"

#define FLAGS 0x00000035

#define THIS ((BossTw*)thisx)

void BossTw_Init(Actor* thisx, GlobalContext* globalCtx);
void BossTw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BossTw_Update(Actor* thisx, GlobalContext* globalCtx);
void BossTw_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_80946B00(Actor* thisx, GlobalContext* globalCtx);
void func_80946C7C(Actor* thisx, GlobalContext* globalCtx);
void func_80947240(Actor* thisx, GlobalContext* globalCtx);
void func_80940D48(Actor* thisx, GlobalContext* globalCtx);
void func_80945084(Actor* thisx, GlobalContext* globalCtx);

void func_809453EC(BossTw* this, GlobalContext* globalCtx);
void func_80945D14(BossTw* this, GlobalContext* globalCtx);
void func_8093EE10(BossTw* this, GlobalContext* globalCtx);
void func_8093A0A8(BossTw* this, GlobalContext* globalCtx);
void func_8093D54C(BossTw* this, GlobalContext* globalCtx);
void func_8093C824(BossTw* this, GlobalContext* globalCtx);
void func_8093D58C(BossTw* this, GlobalContext* globalCtx);

extern AnimationHeader D_06006F28;
extern SkeletonHeader D_060070E0;
extern SkeletonHeader D_0601F888;
extern AnimationHeader D_060244B4;
extern SkeletonHeader D_06032020;

const ActorInit Boss_Tw_InitVars = {
    ACTOR_BOSS_TW,
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_TW,
    sizeof(BossTw),
    (ActorFunc)BossTw_Init,
    (ActorFunc)BossTw_Destroy,
    (ActorFunc)BossTw_Update,
    (ActorFunc)BossTw_Draw,
};

// D_8094A7E8
static ColliderCylinderInit sCylinderInit1 =
{
    { COLTYPE_UNK10, 0x39, 0x09, 0x09, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x30 }, { 0x00100000, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
    { 25, 35, -17, { 0, 0, 0 } },
};

// D_8094A814
static ColliderCylinderInit sCylinderInit2 =
{
    { COLTYPE_UNK3, 0x11, 0x09, 0x09, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x20 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
    { 45, 120, -30, { 0, 0, 0 } },
};

// D_8094A840
static ColliderCylinderInit sCylinderInit3 =
{
    { COLTYPE_UNK3, 0x11, 0x09, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x20 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x05, 0x01 },
    { 45, 120, -30, { 0, 0, 0 } },
};

u8 D_8094A89C = 0x00;

// D_8094A8A0
static InitChainEntry sInitChain[] = {
    ICHAIN_U8(unk_1F, 5, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 0, ICHAIN_STOP),
};

s8 D_8094C840;
u8 D_8094C841;
Actor* D_8094C844;
Actor* D_8094C848;
Actor* D_8094C84C;
u8 D_8094C850;
u8 D_8094C851;
f32 D_8094C854;
f32 D_8094C858;
u8 D_8094C85C;
u8 D_8094C85D;
u8 D_8094C85E;
u8 D_8094C85F;
u8 D_8094C86E;
u8 D_8094C86F;
u8 D_8094C870;
s16 D_8094C872;
u16 D_8094C874;
u16 D_8094C876;
u8 D_8094C878;
u16 D_8094C87A;
s16 D_8094C87C;
u8 D_8094C87E;
struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ char unk_01[0x47];
} D_8094C880[0x96];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80938CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80938DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80938EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80938FC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80939070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80939148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80939250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80939338.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809394FC.s")

#define NON_MATCHING
#ifdef NON_MATCHING
void BossTw_Init(Actor *thisx, GlobalContext *globalCtx) {
    BossTw* this = THIS;
    s16 i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);

    if (this->actor.params >= 0x64) {
        Actor_SetScale(&this->actor, 0.01f);
        this->actor.update = func_80946B00;
        this->actor.draw = func_80946C7C;
        this->actor.flags &= -2;
        Collider_InitCylinder(globalCtx, &this->collider);
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit1);
        if ((this->actor.params == 0x64) || (this->actor.params == 0x65)) {
            this->actionFunc = func_809453EC;
            this->unk_5C8 = 1;
        } else if ((this->actor.params == 0x66) || (this->actor.params == 0x67)) {
            this->actionFunc = func_80945D14;
        } else if (this->actor.params >= 0x68) {
            this->actionFunc = func_8093EE10;
            this->actor.draw = func_80947240;
            this->unk_1AC = 128.0f;
            if (this->actor.params == 0x68) {
                this->actor.posRot.rot.y = D_8094C84C->posRot.rot.y + 0x4000;
            } else {
                this->actor.posRot.rot.y = D_8094C84C->posRot.rot.y - 0x4000;
            }
        }
        this->unk_17A = 0x96;
        return;
    }
    Actor_SetScale(&this->actor, 0.024999999f);
    this->actor.colChkInfo.mass = 0xFF;
    this->actor.colChkInfo.health = 0;
    Collider_InitCylinder(globalCtx, &this->collider);
    if (D_8094A89C == 0) {
        D_8094A89C = 1;
        globalCtx->envCtx.unk_BF = 1;
        globalCtx->envCtx.unk_BE = 1;
        globalCtx->envCtx.unk_BD = 1;
        globalCtx->envCtx.unk_D8 = 0.0f;

        D_8094C840 = 0;
        D_8094C86E = D_8094C872 = D_8094C840 & 0xFF;

        
        
        D_8094C851 = D_8094C841 = D_8094C85F = D_8094C85C = D_8094C85E = D_8094C850 = 0;
        D_8094C87E = D_8094C86F = D_8094C870 = D_8094C872;

        D_8094C874 = D_8094C876 = D_8094C878 = D_8094C87A = D_8094C87C = D_8094C872 & 0xFF;

        D_8094C858 = D_8094C854 = 0.0f;
        D_8094C85D = Math_Rand_ZeroFloat(1.99f);
        globalCtx->unk_11E10 = (u8*)D_8094C880;
        for (i = 0; i < 0x96; i++) {
            D_8094C880[i].unk_00 = 0;
        }
    }
    if (this->actor.params == 0) {
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit2);
        this->actor.naviEnemyId = 0x33;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060070E0, &D_06006F28, 0, 0, 0);
        if (gSaveContext.eventChkInf[7] & 0x20) {
            func_8093A0A8(this, globalCtx);
            this->actor.posRot.pos.x = -600.0f;
            this->actor.posRot.pos.y = 400.0f;
            this->actor.posRot.pos.z = 0.0f;
            Audio_SetBGM(0x1B);
        } else {
            func_8093D54C(this, globalCtx);
        }
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06006F28, -3.0f);
        this->unk_564 = 1;
    } else if (this->actor.params == 1) {
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit2);
        this->actor.naviEnemyId = 0x32;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0601F888, &D_06006F28, 0, 0, 0);
        if (gSaveContext.eventChkInf[7] & 0x20) {
            func_8093A0A8(this, globalCtx);
            this->actor.posRot.pos.x = 600.0f;
            this->actor.posRot.pos.y = 400.0f;
            this->actor.posRot.pos.z = 0.0f;
        } else {
            func_8093D54C(this, globalCtx);
        }
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06006F28, -3.0f);
        this->unk_564 = 1;
    } else {
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit3);
        this->actor.naviEnemyId = 0x5B;
        this->actor.colChkInfo.health = 0x18;
        this->actor.update = func_80940D48;
        this->actor.draw = func_80945084;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06032020, &D_060244B4, 0, 0, 0);
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_060244B4, -3.0f);
        if (gSaveContext.eventChkInf[7] & 0x20) {
            func_8093C824(this, globalCtx);
        } else {
            func_8093D58C(this, globalCtx);
            this->actor.posRot.pos.x = 0.0f;
            this->actor.posRot.pos.y = 1000.0f;
            this->actor.posRot.pos.z = 0.0f;
        }
        this->actor.params = 2;
        D_8094C84C = &this->actor;
        if (Flags_GetClear(globalCtx, globalCtx->roomCtx.curRoom.num)) {
            Actor_Kill(&this->actor);
            Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_DOOR_WARP1, 600.0f, 230.0f, 0.0f, 0, 0, 0, -1);
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_ITEM_B_HEART, -600.0f, 230.0f, 0.0f, 0, 0, 0, 0);
        } else {
            D_8094C844 = Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_TW, this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0, 0, 0, 0);
            D_8094C848 = Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_TW, this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0, 0, 0, 1);
            D_8094C844->attachedA = D_8094C848;
            D_8094C848->attachedA = D_8094C844;
        }
    }

    this->unk_1D4 = (f32)globalCtx->lightCtx.unk_07;
    this->unk_1D8 = (f32)globalCtx->lightCtx.unk_08;
    this->unk_1DC = (f32)globalCtx->lightCtx.unk_09;
    this->unk_1E0 = (f32)globalCtx->lightCtx.unk_0A;
    this->unk_1E4 = 1000.0f;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/BossTw_Init.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/BossTw_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80939F40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80939F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093A0A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093A2AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093A4DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093A5C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093A940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093AB30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093ADB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093AED8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093B1AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C1C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C25C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C2C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C58C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C5F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C684.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C700.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C79C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C7E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C824.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093C910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093D3D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093D444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093D54C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093D580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093D58C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093D5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093EE10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093F108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093F1C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093F9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/BossTw_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80940D48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809416D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80941788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80941BC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80942180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809426F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80942C70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80943028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/BossTw_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80943950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80943D90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80943F08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809447BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80944C50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80945084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809453EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80945D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8094687C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80946B00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80946C7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80947240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809477E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80948528.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80948544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80948668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80949530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809495A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809496D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80949734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80949920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809499AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80949BFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80949C4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80949CE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80949E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8094A0C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8094A12C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8094A1C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8094A398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8094A608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8094A660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8094A6D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8094A740.s")
