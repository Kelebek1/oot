/*
 * File: z_en_horse_link_child.c
 * Overlay: ovl_En_Horse_Link_Child
 * Description: Young Epona
 */

#include "z_en_horse_link_child.h"

#define FLAGS 0x02000010

#define THIS ((EnHorseLinkChild*)thisx)

void EnHorseLinkChild_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorseLinkChild_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorseLinkChild_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorseLinkChild_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A69EC0(EnHorseLinkChild* this);
void func_80A69B7C(EnHorseLinkChild* this);
void func_80A6A724(EnHorseLinkChild* this);
void func_80A6A4DC(EnHorseLinkChild* this);

void func_80A698F4(EnHorseLinkChild* this, GlobalContext* globalCtx);
void func_80A69C18(EnHorseLinkChild* this, GlobalContext* globalCtx);
void func_80A699FC(EnHorseLinkChild* this, GlobalContext* globalCtx);
void func_80A6A068(EnHorseLinkChild* this, GlobalContext* globalCtx);
void func_80A6A7D0(EnHorseLinkChild* this, GlobalContext* globalCtx);
void func_80A6A5A4(EnHorseLinkChild* this, GlobalContext* globalCtx);

extern SkeletonHeader D_06007B20;
extern AnimationHeader D_06002F98;

const ActorInit En_Horse_Link_Child_InitVars = {
    ACTOR_EN_HORSE_LINK_CHILD,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_HORSE_LINK_CHILD,
    sizeof(EnHorseLinkChild),
    (ActorFunc)EnHorseLinkChild_Init,
    (ActorFunc)EnHorseLinkChild_Destroy,
    (ActorFunc)EnHorseLinkChild_Update,
    (ActorFunc)EnHorseLinkChild_Draw,
};

static AnimationHeader* D_80A6AEE0[] = {
    0x060043E4, 0x06004B08, 0x060053F0, 0x0600360C, 0x06002F98,
};

static ColliderCylinderInit_Set3 sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 20, 100, 0, { 0, 0, 0 } },
};

static ColliderJntSphItemInit sJntSphItemsInit[1] = {
    {
        { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 13, { { 0, 0, 0 }, 10 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_UNK10, 0x00, 0x09, 0x39, 0x12, COLSHAPE_JNTSPH },
    1,
    sJntSphItemsInit,
};

static CollisionCheckInfoInit D_80A6AF54 = { 0xA, 0x0023, 0x0064, 0xFE };

static s32 D_80A6AF5C[] = { 0x00000001, 0x00000013 };

static f32 D_80A6AF64[] = { 1.0f, 1.0f, 1.5f, 1.5f, 1.5f };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_STOP),
};

