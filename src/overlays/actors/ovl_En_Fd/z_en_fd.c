#include "z_en_fd.h"

#define FLAGS 0x00000215

#define THIS ((EnFd*)thisx)

void EnFd_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFd_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFd_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A0D40C(EnFd* this, u8 arg1, Vec3f* arg2, Vec3f* arg3, Vec3f* arg4, u8 arg5, f32 arg6, f32 arg7);
void func_80A0C310(EnFd* this, GlobalContext* globalCtx);
void func_80A0DB44(EnFd* this, GlobalContext* globalCtx);
void func_80A0D730(EnFd* this, GlobalContext* globalCtx);
void func_80A0C3A0(EnFd* this, GlobalContext* globalCtx);
void func_80A0C474(EnFd* this, GlobalContext* globalCtx);
void func_80A0C4F0(EnFd* this, GlobalContext* globalCtx);
void func_80A0C5D0(EnFd* this, GlobalContext* globalCtx);
void func_80A0C7EC(EnFd* this, GlobalContext* globalCtx);
void func_80A0CA44(EnFd* this, GlobalContext* globalCtx);
void func_80A0D614(EnFd* this);
void func_80A0D4FC(EnFd* this);


extern SkeletonHeader D_06005810;
extern Gfx D_060079F8[];
extern Gfx D_06007A78[];
extern Gfx D_06007928[];
extern Gfx D_06007938[];

const ActorInit En_Fd_InitVars = {
    ACTOR_EN_FD,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_FW,
    sizeof(EnFd),
    (ActorFunc)EnFd_Init,
    (ActorFunc)EnFd_Destroy,
    (ActorFunc)EnFd_Update,
    (ActorFunc)EnFd_Draw,
};

