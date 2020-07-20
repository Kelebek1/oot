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
extern Gfx D_06012B38;
extern Gfx D_06012CE0;
extern Gfx D_06013310;
extern Gfx D_060134B8;
extern UNK_PTR D_06013AE8;
extern UNK_PTR D_06013D68;
extern UNK_PTR D_06013E98;
extern UNK_PTR D_06013F98;
extern UNK_PTR D_06014070;
extern UNK_PTR D_06014158;
extern UNK_PTR D_06018FC0;
extern UNK_PTR D_06019938;
extern UNK_PTR D_06019D40;
extern UNK_PTR D_0601A430;
extern UNK_PTR D_0601A790;
extern UNK_PTR D_0601A998;
extern UNK_PTR D_0601BC00;
extern UNK_PTR D_0601C1C0;
extern UNK_PTR D_0601CEE0;
extern UNK_PTR D_0601DBE8;
extern UNK_PTR D_0601DDF0;
extern UNK_PTR D_0601F608;
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

Vec3f D_8094A7DC = { 0.0f, 0.0f, 0.0f };

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

s16 D_8094A900[] = {
    0x0000, 0x0001, 0x0002, 
    0x0002, 0x0001, 0x0000
};

Vec3f D_8094A920 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8094A92C = { 0.0f, 0.0f, 0.0f };

Vec3f D_8094A944 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8094A950 = { 0.0f, 2000.0f, -2000.0f };
Vec3f D_8094A95C = { 0.0f, 0.0f, -10000.0f };
Vec3f D_8094A968 = { 0.0f, 0.0f, -8000.0f};
Vec3f D_8094A974 = { 0.0f, 0.0f, -9000.0f};
Vec3f D_8094A980 = { 0.0f, 0.0f, -11000.0f};
Vec3f D_8094A98C = { 0.0f, 0.0f, -12000.0f};

UNK_PTR D_8094A998[] = { 0x0600A438, 0x0600B238, 0x0600B638 };
Vec3f D_8094A9A4 = { 0.0f, 200.0f, 2000.0f };

s8 D_8094C840;
u8 D_8094C841;
Actor* D_8094C844;
Actor* D_8094C848;
BossTw* D_8094C84C;
u8 D_8094C850;
u16 D_8094C851;
f32 D_8094C854;
f32 D_8094C858;
u8 D_8094C85C;
u8 D_8094C85D;
u8 D_8094C85E;
u8 D_8094C85F;
Vec3f D_8094C860;
s16 D_8094C86C;
u8 D_8094C86E;
u8 D_8094C86F;
u8 D_8094C870;
u16 D_8094C872;
u16 D_8094C874;
u16 D_8094C876;
u8 D_8094C878;
u16 D_8094C87A;
s16 D_8094C87C;
u8 D_8094C87E;
typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ s8 unk_01;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ char unk_28[0x4];
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ s32 unk_44;
} BossTw1; // size = 0x48

BossTw1 D_8094C880[0x96];

