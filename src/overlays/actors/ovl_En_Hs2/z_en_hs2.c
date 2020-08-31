/*
 * File: z_en_hs2.c
 * Overlay: ovl_En_Hs2
 * Description: Carpenter's Son (Child Link version)
 */

#include "z_en_hs2.h"
#include "vt.h"

#define FLAGS 0x00000009

#define THIS ((EnHs2*)thisx)

void EnHs2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHs2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHs2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHs2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A6F1A4(EnHs2* this, GlobalContext* globalCtx);

extern SkeletonHeader D_06006260;
extern AnimationHeader D_060005C0;

const ActorInit En_Hs2_InitVars = {
    ACTOR_EN_HS2,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_HS,
    sizeof(EnHs2),
    (ActorFunc)EnHs2_Init,
    (ActorFunc)EnHs2_Destroy,
    (ActorFunc)EnHs2_Update,
    (ActorFunc)EnHs2_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x11, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x01, 0x01 },
    { 40, 40, 0, { 0, 0, 0 } },
};

void EnHs2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHs2* this = THIS;
    s32 pad;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 36.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06006260, &D_060005C0, this->limbDrawTable,
                     this->transitionDrawTable, 16);
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_060005C0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = 0xFF;
    Actor_SetScale(&this->actor, 0.01f);
    // Kokiri shop (when child)
    osSyncPrintf(VT_FGCOL(CYAN) " ヒヨコの店(子人の時) \n" VT_RST);
    this->actionFunc = func_80A6F1A4;
    this->unk_2A8 = 0;
    this->actor.unk_1F = 6;
}

void EnHs2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHs2* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

s32 func_80A6F0B4(EnHs2* this, GlobalContext* globalCtx, u16 arg2, EnHs2ActionFunc func) {
    s16 tmp;

    if (func_8002F194(&this->actor, globalCtx) != 0) {
        this->actionFunc = func;
        return 1;
    }

    this->actor.textId = arg2;
    tmp = this->actor.yawTowardsLink - this->actor.shape.rot.y;
    if ((ABS(tmp) < 0x2151) && (this->actor.xzDistFromLink < 100.0f)) {
        this->unk_2A8 |= 1;
        func_8002F2CC(&this->actor, globalCtx, 100.0f);
    }

    return 0;
}

void func_80A6F164(EnHs2* this, GlobalContext* globalCtx) {
    if (func_8002F334(&this->actor, globalCtx) != 0) {
        this->actionFunc = func_80A6F1A4;
    }

    this->unk_2A8 |= 1;
}

void func_80A6F1A4(EnHs2* this, GlobalContext* globalCtx) {
    u16 reaction = Text_GetFaceReaction(globalCtx, 9);
    if (reaction == 0) {
        reaction = 0x5069;
    }

    func_80A6F0B4(this, globalCtx, reaction, func_80A6F164);
}

void EnHs2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHs2* this = THIS;
    s32 pad;

    Collider_CylinderUpdate(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_MoveForward(&this->actor);
    func_8002E4B4(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        this->skelAnime.animCurrentFrame = 0.0f;
    }

    this->actionFunc(this, globalCtx);

    if (this->unk_2A8 & 1) {
        func_80038290(globalCtx, &this->actor, &this->unk_29C, &this->unk_2A2, this->actor.posRot2.pos);
        this->unk_2A8 &= ~1;
    } else {
        Math_SmoothScaleMaxMinS(&this->unk_29C.x, 0x3200, 6, 0x1838, 0x64);
        Math_SmoothScaleMaxMinS(&this->unk_29C.y, 0, 6, 0x1838, 0x64);
        Math_SmoothScaleMaxMinS(&this->unk_2A2.x, 0, 6, 0x1838, 0x64);
        Math_SmoothScaleMaxMinS(&this->unk_2A2.y, 0, 6, 0x1838, 0x64);
    }
}

s32 EnHs2_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnHs2* this = THIS;

    switch (limbIndex) {
        case 12:
        case 13:
            *dList = NULL;
            return 0;
        case 9:
            rot->x += this->unk_29C.y;
            rot->z += this->unk_29C.x;
            break;
        case 10:
            *dList = NULL;
            return 0;
        case 11:
            *dList = NULL;
            return 0;
    }

    return 0;
}

void EnHs2_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80A6F4CC = { 300.0f, 1000.0f, 0.0f };

    EnHs2* this = THIS;

    if (limbIndex == 9) {
        Matrix_MultVec3f(&D_80A6F4CC, &this->actor.posRot2.pos);
    }
}

void EnHs2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHs2* this = THIS;

    func_800943C8(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnHs2_OverrideLimbDraw, EnHs2_PostLimbDraw, &this->actor);
}