static ColliderJntSphItemInit sJntSphItemsInit[12] = {
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040088, 0x00, 0x00 }, 0x01, 0x05, 0x01 },
        { 21, { { 1600, 0, 0 }, 5 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 12, { { 1600, 0, 0 }, 5 }, 400 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 14, { { 800, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 15, { { 1600, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 16, { { 2000, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 17, { { 800, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 18, { { 1600, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 19, { { 2000, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 4, { { 2200, 0, 0 }, 4 }, 400 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 4, { { 5000, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 8, { { 2200, 0, 0 }, 4 }, 400 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 8, { { 5000, 0, 0 }, 4 }, 300 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_UNK10, 0x11, 0x09, 0x39, 0x10, COLSHAPE_JNTSPH },
    12,
    sJntSphItemsInit,
};

CollisionCheckInfoInit2 D_80A0DFE0 = { 0x18, 0x0002, 0x0019, 0x0019, 0xFF };

struct_80034EC0_Entry D_80A0DFEC[] = { { 0x060010B4, 1.0f, 0.0f, -1.0f, 0x03, 0.0f },
                                       { 0x06005C64, 1.0f, 0.0f, -1.0f, 0x03, -10.0f },
                                       { 0x06006044, 0.0f, 0.0f, -1.0f, 0x03, -10.0f },
                                       { 0x06006A18, 1.0f, 0.0f, -1.0f, 0x01, -10.0f },
                                       { 0x06006B64, 0.0f, 0.0f, -1.0f, 0x03, -10.0f } };

s32 func_80A0B6C0(EnFd *this, GlobalContext *globalCtx) {
    if (this->unk_4C2 != 0) {
        return 0;
    }

    if (Actor_SpawnAttached(&globalCtx->actorCtx, this, globalCtx, ACTOR_EN_FW, this->unk_4D0.x, this->unk_4D0.y, this->unk_4D0.z, 0, this->actor.shape.rot.y, 0, this->unk_4BA) == NULL) {
        return 0;
    }

    this->actor.attachedB->colChkInfo.health = this->actor.colChkInfo.health % 8;

    if (this->actor.attachedB->colChkInfo.health == 0) {
        this->actor.attachedB->colChkInfo.health = 8;
    }

    if ((this->actor.flags & 0x2000) == 0x2000) {
        func_8002DE04(globalCtx, &this->actor, this->actor.attachedB);
    }

    this->unk_4B4 = 1;
    return 1;
}

void func_80A0B7B8(EnFd *this, GlobalContext *globalCtx, s16 arg2, s16 arg3) {
    s32 i;
    s16 tmp;

    for (i = 0; i < arg2; i++) {
        tmp = ((i * 360.0f) / arg2) * 182.04445f;
        tmp += this->actor.yawTowardsLink;
        Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_FD_FIRE, 
            this->actor.posRot.pos.x, 
            this->actor.posRot.pos.y, 
            this->actor.posRot.pos.z, 
            0, 
            tmp, 
            0, 
            (arg3 * 32768) | i);
    }
}

void func_80A0B8D8(EnFd *this, GlobalContext *globalCtx) {
    Vec3f sp44 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp38 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp2C = { 0.0f, 0.0f, 0.0f };

    if ((this->actionFunc == func_80A0C7EC) || (this->actionFunc == func_80A0C5D0)) {
        sp44.x = this->actor.posRot.pos.x;
        sp44.y = this->actor.groundY + 4.0f;
        sp44.z = this->actor.posRot.pos.z;

        sp2C.x = Math_Rand_ZeroOne();
        sp2C.x = (sp2C.x - 0.5f) + (sp2C.x - 0.5f);

        sp2C.y = Math_Rand_ZeroOne();
        sp2C.y = ((sp2C.y - 0.5f) * 0.2f) + 0.3f;

        sp2C.z = Math_Rand_ZeroOne();
        sp2C.z = (sp2C.z - 0.5f) + (sp2C.z - 0.5f);

        func_80A0D40C(this, 1, &sp44, &sp38, &sp2C, 8, 0.6f, 0.2f);
    }
}

s32 func_80A0BA44(EnFd *this, GlobalContext *globalCtx) {
    if ((this->actionFunc == func_80A0C310) ||
       (this->actionFunc == func_80A0C3A0) ||
       (this->actionFunc == func_80A0C474) ||
       (this->actionFunc == func_80A0CA44)) {
        return 0;
    }

    if ((globalCtx->actorCtx.unk_02 != 0) &&
       (this->actor.xzDistFromLink < 300.0f) &&
       (this->actor.yDistFromLink < 60.0f)) {
        return 1;
    }

    return 0;
}

s32 func_80A0BAE0(EnFd *this, GlobalContext *globalCtx) {
    Player* player = PLAYER;
    ColliderJntSphItem* collider;
    s32 tmp;

    if ((this->collider.base.acFlags & 2) ||
        func_80A0BA44(this, globalCtx)) {
        this->collider.base.acFlags &= ~2;
        if (this->unk_4C2 != 0) {
            return 0;
        }

        collider = &this->collider.list[0];
        if ((collider->body.acHitItem != NULL) && 
            (collider->body.acHitItem->toucher.flags & 0x80)) {
            return 0;
        }

        if (!func_80A0B6C0(this, globalCtx)) {
            return 0;
        }

        this->unk_4C2 = 0x1E;
        this->actor.flags &= ~1;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLAME_DAMAGE);
        func_80032C7C(globalCtx, this);
        return 1;
    }

    if (this->unk_4C4 == 0) {
        tmp = 0;
    } else {
        this->unk_4C4--;
        tmp = this->unk_4C4;
    }

    if ((tmp == 0) && (this->collider.base.atFlags & 2)) {
        this->collider.base.atFlags &= ~2;
        if (this->unk_4C2 != 0) {
            return 0;
        }

        if (this->collider.base.atFlags & 4) {
            return 0;
        }

        this->unk_4C4 = 30;
        Audio_PlayActorSound2(&player->actor, NA_SE_PL_BODY_HIT);
        func_8002F71C(globalCtx, this, this->actor.speedXZ + 2.0f, this->actor.yawTowardsLink, 6.0f);

    }
    return 0;
}

s32 func_80A0BC70(EnFd *this, Actor *refActor, GlobalContext *globalCtx) {
    CollisionPoly* sp54;
    u32 sp50;
    Vec3f sp44;
    f32 tmp;
    s16 tmp2;

    if (Math_Vec3f_DistXYZ(&this->actor.posRot.pos, &refActor->posRot.pos) > 400.0f) {
        return 0;
    }

    tmp = Math_Vec3f_Yaw(&this->actor.posRot.pos, &refActor->posRot.pos);
    tmp2 = tmp - this->actor.shape.rot.y;
    if (ABS(tmp2) >= 0x1C71) {
        return 0;
    }

    if (func_8003DE84(&globalCtx->colCtx, &this->actor.posRot.pos, &refActor->posRot.pos, &sp44, &sp54, 1, 0, 0, 1, &sp50) != 0) {
        return 0;
    }

    return 1;
}

Actor *func_80A0BD78(EnFd *this, GlobalContext *globalCtx) {
    Actor *explosiveActor = globalCtx->actorCtx.actorList[ACTORTYPE_EXPLOSIVES].first;

    while (explosiveActor != NULL) {
        if ((explosiveActor->params != 0) || (explosiveActor->attachedA != 0)) {
            explosiveActor = explosiveActor->next;
            continue;
        } else if (explosiveActor->id != ACTOR_EN_BOM) {
            explosiveActor = explosiveActor->next;
            continue;
        } else if (func_80A0BC70(this, explosiveActor, globalCtx) != 1) {
            explosiveActor = explosiveActor->next;
            continue;
        }

        return explosiveActor;
    }
    return NULL;
}

Actor* func_80A0BE34(EnFd *this, GlobalContext *globalCtx) {
    Actor* playerActor;
    Actor* explosiveActor;

    explosiveActor = func_80A0BD78(this, globalCtx);
    if (explosiveActor != NULL) {
        return explosiveActor;
    }
    if (this->unk_4C4 != 0) {
        return NULL;
    }

    playerActor = &PLAYER->actor;
    if (!func_80A0BC70(this, playerActor, globalCtx)) {
        return NULL;
    }

    return playerActor;
}

Vec3f* func_80A0BEA0(Vec3f *arg0, EnFd *this, f32 arg2, s16 arg3) {
    s16 sp36;
    Vec3f sp28;

    sp36 = Math_Vec3f_Yaw(&this->actor.initPosRot.pos, &this->actor.posRot.pos) + (arg3 * 0x1554);

    sp28.x = (Math_Sins(sp36) * arg2) + this->actor.initPosRot.pos.x;
    sp28.z = (Math_Coss(sp36) * arg2) + this->actor.initPosRot.pos.z;

    sp28.x -= this->actor.posRot.pos.x;
    sp28.z -= this->actor.posRot.pos.z;

    *arg0 = sp28;
    return arg0;
}

s32 func_80A0BF6C(EnFd *this, GlobalContext *globalCtx, f32 arg2, s16 *arg3) {
    CollisionPoly* sp5C;
    u32 sp58;
    Vec3f sp4C;
    Vec3f sp40;
    s16 tmp;

    func_80A0BEA0(&sp40, this, arg2, *arg3);
    sp40.x += this->actor.posRot.pos.x;
    sp40.y = this->actor.posRot.pos.y;
    sp40.z += this->actor.posRot.pos.z;

    if (func_8003DE84(&globalCtx->colCtx, &this->actor.posRot.pos, &sp40, &sp4C, &sp5C, 1, 0, 0, 1, &sp58) != 0) {
        *arg3 = -*arg3;
        return 1;
    }

    switch (this->unk_4C0) {
        case 0:
            if (this->unk_4BE == 0) {
                tmp = 0;
            } else {
                this->unk_4BE--;
                tmp = this->unk_4BE;
            }

            if (tmp == 0) {
                break;
            }
        default:
            return 0;
    }

    if (Math_Rand_ZeroOne() > 0.5f) {
        *arg3 = -*arg3;
    }

    return 1;
}

void func_80A0C0A0(EnFd *this, GlobalContext *globalCtx) {
    if (this->unk_4C2 != 0) {
        Math_SmoothScaleMaxMinF(&this->unk_4CC, 0.0f, 0.3f, 10.0f, 0.0f);
        this->actor.shape.unk_14 = this->unk_4CC;
        if (!(this->unk_4CC >= 0.9f)) {
            this->unk_4C2 = 0;
            this->unk_4BE = 0;
            this->actor.speedXZ = 0.0f;
            this->actionFunc = func_80A0CA44;
        }
    }
}

void EnFd_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFd* this = THIS;

    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06005810, NULL, this->limbDrawTable, this->transitionDrawTable,
                     27);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 32.0f);
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderItems);
    func_80061EFC(&this->actor.colChkInfo, DamageTable_Get(15), &D_80A0DFE0);
    this->actor.flags &= ~1;
    this->actor.flags |= 0x1000000;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_4BC = 1;
    this->actor.gravity = -1.0f;
    this->unk_4BA = (Math_Rand_ZeroOne() < 0.5f) ? -1 : 1;
    this->actor.naviEnemyId = 0x22;
    this->actionFunc = func_80A0C310;
}

void EnFd_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFd* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80A0C310(EnFd* this, GlobalContext* globalCtx) {
    this->actor.posRot.pos = this->actor.initPosRot.pos;
    this->actor.params = 0;
    this->actor.shape.unk_14 = 0xFF;
    this->unk_4B4 = 0;
    this->actor.scale.y = 0.0f;
    this->unk_4CC = 255.0f;
    func_80034EC0(&this->skelAnime, D_80A0DFEC, 0);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLAME_LAUGH);
    this->actionFunc = func_80A0C3A0;
}

void func_80A0C3A0(EnFd* this, GlobalContext* globalCtx) {
    if (func_800A56C8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
        this->actor.velocity.y = 6.0f;
        this->actor.scale.y = 0.01f;
        this->actor.speedXZ = 8.0f;
        this->actor.posRot.rot.y ^= 0x8000;
        this->actor.flags |= 1;
        func_80034EC0(&this->skelAnime, D_80A0DFEC, 1);
        this->actionFunc = func_80A0C474;
    } else {
        this->actor.scale.y = this->skelAnime.animCurrentFrame * (0.01f / this->skelAnime.totalFrames);
        this->actor.shape.rot.y += 0x2000;
        this->actor.posRot.rot.y = this->actor.shape.rot.y;
    }
}

void func_80A0C474(EnFd *this, GlobalContext *globalCtx) {
    if ((this->actor.bgCheckFlags & 1) && !(this->actor.velocity.y > 0.0f)) {
        this->actor.velocity.y = 0.0f;
        this->actor.speedXZ = 0.0f;
        this->actor.posRot.rot.y = this->actor.shape.rot.y;
        func_80034EC0(&this->skelAnime, D_80A0DFEC, 2);
        this->actionFunc = func_80A0C4F0;
    }
}

void func_80A0C4F0(EnFd *this, GlobalContext *globalCtx) {
    Vec3f sp28;

    Math_SmoothScaleMaxMinF(&this->skelAnime.animPlaybackSpeed, 1.0f, 0.1f, 1.0f, 0.0f);
    if (func_800A56C8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
        this->unk_4BE = Math_Rand_S16Offset(0x3C, 0x5A);
        this->unk_4C8 = Math_Vec3f_DistXYZ(&this->actor.posRot.pos, &this->actor.initPosRot.pos);
        func_80A0BEA0(&sp28, this, this->unk_4C8, this->unk_4BA);
        this->actor.posRot.rot.y = Math_atan2f(sp28.x, sp28.z) * 10430.378f;
        func_80034EC0(&this->skelAnime, D_80A0DFEC, 4);
        this->actionFunc = func_80A0C5D0;
    }
}

void func_80A0C5D0(EnFd *this, GlobalContext *globalCtx) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 tmp;

    if ((this->unk_4BE < 0x1F) && (this->unk_4C2 == 0)) {
        func_8002F974(&this->actor, NA_SE_EN_FLAME_FIRE_ATTACK - SFX_FLAG);
    } else {
        func_8002F974(&this->actor, NA_SE_EN_FLAME_ROLL - SFX_FLAG);
    }

    if (this->unk_4BE == 0) {
        tmp = 0;
    } else {
        this->unk_4BE--;
        tmp = this->unk_4BE;
    }

    if (tmp != 0) {
        this->actor.shape.rot.y += this->unk_4BA * 8192;
        if ((this->unk_4BE == 0x1E) && (this->unk_4C2 == 0)) {
            if (this->actor.xzDistFromLink > 160.0f) {
                func_80A0B7B8(this, globalCtx, 8, 0);
            } else {
                func_80A0B7B8(this, globalCtx, 8, 1);
            }
        }
    } else {
        sp34 = this->actor.posRot.rot.y;
        sp34 -= this->actor.shape.rot.y;

        sp2C = 0.0f;
        sp30 = fabsf(sp34);
        sp34 = sp34 / sp30;
        Math_SmoothScaleMaxF(&sp2C, sp30, 0.6f, 8192.0f);
        
        sp2C = sp2C * sp34;
        this->actor.shape.rot.y += (s16)sp2C;

        sp2C = fabsf(sp2C);
        if ((s32)sp2C < 0x12D) {
            this->actor.shape.rot.y = this->actor.posRot.rot.y;
        }

        if (this->actor.shape.rot.y == this->actor.posRot.rot.y) {
            this->unk_4B6 = Math_Vec3f_Yaw(&this->actor.initPosRot.pos, &this->actor.posRot.pos);
            if (this->unk_4BA < 0) {
                this->unk_4B8 = 0xFFFF;
            } else {
                this->unk_4B8 = 0;
            }
            this->unk_4C0 = (globalCtx->state.frames & 7) + 2;
            this->unk_4BE = Math_Rand_S16Offset(0x1E, 0x78);
            func_80034EC0(&this->skelAnime, D_80A0DFEC, 3);
            this->actionFunc = func_80A0C7EC;
        }
    }
}

void func_80A0C7EC(EnFd *this, GlobalContext *globalCtx) {
    s16 tmp;
    Actor* playerActor;
    f32 tmpf1;
    Vec3f sp30;

    if ((func_80A0BF6C(this, globalCtx, this->unk_4C8, &this->unk_4BA) != 0) && (this->unk_4C2 == 0)) {
        this->actor.posRot.rot.y = this->actor.posRot.rot.y ^ 0x8000;
        this->actor.velocity.y = 6.0f;
        this->actor.speedXZ = 0.0f;
        func_80034EC0(&this->skelAnime, D_80A0DFEC, 1);
        this->actionFunc = func_80A0C474;
        return;
    }

    tmp = Math_Vec3f_Yaw(&this->actor.initPosRot.pos, &this->actor.posRot.pos) - this->unk_4B6;
    if (this->unk_4BA > 0) {
        if ((tmp & 0xFFFF) < this->unk_4B8) {
            this->unk_4C0--;
        }
    } else if (this->unk_4B8 < (tmp & 0xFFFF)) {
        this->unk_4C0--;
    }

    if (this->unk_4C0 < 0) {
        this->unk_4C0 = 0;
    }

    this->unk_4B8 = tmp;

    playerActor = func_80A0BE34(this, globalCtx);
    if ((playerActor != NULL) && (this->unk_4C2 == 0)) {
        tmpf1 = Math_Vec3f_DistXYZ(&this->actor.initPosRot.pos, &playerActor->posRot.pos);
    } else {
        tmpf1 = 200.0f;
    }

    Math_SmoothScaleMaxMinF(&this->unk_4C8, tmpf1, 0.3f, 100.0f, 0.0f);
    func_80A0BEA0(&sp30, this, this->unk_4C8, this->unk_4BA);
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, Math_atan2f(sp30.x, sp30.z) * 10430.378f, 4, 0xFA0, 1);
    this->actor.posRot.rot = this->actor.shape.rot;
    func_8002F974(&this->actor, NA_SE_EN_FLAME_RUN - SFX_FLAG);
    if ((this->skelAnime.animCurrentFrame == 6.0f) || (this->skelAnime.animCurrentFrame == 13.0f) || (this->skelAnime.animCurrentFrame == 28.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLAME_KICK);
    }

    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 8.0f, 0.1f, 1.0f, 0.0f);
}

void func_80A0CA44(EnFd *this, GlobalContext *globalCtx) {
    if (this->unk_4BE != 0) {
        this->unk_4BE--;
        if (this->unk_4BE == 0) {
            Actor_Kill(&this->actor);
        }
    } else if (this->actor.params & 0x8000) {
        this->actionFunc = func_80A0C310;
    } else if (this->actor.params & 0x4000) {
        this->actor.params = 0;
        this->unk_4BE = 0x1E;
    }
}

void EnFd_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnFd *this = THIS;
    s32 pad;

    if (this->unk_4BC != 0) {
        func_800F5ACC(0x38);
        this->unk_4BC = 0;
    }

    if (this->actionFunc != func_80A0C310) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        func_80A0B8D8(this, globalCtx);
    }

    if ((this->actor.flags & 0x2000) == 0x2000) {
        if (func_80A0B6C0(this, globalCtx)) {
            this->actor.flags &= ~1;
            this->unk_4C2 = 30;
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLAME_DAMAGE);
            func_80032C7C(globalCtx, &this->actor);
        } else {
            this->actor.flags &= ~0x2000;
        }
    } else if (this->actionFunc != func_80A0CA44) {
        func_80A0BAE0(this, globalCtx);
    }

    Actor_MoveForward(&this->actor);
    func_8002E4B4(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    func_80A0C0A0(this, globalCtx);
    this->actionFunc(this, globalCtx);
    func_80A0D614(this);
    func_80A0D4FC(this);
    if ((this->actionFunc != func_80A0C310) &&
        (this->actionFunc != func_80A0C3A0) &&
        (this->actionFunc != func_80A0CA44)) {
        if ((this->unk_4C4 == 0) && (this->unk_4C2 == 0)) {
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        if ((this->actionFunc == func_80A0C7EC) || (this->actionFunc == func_80A0C5D0)) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

s32 func_80A0CCB8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                  Gfx** gfx) {
    EnFd* this = THIS;

    if ((this->unk_4C2 != 0) && ((limbIndex == 13) || (limbIndex == 21))) {
        *dList = NULL;
    }

    return 0;
}

void func_80A0CCF0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnFd* this = THIS;
    Vec3f spC0 = { 6800.0f, 0.0f, 0.0f };
    Vec3f spB4 = { 6800.0f, 0.0f, 0.0f };
    Vec3f spA8 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp9C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp90 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp84 = { 0.0f, 0.0f, 0.0f };
    s32 i;

    if (limbIndex == 21) {
        Matrix_MultVec3f(&spA8, &this->unk_4D0);
    }

    if (limbIndex == 13) {
        Matrix_MultVec3f(&spA8, &this->actor.posRot2.pos);
    }

    if ((limbIndex == 3) || (limbIndex == 6) || (limbIndex == 7) || (limbIndex == 0xA) || (limbIndex == 0xE) ||
        (limbIndex == 0xF) || (limbIndex == 0x11) || (limbIndex == 0x12) || (limbIndex == 0x14) ||
        (limbIndex == 0x16) || (limbIndex == 0x17) || (limbIndex == 0x18) || (limbIndex == 0x19) ||
        (limbIndex == 0x1A)) {
        if ((globalCtx->state.frames & 1) != 0) {
            for (i = 0; i < 1; i++) {
                Matrix_MultVec3f(&spA8, &sp9C);
                sp9C.x += (Math_Rand_ZeroOne() - 0.5f) * 20.0f;
                sp9C.y += (Math_Rand_ZeroOne() - 0.5f) * 40.0f;
                sp9C.z += (Math_Rand_ZeroOne() - 0.5f) * 20.0f;
                sp90.x = (Math_Rand_ZeroOne() - 0.5f) * 0.4f;
                sp90.y = ((Math_Rand_ZeroOne() - 0.5f) * 0.2f) + 0.6f;
                sp90.z = (Math_Rand_ZeroOne() - 0.5f) * 0.4f;
                func_80A0D40C(this, 2, &sp9C, &sp84, &sp90, 0, 0.006f, 0.0f);
            }
        }
    }

    func_800628A4(limbIndex, &this->collider);
}

#ifdef NON_MATCHING
void EnFd_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Color_RGBA8_n sp8C[] = {
        { 0xFF, 0xFF, 0xC8, 0xFF },
        { 0xC8, 0xC8, 0xC8, 0xFF },
        { 0xFF, 0xFF, 0x00, 0xFF },
    };
    Color_RGBA8_n sp80[] = {
        { 0x00, 0xFF, 0x00, 0xFF },
        { 0x00, 0x00, 0xFF, 0xFF },
        { 0xFF, 0x00, 0x00, 0xFF },
    };
    EnFd* this = THIS;
    u32 sp7C = globalCtx->state.frames;
    //GraphicsContext* localGfxCtx = globalCtx->state.gfxCtx;
    s32 tmp;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fd.c", 0x6D7);
    Matrix_Push();
    func_80A0DB44(this, globalCtx);
    func_80A0D730(this, globalCtx);
    Matrix_Pull();
    if ((this->actionFunc != func_80A0C310) && !(this->unk_4CC < 0.9f)) {

        func_80093D84(globalCtx->state.gfxCtx);

        tmp = this->actor.colChkInfo.health - 1;
        tmp = CLAMP(tmp, 0, 0x17) / 8;

        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0x80, sp8C[tmp].r, sp8C[tmp].g, sp8C[tmp].b, (u8)this->unk_4CC);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, sp80[tmp].r, sp80[tmp].g, sp80[tmp].b, (u8)this->unk_4CC);

        gSPSegment(
            gfxCtx->polyXlu.p++, 0x08,
            Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, 255 - ((sp7C * 6) % 256), 8, 0x40));
        gDPPipeSync(gfxCtx->polyXlu.p++);
        gSPSegment(gfxCtx->polyXlu.p++, 0x09, D_80116280);

        gfxCtx->polyXlu.p = SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                              this->skelAnime.dListCount, func_80A0CCB8, func_80A0CCF0, &this->actor,
                                              gfxCtx->polyXlu.p);
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fd.c", 0x71E);
}
#else
Color_RGBA8 D_80A0E0D0[] = {
    { 0xFF, 0xFF, 0xC8, 0xFF },
    { 0xC8, 0xC8, 0xC8, 0xFF },
    { 0xFF, 0xFF, 0x00, 0xFF },
};
Color_RGBA8 D_80A0E0DC[] = {
    { 0x00, 0xFF, 0x00, 0xFF },
    { 0x00, 0x00, 0xFF, 0xFF },
    { 0xFF, 0x00, 0x00, 0xFF },
};
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/EnFd_Draw.s")
#endif

