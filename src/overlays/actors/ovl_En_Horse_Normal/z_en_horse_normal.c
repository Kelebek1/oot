/*
 * File: z_en_horse_normal.c
 * Overlay: ovl_En_Horse_Normal
 * Description: Horse
 */

#include "z_en_horse_normal.h"

#define FLAGS 0x00000000

#define THIS ((EnHorseNormal*)thisx)

void EnHorseNormal_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorseNormal_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorseNormal_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorseNormal_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A6C6B0(EnHorseNormal* this);
void func_80A6C4CC(EnHorseNormal* this);
void func_80A6BC48(EnHorseNormal* this);
void func_80A6BCEC(EnHorseNormal* this);

void func_80A6B91C(EnHorseNormal* this, GlobalContext* globalCtx);
void func_80A6BC00(EnHorseNormal* this, GlobalContext* globalCtx);
void func_80A6BE6C(EnHorseNormal* this, GlobalContext* globalCtx);
void func_80A6C570(EnHorseNormal* this, GlobalContext* globalCtx);
void func_80A6C760(EnHorseNormal* this, GlobalContext* globalCtx);
void func_80A6B9D0(EnHorseNormal* this, GlobalContext* globalCtx);

extern SkeletonHeader D_06009FAC;
extern AnimationHeader D_06004580;
extern Gfx Horse_Normal_D_04049AD0[];

const ActorInit En_Horse_Normal_InitVars = {
    ACTOR_EN_HORSE_NORMAL,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_HORSE_NORMAL,
    sizeof(EnHorseNormal),
    (ActorFunc)EnHorseNormal_Init,
    (ActorFunc)EnHorseNormal_Destroy,
    (ActorFunc)EnHorseNormal_Update,
    (ActorFunc)EnHorseNormal_Draw,
};

static AnimationHeader* D_80A6D370[] = {
    0x06004580, 0x06004C20, 0x060035D4, 0x06002458, 0x060054BC, 0x06001A1C, 0x06000608, 0x06000C20, 0x060013A8,
};

static ColliderCylinderInit sCylinderInit1 = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 40, 100, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit3 = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 60, 100, 0, { 0, 0, 0 } },
};