void func_80A693D0(EnHorseLinkChild* this) {
    if ((D_80A6AF5C[this->unk_1F0] < this->skin.skelAnime.animCurrentFrame) &&
        ((this->unk_1F0 != 0) || !(D_80A6AF5C[1] < this->skin.skelAnime.animCurrentFrame))) {
        Audio_PlaySoundGeneral(NA_SE_EV_KID_HORSE_WALK, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        this->unk_1F0++;
        if (this->unk_1F0 >= 2) {
            this->unk_1F0 = 0;
        }
    }
}

void func_80A6948C(EnHorseLinkChild* this) {
    if (this->unk_150 == 2) {
        func_80A693D0(this);
        return;
    }

    if (this->skin.skelAnime.animCurrentFrame == 0.0f) {
        if ((this->unk_150 == 3) || (this->unk_150 == 4)) {
            Audio_PlaySoundGeneral(NA_SE_EV_KID_HORSE_RUN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                   &D_801333E8);
        } else if (this->unk_150 == 1) {
            if (Math_Rand_ZeroOne() > 0.5f) {
                Audio_PlaySoundGeneral(NA_SE_EV_KID_HORSE_GROAN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                       &D_801333E8);
            } else {
                Audio_PlaySoundGeneral(NA_SE_EV_KID_HORSE_NEIGH, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                       &D_801333E8);
            }
        }
    }
}

f32 func_80A695A4(EnHorseLinkChild* this) {
    f32 val;

    if (this->unk_150 == 2) {
        val = (D_80A6AF64[this->unk_150] * this->actor.speedXZ) * 0.5f;
    } else if (this->unk_150 == 3) {
        val = (D_80A6AF64[this->unk_150] * this->actor.speedXZ) * 0.33333334f;
    } else if (this->unk_150 == 4) {
        val = (D_80A6AF64[this->unk_150] * this->actor.speedXZ) * 0.2f;
    } else {
        val = D_80A6AF64[this->unk_150];
    }
    return val;
}

void EnHorseLinkChild_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHorseLinkChild* this = THIS;
    s32 pad[2];

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Actor_SetScale(&this->actor, 0.005f);
    this->actor.gravity = -3.5f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Squiggly, 20.0f);
    this->unk_14C = 1;
    this->actor.speedXZ = 0.0f;
    this->actor.posRot2.pos = this->actor.posRot.pos;
    this->actor.posRot2.pos.y += 70.0f;
    func_800A663C(globalCtx, &this->skin, &D_06007B20, &D_06002F98);
    this->unk_150 = 0;
    SkelAnime_ChangeAnimDefaultStop(&this->skin.skelAnime, D_80A6AEE0[0]);
    Collider_InitCylinder(globalCtx, &this->colliderCylinder);
    Collider_SetCylinder_Set3(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    Collider_InitJntSph(globalCtx, &this->colliderSphere);
    Collider_SetJntSph(globalCtx, &this->colliderSphere, &this->actor, &sJntSphInit, this->colliderSphereItems);
    func_80061ED4(&this->actor.colChkInfo, NULL, &D_80A6AF54);
    this->unk_1F0 = 0;
    this->unk_1EC = 0;

    if (gSaveContext.sceneSetupIndex >= 4) {
        func_80A69EC0(this);
    } else if (globalCtx->sceneNum == SCENE_SPOT20) {
        if (!Flags_GetEventChkInf(0x14)) {
            Actor_Kill(&this->actor);
            return;
        }
        this->unk_2A0 = gSaveContext.eventChkInf[1] & 0x40;
        func_80A69EC0(this);
    } else {
        func_80A69EC0(this);
    }

    this->actor.shape.rot.z = 0;
    this->actor.posRot.rot.z = this->actor.shape.rot.z;
    this->actor.initPosRot.rot.z = this->actor.shape.rot.z;
}

void EnHorseLinkChild_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHorseLinkChild* this = THIS;

    func_800A6888(globalCtx, &this->skin);
    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
    Collider_DestroyJntSph(globalCtx, &this->colliderSphere);
}

void func_80A6988C(EnHorseLinkChild* this) {
    this->unk_14C = 0;
    this->unk_150++;
    if (this->unk_150 >= 5) {
        this->unk_150 = 0;
    }
    SkelAnime_ChangeAnimDefaultStop(&this->skin.skelAnime, D_80A6AEE0[this->unk_150]);
    this->skin.skelAnime.animPlaybackSpeed = func_80A695A4(this);
}

void func_80A698F4(EnHorseLinkChild* this, GlobalContext* globalCtx) {
    this->actor.speedXZ = 0.0f;
    if (SkelAnime_FrameUpdateMatrix(&this->skin.skelAnime) != 0) {
        func_80A6988C(this);
    }
}

void func_80A6993C(EnHorseLinkChild* this, s32 arg1) {
    this->unk_14C = 2;
    this->actor.speedXZ = 0.0f;
    if ((arg1 != 0) && (arg1 != 1)) {
        arg1 = 0;
    }

    if (arg1 != this->unk_150) {
        this->unk_150 = arg1;
        SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                             SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, -5.0f);
    }
}

void func_80A699FC(EnHorseLinkChild* this, GlobalContext* globalCtx) {
    f32 sp44 = func_8002DB8C(&this->actor, &PLAYER->actor);
    s32 tmp;

    if (SkelAnime_FrameUpdateMatrix(&this->skin.skelAnime) != 0) {
        if ((sp44 < 1000.0f) && (sp44 > 70.0f)) {
            func_80A69B7C(this);
            return;
        }

        tmp = (this->unk_150 == 1) ? 0 : 1;
        if (tmp != this->unk_150) {
            this->unk_150 = tmp;
            SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, -5.0f);
        } else {
            SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, 0);
        }
    }
}

void func_80A69B7C(EnHorseLinkChild* this) {
    this->unk_14C = 1;
    this->unk_150 = 0;
    this->actor.speedXZ = 0.0f;
    SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                         SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, -5.0f);
}