void func_80A0D40C(EnFd* this, u8 arg1, Vec3f* arg2, Vec3f* arg3, Vec3f* arg4, u8 arg5, f32 arg6, f32 arg7) {
    EnFdStruct1* ptr = this->unk_620;
    s16 i;

    for (i = 0; i < 200; i++, ptr++) {
        if (ptr->unk_00 == 0) {

            ptr->unk_04 = arg6;
            ptr->unk_08 = arg7;

            ptr->unk_01[1] = ptr->unk_01[0] = arg5;
            ptr->unk_00 = arg1;

            ptr->unk_14 = *arg2;
            ptr->unk_2C = *arg4;
            ptr->unk_20 = *arg3;

            if ((arg1 & 0xFF) == 2) {
                ptr->unk_0C.a = 0xFF;
                ptr->unk_01[0] = (s16)(Math_Rand_ZeroOne() * 10.0f);
            }
            break;
        }
    }
}

void func_80A0D4FC(EnFd *this) {
    EnFdStruct1 *ptr = this->unk_620;
    s16 i;

    for (i = 0; i < 200; i++, ptr++) {
        if (ptr->unk_00 == 1) {
            ptr->unk_01[0]--;
            if (ptr->unk_01[0] == 0) {
                ptr->unk_00 = 0;
            }

            ptr->unk_2C.x = (Math_Rand_ZeroOne() * 0.4f) - 0.2f;
            ptr->unk_2C.z = (Math_Rand_ZeroOne() * 0.4f) - 0.2f;

            ptr->unk_14.x += ptr->unk_20.x;
            ptr->unk_14.y += ptr->unk_20.y;
            ptr->unk_14.z += ptr->unk_20.z;

            ptr->unk_20.x += ptr->unk_2C.x;
            ptr->unk_20.y += ptr->unk_2C.y;
            ptr->unk_20.z += ptr->unk_2C.z;

            ptr->unk_04 += ptr->unk_08;
        }
    }
}

