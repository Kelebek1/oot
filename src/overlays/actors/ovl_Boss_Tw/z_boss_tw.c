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
void func_80948668(GlobalContext* globalCtx);
void func_8093B1AC(BossTw* this, GlobalContext* globalCtx);
void func_80939F88(BossTw* this, GlobalContext* globalCtx);
void func_8093A2AC(BossTw* this, GlobalContext* globalCtx);
void func_8093A4DC(BossTw* this, GlobalContext* globalCtx);
void func_8093C858(BossTw* this, GlobalContext* globalCtx);


extern AnimationHeader D_06006F28;
extern SkeletonHeader D_060070E0;
extern AnimationHeader D_06007688;
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
extern UNK_PTR D_0601E020;
extern UNK_PTR D_0601E0E0;
extern UNK_PTR D_0601E2C0;
extern UNK_PTR D_0601E3A0;
extern UNK_PTR D_0601E9F0;
extern UNK_PTR D_0601EC68;
extern UNK_PTR D_0601EEB0;
extern UNK_PTR D_0601F238;
extern UNK_PTR D_0601F390;
extern UNK_PTR D_0601F608;
extern SkeletonHeader D_0601F888;
extern AnimationHeader D_060244B4;
extern Gfx D_0602D890[];
extern Gfx D_0602D940[];
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

Vec3f D_8094A8AC[] = {
    {600.0f, 400.0f, 0.0f}, 
    {0.0f, 400.0f, 600.0f}, 
    {-600.0f, 400.0f, 0.0f}, 
    {0.0f, 400.0f, -600.0f}, 
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
UNK_PTR D_8094A9B0[] = { 0x0602A9B0, 0x0602A070, 0x0602A470 };
Vec3f D_8094A9BC = { 0.0f, 0.0f, 0.0f };
Vec3f D_8094A9C8 = { 0.0f, 2000.0f, -2000.0f };
Vec3f D_8094A9D4 = { 13000.0f, 0.0f, 0.0f };
Vec3f D_8094A9E0 = { 13000.0f, 0.0f, 0.0f };
Vec3f D_8094A9EC = { 0.0f, 200.0f, 2000.0f };
Vec3f D_8094A9F8 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8094AA04 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8094AA10 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8094AA1C = { 0.0f, 0.0f, 0.0f };

s8 D_8094C840;
u8 D_8094C841;
BossTw* D_8094C844;
BossTw* D_8094C848;
BossTw* D_8094C84C;
u8 D_8094C850;
u8 D_8094C851;
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
s16 D_8094C872;
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

void func_80939070(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5);
void func_80938CD0(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5, s16 arg6);
void func_80939250(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, f32 arg5, s16 arg6, s16 arg7);
void func_80938DC4(GlobalContext* globalCtx, s16 arg1, Vec3f* arg2, Vec3f* arg3, Vec3f* arg4, f32 arg5, s16 arg6, s16 arg7, s16 arg8);

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
            ptr->unk_01 = (s16)Math_Rand_ZeroFloat(10.0f);
            ptr->unk_2E = arg5;
            break;
        }
        ptr++;
    }
}

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
            ptr->unk_01 = (s16)Math_Rand_ZeroFloat(100.0f);
            break;
        }
        ptr++;
    }
}

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
            ptr->unk_3C = (s16)Math_Rand_ZeroFloat(M_PI);
            ptr->unk_01 = 0;
            break;
        }
        ptr++;
    }
}

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
            ptr->unk_01 = (s16)Math_Rand_ZeroFloat(1000.0f);
            break;
        }
        ptr++;
    }
}

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
            ptr->unk_01 = (s16)Math_Rand_ZeroFloat(1000.0f);
            break;
        }
        ptr++;
    }
}

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
            ptr->unk_01 = (s16)Math_Rand_ZeroFloat(1000.0f);
            break;
        }
        ptr++;
    }
}

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
                ptr->unk_01 = (s16)Math_Rand_ZeroFloat(1000.0f);
                break;
            }
            ptr++;
        }
    }
}

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
                ptr->unk_01 = (s16)Math_Rand_ZeroFloat(1000.0f);
                break;
            }
            ptr++;
        }
    }
}

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
            D_8094C844 = (BossTw*)Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_TW, thisx->posRot.pos.x, thisx->posRot.pos.y, thisx->posRot.pos.z, 0, 0, 0, 0);
            D_8094C848 = (BossTw*)Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_TW, thisx->posRot.pos.x, thisx->posRot.pos.y, thisx->posRot.pos.z, 0, 0, 0, 1);
            D_8094C844->actor.attachedA = &D_8094C848->actor;
            D_8094C848->actor.attachedA = &D_8094C844->actor;
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

void func_80939F40(BossTw* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80939F88;
    if ((this->actor.attachedA != NULL) && (((BossTw*)this->actor.attachedA)->actionFunc == func_8093B1AC)) {
        this->unk_178[0] = 0x28;
    } else {
        this->unk_178[0] = 0x3C;
    }
    this->unk_4C8 = 0.0f;
}

void func_80939F88(BossTw* this, GlobalContext* globalCtx) {
    BossTw* sp24 = (BossTw*)this->actor.attachedA;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothScaleMaxF(&this->actor.speedXZ, 0.0f, 1.0f, 1.0f);
    Math_SmoothScaleMaxS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 5, this->unk_4C8);
    Math_SmoothScaleMaxS(&this->actor.shape.rot.x, 0, 5, this->unk_4C8);
    Math_SmoothScaleMaxF(&this->unk_4C8, 4096.0f, 1.0f, 200.0f);
    func_8002D908(&this->actor);
    func_8002D7EC(&this->actor);
    if (this->unk_178[0] == 0) {
        if ((sp24->actionFunc != func_8093B1AC) && (this->unk_15E != 0)) {
            this->unk_15E = 0;
            func_8093A4DC(this, globalCtx);
            this->actor.speedXZ = 0.0f;
        } else {
            func_8093A0A8(this, globalCtx);
        }
    }
}

void func_8093A0A8(BossTw* this, GlobalContext* globalCtx) {
    BossTw* sp24 = (BossTw*)this->actor.attachedA;

    this->unk_5F8 = 1;
    this->actor.flags |= 1;
    this->actionFunc = func_8093A2AC;
    this->unk_4C8 = 0.0f;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06006F28, -10.0f);
    if ((Math_Rand_ZeroOne() < 0.5f) && 
        (sp24 != NULL) && (sp24->actionFunc == func_8093B1AC)) {
        this->unk_4B0.x = Math_Rand_CenteredFloat(200.0f) + sp24->actor.posRot.pos.x;
        this->unk_4B0.y = Math_Rand_ZeroFloat(200.0f) + 340.0f;
        this->unk_4B0.z = Math_Rand_CenteredFloat(200.0f) + sp24->actor.posRot.pos.z;
        this->unk_178[0] = (s16)Math_Rand_ZeroFloat(50.0f) + 0x32;
    } else if (Math_Rand_ZeroOne() < 0.5f) {
        this->unk_4B0.x = Math_Rand_CenteredFloat(800.0f);
        this->unk_4B0.y = Math_Rand_ZeroFloat(200.0f) + 340.0f;
        this->unk_4B0.z = Math_Rand_CenteredFloat(800.0f);
        this->unk_178[0] = (s16)Math_Rand_ZeroFloat(50.0f) + 0x32;
    } else {
        this->unk_4B0 = D_8094A8AC[(s16)Math_Rand_ZeroFloat(3.99f)];
        this->unk_178[0] = 0xC8;
        this->unk_15E = 1;
    }
}

