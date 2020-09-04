/*
 * File: z_en_mk.c
 * Overlay: ovl_En_Mk
 * Description: Lakeside Professor
 */

#include "z_en_mk.h"

#define FLAGS 0x00000019

#define THIS ((EnMk*)thisx)

void EnMk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMk_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AAD080(EnMk* this, GlobalContext* globalCtx);

extern SkeletonHeader D_06005DF0;
extern AnimationHeader D_06000D88;
extern AnimationHeader D_06000368;
extern AnimationHeader D_06000AC0;
extern AnimationHeader D_06000724;

const ActorInit En_Mk_InitVars = {
    ACTOR_EN_MK,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_MK,
    sizeof(EnMk),
    (ActorFunc)EnMk_Init,
    (ActorFunc)EnMk_Destroy,
    (ActorFunc)EnMk_Update,
    (ActorFunc)EnMk_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x11, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x01, 0x01 },
    { 30, 40, 0, { 0, 0, 0 } },
};

void EnMk_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMk* this = THIS;
    s32 pad;

    this->actor.minVelocityY = -4.0f;
    this->actor.gravity = -1.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 36.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06005DF0, &D_06000D88, this->limbDrawTable,
                     this->transitionDrawTable, 13);
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06000D88);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = 0xFF;
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80AAD080;
    this->unk_27E = 0;
    this->unk_280 = 0;
    this->actor.unk_1F = 6;

    if (gSaveContext.itemGetInf[1] & 1) {
        this->unk_27E |= 4;
    }
}

void EnMk_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMk* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80AACA40(EnMk* this, GlobalContext* globalCtx) {
    if (func_8002F334(&this->actor, globalCtx) != 0) {
        this->actor.flags &= ~0x10000;
        this->actionFunc = func_80AAD080;
    }
    this->unk_27E |= 1;
}

void func_80AACA94(EnMk* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80AACA40;
        func_80088AA0(0xF0);
        gSaveContext.eventInf[1] &= ~1;
    } else {
        func_8002F434(&this->actor, globalCtx, 0x25, 10000.0f, 50.0f);
    }
}

void func_80AACB14(EnMk* this, GlobalContext* globalCtx) {
    if (func_8002F334(&this->actor, globalCtx) != 0) {
        this->actionFunc = func_80AACA94;
        func_8002F434(&this->actor, globalCtx, 0x25, 10000.0f, 50.0f);
    }
}

void func_80AACB6C(EnMk* this, GlobalContext* globalCtx) {
    if (func_8002F194(&this->actor, globalCtx) != 0) {
        this->actionFunc = func_80AACB14;
    }
    this->unk_27E |= 1;
}

void func_80AACBAC(EnMk* this, GlobalContext* globalCtx) {
    if (this->unk_282 > 0) {
        this->unk_282--;
        this->actor.shape.rot.y -= 0x800;
    } else {
        this->actionFunc = func_80AACB6C;
        func_8010B720(globalCtx, 0x4030);
    }
}

void func_80AACC04(EnMk* this, GlobalContext* globalCtx) {
    if (this->unk_282 > 0) {
        this->unk_282--;
    } else {
        this->unk_282 = 0x10;
        this->actionFunc = func_80AACBAC;
        SkelAnime_ChangeAnim(&this->skelAnime, &D_06000D88, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_06000D88.genericHeader), 0, -4.0f);
        this->unk_27E &= ~2;
    }
}

void func_80AACCA0(EnMk* this, GlobalContext* globalCtx) {
    if (this->unk_282 > 0) {
        this->unk_282--;
        this->actor.shape.rot.y += 0x800;
    } else {
        this->unk_282 = 0x78;
        this->actionFunc = func_80AACC04;
        SkelAnime_ChangeAnim(&this->skelAnime, &D_06000724, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_06000724.genericHeader), 0, -4.0f);
        this->unk_27E &= ~2;
    }
}

void func_80AACD48(EnMk* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (func_8010BDBC(&globalCtx->msgCtx) == 5) {
        if (func_80106BC8(globalCtx) != 0) {
            func_80106CCC(globalCtx);
            this->actionFunc = func_80AACCA0;
            globalCtx->msgCtx.msgMode = 0x37;
            player->exchangeItemId = 0;
            this->unk_282 = 0x10;
            SkelAnime_ChangeAnim(&this->skelAnime, &D_06000D88, 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_06000D88.genericHeader), 0, -4.0f);
            this->unk_27E &= ~2;
        }
    }
    this->unk_27E |= 1;
}

void func_80AACE2C(EnMk* this, GlobalContext* globalCtx) {
    if (func_8010BDBC(&globalCtx->msgCtx) == 5) {
        if (func_80106BC8(globalCtx) != 0) {
            func_8010B720(globalCtx, 0x4001);
            SkelAnime_ChangeAnim(&this->skelAnime, &D_06000AC0, 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_06000AC0.genericHeader), 2, -4.0f);
            this->unk_27E &= ~2;
            this->actionFunc = func_80AACD48;
        }
    }
    this->unk_27E |= 1;
}

void func_80AACEE8(EnMk* this, GlobalContext* globalCtx) {
    if (func_8010BDBC(&globalCtx->msgCtx) == 5) {
        if (func_80106BC8(globalCtx) != 0) {
            func_8010B720(globalCtx, 0x4000);
            SkelAnime_ChangeAnim(&this->skelAnime, &D_06000AC0, 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_06000AC0.genericHeader), 0, -4.0f);
            this->unk_27E &= ~2;
            this->actionFunc = func_80AACE2C;
        }
    }
    this->unk_27E |= 1;
}

