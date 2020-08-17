#include "z_en_firefly.h"
#include "overlays/actors/ovl_Obj_Syokudai/z_obj_syokudai.h"

#define FLAGS 0x00005005

#define THIS ((EnFirefly*)thisx)

void EnFirefly_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A14E28(Actor* thisx, GlobalContext* globalCtx);
void func_80A13A08(EnFirefly* this, GlobalContext* globalCtx);
void func_80A142F4(EnFirefly* this, GlobalContext* globalCtx);
void func_80A13FF4(EnFirefly* this, GlobalContext* globalCtx);
void func_80A14088(EnFirefly* this, GlobalContext* globalCtx);
void func_80A14294(EnFirefly* this, GlobalContext* globalCtx);
void func_80A13C98(EnFirefly* this, GlobalContext* globalCtx);
void func_80A141F0(EnFirefly* this, GlobalContext* globalCtx);
void func_80A13DE4(EnFirefly* this, GlobalContext* globalCtx);
void func_80A143B4(EnFirefly* this, GlobalContext* globalCtx);
void func_80A13D68(EnFirefly* this, GlobalContext* globalCtx);

extern AnimationHeader D_0600017C;
extern SkeletonHeader D_060018B8;
extern Gfx D_06001678[];

const ActorInit En_Firefly_InitVars = {
    ACTOR_EN_FIREFLY,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_FIREFLY,
    sizeof(EnFirefly),
    (ActorFunc)EnFirefly_Init,
    (ActorFunc)EnFirefly_Destroy,
    (ActorFunc)EnFirefly_Update,
    (ActorFunc)EnFirefly_Draw,
};

static ColliderJntSphItemInit sJntSphItemsInit[1] = {
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x08 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x09, 0x01, 0x01 },
        { 1, { { 0, 1000, 0 }, 15 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_UNK3, 0x11, 0x09, 0x39, 0x10, COLSHAPE_JNTSPH },
    1,
    sJntSphItemsInit,
};

CollisionCheckInfoInit D_80A14F64 = { 0x01, 0x000A, 0x000A, 0x1E };

DamageTable D_80A14F6C = { 0x10, 0x02, 0x01, 0x02, 0x01, 0x02, 0x02, 0x02, 0x01, 0x02, 0x04,
                           0xF2, 0x34, 0x02, 0x02, 0x02, 0x02, 0x20, 0x34, 0x00, 0x00, 0x00,
                           0x01, 0x04, 0x02, 0x02, 0x08, 0x04, 0x00, 0x00, 0x04, 0x00 };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 5, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, 65036, ICHAIN_CONTINUE),
    ICHAIN_F32(minVelocityY, 65532, ICHAIN_CONTINUE),
    ICHAIN_U8(unk_1F, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 4000, ICHAIN_STOP),
};

void func_80A13070(EnFirefly* this) {
    this->actor.params += 2;
    this->collider.list->body.toucher.effect = 0;
    this->unk_1B8 = 0;
    this->unk_1B9 = 0;
    this->actor.naviEnemyId = 0x12;
}

void func_80A13098(EnFirefly* this) {
    if (this->actor.params == 4) {
        this->actor.params = 0;
    } else {
        this->actor.params -= 2;
    }

    this->collider.list[0].body.toucher.effect = 1;
    this->unk_1B8 = 1;
    this->unk_1B9 = 1;
    this->actor.naviEnemyId = 0x11;
}