static ColliderJntSphItemInit sJntSphItemsInit[1] = {
    {
        { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 11, { { 0, 0, 0 }, 20 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x10, COLSHAPE_JNTSPH },
    1,
    sJntSphItemsInit,
};

static CollisionCheckInfoInit D_80A6D420 = { 0x0A, 0x0023, 0x0064, 0xFE };

// These unreferenced. Second part a struct referencing the first.
// Word 0 being data count, word 1 being the address
// See ovl_En_Horse, same struct used there
static s32 UNUSED_D_80A6D428[] = {
    0x04220001, 0x01800700, 0x06750027, 0xFE830600, 0x06460001, 0xFBE80600, 0x041D0001, 0xF9AC0600,
    0xFC0C0001, 0xF99F0700, 0xF9890001, 0xFC6A0600, 0xF9CE0001, 0xFF7A0600, 0xFC3F0001, 0x01930700,
};
static s32 UNUSED_D_80A6D468[] = { 0x00000008, UNUSED_D_80A6D428 };

static s32 UNUSED_D_80A6D470[] = {
    0x00580000, 0x081E0A00, 0x09B20178, 0x12170700, 0x08B4FFE4, 0x19CD0C00, 0x028EFF9C, 0x22A00700, 0xFED7FE0C,
    0x29AB0C00, 0xEB49FE5C, 0x29900A00, 0xE5E2FE0C, 0x1E500A00, 0xEB740064, 0x15230700, 0xF20BFEF3, 0x0F350A00,

};
static s32 UNUSED_D_80A6D4B8[] = { 0x00000009, UNUSED_D_80A6D470 };

static s32 D_80A6D4C0[] = {
    0x00000000,
    0x00000010,
};
static f32 D_80A6D4C8[] = {
    1.0f, 1.0f, 1.0f, 1.0f, 1.5f, 1.5f, 1.5f, 1.5f, 1.0f,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

void func_80A6B250(EnHorseNormal* this) {
    f32 frame = this->skin.skelAnime.animCurrentFrame;

    if (D_80A6D4C0[this->unk_200] < frame) {
        if ((this->unk_200 != 0) || !(D_80A6D4C0[1] < frame)) {
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_WALK, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                   &D_801333E8);
            this->unk_200++;
            if (this->unk_200 >= 2) {
                this->unk_200 = 0;
            }
        }
    }
}

f32 func_80A6B30C(EnHorseNormal* this) {
    f32 ret;

    if (this->unk_150 == 4) {
        ret = (D_80A6D4C8[this->unk_150] * this->actor.speedXZ) * 0.5f;
    } else if (this->unk_150 == 5) {
        ret = (D_80A6D4C8[this->unk_150] * this->actor.speedXZ) * 0.33333334f;
    } else if (this->unk_150 == 6) {
        ret = (D_80A6D4C8[this->unk_150] * this->actor.speedXZ) * 0.2f;
    } else {
        ret = D_80A6D4C8[this->unk_150];
    }

    return ret;
}

void EnHorseNormal_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHorseNormal* this = THIS;
    s32 pad[2];

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.gravity = -3.5f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Squiggly, 20.0f);
    this->unk_14C = 0;
    this->unk_150 = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.posRot2.pos = this->actor.posRot.pos;
    this->actor.posRot2.pos.y += 70.0f;

    Collider_InitCylinder(globalCtx, &this->collider1);
    Collider_SetCylinder(globalCtx, &this->collider1, &this->actor, &sCylinderInit1);
    Collider_InitJntSph(globalCtx, &this->colliderSphere);
    Collider_SetJntSph(globalCtx, &this->colliderSphere, &this->actor, &sJntSphInit, this->colliderSphereItems);
    Collider_InitCylinder(globalCtx, &this->collider3);
    Collider_SetCylinder(globalCtx, &this->collider3, &this->actor, &sCylinderInit3);
    func_80061ED4(&this->actor.colChkInfo, NULL, &D_80A6D420);

    if (globalCtx->sceneNum == SCENE_SPOT20) {
        if ((this->actor.posRot.rot.z == 0) || (gSaveContext.nightFlag != 0)) {
            Actor_Kill(&this->actor);
            return;
        }

        if (LINK_IS_CHILD) {
            if (Flags_GetEventChkInf(0x14) != 0) {
                if (this->actor.posRot.rot.z != 3) {
                    Actor_Kill(&this->actor);
                    return;
                }
            } else if (this->actor.posRot.rot.z != 1) {
                Actor_Kill(&this->actor);
                return;
            }
        } else if ((Flags_GetEventChkInf(0x18) != 0) || (DREG(1) != 0)) {
            if (this->actor.posRot.rot.z != 7) {
                Actor_Kill(&this->actor);
                return;
            }
        } else if (this->actor.posRot.rot.z != 5) {
            Actor_Kill(&this->actor);
            return;
        }

        this->actor.shape.rot.z = 0;
        this->actor.posRot.rot.z = this->actor.shape.rot.z;
        this->actor.initPosRot.rot.z = this->actor.shape.rot.z;
        func_800A663C(globalCtx, &this->skin, &D_06009FAC, &D_06004580);
        SkelAnime_ChangeAnimDefaultStop(&this->skin.skelAnime, D_80A6D370[this->unk_150]);
        if (((-730.0f == this->actor.posRot.pos.x) && (0.0f == this->actor.posRot.pos.y) &&
             (-1100.0f == this->actor.posRot.pos.z)) ||
            ((880.0f == this->actor.posRot.pos.x) && (0.0f == this->actor.posRot.pos.y) &&
             (-1170.0f == this->actor.posRot.pos.z))) {
            func_80A6C6B0(this);
            return;
        }
    } else if (globalCtx->sceneNum == SCENE_MALON_STABLE) {
        if (gSaveContext.nightFlag == 0) {
            Actor_Kill(&this->actor);
        } else {
            func_800A663C(globalCtx, &this->skin, &D_06009FAC, &D_06004580);
            SkelAnime_ChangeAnimDefaultStop(&this->skin.skelAnime, D_80A6D370[this->unk_150]);
            func_80A6C6B0(this);
        }
        return;
    } else if (globalCtx->sceneNum == SCENE_SPOT12) {
        if ((3707.0f == this->actor.posRot.pos.x) && (1413.0f == this->actor.posRot.pos.y) &&
            (-665.0f == this->actor.posRot.pos.z)) {
            func_800A663C(globalCtx, &this->skin, &D_06009FAC, &D_06004580);
            SkelAnime_ChangeAnimDefaultStop(&this->skin.skelAnime, D_80A6D370[this->unk_150]);
            func_80A6C4CC(this);
            return;
        } else {
            func_800A663C(globalCtx, &this->skin, &D_06009FAC, &D_06004580);
            SkelAnime_ChangeAnimDefaultStop(&this->skin.skelAnime, D_80A6D370[this->unk_150]);
        }
    } else {
        func_800A663C(globalCtx, &this->skin, &D_06009FAC, &D_06004580);
        SkelAnime_ChangeAnimDefaultStop(&this->skin.skelAnime, D_80A6D370[this->unk_150]);
    }

    if (((this->actor.params & 0xF0) == 0x10) && ((this->actor.params & 0xF) != 0xF)) {
        func_80A6B91C(this, globalCtx);
    } else {
        func_80A6BC48(this);
    }
}

