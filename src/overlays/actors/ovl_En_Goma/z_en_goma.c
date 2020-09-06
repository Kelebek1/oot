/*
 * File: z_en_goma.c
 * Overlay: ovl_En_Goma
 * Description: Gohma Larva
 */

#include "z_en_goma.h"
#include "overlays/actors/ovl_Boss_Goma/z_boss_goma.h"

#define FLAGS 0x00000035

#define THIS ((EnGoma*)thisx)

void EnGoma_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGoma_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGoma_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGoma_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A49338(EnGoma* this, GlobalContext* globalCtx);
void func_80A493D8(EnGoma* this, GlobalContext* globalCtx);
void func_80A49668(EnGoma* this, GlobalContext* globalCtx);
void func_80A498A8(EnGoma* this, GlobalContext* globalCtx);
void func_80A49974(EnGoma* this, GlobalContext* globalCtx);
void func_80A49AA8(EnGoma* this, GlobalContext* globalCtx);
void func_80A49BF0(EnGoma* this, GlobalContext* globalCtx);
void func_80A49D0C(EnGoma* this, GlobalContext* globalCtx);
void func_80A4A010(EnGoma* this, GlobalContext* globalCtx);
void func_80A4A120(EnGoma* this, GlobalContext* globalCtx);
void func_80A4A234(EnGoma* this, GlobalContext* globalCtx);
void func_80A4A2EC(EnGoma* this, GlobalContext* globalCtx);
void func_80A4A368(EnGoma* this, GlobalContext* globalCtx);
void func_80A4B3AC(EnGoma* this, GlobalContext* globalCtx);
void func_80A4B3F0(EnGoma* this, GlobalContext* globalCtx);
void func_80A4A50C(EnGoma* this, GlobalContext* globalCtx);
void func_80A4B554(EnGoma* this, GlobalContext* globalCtx);
void func_80A49B30(EnGoma* this);
void func_80A49C94(EnGoma* this);
void func_80A49E80(EnGoma* this);
void func_80A4A18C(EnGoma* this);
u8 func_800635D0(s32);

const ActorInit En_Goma_InitVars = {
    ACTOR_BOSS_GOMA,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_GOL,
    sizeof(EnGoma),
    (ActorFunc)EnGoma_Init,
    (ActorFunc)EnGoma_Destroy,
    (ActorFunc)EnGoma_Update,
    (ActorFunc)EnGoma_Draw,
};

extern Gfx D_05000530[];
extern AnimationHeader D_0600017C;
extern AnimationHeader D_06000334;
extern AnimationHeader D_06000544;
extern AnimationHeader D_06000838;
extern AnimationHeader D_06000B78;
extern AnimationHeader D_06000E4C;
extern AnimationHeader D_06001548;
extern Gfx D_06002A70[];
extern SkeletonHeader D_06003B40;
extern AnimationHeader D_06003D78;

static ColliderCylinderInit D_80A4B7A0 = {
    { COLTYPE_UNK3, 0x11, 0x00, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x08 }, { 0xFFDFFFFF, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
    { 15, 30, 10, { 0, 0, 0 } },
};

static ColliderCylinderInit D_80A4B7CC = {
    { COLTYPE_UNK3, 0x00, 0x09, 0x00, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x08 }, { 0xFFDFFFFF, 0x00, 0x00 }, 0x00, 0x01, 0x00 },
    { 15, 30, 10, { 0, 0, 0 } },
};

static u8 D_80A4B7F8 = 0;

static Vec3f D_80A4B7FC = { 0.0f, 0.0f, 0.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(unk_1F, 3, ICHAIN_CONTINUE),
    ICHAIN_S8(naviEnemyId, 3, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 20, ICHAIN_STOP),
};

