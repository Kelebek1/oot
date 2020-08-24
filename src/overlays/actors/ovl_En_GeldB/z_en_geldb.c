#include "z_en_geldb.h"

#define FLAGS 0x00000015

#define THIS ((EnGeldB*)thisx)

void EnGeldB_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGeldB_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGeldB_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGeldB_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80A39E2C(GlobalContext* globalCtx, EnGeldB* this);

void func_80A35974(EnGeldB* this);
void func_80A35D48(EnGeldB* this);
void func_80A36A10(EnGeldB* this);
void func_80A365DC(EnGeldB* this);
void func_80A3792C(EnGeldB* this);
void func_80A367E4(EnGeldB* this);
void func_80A38290(EnGeldB* this);
void func_80A38430(EnGeldB* this);
void func_80A37D70(EnGeldB* this);
void func_80A37670(EnGeldB* this);
void func_80A3907C(EnGeldB* this);

void func_80A35A08(EnGeldB* this, GlobalContext* globalCtx);
void func_80A35DD0(EnGeldB* this, GlobalContext* globalCtx);
void func_80A360B0(EnGeldB* this, GlobalContext* globalCtx);
void func_80A370BC(EnGeldB* this, GlobalContext* globalCtx);
void func_80A387D0(EnGeldB* this, GlobalContext* globalCtx);
void func_80A36AE4(EnGeldB* this, GlobalContext* globalCtx);
void func_80A36690(EnGeldB* this, GlobalContext* globalCtx);
void func_80A379C0(EnGeldB* this, GlobalContext* globalCtx);
void func_80A36830(EnGeldB* this, GlobalContext* globalCtx);
void func_80A38348(EnGeldB* this, GlobalContext* globalCtx);
void func_80A384E8(EnGeldB* this, GlobalContext* globalCtx);
void func_80A37DEC(EnGeldB* this, GlobalContext* globalCtx);
void func_80A376E0(EnGeldB* this, GlobalContext* globalCtx);
void func_80A36130(EnGeldB* this, GlobalContext* globalCtx);
void func_80A37224(EnGeldB* this, GlobalContext* globalCtx);
void func_80A38960(EnGeldB* this, GlobalContext* globalCtx);
void func_80A37F98(EnGeldB* this, GlobalContext* globalCtx);
void func_80A39120(EnGeldB* this, GlobalContext* globalCtx);
void func_80A380EC(EnGeldB* this, GlobalContext* globalCtx);
void func_80A35C24(EnGeldB* this, GlobalContext* globalCtx);

extern SkeletonHeader D_0600A458;
extern AnimationHeader D_0600B6D4;
extern AnimationHeader D_0600ADF8;
extern AnimationHeader D_0600A814;
extern AnimationHeader D_06001390;
extern AnimationHeader D_06000F5C;
extern AnimationHeader D_06001578;
extern AnimationHeader D_060003CC;
extern AnimationHeader D_060024E8;
extern AnimationHeader D_06002280;
extern AnimationHeader D_06001E10;

const ActorInit En_GeldB_InitVars = {
    ACTOR_EN_GELDB,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_GELDB,
    sizeof(EnGeldB),
    (ActorFunc)EnGeldB_Init,
    (ActorFunc)EnGeldB_Destroy,
    (ActorFunc)EnGeldB_Update,
    (ActorFunc)EnGeldB_Draw,
};

// sCylinderInit
ColliderCylinderInit D_80A39FE0 = {
    { COLTYPE_UNK5, 0x00, 0x09, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x01, { 0x00000000, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x01, 0x01 },
    { 20, 50, 0, { 0, 0, 0 } },
};

// sTrisItemsInit
ColliderTrisItemInit D_80A3A00C[2] = {
    {
        { 0x02, { 0x00000000, 0x00, 0x00 }, { 0xFFC1FFFF, 0x00, 0x00 }, 0x00, 0x01, 0x00 },
        { { { -10.0f, 14.0f, 2.0f }, { -10.0f, -6.0f, 2.0f }, { 9.0f, 14.0f, 2.0f } } },
    },
    {
        { 0x02, { 0x00000000, 0x00, 0x00 }, { 0xFFC1FFFF, 0x00, 0x00 }, 0x00, 0x01, 0x00 },
        { { { -10.0f, -6.0f, 2.0f }, { 9.0f, -6.0f, 2.0f }, { 9.0f, 14.0f, 2.0f } } },
    },
};

// sTrisInit
ColliderTrisInit D_80A3A084 = {
    { COLTYPE_METAL_SHIELD, 0x00, 0x0D, 0x00, 0x00, COLSHAPE_TRIS },
    2,
    D_80A3A00C,
};

// sQuadInit
ColliderQuadInit D_80A3A094 = {
    { COLTYPE_UNK10, 0x11, 0x00, 0x00, 0x00, COLSHAPE_QUAD },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x08 }, { 0x00000000, 0x00, 0x00 }, 0x81, 0x00, 0x00 },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

DamageTable D_80A3A0E4[] = {
    0x10, 0x02, 0x01, 0x02, 0x10, 0x02, 0x02, 0x10, 0x01, 0x02, 0x04, 0x02, 0xF2, 0x02, 0x02, 0x02,
    0x02, 0xE4, 0x60, 0xD3, 0x00, 0x00, 0x01, 0x04, 0x02, 0x02, 0x08, 0x04, 0x04, 0x00, 0x04, 0x00,
};

// sInitChain
InitChainEntry D_80A3A104[] = {
    ICHAIN_F32(unk_4C, 2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, 62536, ICHAIN_STOP),
};

// not referenced anywhere??
static Vec3f D_80A3A118 = { 1100.0f, -700.0f, 0.0f };

void EnGeldB_SetupAction(EnGeldB* this, EnGeldBActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

#ifdef NON_MATCHING
// Big mess, ordering is bad due to EffectBlureInit1 memes
// left as-is to show what I was trying
typedef struct {
    Color_RGBA8 colour1;
    Color_RGBA8 colour2;
    Color_RGBA8 colour3;
    Color_RGBA8 colour4;
} StructColours;

typedef struct {
    /* 0x000 */ char unk_00[0x184];
    union {
        /* 0x184 */ u8 colours[16];
        struct {
            Color_RGBA8_n p1StartColor;
            Color_RGBA8_n p2StartColor;
            Color_RGBA8_n p1EndColor;
            Color_RGBA8_n p2EndColor;
        };
    };
    ///* 0x188 */ Color_RGBA8_n p2StartColor;
    ///* 0x18C */ Color_RGBA8_n p1EndColor;
    ///* 0x190 */ Color_RGBA8_n p2EndColor;
    /* 0x194 */ s32 elemDuration;
    /* 0x198 */ s32 unkFlag;
    /* 0x19C */ s32 calcMode;
} TestStruct; // size = 0x1A0 // was EffectBlureInit1

void EnGeldB_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGeldB* this = THIS;
    s32 pad;
    s32 pad2;
    s32 pad3;
    s32 i;
    TestStruct sp44; // was EffectBlureInit1

    Actor_ProcessInitChain(thisx, D_80A3A104);
    thisx->colChkInfo.damageTable = D_80A3A0E4;
    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawFunc_Teardrop, 0.0f);

    thisx->colChkInfo.mass = 0xFE;
    thisx->colChkInfo.health = 20;
    thisx->colChkInfo.unk_10 = 50;
    thisx->colChkInfo.unk_12 = 100;

    this->unk_30C = 10.0f;

    this->unk_31A = 0;

    thisx->naviEnemyId = 0x54;

    this->unk_314 = thisx->params & 0xFF00;
    thisx->params &= 0xFF;

    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600A458, &D_0600B6D4, this->limbDrawTable,
                     this->transitionDrawTable, 24);
    Collider_InitCylinder(globalCtx, &this->collider1);
    Collider_SetCylinder(globalCtx, &this->collider1, thisx, &D_80A39FE0);
    Collider_InitTris(globalCtx, &this->collider3);
    Collider_SetTris(globalCtx, &this->collider3, thisx, &D_80A3A084, this->collider3Items);
    Collider_InitQuad(globalCtx, &this->collider2);
    Collider_SetQuad(globalCtx, &this->collider2, thisx, &D_80A3A094);

    // var = 0xFF;
    // p1Start

    sp44.colours[0] = sp44.colours[1] = sp44.colours[2] = sp44.colours[3] =
        // p2Start
        sp44.colours[4] = sp44.colours[5] = sp44.colours[6] =
            // sp44.colours[7] = 0x40;

        // p1End
        sp44.colours[8] = sp44.colours[9] = sp44.colours[10] =
            // sp44.colours[11] = 0;

        // p2End
        sp44.colours[12] = sp44.colours[13] = sp44.colours[14] = sp44.colours[15] = 0xFF;
    // sp44.colours[15] = 0;

    // sp44.colours[7] = 0x40;
    // sp44.colours[11] = 0;

    sp44.p1StartColor.a = 0x40;
    sp44.p1EndColor.a = 0;
    if (this) {};

    sp44.elemDuration = 8;
    sp44.unkFlag = 0;
    sp44.calcMode = 2;

    // sp44.p1EndColor.a = 0xFF;
    // sp44.colours[15] = 0;

    /*
    sp44.p2EndColor.r = sp44.p2EndColor.g = sp44.p2EndColor.b = 0xFF;

    sp44.p1EndColor.r = sp44.p1EndColor.g = sp44.p1EndColor.b = 0xFF;
    sp44.p1EndColor.a = 0;

    sp44.p2StartColor.r = sp44.p2StartColor.g = sp44.p2StartColor.b = 0xFF;
    sp44.p2StartColor.a = 0x40;

    sp44.p1StartColor.r = sp44.p1StartColor.g = sp44.p1StartColor.b = sp44.p1StartColor.a = 0xFF;
    sp44.p2EndColor.a = 0;
    */

    Effect_Add(globalCtx, &this->unk_31C, EFFECT_BLURE1, 0, 0, &sp44);

    Actor_SetScale(thisx, 0.012499999f);
    func_80A35974(this);
    if ((this->unk_314 != 0) && Flags_GetCollectible(globalCtx, this->unk_314 >> 8)) {
        Actor_Kill(thisx);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_GeldB/EnGeldB_Init.s")
#endif

void EnGeldB_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGeldB* this = THIS;

    func_800F5B58();
    Effect_Delete(globalCtx, this->unk_31C);
    Collider_DestroyTris(globalCtx, &this->collider3);
    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyQuad(globalCtx, &this->collider2);
}