#ifdef NON_MATCHING
// Regalloc on the ZeroFloat
void func_80938CD0(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5, s16 arg6) {
    s16 i;
    BossTw1* ptr = (BossTw1*)globalCtx->unk_11E10;
    

    for (i = 0; i < arg6; i++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 1;
            ptr->unk_04 = *arg1;
            ptr->unk_10 = *arg2;
            ptr->unk_1C = *arg3;
            ptr->unk_34 = arg4 / 1000.0f;
            ptr->unk_2C = 0xFF;
            ptr->unk_01 = Math_Rand_ZeroFloat(10.0f);
            ptr->unk_2E = arg5;
            break;
        }
        ptr++;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80938CD0.s")
#endif

#ifdef NON_MATCHING
// Regalloc on the ZeroFloat
void func_80938DC4(GlobalContext* globalCtx, s16 arg1, Vec3f* arg2, Vec3f* arg3, Vec3f* arg4, f32 arg5, s16 arg6, s16 arg7, s16 arg8) {
    s16 i;
    BossTw1* ptr = (BossTw1*)globalCtx->unk_11E10;

    for (i = 0; i < arg8; i++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = arg1;
            ptr->unk_04 = *arg2;
            ptr->unk_10 = *arg3;
            ptr->unk_1C = *arg4;
            ptr->unk_34 = arg5 / 1000.0f;
            ptr->unk_2E = arg7;
            ptr->unk_2C = arg6;
            ptr->unk_01 = Math_Rand_ZeroFloat(100.0f);
            break;
        }
        ptr++;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80938DC4.s")
#endif

#ifdef NON_MATCHING
// Regalloc on the ZeroFloat
void func_80938EC0(GlobalContext* globalCtx, Vec3f* arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7) {
    s16 i;
    BossTw1* ptr = (BossTw1*)globalCtx->unk_11E10;

    for (i = 0; i < arg7; i++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 4;
            ptr->unk_04 = *arg1;
            ptr->unk_10 = D_8094A7DC;
            ptr->unk_1C = D_8094A7DC;
            ptr->unk_34 = arg2 * 0.0025f;
            ptr->unk_38 = arg3 * 0.0025f;
            ptr->unk_2E = arg5;
            ptr->unk_30 = arg6;
            ptr->unk_2C = arg4;
            ptr->unk_3C = Math_Rand_ZeroFloat(M_PI);
            ptr->unk_01 = 0;
            break;
        }
        ptr++;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80938EC0.s")
#endif

#ifdef NON_MATCHING
// Regalloc on the ZeroFloat
void func_80938FC4(GlobalContext* globalCtx, s32 arg1) {
    s16 i;
    BossTw1* ptr = (BossTw1*)globalCtx->unk_11E10;

    for (i = 0; i < 0x96; i++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 5;
            ptr->unk_10 = D_8094A7DC;
            ptr->unk_1C = D_8094A7DC;
            ptr->unk_01 = 0;
            ptr->unk_44 = arg1;
            ptr->unk_38 = 0.0f;
            ptr->unk_34 = 0.0f;
            ptr->unk_3C = 0.0f;
            if (arg1 == 0) {
                ptr->unk_2E = 0x64;
            } else {
                ptr->unk_2E = 0x14;
            }
            break;
        }
        ptr++;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80938FC4.s")
#endif

#ifdef NON_MATCHING
// Regalloc on the ZeroFloat
void func_80939070(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5) {
    s16 i;
    BossTw1* ptr = (BossTw1*)globalCtx->unk_11E10;

    for (i = 0; i < 0x96; i++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 6;
            ptr->unk_04 = *arg1;
            ptr->unk_10 = *arg2;
            ptr->unk_1C = *arg3;
            ptr->unk_34 = arg4 / 1000.0f;
            ptr->unk_2E = arg5;
            ptr->unk_30 = 0;
            ptr->unk_2C = 0;
            ptr->unk_01 = Math_Rand_ZeroFloat(1000.0f);
            break;
        }
        ptr++;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80939070.s")
#endif

#ifdef NON_MATCHING
// Regalloc on the ZeroFloat
void func_80939148(GlobalContext* globalCtx, Vec3f* arg1, f32 arg2, f32 arg3, s16 arg4) {
    s16 i;
    BossTw1* ptr = (BossTw1*)globalCtx->unk_11E10;

    for (i = 0; i < 0x96; i++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 7;
            ptr->unk_04 = *arg1;
            ptr->unk_10 = D_8094A7DC;
            ptr->unk_1C = D_8094A7DC;
            ptr->unk_34 = arg2 / 1000.0f;
            ptr->unk_2E = arg4;
            ptr->unk_30 = 0;
            ptr->unk_38 = arg3;
            ptr->unk_3C = Math_Rand_ZeroFloat(6.2831855f);
            ptr->unk_2C = 0;
            ptr->unk_01 = Math_Rand_ZeroFloat(1000.0f);
            break;
        }
        ptr++;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80939148.s")
#endif

#ifdef NON_MATCHING
// Regalloc on the ZeroFloat
void func_80939250(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, f32 arg5, s16 arg6, s16 arg7) {
    s16 i;
    BossTw1* ptr = (BossTw1*)globalCtx->unk_11E10;

    for (i = 0; i < 0x96; i++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 8;
            ptr->unk_04 = *arg1;
            ptr->unk_10 = *arg2;
            ptr->unk_1C = *arg3;
            ptr->unk_34 = arg4 / 1000.0f;
            ptr->unk_38 = arg5 / 1000.0f;
            ptr->unk_2E = arg7;
            ptr->unk_30 = 0;
            ptr->unk_2C = arg6;
            ptr->unk_01 = Math_Rand_ZeroFloat(1000.0f);
            break;
        }
        ptr++;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80939250.s")
#endif

#ifdef NON_MATCHING
// Regalloc on the ZeroFloat
void func_80939338(GlobalContext* globalCtx, f32 arg1, s16 arg2) {
    Player* player = PLAYER;
    s16 i;
    s16 j;
    BossTw1* ptr;

    D_8094C860 = player->unk_9BC;
    D_8094C86C = player->actor.shape.rot.y;
    
    for (i = 0; i < 8; i++) {
        ptr = (BossTw1*)globalCtx->unk_11E10;
        for (j = 0; j < 0x96; j++) {
            if (ptr->unk_00 == 0) {
                ptr->unk_00 = 9;
                ptr->unk_04 = D_8094C860;
                ptr->unk_10 = D_8094A7DC;
                ptr->unk_1C = D_8094A7DC;
                ptr->unk_3C = i * 0.7853982f;
                ptr->unk_40 = 1.5707964f;
                ptr->unk_38 = 0.0f;
                ptr->unk_34 = arg1 / 1000.0f;
                ptr->unk_2E = arg2;
                ptr->unk_30 = 0;
                ptr->unk_2C = 0xFF;
                ptr->unk_01 = Math_Rand_ZeroFloat(1000.0f);
                break;
            }
            ptr++;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80939338.s")
#endif

#ifdef NON_MATCHING
// Regalloc on the ZeroFloat
void func_809394FC(GlobalContext* globalCtx, f32 arg1, s16 arg2) {
    Player* player = PLAYER;
    s16 i;
    s16 j;
    BossTw1* ptr;

    D_8094C860 = player->unk_9BC;
    D_8094C86C = player->actor.shape.rot.y;
    
    for (i = 0; i < 8; i++) {
        ptr = (BossTw1*)globalCtx->unk_11E10;
        for (j = 0; j < 0x96; j++) {
            if (ptr->unk_00 == 0) {
                ptr->unk_00 = 0xA;
                ptr->unk_04 = D_8094C860;
                ptr->unk_10 = D_8094A7DC;
                ptr->unk_1C = D_8094A7DC;
                ptr->unk_3C = i * 0.7853982f;
                ptr->unk_40 = 1.5707964f;
                ptr->unk_38 = 0.0f;
                ptr->unk_34 = arg1 / 1000.0f;
                ptr->unk_2E = arg2;
                ptr->unk_30 = 0;
                ptr->unk_2C = 0xFF;
                ptr->unk_01 = Math_Rand_ZeroFloat(1000.0f);
                break;
            }
            ptr++;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809394FC.s")
#endif

#ifdef NON_MATCHING
// Assignments in the middle
void BossTw_Init(Actor* thisx, GlobalContext* globalCtx) {
    BossTw* this = THIS;
    s16 i;
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&thisx->shape, 0.0f, NULL, 0.0f);

    if (thisx->params >= 0x64) {
        Actor_SetScale(&this->actor, 0.01f);
        thisx->update = func_80946B00;
        thisx->draw = func_80946C7C;
        thisx->flags &= -2;
        Collider_InitCylinder(globalCtx, &this->collider);
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit1);
        if ((thisx->params == 0x64) || (thisx->params == 0x65)) {
            this->actionFunc = func_809453EC;
            this->collider.body.toucher.effect = 1;
        } else if ((thisx->params == 0x66) || (thisx->params == 0x67)) {
            this->actionFunc = func_80945D14;
        } else if (thisx->params >= 0x68) {
            this->actionFunc = func_8093EE10;
            thisx->draw = func_80947240;
            this->unk_1AC = 128.0f;
            if (thisx->params == 0x68) {
                thisx->posRot.rot.y = D_8094C84C->actor.posRot.rot.y + 0x4000;
            } else {
                thisx->posRot.rot.y = D_8094C84C->actor.posRot.rot.y - 0x4000;
            }
        }
        this->unk_178[1] = 0x96;
        return;
    }
    Actor_SetScale(&this->actor, 0.024999999f);
    thisx->colChkInfo.mass = 0xFF;
    thisx->colChkInfo.health = 0;
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
        D_8094C851 &= 0xFFFF;
        D_8094C87E = D_8094C86F = D_8094C870 = D_8094C872;

        D_8094C874 = D_8094C876 = D_8094C878 = D_8094C87A = D_8094C87C = D_8094C872 & 0xFF;

        D_8094C858 = D_8094C854 = 0.0f;
        D_8094C85D = Math_Rand_ZeroFloat(1.99f);
        globalCtx->unk_11E10 = (u8*)D_8094C880;
        for (i = 0; i < 0x96; i++) {
            D_8094C880[i].unk_00 = 0;
        }
    }
    if (thisx->params == 0) {
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit2);
        thisx->naviEnemyId = 0x33;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060070E0, &D_06006F28, 0, 0, 0);
        if (gSaveContext.eventChkInf[7] & 0x20) {
            func_8093A0A8(this, globalCtx);
            thisx->posRot.pos.x = -600.0f;
            thisx->posRot.pos.y = 400.0f;
            thisx->posRot.pos.z = 0.0f;
            Audio_SetBGM(0x1B);
        } else {
            func_8093D54C(this, globalCtx);
        }
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06006F28, -3.0f);
        this->unk_564 = 1;
    } else if (thisx->params == 1) {
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit2);
        thisx->naviEnemyId = 0x32;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0601F888, &D_06006F28, 0, 0, 0);
        if (gSaveContext.eventChkInf[7] & 0x20) {
            func_8093A0A8(this, globalCtx);
            thisx->posRot.pos.x = 600.0f;
            thisx->posRot.pos.y = 400.0f;
            thisx->posRot.pos.z = 0.0f;
        } else {
            func_8093D54C(this, globalCtx);
        }
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06006F28, -3.0f);
        this->unk_564 = 1;
    } else {
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit3);
        thisx->naviEnemyId = 0x5B;
        thisx->colChkInfo.health = 0x18;
        thisx->update = func_80940D48;
        thisx->draw = func_80945084;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06032020, &D_060244B4, 0, 0, 0);
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_060244B4, -3.0f);
        if (gSaveContext.eventChkInf[7] & 0x20) {
            func_8093C824(this, globalCtx);
        } else {
            func_8093D58C(this, globalCtx);
            thisx->posRot.pos.x = 0.0f;
            thisx->posRot.pos.y = 1000.0f;
            thisx->posRot.pos.z = 0.0f;
        }
        thisx->params = 2;
        D_8094C84C = this;
        if (Flags_GetClear(globalCtx, globalCtx->roomCtx.curRoom.num)) {
            Actor_Kill(&this->actor);
            Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_DOOR_WARP1, 600.0f, 230.0f, 0.0f, 0, 0, 0, -1);
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_ITEM_B_HEART, -600.0f, 230.0f, 0.0f, 0, 0, 0, 0);
        } else {
            D_8094C844 = Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_TW, thisx->posRot.pos.x, thisx->posRot.pos.y, thisx->posRot.pos.z, 0, 0, 0, 0);
            D_8094C848 = Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_TW, thisx->posRot.pos.x, thisx->posRot.pos.y, thisx->posRot.pos.z, 0, 0, 0, 1);
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