void func_8093A2AC(BossTw *this, GlobalContext *globalCtx) {
    f32 tmpf1;
    f32 tmpf2;
    f32 tmpf3;
    f32 atan2;
    f32 atan1;
    f32 sqrt;

    Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_FLY - SFX_FLAG);
    Math_SmoothScaleMaxF(&this->unk_4D0, 0.0f, 1.0f, 10.0f);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    tmpf1 = this->unk_4B0.x - this->actor.posRot.pos.x;
    tmpf2 = this->unk_4B0.y - this->actor.posRot.pos.y;
    tmpf3 = this->unk_4B0.z - this->actor.posRot.pos.z;
    
    atan1 = (s16)(Math_atan2f(tmpf1, tmpf3) * 10430.378f);
    sqrt = sqrtf(SQ(tmpf1) + SQ(tmpf3));
    atan2 = (s16)(Math_atan2f(tmpf2, sqrt) * 10430.378f);

    Math_SmoothScaleMaxS(&this->actor.posRot.rot.x, atan2, 0xA, this->unk_4C8);
    Math_SmoothScaleMaxS(&this->actor.posRot.rot.y, atan1, 0xA, this->unk_4C8);
    Math_SmoothScaleMaxS(&this->actor.shape.rot.y, atan1, 0xA, this->unk_4C8);
    Math_SmoothScaleMaxS(&this->actor.shape.rot.x, atan2, 0xA, this->unk_4C8);
    Math_SmoothScaleMaxF(&this->unk_4C8, 4096.0f, 1.0f, 100.0f);
    Math_SmoothScaleMaxF(&this->actor.speedXZ, 10.0f, 1.0f, 1.0f);
    func_8002D908(&this->actor);
    func_8002D7EC(&this->actor);
    if ((this->unk_178[0] == 0) || (sqrt < 70.0f)) {
        func_80939F40(this, globalCtx);
    }
}

void func_8093A4DC(BossTw* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->actionFunc = func_8093B1AC;
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06007688, -5.0f);
    this->unk_1A4 = SkelAnime_GetFrameCount(&D_06007688.genericHeader);
    this->unk_178[1] = 0x46;
    
    this->unk_4B0 = player->actor.posRot.pos;
    this->unk_52C = this->unk_548 = 0.0f;
    this->unk_440 = 0;
    this->unk_4FC = -1;
    this->unk_4F8 = 0.01f;

    this->unk_4D4 = this->unk_4D8 = 
    this->unk_4E4 = this->unk_4EC = this->unk_4F0 = 0.0f;

    this->unk_50C = this->unk_48C;
    this->unk_4E0 = 2000.0f;
    
}