s32 func_80A3559C(GlobalContext* globalCtx, EnGeldB* this, s16 arg2) {
    Player* player = PLAYER;
    s32 pad;
    s16 sp36;
    s16 sp34;
    Actor* refActor;
    s16 sp2E;
    s16 tmp;

    sp36 = this->actor.wallPolyRot - this->actor.shape.rot.y;
    if (sp36 < 0) {
        sp36 = -sp36;
    }

    sp34 = this->actor.yawTowardsLink - this->actor.shape.rot.y;
    if (sp34 < 0) {
        sp34 = -sp34;
    }

    if (func_800354B4(globalCtx, &this->actor, 100.0f, 0x2710, 0x3E80, this->actor.shape.rot.y) != 0) {
        if (player->swordAnimation == 0x11) {
            func_80A370BC(this, globalCtx);
            return 1;
        } else if ((globalCtx->gameplayFrames % 2) != 0) {
            func_80A38430(this);
            return 1;
        }
    }

    if (func_800354B4(globalCtx, &this->actor, 100.0f, 0x5DC0, 0x2AA8, this->actor.shape.rot.y) != 0) {
        this->actor.posRot.rot.y = this->actor.yawTowardsLink;
        this->actor.shape.rot.y = this->actor.yawTowardsLink;
        if ((this->actor.bgCheckFlags & 8) && (ABS(sp36) < 0x2EE0) && (this->actor.xzDistFromLink < 90.0f)) {
            func_80A38290(this);
        } else if (player->swordAnimation == 0x11) {
            func_80A370BC(this, globalCtx);
        } else if ((this->actor.xzDistFromLink < 90.0f) && ((globalCtx->gameplayFrames % 2) != 0)) {
            func_80A38430(this);
        } else {
            func_80A37D70(this);
        }

        return 1;
    } else {
        refActor = Actor_FindNearby(globalCtx, &this->actor, -1, ACTORTYPE_EXPLOSIVES, 80.0f);
        if (refActor != NULL) {
            this->actor.posRot.rot.y = this->actor.yawTowardsLink;
            this->actor.shape.rot.y = this->actor.yawTowardsLink;
            if (((this->actor.bgCheckFlags & 8) && (sp36 < 0x2EE0)) || (refActor->id == ACTOR_EN_BOM_CHU)) {
                if (((refActor->id == ACTOR_EN_BOM_CHU) && (func_8002DB48(&this->actor, refActor) < 80.0f)) &&
                    ((s16)((this->actor.shape.rot.y - refActor->posRot.rot.y) + 0x8000) < 0x3E80)) {
                    func_80A38290(this);
                } else {
                    func_80A387D0(this, globalCtx);
                }
            } else {
                func_80A37D70(this);
            }

            return 1;
        } else if (arg2 != 0) {
            if (sp34 >= 0x1B58) {
                func_80A387D0(this, globalCtx);
            } else {
                sp2E = player->actor.shape.rot.y - this->actor.shape.rot.y;
                if ((this->actor.xzDistFromLink <= 45.0f) && (func_80033AB8(globalCtx, &this->actor) == 0) &&
                    (((globalCtx->gameplayFrames % 8) != 0) || (ABS(sp2E) < 0x38E0))) {
                    func_80A37670(this);
                } else {
                    func_80A36A10(this);
                }
            }

            return 1;
        }
    }

    return 0;
}

void func_80A35974(EnGeldB* this) {
    SkelAnime_ChangeAnimPlaybackStop(&this->skelAnime, &D_0600ADF8, 0.0f);
    this->actor.posRot.pos.y = this->actor.initPosRot.pos.y + 120.0f;
    this->unk_300 = 10;
    this->unk_318 = 1;
    this->unk_2EC = 0;
    this->actor.gravity = -2.0f;
    this->actor.bgCheckFlags &= ~3;
    this->actor.flags &= ~1;
    EnGeldB_SetupAction(this, func_80A35A08);
}

void func_80A35A08(EnGeldB* this, GlobalContext* globalCtx) {
    if (((this->unk_318 != 0) && !Flags_GetSwitch(globalCtx, this->actor.initPosRot.rot.z)) ||
        (this->actor.xzDistFromLink > 300.0f)) {
        this->actor.posRot.rot.y = this->actor.yawTowardsLink;
        this->actor.shape.rot.y = this->actor.yawTowardsLink;
        this->actor.posRot.pos.y = this->actor.groundY + 120.0f;
    } else {
        this->unk_318 = 0;
        this->actor.shape.unk_10 = 90.0f;
        func_800F5ACC(0x38);
    }

    if (this->actor.bgCheckFlags & 2) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_DOWN);
        this->actor.flags |= 1;
        this->skelAnime.animPlaybackSpeed = 1.0f;
        this->actor.posRot.pos.y = this->actor.groundY;
        this->actor.posRot2.pos = this->actor.posRot.pos;
        this->actor.velocity.y = 0.0f;
        this->actor.bgCheckFlags &= ~2;
        func_80033260(globalCtx, &this->actor, &this->unk_4D0, 3.0f, 2, 2.0f, 0, 0, 0);
        func_80033260(globalCtx, &this->actor, &this->unk_4C4, 3.0f, 2, 2.0f, 0, 0, 0);
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        func_80A35D48(this);
    }
}

void func_80A35B8C(EnGeldB* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600ADF8, -2.0f, SkelAnime_GetFrameCount(&D_0600ADF8.genericHeader), 0.0f,
                         3, -4.0f);
    this->unk_300 = 0x14;
    this->unk_318 = 0;
    this->unk_2EC = 0;
    this->actor.posRot.rot.y = this->actor.yawTowardsLink;
    this->actor.shape.rot.y = this->actor.yawTowardsLink;
    EnGeldB_SetupAction(this, func_80A35C24);
}

void func_80A35C24(EnGeldB* this, GlobalContext* globalCtx) {
    if (this->skelAnime.animCurrentFrame == 10.0f) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL_JUMP);
    }

    if (this->skelAnime.animCurrentFrame == 2.0f) {
        this->actor.gravity = 0.0f;
        func_80033260(globalCtx, &this->actor, &this->unk_4D0, 3.0f, 2, 2.0f, 0, 0, 0);
        func_80033260(globalCtx, &this->actor, &this->unk_4C4, 3.0f, 2, 2.0f, 0, 0, 0);
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.y, this->actor.groundY + 300.0f, 1.0f, 20.5f, 0.0f);
        this->unk_300--;
        if (this->unk_300 == 0) {
            Actor_Kill(&this->actor);
        }
    }
}

void func_80A35D48(EnGeldB* this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_0600B6D4, -4.0f);
    this->unk_2EC = 5;
    this->unk_300 = (Math_Rand_ZeroOne() * 10.0f) + 5.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    EnGeldB_SetupAction(this, func_80A35DD0);
}