void EnFirefly_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFirefly* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawFunc_Circle, 25.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_060018B8, &D_0600017C, this->limbDrawTable,
                   this->transitionDrawTable, 28);
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderItems);
    func_80061ED4(&thisx->colChkInfo, &D_80A14F6C, &D_80A14F64);

    if (thisx->params & 0x8000) {
        thisx->flags |= 0x80;
        thisx->draw = func_80A14E28;
        this->actor.params &= 0x7FFF;
    }

    this->unk_1B9 = (thisx->params < 2) ? 1 : 0;

    if (this->unk_1B9) {
        this->actionFunc = func_80A13A08;
        this->unk_1BA = Math_Rand_S16Offset(0x14, 0x3C);
        thisx->shape.rot.x = 0x1554;
        this->unk_1B8 = 1;
        thisx->naviEnemyId = 0x11;
        this->unk_310 = thisx->initPosRot.pos.y;
    } else {
        if (thisx->params == 3) {
            this->actionFunc = func_80A142F4;
        } else {
            this->actionFunc = func_80A13A08;
        }

        if (thisx->params == 4) {
            this->collider.list[0].body.toucher.effect = 2;
            thisx->naviEnemyId = 0x56;
        } else {
            this->collider.list[0].body.toucher.effect = 0;
            thisx->naviEnemyId = 0x12;
        }

        this->unk_310 = thisx->initPosRot.pos.y + 100.0f;
        if (thisx->params == 4) {
            this->unk_1B8 = 2;
        } else {
            this->unk_1B8 = 0;
        }
    }

    this->collider.list[0].dim.worldSphere.radius = sJntSphInit.list[0].dim.modelSphere.radius;
}

void EnFirefly_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFirefly* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80A132F4(EnFirefly* this) {
    this->unk_1BA = Math_Rand_S16Offset(0x46, 0x64);
    this->actor.speedXZ = (Math_Rand_ZeroOne() * 1.5f) + 1.5f;
    Math_ApproxUpdateScaledS(&this->actor.shape.rot.y, func_8002DAC0(&this->actor, &this->actor.initPosRot.pos), 0x300);
    this->unk_1BC = ((this->unk_310 < this->actor.posRot.pos.y) ? 0xC00 : -0xC00) + 0x1554;
    this->skelAnime.animPlaybackSpeed = 1.0f;
    this->actionFunc = func_80A13A08;
}

void func_80A133A0(EnFirefly* this) {
    this->unk_1BA = 0x28;
    this->actor.velocity.y = 0.0f;
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600017C, 0.5f, 0.0f, 0.0f, 1, -3.0f);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FFLY_DEAD);
    this->actor.flags |= 0x10;
    func_8003426C(&this->actor, 0x4000, 0xFF, 0, 0x28);
    this->actionFunc = func_80A13C98;
}

void func_80A13444(EnFirefly* this) {
    this->unk_1BA = 0xF;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80A13D68;
}

void func_80A13464(EnFirefly* this) {
    this->actor.posRot.rot.x = 0x7000;
    this->unk_1BA = 0x12;
    this->skelAnime.animPlaybackSpeed = 1.0f;
    this->actor.speedXZ = 2.5f;
    this->actionFunc = func_80A13FF4;
}

void func_80A1349C(EnFirefly* this) {
    this->unk_1BA = Math_Rand_S16Offset(0x46, 0x64);
    this->skelAnime.animPlaybackSpeed = 1.0f;
    this->unk_1BC = ((this->actor.yDistFromLink > 0.0f) ? -0xC00 : 0xC00) + 0x1554;
    this->actionFunc = func_80A13DE4;
}

void func_80A1350C(EnFirefly* this) {
    this->unk_1BA = 0x96;
    this->unk_1BC = 0x954;
    this->actionFunc = func_80A14088;
    this->skelAnime.animPlaybackSpeed = 1.0f;
}

void func_80A13538(EnFirefly* this) {
    this->unk_1BA = 0x50;
    func_8003426C(&this->actor, 0, 0xFF, 0, 0x50);
    this->unk_1B8 = 0;
    this->actor.velocity.y = 0.0f;
    this->skelAnime.animPlaybackSpeed = 3.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_FREEZE);
    this->actionFunc = func_80A141F0;
}

void func_80A135A8(EnFirefly* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f sp78;

    this->actor.flags |= 0x10;
    this->unk_1B8 = 0;
    this->actor.speedXZ = 0.0f;
    func_8003426C(&this->actor, 0, 0xFF, 0, 0xFF);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FFLY_DEAD);

    for (i = 0; i < 8; i++) {
        sp78.x = ((i & 1) ? 7.0f : -7.0f) + this->actor.posRot.pos.x;
        sp78.y = ((i & 2) ? 7.0f : -7.0f) + this->actor.posRot.pos.y;
        sp78.z = ((i & 4) ? 7.0f : -7.0f) + this->actor.posRot.pos.z;
        func_8002A140(globalCtx, &this->actor, &sp78, 0x96, 0x96, 0x96, 0xFA, 0xEB, 0xF5, 0xFF,
                      (Math_Rand_ZeroOne() * 0.15f) + 0.85f);
    }

    this->actionFunc = func_80A14294;
}