void EnHorseNormal_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHorseNormal* this = THIS;

    func_800A6888(globalCtx, &this->skin);
    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider3);
    Collider_DestroyJntSph(globalCtx, &this->colliderSphere);
}

void func_80A6B91C(EnHorseNormal* this, GlobalContext* globalCtx) {
    this->actor.flags |= 0x10;
    this->unk_14C = 4;
    this->unk_150 = 6;
    this->unk_324 = 0;
    this->actor.speedXZ = 7.0f;
    SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6D370[this->unk_150], func_80A6B30C(this), 0.0f,
                         SkelAnime_GetFrameCount(&D_80A6D370[this->unk_150]->genericHeader), 2, 0.0f);
}

void func_80A6B9D0(EnHorseNormal* this, GlobalContext* globalCtx) {
    Path* path = &globalCtx->setupPathList[this->actor.params & 0xF];
    Vec3s* pos = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points);
    f32 sp44;
    f32 sp40;
    s32 pad;

    pos += this->unk_324;

    sp44 = pos->x - this->actor.posRot.pos.x;
    sp40 = pos->z - this->actor.posRot.pos.z;
    Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, Math_atan2f(sp44, sp40) * 10430.378f, 0xA, 0x7D0, 1);
    this->actor.shape.rot.y = this->actor.posRot.rot.y;
    if ((SQ(sp44) + SQ(sp40)) < 600.0f) {
        this->unk_324++;
        if (this->unk_324 >= path->count) {
            this->unk_324 = 0;
        }
    }

    this->skin.skelAnime.animPlaybackSpeed = func_80A6B30C(this);
    if (SkelAnime_FrameUpdateMatrix(&this->skin.skelAnime) != 0) {
        SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6D370[this->unk_150], func_80A6B30C(this), 0.0f,
                             SkelAnime_GetFrameCount(&D_80A6D370[this->unk_150]->genericHeader), 2, 0.0f);
        func_80A6BCEC(this);
    }
}

void func_80A6BBAC(EnHorseNormal* this) {
    this->unk_14C = 0;
    this->unk_150++;
    if (this->unk_150 >= 9) {
        this->unk_150 = 0;
    }
    SkelAnime_ChangeAnimDefaultStop(&this->skin.skelAnime, D_80A6D370[this->unk_150]);
}

void func_80A6BC00(EnHorseNormal* this, GlobalContext* globalCtx) {
    this->actor.speedXZ = 0.0f;
    if (SkelAnime_FrameUpdateMatrix(&this->skin.skelAnime) != 0) {
        func_80A6BBAC(this);
    }
}