void EnGoma_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGoma* this = THIS;
    f32 tmp;

    this->unk_2C0 = (Math_Rand_ZeroOne() * 200.0f);
    Actor_ProcessInitChain(&this->actor, sInitChain);
    Actor_SetScale(&this->actor, 0.01f);
    if (this->actor.params >= 100) {
        Actor_ChangeType(globalCtx, &globalCtx->actorCtx, &this->actor, 9);
        this->actionFunc = func_80A4B554;
        this->unk_2B8 = 3;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 0.0f);
        this->unk_2CC = this->actor.params + 150;
        this->actor.flags &= ~1;
    } else if (this->actor.params >= 10) {
        this->actor.gravity = -1.3f;
        this->actor.flags &= ~1;
        this->unk_2CC = 50;
        this->unk_2B8 = 2;
        this->unk_2D0 = 1.0f;
        this->actor.velocity.y = (Math_Rand_ZeroOne() * 5.0f) + 5.0f;
        this->actionFunc = func_80A4B3AC;
        this->actor.speedXZ = (Math_Rand_ZeroOne() * 2.3f) + 1.5f;
        this->unk_2CC = 30;
        this->actor.scale.x = (Math_Rand_ZeroOne() * 0.005f) + 0.01f;
        this->actor.scale.y = (Math_Rand_ZeroOne() * 0.005f) + 0.01f;
        this->actor.scale.z = (Math_Rand_ZeroOne() * 0.005f) + 0.01f;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 0.0f);
    } else {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 40.0f);
        SkelAnime_Init(globalCtx, &this->skelAnime, &D_06003B40, &D_06001548, this->limbDrawTable,
                       this->transitionDrawTable, 24);
        SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06001548);
        this->actor.colChkInfo.health = 2;
        if (this->actor.params < 3) {
            this->actionFunc = func_80A493D8;
            this->unk_2CA = 0xA;
            this->actor.speedXZ = 1.5f;
        } else if ((this->actor.params == 8) || (this->actor.params == 6)) {
            this->actionFunc = func_80A49668;
            this->unk_2C8 = D_80A4B7F8;
            D_80A4B7F8++;
        } else if ((this->actor.params == 9) || (this->actor.params == 7)) {
            this->actionFunc = func_80A49668;
        }

        if (this->actor.params >= 8) {
            this->unk_2F0 = -1500.0f;
        } else {
            this->unk_2F0 = 1500.0f;
        }

        this->unk_2B8 = 1;
        this->unk_2D0 = 1.0f;
        this->unk_2D8 = Math_Rand_ZeroOne() * 1000.0f;
        this->unk_2CC = 50;
        Collider_InitCylinder(globalCtx, &this->collider1);
        Collider_SetCylinder(globalCtx, &this->collider1, &this->actor, &D_80A4B7A0);
        Collider_InitCylinder(globalCtx, &this->collider2);
        Collider_SetCylinder(globalCtx, &this->collider2, &this->actor, &D_80A4B7CC);
    }
}

void EnGoma_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGoma* this = THIS;

    if (this->actor.params < 10) {
        Collider_DestroyCylinder(globalCtx, &this->collider1);
        Collider_DestroyCylinder(globalCtx, &this->collider2);
    }
}

void func_80A49294(EnGoma* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06003D78, 2.0f, 0.0f, SkelAnime_GetFrameCount(&D_06003D78.genericHeader),
                         0, -2.0f);
    this->actionFunc = func_80A49338;
    this->unk_2CC = 0x14;
    if (this->actor.params < 6) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_BJR_DAM2);
    } else {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_DAM2);
    }
}

void func_80A49338(EnGoma* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothScaleMaxF(&this->actor.speedXZ, 6.6666665f, 0.5f, 2.0f);
    Math_SmoothScaleMaxS(&this->actor.posRot.rot.y, func_8002DA78(&this->actor, &PLAYER->actor) + 0x8000, 3, 0x7D0);
    Math_SmoothScaleMaxS(&this->actor.shape.rot.y, this->actor.posRot.rot.y, 2, 0xBB8);
    if (this->unk_2CC == 0) {
        func_80A49E80(this);
    }
}