void func_80A13744(EnFirefly* this) {
    this->unk_1BA = 1;
    this->actionFunc = func_80A142F4;
    this->actor.speedXZ = 0.0f;
}

void func_80A13764(EnFirefly* this) {
    this->actor.shape.rot.x = 0x1554;
    this->skelAnime.animPlaybackSpeed = 3.0f;
    this->actor.shape.rot.y = this->actor.yawTowardsLink;
    this->unk_1BA = 0x32;
    this->actor.speedXZ = 3.0f;
    this->actionFunc = func_80A143B4;
}

s32 func_80A1379C(EnFirefly* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    f32 tmpf1;
    f32 tmpf2;

    if (this->actor.params != 3) {
        return 0;
    }

    if (func_8002DBB0(&player->actor, &this->actor.initPosRot.pos) > 300.0f) {
        tmpf1 = func_8002DB6C(&this->actor, &this->actor.initPosRot.pos);
        if (tmpf1 < 5.0f) {
            func_80A13744(this);
            return 1;
        }

        tmpf2 = tmpf1 * 0.05f;
        if (tmpf2 < 1.0f) {
            this->actor.speedXZ *= tmpf2;
        }

        Math_ApproxUpdateScaledS(&this->actor.shape.rot.y, func_8002DAC0(&this->actor, &this->actor.initPosRot.pos),
                                 0x300);
        Math_ApproxUpdateScaledS(&this->actor.shape.rot.x,
                                 func_8002DB28(&this->actor, &this->actor.initPosRot.pos) + 0x1554, 0x100);
        return 1;
    }

    return 0;
}

s32 func_80A138B8(EnFirefly* this, GlobalContext* globalCtx) {
    ObjSyokudai* syokudai = (ObjSyokudai*)globalCtx->actorCtx.actorList[ACTORTYPE_PROP].first;
    ObjSyokudai* found = NULL;
    f32 target = 35000.0f;
    f32 tmpf1;
    Vec3f sp34;

    while (syokudai != NULL) {
        if ((syokudai->actor.id == ACTOR_OBJ_SYOKUDAI) && (syokudai->unk_1E4 != 0)) {
            tmpf1 = func_8002DB48(&this->actor, &syokudai->actor);
            if (tmpf1 < target) {
                target = tmpf1;
                found = syokudai;
            }
        }
        syokudai = (ObjSyokudai*)syokudai->actor.next;
    }

    if (found != NULL) {
        sp34.x = found->actor.posRot.pos.x;
        sp34.y = (found->actor.posRot.pos.y + 52.0f) + 15.0f;
        sp34.z = found->actor.posRot.pos.z;
        if (func_8002DB6C(&this->actor, &sp34) < 15.0f) {
            func_80A13098(this);
        } else {
            Math_ApproxUpdateScaledS(&this->actor.shape.rot.y, func_8002DA78(&this->actor, &found->actor), 0x300);
            Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, func_8002DB28(&this->actor, &sp34) + 0x1554, 0x100);
        }
        return 1;
    }
    return 0;
}

