#include "z_boss_va.h"
#include "overlays/actors/ovl_En_Boom/z_en_boom.h"

#define FLAGS 0x00000035

#define THIS ((BossVa*)thisx)

void BossVa_Init(Actor* thisx, GlobalContext* globalCtx);
void BossVa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BossVa_Update(Actor* thisx, GlobalContext* globalCtx);
void BossVa_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809506F0(BossVa* this);
void func_809517A0(BossVa* this);
void func_809597F4(GlobalContext* globalCtx);
void func_8095A188(BossVaEffect* arg0, GlobalContext* globalCtx);
void func_8095BD24(GlobalContext* globalCtx, s16 arg1);
void func_80953F4C(BossVa* this, GlobalContext* globalCtx);
void func_809540E4(BossVa* this, GlobalContext* globalCtx);
void func_80954A3C(BossVa* this, GlobalContext* globalCtx);
void func_80954B8C(BossVa* this, GlobalContext* globalCtx);
void func_80954924(BossVa* this, GlobalContext* globalCtx);
void func_80957C9C(BossVa* this, GlobalContext* globalCtx);
void func_809567D0(BossVa* this, GlobalContext* globalCtx);
void func_80956E38(BossVa* this, GlobalContext* globalCtx);
void func_809572DC(BossVa* this, GlobalContext* globalCtx);
void func_80950780(BossVa* this, GlobalContext* globalCtx);
void func_80951844(BossVa* this, GlobalContext* globalCtx);

void func_8095B670(GlobalContext* globalCtx, BossVaEffect* arg1, Vec3f* arg2, s16 arg3, s16 arg4);
void func_8095B9B0(GlobalContext* globalCtx, BossVaEffect* arg1, Vec3f* arg2, s16 arg3, s16 arg4);

extern SkeletonHeader D_06015B18;
extern SkeletonHeader D_06017498;
extern SkeletonHeader D_060199A0;
extern SkeletonHeader D_06018870;
extern SkeletonHeader D_06004E70;
extern AnimationHeader D_06005184;
extern AnimationHeader D_060166A8;
extern AnimationHeader D_06018D18;
extern AnimationHeader D_06018150;
extern AnimationHeader D_06000024;
extern Gfx D_06008D70[];
extern Gfx D_06008BB8[];
extern Gfx D_06000FA0[];
extern Gfx D_060156A0[];
extern Gfx D_06015710[];
extern Gfx D_06011738[];
extern Gfx D_06011768[];
extern Gfx D_06009430[];
extern Gfx D_06009468[];
extern Gfx D_060128B8[];
extern Gfx D_06012948[];
extern Gfx D_06012BA0[];
extern Gfx D_06012C50[];
extern Gfx D_060135B0[];
extern Gfx D_06013638[];
extern Gfx D_06008F08[];
extern Gfx D_06008F70[];
extern UNK_TYPE D_04055DB0;

/*
const ActorInit Boss_Va_InitVars = {
    ACTOR_BOSS_VA,
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_BV,
    sizeof(BossVa),
    (ActorFunc)BossVa_Init,
    (ActorFunc)BossVa_Destroy,
    (ActorFunc)BossVa_Update,
    (ActorFunc)BossVa_Draw,
};
*/