void func_80A493D8(EnGoma* this, GlobalContext* globalCtx) {
    this->actor.gravity = -1.3f;
    this->unk_2DC += 0.03f;
    this->unk_2D8 += 1.0f + this->unk_2DC;
    Math_SmoothDownscaleMaxF(&this->unk_2EC, 1.0f, 0.005f);
    Math_SmoothScaleMaxF(&this->unk_2F0, 1500.0f, 1.0f, 150.0f);

    switch (this->unk_2BE) {
        case 0:
            if (this->actor.bgCheckFlags & 1) {
                if (this->actor.params < 6) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_BJR_EGG1);
                } else {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_EGG1);
                }

                if (this->actor.params >= 6) {
                    func_80A498A8(this, globalCtx);
                } else {
                    this->unk_2BE = 1;
                    this->unk_2CC = 3;
                    Math_SmoothScaleMaxF(&this->unk_2D0, 1.5f, 0.5f, 1.0f);
                }
            }
            break;

        case 1:
            if (this->unk_2CC == 0) {
                this->unk_2BE = 2;
                this->unk_2CC = 3;
                Math_SmoothScaleMaxF(&this->unk_2D0, 0.75f, 0.5f, 1.0f);
                this->actor.velocity.y = 5.0f;
                this->actor.speedXZ = 2.0f;
            } else {
                Math_SmoothScaleMaxF(&this->unk_2D0, 1.5f, 0.5f, 1.0f);
            }
            break;

        case 2:
            if (this->unk_2CC == 0) {
                this->unk_2BE = 3;
                this->unk_2CC = 0x50;
            } else {
                Math_SmoothScaleMaxF(&this->unk_2D0, 0.75f, 0.5f, 1.0f);
            }
            break;

        case 3:
            Math_SmoothScaleMaxF(&this->unk_2D0, 1.0f, 0.1f, 0.1f);
            if (this->unk_2CC == 0) {
                func_80A498A8(this, globalCtx);
            }
            break;
    }

    if (this->actor.bgCheckFlags & 1) {
        Math_SmoothDownscaleMaxF(&this->actor.speedXZ, 0.2f, 0.05f);
    }

    this->unk_2D4 += this->actor.speedXZ * 0.1f;
    this->actor.shape.rot.y = this->actor.posRot.rot.y;
}

void func_80A49668(EnGoma* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 i;

    this->unk_2D8 += 1.0f;
    Math_SmoothScaleMaxF(&this->unk_2EC, 0.1f, 1.0f, 0.005f);

    if ((fabsf(this->actor.posRot.pos.x - player->actor.posRot.pos.x) < 100.0f) &&
        (fabsf(this->actor.posRot.pos.z - player->actor.posRot.pos.z) < 100.0f)) {
        this->unk_2C6++;
        if (this->unk_2C6 >= 10) {
            this->actionFunc = func_80A493D8;
        }
    } else {
        this->unk_2C6 = 0;
    }

    if (((this->unk_2C0 & 0xF) == 0) && (Math_Rand_ZeroOne() < 0.5f)) {
        for (i = 0; i < 2; i++) {
            Vec3f a = { 0.0f, 0.0f, 0.0f };
            Vec3f b = { 0.0f, -0.5f, 0.0f };
            Vec3f c;

            c.x = Math_Rand_CenteredFloat(30.0f) + this->actor.posRot.pos.x;
            c.y = Math_Rand_ZeroFloat(30.0f) + this->actor.posRot.pos.y;
            c.z = Math_Rand_CenteredFloat(30.0f) + this->actor.posRot.pos.z;
            func_80029724(globalCtx, &c, &a, &b, 0, (s16)(Math_Rand_ZeroOne() * 5.0f) + 10, -1, 10, 0);
        }
    }
}

void func_80A498A8(EnGoma* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000544, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06000544.genericHeader),
                         2, 0.0f);
    this->actionFunc = func_80A49974;
    Actor_SetScale(&this->actor, 0.005f);
    this->unk_2B8 = 0;
    this->unk_2CC = 5;
    this->actor.shape.rot.y = func_8002DA78(&this->actor, &PLAYER->actor);
    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    func_80A4B3F0(this, globalCtx);
    this->unk_2D0 = 1.0f;
    this->actor.speedXZ = 0.0f;
}

void func_80A49974(EnGoma* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_2CC == 0) {
        func_80A49E80(this);
    }
}

void func_80A499BC(EnGoma* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000838, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06000838.genericHeader),
                         2, -2.0f);
    this->actionFunc = func_80A49AA8;
    if ((s8)this->actor.colChkInfo.health <= 0) {
        this->unk_2CC = 5;
        func_80032C7C(globalCtx, &this->actor);
    } else {
        this->unk_2CC = 10;
    }

    this->actor.speedXZ = 20.0f;
    this->actor.posRot.rot.y = (this->actor.yawTowardsLink + 0x8000);
    if (this->actor.params < 6) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_BJR_DAM1);
    } else {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_DAM1);
    }
}

void func_80A49AA8(EnGoma* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->actor.bgCheckFlags & 1) {
        Math_SmoothDownscaleMaxF(&this->actor.speedXZ, 1.0f, 2.0f);
    }

    if (this->unk_2CC == 0) {
        if ((s8)this->actor.colChkInfo.health <= 0) {
            func_80A49B30(this);
        } else {
            func_80A49294(this);
        }
    }
}