void func_8093A5C4(BossTw* this, GlobalContext* globalCtx, s16 arg2) {
    s16 i;
    BossTw* refActor;
    Vec3f spA4;
    Vec3f sp98;
    Vec3f sp8C;

    for (i = 0; i < 0x96; i++) {
        sp98.x = Math_Rand_CenteredFloat(20.0f);
        sp98.y = Math_Rand_ZeroFloat(10.0f);
        sp98.z = Math_Rand_CenteredFloat(20.0f);
        sp8C.y = 0.2f;
        sp8C.x = Math_Rand_CenteredFloat(0.25f);
        sp8C.z = Math_Rand_CenteredFloat(0.25f);
        spA4 = this->unk_500;
        func_80938CD0(globalCtx, &spA4, &sp98, &sp8C, (s16)Math_Rand_ZeroFloat(2.0f) + 8, arg2, 0x4B);
    }
    if (arg2 == 1) {
        D_8094C841 = 1;
        refActor = (BossTw*)Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_TW, 
            this->unk_500.x, this->unk_500.y, this->unk_500.z, 0, 0, 0, 0x65);
        if (refActor != NULL) {
            if (D_8094C84C->actionFunc == func_8093C858) {
                refActor->unk_178[0] = 0x64;
            } else {
                refActor->unk_178[0] = 0x32;
            }
            D_8094C848->unk_1A8 = D_8094C848->unk_1AC = D_8094C848->unk_1B0 = 255.0f;
            D_8094C848->unk_1B4 = 1.0f;
            D_8094C848->unk_1B8 = 0.005f;
            D_8094C848->unk_4BC = refActor->actor.posRot.pos;
            D_8094C840 = 4;
        }
    } else {
        D_8094C841 = 2;
        refActor = (BossTw*)Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_TW, 
            this->unk_500.x, this->unk_500.y, this->unk_500.z, 0, 0, 0, 0x67);
        if (refActor != NULL) {
            if (D_8094C84C->actionFunc == func_8093C858) {
                refActor->unk_178[0] = 0x64;
            } else {
                refActor->unk_178[0] = 0x32;
            }
            D_8094C844->unk_1B0 = 50.0f;
            D_8094C844->unk_1A8 = 250.0f;
            D_8094C844->unk_1B4 = 0.005f;
            D_8094C844->unk_1BC = 1.0f;
            D_8094C844->unk_1C4 = 70.0f;
            D_8094C844->unk_4BC = refActor->actor.posRot.pos;
            D_8094C840 = 3;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093A940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093AB30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093ADB4.s")

f32 func_8093AED8(Vec3f* arg0) {
    Vec3f sp2C;

    if ((fabsf(arg0->x) < 350.0f) && (fabsf(arg0->z) < 350.0f) && (arg0->y < 240.0f)) {
        if (200.0f < arg0->y) {
            return 240.0f;
        }
        return 35.0f;
    }

    if ((fabsf(arg0->x) < 110.0f) && ((fabsf(arg0->z - 600.0f) < 110.0f) || (fabsf(arg0->z + 600.0f) < 110.0f)) && (arg0->y < 230.0f)) {
        if (190.0f < arg0->y) {
            return 230.0f;
        } else {
            return 35.0f;
        }
    }

    if ((fabsf(arg0->z) < 110.0f) && ((fabsf(arg0->x - 600.0f) < 110.0f) || (fabsf(arg0->x + 600.0f) < 110.0f)) && (arg0->y < 230.0f)) {
        if (190.0f < arg0->y) {
            return 230.0f;
        } else {
            return 35.0f;
        }
    }

    if (arg0->y < -20.0f) {
        return 0.0f;
    }

    if ((1140.0f < fabsf(arg0->x)) || (1140.0f < fabsf(arg0->z))) {
        return 35.0f;
    }

    Matrix_Push();
    Matrix_RotateY(0.7853982f, 0);
    Matrix_MultVec3f(arg0, &sp2C);
    Matrix_Pull();

    if ((920.0f < fabsf(sp2C.x)) || (920.0f < fabsf(sp2C.z))) {
        return 35.0f;
    } else {
        return -100.0f;
    }
}

#ifdef NON_EQUIV
void func_8093B1AC(BossTw *this, GlobalContext *globalCtx) {
    Player* player = PLAYER;
    BossTw* refActor = (BossTw*)this->actor.attachedA;
    s32 tmp;
    s16 tmp16;
    s16 i;
    s16 j;
    
    Vec3s sp128;
    Vec3f sp10C;
    Vec3f sp100;
    Vec3f spF4;
    Vec3f spE4;
    Vec3f spD8;
    Vec3f spCC;
    f32 tmpf1; f32 tmpf2; f32 tmpf3; f32 sqX; f32 sqY; f32 tmpsq;
    


    Math_SmoothScaleMaxF(&this->actor.posRot.pos.y, 400.0f, 0.05f, this->actor.speedXZ);
    Math_SmoothScaleMaxF(&this->actor.speedXZ, 5.0f, 1.0f, 0.25f);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->unk_520 += -0.3f;
    if (this->unk_178[1] != 0) {
        Math_SmoothScaleMaxS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 5, this->unk_4C8);
        if (player->stateFlags1 & 0x800000) {
            tmp16 = (player->actor.shape.rot.y - this->actor.shape.rot.y) + 0x8000;
            if ((tmp16 < 0x2000) || (tmp16 >= -0x1FFF)) {
                Math_SmoothScaleMaxF(&this->unk_4B0.x, player->posRot.pos.x, 1.0f, 400.0f);
                Math_SmoothScaleMaxF(&this->unk_4B0.y, player->posRot.pos.y + 30.0f, 1.0f, 400.0f);
                Math_SmoothScaleMaxF(&this->unk_4B0.z, player->posRot.pos.z, 1.0f, 400.0f);
            } else {
                Math_SmoothScaleMaxF(&this->unk_4B0.x, player->unk_9BC.x, 1.0f, 400.0f);
                Math_SmoothScaleMaxF(&this->unk_4B0.y, player->unk_9BC.y, 1.0f, 400.0f);
                Math_SmoothScaleMaxF(&this->unk_4B0.z, player->unk_9BC.z, 1.0f, 400.0f);
            }
        }
        this->unk_178 = 0x46;
        this->unk_500.x = this->unk_500.y = this->unk_500.z = 0.0f;
        this->unk_4EC += this->unk_4F0 * 0.0025f;
        Math_SmoothScaleMaxF(&this->unk_4D8, 255.0f, 1.0f, 10.0f);
        Math_SmoothScaleMaxF(&this->unk_4F0, 50.0f, 1.0f, 2.0f);
        if (this->unk_178[1] < 0x32) {
            if (this->unk_178[1] < 0xA) {
                if (this->unk_178[1] == 9) {
                    globalCtx->envCtx.unk_D8 = 0.5f;
                    globalCtx->envCtx.unk_BD = 3 - this->actor.params;
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_MASIC_SET);
                }
                if (this->unk_178[1] == 5) {
                    this->unk_4D0 = 255.0f;
                }
                if (this->unk_178[1] >= 5) {
                    for (i = 0; i < 2; i++) {
                        for (j = 0; j < 5; j++) {
                            sp10C = this->unk_450[j];
                            sp100.x = Math_Rand_CenteredFloat(10.0f);
                            sp100.y = Math_Rand_CenteredFloat(10.0f);
                            sp100.z = Math_Rand_CenteredFloat(10.0f);
                            spF4.x = 0.0f;
                            spF4.y = 0.0f;
                            spF4.z = 0.0f;
                            func_80939070(globalCtx, &sp10C, &sp100, &spF4, Math_Rand_ZeroFloat(10.0f) + 25.0f, this->actor.params);
                        }
                    }
                }
            }
            if (this->unk178[1] < 0x14) {
                Math_SmoothScaleMaxF(&this->unk_4D4, 0.0f, 1.0f, 20.0f);
                Math_SmoothScaleMaxF(&this->unk_4D8, 0.0f, 1.0f, 30.0f);
            } else {
                Math_SmoothScaleMaxF(&this->unk_4D4, 255.0f, 1.0f, 10.0f);
                if (this->actor.params == 1) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_MS_FIRE - SFX_FLAG);
                } else {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_MS_FREEZE - SFX_FLAG);
                }
            }
            this->unk_4E8 += this->unk_4E4 * 0.0025f;
            Math_SmoothScaleMaxF(&this->unk_4E0, 0.0f, 0.1f, this->unk_4E4);
            Math_SmoothScaleMaxF(&this->unk_4E4, 50.0f, 1.0f, 2.0f);
        }
        if (func_800A56C8(&this->skelAnime, this->unk_1A4) != 0) {
            SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, 0x6009398, 0.0f);
            this->unk_1A4 = 10000.0f;
        }
        if (this->unk_178[1] == 1) {
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, 0x6003614, 0.0f);
            this->unk_4DC = 0.0f;
            this->unk_4D8 = 0.0f;
            this->unk_4D4 = 0.0f;
            this->unk_1A4 = SkelAnime_GetFrameCount(0x6003614);
            D_8094C86E = 0;
        }
        phi_s3 = &this->unk_50C;
    } else {
        if (func_800A56C8(&this->skelAnime, (bitwise f32) (bitwise s32) this->unk_1A4) != 0) {
            SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, (void *)0x6003E34, 0.0f);
            this->unk_1A4 = 10000.0f;
        }
        if (func_800A56C8(&this->skelAnime, this->unk_1A4 - 5.0f) != 0) {
            this->unk_4FC = (u16)0;
            D_8094C840 = (s8) (this->actor.params + 1);
        }
        if (func_800A56C8(&this->skelAnime, this->unk_1A4 - 13.0f) != 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_THROW_MASIC);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_SHOOT_VOICE);
        }
        tmpf1 = this->unk_4B0.x - this->unk_48C.x;
        tmpf2 = this->unk_4B0.z - this->unk_48C.z;
        tmpf3 = this->unk_4B0.y - this->unk_48C.y;
        sqX = SQ(tmpf1);
        sqZ = SQ(tmpf2);
        this->unk_51C = Math_atan2f(tmpf1, sqX);
        this->unk_518 = -Math_atan2f(tmpf3, sqrtf(sqX + sqZ));
        
        switch (this->unk_4FC) {
            case -1:
            case 0:
                if (this->unk_178[0] != 0) {
                    tmp = func_8093AB30(this, globalCtx);
                    if (tmp == 1) {
                        spCC = D_8094A8DC;
                        for (i = 0; i < 0x96; i++) {
                            spD8 = Math_Rand_CenteredFloat(15.0f);
                            spDC = Math_Rand_CenteredFloat(15.0f);
                            spE0 = Math_Rand_CenteredFloat(15.0f);
                            spE4 = player->unk_9BC;
                            func_80938CD0(globalCtx, &spE4, &spD8, &spCC, (s16)Math_Rand_ZeroFloat(2.0f) + 5, this->actor.params, 0x96);
                        }
                        this->unk_4FC = 1;
                        func_80078914(&player->actor.projectedPos.pos.x, 0x180C);
                        func_800D20CC(&player->mf_A20, &sp128, 0);
                        this->unk_524.x = -sp128.x;
                        this->unk_500.x = 0.0f;
                        this->unk_500.y = 0.0f;
                        this->unk_500.z = 0.0f;
                        this->unk_524.y = sp128.y + 0x8000;
                        globalCtx->envCtx.unk_D8 = 1.0f;
                        func_800AA000(0.0f, 0x64, 5, 4);
                    } else if (tmp == 0) {
                        func_8093A940(this, globalCtx);
                        if (this->unk_440 == 0) {
                            tmpsq = sqrtf((sqX + SQ(tmpf3)) + sqZ);
                            Math_SmoothScaleMaxF(&this->unk_52C, tmpsq + tmpsq, 1.0f, 40.0f);
                        }
                    }
                }

                func_800A6E10(&globalCtx->mf_11D60, &this->unk_50C, &this->unk_54C, &this->actor.projectedW);
                if (this->actor.params == 1) {
                    Audio_PlaySoundGeneral(NA_SE_EN_TWINROBA_SHOOT_FIRE - SFX_FLAG, this->unk_54C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
                } else {
                    Audio_PlaySoundGeneral(NA_SE_EN_TWINROBA_SHOOT_FREEZE - SFX_FLAG, this->unk_54C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
                }
                break;

            case 1:
                if (!CHECK_PAD(globalCtx->state.input[0].press, R_TRIG)) {
                    temp_s0_2 = globalCtx->unk1C44;
                    this->unk_52C = sqrtf(sqX + SQ(tmpf3) + sqZ);
                    Math_SmoothScaleMaxF(&this->unk_548, 2000.0f, 1.0f, 40.0f);
                    Math_SmoothScaleMaxF(&this->unk_4B0.x, player->unk_9BC.x, 1.0f, 400.0f);
                    Math_SmoothScaleMaxF(&this->unk_4B0.y, player->unk_9BC.y, 1.0f, 400.0f);
                    Math_SmoothScaleMaxF(&this->unk_4B0.z, player->unk_9BC.z, 1.0f, 400.0f);
                    if ((this->unk_150 & 3) == 0) {
                        func_80938EC0(globalCtx, temp_s0_2 + 0x9BC, 0.5f, 3.0f, 0xFF, (?32) this->actor.params, 1, 0x96);
                    }
                } else {
                    this->unk_4FC = 0;
                    this->unk_548 = 0.0f;
                }
                temp_s1 = this + 0x558;
                func_800A6E10(&globalCtx->mf_11D60, this->unk_530, temp_s1, &this->actor.projectedW);
                if (this->actor.params == 1) {
                    Audio_PlaySoundGeneral((u16)0x3122U, temp_s1, 4U, &D_801333E0, &D_801333E0, &D_801333E8);
                    Audio_PlaySoundGeneral((u16)0x3117U, temp_s1, 4U, &D_801333E0, &D_801333E0, &D_801333E8);
                } else {
                    Audio_PlaySoundGeneral((u16)0x3111U, temp_s1, 4U, &D_801333E0, &D_801333E0, &D_801333E8);
                    Audio_PlaySoundGeneral((u16)0x3118U, temp_s1, 4U, &D_801333E0, &D_801333E0, &D_801333E8);
                }
                break;

        }
        temp_v0_4 = (s16) this->unk_178;
        phi_v0_3 = temp_v0_4;
        if (temp_v0_4 == 0) {
            if (D_8094C840 != 1) {
                phi_v0_3 = temp_v0_4;
                if (D_8094C840 == 2) {
block_62:
                    D_8094C840 = (u8)0;
                    phi_v0_3 = (s16) this->unk_178;
                }
            } else {
                goto block_62;
            }
        }
        if (phi_v0_3 == 0) {
            Math_SmoothScaleMaxF(&this->unk_4F8, 0.0f, 1.0f, 0.0005f);
            if (0.0f == this->unk_4F8) {
                func_8093C164(this, globalCtx);
                this->unk_548 = 0.0f;
                this->unk_52C = 0.0f;
            }
        }
    }
    Matrix_Translate(this->unk_48C.x, this->unk_48C.y, (bitwise f32) (bitwise s32) this->unk_48C.z, (u8)0U);
    Matrix_RotateY(this->unk_51C, (u8)1U);
    Matrix_RotateX(this->unk_518, (u8)1U);
    sp130 = 0.0f;
    sp134 = 0.0f;
    temp_s2_3 = &sp130;
    sp138 = this->unk_52C + -5.0f;
    Matrix_MultVec3f((Vec3f *) temp_s2_3, &this->unk_50C);
    if (this->unk_440 == 0) {
        if (this->unk_4FC == 0) {
            if ((s16) this->unk_178 != 0) {
                temp_f0_2 = func_8093AED8(&this->unk_50C);
                temp_cond = 0.0f <= temp_f0_2;
                this->unk_500.y = temp_f0_2;
                if (temp_cond) {
                    this->unk_440 = (u16)1;
                    this->unk_500.x = (f32) this->unk_50C.x;
                    this->unk_500.z = (f32) this->unk_50C.z;
                    func_8093A5C4(this, globalCtx, this->actor.params);
                    this->unk_178 = (u16)0x14;
                }
            }
        }
    }
    if (this->unk_4FC == 1) {
        temp_s3_3 = this->unk_530;
        if (this->unk_440 == 0) {
            func_800D20CC((MtxF *) (player + 0xA20), (Vec3s *) &sp128, 0);
            temp_a1 = (s32) ((0 - sp128) << 0x10) >> 0x10;
            sp12A = sp12A + 0x8000;
            sp128 = (s16) temp_a1;
            Math_SmoothScaleMaxS((s16 *) &this->unk_524, (s16) temp_a1, (u16)5, (u16)0x2000);
            Math_SmoothScaleMaxS(&this->unk_524.y, sp12A, (u16)5, (u16)0x2000);
            this->unk_53C = (f32) (((f32) this->unk_524.x / 32768.0f) * 3.1415927f);
            this->unk_540 = (f32) (((f32) this->unk_524.y / 32768.0f) * 3.1415927f);
        }
        Matrix_Translate(this->unk_50C.x, this->unk_50C.y, (bitwise f32) (bitwise s32) this->unk_50C.z, (u8)0U);
        Matrix_RotateY(this->unk_540, (u8)1U);
        Matrix_RotateX(this->unk_53C, (u8)1U);
        sp130 = 0.0f;
        sp134 = 0.0f;
        sp138 = this->unk_548 + -170.0f;
        Matrix_MultVec3f((Vec3f *) temp_s2_3, (Vec3f *) temp_s3_3);
        if (this->unk_440 == 0) {
            sp138 = 0.0f;
            phi_s0_4 = 0;
loop_76:
            Matrix_MultVec3f((Vec3f *) temp_s2_3, (Vec3f *) &spBC);
            temp_f0_3 = func_8093AED8((Vec3f *) &spBC);
            temp_cond_2 = 0.0f <= temp_f0_3;
            this->unk_500.y = temp_f0_3;
            if (temp_cond_2) {
                temp_s2_4 = &spA4;
                temp_s1_3 = &spB0;
                phi_s0_3 = 0;
                if (35.0f != this->unk_500.y) {
                    phi_s0_3 = 0;
                    if (0.0f < this->unk_53C) {
                        phi_s0_3 = 0;
                        if ((s16) this->unk_178 != 0) {
                            this->unk_440 = (u16)1;
                            this->unk_500.x = spBC;
                            this->unk_500.z = spC4;
                            func_8093A5C4(this, globalCtx, this->actor.params);
                            this->unk_178 = (u16)0x14;
                        } else {
loop_81:
                            spB0 = Math_Rand_CenteredFloat(20.0f);
                            spB4 = Math_Rand_CenteredFloat(20.0f);
                            spB8 = Math_Rand_CenteredFloat(20.0f);
                            spA4 = 0.0f;
                            spA8 = 0.0f;
                            spAC = 0.0f;
                            func_80939070(globalCtx, (Vec3f *) temp_s3_3, (Vec3f *) temp_s1_3, (Vec3f *) temp_s2_4, Math_Rand_ZeroFloat(10.0f) + 25.0f, (?32) this->actor.params);
                            temp_s0_4 = (s32) ((phi_s0_3 + 1) << 0x10) >> 0x10;
                            phi_s0_3 = temp_s0_4;
                            if (temp_s0_4 < 5) {
                                goto loop_81;
                            }
                            this->unk_548 = sp138;
                            Math_SmoothScaleMaxF(&globalCtx->envCtx.unk_D8, 0.8f, 1.0f, 0.2f);
                        }
                    } else {
                        goto loop_81;
                    }
                } else {
                    goto loop_81;
                }
            } else {
                temp_f10 = sp138 + 20.0f;
                temp_s0_5 = (s32) ((phi_s0_4 + 1) << 0x10) >> 0x10;
                sp138 = temp_f10;
                if (!(this->unk_548 < temp_f10)) {
                    phi_s0_4 = temp_s0_5;
                    if (temp_s0_5 < 0xC8) {
                        goto loop_76;
                    }
                }
            }
        }
        if (func_8093ADB4(this, &this->actor.posRot) != 0) {
            if ((this->unk_150 & 3) == 0) {
                func_80938EC0(globalCtx, (Vec3f *) temp_s3_3, 0.5f, 3.0f, 0xFF, (?32) this->actor.params, 1, 0x96);
            }
        }
        if (func_8093ADB4(this, &redActor->posRot) != 0) {
            if (&func_8093C2C4 != redActor->unk14C) {
                temp_s3_4 = &sp80;
                temp_s2_5 = &sp8C;
                temp_s1_4 = &sp98;
                phi_s0_5 = 0;
loop_91:
                sp98 = Math_Rand_CenteredFloat(50.0f) + redActor->posRot.pos.x;
                sp9C = Math_Rand_CenteredFloat(50.0f) + redActor->posRot.pos.y;
                spA0 = Math_Rand_CenteredFloat(50.0f) + redActor->posRot.pos.z;
                sp8C = Math_Rand_CenteredFloat(20.0f);
                sp90 = Math_Rand_CenteredFloat(20.0f);
                sp94 = Math_Rand_CenteredFloat(20.0f);
                sp80 = 0.0f;
                sp84 = 0.0f;
                sp88 = 0.0f;
                func_80939070(globalCtx, (Vec3f *) temp_s1_4, (Vec3f *) temp_s2_5, (Vec3f *) temp_s3_4, Math_Rand_ZeroFloat(10.0f) + 25.0f, (?32) this->actor.params);
                temp_s0_6 = (s32) ((phi_s0_5 + 1) << 0x10) >> 0x10;
                phi_s0_5 = temp_s0_6;
                if (temp_s0_6 < 0x32) {
                    goto loop_91;
                }
                func_8093C25C(redActor, globalCtx);
                Audio_PlayActorSound2((Actor *) redActor, (u16)0x3916U);
                globalCtx->envCtx.unk_D8 = 1.0f;
                redActor->colChkInfo.health = (u8) (redActor->colChkInfo.health + 1);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_8093B1AC.s")
#endif

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
        Matrix_Translate(this->unk_4BC.x, this->unk_4BC.y, this->unk_4BC.z, 0);
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
        Matrix_Translate(this->unk_4BC.x, this->unk_4BC.y, this->unk_4BC.z, 0);
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
                Matrix_Translate(this->unk_50C.x, this->unk_50C.y, this->unk_50C.z, 0);
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
                    tmpf1 = this->unk_4BC.x - player->actor.posRot.pos.x;
                    tmpf2 = this->unk_4BC.z - player->actor.posRot.pos.z;
                    if ((fabsf(this->unk_4BC.y - player->actor.posRot.pos.y) < 10.0f) && 
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

s32 func_80943950(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    BossTw* this = THIS;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1BE3);
        
        switch (limbIndex) {
            case 21:
                gSPSegment(gfxCtx->polyOpa.p++, 0x0C, Gfx_TexScroll(globalCtx->state.gfxCtx, 0, (f32)this->unk_150, 8, 8));
                gSPSegment(gfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_8094A9B0[this->unk_4CC]));
                gSPSegment(gfxCtx->polyOpa.p++, 0x09, SEGMENTED_TO_VIRTUAL(D_8094A9B0[this->unk_4CE]));
                gDPSetEnvColor(gfxCtx->polyOpa.p++, 0xFF, 0xFF, 0xFF, this->unk_160);
                break;
            case 17:
            case 41:
                *dList = NULL;
                gSPSegment(gfxCtx->polyXlu.p++, 0x0A, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x20, 1, 0, -this->unk_150 * 0xF, 0x20, 0x40));
                break;
            case 18:
            case 42:
                *dList = NULL;
                gSPSegment(gfxCtx->polyXlu.p++, 0x0B, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x20, 1, 0, -this->unk_150 * 0xA, 0x20, 0x40));
                break;
            case 16:
            case 32:
                *dList = NULL;
                gSPSegment(gfxCtx->polyXlu.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x20, 1, this->unk_150, -this->unk_150 * 7, 0x20, 0x40));
                break;
            case 15:
            case 31:
                *dList = NULL;
                gSPSegment(gfxCtx->polyXlu.p++, 0x09, Gfx_TexScroll(globalCtx->state.gfxCtx, 0, this->unk_150, 0x20, 0x40));
                break;
            case 19:
                if (this->unk_5F8 != 0) {
                    *dList = D_0602D940;
                }
                break;
            case 20:
                if (this->unk_5F8 != 0) {
                    *dList = D_0602D890;
                }
                break;
        }

        if (this->unk_5F8 != 0) {
            if ((limbIndex == 34) || (limbIndex == 40)) {
                *dList = NULL;
            }
        }

        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1C53);
    }
    return 0;
}