void func_80A35DD0(EnGeldB* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 pad;
    s16 tmp;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_2FA != 0) {
        tmp = (this->actor.yawTowardsLink - this->actor.shape.rot.y) - this->unk_4DE;
        if (ABS(tmp) >= 0x2001) {
            this->unk_2FA--;
            return;
        }

        this->unk_2FA = 0;
    }

    tmp = this->actor.yawTowardsLink - this->actor.shape.rot.y;
    if (!func_80A39E2C(globalCtx, this)) {
        if (this->unk_2F8 != 0) {
            this->unk_2F8--;
            if (ABS(tmp) < 0x1FFE) {
                this->unk_2F8 = 0;
            } else {
                return;
            }
        } else if (func_80A3559C(globalCtx, this, 0)) {
            return;
        }

        tmp = player->actor.shape.rot.y - this->actor.shape.rot.y;
        if ((this->actor.xzDistFromLink < 100.0f) && (player->swordState != 0) && (ABS(tmp) >= 0x1F40)) {
            this->actor.posRot.rot.y = this->actor.yawTowardsLink;
            this->actor.shape.rot.y = this->actor.yawTowardsLink;
            func_80A36A10(this);
            return;
        }

        this->unk_300--;
        if (this->unk_300 == 0) {
            if (func_8002E084(&this->actor, 0x1555) != 0) {
                if ((this->actor.xzDistFromLink < 210.0f) && (this->actor.xzDistFromLink > 150.0f) &&
                    (Math_Rand_ZeroOne() < 0.3f)) {
                    if ((func_80033AB8(globalCtx, &this->actor) != 0) || (Math_Rand_ZeroOne() > 0.5f) ||
                        (ABS(tmp) < 0x38E0)) {
                        func_80A365DC(this);
                    } else {
                        func_80A3792C(this);
                    }
                } else if (Math_Rand_ZeroOne() > 0.3f) {
                    func_80A360B0(this, globalCtx);
                } else {
                    func_80A36A10(this);
                }
            } else {
                func_80A367E4(this);
            }

            if ((globalCtx->gameplayFrames & 0x5F) == 0) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_BREATH);
            }
        }
    }
}

void func_80A360B0(EnGeldB* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_060024E8, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_060024E8.genericHeader),
                         1, -4.0f);
    this->unk_2EC = 8;
    EnGeldB_SetupAction(this, func_80A36130);
}

void func_80A36130(EnGeldB* this, GlobalContext* globalCtx) {
    s32 sp44;
    s32 sp40;
    s32 pad;
    s16 tmp;
    Player* player = PLAYER;
    s32 pad2;
    s32 pad3;
    f32 sp28;

    if (func_80A39E2C(globalCtx, this) == 0) {
        Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 1, 0x2EE, 0);
        this->actor.posRot.rot.y = this->actor.shape.rot.y;
        if (this->actor.xzDistFromLink <= 40.0f) {
            Math_SmoothScaleMaxMinF(&this->actor.speedXZ, -8.0f, 1.0f, 1.5f, 0.0f);
        } else if (this->actor.xzDistFromLink > 55.0f) {
            Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 8.0f, 1.0f, 1.5f, 0.0f);
        } else {
            Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 1.0f, 6.65f, 0.0f);
        }

        this->skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.125f;
        tmp = player->actor.shape.rot.y - this->actor.shape.rot.y;
        tmp = ABS(tmp);

        if ((this->actor.xzDistFromLink < 150.0f) && (player->swordState != 0) && (tmp >= 0x1F40)) {
            this->actor.shape.rot.y = this->actor.posRot.rot.y = this->actor.yawTowardsLink;
            if (Math_Rand_ZeroOne() > 0.7f) {
                func_80A36A10(this);
                return;
            }
        }

        sp44 = this->skelAnime.animCurrentFrame;
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);

        sp28 = ABS(this->skelAnime.animPlaybackSpeed);
        sp40 = this->skelAnime.animCurrentFrame - sp28;
        sp28 = ABS(this->skelAnime.animPlaybackSpeed);

        if (func_8002E084(&this->actor, 0x11C7) == 0) {
            if (Math_Rand_ZeroOne() > 0.5f) {
                func_80A36A10(this);
            } else {
                func_80A35D48(this);
            }
        } else if (this->actor.xzDistFromLink < 90.0f) {
            if ((func_80033AB8(globalCtx, &this->actor) == 0) &&
                ((Math_Rand_ZeroOne() > 0.03f) || ((this->actor.xzDistFromLink <= 45.0f) && (tmp < 0x38E0)))) {
                func_80A37670(this);
            } else if ((func_80033AB8(globalCtx, &this->actor) != 0) && (Math_Rand_ZeroOne() > 0.5f)) {
                func_80A37D70(this);
            } else {
                func_80A36A10(this);
            }
        }

        if (func_80A3559C(globalCtx, this, 0) == 0) {
            if ((this->actor.xzDistFromLink < 210.0f) && (this->actor.xzDistFromLink > 150.0f)) {
                if (func_8002E084(&this->actor, 0x71C) != 0) {
                    if (func_80033A84(globalCtx, &this->actor) != 0) {
                        if (Math_Rand_ZeroOne() > 0.5f) {
                            func_80A365DC(this);
                        } else {
                            func_80A3792C(this);
                        }
                    } else {
                        func_80A36A10(this);
                        return;
                    }
                }
            }

            if ((globalCtx->gameplayFrames & 0x5F) == 0) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_BREATH);
            }

            if ((s32)this->skelAnime.animCurrentFrame != sp44) {
                if (((sp40 < 0) && (((s32)sp28 + sp44) > 0)) || ((sp40 < 4) && (((s32)sp28 + sp44) > 4))) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_MUSI_LAND);
                }
            }
        }
    }
}

void func_80A365DC(EnGeldB* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06001390, -1.0f, SkelAnime_GetFrameCount(&D_06001390.genericHeader), 0.0f,
                         2, -3.0f);
    this->actor.shape.rot.y = this->actor.yawTowardsLink;
    this->actor.posRot.rot.y = this->actor.yawTowardsLink;
    this->unk_300 = 0;
    this->unk_318 = 1;
    this->unk_2EC = 0xE;
    this->actor.speedXZ = 10.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL_JUMP);
    EnGeldB_SetupAction(this, func_80A36690);
}

void func_80A36690(EnGeldB* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 sp22 = player->actor.shape.rot.y - this->actor.shape.rot.y;

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        this->unk_318 = 0;
        this->actor.speedXZ = 0.0f;
        if (func_8002E084(&this->actor, 0x1554) == 0) {
            func_80A35D48(this);
            this->unk_300 = (Math_Rand_ZeroOne() * 5.0f) + 5.0f;
            if (ABS(sp22) < 0x38E0) {
                this->unk_2FA = 0x14;
            }
        } else if ((func_80033AB8(globalCtx, &this->actor) == 0) &&
                   ((Math_Rand_ZeroOne() > 0.5f) || (ABS(sp22) < 0x3FFC))) {
            func_80A37670(this);
        } else {
            func_80A360B0(this, globalCtx);
        }
    }

    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_BREATH);
    }
}

void func_80A367E4(EnGeldB* this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_0600A814, -4.0f);
    this->unk_2EC = 9;
    EnGeldB_SetupAction(this, func_80A36830);
}

void func_80A36830(EnGeldB* this, GlobalContext* globalCtx) {
    s16 rot;
    s16 tmp;
    s16 tmp2;
    f32 tmpf1;

    if (func_80A39E2C(globalCtx, this) == 0) {
        if (func_80A3559C(globalCtx, this, 0) == 0) {
            rot = this->actor.shape.rot.y;
            tmp = this->actor.yawTowardsLink - rot;
            if (tmp > 0) {
                tmp2 = (tmp * 0.25f) + 2000.0f;
            } else {
                tmp2 = (tmp * 0.25f) - 2000.0f;
            }

            this->actor.shape.rot.y = rot + tmp2;
            this->actor.posRot.rot.y = this->actor.shape.rot.y;
            if (tmp > 0) {
                tmpf1 = tmp2 * 0.5f;
                if (tmpf1 > 1.0f) {
                    tmpf1 = 1.0f;
                }
            } else {
                tmpf1 = tmp2 * 0.5f;
                if (tmpf1 < -1.0f) {
                    tmpf1 = -1.0f;
                }
            }

            this->skelAnime.animPlaybackSpeed = -tmpf1;
            SkelAnime_FrameUpdateMatrix(&this->skelAnime);
            if (func_8002E084(&this->actor, 0x1555) != 0) {
                if (Math_Rand_ZeroOne() > 0.8f) {
                    func_80A36A10(this);
                } else {
                    func_80A360B0(this, globalCtx);
                }
            }
            if ((globalCtx->gameplayFrames & 0x5F) == 0) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_BREATH);
            }
        }
    }
}

