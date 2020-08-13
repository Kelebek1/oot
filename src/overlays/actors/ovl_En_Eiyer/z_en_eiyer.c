#include "z_en_eiyer.h"

#define FLAGS 0x00000005

#define THIS ((EnEiyer*)thisx)

void EnEiyer_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEiyer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEiyer_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEiyer_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A00218(EnEiyer* this);
void func_80A003B4(EnEiyer* this);
void func_80A00858(EnEiyer* this, GlobalContext* globalCtx);
void func_80A00A84(EnEiyer* this, GlobalContext* globalCtx);
void func_80A00950(EnEiyer* this, GlobalContext* globalCtx);
void func_80A008D4(EnEiyer* this, GlobalContext* globalCtx);
void func_80A012F4(EnEiyer* this, GlobalContext* globalCtx);
void func_80A00B18(EnEiyer* this, GlobalContext* globalCtx);
void func_80A00C70(EnEiyer* this, GlobalContext* globalCtx);
void func_80A00E8C(EnEiyer* this, GlobalContext* globalCtx);
void func_80A00F84(EnEiyer* this, GlobalContext* globalCtx);
void func_80A01010(EnEiyer* this, GlobalContext* globalCtx);
void func_80A01374(EnEiyer* this, GlobalContext* globalCtx);
void func_80A01104(EnEiyer* this, GlobalContext* globalCtx);
void func_80A01240(EnEiyer* this, GlobalContext* globalCtx);

extern SkeletonHeader D_06003410;
extern AnimationHeader D_060012AC;
extern AnimationHeader D_06000704;
extern AnimationHeader D_06000FC0;
extern AnimationHeader D_060004C4;
extern AnimationHeader D_06000288;

const ActorInit En_Eiyer_InitVars = {
    ACTOR_EN_EIYER,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_EI,
    sizeof(EnEiyer),
    (ActorFunc)EnEiyer_Init,
    (ActorFunc)EnEiyer_Destroy,
    (ActorFunc)EnEiyer_Update,
    (ActorFunc)EnEiyer_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK0, 0x11, 0x09, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x04, 0x08 }, { 0x00000019, 0x00, 0x00 }, 0x09, 0x01, 0x01 },
    { 27, 17, -10, { 0, 0, 0 } },
};

CollisionCheckInfoInit D_80A0199C = { 0x02, 0x002D, 0x000F, 0x64 };

DamageTable D_80A019A4 = { 0x10, 0x02, 0x01, 0x02, 0x10, 0x02, 0x02, 0x02, 0x01, 0x02, 0x04,
                           0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x04, 0x04, 0x00, 0x00,
                           0x01, 0x04, 0x02, 0x02, 0x08, 0x04, 0x00, 0x00, 0x04, 0x00 };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(naviEnemyId, 25, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 5, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 2500, ICHAIN_STOP),
};

void EnEiyer_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEiyer* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 600.0f, ActorShadow_DrawFunc_Circle, 65.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06003410, &D_060012AC, this->limbDrawTable,
                   this->transitionDrawTable, 19);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    func_80061ED4(&this->actor.colChkInfo, &D_80A019A4, &D_80A0199C);
    if (this->actor.params < 3) {
        Actor* actor = Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_EIYER,
                                           this->actor.initPosRot.pos.x, this->actor.initPosRot.pos.y,
                                           this->actor.initPosRot.pos.z, 0, this->actor.shape.rot.y + 0x4000, 0,
                                           this->actor.params + 1);
        if (actor == NULL) {
            Actor_Kill(&this->actor);
            return;
        }

        if (this->actor.params == 0) {
            Actor* actor = this->actor.attachedB;
            s32 i = 0;

            while (i != 3) {
                if (actor == NULL) {
                    break;
                }
                i++;
                actor = actor->attachedB;
            }

            if (i != 3) {
                actor = &this->actor;
                while (actor != NULL) {
                    Actor_Kill(actor);
                    actor = actor->attachedB;
                }
                return;
            }

            this->actor.attachedB->attachedA = &this->actor;
            this->actor.attachedB->attachedB->attachedA = &this->actor;
            this->actor.attachedB->attachedB->attachedB->attachedA = &this->actor;
        }
    }

    if ((this->actor.params == 0) || (this->actor.params == 10)) {
        func_80A00218(this);
    } else {
        func_80A003B4(this);
    }
}