void func_80A69C18(EnHorseLinkChild* this, GlobalContext* globalCtx) {
    s16 ret;
    f32 tmpf1;
    s32 tmp;

    if ((this->unk_150 == 4) || (this->unk_150 == 3) || (this->unk_150 == 2)) {
        ret = func_8002DA78(&this->actor, &PLAYER->actor) - this->actor.posRot.rot.y;
        if (ret >= 0x12D) {
            this->actor.posRot.rot.y += 0x12C;
        } else {
            if (ret < -0x12C) {
                this->actor.posRot.rot.y -= 0x12C;
            } else {
                this->actor.posRot.rot.y = this->actor.posRot.rot.y + ret;
            }
        }
        this->actor.shape.rot.y = this->actor.posRot.rot.y;
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skin.skelAnime) != 0) {
        tmpf1 = func_8002DB8C(&this->actor, &PLAYER->actor);
        if (tmpf1 > 1000.0f) {
            func_80A6993C(this, 0);
            return;
        }

        if ((tmpf1 < 1000.0f) && (tmpf1 >= 300.0f)) {
            this->actor.speedXZ = 6.0f;
            tmp = 4;
        } else if ((tmpf1 < 300.0f) && (tmpf1 >= 150.0f)) {
            this->actor.speedXZ = 4.0f;
            tmp = 3;
        } else if ((tmpf1 < 150.0f) && (tmpf1 >= 70.0f)) {
            tmp = 2;
            this->actor.speedXZ = 2.0f;
            this->unk_1F0 = 0;
        } else {
            func_80A6993C(this, 1);
            return;
        }

        if (tmp != this->unk_150) {
            this->unk_150 = tmp;
            SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, -5.0f);
        } else {
            SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, 0.0f);
        }
    }
}

void func_80A69EC0(EnHorseLinkChild* this) {
    this->unk_14C = 3;
    this->unk_150 = 0;
    this->actor.speedXZ = 0.0f;
    SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                         SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, -5.0f);
}

void func_80A69F5C(EnHorseLinkChild* this, GlobalContext* globalCtx) {
    if ((this->unk_150 == 4) || (this->unk_150 == 3) || (this->unk_150 == 2)) {
        Player* player = PLAYER;
        s16 tmp2;
        s32 pad;

        if (Math3D_Vec3f_DistXYZ(&player->actor.posRot.pos, &this->actor.initPosRot.pos) < 250.0f) {
            tmp2 = player->actor.shape.rot.y;
            tmp2 += (((func_8002DA78(&this->actor, &player->actor) > 0) ? 1 : -1) * 16384);
        } else {
            tmp2 = Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.initPosRot.pos) - this->actor.posRot.rot.y;
        }

        if (tmp2 >= 0x12D) {
            this->actor.posRot.rot.y += 0x12C;
        } else if (tmp2 < -0x12C) {
            this->actor.posRot.rot.y -= 0x12C;
        } else {
            this->actor.posRot.rot.y += tmp2;
        }
        this->actor.shape.rot.y = this->actor.posRot.rot.y;
    }
}

void func_80A6A068(EnHorseLinkChild* this, GlobalContext* globalCtx) {
    Player* player;
    f32 sp50;
    s32 ret;
    s32 tmp;
    f32 sp44;
    s32 pad;

    func_80A69F5C(this, globalCtx);
    player = PLAYER;
    sp50 = func_8002DB8C(&this->actor, &player->actor);
    if (gSaveContext.entranceIndex == 0x2AE) {
        Audio_PlaySoundGeneral(NA_SE_EV_KID_HORSE_NEIGH, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        func_80A6A724(this);
        return;
    }

    if (((gSaveContext.eventChkInf[1] & 0x40) && (DREG(53) != 0)) ||
        ((globalCtx->sceneNum == SCENE_SPOT20) && (gSaveContext.cutsceneIndex == 0xFFF1))) {
        func_80A6A4DC(this);
    } else {
        this->unk_2A0 = gSaveContext.eventChkInf[1] & 0x40;
    }

    tmp = this->unk_150;
    ret = SkelAnime_FrameUpdateMatrix(&this->skin.skelAnime);

    if ((ret != 0) || (this->unk_150 == 1) || (this->unk_150 == 0)) {
        if (gSaveContext.eventChkInf[1] & 0x20) {
            sp44 = Math3D_Vec3f_DistXYZ(&this->actor.posRot.pos, &this->actor.initPosRot.pos);
            if (Math3D_Vec3f_DistXYZ(&player->actor.posRot.pos, &this->actor.initPosRot.pos) > 250.0f) {
                if (sp44 >= 300.0f) {
                    tmp = 4;
                    this->actor.speedXZ = 6.0f;
                } else if ((sp44 < 300.0f) && (sp44 >= 150.0f)) {
                    tmp = 3;
                    this->actor.speedXZ = 4.0f;
                } else if ((sp44 < 150.0f) && (sp44 >= 70.0f)) {
                    tmp = 2;
                    this->actor.speedXZ = 2.0f;
                    this->unk_1F0 = 0;
                } else {
                    this->actor.speedXZ = 0.0f;
                    if (this->unk_150 == 0) {
                        if (ret == 1) {
                            tmp = 1;
                        } else {
                            tmp = 0;
                        }
                    } else if (ret == 1) {
                        tmp = 0;
                    } else {
                        tmp = 1;
                    }
                }
            } else if (sp50 < 200.0f) {
                tmp = 4;
                this->actor.speedXZ = 6.0f;
            } else if (sp50 < 300.0f) {
                tmp = 3;
                this->actor.speedXZ = 4.0f;
            } else if (sp50 < 400.0f) {
                tmp = 2;
                this->actor.speedXZ = 2.0f;
                this->unk_1F0 = 0;
            } else {
                this->actor.speedXZ = 0.0f;
                if (this->unk_150 == 0) {
                    if (ret == 1) {
                        tmp = 1;
                    } else {
                        tmp = 0;
                    }
                } else if (ret == 1) {
                    tmp = 0;
                } else {
                    tmp = 1;
                }
            }
        } else {
            this->actor.speedXZ = 0.0f;
            if (this->unk_150 == 0) {
                if (ret == 1) {
                    tmp = 1;
                } else {
                    tmp = 0;
                }
            } else {
                if (ret == 1) {
                    tmp = 0;
                } else {
                    tmp = 1;
                }
            }
        }
    }

    if ((tmp != this->unk_150) || (ret == 1)) {
        this->unk_150 = tmp;
        SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                             SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, -5.0f);
    } else {
        SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this),
                             this->skin.skelAnime.animCurrentFrame,
                             SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, 0.0f);
    }
}