void func_80A49B30(EnGoma* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000B78, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06000B78.genericHeader),
                         2, -2.0f);
    this->actionFunc = func_80A49BF0;
    this->unk_2CC = 0x1E;
    if (this->actor.params < 6) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_BJR_DEAD);
    } else {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_DEAD);
    }

    this->unk_2CA = 0x64;
    this->actor.flags &= ~1;
}

void func_80A49BF0(EnGoma* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->actor.bgCheckFlags & 1) {
        Math_SmoothDownscaleMaxF(&this->actor.speedXZ, 1.0f, 2.0f);
    }

    if (this->unk_2CC == 0x11) {
        if (this->actor.params < 6) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_BJR_LAND);
        } else {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_LAND);
        }
    }

    if (this->unk_2CC == 0) {
        func_80A49C94(this);
    }
}

void func_80A49C94(EnGoma* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000334, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06000334.genericHeader),
                         0, -2.0f);
    this->actionFunc = func_80A49D0C;
    this->unk_2CC = 3;
}

void func_80A49D0C(EnGoma* this, GlobalContext* globalCtx) {
    Vec3f a;
    Vec3f b;
    BossGoma* goma;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothDownscaleMaxF(&this->actor.speedXZ, 1.0f, 2.0f);

    if (this->unk_2CC == 2) {
        b.x = this->actor.posRot.pos.x;
        b.y = (this->actor.posRot.pos.y + 5.0f) - 10.0f;
        b.z = this->actor.posRot.pos.z;
        a = D_80A4B7FC;
        a.y = 0.03f;
        func_80029DBC(globalCtx, &b, &D_80A4B7FC, &a, 0x28, 0);
    }

    if ((this->unk_2CC == 0) &&
        (Math_SmoothScaleMaxMinF(&this->actor.scale.y, 0.0f, 0.5f, 0.00225f, 0.00001f) <= 0.001f)) {
        if (this->actor.params < 6) {
            // Warning, out of bounds
            goma = (BossGoma*)this->actor.parent;
            goma->unk_1A4[this->actor.params] = -1;
        }
        Audio_PlaySoundGeneral(NA_SE_EN_EXTINCT, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        Actor_Kill(&this->actor);
        Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.posRot.pos, 0x30);
    }

    this->unk_2C4 = 2;
}

void func_80A49E80(EnGoma* this) {
    f32 tmp = SkelAnime_GetFrameCount(&D_06001548.genericHeader);

    this->unk_2CC = Math_Rand_S16Offset(10, 30);
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06001548, 1.0f, 0.0f, tmp, 0, -5.0f);
    this->actionFunc = func_80A4A2EC;
    this->unk_2B8 = 0;
}

void func_80A49F10(EnGoma* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06003D78, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06003D78.genericHeader),
                         0, -5.0f);
    this->actionFunc = func_80A4A368;
    this->unk_2CC = Math_Rand_S16Offset(0x46, 0x6E);
}

void func_80A49F94(EnGoma* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000E4C, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06000E4C.genericHeader),
                         2, -5.0f);
    this->actionFunc = func_80A4A010;
    this->unk_2CC = 0x1E;
}

void func_80A4A010(EnGoma* this, GlobalContext* globalCtx) {
    s16 tmp;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothDownscaleMaxF(&this->actor.speedXZ, 0.5f, 2.0f);

    tmp = func_8002DA78(&this->actor, &PLAYER->actor);

    Math_SmoothScaleMaxS(&this->actor.posRot.rot.y, tmp, 2, 0xFA0);
    Math_SmoothScaleMaxS(&this->actor.shape.rot.y, tmp, 2, 0xBB8);
    if (this->unk_2CC == 0) {
        func_80A4A18C(this);
    }

    this->unk_2C4 = 0;
}

void func_80A4A0A8(EnGoma* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600017C, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_0600017C.genericHeader),
                         2, 0.0f);
    this->actionFunc = func_80A4A120;
    this->unk_2CC = 10;
}

void func_80A4A120(EnGoma* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->actor.bgCheckFlags & 1) {
        Math_SmoothDownscaleMaxF(&this->actor.speedXZ, 1.0f, 2.0f);
    }

    if (this->unk_2CC == 0) {
        func_80A49E80(this);
    }
}