void func_80A6BC48(EnHorseNormal* this) {
    this->unk_14C = 1;
    this->unk_150 = 0;
    this->unk_21C = 0;
    this->unk_21E = 0;
    this->actor.speedXZ = 0.0f;
    this->unk_218 = 0.0f;
    SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6D370[this->unk_150], func_80A6B30C(this), 0.0f,
                         SkelAnime_GetFrameCount(&D_80A6D370[this->unk_150]->genericHeader), 2, 0.0f);
}

void func_80A6BCEC(EnHorseNormal* this) {
    if (this->unk_150 == 5) {
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_RUN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    } else if (this->unk_150 == 6) {
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_RUN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    }
}

void func_80A6BD7C(EnHorseNormal* this) {
    f32 frame = this->skin.skelAnime.animCurrentFrame;

    if ((this->unk_150 == 0) && (frame > 28.0f) && ((this->unk_1E4 & 1) == 0)) {
        this->unk_1E4 |= 1;
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_SANDDUST, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
    } else if ((this->unk_150 == 3) && (frame > 25.0f) && ((this->unk_1E4 & 2) == 0)) {
        this->unk_1E4 |= 2;
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_LAND2, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
    }
}

void func_80A6BE6C(EnHorseNormal* this, GlobalContext* globalCtx) {
    static s32 D_80A6D4F4[] = { 0x00000000, 0x00000001, 0x00000004, 0x00000005, 0x00000006, 0x00000002, 0x00000003 };

    static s32 D_80A6D510[] = {
        0x00000000, 0x00000000, 0x00000002, 0x00000002, 0x00000001, 0x00000001, 0x00000001, 0x00000003, 0x00000003,
    };

    s32 sp4C = this->unk_150;
    f32 rand;

    switch (D_80A6D510[this->unk_150]) {
        case 0:
            sp4C = this->unk_150;
            func_80A6BD7C(this);
            this->actor.speedXZ = 0.0f;
            this->unk_218 = 0.0f;
            break;

        case 1:
            if (Math_Rand_ZeroOne() < 0.1f) {
                rand = Math_Rand_ZeroOne();
                this->unk_218 = (rand + rand) - 1.0f;
            }

            this->actor.speedXZ += this->unk_218;
            if (this->actor.speedXZ <= 0.0f) {
                this->actor.speedXZ = 0.0f;
                this->unk_218 = 0.0f;
                sp4C = 0;
            } else if (this->actor.speedXZ < 3.0f) {
                func_80A6B250(this);
                sp4C = 4;
            } else if (this->actor.speedXZ < 6.0f) {
                sp4C = 5;
            } else if (this->actor.speedXZ < 8.0f) {
                sp4C = 6;
            } else {
                this->actor.speedXZ = 8.0f;
                sp4C = 6;
            }

            if ((Math_Rand_ZeroOne() < 0.1f) ||
                ((this->unk_21E == 0) && ((this->actor.bgCheckFlags & 8) || (this->collider1.base.maskA & 2) ||
                                          (this->colliderSphere.base.maskA & 2)))) {
                this->unk_21E += (Math_Rand_ZeroOne() * 30.0f) - 15.0f;
                if (this->unk_21E >= 0x33) {
                    this->unk_21E = 0x32;
                } else if (this->unk_21E < -0x32) {
                    this->unk_21E = -0x32;
                }
            }

            this->unk_21C += this->unk_21E;
            if (this->unk_21C < -0x12C) {
                this->unk_21C = -0x12C;
            } else if (this->unk_21C >= 0x12D) {
                this->unk_21C = 0x12C;
            } else if ((Math_Rand_ZeroOne() < 0.25f) && (fabsf(this->unk_21C) < 100.0f)) {
                this->unk_21C = 0;
                this->unk_21E = 0;
            }
            this->actor.posRot.rot.y += this->unk_21C;
            this->actor.shape.rot.y = this->actor.posRot.rot.y;
            break;

        case 2:
        case 3:
            break;
    }

    if ((this->unk_150 != sp4C) || (SkelAnime_FrameUpdateMatrix(&this->skin.skelAnime) != 0)) {
        if (sp4C != this->unk_150) {
            this->unk_150 = sp4C;
            this->unk_1E4 &= ~1;
            this->unk_1E4 &= ~2;
            if (sp4C == 1) {
                Audio_PlaySoundGeneral(NA_SE_EV_HORSE_GROAN, &this->unk_204, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            } else if (sp4C == 3) {
                Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_204, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            } else {
                func_80A6BCEC(this);
            }
            SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6D370[this->unk_150], func_80A6B30C(this), 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A6D370[this->unk_150]->genericHeader), 2, -3.0f);
            return;
        }

        switch (D_80A6D510[this->unk_150]) {
            case 0:
                if (Math_Rand_ZeroOne() < 0.25f) {
                    this->unk_218 = 1.0f;
                    sp4C = 4;
                } else {
                    sp4C = D_80A6D4F4[(s32)(Math_Rand_ZeroOne() * 2)];
                    this->actor.speedXZ = 0.0f;
                    this->unk_218 = 0.0f;
                }
                break;

            case 1:
            case 2:
            case 3:
                break;
        }

        this->unk_1E4 &= ~1;
        this->unk_1E4 &= ~2;
        if (sp4C == 1) {
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_GROAN, &this->unk_204, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        } else if (sp4C == 3) {
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_204, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        } else {
            func_80A6BCEC(this);
        }

        if (sp4C != this->unk_150) {
            this->unk_150 = sp4C;
            SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6D370[this->unk_150], func_80A6B30C(this), 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A6D370[this->unk_150]->genericHeader), 2, -3.0f);
        } else {
            SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6D370[this->unk_150], func_80A6B30C(this), 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A6D370[this->unk_150]->genericHeader), 2, 0.0f);
        }
    }
}