void EnEiyer_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnEiyer* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A001A4(EnEiyer* this) {
    this->actor.posRot.pos.x = (Math_Sins(this->actor.posRot.rot.y) * 80.0f) + this->actor.initPosRot.pos.x;
    this->actor.posRot.pos.z = (Math_Coss(this->actor.posRot.rot.y) * 80.0f) + this->actor.initPosRot.pos.z;
    this->actor.shape.rot.y = this->actor.posRot.rot.y + 0x4000;
}

void func_80A00218(EnEiyer* this) {
    this->collider.body.bumper.flags = 0x19;
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_060012AC);
    this->actor.posRot.pos.x = this->actor.initPosRot.pos.x;
    this->actor.posRot.pos.y = this->actor.initPosRot.pos.y - 40.0f;
    this->actor.posRot.pos.z = this->actor.initPosRot.pos.z;
    this->actor.velocity.y = 0.0f;
    this->actor.speedXZ = 0.0f;
    if (this->actor.params != 10) {
        if (this->actor.params == 0) {
            this->actor.posRot.rot.y = Math_Rand_ZeroOne() * 65536.0f;
        } else {
            this->actor.posRot.rot.y = this->actor.attachedA->posRot.rot.y + (this->actor.params * 16384);
        }
        func_80A001A4(this);
    } else {
        s32 rand = Math_Rand_ZeroOne() * 65536.0f;
        this->actor.shape.rot.y = rand;
        this->actor.posRot.rot.y = rand;
    }

    this->collider.base.atFlags &= ~1;
    this->collider.base.acFlags &= ~1;
    this->actor.flags &= ~0x1001;
    this->actor.shape.unk_10 = 0.0f;
    this->actor.shape.unk_08 = 0.0f;
    this->actionFunc = func_80A00858;
}

void func_80A00358(EnEiyer* this) {
    if (this->actor.params == 0xA) {
        this->actionFunc = func_80A00950;
        this->actor.speedXZ = -0.5f;
    } else {
        this->actionFunc = func_80A008D4;
    }

    this->collider.base.acFlags |= 1;
    this->actor.flags &= ~0x10;
    this->actor.flags |= 1;
}

void func_80A003B4(EnEiyer* this) {
    this->actor.flags &= ~1;
    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_80A00A84;
}

void func_80A003DC(EnEiyer* this, GlobalContext* globalCtx) {
    this->actor.speedXZ = 0.0f;

    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_06000704);
    this->collider.body.bumper.flags = 0xFFCFFFFF;
    this->unk_27C = this->actor.posRot.pos;
    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    this->actor.flags |= 0x1000;
    this->collider.base.acFlags &= ~1;
    this->actor.shape.unk_10 = 65.0f;
    this->actor.shape.unk_08 = 600.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_OCTAROCK_JUMP);
    func_8002949C(globalCtx, &this->actor.posRot.pos, 0, 0, 1, 0x2BC);
    this->actionFunc = func_80A00B18;
}

void func_80A004BC(EnEiyer* this) {
    this->unk_196 = this->actor.shape.rot.y;
    this->unk_27C.y = (cosf(-0.3926991f) * 5.0f) + this->actor.posRot.pos.y;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000FC0, -5.0f);
    this->unk_194 = 0x3C;
    this->actionFunc = func_80A00C70;
}

void func_80A00534(EnEiyer* this) {
    this->actionFunc = func_80A00E8C;
}

void func_80A00544(EnEiyer* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->actor.velocity.y = 0.0f;
    this->unk_27C.y = player->actor.posRot.pos.y + 15.0f;
    this->collider.base.atFlags |= 1;
    this->collider.base.atFlags &= ~2;
    this->actionFunc = func_80A00F84;
}

void func_80A00588(EnEiyer* this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_060004C4, -3.0f);
    this->collider.base.atFlags &= ~1;
    this->actor.flags |= 0x10;
    this->unk_194 = -1;
    this->actor.gravity = 0.0f;
    this->collider.dim.height = sCylinderInit.dim.height;
    this->actionFunc = func_80A01010;
}