void BossTw_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BossTw* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    if (thisx->params < 100) {
        SkelAnime_Free(&this->skelAnime, globalCtx);
    }
    if (thisx->params == 2) {
        D_8094A89C = 0;
    }
}

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

void func_8093C684(BossTw* this, GlobalContext* globalCtx);
void func_8093A2AC(BossTw* this, GlobalContext* globalCtx);
void func_8093C700(BossTw* this, GlobalContext* globalCtx);
void func_80939F88(BossTw* this, GlobalContext* globalCtx);
void func_8093C858(BossTw* this, GlobalContext* globalCtx);
void func_8093C7E4(BossTw* this, GlobalContext* globalCtx);

void func_80938CD0(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5, s16 arg6);

#ifdef NON_MATCHING
// sp68 and sp5c need to be on the stack and it should match
// if if lines near the bottom can show it, but still not matching and obv wrong
void BossTw_Update(Actor* thisx, GlobalContext* globalCtx) {
    BossTw* this = THIS;
    Player* player = PLAYER;

    s16 tmp16;
    Vec3f sp74;
    s16 i;
    Vec3f sp68;

    Vec3f sp5C;
    

    this->collider.base.type = 3;
    Math_SmoothScaleMaxF(&this->unk_1D4, globalCtx->lightCtx.unk_07, 1.0f, 10.0f);
    Math_SmoothScaleMaxF(&this->unk_1D8, globalCtx->lightCtx.unk_08, 1.0f, 10.0f);
    Math_SmoothScaleMaxF(&this->unk_1DC, globalCtx->lightCtx.unk_09, 1.0f, 10.0f);
    Math_SmoothScaleMaxF(&this->unk_1E0, globalCtx->lightCtx.unk_0A, 1.0f, 10.0f);
    Math_SmoothScaleMaxF(&this->unk_1E4, 1000.0f, 1.0f, 10.0f);
    this->unk_150++;
    this->unk_152++;
    this->unk_156++;
    
    if (this->unk_156 >= 50) {
        this->unk_156 = 0;
    }
    this->unk_1E8[this->unk_156] = this->actor.posRot.pos;
    for (i = 0; i < 5; i++) {
        if (this->unk_178[i] != 0) {
            this->unk_178[i]--;
        }
    }
    if (this->unk_15A != 0) {
        this->unk_15A--;
    }
    if (this->unk_15C != 0) {
        this->unk_15C--;
    }
    if ((this->actionFunc == func_8093A2AC) || (this->actionFunc == func_8093C700) || (this->actionFunc == func_80939F88)) {
        tmp16 = (player->actor.shape.rot.y - this->actor.yawTowardsLink) + 0x8000;
        if ((tmp16 < 0x1000) && (tmp16 >= -0xFFF) && (player->unk_A73 != 0)) {
            func_8093C684(this, globalCtx);
        }
    }
    this->actionFunc(this, globalCtx);
    if (this->actionFunc != func_8093C858) {
        this->collider.dim.radius = 0x2D;
        if (this->actionFunc == func_8093C700) {
            this->collider.dim.radius *= 2;
        }
        this->collider.dim.height = 0x78;
        this->collider.dim.yShift = -0x1E;
        if (this->unk_15A == 0) {
            if (this->collider.base.acFlags & 2) {
                this->collider.base.acFlags &= ~2;
            }
            Collider_CylinderUpdate(&this->actor, &this->collider);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
        if (this->actor.params == 0) {
            this->unk_188 += 1.0f;
            this->unk_198 -= 7.0f;
            this->unk_19C += 1.0f;
        } else {
            this->unk_188 = this->unk_188;
            this->unk_190 = this->unk_190;
            this->unk_198 += -15.0f;
            this->unk_1A0 += -10.0f;
        }
        if (!(this->unk_152 & 0x1F) && (Math_Rand_ZeroOne() < 0.3f)) {
            this->unk_158 = 4;
        }
        this->unk_4CC = D_8094A900[this->unk_158];
        if (this->unk_158 != 0) {
            this->unk_158--;
        }
        if ((this->actionFunc != func_8093C7E4) && (this->unk_5F8 != 0)) {
            sp68 = D_8094A920;
            sp5C = D_8094A92C;
            if (this->unk_4D0 > 0.0f) {
                for (i = 0; i <= 0; i++) {
                    sp74 = this->unk_450;
                    sp74.x += Math_Rand_CenteredFloat(70.0f);
                    sp74.y += Math_Rand_CenteredFloat(70.0f);
                    sp74.z += Math_Rand_CenteredFloat(70.0f);
                    sp5C.x = Math_Rand_CenteredFloat(0.5f);
                    sp5C.y = 0.4f;
                    sp5C.z = Math_Rand_CenteredFloat(0.5f);
                    func_80938CD0(globalCtx, &sp74, &sp68, &sp5C, (s16)Math_Rand_ZeroFloat(2.0f) + 8, this->actor.params, 0x25);
                }
            }
            for (i = 0; i <= 0; i++) {
                sp74 = this->unk_444;
                sp74.x += Math_Rand_CenteredFloat(70.0f);
                sp74.y += Math_Rand_CenteredFloat(70.0f);
                sp74.z += Math_Rand_CenteredFloat(70.0f);
                sp5C.x = Math_Rand_CenteredFloat(0.5f);
                sp5C.y = 0.4f;
                sp5C.z = Math_Rand_CenteredFloat(0.5f);
                func_80938CD0(globalCtx, &sp74, &sp68, &sp5C, (s16)Math_Rand_ZeroFloat(2.0f) + 8, this->actor.params, 0x25);
            }
        }
        //if (&sp68){};
        //if (&sp5C){};
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/BossTw_Update.s")
#endif

void func_80940D48(BossTw* this, GlobalContext* globalCtx);

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80940D48.s")

void func_8093D444(BossTw* this, GlobalContext* globalCtx);

s32 func_809416D0(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    BossTw* this = THIS;

    if ((limbIndex == 21) && (this->unk_5F8 == 0)) {
        if (this->actor.params == 0) {
            *dList = &D_06012CE0;
        } else {
            *dList = &D_060134B8;
        }
    }
    if (limbIndex == 14) {
        if (this->actionFunc == func_8093D444) {
            *dList = NULL;
        } else if (this->unk_4D0 == 0.0f) {
            if (this->actor.params == 0) {
                *dList = &D_06012B38;
            } else {
                *dList = &D_06013310;
            }
        }
    }
    return 0;
}

#ifdef NON_MATCHING
void func_80941788(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    BossTw* this = THIS;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1818);

        switch (limbIndex) {
            case 21:
                Matrix_MultVec3f(&D_8094A944, &thisx->posRot2.pos);
                Matrix_MultVec3f(&D_8094A950, &this->unk_444);
                if (this->unk_5F8 != 0) {
                    gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x182E), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    if (this->actor.params == 0) {
                        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_06013AE8));
                    } else {
                        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_06013D68));
                    }
                }
                break;
            case 14:
                Matrix_MultVec3f(&D_8094A95C, &this->unk_450);
                Matrix_MultVec3f(&D_8094A968, &this->unk_45C);
                Matrix_MultVec3f(&D_8094A974, &this->unk_468);
                Matrix_MultVec3f(&D_8094A980, &this->unk_474);
                Matrix_MultVec3f(&D_8094A98C, &this->unk_480);
                if (this->unk_4D0 > 0.0f) {
                    gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x184D), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    if (this->actor.params == 0) {
                        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xE1, 0xFF, (s8)this->unk_4D0);
                        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_06013E98));
                        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xC3, 0xE1, 0xEB, (s8)this->unk_4D0);
                        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_06013F98));
                    } else {
                        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x64, 0x14, 0x00, (s8)this->unk_4D0);
                        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_06014070));
                        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0x46, 0x00, (s8)this->unk_4D0);
                        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_06014158));
                    }
                }
                break;
        }

        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x185C);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80941788.s")