void func_80A4A18C(EnGoma* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000544, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06000544.genericHeader),
                         2, 0.0f);
    this->actionFunc = func_80A4A234;
    this->actor.velocity.y = 8.0f;
    if (this->actor.params < 6) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_BJR_CRY);
    } else {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_CRY);
    }
}

void func_80A4A234(EnGoma* this, GlobalContext* globalCtx) {
    this->actor.flags |= 0x1000000;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothScaleMaxF(&this->actor.speedXZ, 10.0f, 0.5f, 5.0f);
    if ((this->actor.velocity.y <= 0.0f) && (this->actor.bgCheckFlags & 1)) {
        func_80A4A0A8(this);
        if (this->actor.params < 6) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_BJR_LAND2);
        } else {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_LAND2);
        }
    }

    this->unk_2C4 = 0;
}

void func_80A4A2EC(EnGoma* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothDownscaleMaxF(&this->actor.speedXZ, 0.5f, 2.0f);
    Math_SmoothScaleMaxS(&this->actor.shape.rot.y, func_8002DA78(&this->actor, &PLAYER->actor), 2, 0xBB8);
    if (this->unk_2CC == 0) {
        func_80A49F10(this);
    }
}

void func_80A4A368(EnGoma* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (func_800A56C8(&this->skelAnime, 1.0f) || func_800A56C8(&this->skelAnime, 5.0f)) {
        if (this->actor.params < 6) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_BJR_WALK);
        } else {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_WALK);
        }
    }

    Math_SmoothScaleMaxF(&this->actor.speedXZ, 3.3333333f, 0.5f, 2.0f);
    Math_SmoothScaleMaxS(&this->actor.posRot.rot.y, this->actor.yawTowardsLink, 3, 0x7D0);
    Math_SmoothScaleMaxS(&this->actor.shape.rot.y, this->actor.posRot.rot.y, 2, 0xBB8);
    if (this->actor.bgCheckFlags & 1) {
        this->actor.velocity.y = 0.0f;
    }

    if (this->actor.xzDistFromLink <= 150.0f) {
        func_80A49F94(this);
    }
}

void func_80A4A470(EnGoma* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80A4A50C;
    this->unk_2F8 = 100;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06001548, -5.0f);
    this->unk_2CC = (s16)Math_Rand_ZeroFloat(15.0f) + 3;
    if (this->actor.params < 6) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_BJR_FREEZE);
    } else {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_FREEZE);
    }
}

void func_80A4A50C(EnGoma* this, GlobalContext* globalCtx) {
    func_8003426C(&this->actor, 0, 0xB4, 0, 2);
    this->unk_2C4 = 2;
    if (this->unk_2CC) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    }

    if (this->actor.bgCheckFlags & 1) {
        this->actor.velocity.y = 0.0f;
        Math_SmoothDownscaleMaxF(&this->actor.speedXZ, 0.5f, 2.0f);
    }

    if (this->unk_2F8 == 0) {
        func_80A49E80(this);
    } else {
        this->unk_2F8--;
        if (this->unk_2F8 < 30) {
            if (this->unk_2F8 & 1) {
                this->actor.posRot.pos.x += 1.5f;
                this->actor.posRot.pos.z += 1.5f;
            } else {
                this->actor.posRot.pos.x -= 1.5f;
                this->actor.posRot.pos.z -= 1.5f;
            }
        }
    }
}

void func_80A4A608(EnGoma* this, GlobalContext* globalCtx) {
    s16 tmp2;
    s16 tmp;

    tmp = func_8002DA78(&this->actor, &PLAYER->actor) - this->actor.shape.rot.y;
    tmp2 = func_8002DAE0(&this->actor, &PLAYER->actor) - this->actor.shape.rot.x;

    if (tmp > 0x1770) {
        tmp = 0x1770;
    }

    if (tmp < -0x1770) {
        tmp = -0x1770;
    }

    Math_SmoothScaleMaxS(&this->unk_2BC, tmp, 3, 0x7D0);
    Math_SmoothScaleMaxS(&this->unk_2BA, tmp2, 3, 0x7D0);
}