void func_80A6C4CC(EnHorseNormal* this) {
    this->unk_14C = 2;
    this->unk_150 = 0;
    this->unk_21C = 0;
    this->unk_21E = 0;
    this->actor.speedXZ = 0.0f;
    this->unk_218 = 0.0f;
    SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6D370[this->unk_150], func_80A6B30C(this), 0.0f,
                         SkelAnime_GetFrameCount(&D_80A6D370[this->unk_150]->genericHeader), 2, 0.0f);
}

void func_80A6C570(EnHorseNormal* this, GlobalContext* globalCtx) {
    f32 rand;

    if (SkelAnime_FrameUpdateMatrix(&this->skin.skelAnime) != 0) {
        rand = Math_Rand_ZeroOne();
        if (rand < 0.4f) {
            this->unk_150 = 0;
        } else if (rand < 0.8f) {
            this->unk_150 = 1;
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_GROAN, &this->unk_204, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        } else {
            this->unk_150 = 3;
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_204, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        }

        SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6D370[this->unk_150], func_80A6B30C(this), 0.0f,
                             SkelAnime_GetFrameCount(&D_80A6D370[this->unk_150]->genericHeader), 2, 0.0f);
    }
}

void func_80A6C6B0(EnHorseNormal* this) {
    this->unk_14C = 3;
    this->unk_150 = 0;
    this->unk_21C = 0;
    this->unk_21E = 0;
    this->actor.flags |= 0x30;
    this->actor.speedXZ = 0.0f;
    this->unk_218 = 0.0f;
    SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6D370[this->unk_150], func_80A6B30C(this), 0.0f,
                         SkelAnime_GetFrameCount(&D_80A6D370[this->unk_150]->genericHeader), 2, 0.0f);
}

void func_80A6C760(EnHorseNormal* this, GlobalContext* globalCtx) {
    f32 rand;

    func_80A6BD7C(this);
    if (SkelAnime_FrameUpdateMatrix(&this->skin.skelAnime) != 0) {
        rand = Math_Rand_ZeroOne();
        if (rand < 0.4f) {
            this->unk_150 = 0;
        } else if (rand < 0.8f) {
            this->unk_150 = 1;
            this->unk_1E4 |= 0x20;
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_GROAN, &this->unk_204, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        } else {
            this->unk_150 = 3;
            this->unk_1E4 = this->unk_1E4 | 0x20;
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_204, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        }

        SkelAnime_ChangeAnim(&this->skin.skelAnime, D_80A6D370[this->unk_150], func_80A6B30C(this), 0.0f,
                             SkelAnime_GetFrameCount(&D_80A6D370[this->unk_150]->genericHeader), 2, 0.0f);
        this->unk_1E4 &= ~1;
        this->unk_1E4 &= ~2;
        this->unk_1E4 &= ~8;
        this->unk_1E4 &= ~0x10;
    }
}