#endif

#ifdef NON_MATCHING
// gSegments
void func_80941BC0(BossTw* this, GlobalContext* globalCtx) {

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x18C5);
        Matrix_Push();
        func_80093D84(globalCtx->state.gfxCtx);
        Matrix_Translate(this->unk_4BC, this->unk_4C0, this->unk_4C4, 0);
        Matrix_Scale(this->unk_1B4, this->unk_1B4, this->unk_1B4, 1);

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x18D6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, (s16)this->unk_1B0);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x00, 0x28, 0x1E, 0x50);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_0601BC00));
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xD7, 0xD7, 0xD7, this->unk_1BC * (s16)this->unk_1B0);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xFF, 0xFF, 0x80);
        gSPSegment(gfxCtx->polyXlu.p++, 0x08, 
            Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 
                    (u8)this->unk_1C4 & 0x3F, (u8)(this->unk_152 * 4) & 0x3F, 0x10, 0x10));

        Matrix_Push();
        Matrix_RotateY(this->unk_1C0, 1);

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1917), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_0601C1C0));

        Matrix_Pull();

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x191B), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfxCtx->polyXlu.p++, 0x0D, 
            Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
                this->unk_152 & 0x7F, (this->unk_152 * 8) & 0xFF, 
                0x20, 0x40, 1, (-this->unk_152 * 2) & 0x3F, 0, 0x10, 0x10));
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xC3, 0xE1, 0xEB, (s8)this->unk_1A8);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xFF, 0xFF, 0x80);
        gDPSetRenderMode(gfxCtx->polyXlu.p++, G_RM_FOG_SHADE_A, G_RM_ZB_OVL_SURF2);
        gSPSetGeometryMode(gfxCtx->polyXlu.p++, G_CULL_BACK | G_FOG);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_0601A790));

        Matrix_Pull();

        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x193D);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80941BC0.s")