void func_80A13A08(EnFirefly* this, GlobalContext* globalCtx) {
    s32 tmp;
    f32 rand;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_1BA != 0) {
        this->unk_1BA--;
    }

    tmp = func_800A56C8(&this->skelAnime, 0.0f);
    this->actor.speedXZ = (Math_Rand_ZeroOne() * 1.5f) + 1.5f;
    if (((this->unk_1B9 != 0) || (this->actor.params == 4)) ||
        (!func_80A1379C(this, globalCtx) && !func_80A138B8(this, globalCtx))) {
        if (tmp != 0) {
            rand = Math_Rand_ZeroOne();
            if (rand < 0.5f) {
                Math_ApproxUpdateScaledS(&this->actor.shape.rot.y,
                                         func_8002DAC0(&this->actor, &this->actor.initPosRot.pos), 0x300);
            } else if (rand < 0.8f) {
                this->actor.shape.rot.y += Math_Rand_CenteredFloat(1536.0f);
            }

            if (this->actor.posRot.pos.y < (this->actor.groundY + 20.0f)) {
                this->unk_1BC = 0x954;
            } else if (this->unk_310 < this->actor.posRot.pos.y) {
                this->unk_1BC = 0x2154;
            } else if (Math_Rand_ZeroOne() > 0.35f) {
                this->unk_1BC = 0x954;
            } else {
                this->unk_1BC = 0x2154;
            }
        } else if (this->actor.bgCheckFlags & 1) {
            this->unk_1BC = 0x954;
        } else if ((this->actor.bgCheckFlags & 0x10) || (this->unk_310 < this->actor.posRot.pos.y)) {
            this->unk_1BC = 0x2154;
        }

        Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, this->unk_1BC, 0x100);
    }

    if (this->actor.bgCheckFlags & 8) {
        Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.wallPolyRot, 2, 0xC00, 0x300);
    }

    if ((this->unk_1BA == 0) && (this->actor.xzDistFromLink < 200.0f) && (func_8008F080(globalCtx) != 2)) {
        func_80A1349C(this);
    }
}

void func_80A13C98(EnFirefly* this, GlobalContext* globalCtx) {
    if (func_800A56C8(&this->skelAnime, 6.0f) != 0) {
        this->skelAnime.animPlaybackSpeed = 0.0f;
    }

    this->actor.dmgEffectTimer = 0x28;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_ApproxF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (this->actor.flags & 0x8000) {
        this->actor.dmgEffectTimer = 0x28;
        return;
    }

    Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, 0x6800, 0x200);
    this->actor.shape.rot.y -= 0x300;
    if (this->unk_1BA != 0) {
        this->unk_1BA--;
    }

    if ((this->actor.bgCheckFlags & 1) || (this->unk_1BA == 0)) {
        func_80A13444(this);
    }
}

void func_80A13D68(EnFirefly* this, GlobalContext* globalCtx) {
    if (this->unk_1BA != 0) {
        this->unk_1BA--;
    }

    Math_ApproxF(&this->actor.scale.x, 0.0f, 0.00034f);
    this->actor.scale.y = this->actor.scale.z = this->actor.scale.x;
    if (this->unk_1BA == 0) {
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.posRot.pos, 0xE0);
        Actor_Kill(&this->actor);
    }
}

void func_80A13DE4(EnFirefly* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f sp38;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_1BA != 0) {
        this->unk_1BA--;
    }

    Math_ApproxF(&this->actor.speedXZ, 4.0f, 0.5f);
    if (this->actor.bgCheckFlags & 8) {
        Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.wallPolyRot, 2, 0xC00, 0x300);
        Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, this->unk_1BC, 0x100);
    } else if (func_8002E084(&this->actor, 0x2800) != 0) {
        if (func_800A56C8(&this->skelAnime, 4.0f) != 0) {
            this->skelAnime.animPlaybackSpeed = 0.0f;
            this->skelAnime.animCurrentFrame = 4.0f;
        }

        Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 2, 0xC00, 0x300);
        sp38.x = player->actor.posRot.pos.x;
        sp38.y = player->actor.posRot.pos.y + 20.0f;
        sp38.z = player->actor.posRot.pos.z;
        Math_SmoothScaleMaxMinS(&this->actor.shape.rot.x, func_8002DB28(&this->actor, &sp38) + 0x1554, 2, 0x400, 0x100);
    } else {
        this->skelAnime.animPlaybackSpeed = 1.5f;
        if (this->actor.xzDistFromLink > 80.0f) {
            Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 2, 0xC00, 0x300);
        }

        if (this->actor.bgCheckFlags & 1) {
            this->unk_1BC = 0x954;
        }

        if ((this->actor.bgCheckFlags & 0x10) || (this->unk_310 < this->actor.posRot.pos.y)) {
            this->unk_1BC = 0x2154;
        } else {
            this->unk_1BC = 0x954;
        }

        Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, this->unk_1BC, 0x100);
    }

    if ((this->unk_1BA == 0) || (func_8008F080(globalCtx) == 2)) {
        func_80A1350C(this);
    }
}