static ColliderCylinderInit sCylinderInit =
{
    { COLTYPE_UNK10, 0x11, 0x09, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFEF, 0x03, 0x08 }, { 0x00000010, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
    { 85, 120, 0, { 0, 0, 0 } },
};

static ColliderJntSphItemInit sJntSphItemsInit[1] = {
    {
        { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000010, 0x00, 0x00 }, 0x00, 0x01, 0x00 },
        { 0, { { 0, 0, 0 }, 25 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit =
{
    { COLTYPE_UNK6, 0x00, 0x09, 0x00, 0x10, COLSHAPE_JNTSPH },
    1, sJntSphItemsInit,
};

static ColliderQuadInit sQuadInit =
{
    { COLTYPE_METAL_SHIELD, 0x11, 0x09, 0x00, 0x00, COLSHAPE_QUAD },
    { 0x00, { 0x20000000, 0x03, 0x04 }, { 0x00000010, 0x00, 0x00 }, 0x81, 0x01, 0x00 },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

Vec3f D_8095C044[] = {
    {0.0f, 175.35000610351562f, 0.0f },
    {0.0f, 175.35000610351562f, 0.0f },
    {0.0f, 175.35000610351562f, 0.0f },
    {120.0f, 103.42500305175781f, -67.0f },
    {0.0f, 103.42500305175781f, 140.0f },
    {-120.0f, 103.42500305175781f, -70.0f },
    {-2.0f, 16.0f, 50.0f },
    {48.0f, 16.0f, 15.0f },
    {25.0f, 16.0f, -36.0f },
    {-29.0f, 16.0f, -36.0f },
    {-63.0f, 16.0f, 22.0f },
    {0.0f, -10.0f, -64.0f },
    {63.0f, -10.0f, -22.0f },
    {35.0f, -10.0f, 46.0f },
    {-36.0f, -10.0f, 46.0f },
    {-49.0f, -10.0f, -17.0f }
};



Vec3s D_8095C1D6[] = { 
    {0x1FFE, 0x0000, 0x0000},
    {0x1FFE, 0x5550, 0x0000}, 
    {0x1FFE, 0xAAB0, 0x0000}, 
    {0xD558, 0x5550, 0x0000}, 
    {0xD558, 0x0000, 0x0000},    
    {0xD558, 0xAAB0, 0x0000}, 
    {0x2AA8, 0xFCCC, 0x0000}, 
    {0x2AA8, 0x3330, 0x0000}, 
    {0x2AA8, 0x6660, 0x0000},
    {0x2AA8, 0x99A0, 0x0000},    
    {0x2AA8, 0xCCD0, 0x0000}, 
    {0x4C98, 0x81D0, 0x0000}, 
    {0x4C98, 0x4F70, 0x0000}, 
    {0x4C98, 0x1758, 0x0000}, 
    {0x4C98, 0xE8A8, 0x0000},    
    {0x4C98, 0xB648, 0x0000}
};

DamageTable D_8095C200[] = {
    0x10, 0x02, 0x01, 0x02, 
    0x10, 0x02, 0x02, 0x10, 
    0x01, 0x02, 0x04, 0x02, 
    0x02, 0x02, 0x02, 0x02, 
    0x02, 0xE0, 0x60, 0xD0, 
    0x00, 0x00, 0x01, 0x04, 
    0x02, 0x02, 0x08, 0x04, 
    0x00, 0x00, 0x04, 0x00
};

Vec3f D_8095C220 = { 0.0f, 0.0f, 0.0f };
u8 D_8095C226[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

s16 D_8095C23C;
Vec3f D_8095C258 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C264 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C270 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C27C = { 15.0f, 0.0f, 0.0f };
Vec3f D_8095C288 = { -15.0f, 0.0f, 0.0f };
Vec3f D_8095C294 = { 15.0f, 0.0f, 0.0f };
Vec3f D_8095C2A0 = { -15.0f, 0.0f, 0.0f };
Vec3f D_8095C2AC = { 0.0f, 45.0f, 0.0f };
Vec3f D_8095C2B8 = { 0.4f, 0.4f, 0.4f };
Vec3f D_8095C2C4 = { 15.0f, 40.0f, 0.0f };
Vec3f D_8095C2D0 = { -15.0f, 40.0f, 0.0f };
Vec3f D_8095C2DC = { 15.0f, 40.0f, 0.0f };
Vec3f D_8095C2E8 = { -15.0f, 40.0f, 0.0f };
Color_RGBA8 D_8095C2F4 = { 0xFA, 0xFA, 0xE6, 0xC8 };
Color_RGBA8 D_8095C2F8 = { 0x00, 0x00, 0xFF, 0xFF };
// Some data here

UNK_PTR D_8095C300[] = {
    0x060096F8, 0x0600A6F8, 0x0600B6F8, 0x0600C6F8, 
    0x0600D6F8, 0x0600E6F8, 0x0600F6F8, 0x060106F8
};

Gfx* D_8095C380[] = {
    0x0601A3E8, 0x0601AEE8, 0x0601B9E8, 0x0601C4E8, 
    0x0601CFE8, 0x0601DAE8, 0x0601E5E8, 0x0601F0E8
};

s16 D_8095C3A0[] = {
    0x0344, 0x0384, 0x0344, 0x03F8, 
    0x0320, 0x03F8, 0x0344, 0x0384
};

BossVaEffect D_8095DF50[400];

u8 D_809668D0;
u8 D_809668D1;
s8 D_809668D2;
Vec3f D_809668D8;
Vec3f D_809668E8;
Vec3f D_809668F8;
Vec3f D_80966908;
Vec3f D_80966918;
Vec3f D_80966928;
s16 D_80966934;
Vec3s D_80966938;
u16 D_8096693E;

void func_8094F2C0(BossVa *this, BossVaActionFunc func) {
    this->actionFunc = func;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8094F2C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8094F50C.s")

void func_8094F60C(GlobalContext *globalCtx, BossVaEffect *arg1, s16 arg2, s16 arg3, s32 arg4) {
    s32 i;
    Vec3f sp60;

    for (i = arg4; i > 0; i--) {
        sp60.x = Math_Rand_CenteredFloat(10.0f) + arg1->unk_00.x;
        sp60.y = arg1->unk_00.y - (Math_Rand_ZeroOne() * 15.0f);
        sp60.z = Math_Rand_CenteredFloat(10.0f) + arg1->unk_00.z;
        func_8095B670(globalCtx, D_8095DF50, &sp60, (s16)Math_Rand_CenteredFloat(26000.0f) + arg2, arg3);
    }
}

void func_8094F734(GlobalContext *globalCtx, BossVaEffect *arg1, s16 arg2, s16 arg3) {
    s32 i;
    Vec3f sp58;

    i = (D_809668D2 < 0x14) ? 2 : 1;

    for (; i > 0; i--) {
        sp58.x = Math_Rand_CenteredFloat(10.0f) + arg1->unk_00.x;
        sp58.y = Math_Rand_CenteredFloat(10.0f) + arg1->unk_00.y;
        sp58.z = Math_Rand_CenteredFloat(10.0f) + arg1->unk_00.z;
        func_8095B9B0(globalCtx, D_8095DF50, &sp58, (s16)Math_Rand_CenteredFloat(26000.0f) + arg2, arg3);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8094F864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8094F9E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8094FB6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8094FBB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8094FC30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8094FC70.s")

#ifdef NON_MATCHING
// Regalloc, stack
void BossVa_Init(Actor* thisx, GlobalContext* globalCtx) {
    BossVa* this = THIS;
    s32 pad;
    s32 i;
    s16 tmp16;
    Vec3f sp5C;

    Actor_SetScale(thisx, 0.1f);
    this->actor.unk_1F = 5;
    this->actor.colChkInfo.mass = 0xFF;

    switch (this->actor.params + 1) {
        case 0:
            SkelAnime_Init(globalCtx, &this->skelAnime, &D_06015B18, &D_06005184, NULL, NULL, 0);
            this->actor.flags |= 0x1000000;
            break;
        case 1:
        case 2:
        case 3:
            SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06017498, &D_060166A8, NULL, NULL, 0);
            break;
        case 4:
        case 5:
        case 6:
            SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060199A0, &D_06018D18, NULL, NULL, 0);
            break;
        case 17:
        case 18:
        case 19:
            SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06018870, &D_06018150, NULL, NULL, 0);
            break;
        
        default:
            this->actor.flags |= 0x1000000;
            SkelAnime_Init(globalCtx, &this->skelAnime, &D_06004E70, &D_06000024, NULL, NULL, 0);
            this->actor.shape.unk_08 = 400.0f;
            break;
        case 20:
            break;
    }

    this->actor.posRot2.pos = this->actor.posRot.pos;
    this->unk_194 = 0;
    this->actor.naviEnemyId = 0x14;

    switch (this->actor.params + 1) {
        case 0:
            Actor_SpawnAttached(&globalCtx->actorCtx, thisx, globalCtx, ACTOR_BOSS_VA, 0.0f, 80.0f, 400.0f, 0, 0, 0, 0x13);
            if (Flags_GetClear(globalCtx, globalCtx->roomCtx.curRoom.num)) {
                tmp16 = ACTOR_EN_RU1;
                if (gSaveContext.eventChkInf[3] & 0x80) {
                    tmp16 = ACTOR_DOOR_WARP1;
                }
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, tmp16, this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0, 0, 0, 0);
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_ITEM_B_HEART, this->actor.posRot.pos.x + 160.0f, this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0, 0, 0, 0);
                D_80966934 = 100;
                Actor_Kill(thisx);
            } else {
                this->actor.colChkInfo.damageTable = D_8095C200;
                D_8096693E = 0xFFFF;
                if (gSaveContext.eventChkInf[7] & 0x40) {
                    D_809668D2 = 8;
                    D_80966934 = 100;
                    func_8002DF54(globalCtx, thisx, 1);
                    globalCtx->envCtx.unk_E2[0] = 0xDC;
                    globalCtx->envCtx.unk_E2[1] = 0xDC;
                    globalCtx->envCtx.unk_E2[2] = 0xBE;
                    globalCtx->envCtx.unk_E2[3] = 0xD2;
                    func_80064520(globalCtx, &globalCtx->csCtx);
                    D_8095C23C = Gameplay_CreateSubCamera(globalCtx);
                    Gameplay_ChangeCameraStatus(globalCtx, 0, 1);
                    Gameplay_ChangeCameraStatus(globalCtx, D_8095C23C, 7);
                    D_809668F8.x = D_809668D8.x = 140.0f;
                    D_809668F8.y = D_809668D8.y = 205.0f;
                    D_809668F8.z = D_809668D8.z = -20.0f;
                    D_80966908.x = D_809668E8.x = 10.0f;
                    D_80966908.y = D_809668E8.y = 50.0f;
                    D_80966908.z = D_809668E8.z = -220.0f;
                    func_800C04D8(globalCtx, D_8095C23C, &D_809668E8, &D_809668D8);
                    this->unk_198 = 0x14;

                    for (i = 15; i > 5; i--) {
                        Actor_SpawnAttached(&globalCtx->actorCtx, thisx, globalCtx, 0xBA, 
                            D_8095C044[i].x + this->actor.posRot.pos.x, 
                            D_8095C044[i].y + this->actor.posRot.pos.y, 
                            D_8095C044[i].z + this->actor.posRot.pos.z, 
                            D_8095C1D6[i].x + this->actor.posRot.rot.x, 
                            D_8095C1D6[i].y + this->actor.posRot.rot.y, 
                            D_8095C1D6[i].z + this->actor.posRot.rot.z, 
                            i);
                    }

                    sp5C = D_8095C220;
                    D_80966918 = sp5C;
                    D_80966928 = sp5C;

                } else {
                    D_809668D2 = -4;
                    D_80966934 = 5;
                }

                this->unk_1CC.x = 1.0f;
                Collider_InitCylinder(globalCtx, &this->collider1);
                Collider_SetCylinder(globalCtx, &this->collider1, thisx, &sCylinderInit);

                for (i = 5; i >= 0; i--) {
                    Actor_SpawnAttached(&globalCtx->actorCtx, thisx, globalCtx, 0xBA, 
                        D_8095C044[i].x + this->actor.posRot.pos.x, 
                        D_8095C044[i].y + this->actor.posRot.pos.y, 
                        D_8095C044[i].z + this->actor.posRot.pos.z, 
                        D_8095C1D6[i].x + this->actor.posRot.rot.x, 
                        D_8095C1D6[i].y + this->actor.posRot.rot.y, 
                        D_8095C1D6[i].z + this->actor.posRot.rot.z, 
                        i);
                }

                Lib_MemSet((u8*)D_8095DF50, 0x8980, 0);
                if (D_809668D2 < 0xD) {
                    func_809506F0(this);
                } else {
                    func_809517A0(this);
                }
            }
            break;

        case 1:
        case 2:
        case 3:
            Collider_InitJntSph(globalCtx, &this->collider2);
            Collider_SetJntSph(globalCtx, &this->collider2, thisx, &sJntSphInit, this->unk_2F8);
            if (D_809668D2 < 0xD) {
                func_80953F4C(this, globalCtx);
            } else {
                func_809540E4(this, globalCtx);
            }
            this->unk_194++;
            break;

        case 4:
        case 5:
        case 6:
            Collider_InitQuad(globalCtx, &this->collider3);
            Collider_SetQuad(globalCtx, &this->collider3, thisx, &sQuadInit);
            if (D_809668D2 < 0xD) {
                func_80954A3C(this, globalCtx);
            } else {
                func_80954B8C(this, globalCtx);
            }
            break;

        case 17:
        case 18:
        case 19:
            func_80954924(this, globalCtx);
            break;

        case 20:
            func_80957C9C(this, globalCtx);
            break;

        default:
            Collider_InitJntSph(globalCtx, &this->collider2);
            Collider_SetJntSph(globalCtx, &this->collider2, thisx, &sJntSphInit, this->unk_2F8);
            Collider_InitQuad(globalCtx, &this->collider3);
            Collider_SetQuad(globalCtx, &this->collider3, thisx, &sQuadInit);
            this->unk_1D8.x = 1.0f;
            this->unk_1D8.y = 1.0f;
            if (D_809668D2 < 0xD) {
                func_809567D0(this, globalCtx);
            } else if (D_809668D1 >= 9) {
                func_80956E38(this, globalCtx);
            } else {
                func_809572DC(this, globalCtx);
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/BossVa_Init.s")
#endif

void BossVa_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    BossVa* this = THIS;

    SkelAnime_Free(&this->skelAnime, globalCtx);
    Collider_DestroyJntSph(globalCtx, &this->collider2);
    Collider_DestroyCylinder(globalCtx, &this->collider1);
}

void func_809506F0(BossVa *this) {
    f32 frames = SkelAnime_GetFrameCount(&D_06005184.genericHeader);

    SkelAnime_ChangeAnim(&this->skelAnime, &D_06005184, 1.0f, frames, frames, 2, 0.0f);
    this->actor.shape.unk_08 = -450.0f;
    this->actor.flags &= -2;
    func_8094F2C0(this, func_80950780);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80950780.s")

void func_809517A0(BossVa *this) {
    f32 frames = SkelAnime_GetFrameCount(&D_06005184.genericHeader);

    SkelAnime_ChangeAnim(&this->skelAnime, &D_06005184, 1.0f, frames, frames, 2, 0.0f);
    this->actor.shape.unk_08 = -450.0f;
    this->actor.flags = this->actor.flags & -2;
    this->unk_198 = 0x19;
    D_809668D0 = 0x80;
    func_8094F2C0(this, func_80951844);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80951844.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80951AD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80951C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80952100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095213C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809527A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80952858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095335C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809533F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80953F4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80953FC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809540E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80954168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095438C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80954454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80954924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809549A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80954A3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80954AD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80954B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80954C20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80955658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095575C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095586C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80955940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80955E64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80955EEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80956644.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809566C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809567D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809568E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80956E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80956EE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809572DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80957384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80957998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809579F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80957C10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80957C68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80957C9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80957CEC.s")

#ifdef NON_MATCHING
// globalCtx stack memes, issue with the loop
void BossVa_Update(Actor* thisx, GlobalContext *globalCtx) {
    BossVa* this = THIS;
    s32 i;
    s16* ptr;

    this->actionFunc(this, globalCtx);

    switch (this->actor.params + 1) {
        case 0:
            if (this->collider1.base.acFlags & 2) {
                this->collider1.base.acFlags &= ~2;
                if (this->collider1.base.ac->id == ACTOR_EN_BOOM) {
                    ((EnBoom*)this->collider1.base.ac)->returnTimer = 0;
                }
            }
            func_809597F4(globalCtx);

            for (i = 2; i >= 0; i--) {

                if ((globalCtx->envCtx.unk_8C[i] - 1) > 0) {
                    globalCtx->envCtx.unk_8C[i] -= 1;
                } else {
                    globalCtx->envCtx.unk_8C[i] = 0;
                }

                if ((globalCtx->envCtx.unk_8C[i + 3] - 10) > 0) {
                    globalCtx->envCtx.unk_8C[i + 3] -= 10;
                } else {
                    globalCtx->envCtx.unk_8C[i + 3] = 0;
                }

                if ((globalCtx->envCtx.unk_8C[i + 6] - 10) > 0) {
                    globalCtx->envCtx.unk_8C[i + 6] -= 10;
                } else {
                    globalCtx->envCtx.unk_8C[i + 6] = 0;
                }
            }

            if (this->unk_194 > 0) {
                this->unk_194--;
            }
            break;

        default:
            this->unk_19C++;
            this->actor.posRot2.pos = this->actor.posRot.pos;
            this->actor.posRot2.pos.y = this->actor.posRot2.pos.y + 45.0f;

            this->unk_1D8.y = (Math_Coss(this->unk_19C * 4004) * 0.24f) + 0.76f;
            this->unk_1D8.x = (Math_Sins(this->unk_19C * 4004) * 0.2f) + 1.0f;
            break;

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 20:
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/BossVa_Update.s")
#endif

#ifdef NON_MATCHING
// 2Tex
s32 func_80957F60(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor* thisx) {
    BossVa* this = THIS;
    s32 pad;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x103C);

        if (limbIndex == 0x14) {
            gDPPipeSync(gfxCtx->polyOpa.p++);
            gSPSegment(gfxCtx->polyOpa.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 8, 0x10, 1, 0, (-globalCtx->gameplayFrames * 2) % 64, 0x10, 0x10));
            gDPSetEnvColor(gfxCtx->polyOpa.p++, 0x00, 0x00, 0x00, this->unk_1AE);
            Matrix_RotateX(-1.5707964f, MTXMODE_APPLY);
        } else if ((limbIndex >= 0xA) && (limbIndex < 0x14)) {
            rot->x -= 0x4000;
            *dList = NULL;
        } else if (limbIndex == 6) {
            Matrix_Scale(this->unk_1A4, this->unk_1A4, this->unk_1A4, MTXMODE_APPLY);
        } else if (limbIndex == 0x3D) {
            Matrix_Scale(this->unk_1A0, this->unk_1A0, this->unk_1A0, MTXMODE_APPLY);
        } else if (limbIndex == 7) {
            rot->x -= 0xCCC;
        }

        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1057);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80957F60.s")
#endif

void func_80958150(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    BossVa* this = THIS;
    Vec3f sp78 = D_8095C258;
    s32 pad;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1060);
        if (limbIndex == 6) {
            if (D_809668D1 < 9) {
                sp78.x = -1000.0f;
            } else {
                sp78.x = 200.0f;
            }
            Matrix_MultVec3f(&sp78, &this->unk_1D8);
        } else if ((limbIndex >= 0xA) && (limbIndex < 0x14) && (D_8095C226[limbIndex] != 0)) {
            if (((limbIndex >= 0x10) || (limbIndex == 0xA)) && (D_809668D1 < 0xA)) {
                gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1070), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gfxCtx->polyXlu.p++, &D_06008BB8);
            } else if ((limbIndex >= 0xB) && (D_809668D1 < 4)) {
                gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gfxCtx->polyXlu.p++, &D_06008BB8);
            }

            if (D_809668D2 >= 0xE) {
                sp78.x = Math_Rand_CenteredFloat(530.0f);
                sp78.y = Math_Rand_CenteredFloat(530.0f);
                sp78.z = -60.0f;
            }
            Matrix_MultVec3f(&sp78, &this->unk_1FC[limbIndex - 10]);
        } else if (limbIndex == 0x19) {
            gSPSegment(gfxCtx->polyXlu.p++, 0x09, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0U, (globalCtx->gameplayFrames * 0xA) % 128, 0x10, 0x20, 1, 0, (globalCtx->gameplayFrames * 5) % 128, 0x10, 0x20));
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1088), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, &D_06008D70);
        } else if ((*dList != NULL) && (limbIndex >= 0x1D) && (limbIndex < 0x38)) {
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x108C), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, *dList);
        } else if ((limbIndex == 0x18) && (D_809668D2 < 0xE)) {
            sp78.x = (thisx->shape.unk_08 + 450.0f) + -140.0f;
            Matrix_MultVec3f(&sp78, &this->unk_280);
            sp78.x = 200.0f;
            Matrix_MultVec3f(&sp78, &this->unk_274);
        }

        if ((limbIndex == 7) && (D_809668D2 >= 0xE)) {
            sp78.x = Math_Rand_CenteredFloat(320.0f) + -250.0f;
            sp78.y = Math_Rand_CenteredFloat(320.0f);
            sp78.z = Math_Rand_CenteredFloat(320.0f);

            if (sp78.y < 0.0f) {
                sp78.y -= 150.0f;
            } else {
                sp78.y += 150.0f;
            }

            if (sp78.z < 0.0f) {
                sp78.z -= 150.0f;
            } else {
                sp78.z += 150.0f;
            }
            Matrix_MultVec3f(&sp78, &this->unk_274);
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x10A8);
    }
}