void func_80943D90(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    BossTw* this = THIS;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1C5E);
        
        switch (limbIndex) {
            case 34:
                Matrix_MultVec3f(&D_8094A9D4, &this->unk_498);
                break;
            case 40:
                Matrix_MultVec3f(&D_8094A9E0, &this->unk_4A4);
                break;
            case 21:
                Matrix_MultVec3f(&D_8094A9BC, &this->actor.posRot2.pos);
                Matrix_MultVec3f(&D_8094A9C8, &this->unk_444);
                break;
            case 15:
            case 16:
            case 17:
            case 18:
            case 31:
            case 32:
            case 41:
            case 42:
                Matrix_Push();
                Matrix_Scale(this->unk_1B4, this->unk_1B4, this->unk_1B4, 1);
                gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1C7F), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                Matrix_Pull();
                gSPDisplayList(gfxCtx->polyXlu.p++, *dList);
                break;
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1C85);
    }
}

#ifdef NON_MATCHING
// stack
void func_80943F08(BossTw* this, GlobalContext* globalCtx) {
    s16 tmp;
    Player* player = PLAYER;
    s16 flg;
    
    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];
        s32 pad;
        f32 tmpf2;
        f32 tmpf1;

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1C8F);
        Matrix_Push();
        flg = D_8094C850 | D_8094C851;
        if (flg == 1) {
            func_80078884(0x1032);
        } else if (flg == 2) {
            func_80078884(0x1033);
        } else if (flg == 3) {
            func_80078884(0x1034);
        }
        //tmp = 0;
        if ((flg != 0) && (flg < 4)) {
            Math_SmoothScaleMaxF(&D_8094C854, 255.0f, 1.0f, 20.0f);
            if (flg == 3) {
                flg *= 3;
            }
        } else if (flg == 0) {
            D_8094C854 = 0.0f;
        } else {
            Math_SmoothScaleMaxF(&D_8094C854, 0.0f, 1.0f, 10.0f);
            
            if (D_8094C854 == 0.0f) {
                D_8094C850 = 0;
                D_8094C851 = 0;
            }
            flg = 1;
        }

        if ((func_8008F098(globalCtx)) && (flg != 0)) {
            Matrix_Mult(&player->mf_A20, 0);
            Matrix_RotateX(1.5707964f, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1CC2), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            tmp = ((Math_Sins((this->unk_150 * 0xAAA) * flg) * D_8094C854) * 0.5f) + (D_8094C854 * 0.5f);
            if (D_8094C850 != 0) {
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xF5, 0xFF, tmp);
                gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601E0E0));
                gSPSegment(gfxCtx->polyXlu.p++, 0x08, 
                    Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
                        (this->unk_150 * 2) * flg, 0, 
                        0x20, 0x20, 1, 
                        (-this->unk_150 * 2) * flg, 0, 
                        0x20, 0x20));
                gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x64, 0x14, 0x00, (s8)D_8094C854);
                gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601E020));
            } else {
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xE1, 0xFF, 0xFF, tmp);
                gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601E3A0));
                gSPSegment(gfxCtx->polyXlu.p++, 0x08, 
                    Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
                        0, (-this->unk_150 * 5) * flg, 
                        0x20, 0x40, 1, 
                        (this->unk_150 * 4) * flg, 0, 
                        0x20, 0x20));
                gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xAF, 0xCD, 0xC3, (s8)D_8094C854);
                gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601E2C0));
            }
        }
        if (D_8094C86F != 0) {
            if (D_8094C872 > 0) {
                tmpf1 = 100.0f;
            } else {
                tmpf1 = 60.0f;
            }
            D_8094C86F--;
            Math_SmoothScaleMaxF(&D_8094C858, 255.0f, 1.0f, tmpf1);
        } else {
            if (D_8094C872 > 0) {
                tmpf1 = 40.0f;
            } else {
                tmpf1 = 20.0f;
            }
            Math_SmoothScaleMaxF(&D_8094C858, 0.0f, 1.0f, tmpf1);
        }
        if (func_8008F098(globalCtx) && (D_8094C858 > 0.0f)) {
            if (D_8094C872 > 0) {
                tmpf2 = 1.3f;
            } else {
                tmpf2 = 1.0f;
            }
            Matrix_Mult(&player->mf_A20, 0);
            Matrix_RotateX(1.5707964f, 1);
            Matrix_Scale(tmpf2, tmpf2, tmpf2, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1D3E), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            if (D_8094C850 != 0) {
                gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xDC, 0x14, (s8)D_8094C858);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0x00, 0x14, 0x6E);
            } else {
                gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, (s8)D_8094C858);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xB9, 0xE1, 0xCD, 0x96);
            }

            gSPSegment(gfxCtx->polyXlu.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
                0, this->unk_150 * D_8094C872, 0x20, 
                0x40, 1, 0, 
                this->unk_150 * D_8094C872, 0x20, 0x20));
            gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601E9F0));
        }
        Matrix_Pull();
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1D6B);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80943F08.s")
#endif