void func_80A13FF4(EnFirefly* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, 0, 0x100);
    Math_ApproxF(&this->actor.velocity.y, 0.0f, 0.4f);
    if (Math_ApproxF(&this->actor.speedXZ, 0.0f, 0.15f) != 0) {
        if (this->unk_1BA != 0) {
            this->unk_1BA--;
        }

        if (this->unk_1BA == 0) {
            func_80A1350C(this);
        }
    }
}

void func_80A14088(EnFirefly* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_1BA != 0) {
        this->unk_1BA--;
    }

    if (((fabsf(this->actor.posRot.pos.y - this->unk_310) < 10.0f) &&
         (Math_Vec3f_DistXZ(&this->actor.posRot.pos, &this->actor.initPosRot.pos) < 20.0f)) ||
        (this->unk_1BA == 0)) {
        func_80A132F4(this);
        return;
    }

    Math_ApproxF(&this->actor.speedXZ, 3.0f, 0.3f);
    if (this->actor.bgCheckFlags & 1) {
        this->unk_1BC = 0x954;
    } else if ((this->actor.bgCheckFlags & 0x10) || (this->unk_310 < this->actor.posRot.pos.y)) {
        this->unk_1BC = 0x2154;
    } else {
        this->unk_1BC = 0x954;
    }

    if (this->actor.bgCheckFlags & 8) {
        Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.wallPolyRot, 2, 0xC00, 0x300);
    } else {
        Math_ApproxUpdateScaledS(&this->actor.shape.rot.y, func_8002DAC0(&this->actor, &this->actor.initPosRot.pos),
                                 0x300);
    }

    Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, this->unk_1BC, 0x100);
}

void func_80A141F0(EnFirefly* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_ApproxF(&this->actor.speedXZ, 0.0f, 0.5f);
    Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, 0x1554, 0x100);
    if (this->unk_1BA != 0) {
        this->unk_1BA--;
    }

    if (this->unk_1BA == 0) {
        if (this->unk_1B9 != 0) {
            this->unk_1B8 = 1;
        } else if (this->actor.params == 4) {
            this->unk_1B8 = 2;
        }

        func_80A132F4(this);
    }
}

void func_80A14294(EnFirefly* this, GlobalContext* globalCtx) {
    if ((this->actor.bgCheckFlags & 1) || (this->actor.groundY == -32000.0f)) {
        this->actor.dmgEffectTimer = 0;
        func_80A13444(this);
    } else {
        this->actor.dmgEffectTimer = 0xFF;
    }
}

void func_80A142F4(EnFirefly* this, GlobalContext* globalCtx) {
    Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, 0, 0x100);
    if (this->unk_1BA != 0) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        if (func_800A56C8(&this->skelAnime, 6.0f) != 0) {
            this->unk_1BA--;
        }
    } else if (Math_Rand_ZeroOne() < 0.02f) {
        this->unk_1BA = 1;
    }

    if (this->actor.xzDistFromLink < 120.0f) {
        func_80A13764(this);
    }
}

void func_80A143B4(EnFirefly* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f sp28;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_1BA != 0) {
        this->unk_1BA--;
    }

    if (this->unk_1BA < 0x28) {
        Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, -0xAAC, 0x100);
    } else {
        sp28.x = player->actor.posRot.pos.x;
        sp28.y = player->actor.posRot.pos.y + 20.0f;
        sp28.z = player->actor.posRot.pos.z;
        Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, func_8002DB28(&this->actor, &sp28) + 0x1554, 0x100);
        Math_ApproxUpdateScaledS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 0x300);
    }

    if (this->unk_1BA == 0) {
        func_80A132F4(this);
    }
}

void func_80A1448C(EnFirefly* this, GlobalContext* globalCtx) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_8002A4D4(globalCtx, &this->actor, &this->actor.posRot.pos, 0x28, 0, 0, i);
    }

    this->unk_1B8 = 0;
}