s32 func_809586A4(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor* thisx) {
    BossVa* this = THIS;

    if ((this->unk_194 == 0) && (limbIndex == 4)) {
        rot->z += this->unk_1F6;
    }
    return 0;
}

void func_809586E4(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor* thisx) {
    BossVa* this = THIS;
    Vec3f sp20 = D_8095C264;
    s32 pad;

    if (this->unk_194 != 0) {
        switch (limbIndex) {
            case 4:
                Matrix_MultVec3f(&D_8095C220, &this->actor.posRot2.pos);
                func_800628A4(0, &this->collider2);
                break;
            case 7:
                Matrix_MultVec3f(&D_8095C220, &this->unk_1B4);
                sp20.x = ((this->unk_198 & 0x1F) >> 1) * -40.0f;
                sp20.y = ((this->unk_198 & 0x1F) >> 1) * -7.0f;
                Matrix_MultVec3f(&sp20, &this->unk_1FC[0]);
                break;
            case 9:
                sp20.x = ((this->unk_198 & 0x1F) >> 1) * -60.0f;
                sp20.y = ((this->unk_198 & 0x1F) >> 1) * -45.0f;
                Matrix_MultVec3f(&sp20, &this->unk_1FC[1]);
                break;
        }
    } else {
        switch (limbIndex) {
            case 5:
                Matrix_MultVec3f(&D_8095C220, &this->unk_1B4);
                break;
            case 8:
                sp20.x = (this->unk_19C & 7) * 90.0f;
                Matrix_MultVec3f(&sp20, &this->unk_1FC[2]);
                break;
            case 9:
                sp20.x = (this->unk_19C & 7) * 50.0f;
                Matrix_MultVec3f(&sp20, &this->unk_1FC[1]);
                break;
            case 10:
                sp20.x = (this->unk_19C & 7) * 46.0f;
                Matrix_MultVec3f(&sp20, &this->unk_1FC[0]);
                break;
        }
    }
}