void func_80A6C8E0(EnHorseNormal* this, GlobalContext* globalCtx) {
    s32 pad2;
    CollisionPoly* sp38;
    s32 pad;
    Vec3f sp28;
    s32 sp24;

    sp28.x = (Math_Sins(this->actor.shape.rot.y) * 30.0f) + this->actor.posRot.pos.x;
    sp28.y = this->actor.posRot.pos.y + 60.0f;
    sp28.z = (Math_Coss(this->actor.shape.rot.y) * 30.0f) + this->actor.posRot.pos.z;
    this->unk_220 = func_8003C940(&globalCtx->colCtx, &sp38, &sp24, &sp28);
    this->actor.shape.rot.x = Math_atan2f(this->actor.posRot.pos.y - this->unk_220, 30.0f) * 10430.378f;
}

void EnHorseNormal_Update(Actor* thisx, GlobalContext* globalCtx) {
    static EnHorseNormalActionFunc D_80A6D534[] = {
        func_80A6BC00, func_80A6BE6C, func_80A6C570, func_80A6C760, func_80A6B9D0,
    };

    EnHorseNormal* this = THIS;
    s32 pad;

    D_80A6D534[this->unk_14C](this, globalCtx);
    Actor_MoveForward(&this->actor);
    func_8002E4B4(globalCtx, &this->actor, 20.0f, 35.0f, 100.0f, 0x1D);
    if ((globalCtx->sceneNum == SCENE_SPOT20) && (this->actor.posRot.pos.z < -2400.0f)) {
        this->actor.posRot.pos.z = -2400.0f;
    }

    this->actor.posRot2.pos = this->actor.posRot.pos;
    this->actor.posRot2.pos.y += 70.0f;
    this->unk_204 = this->actor.projectedPos;
    this->unk_204.y += 120.0f;
    Collider_CylinderUpdate(&this->actor, &this->collider1);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    if (this->actor.speedXZ == 0.0f) {
        this->actor.colChkInfo.mass = 0xFF;
    } else {
        this->actor.colChkInfo.mass = 0xFE;
    }
}