void func_80A4A6AC(EnGoma* this, GlobalContext* globalCtx) {
    static Vec3f D_80A4B830 = { 0.0f, 0.0f, 20.0f };

    Player* player = PLAYER;
    BossGoma* goma;
    u8 tmp;
    ColliderTouch* toucher;

    if (this->unk_2C2 != 0) {
        this->unk_2C2--;
        return;
    }

    if ((this->collider1.base.atFlags & 2) && (this->actionFunc == func_80A4A234)) {
        func_80A4A0A8(this);
        this->actor.speedXZ = 0.0f;
        this->actor.velocity.y = 0.0f;
    }

    if ((this->collider2.base.acFlags & 2) && ((s8)this->actor.colChkInfo.health > 0)) {
        toucher = &this->collider2.body.acHitItem->toucher;
        this->collider2.base.acFlags &= 0xFFFD;
        if (this->unk_2B8 == 0) {
            if ((toucher->flags << 0xB) < 0) {
                if (this->actionFunc == func_80A4A234) {
                    func_80A4A0A8(this);
                    this->actor.speedXZ = -5.0f;
                    this->actor.velocity.y = 0.0f;
                } else {
                    Matrix_RotateY((player->actor.shape.rot.y / 32768.0f) * M_PI, 0);
                    Matrix_MultVec3f(&D_80A4B830, &this->unk_2FC);
                    this->unk_2CA = 5;
                }
            } else if (toucher->flags & 1) {
                if (this->actionFunc != func_80A4A50C) {
                    func_80A4A470(this, globalCtx);
                    this->unk_2C2 = 8;
                }
            } else {
                tmp = func_800635D0(toucher->flags);
                if (tmp != 0) {
                    func_800299AC(globalCtx, &this->actor.posRot2.pos);
                } else {
                    tmp = 1;
                }

                this->actor.colChkInfo.health -= tmp;
                func_80A499BC(this, globalCtx);
                func_8003426C(&this->actor, 0x4000, 0xFF, 0, 5);
                this->unk_2C2 = 0xD;
            }
        } else {
            if (this->actor.params < 6) {
                // Warning, out of bounds
                goma = (BossGoma*)this->actor.parent;
                goma->unk_1A4[this->actor.params] = -1;
            }

            func_80A4B3F0(this, globalCtx);
            Actor_Kill(&this->actor);
        }
    }
}

void func_80A4A8D4(EnGoma* this) {
    static f32 D_80A4B83C[] = { 255.0f, 0.0f, 50.0f };
    static f32 D_80A4B848[] = { 17.0f, 255.0f, 50.0f };
    static f32 D_80A4B854[] = { 0.0f, 170.0f, 50.0f };

    Math_SmoothScaleMaxF(&this->unk_2E0[0], D_80A4B83C[this->unk_2C4], 0.5f, 20.0f);
    Math_SmoothScaleMaxF(&this->unk_2E0[1], D_80A4B848[this->unk_2C4], 0.5f, 20.0f);
    Math_SmoothScaleMaxF(&this->unk_2E0[2], D_80A4B854[this->unk_2C4], 0.5f, 20.0f);
}

void func_80A4A964(EnGoma* this) {
    f32 x;
    f32 y;
    f32 z;

    if (this->actor.floorPoly != NULL) {
        x = this->actor.floorPoly->norm.x * (1.0f / 32767);
        y = this->actor.floorPoly->norm.y * (1.0f / 32767);
        z = this->actor.floorPoly->norm.z * (1.0f / 32767);
        Math_SmoothScaleMaxS(&this->unk_2B4, -Math_atan2f(-(z)*y, 1.0f) * 10430.378f, 1, 0x3E8);
        Math_SmoothScaleMaxS(&this->unk_2B6, Math_atan2f(-(x)*y, 1.0f) * 10430.378f, 1, 0x3E8);
    }
}