#endif

#ifdef NON_MATCHING
// gSegments
void func_80942180(BossTw* this, GlobalContext* globalCtx) {
    s32 pad;
    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1944);
        Matrix_Push();
        func_80093D84(globalCtx->state.gfxCtx);
        Matrix_Translate(this->unk_4BC, this->unk_4C0, this->unk_4C4, 0);
        Matrix_Scale(this->unk_1B8, this->unk_1B8, this->unk_1B8, 1);

        gSPSegment(gfxCtx->polyXlu.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, (0 - this->unk_150) & 0x7F, 0, 0x20, 0x20, 1, (this->unk_150 * 2) & 0x7F, 0, 0x20, 0x20));
        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1961), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x64, 0x28, 0x00, (s8)this->unk_1B0);
        gDPPipeSync(gfxCtx->polyXlu.p++);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xF5, 0xFF, 0x80);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_06019D40));

        func_800D1FD4(&globalCtx->mf_11DA0);

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1972), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfxCtx->polyXlu.p++, 0x08, 
            Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
                this->unk_150 & 0x7F, (-this->unk_150 * 6) & 0xFF, 
                0x20, 0x40, 1, 
                (this->unk_150 * 2) & 0x7F, (-this->unk_150 * 6) & 0xFF, 
                0x20, 0x40));
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x50, 0x00, 0x00, (s8)this->unk_1AC);
        gDPPipeSync(gfxCtx->polyXlu.p++);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x00, 0x00, 0x00, 0x64);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_06018FC0));
        gSPSegment(gfxCtx->polyXlu.p++, 0x08, 
            Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
                (-this->unk_150 * 3) & 0x7F, 0, 
                0x20, 0x20, 1, 0, (-this->unk_150 * 10) & 0xFF, 
                0x20, 0x40));
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x64, 0x32, 0x00, (s8)(this->unk_1A8 * 0.7f));
        gDPPipeSync(gfxCtx->polyXlu.p++);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xC8, 0xEB, 0xF0, 0x80);

        Matrix_Scale(this->unk_1B4, this->unk_1B4, this->unk_1B4, 1);

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x19AF), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_06019938));

        Matrix_Pull();

        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x19B3);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80942180.s")