void func_80A00600(EnEiyer* this) {
    this->unk_27C.y = this->actor.posRot.pos.y;
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000FC0, 2.0f, 0.0f, 0.0f, 0, -3.0f);
    this->unk_194 = 0x28;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.speedXZ = 5.0f;
    func_8003426C(&this->actor, 0x4000, 0xC8, 0, 0x28);
    this->collider.base.acFlags &= ~1;
    this->actionFunc = func_80A01104;
}

void func_80A006B0(EnEiyer* this) {
    this->unk_194 = 0x14;
    func_8003426C(&this->actor, 0x4000, 0xC8, 0, 0x28);
    if (this->collider.body.bumper.flags != 0x19) {
        this->actor.speedXZ = 6.0f;
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000FC0, -3.0f);
    } else {
        this->actor.speedXZ -= 6.0f;
    }

    this->collider.body.bumper.flags = 0xFFCFFFFF;
    this->collider.base.atFlags &= ~1;
    this->collider.base.acFlags &= ~1;
    this->actionFunc = func_80A01240;
}

void func_80A0076C(EnEiyer* this) {
    this->actor.dmgEffectParams |= 0x2000;
    this->actionFunc = func_80A012F4;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
}

void func_80A00794(EnEiyer* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000288, 2.0f, 0.0f, 0.0f, 0, -8.0f);
    this->unk_194 = 0x50;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = -1.0f;
    this->collider.dim.height = sCylinderInit.dim.height + 8;
    func_8003426C(&this->actor, 0, 0xC8, 0, 0x50);
    this->collider.base.atFlags &= ~1;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_FREEZE);
    this->actionFunc = func_80A01374;
}

void func_80A00858(EnEiyer* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (Math_ApproxF(&this->actor.posRot.pos.y, this->actor.initPosRot.pos.y, 0.75f) != 0) {
        func_80A00358(this);
    }
}

void func_80A008A4(EnEiyer* this, GlobalContext* globalCtx) {
    if (this->collider.base.maskB & 1) {
        this->collider.base.maskB &= ~1;
        func_80A003DC(this, globalCtx);
    }
}

void func_80A008D4(EnEiyer* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actor.posRot.rot.y -= 0x60;
    func_80A001A4(this);
    func_80A008A4(this, globalCtx);
    if ((this->actor.params != 0) && (((EnEiyer*)this->actor.attachedA)->actionFunc != func_80A008D4)) {
        func_80A003B4(this);
    }
}

void func_80A00950(EnEiyer* this, GlobalContext* globalCtx) {
    s32 sp24;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (func_8002DBB0(&this->actor, &this->actor.initPosRot.pos) > 100.0f) {
        this->unk_196 = func_8002DAC0(&this->actor, &this->actor.initPosRot.pos) + 0x8000;
    } else if (this->unk_196 == this->actor.posRot.rot.y) {
        if (Math_Rand_ZeroOne() > 0.99f) {
            sp24 = (Math_Rand_ZeroOne() < 0.5f) ? -1 : 1;
            this->unk_196 = (((Math_Rand_ZeroOne() * 8192.0f) + 8192.0f) * sp24) + this->actor.posRot.rot.y;
        }
    }

    Math_ApproxUpdateScaledS(&this->actor.posRot.rot.y, this->unk_196, 0xB6);
    func_80A008A4(this, globalCtx);
}

void func_80A00A84(EnEiyer* this, GlobalContext* globalCtx) {
    EnEiyer* refActor;

    if ((this->actor.initPosRot.pos.y - 50.0f) < this->actor.posRot.pos.y) {
        this->actor.posRot.pos.y -= 0.5f;
    }

    refActor = (EnEiyer*)this->actor.attachedA;
    if (refActor->actionFunc == func_80A012F4) {
        Actor_Kill(&this->actor);
    } else if (refActor->actionFunc == func_80A00858) {
        func_80A00218(this);
    }
}