s32 func_80958934(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor* thisx) {
    BossVa* this = THIS;
    MtxF sp2C;
    s32 pad;

    switch (limbIndex) {
        case 4:
            rot->y += this->unk_1E6;
            rot->z += this->unk_1E4;
            break;

        case 5:
            rot->y += this->unk_1EC;
            rot->z += this->unk_1EA;
            break;

        case 7:
            Matrix_Translate(pos->x, pos->y, pos->z, 1);
            Matrix_Get(&sp2C);
            func_800D2264(&sp2C, &D_80966938, 0);
            Matrix_RotateX(-D_80966938.x * 0.0000958738f, 1);
            Matrix_RotateY(-D_80966938.y * 0.0000958738f, 1);
            Matrix_RotateZ(-D_80966938.z * 0.0000958738f, 1);
            Matrix_RotateY(this->unk_1F2 * 0.0000958738f, 1);
            Matrix_RotateZ(this->unk_1F0 * 0.0000958738f, 1);
            pos->z = 0.0f;
            pos->y = 0.0f;
            pos->x = 0.0f;
            rot->z = 0;
            rot->y = rot->z;
            rot->x = rot->z;
            break;
    }
    return 0;
}

void func_80958B0C(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor* thisx) {
    BossVa* this = THIS;
    Vec3f sp70 = D_8095C270;
    Vec3f sp64 = D_8095C27C;
    Vec3f sp58 = D_8095C288;
    Vec3f sp4C = D_8095C294;
    Vec3f sp40 = D_8095C2A0;
    s16 sp3E;
    s16 sp3C;

    switch (limbIndex) {
        case 3:
            sp70.x = (this->unk_19C & 7) * 30.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[0]);
            break;

        case 4:
            Matrix_MultVec3f(&D_8095C220, &this->unk_1B4);
            sp70.x = (this->unk_19C & 7) * 30.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[1]);
            break;

        case 5:
            Matrix_MultVec3f(&D_8095C220, &this->unk_1C0);
            sp70.x = (this->unk_19C & 7) * 46.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[2]);
            break;

        case 7:
            Matrix_MultVec3f(&D_8095C220, &this->unk_1CC);
            sp70.x = (this->unk_19C & 7) * 46.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[3]);
            sp70.x = 20.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[9]);
            func_80035844(&this->unk_1FC[9], &this->unk_1D8, &this->unk_1F6, 0);
            sp3E = this->unk_1F6;
            sp3C = this->unk_1F8;
            Matrix_Push();
            Matrix_Translate(this->unk_1FC[9].x, this->unk_1FC[9].y, this->unk_1FC[9].z, 0);
            Matrix_RotateRPY(sp3E, sp3C, 0, 1);
            sp70.x = 0.0f;
            if (D_809668D1 >= 0xF) {
                sp70.z = ((this->unk_19C - 0x10) & 7) * 120.0f;
            } else {
                sp70.z = ((this->unk_19C - 0x20) & 0xF) * 80.0f;
            }
            sp70.z += 40.0f;
            sp40.z = sp70.z;
            sp4C.z = sp70.z;
            sp70.z += 50.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[4]);
            if (D_809668D1 >= 0xF) {
                sp70.z -= 33.0f;
                if (sp70.z < 0.0f) {
                    sp70.z = 0.0f;
                }
                Matrix_MultVec3f(&sp70, &this->unk_1FC[6]);
                sp70.z -= 33.0f;
                if (sp70.z < 0.0f) {
                    sp70.z = 0.0f;
                }
            } else {
                sp70.z -= 22.0f;
                if (sp70.z < 0.0f) {
                    sp70.z = 0.0f;
                }
                Matrix_MultVec3f(&sp70, &this->unk_1FC[6]);
                sp70.z -= 22.0f;
                if (sp70.z < 0.0f) {
                    sp70.z = 0.0f;
                }
            }
            Matrix_MultVec3f(&sp70, &this->unk_1FC[5]);
            Matrix_MultVec3f(&sp64, &this->collider3.dim.quad[1]);
            Matrix_MultVec3f(&sp58, &this->collider3.dim.quad[0]);
            Matrix_MultVec3f(&sp4C, &this->collider3.dim.quad[3]);
            Matrix_MultVec3f(&sp40, &this->collider3.dim.quad[2]);
            func_80062734(&this->collider3, &this->collider3.dim.quad[0], &this->collider3.dim.quad[1], 
                &this->collider3.dim.quad[2], &this->collider3.dim.quad[3]);
            Matrix_Pull();
            break;
    }
}