void func_80A36A10(EnGeldB* this) {
    f32 rand;

    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600A814, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_0600A814.genericHeader),
                         1, 0.0f);
    rand = Math_Rand_CenteredFloat(12.0f);
    this->actor.speedXZ = rand;
    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    this->skelAnime.animPlaybackSpeed = -rand * 0.5f;
    this->unk_300 = (Math_Rand_ZeroOne() * 30.0f) + 30.0f;
    this->unk_2EC = 10;
    this->unk_304 = 0.0f;
    EnGeldB_SetupAction(this, func_80A36AE4);
}

void func_80A36AE4(EnGeldB* this, GlobalContext* globalCtx) {
    s16 sp3E;
    s16 rot;
    s32 pad;
    s32 sp34;
    s32 pad2;
    f32 absFrame;
    Player* player = PLAYER;
    s32 tmp5;
    s32 absFrame32;

    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 1, 0xFA0, 1);
    if ((func_80A39E2C(globalCtx, this) == 0) && (func_80A3559C(globalCtx, this, 0) == 0)) {
        rot = this->actor.shape.rot.y;
        this->actor.posRot.rot.y = rot + 0x3A98;
        sp3E = player->actor.shape.rot.y + 0x8000;
        if (Math_Sins(sp3E - rot) >= 0.0f) {
            this->actor.speedXZ -= 0.25f;
            if (this->actor.speedXZ < -8.0f) {
                this->actor.speedXZ = -8.0f;
            }
        } else if (Math_Sins(sp3E - this->actor.shape.rot.y) < 0.0f) {
            this->actor.speedXZ += 0.25f;
            if (this->actor.speedXZ > 8.0f) {
                this->actor.speedXZ = 8.0f;
            }
        }

        if ((this->actor.bgCheckFlags & 8) ||
            !func_800339B8(&this->actor, globalCtx, this->actor.speedXZ, this->actor.shape.rot.y + 0x3E80)) {
            s16 tmp;
            if (this->actor.bgCheckFlags & 8) {
                tmp = ((this->actor.speedXZ >= 0.0f) ? this->actor.shape.rot.y + 0x3E80
                                                     : this->actor.shape.rot.y - 0x3E80);
                tmp = this->actor.wallPolyRot - tmp;
            } else {
                this->actor.speedXZ *= -0.8f;
                tmp = 0;
            }

            if (ABS(tmp) >= 0x4001) {
                this->actor.speedXZ *= -0.8f;
                if (this->actor.speedXZ < 0.0f) {
                    this->actor.speedXZ -= 0.5f;
                } else {
                    this->actor.speedXZ += 0.5f;
                }
            }
        }

        if (this->actor.xzDistFromLink <= 45.0f) {
            Math_SmoothScaleMaxMinF(&this->unk_304, -4.0f, 1.0f, 1.5f, 0.0f);
        } else if (this->actor.xzDistFromLink > 40.0f) {
            Math_SmoothScaleMaxMinF(&this->unk_304, 4.0f, 1.0f, 1.5f, 0.0f);
        } else {
            Math_SmoothScaleMaxMinF(&this->unk_304, 0.0f, 1.0f, 6.65f, 0.0f);
        }

        if (this->unk_304 != 0.0f) {
            this->actor.posRot.pos.x += Math_Sins(this->actor.shape.rot.y) * this->unk_304;
            this->actor.posRot.pos.z += Math_Coss(this->actor.shape.rot.y) * this->unk_304;
        }

        if (ABS(this->unk_304) < ABS(this->actor.speedXZ)) {
            this->skelAnime.animPlaybackSpeed = -this->actor.speedXZ * 0.5f;
        } else {
            this->skelAnime.animPlaybackSpeed = -this->unk_304 * 0.5f;
        }

        this->skelAnime.animPlaybackSpeed = CLAMP(this->skelAnime.animPlaybackSpeed, -3.0f, 3.0f);
        sp34 = this->skelAnime.animCurrentFrame;
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);

        tmp5 = this->skelAnime.animCurrentFrame - ABS(this->skelAnime.animPlaybackSpeed);
        absFrame = ABS(this->skelAnime.animPlaybackSpeed);
        absFrame32 = absFrame;
        if (sp34 != (s32)this->skelAnime.animCurrentFrame) {
            if (((tmp5 < 0) && ((absFrame32 + sp34) > 0)) || ((tmp5 < 5) && ((absFrame32 + sp34) > 5))) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_MUSI_LAND);
            }
        }

        if ((globalCtx->gameplayFrames & 0x5F) == 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_BREATH);
        }

        if ((Math_Coss(sp3E - this->actor.shape.rot.y) < -0.85f) && (func_80033AB8(globalCtx, &this->actor) == 0) &&
            (this->actor.xzDistFromLink <= 45.0f)) {
            func_80A37670(this);
        } else {
            this->unk_300--;
            if (this->unk_300 == 0) {
                if (func_80033AB8(globalCtx, &this->actor) && (Math_Rand_ZeroOne() > 0.5f)) {
                    func_80A37D70(this);
                } else {
                    func_80A35D48(this);
                }
            }
        }
    }
}

void func_80A370BC(EnGeldB* this, GlobalContext* globalCtx) {
    s16 tmp;
    Player* player = PLAYER;

    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600A814, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_0600A814.genericHeader),
                         1, 0.0f);
    tmp = player->actor.shape.rot.y;
    if (Math_Sins(tmp - this->actor.shape.rot.y) > 0.0f) {
        this->actor.speedXZ = -10.0f;
    } else if (Math_Sins(tmp - this->actor.shape.rot.y) < 0.0f) {
        this->actor.speedXZ = 10.0f;
    } else if (Math_Rand_ZeroOne() > 0.5f) {
        this->actor.speedXZ = 10.0f;
    } else {
        this->actor.speedXZ = -10.0f;
    }

    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    this->unk_300 = 6;
    this->unk_304 = 0.0f;
    this->unk_30C = 0.0f;
    this->skelAnime.animPlaybackSpeed = -this->actor.speedXZ * 0.5f;
    this->unk_2EC = 0x10;
    EnGeldB_SetupAction(this, func_80A37224);
}

void func_80A37224(EnGeldB* this, GlobalContext* globalCtx) {
    s32 tmp2;
    s32 sp28;
    f32 tmp3;

    this->actor.posRot.rot.y = this->actor.yawTowardsLink + 0x3A98;
    if ((this->actor.bgCheckFlags & 8) ||
        ((func_800339B8(&this->actor, globalCtx, this->actor.speedXZ, this->actor.shape.rot.y + 0x3E80) == 0))) {
        s16 tmp;

        if (this->actor.bgCheckFlags & 8) {
            tmp = (this->actor.speedXZ >= 0.0f) ? this->actor.shape.rot.y + 0x3E80 : this->actor.shape.rot.y - 0x3E80;
            tmp = this->actor.wallPolyRot - tmp;
        } else {
            this->actor.speedXZ *= -0.8f;
            tmp = 0;
        }

        if (ABS(tmp) >= 0x4001) {
            func_80A38290(this);
            return;
        }
    }

    if (this->actor.xzDistFromLink <= 45.0f) {
        Math_SmoothScaleMaxMinF(&this->unk_304, -4.0f, 1.0f, 1.5f, 0.0f);
    } else if (this->actor.xzDistFromLink > 40.0f) {
        Math_SmoothScaleMaxMinF(&this->unk_304, 4.0f, 1.0f, 1.5f, 0.0f);
    } else {
        Math_SmoothScaleMaxMinF(&this->unk_304, 0.0f, 1.0f, 6.65f, 0.0f);
    }

    if (this->unk_304 != 0.0f) {
        this->actor.posRot.pos.x += Math_Sins(this->actor.yawTowardsLink) * this->unk_304;
        this->actor.posRot.pos.z += Math_Coss(this->actor.yawTowardsLink) * this->unk_304;
    }

    if (ABS(this->unk_304) < ABS(this->actor.speedXZ)) {
        this->skelAnime.animPlaybackSpeed = -this->actor.speedXZ * 0.5f;
    } else {
        this->skelAnime.animPlaybackSpeed = -this->unk_304 * 0.5f;
    }

    this->skelAnime.animPlaybackSpeed = CLAMP(this->skelAnime.animPlaybackSpeed, -3.0f, 3.0f);
    sp28 = this->skelAnime.animCurrentFrame;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    tmp2 = this->skelAnime.animCurrentFrame - ABS(this->skelAnime.animPlaybackSpeed);
    tmp3 = ABS(this->skelAnime.animPlaybackSpeed);

    if ((s32)this->skelAnime.animCurrentFrame != sp28) {
        if (((tmp2 < 0) && (((s32)tmp3 + sp28) > 0)) || ((tmp2 < 5) && (((s32)tmp3 + sp28) > 5))) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_MUSI_LAND);
        }
    }

    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_BREATH);
    }

    this->unk_300--;
    if (this->unk_300 == 0) {
        this->actor.shape.rot.y = this->actor.yawTowardsLink;
        if (func_80A39E2C(globalCtx, this) == 0) {
            if ((func_80033AB8(globalCtx, &this->actor) == 0) && (this->actor.xzDistFromLink <= 70.0f)) {
                func_80A37670(this);
            } else {
                func_80A37D70(this);
            }
        }
    } else if (this->actor.speedXZ >= 0.0f) {
        this->actor.shape.rot.y += 0x4000;
    } else {
        this->actor.shape.rot.y -= 0x4000;
    }
}