void func_80A00B18(EnEiyer* this, GlobalContext* globalCtx) {
    s32 sp3C = SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    f32 sp38 = this->skelAnime.animCurrentFrame;

    if (sp38 < 12.0f) {
        f32 sp34;

        this->actor.posRot.pos.y = ((1.0f - cosf(0.2607522f * sp38)) * 40.0f) + this->actor.initPosRot.pos.y;
        sp34 = sinf(0.2607522f * sp38) * -40.0f;
        this->actor.posRot.pos.x = (Math_Sins(this->actor.shape.rot.y) * sp34) + this->unk_27C.x;
        this->actor.posRot.pos.z = (Math_Coss(this->actor.shape.rot.y) * sp34) + this->unk_27C.z;
    } else {
        Math_ApproxF(&this->actor.posRot.pos.y, this->actor.initPosRot.pos.y + 80.0f, 0.5f);
        this->actor.speedXZ = 0.8f;
    }

    if (sp3C != 0) {
        this->collider.base.acFlags |= 1;
        func_80A004BC(this);
    } else {
        u32 sp30;

        this->actor.groundY =
            func_8003C9A4(&globalCtx->colCtx, &this->actor.floorPoly, &sp30, &this->actor, &this->actor.posRot.pos);
    }
}

void func_80A00C70(EnEiyer* this, GlobalContext* globalCtx) {
    f32 sp2C;
    f32 sp28;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_194 != 0) {
        this->unk_194--;
    }

    sp2C = this->skelAnime.animCurrentFrame;
    Math_SmoothScaleMaxF(&this->unk_27C.y, (this->actor.groundY + 80.0f) + 5.0f, 0.3f, this->actor.speedXZ);
    sp28 = cosf((sp2C - 5.0f) * 0.07853982f);
    this->actor.posRot.pos.y = this->unk_27C.y - (sp28 * 5.0f);
    if (sp2C <= 45.0f) {
        Math_ApproxF(&this->actor.speedXZ, 1.0f, 0.03f);
    } else {
        Math_ApproxF(&this->actor.speedXZ, 1.5f, 0.03f);
    }

    if (this->actor.bgCheckFlags & 8) {
        this->unk_196 = this->actor.wallPolyRot;
    }

    if (Math_ApproxUpdateScaledS(&this->actor.posRot.rot.y, this->unk_196, 0xB6) != 0) {
        if ((this->unk_194 != 0) || (Math_Rand_ZeroOne() > 0.05f)) {
            this->actor.posRot.rot.y += 0x100;
        } else {
            s16 sp26 = Math_Rand_S16Offset(0x2000, 0x2000);
            this->unk_196 = (((Math_Rand_ZeroOne() < 0.5f) ? -1 : 1) * sp26) + this->actor.posRot.rot.y;
        }
    }

    if ((this->unk_194 == 0) && (this->actor.yDistFromLink < 0.0f) && (this->actor.xzDistFromLink < 120.0f)) {
        func_80A00534(this);
    }

    func_8002F974(&this->actor, NA_SE_EN_EIER_FLY - SFX_FLAG);
}

void func_80A00E8C(EnEiyer* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f sp28;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if ((this->actor.shape.rot.x > 0) && (this->actor.shape.rot.x < 0x8000)) {
        sp28.x = player->actor.posRot.pos.x;
        sp28.y = player->actor.posRot.pos.y + 20.0f;
        sp28.z = player->actor.posRot.pos.z;
        if (Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, func_8002DB28(&this->actor, &sp28), 0x1000) != 0) {
            func_80A00544(this, globalCtx);
        }
    } else {
        this->actor.shape.rot.x = this->actor.shape.rot.x - 0x1000;
    }

    this->actor.posRot.rot.x = -this->actor.shape.rot.x;
    Math_ApproxF(&this->actor.speedXZ, 5.0f, 0.3f);
    Math_SmoothScaleMaxS(&this->actor.posRot.rot.y, this->actor.yawTowardsLink, 2, 0x71C);
    func_8002F974(&this->actor, NA_SE_EN_EIER_FLY - SFX_FLAG);
}