s32 func_80958F6C(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    BossVa* this = THIS;

    switch (limbIndex) {
        case 2:
            *dList = NULL;
            break;
        case 3:
            Matrix_Scale(this->unk_1D8.x, 1.0f, this->unk_1D8.x, 1);
            break;
        case 4:
            Matrix_Scale(1.0f, this->unk_1D8.y, 1.0f, 1);
            break;
    }
    return 0;
}

void func_80958FFC(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor* thisx) {
    BossVa* this = THIS;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x118E);
        if (limbIndex == 2) {
            gSPSegment(gfxCtx->polyXlu.p++, 0x0A, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, (globalCtx->gameplayFrames * 10) % 32, 0x10, 0x20, 1, 0, (-globalCtx->gameplayFrames * 5) % 32, 0x10, 0x20));
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x119C), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06000FA0);
        } else if ((limbIndex == 3) || (limbIndex == 4)) {
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x11A0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, *dList);
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x11A5);
    }
}

#ifdef NON_MATCHING
// 2Tex, regalloc, wrong jump location for case 0
void BossVa_Draw(Actor* thisx, GlobalContext *globalCtx) {
    BossVa* this = THIS;
    s32 pad;
    Vec3f spBC;
    Vec3f spB0 = D_8095C2AC;
    Vec3f spA4 = D_8095C2B8;
    Vec3f sp98 = D_8095C2C4;
    Vec3f sp8C = D_8095C2D0;
    Vec3f sp80 = D_8095C2DC;
    Vec3f sp74 = D_8095C2E8;
    Color_RGBA8 sp70 = D_8095C2F4;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x11BE);
        func_80093D18(globalCtx->state.gfxCtx);
        func_80093D84(globalCtx->state.gfxCtx);

        switch (this->actor.params + 1) {
            case 0:
                if (globalCtx->envCtx.unk_9E != 0) {
                    globalCtx->envCtx.unk_9E += 0x15E;
                    if (globalCtx->envCtx.unk_9E > 0) {
                        globalCtx->envCtx.unk_9E = 0;
                    }
                }

                if (globalCtx->envCtx.unk_A0 != 0) {
                    globalCtx->envCtx.unk_A0 += 0x15E;
                    if (globalCtx->envCtx.unk_A0 > 0) {
                        globalCtx->envCtx.unk_A0 = 0;
                    }
                }

                if (this->unk_197 == 0) {
                    gSPSegment(gfxCtx->polyOpa.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 8, 0x10, 1, 0, (-globalCtx->gameplayFrames * 10) % 16, 0x10, 0x10));
                    gSPSegment(gfxCtx->polyOpa.p++, 0x09, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, ((-globalCtx->gameplayFrames * 1) * 10) % 32, 0x10, 0x20, 1, 0, ((-globalCtx->gameplayFrames * 1) * 5) % 32, 0x10, 0x20));
                    SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, func_80957F60, func_80958150, &this->actor);
                }
                break;

            case 1:
            case 2:
            case 3:
                if (this->unk_197 == 0) {
                    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, func_809586A4, func_809586E4, &this->actor);
                }
                break;

            case 4:
            case 5:
            case 6:
                if (this->unk_197 == 0) {
                    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, func_80958934, func_80958B0C, &this->actor);
                }
                break;

            case 17:
            case 18:
            case 19:
                SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL, NULL, NULL);
                break;

            default:
                if (this->unk_197 == 0) {
                    SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, func_80958F6C, func_80958FFC, &this->actor);
                    func_800628A4(0, &this->collider2);
                    if (D_809668D2 < 0xD) {
                        spBC = this->actor.attachedA->posRot.pos;
                    } else {
                        spBC = ((BossVa*)this->actor.attachedA)->unk_1D8;
                    }
                    Matrix_MultVec3f(&D_8095C220, &this->unk_1FC[1]);
                    Matrix_Push();
                    Matrix_Translate(spBC.x, spBC.y, spBC.z, 0);
                    Matrix_RotateRPY(this->actor.posRot.rot.x, this->actor.posRot.rot.y, 0, 1);
                    sp80.z = sp74.z = this->unk_1A0;
                    spB0.z = (this->unk_19C & 0xF) * (this->unk_1A0 * 0.0625f);
                    Matrix_MultVec3f(&spB0, &this->unk_1FC[0]);
                    Matrix_MultVec3f(&sp98, &this->collider3.dim.quad[1]);
                    Matrix_MultVec3f(&sp8C, &this->collider3.dim.quad[0]);
                    Matrix_MultVec3f(&sp80, &this->collider3.dim.quad[3]);
                    Matrix_MultVec3f(&sp74, &this->collider3.dim.quad[2]);
                    func_80062734(&this->collider3, &this->collider3.dim.quad[0], &this->collider3.dim.quad[1], &this->collider3.dim.quad[2], &this->collider3.dim.quad[3]);
                    Matrix_Pull();
                    spBC = this->actor.posRot.pos;
                    spBC.y += 9.0f;
                    if (this->actor.dmgEffectTimer != 0) {
                        func_80026A6C(globalCtx);
                    }
                    func_80033C30(&spBC, &spA4, 0xFF, globalCtx);
                    if (this->actor.dmgEffectTimer != 0) {
                        Color_RGBA8 sp50 = D_8095C2F8;
                        func_80026860(globalCtx, &sp50, this->actor.dmgEffectTimer, this->actor.dmgEffectParams & 0xFF);
                    }
                }
                break;

            case 20:
                break;
        }

        if (this->actor.params == -1) {
            func_8095A188(D_8095DF50, globalCtx);
        } else if (this->actor.params == 0x13) {
            func_8095BD24(globalCtx, D_80966934);
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1241);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/BossVa_Draw.s")
#endif

