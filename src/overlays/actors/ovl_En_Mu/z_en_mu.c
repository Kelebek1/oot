/*
 * File: z_en_mu.c
 * Overlay: ovl_En_Mu
 * Description: Haggling Townspeople
 */

#include "z_en_mu.h"

#define FLAGS 0x00000009

#define THIS ((EnMu*)thisx)

void EnMu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMu_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AB0724(EnMu* this, GlobalContext* globalCtx);

extern SkeletonHeader D_06004F70;
extern AnimationHeader D_060003F4;

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 100, 70, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 D_80AB0BFC = { 0x00, 0x0000, 0x0000, 0x0000, 0xFF };

const ActorInit En_Mu_InitVars = {
    ACTOR_EN_MU,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_MU,
    sizeof(EnMu),
    (ActorFunc)EnMu_Init,
    (ActorFunc)EnMu_Destroy,
    (ActorFunc)EnMu_Update,
    (ActorFunc)EnMu_Draw,
};

void func_80AB0420(EnMu* this, EnMuActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void func_80AB0428(EnMu* this, GlobalContext* globalCtx) {
    u8 sp30[] = { 0x42, 0x43, 0x3F, 0x41, 0x3E };
    u8 sp28[] = { 0x01, 0x02, 0x04, 0x08, 0x10 };
    u8 sp27;
    s32 rand;
    s32 i;

    sp27 = gSaveContext.eventInf[2];
    sp27 &= 0x1F;
    gSaveContext.eventInf[2] &= 0xFFE0;
    rand = ((s32)(Math_Rand_ZeroOne() * 5.0f) + globalCtx->state.frames) % 5;

    for (i = 0; i < 5; i++) {
        if (!(sp27 & sp28[rand])) {
            break;
        }
        rand++;
        if (rand >= 5) {
            rand = 0;
        }
    }

    if (i == 5) {
        if (this->unk_208 == (sp30[rand] | 0x7000)) {
            rand++;
            if (rand >= 5) {
                rand = 0;
            }
        }
        sp27 = 0;
    }
    sp27 |= sp28[rand];
    sp27 &= 0xFF;

    this->unk_208 = sp30[rand] | 0x7000;
    gSaveContext.eventInf[2] |= sp27;
}

u16 func_80AB0584(GlobalContext* globalCtx, Actor* thisx) {
    EnMu* this = THIS;
    u16 reaction = Text_GetFaceReaction(globalCtx, this->actor.params + 0x3A);

    if (reaction != 0) {
        return reaction;
    }
    return this->unk_208;
}

s16 func_80AB05C4(GlobalContext* globalCtx, Actor* thisx) {
    EnMu* this = THIS;

    switch (func_8010BDBC(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            return 1;
        case 2:
            func_80AB0428(this, globalCtx);
            return 0;
    }

    return 1;
}

void EnMu_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMu* this = THIS;
    s32 pad;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 160.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06004F70, &D_060003F4, 0, 0, 0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    func_80061EFC(&this->actor.colChkInfo, NULL, &D_80AB0BFC);
    this->actor.unk_1F = 6;
    Actor_SetScale(&this->actor, 0.01f);
    func_80AB0428(this, globalCtx);
    func_80AB0420(this, func_80AB0724);
}

void EnMu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMu* this = THIS;

    SkelAnime_Free(&this->skelAnime, globalCtx);
}

void func_80AB0724(EnMu* this, GlobalContext* globalCtx) {
    func_80034F54(globalCtx, this->unk_20A, this->unk_22A, 0x10);
}

void EnMu_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMu* this = THIS;
    f32 tmpf1;
    s32 pad;
    Vec3s sp2C;

    sp2C.x = this->actor.posRot.pos.x;
    sp2C.y = this->actor.posRot.pos.y;
    sp2C.z = this->actor.posRot.pos.z;
    this->collider.dim.pos = sp2C;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_8002E4B4(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    this->actionFunc(this, globalCtx);
    tmpf1 = this->collider.dim.radius + 30.0f;
    func_800343CC(globalCtx, &this->actor, &this->unk_1E0.unk_00, tmpf1, func_80AB0584, func_80AB05C4);
    this->actor.posRot2.pos = this->actor.posRot.pos;
    this->actor.posRot2.pos.y = this->actor.posRot2.pos.y + 60.0f;
}

s32 func_80AB08A4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnMu* this = THIS;

    if ((limbIndex == 5) || (limbIndex == 6) || (limbIndex == 7) || (limbIndex == 11) || (limbIndex == 12) ||
        (limbIndex == 13) || (limbIndex == 14)) {
        rot->y += Math_Sins(this->unk_20A[limbIndex]) * 200.0f;
        rot->z += Math_Coss(this->unk_22A[limbIndex]) * 200.0f;
    }

    return 0;
}

void func_80AB0994(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

Gfx* func_80AB09A8(GraphicsContext* gfxCtx, u8 r, u8 g, u8 b, u8 a) {
    Gfx* dList = Graph_Alloc(gfxCtx, 2 * sizeof(Gfx));

    gDPSetEnvColor(dList, r, g, b, a);
    gSPEndDisplayList(dList + 1);
    return dList;
}

void EnMu_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMu* this = THIS;
    Color_RGBA8_n sp84[][5] = {
        {
            { 100, 130, 235, 0 },
            { 160, 250, 60, 0 },
            { 90, 60, 20, 0 },
            { 30, 240, 200, 0 },
            { 140, 70, 20, 0 },
        },
        {
            { 140, 70, 20, 0 },
            { 30, 240, 200, 0 },
            { 90, 60, 20, 0 },
            { 160, 250, 60, 0 },
            { 100, 130, 235, 0 },
        },
    };
    u8 sp7C[] = {
        0x08, 0x09, 0x0A, 0x0B, 0x0C,
    };
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_mu.c", 514);

    Matrix_Translate(-1200.0f, 0.0f, -1400.0f, MTXMODE_APPLY);

    for (i = 0; i < 5; i++) {
        gSPSegment(oGfxCtx->polyOpa.p++, sp7C[i],
                   func_80AB09A8(globalCtx->state.gfxCtx, sp84[this->actor.params][i].r, sp84[this->actor.params][i].g,
                                 sp84[this->actor.params][i].b, sp84[this->actor.params][i].a));
    }

    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80AB08A4, func_80AB0994, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_mu.c", 534);
}