void func_80A00F84(EnEiyer* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actor.speedXZ *= 1.1f;
    if ((this->actor.bgCheckFlags & 8) || (this->actor.bgCheckFlags & 1)) {
        func_80A00588(this);
    }

    if (this->collider.base.atFlags & 2) {
        this->collider.base.atFlags &= ~3;
    }

    func_8002F974(&this->actor, NA_SE_EN_EIER_FLY - SFX_FLAG);
}

void func_80A01010(EnEiyer* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_ApproxUpdateScaledS(&this->actor.posRot.rot.x, -0x4000, 0x450);
    Math_ApproxF(&this->actor.speedXZ, 7.0f, 1.0f);
    if (this->unk_194 == -1) {
        if ((this->actor.bgCheckFlags & 8) || (this->actor.bgCheckFlags & 1)) {
            this->unk_194 = 10;
            Audio_PlaySoundAtPosition(globalCtx, &this->actor.posRot.pos, 0x1E, NA_SE_EN_OCTAROCK_SINK);
            if (this->actor.bgCheckFlags & 1) {
                func_8002949C(globalCtx, &this->actor.posRot.pos, 0, 0, 1, 0x2BC);
            }
        }
    } else {
        if (this->unk_194 != 0) {
            this->unk_194--;
        }

        if (this->unk_194 == 0) {
            this->actor.shape.rot.x = 0;
            this->actor.posRot.rot.x = 0;
            func_80A00218(this);
        }
    }
}

void func_80A01104(EnEiyer* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_194 != 0) {
        this->unk_194--;
    }

    Math_SmoothScaleMaxF(&this->unk_27C.y, (this->actor.groundY + 80.0f) + 5.0f, 0.5f, this->actor.speedXZ);
    this->actor.posRot.pos.y = this->unk_27C.y - 5.0f;
    if (this->actor.bgCheckFlags & 8) {
        this->unk_196 = this->actor.wallPolyRot;
    } else {
        this->unk_196 = this->actor.yawTowardsLink + 0x8000;
    }

    Math_ApproxUpdateScaledS(&this->actor.posRot.rot.y, this->unk_196, 0x38E);
    Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, 0, 0x200);
    this->actor.shape.rot.z = sinf(this->unk_194 * 0.62831855f) * 5120.0f;
    if (this->unk_194 == 0) {
        this->actor.shape.rot.x = 0;
        this->actor.shape.rot.z = 0;
        this->collider.base.acFlags |= 1;
        func_80A004BC(this);
    }

    this->actor.posRot.rot.x = -this->actor.shape.rot.x;
}

void func_80A01240(EnEiyer* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->actor.speedXZ > 0.0f) {
        Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, -0x4000, 0x400);
    } else {
        Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, 0x4000, 0x400);
    }

    this->actor.shape.rot.z += 0x1000;
    if (this->unk_194 != 0) {
        this->unk_194--;
    }

    this->actor.posRot.rot.x = -this->actor.shape.rot.x;
    if ((this->unk_194 == 0) || (this->actor.bgCheckFlags & 0x10)) {
        func_80A0076C(this);
    }
}

void func_80A012F4(EnEiyer* this, GlobalContext* globalCtx) {
    s16 tmp = this->actor.shape.unk_14 - 5;

    this->actor.shape.unk_14 = CLAMP_MIN(tmp, 0);
    this->actor.posRot.pos.y -= 2.0f;
    if (this->actor.shape.unk_14 == 0) {
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.posRot.pos, 0x50);
        Actor_Kill(&this->actor);
    }
}

void func_80A01374(EnEiyer* this, GlobalContext* globalCtx) {
    if (this->unk_194 != 0) {
        this->unk_194--;
    }

    Math_ApproxUpdateScaledS(&this->actor.shape.rot.x, 0, 0x200);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (func_800A56C8(&this->skelAnime, 0.0f) != 0) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_EIER_FLUTTER);
    }

    if ((this->actor.bgCheckFlags & 2) != 0) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_DODO_M_GND);
    }

    if (this->unk_194 == 0) {
        this->actor.gravity = 0.0f;
        this->actor.velocity.y = 0.0f;
        this->collider.dim.height = sCylinderInit.dim.height;
        func_80A004BC(this);
    }
}