void func_80A0D614(EnFd *this) {
    EnFdStruct1* ptr = this->unk_620;
    s16 i;
    Color_RGBA8_n sp8[] = {
        {0xFF, 0x80, 0x00, 0x00}, 
        {0xFF, 0x00, 0x00, 0x00}, 
        {0xFF, 0xFF, 0x00, 0x00}, 
        {0xFF, 0x00, 0x00, 0x00}
    };   

    for (i = 0; i < 200; i++, ptr++) {
        if (ptr->unk_00 == 2) {
            ptr->unk_14.x = ptr->unk_14.x + ptr->unk_20.x;
            ptr->unk_14.y = ptr->unk_14.y + ptr->unk_20.y;
            ptr->unk_14.z = ptr->unk_14.z + ptr->unk_20.z;

            ptr->unk_01[0]++;

            ptr->unk_20.x = ptr->unk_20.x + ptr->unk_2C.x;
            ptr->unk_20.y = ptr->unk_20.y + ptr->unk_2C.y;
            ptr->unk_20.z = ptr->unk_20.z + ptr->unk_2C.z;

            ptr->unk_0C.r = sp8[ptr->unk_01[0] % 4].r;
            ptr->unk_0C.g = sp8[ptr->unk_01[0] % 4].g;
            ptr->unk_0C.b = sp8[ptr->unk_01[0] % 4].b;

            if (ptr->unk_0C.a > 30) {
                ptr->unk_0C.a -= 30;
            } else {
                ptr->unk_0C.a = 0;
                ptr->unk_00 = 0;
            }
        }
    }
}