void func_80A37670(EnGeldB* this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_060003CC);
    this->collider2.base.atFlags &= ~4;
    this->unk_2EC = 7;
    this->unk_312 = 0;
    this->actor.speedXZ = 0.0f;
    func_800F8A44(&this->actor.projectedPos, NA_SE_EN_GERUDOFT_BREATH);
    EnGeldB_SetupAction(this, func_80A376E0);
}

void func_80A376E0(EnGeldB* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 sp22;
    s16 sp20;
    s16 rot;
    s32 frame;

    rot = this->actor.shape.rot.y;
    sp22 = player->actor.shape.rot.y - rot;
    sp20 = this->actor.yawTowardsLink - rot;

    if (sp22 < 0) {
        if (this) {};
        sp22 = -sp22;
    }

    if (sp20 < 0) {
        if (this) {};
        sp20 = -sp20;
    }

    this->actor.speedXZ = 0.0f;
    frame = this->skelAnime.animCurrentFrame;
    if (frame == 1) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_ATTACK);
        this->unk_310 = 1;
    } else if (frame == 6) {
        this->unk_310 = -1;
    }

    if (this->collider2.base.atFlags & 4) {
        this->unk_310 = -1;
        this->collider2.base.atFlags &= ~6;
        func_80A37D70(this);
        return;
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        if (func_8002E084(&this->actor, 0x1554) == 0) {
            func_80A35D48(this);
            this->unk_300 = (Math_Rand_ZeroOne() * 5.0f) + 5.0f;
            if (sp20 >= 0x4001) {
                this->unk_2FA = 0x14;
            }
            return;
        } else if ((Math_Rand_ZeroOne() > 0.7f) || (this->actor.xzDistFromLink >= 120.0f)) {
            func_80A35D48(this);
            this->unk_300 = (Math_Rand_ZeroOne() * 5.0f) + 5.0f;
            return;
        }

        this->actor.posRot.rot.y = this->actor.yawTowardsLink;
        if (Math_Rand_ZeroOne() > 0.7f) {
            func_80A387D0(this, globalCtx);
        } else if (sp22 < 0x2711) {
            if (sp20 >= 0x3E81) {
                this->actor.posRot.rot.y = this->actor.yawTowardsLink;
                func_80A36A10(this);
            } else {
                func_80A3559C(globalCtx, this, 1);
            }
        } else {
            func_80A36A10(this);
        }
    }
}

void func_80A3792C(EnGeldB* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000F5C, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06000F5C.genericHeader),
                         3, 0.0f);
    this->collider2.base.atFlags &= ~6;
    this->unk_2EC = 0xC;
    this->unk_312 = 0;
    this->actor.speedXZ = 0.0f;
    EnGeldB_SetupAction(this, func_80A379C0);
}

void func_80A379C0(EnGeldB* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 rot;
    s16 tmp;
    s32 frame;

    if (this->unk_312 < 2) {
        if (this->collider2.base.atFlags & 4) {
            this->collider2.base.atFlags &= ~6;
            this->unk_312 = 1;
            this->skelAnime.animPlaybackSpeed = 1.5f;
        } else if (this->collider2.base.atFlags & 2) {
            this->collider2.base.atFlags &= ~2;
            if (this->collider2.base.at == &player->actor) {
                func_8002F71C(globalCtx, &this->actor, 6.0f, this->actor.yawTowardsLink, 6.0f);
                this->unk_312 = 2;
                func_8002DF54(globalCtx, &this->actor, 0x18);
                func_8010B680(globalCtx, 0x6003, &this->actor);
                this->unk_300 = 30;
                this->actor.speedXZ = 0.0f;
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_YOUNG_LAUGH);
                return;
            }
        }
    }

    frame = this->skelAnime.animCurrentFrame;
    if (frame < 9) {
        this->actor.shape.rot.y = this->actor.posRot.rot.y = this->actor.yawTowardsLink;
    } else if (frame == 13) {
        func_80033260(globalCtx, &this->actor, &this->unk_4D0, 3.0f, 2, 2.0f, 0, 0, 0);
        func_80033260(globalCtx, &this->actor, &this->unk_4C4, 3.0f, 2, 2.0f, 0, 0, 0);
        this->unk_310 = 1;
        this->actor.speedXZ = 10.0f;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_ATTACK);
    } else if (frame == 21) {
        this->actor.speedXZ = 0.0f;
    } else if (frame == 24) {
        this->unk_310 = -1;
    }

    if ((SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) && (this->unk_312 < 2)) {
        if (func_8002E084(&this->actor, 0x1554) == 0) {
            func_80A35D48(this);
            this->unk_300 = (Math_Rand_ZeroOne() * 5.0f) + 5.0f;
            this->unk_2FA = 0x2E;
            return;
        }

        if (this->unk_312 != 0) {
            func_80A37D70(this);
            return;
        }

        if ((Math_Rand_ZeroOne() > 0.7f) || (this->actor.xzDistFromLink) >= 120.0f) {
            func_80A35D48(this);
            this->unk_300 = (Math_Rand_ZeroOne() * 5.0f) + 5.0f;
            return;
        }

        this->actor.posRot.rot.y = this->actor.yawTowardsLink;
        if (Math_Rand_ZeroOne() > 0.7f) {
            func_80A387D0(this, globalCtx);
            return;
        }

        tmp = this->actor.shape.rot.y;
        rot = player->actor.shape.rot.y - tmp;
        if (rot < 0) {
            rot = -rot;
        }

        if (rot < 0x2711) {
            rot = this->actor.yawTowardsLink - tmp;
            if (rot < 0) {
                rot = -rot;
            }

            if (rot >= 0x3E81) {
                this->actor.posRot.rot.y = this->actor.yawTowardsLink;
                func_80A36A10(this);
            } else {
                func_80A3559C(globalCtx, this, 1);
            }
        } else {
            func_80A36A10(this);
        }
    }
}

void func_80A37D70(EnGeldB* this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06001390, -3.0f);
    this->unk_300 = 0;
    this->unk_318 = 1;
    this->unk_2EC = 4;
    this->actor.speedXZ = -8.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL_JUMP);
    this->actor.posRot.rot.y = this->actor.yawTowardsLink;
    this->actor.shape.rot.y = this->actor.yawTowardsLink;
    EnGeldB_SetupAction(this, func_80A37DEC);
}

void func_80A37DEC(EnGeldB* this, GlobalContext* globalCtx) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        if ((func_80033AB8(globalCtx, &this->actor) == 0) && (this->actor.xzDistFromLink < 170.0f) &&
            (this->actor.xzDistFromLink > 140.0f) && (Math_Rand_ZeroOne() < 0.2f)) {
            func_80A3792C(this);
        } else if ((globalCtx->gameplayFrames & 1) != 0) {
            func_80A387D0(this, globalCtx);
        } else {
            func_80A35D48(this);
        }
    }

    if ((globalCtx->state.frames & 0x5F) == 0) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_BREATH);
    }
}

void func_80A37EF0(EnGeldB* this) {
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = 0.0f;
    }

    if (((this->unk_2FE != 15) || this->unk_2EC == 12)) {
        SkelAnime_ChangeAnimPlaybackStop(&this->skelAnime, &D_06002280, 0.0f);
    }

    if (this->unk_2FE == 15) {
        this->unk_2FC = 0x24;
    }

    Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_FREEZE);
    this->unk_2EC = 15;
    EnGeldB_SetupAction(this, func_80A37F98);
}

void func_80A37F98(EnGeldB* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 2) {
        this->actor.speedXZ = 0.0f;
    }

    if (this->actor.bgCheckFlags & 1) {
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ += 0.05f;
        }

        this->unk_318 = 0;
    }

    if ((this->actor.dmgEffectTimer == 0) && (this->actor.bgCheckFlags & 1)) {
        if (this->actor.colChkInfo.health == 0) {
            func_80A3907C(this);
        } else {
            func_80A3559C(globalCtx, this, 1);
        }
    }
}

void func_80A38054(EnGeldB* this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06002280, -4.0f);
    if (this->actor.bgCheckFlags & 1) {
        this->unk_318 = 0;
        this->actor.speedXZ = -4.0f;
    } else {
        this->unk_318 = 1;
    }

    this->unk_2FA = 0;
    this->actor.posRot.rot.y = this->actor.yawTowardsLink;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_DAMAGE);
    this->unk_2EC = 2;
    EnGeldB_SetupAction(this, func_80A380EC);
}