void func_80A6CAFC(EnHorseNormal* this, GlobalContext* globalCtx, ColliderJntSphItem* colliderSphereItem) {
    Vec3f sp4C;
    Vec3f sp40;
    s32 i;
    s32 pad;

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

void func_80A6CC88(GlobalContext* globalCtx, EnHorseNormal* this, Vec3f* arg2) {
    f32 frame = this->skin.skelAnime.animCurrentFrame;
    f32 sp38;

    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->mf_11D60, arg2, &this->unk_1E8, &sp38);
    this->unk_1F4 = this->unk_1E8;
    this->unk_1F4.y += 120.0f;

    if ((this->unk_150 == 0) && (frame > 28.0f) && ((this->unk_1E4 & 8) == 0)) {
        this->unk_1E4 |= 8;
        Audio_PlaySoundGeneral(0x282C, &this->unk_1E8, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    } else if ((this->unk_150 == 3) && (frame > 25.0f) && ((this->unk_1E4 & 0x10) == 0)) {
        this->unk_1E4 |= 0x10;
        Audio_PlaySoundGeneral(0x282B, &this->unk_1E8, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    } else if ((this->unk_150 == 3) && ((this->unk_1E4 & 0x20) != 0)) {
        this->unk_1E4 &= ~0x20;
        Audio_PlaySoundGeneral(0x2805, &this->unk_1F4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    } else if ((this->unk_150 == 1) && ((this->unk_1E4 & 0x20) != 0)) {
        this->unk_1E4 &= ~0x20;
        Audio_PlaySoundGeneral(0x2816, &this->unk_1F4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    }
}

void EnHorseNormal_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHorseNormal* this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_horse_normal.c", 2224);

    if ((globalCtx->sceneNum != SCENE_SPOT20) || (globalCtx->sceneNum != SCENE_MALON_STABLE)) {
        func_80A6C8E0(this, globalCtx);
    }

    func_80093D18(globalCtx->state.gfxCtx);
    func_800A6330(&this->actor, globalCtx, &this->skin, func_80A6CAFC, 1);
    if (this->unk_14C == 3) {
        MtxF sp74;
        s32 pad2;
        Vec3f sp64 = { 0.0f, 0.0f, 0.0f };
        s16 sp62;
        f32 sp5C;
        Mtx* matrix;

        sp5C = this->actor.posRot.pos.y - this->actor.groundY;
        if (globalCtx->sceneNum == SCENE_MALON_STABLE) {
            if ((this->actor.posRot.pos.x == 355.0f) && (this->actor.posRot.pos.y == 0.0f) &&
                (this->actor.posRot.pos.z == -245.0f)) {
                sp64.x = 235.0f;
                sp64.y = 0.0f;
                sp64.z = 100.0f;
                sp62 = 0x7FFF;
            } else if ((this->actor.posRot.pos.x == 238.0f) && (this->actor.posRot.pos.y == 0.0f) &&
                       (this->actor.posRot.pos.z == -245.0f)) {
                sp64.x = 478.0f;
                sp64.y = 0.0f;
                sp64.z = 100.0f;
                sp62 = 0x7FFF;
            }
        } else if (globalCtx->sceneNum == SCENE_SPOT20) {
            if ((this->actor.posRot.pos.x == -730.0f) && (this->actor.posRot.pos.y == 0.0f) &&
                (this->actor.posRot.pos.z == -1100.0f)) {
                sp64.x = 780.0f;
                sp64.y = 0.0f;
                sp64.z = -80.0f;
                sp62 = 0;
            } else if ((this->actor.posRot.pos.x == 880.0f) && (this->actor.posRot.pos.y == 0.0f) &&
                       (this->actor.posRot.pos.z == -1170.0f)) {
                sp64.x = -1000.0f;
                sp64.y = 0.0f;
                sp64.z = -70.0f;
                sp62 = 0;
            }
        }

        func_80A6CC88(globalCtx, this, &sp64);
        SkinMatrix_SetScaleRotateYRPTranslate(&sp74, this->actor.scale.x, this->actor.scale.y, this->actor.scale.z,
                                              this->actor.shape.rot.x, sp62, this->actor.shape.rot.z, sp64.x,
                                              (this->actor.shape.unk_08 * this->actor.scale.y) + sp64.y, sp64.z);
        matrix = SkinMatrix_MtxFToNewMtx(globalCtx->state.gfxCtx, &sp74);
        if (matrix == NULL) {
            return;
        }

        gSPMatrix(oGfxCtx->polyOpa.p++, &gMtxClear, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(oGfxCtx->polyOpa.p++, matrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        func_800A63CC(&this->actor, globalCtx, &this->skin, 0, 0, 1, 0, 3);
        this->collider3.dim.pos.x = sp64.x;
        this->collider3.dim.pos.y = sp64.y;
        this->collider3.dim.pos.z = sp64.z;
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
        func_80094044(globalCtx->state.gfxCtx);
        gDPSetPrimColor(oGfxCtx->polyXlu.p++, 0, 0, 0, 0, 0, 255);
        Matrix_Translate(sp64.x, sp64.y, sp64.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x * ((1.0f - (sp5C * 0.01f)) * this->actor.shape.unk_10), 1.0f,
                     this->actor.scale.z * ((1.0f - (sp5C * 0.01f)) * this->actor.shape.unk_10), MTXMODE_APPLY);
        Matrix_RotateY(sp62 * 0.0000958738f, MTXMODE_APPLY);
        matrix = Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_horse_normal.c", 2329);
        if (matrix != NULL) {
            gSPMatrix(oGfxCtx->polyXlu.p++, matrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(oGfxCtx->polyXlu.p++, Horse_Normal_D_04049AD0);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_horse_normal.c", 2339);
}