#ifdef NON_MATCHING
// stack memes
void func_80A0D730(EnFd* this, GlobalContext* globalCtx) {

    static UNK_TYPE D_80A0E0F8[] = {
        0x040539B0, 0x040535B0, 0x040531B0, 0x04052DB0, 
        0x040529B0, 0x040525B0, 0x040521B0, 0x04051DB0,
    };

    EnFdStruct1* ptr = this->unk_620;
    // GraphicsContext* localgfxCtx = globalCtx->state.gfxCtx;

    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];
    s16 i;
    u8 flag;
    s16 tmp;

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fd.c", 0x7B1);
    flag = 0;
    func_80093D84(globalCtx->state.gfxCtx);

    for (i = 0; i < 200; i++, ptr++) {
        if (ptr->unk_00 == 1) {
            if (flag == 0) {
                
                gfxCtx->polyXlu.p = Gfx_CallSetupDL(gfxCtx->polyXlu.p, 0);
                if (this){};
                gSPDisplayList(gfxCtx->polyXlu.p++, D_06007928);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 255, 10, 0, (this->unk_4CC / 255.0f) * 255);
                flag = 1;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 255, 255, 0, (this->unk_4CC / 255.0f) * 255);
            gDPPipeSync(gfxCtx->polyXlu.p++);

            Matrix_Translate(ptr->unk_14.x, ptr->unk_14.y, ptr->unk_14.z, 0);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_Scale(ptr->unk_04, ptr->unk_04, 1.0f, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_fd.c", 0x7D6),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            tmp = (8.0f / ptr->unk_01[1]) * ptr->unk_01[0];
            gSPSegment(gfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A0E0F8[tmp]));
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06007938);
        }
    }
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fd.c", 0x7E4);
}
#else
UNK_TYPE D_80A0E0F8[] = {
    0x040539B0, 0x040535B0, 0x040531B0, 0x04052DB0, 
    0x040529B0, 0x040525B0, 0x040521B0, 0x04051DB0,
};
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0D730.s")
#endif

#ifdef NON_MATCHING
// Regalloc
void func_80A0DB44(EnFd* this, GlobalContext* globalCtx) {
    EnFdStruct1* ptr = this->unk_620;
    s16 i;
    u8 flag;

    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fd.c", 0x7F2);

    flag = 0;

    if (1) {};
    func_80093D84(globalCtx->state.gfxCtx);

    for (i = 0; i < 200; i++, ptr++) {
        if (ptr->unk_00 == 2) {
            if (!flag) {
                func_80093D84(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_060079F8);
                flag = 1;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, ptr->unk_0C.r, ptr->unk_0C.g, ptr->unk_0C.b,
                            ptr->unk_0C.a * (this->unk_4CC / 255.0f));
            gDPPipeSync(gfxCtx->polyXlu.p++);

            Matrix_Translate(ptr->unk_14.x, ptr->unk_14.y, ptr->unk_14.z, 0);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_Scale(ptr->unk_04, ptr->unk_04, 1.0f, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_fd.c", 0x810),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06007A78);
        }
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fd.c", 0x817);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0DB44.s")
#endif