void func_80A380EC(EnGeldB* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 2) {
        this->actor.speedXZ = 0.0f;
    }

    if (this->actor.bgCheckFlags & 1) {
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ += 0.05f;
        }

        this->unk_318 = 0;
    }

    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 1, 0x1194, 0);
    if ((func_80A39E2C(globalCtx, this) == 0) && (func_80A3559C(globalCtx, this, 0) == 0) &&
        (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0)) {
        if (this->actor.bgCheckFlags & 1) {
            s16 tmp = this->actor.wallPolyRot - this->actor.shape.rot.y;
            if ((this->actor.bgCheckFlags & 8) && (ABS(tmp) < 0x2EE0)) {
                if (this->actor.xzDistFromLink < 90.0f) {
                    func_80A38290(this);
                    return;
                }
            }

            if (func_80A39E2C(globalCtx, this) == 0) {
                if ((this->actor.xzDistFromLink <= 45.0f) && (func_80033AB8(globalCtx, &this->actor) == 0) &&
                    ((globalCtx->gameplayFrames & 7) != 0)) {
                    func_80A37670(this);
                } else {
                    func_80A37D70(this);
                }
            }
        }
    }
}

void func_80A38290(EnGeldB* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06001390, -1.0f, SkelAnime_GetFrameCount(&D_06001390.genericHeader), 0.0f,
                         2, -3.0f);
    this->unk_300 = 0;
    this->unk_318 = 0;
    this->unk_2EC = 3;
    this->actor.speedXZ = 6.5f;
    this->actor.velocity.y = 15.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL_JUMP);
    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    EnGeldB_SetupAction(this, func_80A38348);
}

void func_80A38348(EnGeldB* this, GlobalContext* globalCtx) {
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 1, 0xFA0, 1);
    if (this->actor.velocity.y >= 5.0f) {
        func_800355B8(globalCtx, &this->unk_4D0);
        func_800355B8(globalCtx, &this->unk_4C4);
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        if ((this->actor.bgCheckFlags & 3) != 0) {
            this->actor.shape.rot.x = 0;
            this->actor.shape.rot.y = this->actor.yawTowardsLink;
            this->actor.posRot.rot.y = this->actor.yawTowardsLink;
            this->actor.speedXZ = 0.0f;
            this->actor.velocity.y = 0.0f;
            this->actor.posRot.pos.y = this->actor.groundY;
            if (func_80033AB8(globalCtx, &this->actor) == 0) {
                func_80A37670(this);
            } else {
                func_80A35D48(this);
            }
        }
    }
}

void func_80A38430(EnGeldB* this) {
    f32 frame = SkelAnime_GetFrameCount(&D_06001578.genericHeader);

    if (this->unk_310 != 0) {
        this->unk_310 = -1;
    }

    this->actor.speedXZ = 0.0f;
    this->unk_2EC = 6;
    this->unk_300 = (s32)Math_Rand_CenteredFloat(10.0f) + 10;
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06001578, 0.0f, 0.0f, frame, 2, 0.0f);
    EnGeldB_SetupAction(this, func_80A384E8);
}

void func_80A384E8(EnGeldB* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 rot;
    s16 tmp;
    s16 pad;
    s16 tmp2;

    if (this->unk_300 != 0) {
        this->unk_300--;
    } else {
        this->skelAnime.animPlaybackSpeed = 1.0f;
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        rot = this->actor.shape.rot.y;
        tmp = this->actor.yawTowardsLink - rot;
        if ((ABS(tmp) < 0x4001) && (this->actor.xzDistFromLink < 40.0f) && (ABS(this->actor.yDistFromLink) < 50.0f)) {
            if (func_800354B4(globalCtx, &this->actor, 100.0f, 0x2710, 0x4000, rot) != 0) {
                if (player->swordAnimation == 17) {
                    func_80A370BC(this, globalCtx);
                } else if ((globalCtx->gameplayFrames & 1) != 0) {
                    func_80A38430(this);
                } else {
                    func_80A37D70(this);
                }
                return;
            }

            tmp2 = player->actor.shape.rot.y - this->actor.shape.rot.y;
            if ((func_80033AB8(globalCtx, &this->actor) == 0) &&
                (((globalCtx->gameplayFrames & 1) != 0) || (ABS(tmp2) < 0x38E0))) {
                func_80A37670(this);
            } else {
                func_80A36A10(this);
            }
        } else {
            func_80A36A10(this);
        }
        return;
    }

    if ((this->unk_300 == 0) &&
        (func_800354B4(globalCtx, &this->actor, 100.0f, 0x2710, 0x4000, this->actor.shape.rot.y) != 0)) {
        if (player->swordAnimation == 17) {
            func_80A370BC(this, globalCtx);
            return;
        }

        if (func_80A39E2C(globalCtx, this) == 0) {
            if (globalCtx->gameplayFrames & 1) {
                if ((this->actor.xzDistFromLink < 100.0f) && Math_Rand_ZeroOne() > 0.7f) {
                    func_80A38290(this);
                } else {
                    func_80A37D70(this);
                }
            } else {
                func_80A38430(this);
            }
        }
    }
}

void func_80A387D0(EnGeldB* this, GlobalContext* globalCtx) {
    s16 tmp;
    Player* player;

    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600A814, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_0600A814.genericHeader),
                         1, 0.0f);
    player = PLAYER;
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 1, 0xFA0, 1);
    tmp = player->actor.shape.rot.y;
    if (Math_Sins(tmp - this->actor.shape.rot.y) > 0.0f) {
        this->actor.speedXZ = -6.0f;
    } else if (Math_Sins(tmp - this->actor.shape.rot.y) < 0.0f) {
        this->actor.speedXZ = 6.0f;
    } else {
        this->actor.speedXZ = Math_Rand_CenteredFloat(12.0f);
    }

    this->actor.posRot.rot.y = this->actor.shape.rot.y + 0x3FFF;
    this->skelAnime.animPlaybackSpeed = -this->actor.speedXZ * 0.5f;
    this->unk_304 = 0.0f;
    this->unk_300 = (Math_Rand_ZeroOne() * 10.0f) + 5.0f;
    this->unk_2EC = 0xD;
    EnGeldB_SetupAction(this, func_80A38960);
}