void func_809447BC(BossTw* this, GlobalContext* globalCtx) {
    
    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];
        s32 pad;

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1D7A);
        func_80093D84(globalCtx->state.gfxCtx);

        gSPSegment(gfxCtx->polyXlu.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, -this->unk_150 * 15, 0x20, 0x40, 1, 0, 0, 0x40, 0x40));

        Matrix_Push();
        Matrix_Translate(0.0f, 232.0f, -600.0f, 0);
        Matrix_Scale(this->unk_4E8, this->unk_4E8, this->unk_4E8, 1);

        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x00, 0x00, 0x00, (s8)this->unk_4E0);
        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1D9E), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601EC68));
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x87, 0xAF, 0xA5, (s8)this->unk_4E0);

        Matrix_Translate(0.0f, 2.0f, 0.0f, 1);
        Matrix_RotateX(1.5707964f, 1);

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1DAC), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601CEE0));

        Matrix_Translate(0.0f, 232.0f, 600.0f, 0);
        Matrix_Scale(this->unk_4E8, this->unk_4E8, this->unk_4E8, 1);

        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x00, 0x00, 0x00, (s8)this->unk_4E0);
        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1DC1), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601EC68));
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0x00, (s8)this->unk_4E0);

        Matrix_Translate(0.0f, 2.0f, 0.0f, 1);
        Matrix_RotateX(1.5707964f, 1);

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1DCF), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601DBE8));

        Matrix_Pull();
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1DD3);
    }
}