void EnGoma_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGoma* this = THIS;
    s32 pad;
    Player* player = PLAYER;

    if (this->unk_2CC) {
        this->unk_2CC--;
    }

    if (this->unk_2CA) {
        this->unk_2CA--;
    }

    this->actionFunc(this, globalCtx);
    Actor_MoveForward(&this->actor);
    thisx->posRot.pos.x += this->unk_2FC.x;
    thisx->posRot.pos.z += this->unk_2FC.z;
    Math_SmoothDownscaleMaxF(&this->unk_2FC.x, 1.0f, 3.0f);
    Math_SmoothDownscaleMaxF(&this->unk_2FC.z, 1.0f, 3.0f);
    if (this->actor.params < 10) {
        this->unk_2C0++;
        Math_SmoothScaleMaxMinF(&thisx->scale.x, 0.01f, 0.5f, 0.00075f, 0.000001f);
        Math_SmoothScaleMaxMinF(&thisx->scale.y, 0.01f, 0.5f, 0.00075f, 0.000001f);
        Math_SmoothScaleMaxMinF(&thisx->scale.z, 0.01f, 0.5f, 0.00075f, 0.000001f);
        func_80A4A6AC(this, globalCtx);
        func_8002E4B4(globalCtx, thisx, 50.0f, 50.0f, 100.0f, 5);
        func_80A4A964(this);
        Actor_SetHeight(thisx, 20.0f);
        func_80A4A608(this, globalCtx);
        func_80A4A8D4(this);
        this->unk_2C4 = 1;
        if (player->swordState != 0) {
            this->collider2.dim.radius = 35;
            this->collider2.dim.height = 35;
            this->collider2.dim.yShift = 0;
        } else {
            this->collider2.dim.radius = 15;
            this->collider2.dim.height = 30;
            this->collider2.dim.yShift = 10;
        }

        if (this->unk_2CA == 0) {
            Collider_CylinderUpdate(thisx, &this->collider1);
            Collider_CylinderUpdate(thisx, &this->collider2);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        }
    }
}