void func_80A6A4DC(EnHorseLinkChild* this) {
    this->unk_14C = 5;
    if (Math_Rand_ZeroOne() > 0.5f) {
        this->unk_150 = 0;
    } else {
        this->unk_150 = 1;
    }

    DREG(53) = 0;
    SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                         SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, 0.0f);
}

void func_80A6A5A4(EnHorseLinkChild* this, GlobalContext* globalCtx) {
    s16 sp36;

    if (DREG(53) != 0) {
        DREG(53) = 0;
        Audio_PlaySoundGeneral(NA_SE_EV_KID_HORSE_NEIGH, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        func_80A6A724(this);
        return;
    }

    this->actor.speedXZ = 0.0f;
    sp36 = func_8002DA78(&this->actor, &PLAYER->actor) - this->actor.posRot.rot.y;
    if (Math_Coss(sp36) < 0.7071f) {
        if (this->unk_150 == 2) {
            func_8006DD9C(&this->actor, &PLAYER->actor.posRot.pos, 0x12C);
        }
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skin.skelAnime) != 0) {
        if (Math_Coss(sp36) < 0.0f) {
            this->unk_150 = 2;
            SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], D_80A6AF64[this->unk_150], 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A6AEE0[2]->genericHeader), 2, -5.0f);
        } else {
            func_80A6A4DC(this);
        }
    }
}

void func_80A6A724(EnHorseLinkChild* this) {
    this->unk_1E4 = 0;
    this->unk_14C = 4;
    this->unk_150 = 2;
    this->unk_1E8 = 0;
    this->actor.speedXZ = 2.0f;
    SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                         SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, -5.0f);
}

void func_80A6A7D0(EnHorseLinkChild* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    f32 tmpf1;
    s32 tmp;

    this->unk_1E4++;
    if (this->unk_1E4 >= 0x12D) {
        this->unk_1E8 = 1;
    }

    if ((this->unk_150 == 4) || (this->unk_150 == 3) || (this->unk_150 == 2)) {
        if (this->unk_1E8 == 0) {
            func_8006DD9C(&this->actor, &player->actor.posRot.pos, 0x12C);
        } else {
            func_8006DD9C(&this->actor, &this->actor.initPosRot.pos, 0x12C);
        }
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skin.skelAnime) != 0) {
        if (this->unk_1E8 == 0) {
            tmpf1 = func_8002DB8C(&this->actor, &PLAYER->actor);
        } else {
            tmpf1 = Math3D_Vec3f_DistXYZ(&this->actor.posRot.pos, &this->actor.initPosRot.pos);
        }

        if (this->unk_1E8 == 0) {
            if (tmpf1 >= 300.0f) {
                this->actor.speedXZ = 6.0f;
                tmp = 4;
            } else if (tmpf1 >= 150.0f) {
                this->actor.speedXZ = 4.0f;
                tmp = 3;
            } else {
                tmp = 2;
                this->actor.speedXZ = 2.0f;
                this->unk_1F0 = 0;
            }
        } else if (tmpf1 >= 300.0f) {
            this->actor.speedXZ = 6.0f;
            tmp = 4;
        } else if (tmpf1 >= 150.0f) {
            this->actor.speedXZ = 4.0f;
            tmp = 3;
        } else {
            if (tmpf1 >= 70.0f) {
                tmp = 2;
                this->actor.speedXZ = 2.0f;
                this->unk_1F0 = 0;
            } else {
                func_80A6A4DC(this);
                return;
            }
        }

        if (tmp != this->unk_150) {
            this->unk_150 = tmp;
            SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, -5.0f);
        } else {
            SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6AEE0[this->unk_150], func_80A695A4(this), 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A6AEE0[this->unk_150]->genericHeader), 2, 0.0f);
        }
    }
}