#ifdef NON_MATCHING
// Regalloc, wrong data accesses/types
void func_809597F4(GlobalContext *globalCtx) {
    Player* player = PLAYER; // spB8
    s16 spB6;
    s16 i;
    BossVaEffect* ptr = D_8095DF50;
    f32 tmpf1;
    s16 tmp16;
    s16 spAA;
    BossVa* refActor; // spA4
    s32 pad;
    Vec3f sp94;
    CollisionPoly* sp90;
    s32 pad2;
    Vec3f sp80;
    CollisionPoly* sp7C;

    Vec3f sp64;

    for (i = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 != 0) {
            ptr->unk_00.x += ptr->unk_0C.x;
            ptr->unk_00.y += ptr->unk_0C.y;
            ptr->unk_00.z += ptr->unk_0C.z;
            ptr->unk_26--;
            ptr->unk_0C.x += ptr->unk_18.x;
            ptr->unk_0C.y += ptr->unk_18.y;
            ptr->unk_0C.z += ptr->unk_18.z;
            if ((ptr->unk_24 == 1) || (ptr->unk_24 == 3)) {
                refActor = ptr->unk_54;

                ptr->unk_2E += (s16)(Math_Rand_ZeroOne() * 20000.0f) + 0x2000;
                ptr->unk_2C += (s16)(Math_Rand_ZeroOne() * 10000.0f) + 0x2000;

                if ((ptr->unk_28 == 1) || (ptr->unk_28 == 4)) {
                    spAA = ptr->unk_2A - Math_Vec3f_Pitch(&refActor->actor.posRot.pos, &((BossVa*)refActor->actor.attachedA)->unk_1D8);
                    ptr->unk_00.x = refActor->actor.posRot.pos.x - (Math_Sins(refActor->actor.posRot.rot.y) * ptr->unk_44[1]);
                    ptr->unk_00.z = refActor->actor.posRot.pos.z - (Math_Coss(refActor->actor.posRot.rot.y) * ptr->unk_44[1]);
                    ptr->unk_00.y = (Math_Coss(-spAA) * ptr->unk_44[2]) + refActor->actor.posRot.pos.y;
                } else if ((ptr->unk_28 == 2) || (ptr->unk_28 == 5)) {
                    ptr->unk_00.x = ptr->unk_44[1] + refActor->actor.posRot.pos.x;
                    ptr->unk_00.y = ptr->unk_44[2] + refActor->actor.posRot.pos.y;
                    ptr->unk_00.z = ptr->unk_44[3] + refActor->actor.posRot.pos.z;
                } else {
                    spB6 = Math_Rand_ZeroFloat(17.9f);
                    ptr->unk_00.x = Math_Rand_CenteredFloat(10.0f) + player->unk_908[spB6].x;
                    ptr->unk_00.y = Math_Rand_CenteredFloat(15.0f) + player->unk_908[spB6].y;
                    ptr->unk_00.z = Math_Rand_CenteredFloat(10.0f) + player->unk_908[spB6].z;
                }

                if (ptr->unk_26 < 100) {
                    ptr->unk_30[3] -= 50;
                    if (ptr->unk_30[3] < 0) {
                        ptr->unk_30[3] = 0;
                        ptr->unk_26 = 0;
                        ptr->unk_24 = 0;
                    }
                }
            }

            if (ptr->unk_24 == 2) {
                ptr->unk_2E += (s16)(Math_Rand_ZeroOne() * 20000.0f) + 0x4000;
                if (ptr->unk_26 < 100) {
                    ptr->unk_30[3] -= 50;
                    if (ptr->unk_30[3] < 0) {
                        ptr->unk_30[3] = 0;
                        ptr->unk_26 = 0;
                        ptr->unk_24 = 0;
                    }
                }
            }

            if (ptr->unk_24 == 4) {
                refActor = ptr->unk_54;

                ptr->unk_2E += (s16)(Math_Rand_ZeroOne() * 10000.0f) + 0x24A8;
                ptr->unk_00.x = ptr->unk_44[1] + refActor->actor.posRot.pos.x;
                ptr->unk_00.y = (refActor->actor.posRot.pos.y + 310.0f) + (refActor->actor.shape.unk_08 * refActor->actor.scale.y);
                ptr->unk_00.z = ptr->unk_44[3] + refActor->actor.posRot.pos.z;
                ptr->unk_28 = (ptr->unk_28 + 1) & 7;
                
                if (ptr->unk_26 < 100) {
                    ptr->unk_30[3] -= 50;
                    if (ptr->unk_30[3] < 0) {
                        ptr->unk_30[3] = 0;
                        ptr->unk_26 = 0;
                        ptr->unk_24 = 0;
                    }
                }
            }

            if (ptr->unk_24 == 5) {
                ptr->unk_30[3] -= 20;
                ptr->unk_28 = (ptr->unk_28 + 1) & 7;
                if (ptr->unk_30[3] <= 0) {
                    ptr->unk_30[3] = 0;
                    ptr->unk_26 = 0;
                    ptr->unk_24 = 0;
                }
            }

            if (ptr->unk_24 == 6) {
                if (ptr->unk_28 < 2) {
                    sp94 = ptr->unk_00;
                    sp94.y = sp94.y - (ptr->unk_0C.y + 4.0f);
                    tmpf1 = func_8003C890(&globalCtx->colCtx, &sp90, &sp94);
                    if (sp90 != NULL) {
                        if (ptr->unk_00.y <= tmpf1) {
                            ptr->unk_28 = 2;
                            ptr->unk_00.y = tmpf1 + 1.0f;
                            if (D_809668D2 < 20) {
                                ptr->unk_26 = 0x50;
                            } else {
                                ptr->unk_26 = 0xEA60;
                            }

                            sp64 = D_8095C220;
                            ptr->unk_0C = sp64;
                            ptr->unk_18 = sp64;
                        }
                    }

                    if (ptr->unk_26 == 0) {
                        ptr->unk_24 = 0;
                    }

                } else if (ptr->unk_26 < 0x14) {
                    ptr->unk_30[3] = ptr->unk_26 * 10;
                    ptr->unk_38[3] = ptr->unk_26 * 5;
                } else if (ptr->unk_26 >= 0xC351) {
                    ptr->unk_26++;
                }

                if (ptr->unk_26 == 0) {
                    ptr->unk_24 = 0;
                }
            }

            if (ptr->unk_24 == 8) {
                if (ptr->unk_28 == 0) {
                    sp80 = ptr->unk_00;
                    sp80.y = sp80.y - (ptr->unk_0C.y + 4.0f);
                    ptr->unk_2A += 0x1770;
                    tmpf1 = func_8003C890(&globalCtx->colCtx, &sp7C, &sp80);
                    if ((sp7C != NULL) && (ptr->unk_00.y <= tmpf1)) {
                        ptr->unk_28 = 1;
                        ptr->unk_26 = 0x1E;
                        ptr->unk_00.y = tmpf1 + 1.0f;

                        sp64 = D_8095C220;
                        ptr->unk_0C = sp64;
                        ptr->unk_18 = sp64;
                        ptr->unk_2A = -0x4000;
                    }

                    if (ptr->unk_26 == 0) {
                        ptr->unk_24 = 0;
                    }

                } else if (ptr->unk_28 == 2) {
                    if (ptr->unk_26 == 0) {
                        ptr->unk_24 = 0;
                    }

                } else {
                    Math_SmoothScaleMaxMinF(&ptr->unk_44[0], 0.075f, 1.0f, 0.005f, 0.0f);
                    Math_SmoothScaleMaxMinF(&ptr->unk_44[2], 0.0f, 0.6f, 0.005f, 0.0013f);
                    if ((globalCtx->gameplayFrames % 4) == 0) {
                        Math_SmoothScaleMaxMinS(&ptr->unk_30[0], 0x5F, 1, 1, 0);
                    }
                }
                ptr->unk_44[1] += ptr->unk_44[2];
            }

            if (ptr->unk_24 == 7) {
                refActor = ptr->unk_54;

                ptr->unk_2E += 0x157C;
                ptr->unk_38[3] = (s16)(Math_Sins(ptr->unk_2E) * 50.0f) + 0x50;
                Math_SmoothScaleMaxMinF(&ptr->unk_40, ptr->unk_44[0], 1.0f, 0.01f, 0.005f);
                ptr->unk_00.x = ptr->unk_44[1] + refActor->actor.posRot.pos.x;
                ptr->unk_00.y = ptr->unk_44[2] + refActor->actor.posRot.pos.y;
                ptr->unk_00.z = ptr->unk_44[3] + refActor->actor.posRot.pos.z;

                switch (ptr->unk_28) {
                    case 0:
                        if (ptr->unk_26 == 0) {
                            tmp16 = Math_Vec3f_Yaw(&refActor->actor.posRot.pos, &ptr->unk_00);
                            ptr->unk_24 = 0;
                            func_8094F60C(globalCtx, ptr, tmp16, ptr->unk_40 * 4500.0f, 1);
                            func_8094F734(globalCtx, ptr, tmp16, ptr->unk_40 * 1.2f);
                        }
                        break;

                    case 1:
                    case 2:
                        if (refActor->unk_195 != 0) {
                            ptr->unk_24 = 0;
                            tmp16 = Math_Vec3f_Yaw(&refActor->actor.posRot.pos, &ptr->unk_00);
                            func_8094F60C(globalCtx, ptr, tmp16, ptr->unk_40 * 4500.0f, 1);
                            func_8094F734(globalCtx, ptr, tmp16, ptr->unk_40 * 1.2f);
                        }
                        break;
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809597F4.s")
#endif

#ifdef NON_MATCHING
// Stack, 2 lines out of order near the end
void func_8095A188(BossVaEffect *arg0, GlobalContext *globalCtx) {
    BossVaEffect* ptr = arg0;
    u8 flag = 0;
    s16 i;
    s32 pad2;
    BossVa* refActor;
    Camera* camera;

    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];
    

    camera = Gameplay_GetCamera(globalCtx, D_8095C23C);

    Graph_OpenDisps(dispRefs, gfxCtx, "../z_boss_va.c", 0x1359);
    
    for (i = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 1) {
            if (!flag) {
                func_80093D84(globalCtx->state.gfxCtx);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x82, 0x82, 0x1E, 0x00);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_060156A0);
                flag += 1;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xE6, 0xE6, 0xE6, ptr->unk_30[3]);
            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_RotateZ((ptr->unk_2E / 32768.0f) * 3.1416f, 1);
            Matrix_Scale(ptr->unk_40 * 0.0185f, ptr->unk_40 * 0.0185f, 1.0f, 1);
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(gfxCtx, "../z_boss_va.c", 0x1370), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06015710);
        }
    }

    for (ptr = arg0, i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 4) {
            if (!flag) {
                func_80093D84(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_06011738);
                flag += 1;
            }
            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_Scale(ptr->unk_40, ptr->unk_40, ptr->unk_40, 1);
            Matrix_RotateZ((ptr->unk_2E / 32768.0f) * M_PI, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(gfxCtx, "../z_boss_va.c", 0x138A), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPPipeSync(gfxCtx->polyXlu.p++);
            gSPSegment(gfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_8095C300[ptr->unk_28]));
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, ptr->unk_30[0], ptr->unk_30[1], ptr->unk_30[2], ptr->unk_30[3]);
            gDPPipeSync(gfxCtx->polyXlu.p++);
            gDPSetEnvColor(gfxCtx->polyXlu.p++, ptr->unk_38[0], ptr->unk_38[1], ptr->unk_38[2], ptr->unk_38[3]);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06011768);
        }
    }

    for (ptr = arg0, i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 6) {
            if (!flag) {
                func_80093D84(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_06009430);
                gSPSegment(gfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(&D_04055DB0));
                flag += 1;
            }

            gDPPipeSync(gfxCtx->polyXlu.p++);
            gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x00, 0x64, 0x00, ptr->unk_38[3]);
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x00, 0x96, 0x00, ptr->unk_30[3]);

            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            if (ptr->unk_28 == 2) {
                Matrix_RotateX(1.5707964f, 1);
            } else {
                func_800D1FD4(&globalCtx->mf_11DA0);
            }

            Matrix_Scale(ptr->unk_40, ptr->unk_40, 1.0f, 1);

            gDPPipeSync(gfxCtx->polyXlu.p++);
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(gfxCtx, "../z_boss_va.c", 0x13BC), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06009468);
        }
    }


    for (ptr = arg0, i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 7) {
            refActor = ptr->unk_54;
            if (!flag) {
                func_80093D18(globalCtx->state.gfxCtx);
                gDPSetEnvColor(gfxCtx->polyOpa.p++, 0x00, 0x00, 0x00, ptr->unk_38[3]);
                gSPDisplayList(gfxCtx->polyOpa.p++, D_060128B8);
                flag += 1;
            }

            if ((ptr->unk_28 != 1) || ((Math_Vec3f_DistXZ(&camera->eye, &ptr->unk_00) - Math_Vec3f_DistXZ(&camera->eye, &refActor->actor.posRot.pos)) < 10.0f)) {
                Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
                Matrix_Scale(ptr->unk_40, ptr->unk_40, ptr->unk_40, 1);

                gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(gfxCtx, "../z_boss_va.c", 0x13D8), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gfxCtx->polyOpa.p++, D_06012948);
            }
        }
    }

    for (ptr = arg0, i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 8) {
            if (!flag) {
                func_80093D18(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyOpa.p++, D_06012BA0);
                flag += 1;
            }

            gDPPipeSync(gfxCtx->polyOpa.p++);
            gDPSetEnvColor(gfxCtx->polyOpa.p++, 0xFF, 0xFF, 0xFF, ptr->unk_30[3]);
            gDPSetPrimColor(gfxCtx->polyOpa.p++, 0, 0, ptr->unk_30[0], ptr->unk_30[1], ptr->unk_30[2], ptr->unk_30[3]);

            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            Matrix_RotateRPY(ptr->unk_2A, ptr->unk_2C, 0, 1);
            Matrix_Scale(ptr->unk_40, ptr->unk_40, ptr->unk_40, 1);
            Matrix_RotateX(ptr->unk_44[1] * 0.115f, 1);
            Matrix_RotateY(ptr->unk_44[1] * 0.13f, 1);
            Matrix_RotateZ(ptr->unk_44[1] * 0.1f, 1);
            Matrix_Scale(1.0f - ptr->unk_44[0], ptr->unk_44[0] + 1.0f, 1.0f - ptr->unk_44[0], 1);
            Matrix_RotateZ(-(ptr->unk_44[1] * 0.1f), 1);
            Matrix_RotateY(-(ptr->unk_44[1] * 0.13f), 1);
            Matrix_RotateX(-(ptr->unk_44[1] * 0.115f), 1);

            gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(gfxCtx, "../z_boss_va.c", 0x1404), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyOpa.p++, D_06012C50);
        }
    }

    for (ptr = arg0, i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 5) {
            if (!flag) {
                func_80093D84(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_060135B0);
                flag += 1;
            }

            gDPPipeSync(gfxCtx->polyXlu.p++);
            gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xFF, 0x32, ptr->unk_30[3]);
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, ptr->unk_30[3]);

            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            Matrix_RotateRPY(ptr->unk_2A, ptr->unk_2C, 0, 1);
            Matrix_Scale(ptr->unk_40, ptr->unk_40, ptr->unk_40, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(gfxCtx, "../z_boss_va.c", 0x1420), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06013638);
        }
    }

    for (ptr = arg0, i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 2) {
            if (!flag) {
                func_80093C14(globalCtx->state.gfxCtx);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x82, 0x82, 0x1E, 0x00);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_060156A0);
                flag += 1;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xE6, 0xE6, 0xE6, ptr->unk_30[3]);
            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_RotateZ((ptr->unk_2E / 32768.0f) * M_PI, 1);
            Matrix_Scale(ptr->unk_40 * 0.02f, ptr->unk_40 * 0.02f, 1.0f, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(gfxCtx, "../z_boss_va.c", 0x143C), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06015710);
        }
    }

    for (ptr = arg0, i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 3) {
            if (!flag) {
                func_80093D84(globalCtx->state.gfxCtx);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xFF, 0x64, 0x00);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_06008F08);
                flag += 1;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, ptr->unk_30[3]);
            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            Matrix_RotateZ((ptr->unk_2E / 32768.0f) * M_PI, 1);
            Matrix_RotateY((ptr->unk_2C / 32768.0f) * M_PI, 1);
            Matrix_Scale(ptr->unk_40, ptr->unk_40, 1.0f, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(gfxCtx, "../z_boss_va.c", 0x1458), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06008F70);
        }
    }

    Graph_CloseDisps(dispRefs, gfxCtx, "../z_boss_va.c", 0x145F);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095A188.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095B028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095B318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095B4A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095B670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095B80C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095B9B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_8095BBD0.s")

void func_8095BD24(GlobalContext *globalCtx, s16 arg1) {
    MtxF sp98;
    f32 tmpf1;
    f32 tmpf2 = 0.0f;
    f32 tmpf3;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];
    s32 i;

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x15E0);
    Matrix_Translate(0.0f, 80.0f, 400.0f, 0);
    Matrix_RotateY(M_PI, 1);
    tmpf3 = (arg1 * 0.01f) * 0.1f;
    Matrix_Scale(0.1f, tmpf3, 0.1f, 1);

    if (tmpf3 != 0.0f) {
        tmpf1 = 0.1f / tmpf3;
    } else {
        tmpf1 = 0.0f;
    }

    Matrix_Get(&sp98);

    for (i = 0; i < 8; i++, tmpf2 -= 0.7853982f) {
        Matrix_Put(&sp98);
        Matrix_RotateZ(tmpf2, 1);
        Matrix_Translate(0.0f, D_8095C3A0[i] * tmpf1, 0.0f, 1);

        gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x15F5), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyOpa.p++, D_8095C380[i]);
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x15FD);
}