void func_80A0142C(EnEiyer* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= ~2;
        func_80035650(&this->actor, &this->collider.body, 1);
        if ((this->actor.colChkInfo.damageEffect != 0) || (this->actor.colChkInfo.damage != 0)) {
            if (Actor_ApplyDamage(&this->actor) == 0) {
                func_80032C7C(globalCtx, &this->actor);
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_EIER_DEAD);
                this->actor.flags &= ~1;
            }

            if (this->collider.body.bumper.flags == 0x19) {
                if (this->actor.colChkInfo.damage == 0) {
                    func_80A003DC(this, globalCtx);

                } else {
                    func_80A006B0(this);
                }
            } else if (this->actor.colChkInfo.damageEffect == 1) {
                if (this->actionFunc != func_80A01374) {
                    func_80A00794(this);
                }
            } else if (this->actor.colChkInfo.health != 0) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_EIER_DAMAGE);
                func_80A00600(this);
            } else {
                this->collider.dim.height = sCylinderInit.dim.height;
                func_80A006B0(this);
            }
        }
    }
}

void EnEiyer_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEiyer* this = THIS;
    s32 pad;

    func_80A0142C(this, globalCtx);
    this->actionFunc(this, globalCtx);
    if ((this->actor.posRot.rot.x == 0) || (this->actionFunc == func_80A01374)) {
        Actor_MoveForward(&this->actor);
    } else {
        func_8002D97C(&this->actor);
    }

    if ((this->actionFunc == func_80A00C70) || (this->actionFunc == func_80A00F84) ||
        (this->actionFunc == func_80A01374) || (this->actionFunc == func_80A01240) ||
        (this->actionFunc == func_80A01104) || ((this->actionFunc == func_80A01010) && (this->unk_194 == -1))) {
        func_8002E4B4(globalCtx, &this->actor, 5.0f, 27.0f, 30.0f, 7);
    }

    if ((this->actor.params == 10) || ((this->actionFunc != func_80A00858) && (this->actionFunc != func_80A008D4))) {
        this->actor.shape.rot.y = this->actor.posRot.rot.y;
    }

    if ((this->actor.params == 0) || (this->actor.params == 10)) {
        Collider_CylinderUpdate(&this->actor, &this->collider);
        if (this->collider.base.atFlags & 1) {
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
        if (this->collider.base.acFlags & 1) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
        if (this->actionFunc != func_80A00B18) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }

    if (this->actor.flags & 1) {
        this->actor.posRot2.pos.x = (Math_Sins(this->actor.shape.rot.y) * 12.5f) + this->actor.posRot.pos.x;
        this->actor.posRot2.pos.z = (Math_Coss(this->actor.shape.rot.y) * 12.5f) + this->actor.posRot.pos.z;
        this->actor.posRot2.pos.y = this->actor.posRot.pos.y;
    }
}

s32 func_80A0178C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                  Gfx** gfx) {
    EnEiyer* this = THIS;

    if (limbIndex == 1) {
        pos->z += 2500.0f;
    }

    if ((this->collider.body.bumper.flags == 25) && (limbIndex != 9) && (limbIndex != 10)) {
        *dList = NULL;
    }

    return 0;
}

void EnEiyer_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnEiyer* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_eiyer.c", 0x5D6);
    if (this->actionFunc != func_80A012F4) {
        func_80093D18(globalCtx->state.gfxCtx);
        gSPSegment(gfxCtx->polyOpa.p++, 0x08, &D_80116280[2]);
        gDPSetEnvColor(gfxCtx->polyOpa.p++, 255, 255, 255, 255);
        gfxCtx->polyOpa.p = SkelAnime_Draw2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                            func_80A0178C, NULL, &this->actor, gfxCtx->polyOpa.p);
    } else {
        func_80093D84(globalCtx->state.gfxCtx);
        gSPSegment(gfxCtx->polyXlu.p++, 0x08, D_80116280);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 255, 255, 255, this->actor.shape.unk_14);
        gfxCtx->polyXlu.p = SkelAnime_Draw2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                            func_80A0178C, NULL, &this->actor, gfxCtx->polyXlu.p);
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_eiyer.c", 0x605);
}