void func_80944C50(BossTw* this, GlobalContext* globalCtx) {
    f32 tmpf1;
    s32 pad;
    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1DDD);
        Matrix_Push();
        Matrix_Translate(0.0f, 750.0f, 0.0f, 0);
        Matrix_Scale(0.35f, 0.35f, 0.35f, 1);
        Matrix_Push();
        Matrix_Scale(this->unk_1D0, this->unk_1D0, this->unk_1D0, 1);

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1DF7), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601F390));

        Matrix_Pull();

        gSPSegment(gfxCtx->polyXlu.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
            -D_8094C848->unk_150 * 2, 0, 0x20, 0x20, 
            1, -D_8094C848->unk_150 * 2, 0, 
            0x20, 0x40));
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, (s16)this->unk_1CC / 2);
        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1E0E), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601F238));
        gSPSegment(gfxCtx->polyXlu.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0,
            -D_8094C848->unk_150 * 5, -D_8094C848->unk_150 * 2, 0x20, 0x40, 
            1, 0, -D_8094C848->unk_150 * 2, 0x10, 0x10));
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, (s8)(this->unk_1CC * 0.3f));

        tmpf1 = this->unk_1CC / 150.0f;
        if (tmpf1 > 1.0f) {
            tmpf1 = 1.0f;
        }
        Matrix_Scale(tmpf1, 1.0f, tmpf1, 1);

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1E30), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_0601EEB0));

        Matrix_Pull();
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1E34);
    }
}


void func_80943F08(BossTw* this, GlobalContext* globalCtx);

void func_80945084(Actor* thisx, GlobalContext* globalCtx) {
    BossTw* this = THIS;
    s32 pad;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1E44);
        if (this->unk_564 != 0) {
            func_80093D18(globalCtx->state.gfxCtx);
            func_80093D84(globalCtx->state.gfxCtx);
            if (this->unk_15C & 2) {
                gfxCtx->polyOpa.p = Gfx_SetFog2(gfxCtx->polyOpa.p, 0xFF, 0x32, 0, 0, 0x384, 0x44B);
            } else {
                gfxCtx->polyOpa.p = Gfx_SetFog2(gfxCtx->polyOpa.p, this->unk_1D4, this->unk_1D8, this->unk_1DC, 0, this->unk_1E0, this->unk_1E4);
            }
            Matrix_Push();
            SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, func_80943950, func_80943D90, &this->actor);
            Matrix_Pull();
            Matrix_MultVec3f(&D_8094A9EC, &this->unk_48C);
            gfxCtx->polyOpa.p = Gfx_SetFog2(gfxCtx->polyOpa.p, globalCtx->lightCtx.unk_07, globalCtx->lightCtx.unk_08, globalCtx->lightCtx.unk_09, 0, globalCtx->lightCtx.unk_0A, 0x3E8);
        }
        func_80948668(globalCtx);
        func_80943F08(this, globalCtx);
        if (this->unk_4D8 > 0.0f) {
            func_809447BC(this, globalCtx);
        }
        if (this->unk_1CC > 0.0f) {
            func_80944C50(this, globalCtx);
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_tw.c", 0x1E7C);
    }
}