void func_80A1450C(EnFirefly* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= ~2;
        func_80035650(&this->actor, &this->collider.list[0].body, 1);
        if ((this->actor.colChkInfo.damageEffect != 0) || (this->actor.colChkInfo.damage != 0)) {
            if (Actor_ApplyDamage(&this->actor) == 0) {
                func_80032C7C(globalCtx, &this->actor);
                this->actor.flags &= ~1;
            }

            if (this->actor.colChkInfo.damageEffect == 2) {
                if (this->actor.params == 4) {
                    this->actor.colChkInfo.health = 0;
                    func_80032C7C(globalCtx, &this->actor);
                    func_80A1448C(this, globalCtx);
                    func_80A133A0(this);
                } else if (this->unk_1B9 == 0) {
                    func_80A13098(this);
                    if (this->actionFunc == func_80A142F4) {
                        func_80A132F4(this);
                    }
                }
            } else if (this->actor.colChkInfo.damageEffect == 3) {
                if (this->actor.params == 4) {
                    func_80A133A0(this);
                } else {
                    func_80A135A8(this, globalCtx);
                }
            } else if (this->actor.colChkInfo.damageEffect == 1) {
                if (this->actionFunc != func_80A141F0) {
                    func_80A13538(this);
                }
            } else {
                if ((this->actor.colChkInfo.damageEffect == 15) && (this->actor.params == 4)) {
                    func_80A1448C(this, globalCtx);
                }
                func_80A133A0(this);
            }
        }
    }
}

#ifdef NON_MATCHING
// globalCtx whyyy
void EnFirefly_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFirefly* this = THIS;
    s32 pad;
    f32 sp34;

    if (this->collider.base.atFlags & 2) {
        this->collider.base.atFlags &= ~2;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FFLY_ATTACK);
        if (this->unk_1B9 != 0) {
            func_80A13070(this);
        }

        if (this->actionFunc != func_80A143B4) {
            func_80A13464(this);
        }
    }

    func_80A1450C(this, globalCtx);
    this->actionFunc(this, globalCtx);
    if (!(this->actor.flags & 0x8000)) {
        if ((this->actor.colChkInfo.health == 0) || (this->actionFunc == func_80A141F0)) {
            Actor_MoveForward(&this->actor);
        } else {
            if (this->actionFunc != func_80A13FF4) {
                this->actor.posRot.rot.x = 0x1554 - this->actor.shape.rot.x;
            }

            func_8002D97C(&this->actor);
        }
    }

    func_8002E4B4(globalCtx, &this->actor, 10.0f, 10.0f, 15.0f, 7);

    this->collider.list[0].dim.worldSphere.center.x = this->actor.posRot.pos.x;
    this->collider.list[0].dim.worldSphere.center.y = this->actor.posRot.pos.y + 10.0f;
    this->collider.list[0].dim.worldSphere.center.z = this->actor.posRot.pos.z;

    if ((this->actionFunc == func_80A13DE4) || (this->actionFunc == func_80A143B4)) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    if (this->actor.colChkInfo.health != 0) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        this->actor.posRot.rot.y = this->actor.shape.rot.y;
        if (func_800A56C8(&this->skelAnime, 5.0f) != 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_FFLY_FLY);
        }
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    sp34 = Math_Sins(this->actor.shape.rot.x);
    this->actor.posRot2.pos.x = (Math_Sins(this->actor.shape.rot.y) * (10.0f * sp34)) + this->actor.posRot.pos.x;
    this->actor.posRot2.pos.y = (Math_Coss(this->actor.shape.rot.x) * 10.0f) + this->actor.posRot.pos.y;
    sp34 = Math_Sins(this->actor.shape.rot.x);
    this->actor.posRot2.pos.z = (Math_Coss(this->actor.shape.rot.y) * (10.0f * sp34)) + this->actor.posRot.pos.z;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Firefly/EnFirefly_Update.s")
#endif

s32 func_80A14960(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor,
                  Gfx** gfx) {
    if ((actor->draw == func_80A14E28) && (globalCtx->actorCtx.unk_03 == 0)) {
        *dList = NULL;
    } else if (limbIndex == 1) {
        pos->y += 2300.0f;
    }
    return 0;
}