#endif

#ifdef NON_MATCHING
// gSegments
void func_809426F0(BossTw* this, GlobalContext* globalCtx) {
    s16 i;
    f32 tmpf1;
    UNK_PTR gSeg;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x19BB);

        gSPSegment(gfxCtx->polyXlu.p++, 0x08, 
            Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
                0, (-this->unk_152 * 15) & 0xFF, 
                0x20, 0x40, 1, 0, 0, 
                0x40, 0x40));

        Matrix_Push();
        Matrix_Translate(0.0f, 0.0f, 5000.0f, 1);
        tmpf1 = this->unk_4E0 / 2000.0f;
        Matrix_Scale(tmpf1, tmpf1, tmpf1, 1);
        Matrix_RotateZ(this->unk_4EC, 1);

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x19D6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if (this->actor.params == 0) {
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x87, 0xAF, 0xA5, (s8)this->unk_4D8);
            gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_0601CEE0));
        } else {
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0x00, (s8)this->unk_4D8);
            gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_0601DBE8));
        }

        Matrix_Pull();

        if (this->actor.params == 0) {
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xC3, 0xE1, 0xEB, (s8)this->unk_4D4);
            gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_0601A998));
        } else {
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xC8, 0x14, 0x00, (s8)this->unk_4D4);
            gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xD7, 0xFF, 0x80);
        }

        gSeg = SEGMENTED_TO_VIRTUAL(D_0601A430);
        for (i = 0; i < 8; i++) {
            Matrix_Push();
            Matrix_Translate(0.0f, 0.0f, 5000.0f, 1);
            Matrix_RotateZ((((i * M_PI) + (i * M_PI)) * 0.125f) + this->unk_4E8, 1);
            Matrix_Translate(0.0f, this->unk_4E0 * 1.5f, 0.0f, 1);

            gSPSegment(gfxCtx->polyXlu.p++, 0x08, 
                Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
                    ((this->unk_152 * 3) + (i * 10)) & 0x7F, ((-this->unk_152 * 0xF) + (i * 50)) & 0xFF, 
                    0x20, 0x40, 1, 0, 0, 0x20, 0x20));

            Matrix_Scale(0.4f, 0.4f, 0.4f, 1);
            func_800D1FD4(&globalCtx->mf_11DA0);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1A5F), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, gSeg);

            Matrix_Pull();
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1A64);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809426F0.s")
#endif