#ifdef NON_MATCHING
void func_809453EC(BossTw* this, GlobalContext* globalCtx) {
    
    Vec3f spC0;
    Player* player = PLAYER;
    Vec3f spA8;
    Vec3f sp9C;
    Vec3s sp94;
    Vec3f sp84;
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    s16 i;
    s16 i2;
    s32 tmp;
    s16 tmp16;
    f32 tmpf1;
    f32 tmpf2;
    f32 tmpf3;
    f32 tmpf4;

    switch (this->actor.params) {
        case 100:
            switch (this->unk_440) {
                case 0:
                    Actor_SetScale(&this->actor, 0.03f);
                    this->unk_440 = 1;
                    spC0.x = player->actor.posRot.pos.x - this->actor.posRot.pos.x;
                    spC0.y = (player->actor.posRot.pos.y + 30.0f) - this->actor.posRot.pos.y;
                    spC0.z = player->actor.posRot.pos.z - this->actor.posRot.pos.z;
                    this->actor.posRot.rot.y = Math_atan2f(spC0.x, spC0.z) * 10430.378f;
                    this->actor.posRot.rot.x = Math_atan2f(spC0.y, sqrtf(SQ(spC0.x) + SQ(spC0.z))) * 10430.378f;
                    this->actor.speedXZ = 20.0f;

                    for (i = 0; i < 50; i++) {
                        this->unk_1E8[i] = this->actor.posRot.pos;
                    }
                    this->unk_1AC = 255.0f;
                case 1:
                case 10:
                    this->unk_565 = 1;
                    if (this->unk_178[0] == 0) {
                        func_8002D908(&this->actor);
                        func_8002D7EC(&this->actor);
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_SHOOT_FIRE - SFX_FLAG);
                    } else {
                        this->actor.posRot.pos = player->unk_9BC;
                        this->actor.posRot.pos.y = -2000.0f;
                        func_800D20CC(&player->mf_A20, &sp94, 0);
                        sp94.x = -sp94.x;
                        sp94.y += 0x8000;
                        Math_SmoothScaleMaxS(&this->unk_524.x, sp94.x, 10, 0x800);
                        Math_SmoothScaleMaxS(&this->unk_524.y, sp94.y, 10, 0x800);
                        if (this->unk_178[0] == 50) {
                            D_8094C86F = 10;
                            D_8094C872 = 7;
                            globalCtx->envCtx.unk_D8 = 1.0f;
                        }
                        if (this->unk_178[0] < 51) {
                            Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_SHOOT_FIRE - SFX_FLAG);
                            Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_REFL_FIRE - SFX_FLAG);
                            Matrix_RotateY((this->unk_524.y / 32678.0f) * M_PI, 0);
                            Matrix_RotateX((this->unk_524.x / 32678.0f) * M_PI, 1);
                            sp9C.x = 0.0f;
                            sp9C.y = 0.0f;
                            sp9C.z = 50.0f;
                            Matrix_MultVec3f(&sp9C, &spA8);
                            tmp16 = this->unk_178[0] * 10;
                            if (tmp16 >= 0x100) {
                                tmp16 = 0xFF;
                            }
                            func_80939250(globalCtx, &sp9C, &spA8, &D_8094A7DC, 10.0f, 80.0f, tmp16, 1);
                        }
                        if (this->unk_178[0] == 1) {
                            D_8094C840 = 0;
                            D_8094C850++;
                            Actor_Kill(&this->actor);
                            return;
                        }
                    }

                    this->unk_500.y = func_8093AED8(&this->actor.posRot.pos);
                    if (this->unk_500.y >= 0.0f) {
                        if (this->unk_500.y != 35.0f) {
                            this->unk_500.x = this->actor.posRot.pos.x;
                            this->unk_500.z = this->actor.posRot.pos.z;
                            func_8093A5C4(this, globalCtx, 1);
                        } else {
                            for (i = 0; i < 50; i++) {
                                sp84.x = Math_Rand_CenteredFloat(20.0f);
                                sp84.y = Math_Rand_CenteredFloat(20.0f);
                                sp84.z = Math_Rand_CenteredFloat(20.0f);
                                sp78.x = 0.0f;
                                sp78.y = 0.0f;
                                sp78.z = 0.0f;
                                func_80939070(globalCtx, &this->actor.posRot.pos, &sp84, &sp78, Math_Rand_ZeroFloat(10.0f) + 25.0f, this->unk_566);
                            }
                            globalCtx->envCtx.unk_D8 = 0.5f;
                        }
                        this->unk_440 = 2;
                        this->unk_178[0] = 20;
                    } else {
                        sp60 = D_8094A9F8;
                        sp54 = D_8094AA04;
                        for (i = 0; i < 10; i++) {
                            sp6C = this->unk_1E8[(s16)Math_Rand_ZeroFloat(29.9f)];
                            sp6C.x += Math_Rand_CenteredFloat(40.0f);
                            sp6C.y += Math_Rand_CenteredFloat(40.0f);
                            sp6C.z += Math_Rand_CenteredFloat(40.0f);
                            sp54.y = 0.4f;
                            sp54.x = Math_Rand_CenteredFloat(0.5f);
                            sp54.z = Math_Rand_CenteredFloat(0.5f);
                            func_80938CD0(globalCtx, &sp6C, &sp60, &sp54, (s16)Math_Rand_ZeroFloat(2.0f) + 8, 1, 0x4B);
                        }
                    }
                    break;
                
                case 2:
                    Math_SmoothScaleMaxF(&this->unk_1AC, 0.0f, 1.0f, 15.0f);
                    if (this->unk_178[0] == 0) {
                        Actor_Kill(&this->actor);
                    }
                    break;
            }
            break;

        case 101:
            switch (this->unk_178[0]) {
                default:
                    if (this->unk_178[0] == 1) {
                        D_8094C840 = 0;
                    }
                    if (D_8094C841 == 2) {
                        this->unk_178[0] = 0;
                    }
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_FIRE_EXP - SFX_FLAG);
                    tmpf2 = D_8094C848->unk_4BC.x - player->actor.posRot.pos.x;
                    tmpf4 = D_8094C848->unk_4BC.y - player->actor.posRot.pos.y;
                    tmpf3 = D_8094C848->unk_4BC.z - player->actor.posRot.pos.z;
                    if ((player->unk_A60 == 0) && (player->actor.bgCheckFlags & 1) && 
                        (fabsf(tmpf4) < 10.0f) && 
                        (sqrtf(SQ(tmpf2) + SQ(tmpf3)) < (D_8094C848->unk_1B8 * 4550.0f))) {
                        for (i2 = 0; i2 < 18; i2++) {
                            player->unk_A61[i2] = Math_Rand_S16Offset(0, 0xC8);
                        }
                        player->unk_A60 = 1;
                        if (this->unk_168 == 0) {
                            func_8002F7DC(&player->actor, *((u16*)player->ageProperties + 0x49) + NA_SE_VO_LI_DEMO_DAMAGE);
                            this->unk_168 = 0x28;
                        }
                        D_8094C84C->unk_178[2] = 0x64;
                    }
                    Math_SmoothScaleMaxF(&D_8094C848->unk_1B8, 0.04f, 0.1f, 0.002f);
                    break;
                    
                case 0:
                    if (2 == D_8094C841) {
                        tmpf1 = 3.0f;
                    } else {
                        tmpf1 = 1.0f;
                    }
                    Math_SmoothScaleMaxF(&D_8094C848->unk_1A8, 0.0f, 1.0f, 10.0f * tmpf1);
                    Math_SmoothScaleMaxF(&D_8094C848->unk_1B4, 0.0f, 1.0f, 0.03f * tmpf1);
                    Math_SmoothScaleMaxF(&D_8094C848->unk_1AC, 0.0f, 1.0f, 3.0f * tmpf1);
                    Math_SmoothScaleMaxF(&D_8094C848->unk_1B0, 0.0f, 1.0f, 6.0f * tmpf1);
                    if (D_8094C848->unk_1AC <= 0.0f) {
                        Actor_Kill(&this->actor);
                    }
                    break;
                    
                
            }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_809453EC.s")
#endif