#ifdef NON_MATCHING
// Main issue is sp30 not constantly loaded and saved
// The whole ABS part may still be wrong, copying other functions where I matched it
void func_80A38960(EnGeldB* this, GlobalContext* globalCtx) {
    s16 sp56;
    Player* player = PLAYER;
    s32 sp4C;
    s32 sp48;
    s16 tmp;
    f32 sp30;

    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 1, 0xBB8, 1);
    sp56 = player->actor.shape.rot.y + 0x8000;
    if (Math_Sins(sp56 - this->actor.shape.rot.y) > 0.0f) {
        this->actor.speedXZ = this->actor.speedXZ + 0.125f;
    } else if (Math_Sins(sp56 - this->actor.shape.rot.y) <= 0.0f) {
        this->actor.speedXZ = this->actor.speedXZ - 0.125f;
    }

    if ((this->actor.bgCheckFlags & 8) ||
        !func_800339B8(&this->actor, globalCtx, this->actor.speedXZ, this->actor.shape.rot.y + 0x3E80)) {
        if (this->actor.bgCheckFlags & 8) {
            tmp = (this->actor.speedXZ >= 0.0f) ? this->actor.shape.rot.y + 0x3E80 : this->actor.shape.rot.y - 0x3E80;
            tmp = this->actor.wallPolyRot - tmp;
        } else {
            this->actor.speedXZ *= -0.8f;
            tmp = 0;
        }

        if (ABS(tmp) >= 0x4001) {
            this->actor.speedXZ *= -0.8f;
            if (this->actor.speedXZ < 0.0f) {
                this->actor.speedXZ -= 0.5f;
            } else {
                this->actor.speedXZ += 0.5f;
            }
        }
    }

    if (this->actor.speedXZ <= 0.0f) {
        this->actor.posRot.rot.y = this->actor.shape.rot.y + 0x3E80;
    } else {
        this->actor.posRot.rot.y = this->actor.shape.rot.y - 0x3E80;
    }

    if (this->actor.xzDistFromLink <= 45.0f) {
        Math_SmoothScaleMaxMinF(&this->unk_304, -4.0f, 1.0f, 1.5f, 0.0f);
    } else if (this->actor.xzDistFromLink > 40.0f) {
        Math_SmoothScaleMaxMinF(&this->unk_304, 4.0f, 1.0f, 1.5f, 0.0f);
    } else {
        Math_SmoothScaleMaxMinF(&this->unk_304, 0.0f, 1.0f, 6.65f, 0.0f);
    }

    if (this->unk_304 != 0.0f) {
        this->actor.posRot.pos.x += Math_Sins(this->actor.shape.rot.y) * this->unk_304;
        this->actor.posRot.pos.z += Math_Coss(this->actor.shape.rot.y) * this->unk_304;
    }

    if (ABS(this->unk_304) < ABS(this->actor.speedXZ)) {
        this->skelAnime.animPlaybackSpeed = -this->actor.speedXZ * 0.5f;
    } else {
        this->skelAnime.animPlaybackSpeed = -this->unk_304 * 0.5f;
    }

    this->skelAnime.animPlaybackSpeed = CLAMP(this->skelAnime.animPlaybackSpeed, -3.0f, 3.0f);

    sp4C = this->skelAnime.animCurrentFrame;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    // sp30 = ABS(this->skelAnime.animPlaybackSpeed);
    sp48 = this->skelAnime.animCurrentFrame - ABS(this->skelAnime.animPlaybackSpeed);
    sp30 = ABS(this->skelAnime.animPlaybackSpeed);

    if (func_80A39E2C(globalCtx, this) || func_80A3559C(globalCtx, this, 0)) {
        return;
    }

    this->unk_300--;
    if (this->unk_300 == 0) {
        s16 rot = this->actor.shape.rot.y;
        s16 tmp4 = player->actor.shape.rot.y - rot;
        if (tmp4 < 0) {
            tmp4 = -tmp4;
        }

        if (tmp4 >= 0x3A98) {
            func_80A35D48(this);
            this->unk_300 = (Math_Rand_ZeroOne() * 5.0f) + 1.0f;
        } else {
            s16 tmp5;
            this->actor.posRot.rot.y = rot;
            tmp5 = PLAYER->actor.shape.rot.y - rot;

            if ((this->actor.xzDistFromLink <= 45.0f) && (func_80033AB8(globalCtx, &this->actor) == 0) &&
                (((globalCtx->gameplayFrames % 4) != 0) || (ABS(tmp5) < 0x38E0))) {
                func_80A37670(this);
            } else if ((this->actor.xzDistFromLink < 210.0f) && (this->actor.xzDistFromLink > 150.0f) &&
                       ((globalCtx->gameplayFrames & 1) == 0)) {
                if (sp30) {};
                if ((func_80033AB8(globalCtx, &this->actor) == 0) ||
                    ((Math_Rand_ZeroOne() > 0.5f) || (ABS(tmp5) < 0x38E0))) {
                    func_80A365DC(this);
                } else {
                    func_80A3792C(this);
                }
            } else {
                func_80A360B0(this, globalCtx);
            }
        }
    }

    if (sp4C != (s32)this->skelAnime.animCurrentFrame) {
        if (((sp48 < 0) && (((s32)sp30 + sp4C) > 0)) || ((sp48 < 5) && (((s32)sp30 + sp4C) > 5))) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_MUSI_LAND);
        }
    }

    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_BREATH);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_GeldB/func_80A38960.s")
#endif

void func_80A3907C(EnGeldB* this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06001E10, -4.0f);
    this->actor.shape.rot.y = this->actor.yawTowardsLink;
    this->actor.posRot.rot.y = this->actor.yawTowardsLink;
    if (this->actor.bgCheckFlags & 1) {
        this->unk_318 = 0;
        this->actor.speedXZ = -6.0f;
    } else {
        this->unk_318 = 1;
    }

    this->unk_2EC = 1;
    this->actor.flags &= ~1;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_DEAD);
    EnGeldB_SetupAction(this, func_80A39120);
}

void func_80A39120(EnGeldB* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 2) {
        this->actor.speedXZ = 0.0f;
    }

    if (this->actor.bgCheckFlags & 1) {
        Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 1.0f, 0.5f, 0.0f);
        this->unk_318 = 0;
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        func_80A35B8C(this);
    } else if ((s32)this->skelAnime.animCurrentFrame == 10) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_DOWN);
        func_800F5B58();
    }
}

void func_80A391D8(EnGeldB* this, GlobalContext* globalCtx) {
    if ((this->unk_2EC == 5) && (this->unk_2FA != 0)) {
        this->unk_4DE = Math_Sins(this->unk_2FA * 4200) * 8920.0f;
        return;
    }

    if (this->unk_2EC != 0xF) {
        if ((this->unk_2EC != 7) && (this->unk_2EC != 12)) {
            Math_SmoothScaleMaxMinS(&this->unk_4DE, this->actor.yawTowardsLink - this->actor.shape.rot.y, 1, 0x1F4, 0);
            this->unk_4DE = CLAMP(this->unk_4DE, -0x256F, 0x256F);
        } else {
            this->unk_4DE = 0;
        }
    }
}

void func_80A392D8(EnGeldB* this, GlobalContext* globalCtx) {
    u8 dmgEff;

    if (this->collider3.base.acFlags & 0x80) {
        this->collider3.base.acFlags &= ~0x80;
        this->collider1.base.acFlags &= ~2;
        return;
    }

    if ((this->collider1.base.acFlags & 2) && (this->unk_2EC >= 5) && (this->unk_312 < 2)) {
        this->collider1.base.acFlags &= ~2;
        if (this->actor.colChkInfo.damageEffect != 6) {
            this->unk_2FE = this->actor.colChkInfo.damageEffect;
            func_80035650(&this->actor, &this->collider1.body, 1);
            func_800F8A44(&this->actor.projectedPos, NA_SE_EN_GERUDOFT_BREATH);
            dmgEff = this->actor.colChkInfo.damageEffect;
            if ((dmgEff == 1) || (dmgEff == 15)) {
                if (this->unk_2EC != 15) {
                    func_8003426C(&this->actor, 0, 0x78, 0, 0x50);
                    Actor_ApplyDamage(&this->actor);
                    func_80A37EF0(this);
                }
            } else {
                func_8003426C(&this->actor, 0x4000, 0xFF, 0, 8);
                if (Actor_ApplyDamage(&this->actor) == 0) {
                    if (this->unk_314 != 0) {
                        EnItem00* item = Item_DropCollectible(globalCtx, &this->actor.posRot.pos, this->unk_314 | 0x11);
                        if (item != NULL) {
                            item->actor.posRot.rot.y =
                                Math_Vec3f_Yaw(&item->actor.posRot.pos, &this->actor.initPosRot.pos);
                            item->actor.speedXZ = 6.0f;
                            Audio_PlaySoundGeneral(NA_SE_SY_TRE_BOX_APPEAR, &D_801333D4, 4, &D_801333E0, &D_801333E0,
                                                   &D_801333E8);
                        }
                    }
                    func_80A3907C(this);
                    func_80032C7C(globalCtx, &this->actor);
                } else {
                    func_80A38054(this);
                }
            }
        }
    }
}

void EnGeldB_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGeldB* this = THIS;
    s32 pad;

    func_80A392D8(this, globalCtx);
    if (this->actor.colChkInfo.damageEffect != 6) {
        Actor_MoveForward(&this->actor);
        func_8002E4B4(globalCtx, &this->actor, 15.0f, 30.0f, 60.0f, 0x1D);
        this->actionFunc(this, globalCtx);
        this->actor.posRot2.pos = this->actor.posRot.pos;
        this->actor.posRot2.pos.y += 40.0f;
        func_80A391D8(this, globalCtx);
    }

    Collider_CylinderUpdate(&this->actor, &this->collider1);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    if ((this->unk_2EC >= 5) && (this->unk_312 < 2)) {
        if ((this->actor.dmgEffectTimer == 0) || !(this->actor.dmgEffectParams & 0x4000)) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        }
    }

    if ((this->unk_2EC == 6) && (this->skelAnime.animCurrentFrame == 0.0f)) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
    }

    if (this->unk_310 > 0) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    }

    if (this->unk_31A == 0) {
        if ((Math_Rand_ZeroOne() < 0.1f) && ((globalCtx->gameplayFrames & 3) == 0)) {
            this->unk_31A++;
        }
    } else {
        this->unk_31A = (this->unk_31A + 1) & 3;
    }
}