#ifdef NON_MATCHING
// gSegments
void func_80942C70(BossTw* this, GlobalContext* globalCtx) {
    s16 tmpf1;
    s32 pad;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];
        s32 pad2;
        s32 pad3;

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1A6D);

        if (this->unk_52C != 0.0f) {
            Matrix_Push();

            gSPSegment(gfxCtx->polyXlu.p++, 0x0C, 
                Gfx_TexScroll(globalCtx->state.gfxCtx, 0, 
                    (-this->unk_150 * 0xF) & 0xFF, 0x20, 0x40));

            tmpf1 = (this->unk_4F8 * 100.0f) * 255.0f;
            if (this->actor.params == 1) {
                gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0x3C, (s8)tmpf1);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0x00, 0x00, 0x80);
            } else {
                gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, (s8)tmpf1);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x64, 0x64, 0xFF, 0x80);
            }

            Matrix_Translate(this->unk_48C.x, this->unk_48C.y, this->unk_48C.z, 0);
            Matrix_RotateY(this->unk_51C, 1);
            Matrix_RotateX(this->unk_518, 1);
            Matrix_RotateZ(this->unk_520, 1);
            Matrix_Scale(this->unk_4F8, this->unk_4F8, ((this->unk_52C * 0.01f) * 98.0f) / 20000.0f, 1);
            
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1ABE), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            
            gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_0601DDF0));

            if (this->unk_548 > 10.0f) {
                Matrix_Translate(this->unk_50C, this->unk_510, this->unk_514, 0);
                Matrix_RotateY(this->unk_540, 1);
                Matrix_RotateX(this->unk_53C, 1);
                Matrix_RotateZ(this->unk_520, 1);
                Matrix_Scale(this->unk_4F8, this->unk_4F8, ((this->unk_548 * 0.01f) * 100.0f) / 20000.0f, 1);
                
                gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1AD6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gfxCtx->polyXlu.p++, PHYSICAL_TO_VIRTUAL(D_0601DDF0) + SEGMENT_OFFSET(D_0601DDF0));

            }
            Matrix_Pull();
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1ADE);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80942C70.s")
#endif