#define NON_MATCHING
#ifdef NON_MATCHING
void func_80945D14(BossTw *this, GlobalContext *globalCtx) {
    f32 distXZ;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    f32 temp_f2;
    Player *player = PLAYER;
    s32 pad2;
    Vec3f sp100;
    Vec3f spF4;
    Vec3s spEC;
    s16 phi_s0;
    Vec3f spDC;
    Vec3f spD0;
    Vec3f spC4;
    Vec3f spB8;
    Vec3f spAC;
    s32 pad;
    Vec3f sp9C;
    Vec3f sp90;
    Vec3f sp84;
    f32 phi_f0;
    Vec3f sp74;
    Vec3f sp68;
    Vec3f sp5C;
    s16 phi_v0;
    

    switch(this->actor.params) {
        case 0x66:
            switch(this->unk_440){
                case 0:
                    Actor_SetScale(&this->actor, 0.03f);
                    this->unk_440 = 1;
                    diffX = player->actor.posRot.pos.x - this->actor.posRot.pos.x;
                    diffY = (player->actor.posRot.pos.y + 30.0f) - this->actor.posRot.pos.y;
                    diffZ = player->actor.posRot.pos.z- this->actor.posRot.pos.z;
                    this->actor.posRot.rot.y = Math_atan2f(diffX, diffZ) * 10430.378f;
                    distXZ = sqrtf(SQ(diffX) + SQ(diffZ));
                    this->actor.posRot.rot.x = Math_atan2f(diffY, distXZ) * 10430.378f;
                    this->actor.speedXZ = 20;
                    for(phi_s0 = 0; phi_s0 < 50; phi_s0++){
                        this->unk_1E8[phi_s0] = this->actor.posRot.pos;
                    }
                    this->unk_1AC = 255.0f;
                case 1:
                case 0xA:
                    this->unk_565 = 1;
                    if (this->unk_178[0] == 0) {
                        func_8002D908(&this->actor);
                        func_8002D7EC(&this->actor);
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_SHOOT_FREEZE & ~SFX_FLAG);
                    } else {
                        
                        this->actor.posRot.pos = player->unk_9BC;
                        this->actor.posRot.pos.y = -2000.0f;
                        func_800D20CC(&player->mf_A20, &spEC, MTXMODE_NEW);
                        spEC.y += 0x8000;
                        spEC.x = -spEC.x;
                        Math_SmoothScaleMaxS(&this->unk_524.x, spEC.x, 0xA, 0x800);
                        Math_SmoothScaleMaxS(&this->unk_524.y, spEC.y, 0xA, 0x800);
                        if(!player){}
                        if (this->unk_178[0] == 0x32) {
                            D_8094C86F = 0xA;
                            D_8094C872 = 7;
                            globalCtx->envCtx.unk_D8 = 1.0f;
                        }
                        if (this->unk_178[0] < 0x33) {
                            
                            Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_SHOOT_FREEZE & ~SFX_FLAG);
                            Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_REFL_FREEZE & ~SFX_FLAG);
                            Matrix_RotateY((this->unk_524.y / 32678.0f) * M_PI, MTXMODE_NEW);
                            Matrix_RotateX((this->unk_524.x / 32678.0f) * M_PI, MTXMODE_APPLY);
                            spF4.x = 0.0f;
                            spF4.y = 0.0f;
                            spF4.z = 50.0f;
                            Matrix_MultVec3f(&spF4, &sp100);
                            phi_v0 = this->unk_178[0] * 10;
                            if (phi_v0 >= 0x100) {
                                phi_v0 = 0xFF;
                            }
                            func_80939250(globalCtx, &player->unk_9BC, &sp100, &D_8094A7DC, 10.0f, 80.0f, phi_v0, 0);
                        }
                        if (this->unk_178[0] == 1) {
                            D_8094C840 = 0;
                            D_8094C851++;
                            Actor_Kill(&this->actor);
                        }
                        return;
                    }

                    this->unk_500.y = func_8093AED8(&this->actor.posRot.pos);
                    
                    if (this->unk_500.y >= 0.0f) {
                        if (this->unk_500.y != 35.0f) {
                            this->unk_500.x = this->actor.posRot.pos.x;
                            this->unk_500.z = this->actor.posRot.pos.z;
                            func_8093A5C4(this, globalCtx, 0);
                        } else {
                            for(phi_s0 = 0; phi_s0 < 50; phi_s0++){
                                
                                spDC.x = Math_Rand_CenteredFloat(20);
                                spDC.y = Math_Rand_CenteredFloat(20);
                                spDC.z = Math_Rand_CenteredFloat(20);
                                spD0.x = 0.0f;
                                spD0.y = 0.0f;
                                spD0.z = 0.0f;
                                func_80939070(globalCtx, &this->actor.posRot.pos, &spDC, &spD0, Math_Rand_ZeroFloat(10.0f) + 25.0f, this->unk_566);
                            }
                            globalCtx->envCtx.unk_D8 = 0.5f;
                        }

                        this->unk_440 = 2;
                        this->unk_178[0] = 0x14;
                    } else {                    
                        
                        spB8 = D_8094AA10;
                        spAC = D_8094AA1C;
                        for(phi_s0 = 0; phi_s0 < 10; phi_s0++){

                            spC4 = this->unk_1E8[(s16)Math_Rand_ZeroFloat(29.9f)];
                            spC4.x += Math_Rand_CenteredFloat(40.0f);
                            spC4.y += Math_Rand_CenteredFloat(40.0f);
                            spC4.z += Math_Rand_CenteredFloat(40.0f);
                            spAC.y = 0.4f;
                            spAC.x = Math_Rand_CenteredFloat(0.5f);
                            spAC.z = Math_Rand_CenteredFloat(0.5f);
                            func_80938CD0(globalCtx, &spC4, &spB8, &spAC, (s16)Math_Rand_ZeroFloat(2.0f) + 8, 0, 0x4B);
                        }
                    }
                    break;
                case 2:
                    Math_SmoothScaleMaxF(&this->unk_1AC, 0.0f, 1.0f, 15.0f);
                    if (this->unk_178[0] == 0) {
                        Actor_Kill(&this->actor);
                    }
                    break;
            }
            break;
        case 0x67:
            if (this->unk_178[0] != 0) {
                if (this->unk_178[0] == 1) {
                    D_8094C840 = 0;
                }
                if (D_8094C841 == 1) {
                    this->unk_178[0] = 0;
                }

                Audio_PlayActorSound2(&this->actor, NA_SE_EV_ICE_FREEZE & ~SFX_FLAG);
                
                phi_v0 = D_8094C84C->actionFunc == func_8093C858 ? 0x46 : 0x14;

                if (phi_v0 < this->unk_178[0]) {
                    
                    
                    
                    sp9C.x = Math_Rand_CenteredFloat(320.0f) + D_8094C844->unk_4BC.x;
                    sp9C.z = Math_Rand_CenteredFloat(320.0f) + D_8094C844->unk_4BC.z;
                    sp9C.y = D_8094C844->unk_4BC.y;
                    sp90.x = 0.0f;
                    sp90.y = 0.0f;
                    sp90.z = 0.0f;
                    sp84.x = 0.0f;
                    sp84.z = 0.0f;
                    sp84.y = 0.13f;
                    func_80938DC4(globalCtx, 3, &sp9C, &sp90, &sp84, Math_Rand_ZeroFloat(5.0f) + 20.0f, 0, 0, 0x50);
                    sp90.x = Math_Rand_CenteredFloat(10.0f);
                    sp90.z = Math_Rand_CenteredFloat(10.0f);
                    sp90.y = Math_Rand_ZeroFloat(3.0f) + 3.0f;
                    sp9C.x = D_8094C844->unk_4BC.x + (sp90.x * 0.5f);
                    sp9C.z = D_8094C844->unk_4BC.z + (sp90.z * 0.5f);
                    func_80938DC4(globalCtx, 3, &sp9C, &sp90, &sp84, Math_Rand_ZeroFloat(5.0f) + 15.0f, 0xFF, 2, 0x82);
                }
                
                Math_SmoothScaleMaxF(&D_8094C844->unk_1A8, 80.0f, 1.0f, 3.0f);
                Math_SmoothScaleMaxF(&D_8094C844->unk_1B0, 255.0f, 1.0f, 10.0f);
                Math_SmoothScaleMaxF(&D_8094C844->unk_1B4, 0.04f, 0.1f, 0.002f);
                Math_SmoothScaleMaxF(&D_8094C844->unk_1C4, 70.0f, 1.0f, 5.0f);
                if (this->unk_178[0] == 0x46 || this->unk_178[0] == 0x1E) {
                    D_8094C844->unk_1C4 = 10.0f;
                }

                if ((this->unk_178[0] & 3) == 0) {
                    temp_f2 = (s16)Math_Rand_ZeroFloat(9.9f);
                    D_8094C844->unk_1C0 = ((temp_f2 + temp_f2) * M_PI) / 10.0f;
                    return;
                }
            } else {
                if (D_8094C841 == 1) {
                    if (1.0f < D_8094C844->unk_1B0) {
                        for(phi_s0 = 0; phi_s0 < 3; phi_s0++){
                            
                            
                            
                            sp74.x = Math_Rand_CenteredFloat(280.0f) + D_8094C844->unk_4BC.x;
                            sp74.z = Math_Rand_CenteredFloat(280.0f) + D_8094C844->unk_4BC.z;
                            sp74.y = D_8094C844->unk_4BC.y + 30.0f;
                            sp68.x = 0.0f;
                            sp68.y = 0.0f;
                            sp68.z = 0.0f;
                            sp5C.x = 0.0f;
                            sp5C.y = 0.13f;
                            sp5C.z = 0.0f;
                            func_80938DC4(globalCtx, 3, &sp74, &sp68, &sp5C, Math_Rand_ZeroFloat(5.0f) + 20.0f, 0, 0, 0x50);
                        }
                    }
                    phi_f0 = 3.0f;
                } else {
                    phi_f0 = 1.0f;
                }
                Math_SmoothScaleMaxF(&D_8094C844->unk_1BC, 0.0f, 1.0f, 0.2f * phi_f0);
                Math_SmoothScaleMaxF(&D_8094C844->unk_1B0, 0.0f, 1.0f, 5.0f * phi_f0);
                Math_SmoothScaleMaxF(&D_8094C844->unk_1A8, 0.0f, 1.0f, phi_f0);
                if (D_8094C844->unk_1A8 <= 0.0f) {
                    Actor_Kill(&this->actor);
                }
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Tw/func_80945D14.s")
#endif

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