void func_80A149B4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, EnFirefly* this, Gfx** gfx) {
    static Color_RGBA8_n D_80A14FA0 = { 255, 255, 100, 255 };
    static Color_RGBA8_n D_80A14FA4 = { 255, 50, 0, 0 };
    static Color_RGBA8_n D_80A14FA8 = { 100, 200, 255, 255 };
    static Color_RGBA8_n D_80A14FAC = { 0, 0, 255, 0 };
    static Vec3f D_80A14FB0 = { 0.0f, 0.5f, 0.0f };
    static Vec3f D_80A14FBC = { 0.0f, 0.5f, 0.0f };
    static Vec3f D_80A14FC8 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp94;
    Vec3f* sp90;
    Color_RGBA8_n* color1;
    Color_RGBA8_n* color2;
    MtxF sp48;
    s16 tmp1;
    s16 tmp2;

    if ((this->unk_1B9 == 0) && (limbIndex == 0x1B)) {
        gSPDisplayList(gfx[0]++, D_06001678);
    } else if ((this->unk_1B8 == 1) || (this->unk_1B8 == 2)) {
        if ((limbIndex == 15) || (limbIndex == 21)) {
            if (this->actionFunc != func_80A13D68) {
                Matrix_Get(&sp48);
                sp94.x = (Math_Rand_ZeroOne() * 5.0f) + sp48.wx;
                sp94.y = (Math_Rand_ZeroOne() * 5.0f) + sp48.wy;
                sp94.z = (Math_Rand_ZeroOne() * 5.0f) + sp48.wz;
                tmp1 = -0x28;
                tmp2 = 3;
            } else {
                if (limbIndex == 0xF) {
                    sp94.x = (Math_Sins(this->unk_1BA * 9100) * this->unk_1BA) + this->actor.posRot.pos.x;
                    sp94.z = (Math_Coss(this->unk_1BA * 9100) * this->unk_1BA) + this->actor.posRot.pos.z;
                } else {
                    sp94.x = this->actor.posRot.pos.x - (Math_Sins(this->unk_1BA * 9100) * this->unk_1BA);
                    sp94.z = this->actor.posRot.pos.z - (Math_Coss(this->unk_1BA * 9100) * this->unk_1BA);
                }
                sp94.y = this->actor.posRot.pos.y + ((15 - this->unk_1BA) * 1.5f);
                tmp1 = -5;
                tmp2 = 0xA;
            }

            if (this->unk_1B8 == 1) {
                color1 = &D_80A14FA0;
                color2 = &D_80A14FA4;
            } else {
                color1 = &D_80A14FA8;
                color2 = &D_80A14FAC;
            }

            func_8002843C(globalCtx, &sp94, &D_80A14FB0, &D_80A14FBC, color1, color2, 0xFA, tmp1, tmp2);
        }
    }

    if ((limbIndex == 15) || (limbIndex == 21) || (limbIndex == 10)) {
        if (limbIndex == 15) {
            sp90 = &this->unk_14C;
        } else if (limbIndex == 21) {
            sp90 = &this->unk_158;
        } else {
            sp90 = &this->unk_164;
        }

        Matrix_MultVec3f(&D_80A14FC8, sp90);
        sp90->y -= 5.0f;
    }
}

void EnFirefly_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFirefly* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_firefly.c", 0x6C5);
    func_80093D18(globalCtx->state.gfxCtx);
    if (this->unk_1B9 != 0) {
        gDPSetEnvColor(gfxCtx->polyOpa.p++, 0, 0, 0, 0);
    } else {
        gDPSetEnvColor(gfxCtx->polyOpa.p++, 0, 0, 0, 255);
    }

    gfxCtx->polyOpa.p = SkelAnime_Draw2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, func_80A14960,
                                        func_80A149B4, &this->actor, gfxCtx->polyOpa.p);
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_firefly.c", 0x6E3);
}

void func_80A14E28(Actor* thisx, GlobalContext* globalCtx) {
    EnFirefly* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_firefly.c", 0x6EF);
    func_80093D84(globalCtx->state.gfxCtx);
    if (this->unk_1B9 != 0) {
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 0, 0, 0, 0);
    } else {
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 0, 0, 0, 255);
    }

    gfxCtx->polyXlu.p = SkelAnime_Draw2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, func_80A14960,
                                        func_80A149B4, &this->actor, gfxCtx->polyXlu.p);
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_firefly.c", 0x70D);
}