s32 func_80A39688(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGeldB* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_geldB.c", 2507);
    if (limbIndex == 3) {
        rot->z += this->unk_4DC;
        rot->x += this->unk_4DE;
        rot->y += this->unk_4E0;
    } else if (limbIndex == 6) {
        gDPPipeSync(gfxCtx->polyOpa.p++);
        gDPSetEnvColor(gfxCtx->polyOpa.p++, 80, 60, 10, 255);
    } else if ((limbIndex == 11) || (limbIndex == 16)) {
        gDPPipeSync(gfxCtx->polyOpa.p++);
        gDPSetEnvColor(gfxCtx->polyOpa.p++, 140, 170, 230, 255);
        gDPSetPrimColor(gfxCtx->polyOpa.p++, 0, 0, 255, 255, 255, 255);
    } else {
        gDPPipeSync(gfxCtx->polyOpa.p++);
        gDPSetEnvColor(gfxCtx->polyOpa.p++, 140, 0, 0, 255);
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_geldB.c", 2529);
    return 0;
}

void func_80A39824(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80A3A11C = { 300.0f, 0.0f, 0.0f };
    static Vec3f D_80A3A128 = { 0.0f, -3000.0f, 0.0f };
    static Vec3f D_80A3A134 = { 400.0f, 0.0f, 0.0f };
    static Vec3f D_80A3A140 = { 1600.0f, -4000.0f, 0.0f };
    static Vec3f D_80A3A14C = { -3000.0f, -2000.0f, 1300.0f };
    static Vec3f D_80A3A158 = { -3000.0f, -2000.0f, -1300.0f };
    static Vec3f D_80A3A164 = { 1000.0f, 1000.0f, 0.0f };
    static Vec3f D_80A3A170 = { 0.0f, 0.0f, 0.0f };

    Vec3f sp5C;
    Vec3f sp50;
    EnGeldB* this = THIS;
    s32 tmp = -1;
    Vec3f sp3C;

    if (limbIndex == 0xB) {
        Matrix_MultVec3f(&D_80A3A140, &this->collider2.dim.quad[1]);
        Matrix_MultVec3f(&D_80A3A14C, &this->collider2.dim.quad[0]);
        Matrix_MultVec3f(&D_80A3A158, &this->collider2.dim.quad[3]);
        Matrix_MultVec3f(&D_80A3A164, &this->collider2.dim.quad[2]);
        func_80062734(&this->collider2, &this->collider2.dim.quad[0], &this->collider2.dim.quad[1],
                      &this->collider2.dim.quad[2], &this->collider2.dim.quad[3]);
        Matrix_MultVec3f(&D_80A3A128, &sp5C);
        Matrix_MultVec3f(&D_80A3A134, &sp50);

        if ((this->unk_310 < 0) || ((this->unk_2EC != 7) && (this->unk_2EC != 12))) {
            EffectBlure_AddSpace(Effect_GetByIndex(this->unk_31C));
            this->unk_310 = 0;
        } else if (this->unk_310 > 0) {
            EffectBlure_AddVertex(Effect_GetByIndex(this->unk_31C), &sp5C, &sp50);
        }
    } else {
        func_8002BDB0(&this->actor, limbIndex, 19, &D_80A3A11C, 0x16, &D_80A3A11C);
    }

    if (limbIndex == 19) {
        Matrix_MultVec3f(&D_80A3A11C, &this->unk_4D0);
    } else if (limbIndex == 22) {
        Matrix_MultVec3f(&D_80A3A11C, &this->unk_4C4);
    }

    if (this->unk_2FC != 0) {
        switch (limbIndex) {
            case 3:
                tmp = 0;
                break;
            case 16:
                tmp = 1;
                break;
            case 11:
                tmp = 2;
                break;
            case 12:
                tmp = 3;
                break;
            case 7:
                tmp = 4;
                break;
            case 2:
                tmp = 5;
                break;
            case 23:
                tmp = 6;
                break;
            case 19:
                tmp = 7;
                break;
            case 22:
                tmp = 8;
                break;
        }

        if (tmp >= 0) {
            Matrix_MultVec3f(&D_80A3A170, &sp3C);
            this->unk_14C[tmp].x = sp3C.x;
            this->unk_14C[tmp].y = sp3C.y;
            this->unk_14C[tmp].z = sp3C.z;
        }
    }
}

#ifdef NON_MATCHING
// Something with 2FC or the func_8002A1DC call
void EnGeldB_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Vec3f D_80A3A17C[] = {
        { -3000.0f, 6000.0f, 1600.0f },
        { -3000.0f, 0.0f, 1600.0f },
        { 3000.0f, 6000.0f, 1600.0f },
    };

    static Vec3f D_80A3A1A0[] = {
        { -3000.0f, 0.0f, 1600.0f },
        { 3000.0f, 0.0f, 1600.0f },
        { 3000.0f, 6000.0f, 1600.0f },
    };

    static UNK_TYPE D_80A3A1C4[] = { 0x06005FE8, 0x060065A8, 0x06006D28, 0x060065A8 };

    EnGeldB* this = THIS;
    Vec3f sp90[3];
    Vec3f sp6C[3];
    s32 i;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_geldB.c", 2672);
    if ((this->unk_312 >= 2) && (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0)) {
        if (this->unk_312 == 2) {
            SkelAnime_ChangeAnim(&this->skelAnime, &D_06000F5C, 0.5f, 0.0f, 12.0f, 3, 4.0f);
            this->actor.shape.rot.y = this->actor.yawTowardsLink;
            this->actor.posRot.rot.y = this->actor.yawTowardsLink;
            this->unk_312++;
        } else {
            this->unk_300--;
            if (this->unk_300 == 0) {
                if ((INV_CONTENT(ITEM_HOOKSHOT) == ITEM_NONE) || (INV_CONTENT(ITEM_LONGSHOT) == ITEM_NONE)) {
                    globalCtx->nextEntranceIndex = 0x1A5;
                } else if (gSaveContext.eventChkInf[12] & 0x80) {
                    globalCtx->nextEntranceIndex = 0x5F8;
                } else {
                    globalCtx->nextEntranceIndex = 0x3B4;
                }

                globalCtx->fadeTransition = 0x26;
                globalCtx->sceneLoadFlag = 0x14;
            }
        }
    }

    if ((this->unk_2EC != 0) || (this->unk_318 == 0)) {
        do {
            func_80093D18(globalCtx->state.gfxCtx);
        } while (0);
        gSPSegment(gfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A3A1C4[this->unk_31A]));

        SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                         func_80A39688, func_80A39824, &this->actor);
        if (this->unk_2EC == 6) {
            for (i = 0; i < 4; i++) {
                Matrix_MultVec3f(&D_80A3A17C[i], &sp90[i]);
                Matrix_MultVec3f(&D_80A3A1A0[i], &sp6C[i]);
            }

            func_800627A0(&this->collider3, 0, &sp90[0], &sp90[1], &sp90[2]);
            func_800627A0(&this->collider3, 1, &sp6C[0], &sp6C[1], &sp6C[2]);
        }

        if (this->unk_2FC != 0) {
            this->actor.dmgEffectTimer++;
            this->unk_2FC--;
            if ((this->unk_2FC & 3) == 0) {
                func_8002A1DC(globalCtx, &this->actor, &this->unk_14C[this->unk_2FC >> 2], 0x96, 0x96, 0x96, 0xFA, 0xEB,
                              0xF5, 0xFF, 1.5f);
            }
        }
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_geldB.c", 2744);
}
#else
Vec3f D_80A3A17C[] = {
    { -3000.0f, 6000.0f, 1600.0f },
    { -3000.0f, 0.0f, 1600.0f },
    { 3000.0f, 6000.0f, 1600.0f },
};

Vec3f D_80A3A1A0[] = {
    { -3000.0f, 0.0f, 1600.0f },
    { 3000.0f, 0.0f, 1600.0f },
    { 3000.0f, 6000.0f, 1600.0f },
};
UNK_TYPE D_80A3A1C4[] = { 0x06005FE8, 0x060065A8, 0x06006D28, 0x060065A8 };
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_GeldB/EnGeldB_Draw.s")
#endif

#ifdef NON_MATCHING
// Regalloc on shape.rot.y, shouldn't be in v1
s32 func_80A39E2C(GlobalContext* globalCtx, EnGeldB* this) {
    Actor* refActor = (Actor*)func_80033780(globalCtx, &this->actor, 800.0f);
    s16 tmp;
    f32 tmpf1;

    if (refActor != NULL) {
        tmp = func_8002DA78(&this->actor, refActor) - this->actor.shape.rot.y;
        this->actor.posRot.rot.y = this->actor.shape.rot.y;
        tmpf1 = func_8002DB6C(&this->actor, &refActor->posRot.pos);

        if ((ABS(tmp) < 0x2EE0) && (sqrt(tmpf1) < 600.0)) {
            if (refActor->id == ACTOR_ARMS_HOOK) {
                func_80A38290(this);
            } else {
                func_80A38430(this);
            }
        } else {
            this->actor.posRot.rot.y = this->actor.shape.rot.y + 0x3FFF;
            if ((ABS(tmp) < 0x2000) || (ABS(tmp) > 0x5FFF)) {
                func_80A387D0(this, globalCtx);
                this->actor.speedXZ *= 3.0f;
            } else if (ABS(tmp) < 0x5FFF) {
                func_80A37D70(this);
            }
        }
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_GeldB/func_80A39E2C.s")
#endif