void func_80AACFA0(EnMk* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80AACA40;
        gSaveContext.itemGetInf[1] |= 1;
    } else {
        func_8002F434(&this->actor, globalCtx, 0x3E, 10000.0f, 50.0f);
    }
}

void func_80AAD014(EnMk* this, GlobalContext* globalCtx) {
    if (func_8002F334(&this->actor, globalCtx) != 0) {
        this->actionFunc = func_80AACFA0;
        func_8002F434(&this->actor, globalCtx, 0x3E, 10000.0f, 50.0f);
    }
    this->unk_27E |= 1;
}

void func_80AAD080(EnMk* this, GlobalContext* globalCtx) {
    s32 pad2[2];
    Player* player = PLAYER;
    s16 tmp;
    s32 ret;

    if (func_8002F194(&this->actor, globalCtx) != 0) {
        ret = func_8002F368(globalCtx);
        if (this->actor.textId != 0x4018) {
            player->actor.textId = this->actor.textId;
            this->actionFunc = func_80AACA40;
        } else if (INV_CONTENT(ITEM_ODD_MUSHROOM) == ITEM_EYEDROPS) {
            player->actor.textId = 0x4032;
            this->actionFunc = func_80AACA40;
        } else {
            switch (ret) {
                case 0:
                    if (this->unk_280 >= 8) {
                        if (gSaveContext.itemGetInf[1] & 1) {
                            player->actor.textId = 0x4075;
                            this->actionFunc = func_80AACA40;
                        } else {
                            player->actor.textId = 0x4074;
                            this->actionFunc = func_80AAD014;
                            this->unk_280 = 0;
                        }
                    } else if (this->unk_280 == 0) {
                        player->actor.textId = 0x4018;
                        this->actionFunc = func_80AACA40;
                    } else {
                        player->actor.textId = this->unk_280 + 0x406C;
                        this->actionFunc = func_80AACA40;
                    }
                    break;

                case 13:
                    player->actor.textId = 0x4019;
                    this->actionFunc = func_80AACEE8;
                    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000368, 1.0f, 0.0f,
                                         SkelAnime_GetFrameCount(&D_06000368.genericHeader), 2, -4.0f);
                    this->unk_27E &= ~2;
                    gSaveContext.timer2State = 0;
                    func_80078884(NA_SE_SY_TRE_BOX_APPEAR);
                    break;

                default:
                    player->actor.textId = 0x4018;
                    this->actionFunc = func_80AACA40;
                    break;
            }
        }
    } else {
        this->actor.textId = Text_GetFaceReaction(globalCtx, 0x1A);
        if (this->actor.textId == 0) {
            this->actor.textId = 0x4018;
        }

        tmp = this->actor.yawTowardsLink - this->actor.shape.rot.y;
        if ((ABS(tmp) < 0x2151) && (this->actor.xzDistFromLink < 100.0f)) {
            func_8002F298(&this->actor, globalCtx, 100.0f, 0xD);
            this->unk_27E |= 1;
        }
    }
}

void EnMk_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMk* this = THIS;
    Player* player;
    Vec3s sp40;
    s32 pad;

    Collider_CylinderUpdate(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_MoveForward(&this->actor);
    func_8002E4B4(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    if (!(this->unk_27E & 2)) {
        if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
            this->unk_27E |= 2;
        }
    }

    this->actionFunc(this, globalCtx);

    if (this->unk_27E & 1) {
        func_80038290(globalCtx, &this->actor, &this->unk_278, &sp40, this->actor.posRot2.pos);
    } else {
        Math_SmoothScaleMaxMinS(&this->unk_278.x, 0, 6, 0x1838, 0x64);
        Math_SmoothScaleMaxMinS(&this->unk_278.y, 0, 6, 0x1838, 0x64);
    }

    player = PLAYER;
    if (this->unk_27E & 8) {
        if (!(player->stateFlags2 & 0x400)) {
            this->unk_27E &= ~8;
        }
    } else {
        if (player->currentBoots == 1) {
            this->unk_27E |= 8;
            return;
        }

        if (player->stateFlags2 & 0x400) {
            s16 tmp = player->actor.waterY;

            if (tmp > 0) {
                if (tmp >= 0x140) {
                    if (tmp >= 0x163) {
                        tmp = 8;
                    } else {
                        tmp = 7;
                    }
                } else if (tmp < 0x50) {
                    tmp = 1;
                } else {
                    tmp *= 0.025f;
                }

                if (this->unk_280 < tmp) {
                    this->unk_280 = tmp;
                    if (!(this->unk_27E & 4) && (this->unk_280 >= 8)) {
                        this->unk_27E |= 4;
                        func_80078884(NA_SE_SY_CORRECT_CHIME);
                    }
                }
            }
        }
    }
}

s32 EnMk_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnMk* this = THIS;

    if (limbIndex == 11) {
        rot->y -= this->unk_278.y;
        rot->z += this->unk_278.x;
    }
    return 0;
}

void EnMk_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80AAD64C = { 1000.0f, -100.0f, 0.0f };

    EnMk* this = THIS;

    if (limbIndex == 11) {
        Matrix_MultVec3f(&D_80AAD64C, &this->actor.posRot2.pos);
    }
}

void EnMk_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMk* this = THIS;

    func_800943C8(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnMk_OverrideLimbDraw, EnMk_PostLimbDraw, &this->actor);
}