void EnHorseLinkChild_Update(Actor* thisx, GlobalContext* globalCtx) {
    static EnHorseLinkChildActionFunc D_80A6AF7C[] = {
        func_80A698F4, func_80A69C18, func_80A699FC, func_80A6A068, func_80A6A7D0, func_80A6A5A4,
    };

    EnHorseLinkChild* this = THIS;
    s32 pad;

    D_80A6AF7C[this->unk_14C](this, globalCtx);
    Actor_MoveForward(&this->actor);
    func_8002E4B4(globalCtx, &this->actor, 20.0f, 55.0f, 100.0f, 0x1D);
    if (globalCtx->sceneNum == 0x63) {
        if (this->actor.posRot.pos.z < -2400.0f) {
            this->actor.posRot.pos.z = -2400.0f;
        }
    }

    this->actor.posRot2.pos = this->actor.posRot.pos;
    this->actor.posRot2.pos.y = this->actor.posRot2.pos.y + 70.0f;
    if ((Math_Rand_ZeroOne() < 0.025f) && (this->unk_1EC == 0)) {
        this->unk_1EC++;
    } else if (this->unk_1EC > 0) {
        this->unk_1EC++;
        if (this->unk_1EC >= 4) {
            this->unk_1EC = 0;
        }
    }

    Collider_CylinderUpdate(&this->actor, &this->colliderCylinder);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    func_80A6948C(this);
}

void func_80A6ABF8(Actor* thisx, GlobalContext* globalCtx, ColliderJntSphItem* colliderSphereItem) {
    Vec3f sp4C;
    Vec3f sp40;
    s32 i;
    EnHorseLinkChild* this = THIS;

    for (i = 0; i < this->colliderSphere.count; i++) {
        sp4C.x = this->colliderSphere.list[i].dim.modelSphere.center.x;
        sp4C.y = this->colliderSphere.list[i].dim.modelSphere.center.y;
        sp4C.z = this->colliderSphere.list[i].dim.modelSphere.center.z;
        func_800A6408(colliderSphereItem, this->colliderSphere.list[i].dim.joint, &sp4C, &sp40);
        this->colliderSphere.list[i].dim.worldSphere.center.x = sp40.x;
        this->colliderSphere.list[i].dim.worldSphere.center.y = sp40.y;
        this->colliderSphere.list[i].dim.worldSphere.center.z = sp40.z;
        this->colliderSphere.list[i].dim.worldSphere.radius =
            this->colliderSphere.list[i].dim.modelSphere.radius * this->colliderSphere.list[i].dim.scale;
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere.base);
}

s32 func_80A6AD84(Actor* thisx, GlobalContext* globalCtx, s32 arg2, s32 arg3) {
    static UNK_TYPE D_80A6AF94[] = { 0x06001D28, 0x06001928, 0x06001B28 };
    static u8 D_80A6AFA0[] = { 0x00, 0x01, 0x02, 0x01 };

    EnHorseLinkChild* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_horse_link_child.c", 1467);

    if (arg2 == 13) {
        u8 idx = D_80A6AFA0[this->unk_1EC];

        gSPSegment(oGfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A6AF94[idx]));
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_horse_link_child.c", 1479);
    return 1;
}

void EnHorseLinkChild_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHorseLinkChild* this = THIS;

    func_80093D18(globalCtx->state.gfxCtx);
    func_800A6360(&this->actor, globalCtx, &this->skin, func_80A6ABF8, func_80A6AD84, 1);
}