#ifdef NON_MATCHING
// gSegments
void func_80943028(BossTw *this, GlobalContext *globalCtx) {
    f32 tmpf1;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1AE5);
        Matrix_Push();
        Matrix_Translate(this->actor.posRot.pos.x, this->actor.posRot.pos.y + 57.0f, this->actor.posRot.pos.z, 0);
        Matrix_Scale(this->unk_1C8, this->unk_1C8, this->unk_1C8, 1);

        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1AFC), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_0601F608));

        func_80094044(globalCtx->state.gfxCtx);

        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x00, 0x00, 0x00, 0xC8);

        Matrix_Translate(this->actor.posRot.pos.x, 240.0f, this->actor.posRot.pos.z, 0);
        tmpf1 = (this->actor.scale.x * 4000.0f) / 100.0f;
        Matrix_Scale(tmpf1, 1.0f, tmpf1, 1);

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1B0E), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_04049210));

        Matrix_Pull();
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1B15);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80943028.s")
#endif

#ifdef NON_MATCHING
void BossTw_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BossTw* this = THIS;
    s32 pad;
    Player* player = PLAYER;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];
        f32 tmpf1;
        f32 tmpf2;
        s32 pad2;


        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1B23);
        if (this->unk_564 != 0) {
            gSPSegment(gfxCtx->polyOpa.p++, 0x0A, SEGMENTED_TO_VIRTUAL(D_8094A998[this->unk_4CC]));
            gSPSegment(gfxCtx->polyXlu.p++, 0x0A, SEGMENTED_TO_VIRTUAL(D_8094A998[this->unk_4CC]));
            gSPSegment(gfxCtx->polyXlu.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
                (s16)this->unk_184 & 0x7F, (s16)this->unk_194 & 0x7F, 0x20, 0x20, 1, 
                (s16)this->unk_188 & 0x7F, (s16)this->unk_198 & 0xFF, 0x20, 0x40));
            
            if (this->actor.params == 0) {
                gSPSegment(gfxCtx->polyXlu.p++, 0x09, Gfx_TexScroll(globalCtx->state.gfxCtx, 
                    (s16)this->unk_18C & 0x7F, (s16)this->unk_19C & 0xFF, 0x20, 0x40));
            } else {
                gSPSegment(gfxCtx->polyXlu.p++, 0x09, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
                    (s16)this->unk_18C & 0x7F, (s16)this->unk_19C & 0x7F, 0x20, 0x20, 1, 
                    (s16)this->unk_190 & 0x7F, (s16)this->unk_1A0 & 0xFF, 0x20, 0x40));
            }

            func_80093D18(globalCtx->state.gfxCtx);
            func_80093D84(globalCtx->state.gfxCtx);
            if (this->unk_15C & 2) {
                gfxCtx->polyOpa.p = Gfx_SetFog(gfxCtx->polyOpa.p, 
                    0xFF, 0x32, 0, 0, 0x384, 0x44B);
            } else {
                gfxCtx->polyOpa.p = Gfx_SetFog(gfxCtx->polyOpa.p, 
                    this->unk_1D4, this->unk_1D8, 
                    this->unk_1DC, 0, 
                    this->unk_1E0, this->unk_1E4);
            }

            Matrix_Push();
            SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, func_809416D0, func_80941788, &this->actor);
            Matrix_Pull();
            gfxCtx->polyOpa.p = func_800BC8A0(globalCtx, gfxCtx->polyOpa.p);
        }
        if (thisx->params == 0) {
            if (0.0f < this->unk_1A8) {
                if (0.0f < this->unk_1B0) {
                    tmpf1 = this->unk_4BC - player->actor.posRot.pos.x;
                    tmpf2 = this->unk_4C4 - player->actor.posRot.pos.z;
                    if ((fabsf(this->unk_4C0 - player->actor.posRot.pos.y) < 10.0f) && 
                        (player->actor.bgCheckFlags & 1) && 
                        (sqrtf(SQ(tmpf1) + SQ(tmpf2)) < (this->unk_1B4 * 4600.0f)) && 
                        (D_8094C85F == 0) && 
                        (200.0f < this->unk_1B0)) {
                        D_8094C85F = 1;
                        D_8094C84C->unk_178[2] = 0x64;
                    }
                }
                func_80941BC0(this, globalCtx);
            }
        } else {
            func_80942180(this, globalCtx);
        }
        if (this->unk_564) {
            if (this->actionFunc == func_8093D444) {
                func_80943028(this, globalCtx);
            } else {
                func_809426F0(this, globalCtx);
                Matrix_MultVec3f(&D_8094A9A4, &this->unk_48C);
                func_80942C70(this, globalCtx);
            }
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1BD3);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/BossTw_Draw.s")
#endif

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
