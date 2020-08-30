/*
 * File: z_en_hs.c
 * Overlay: ovl_En_Hs
 * Description: Carpenter's Son
 */

#include "z_en_hs.h"
#include "vt.h"

#define FLAGS 0x00000009

#define THIS ((EnHs*)thisx)

void EnHs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHs_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A6E9AC(EnHs* this, GlobalContext* globalCtx);
void func_80A6E6B0(EnHs* this, GlobalContext* globalCtx);

extern SkeletonHeader D_06006260;
extern AnimationHeader D_060005C0;
extern AnimationHeader D_06000304;
extern AnimationHeader D_06000528;

const ActorInit En_Hs_InitVars = {
    ACTOR_EN_HS,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_HS,
    sizeof(EnHs),
    (ActorFunc)EnHs_Init,
    (ActorFunc)EnHs_Destroy,
    (ActorFunc)EnHs_Update,
    (ActorFunc)EnHs_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x11, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x01, 0x01 },
    { 40, 40, 0, { 0, 0, 0 } },
};

void func_80A6E3A0(EnHs* this, EnHsActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnHs_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHs* this = THIS;
    s32 pad;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 36.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06006260, &D_060005C0, this->limbDrawTable,
                     this->transitionDrawTable, 16);
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_060005C0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = 0xFF;
    Actor_SetScale(&this->actor, 0.01f);
    if (LINK_IS_CHILD) {
        this->actor.params = 0;
    } else {
        this->actor.params = 1;
    }

    if (this->actor.params == 1) {
        // Kokiri shop (when adult)
        osSyncPrintf(VT_FGCOL(CYAN) " ヒヨコの店(大人の時) \n" VT_RST);
        func_80A6E3A0(this, func_80A6E9AC);
        if (gSaveContext.itemGetInf[3] & 1) {
            // Kokiri shop closed
            osSyncPrintf(VT_FGCOL(CYAN) " ヒヨコ屋閉店 \n" VT_RST);
            Actor_Kill(&this->actor);
        }
    } else {
        // Kokiri shop (when child)
        osSyncPrintf(VT_FGCOL(CYAN) " ヒヨコの店(子人の時) \n" VT_RST);
        func_80A6E3A0(this, func_80A6E9AC);
    }

    this->unk_2A8 = 0;
    this->actor.unk_1F = 6;
}

void EnHs_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHs* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

s32 func_80A6E53C(EnHs* this, GlobalContext* globalCtx, u16 arg2, EnHsActionFunc arg3) {
    s16 tmp;

    if (func_8002F194(&this->actor, globalCtx) != 0) {
        func_80A6E3A0(this, arg3);
        return 1;
    } else {
        this->actor.textId = arg2;
        tmp = this->actor.yawTowardsLink - this->actor.shape.rot.y;
        if ((ABS(tmp) < 0x2151) && (this->actor.xzDistFromLink < 100.0f)) {
            this->unk_2A8 |= 1;
            func_8002F2CC(&this->actor, globalCtx, 100.0f);
        }
    }
    return 0;
}

void func_80A6E5EC(EnHs* this, GlobalContext* globalCtx) {
    if (func_8002F334(&this->actor, globalCtx) != 0) {
        func_80A6E3A0(this, func_80A6E6B0);
    }

    this->unk_2A8 |= 1;
}

void func_80A6E630(EnHs* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 6) && (func_80106BC8(globalCtx) != 0)) {
        func_80088AA0(0xB4);
        func_80A6E3A0(this, func_80A6E6B0);
        gSaveContext.eventInf[1] &= ~1;
    }

    this->unk_2A8 |= 1;
}

void func_80A6E6B0(EnHs* this, GlobalContext* globalCtx) {
    func_80A6E53C(this, globalCtx, 0x10B6, func_80A6E5EC);
}

void func_80A6E6D8(EnHs* this, GlobalContext* globalCtx) {
    if (func_8002F334(&this->actor, globalCtx) != 0) {
        func_80A6E3A0(this, func_80A6E9AC);
    }
}

void func_80A6E70C(EnHs* this, GlobalContext* globalCtx) {
    if (func_8002F334(&this->actor, globalCtx) != 0) {
        func_80A6E3A0(this, func_80A6E9AC);
    }
}

void func_80A6E740(EnHs* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        func_80A6E3A0(this, func_80A6E630);
    } else {
        func_8002F434(&this->actor, globalCtx, 0x1F, 10000.0f, 50.0f);
    }

    this->unk_2A8 |= 1;
}

void func_80A6E7BC(EnHs* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 4) && (func_80106BC8(globalCtx) != 0)) {
        switch (globalCtx->msgCtx.choiceIndex) {
            case 0:
                func_80A6E3A0(this, func_80A6E740);
                func_8002F434(&this->actor, globalCtx, 0x1F, 10000.0f, 50.0f);
                break;

            case 1:
                func_8010B720(globalCtx, 0x10B4);
                func_80A6E3A0(this, func_80A6E70C);
                break;
        }
        SkelAnime_ChangeAnim(&this->skelAnime, &D_060005C0, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_060005C0.genericHeader), 0, 8.0f);
    }

    this->unk_2A8 |= 1;
}

void func_80A6E8CC(EnHs* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((func_8010BDBC(&globalCtx->msgCtx) == 5) && (func_80106BC8(globalCtx) != 0)) {
        func_8010B720(globalCtx, 0x10B3);
        func_80A6E3A0(this, func_80A6E7BC);
        SkelAnime_ChangeAnim(&this->skelAnime, &D_06000528, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_06000528.genericHeader), 0, 8.0f);
    }

    if (this->unk_2AA > 0) {
        this->unk_2AA--;
        if (this->unk_2AA == 0) {
            func_8002F7DC(&player->actor, NA_SE_EV_CHICKEN_CRY_M);
        }
    }

    this->unk_2A8 |= 1;
}

void func_80A6E9AC(EnHs* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 tmp;

    if (func_8002F194(&this->actor, globalCtx) != 0) {
        if (func_8002F368(globalCtx) == 7) {
            player->actor.textId = 0x10B2;
            func_80A6E3A0(this, func_80A6E8CC);
            SkelAnime_ChangeAnim(&this->skelAnime, &D_06000304, 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_06000304.genericHeader), 0, 8.0f);
            this->unk_2AA = 0x28;
            func_80078884(0x4807);
        } else {
            player->actor.textId = 0x10B1;
            func_80A6E3A0(this, func_80A6E6D8);
        }
    } else {
        tmp = this->actor.yawTowardsLink - this->actor.shape.rot.y;
        this->actor.textId = 0x10B1;
        if ((ABS(tmp) < 0x2151) && (this->actor.xzDistFromLink < 100.0f)) {
            func_8002F298(&this->actor, globalCtx, 100.0f, 7);
        }
    }
}

void EnHs_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHs* this = THIS;
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

s32 func_80A6EC58(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnHs* this = THIS;

    switch (limbIndex) {
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

        case 12:
            if (this->actor.params == 1) {
                *dList = NULL;
                return 0;
            }
            break;

        case 13:
            if (this->actor.params == 1) {
                *dList = NULL;
                return 0;
            }
            break;
    }

    return 0;
}

void func_80A6ED14(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80A6EDFC = { 300.0f, 1000.0f, 0.0f };

    EnHs* this = THIS;

    if (limbIndex == 9) {
        Matrix_MultVec3f(&D_80A6EDFC, &this->actor.posRot2.pos);
    }
}

void EnHs_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHs* this = THIS;

    func_800943C8(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80A6EC58, func_80A6ED14, &this->actor);
}