s32 EnGoma_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                            Actor* thisx) {
    EnGoma* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_goma.c", 1976);

    gDPSetEnvColor(oGfxCtx->polyOpa.p++, (s16)this->unk_2E0[0], (s16)this->unk_2E0[1], (s16)this->unk_2E0[2], 255);
    if (limbIndex == 7) {
        rot->x += this->unk_2BA;
        rot->y += this->unk_2BC;
    } else if ((limbIndex == 3) && (this->unk_2C2)) {
        gDPSetEnvColor(oGfxCtx->polyOpa.p++, (s16)(Math_Rand_ZeroOne() * 255.0f), (s16)(Math_Rand_ZeroOne() * 255.0f),
                       (s16)(Math_Rand_ZeroOne() * 255.0f), 255);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_goma.c", 2011);
    return 0;
}

Gfx* func_80A4AE60(GraphicsContext* gfxCtx) {
    Gfx* dList;
    Gfx* dListHead;
    dList = dListHead = Graph_Alloc(gfxCtx, sizeof(Gfx) * 4);

    gDPPipeSync(dListHead++);
    gDPSetRenderMode(dListHead++, G_RM_PASS, G_RM_AA_ZB_TEX_EDGE2);
    gSPClearGeometryMode(dListHead++, G_CULL_BACK);
    gSPEndDisplayList(dListHead++);
    return dList;
}

void EnGoma_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnGoma* this = THIS;
    s16 tmp;
    Vec3f* tmpvec;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_goma.c", 2040);

    func_80093D18(globalCtx->state.gfxCtx);
    switch (this->unk_2B8) {
        case 0:
            this->actor.naviEnemyId = 3;
            tmpvec = &globalCtx->mainCamera.unk_80;
            Matrix_Translate(this->actor.posRot.pos.x,
                             this->actor.posRot.pos.y + ((this->actor.shape.unk_08 * this->actor.scale.y) + tmpvec->y),
                             this->actor.posRot.pos.z, 0);
            Matrix_RotateX((this->unk_2B4 / 32768.0f) * M_PI, 1);
            Matrix_RotateZ((this->unk_2B6 / 32768.0f) * M_PI, 1);
            Matrix_RotateY((this->actor.shape.rot.y / 32768.0f) * M_PI, 1);
            Matrix_RotateX((this->actor.shape.rot.x / 32768.0f) * M_PI, 1);
            Matrix_RotateZ((this->actor.shape.rot.z / 32768.0f) * M_PI, 1);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1);
            SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, EnGoma_OverrideLimbDraw,
                           NULL, &this->actor);
            break;

        case 1:
            this->actor.naviEnemyId = 2;
            // This one isn't quite M_PI
            tmp = (s16)(sinf(((this->unk_2C0 * 5.0f) * 3.1415f) / 180.0f) * 31.9f) + 0x1F;

            gSPSegment(oGfxCtx->polyOpa.p++, 0x08, func_80094E78(globalCtx->state.gfxCtx, 0, tmp));
            Matrix_Push();
            Matrix_Scale(this->unk_2D0, 1.0f / this->unk_2D0, this->unk_2D0, 1);
            Matrix_RotateY(this->unk_2D8 * 0.15f, 1);
            Matrix_RotateZ(this->unk_2D8 * 0.1f, 1);
            Matrix_Scale((0.95f - this->unk_2EC), this->unk_2EC + 1.05f, (0.95f - this->unk_2EC), 1);
            Matrix_RotateZ(-(this->unk_2D8 * 0.1f), 1);
            Matrix_RotateY(-(this->unk_2D8 * 0.15f), 1);
            Matrix_Translate(0.0f, this->unk_2F0, 0.0f, 1);
            Matrix_RotateX(this->unk_2D4, 1);
            gSPMatrix(oGfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_goma.c", 2101),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(oGfxCtx->polyOpa.p++, D_06002A70);
            Matrix_Pull();
            break;

        case 2:
            gSPMatrix(oGfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_goma.c", 2107),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(oGfxCtx->polyOpa.p++, D_05000530);
            break;

        case 3:
            if (this->unk_308) {
                gSPSegment(oGfxCtx->polyOpa.p++, 0x08, func_80A4AE60(globalCtx->state.gfxCtx));
                gSPMatrix(oGfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_goma.c", 2114),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(oGfxCtx->polyOpa.p++, this->unk_308);
            }
            break;
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_goma.c", 2119);
}

void func_80A4B3AC(EnGoma* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.y = this->actor.shape.rot.y + 0x9C4;
    this->actor.shape.rot.x = this->actor.shape.rot.x + 0xDAC;
    if (this->unk_2CC == 0) {
        Actor_Kill(&this->actor);
    }
}

void func_80A4B3F0(EnGoma* this, GlobalContext* globalCtx) {
    s16 i;

    if (this->actor.params < 6) {
        Audio_PlaySoundAtPosition(globalCtx, &this->actor.posRot.pos, 40, NA_SE_EN_GOMA_BJR_EGG2);
    } else {
        Audio_PlaySoundAtPosition(globalCtx, &this->actor.posRot.pos, 40, NA_SE_EN_GOMA_EGG2);
    }

    for (i = 0; i < 15; i++) {
        if (globalCtx) {};
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_GOMA,
                            this->actor.posRot.pos.x + Math_Rand_CenteredFloat(10.0f),
                            (this->actor.posRot.pos.y + Math_Rand_CenteredFloat(10.0f)) + 15.0f,
                            this->actor.posRot.pos.z + Math_Rand_CenteredFloat(10.0f), 0.0f,
                            Math_Rand_CenteredFloat(65535.99f), 0.0f, i + 10);
    }
}

void func_80A4B554(EnGoma* this, GlobalContext* globalCtx) {
    Vec3f velocity = { 0.0f, 0.0f, 0.0f };
    Vec3f accel = { 0.0f, 1.0f, 0.0f };
    Color_RGBA8_n primColor = { 255, 255, 255, 255 };
    Color_RGBA8_n envColor = { 0, 100, 255, 255 };
    Vec3f pos;

    this->actor.posRot.pos.y -= 5.0f;
    func_8002E4B4(globalCtx, &this->actor, 50.0f, 50.0f, 100.0f, 4);
    this->actor.posRot.pos.y += 5.0f;
    if ((this->actor.bgCheckFlags & 1) != 0) {
        this->actor.velocity.y = 0.0f;
    } else if (this->unk_2CC < 0xFA) {
        this->actor.shape.rot.y += 0x7D0;
    }

    if (this->unk_2CC == 0xFA) {
        this->actor.gravity = -1.0f;
    }

    if (this->unk_2CC < 0x79) {
        if (Math_SmoothScaleMaxMinF(&this->actor.scale.y, 0, 1.0f, 0.00075f, 0.0f) <= 0.001f) {
            Actor_Kill(&this->actor);
        }

        this->actor.scale.z = this->actor.scale.y;
        this->actor.scale.x = this->actor.scale.y;
    }

    if (!(this->unk_2CC & 7) && this->unk_2CC) {
        pos.x = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.x;
        pos.y = Math_Rand_CenteredFloat(10.0f) + this->actor.posRot.pos.y;
        pos.z = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.z;
        func_8002836C(globalCtx, &pos, &velocity, &accel, &primColor, &envColor, 500, 10, 10);
    }
}
