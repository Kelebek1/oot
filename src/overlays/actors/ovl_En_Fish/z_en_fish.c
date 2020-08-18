#include "z_en_fish.h"
#include "vt.h"

#define FLAGS 0x00000000

#define THIS ((EnFish*)thisx)

void EnFish_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A16618(EnFish* this);
void func_80A157A4(EnFish* this);
void func_80A15F24(EnFish* this);
void func_80A158EC(EnFish* this);
void func_80A15D18(EnFish* this);
void func_80A15AD4(EnFish* this);
void func_80A160BC(EnFish* this);
void func_80A163DC(EnFish* this);
void func_80A16670(EnFish* this, GlobalContext* globalCtx);
void func_80A157FC(EnFish* this, GlobalContext* globalCtx);
void func_80A15F84(EnFish* this, GlobalContext* globalCtx);
void func_80A15944(EnFish* this, GlobalContext* globalCtx);
void func_80A15D68(EnFish* this, GlobalContext* globalCtx);
void func_80A15B2C(EnFish* this, GlobalContext* globalCtx);
void func_80A16200(EnFish* this, GlobalContext* globalCtx);
void func_80A16450(EnFish* this, GlobalContext* globalCtx);

extern SkeletonHeader D_04018FE0;
extern AnimationHeader D_0401909C;
extern AnimationHeader D_040185FC;

EnFish* D_80A17010 = NULL;
f32 D_80A17014 = 0.0f;
f32 D_80A17018 = 0.0f;

static ColliderJntSphItemInit sJntSphItemsInit[1] = {
    {
        { 0x00, { 0x00000000, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 5 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x10, COLSHAPE_JNTSPH },
    1,
    sJntSphItemsInit,
};

const ActorInit En_Fish_InitVars = {
    ACTOR_EN_FISH,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnFish),
    (ActorFunc)EnFish_Init,
    (ActorFunc)EnFish_Destroy,
    (ActorFunc)EnFish_Update,
    (ActorFunc)EnFish_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 900, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 40, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 700, ICHAIN_STOP),
};

f32 func_80A15280(Vec3f* a, Vec3f* b) {
    return SQ(a->x - b->x) + SQ(a->z - b->z);
}

void func_80A152AC(EnFish* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0401909C, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_0401909C.genericHeader),
                         1, 2.0f);
}

void func_80A15310(EnFish* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_040185FC, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_040185FC.genericHeader),
                         1, 2.0f);
}

void func_80A15374(EnFish* this) {
    this->unk_24A = 0x190;
    Actor_SetScale(&this->actor, 0.001f);
    this->actor.draw = NULL;
}

#ifdef NON_MATCHING
// Sym
void func_80A153AC(EnFish* this, GlobalContext* globalCtx) {
    if (D_80A17010 == NULL) {
        D_80A17010 = this;
        Actor_SetScale(&this->actor, 0.01f);
        this->actor.draw = EnFish_Draw;
        this->actor.shape.rot.x = 0;
        this->actor.shape.rot.y = -0x6410;
        this->actor.shape.rot.z = 0x4000;
        this->actor.shape.unk_08 = 600.0f;
        D_80A17014 = 10.0f;
        D_80A17018 = 0.0f;
        this->actor.flags |= 0x10;
        func_80A15310(this);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fish/func_80A153AC.s")
#endif

void func_80A15444(EnFish* this) {
    D_80A17010 = NULL;
    D_80A17014 = 0.0f;
    D_80A17018 = 0.0f;
}

void EnFish_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;
    s16 params = this->actor.params;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_04018FE0, &D_0401909C, this->limbDrawTable,
                     this->transitionDrawTable, 7);
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderItems);
    this->actor.colChkInfo.mass = 0x32;
    this->unk_24C = Math_Rand_ZeroOne() * 65535.5f;
    this->unk_24E = Math_Rand_ZeroOne() * 65535.5f;
    if (params == 0) {
        this->actor.flags |= 0x10;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 8.0f);
        func_80A15F24(this);
    } else if (params == 1) {
        func_80A16618(this);
    } else {
        func_80A157A4(this);
    }
}

void EnFish_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    Collider_DestroyJntSph(globalCtx, &THIS->collider);
}

void func_80A155D0(EnFish* this) {
    f32 tmpf1;
    f32 sp18;

    sp18 = Math_Sins(this->unk_24E);
    this->actor.shape.unk_08 += ((Math_Sins(this->unk_24C) * 10.0f) + (sp18 * 5.0f));
    if (this->actor.shape.unk_08 < -200.0f) {
        this->actor.shape.unk_08 = -200.0f;
        return;
    }

    if (this->actor.shape.unk_08 > 200.0f) {
        tmpf1 = 200.0f;
    } else {
        tmpf1 = this->actor.shape.unk_08;
    }
    this->actor.shape.unk_08 = tmpf1;
}

s32 func_80A15688(EnFish* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = PLAYER;
    Vec3f sp1C;

    if (this->actor.xzDistFromLink < 32.0f) {
        sp1C.x = (Math_Sins(this->actor.yawTowardsLink + 0x8000) * 16.0f) + player->actor.posRot.pos.x;
        sp1C.y = player->actor.posRot.pos.y;
        sp1C.z = (Math_Coss(this->actor.yawTowardsLink + 0x8000) * 16.0f) + player->actor.posRot.pos.z;
        if (func_80A15280(&sp1C, &this->actor.posRot.pos) <= 400.0f) {
            return 1;
        }
    }

    return 0;
}

s32 func_80A15774(EnFish* this, GlobalContext* globalCtx) {
    return this->actor.xzDistFromLink < 60.0f;
}

void func_80A157A4(EnFish* this) {
    this->actor.gravity = 0.0f;
    this->actor.minVelocityY = 0.0f;
    this->unk_248 = Math_Rand_S16Offset(5, 0x23);
    this->unk_250 = 0;
    func_80A152AC(this);
    this->actionFunc = func_80A157FC;
}

void func_80A157FC(EnFish* this, GlobalContext* globalCtx) {
    f32 tmpf1;

    func_80A155D0(this);
    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 0.05f, 0.3f, 0.0f);
    tmpf1 = (this->actor.speedXZ * 1.4f) + 0.8f;
    this->skelAnime.animPlaybackSpeed = CLAMP_MAX(tmpf1, 2.0f);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actor.shape.rot.y = this->actor.posRot.rot.y;
    if (this->unk_248 <= 0) {
        func_80A158EC(this);
    } else if (this->actor.attachedB == &this->actor) {
        func_80A15D18(this);
    } else if (func_80A15774(this, globalCtx)) {
        func_80A15AD4(this);
    }
}

void func_80A158EC(EnFish* this) {
    this->actor.gravity = 0.0f;
    this->actor.minVelocityY = 0.0f;
    this->unk_248 = Math_Rand_S16Offset(0xF, 0x2D);
    this->unk_250 = 0;
    func_80A152AC(this);
    this->actionFunc = func_80A15944;
}

void func_80A15944(EnFish* this, GlobalContext* globalCtx) {
    f32 tmpf1;

    func_80A155D0(this);
    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 1.8f, 0.08f, 0.4f, 0.0f);
    if ((func_80A15280(&this->actor.posRot.pos, &this->actor.initPosRot.pos) > 6400.0f) || (this->unk_248 < 4)) {
        func_80077B58(&this->actor.posRot.rot.y, Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.initPosRot.pos),
                      0xBB8);
    } else if ((this->actor.attachedB != NULL) && (this->actor.attachedB != &this->actor)) {
        func_80077B58(&this->actor.posRot.rot.y,
                      Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.attachedB->posRot.pos), 0xBB8);
    }

    this->actor.shape.rot.y = this->actor.posRot.rot.y;
    tmpf1 = (this->actor.speedXZ * 1.5f) + 0.8f;
    this->skelAnime.animPlaybackSpeed = CLAMP_MAX(tmpf1, 4.0f);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_248 <= 0) {
        func_80A157A4(this);
    } else if (this->actor.attachedB == &this->actor) {
        func_80A15D18(this);
    } else if (func_80A15774(this, globalCtx)) {
        func_80A15AD4(this);
    }
}

void func_80A15AD4(EnFish* this) {
    this->actor.gravity = 0.0f;
    this->actor.minVelocityY = 0.0f;
    this->unk_248 = Math_Rand_S16Offset(0xA, 0x28);
    this->unk_250 = 0;
    func_80A152AC(this);
    this->actionFunc = func_80A15B2C;
}

#ifdef NON_MATCHING
// Stack
void func_80A15B2C(EnFish* this, GlobalContext* globalCtx) {
    // s16 pad;
    f32 ret;
    s16 pad2;
    s16 sp34;

    func_80A155D0(this);
    sp34 = func_80A15774(this, globalCtx);
    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 4.2f, 0.08f, 1.4f, 0.0f);
    ret = func_80A15280(&this->actor.posRot.pos, &this->actor.initPosRot.pos);
    if (ret > 25600.0f) {
        func_80077B58(&this->actor.posRot.rot.y, Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.initPosRot.pos),
                      0xBB8);
    } else {
        if ((this->actor.attachedB != NULL) && (this->actor.attachedB != &this->actor)) {
            func_80077B58(&this->actor.posRot.rot.y,
                          Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.attachedB->posRot.pos), 0x7D0);
        } else if (sp34) {
            s16 yaw = this->actor.yawTowardsLink + 0x8000;
            s16 frames = globalCtx->state.frames;
            if (frames & 0x10) {
                if (frames & 0x20) {
                    yaw += 0x2000;
                }
            } else if (frames & 0x20) {
                if (globalCtx) {};
                yaw -= 0x2000;
            }

            func_80077B58(&this->actor.posRot.rot.y, yaw, 0x7D0);
        }
    }

    this->actor.shape.rot.y = this->actor.posRot.rot.y;
    this->skelAnime.animPlaybackSpeed = CLAMP_MAX((this->actor.speedXZ * 1.5f) + 0.8f, 4.0f);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if ((this->unk_248 <= 0) || !sp34) {
        func_80A157A4(this);
    } else if (this->actor.attachedB == &this->actor) {
        func_80A15D18(this);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fish/func_80A15B2C.s")
#endif

void func_80A15D18(EnFish* this) {
    this->actor.gravity = 0.0f;
    this->actor.minVelocityY = 0.0f;
    func_80A152AC(this);
    this->unk_248 = Math_Rand_S16Offset(0xA, 0x28);
    this->unk_250 = 0;
    this->actionFunc = func_80A15D68;
}

#ifdef NON_MATCHING
// Unfixable stack as-is
void func_80A15D68(EnFish* this, GlobalContext* globalCtx) {
    Player* player = PLAYER; // sp48
    s32 pad;

    func_80A155D0(this);
    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 1.8f, 0.1f, 0.5f, 0.0f);
    if (func_80A15280(&this->actor.posRot.pos, &this->actor.initPosRot.pos) > 6400.0f) {
        func_80077B58(&this->actor.posRot.rot.y, Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.initPosRot.pos),
                      0xBB8);
    } else {
        Vec3f sp38;
        s16 sp34;
        s32 pad2;

        if (((s16)globalCtx->state.frames & 0x40) != 0) {
            sp34 = this->actor.yawTowardsLink + 0x9000;
        } else {
            sp34 = this->actor.yawTowardsLink + 0x7000;
        }

        sp38.x = (Math_Sins(sp34) * 20.0f) + player->actor.posRot.pos.x;
        sp38.y = player->actor.posRot.pos.y;
        sp38.z = (Math_Coss(sp34) * 20.0f) + player->actor.posRot.pos.z;
        func_80077B58(&this->actor.posRot.rot.y, Math_Vec3f_Yaw(&this->actor.posRot.pos, &sp38), 0xBB8);
    }

    this->actor.shape.rot.y = this->actor.posRot.rot.y;
    this->skelAnime.animPlaybackSpeed = CLAMP_MAX((this->actor.speedXZ * 1.5f) + 0.8f, 4.0f);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_248 <= 0) {
        func_80A157A4(this);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fish/func_80A15D68.s")
#endif

void func_80A15F24(EnFish* this) {
    this->actor.gravity = -1.0f;
    this->actor.minVelocityY = -10.0f;
    this->actor.shape.unk_08 = 0.0f;
    func_80A15310(this);
    this->unk_250 = 5;
    this->actionFunc = func_80A15F84;
    this->unk_248 = 0x12C;
}

void func_80A15F84(EnFish* this, GlobalContext* globalCtx) {
    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 0.1f, 0.1f, 0.0f);
    func_80077B58(&this->actor.posRot.rot.x, 0x4000, 0x64);
    func_80077B58(&this->actor.posRot.rot.z, -0x4000, 0x64);
    this->actor.shape.rot.x = this->actor.posRot.rot.x;
    this->actor.shape.rot.y = this->actor.posRot.rot.y;
    this->actor.shape.rot.z = this->actor.posRot.rot.z;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->actor.bgCheckFlags & 1) {
        this->unk_248 = 0x190;
        func_80A160BC(this);
    } else if (this->actor.bgCheckFlags & 0x20) {
        func_80A163DC(this);
    } else if ((this->unk_248 <= 0) && (this->actor.params == 0) && (this->actor.groundY < -31990.0f)) {
        osSyncPrintf(VT_COL(YELLOW, BLACK));
        // Outside the world, hello darkness my old friend.
        osSyncPrintf("BG 抜け？ Actor_delete します(%s %d)\n", "../z_en_sakana.c", 0x336);
        osSyncPrintf(VT_RST);
        Actor_Kill(&this->actor);
    }
}

void func_80A160BC(EnFish* this) {
    s32 pad1;
    s32 pad2;
    s32 flag;
    f32 rand;

    this->actor.gravity = -1.0f;
    this->actor.minVelocityY = -10.0f;
    rand = Math_Rand_ZeroOne();
    if (rand < 0.1f) {
        this->actor.velocity.y = (Math_Rand_ZeroOne() * 3.0f) + 2.5f;
        flag = 1;
    } else if (rand < 0.2f) {
        this->actor.velocity.y = (Math_Rand_ZeroOne() * 1.2f) + 0.2f;
        flag = 1;
    } else {
        this->actor.velocity.y = 0.0f;
        if (Math_Rand_ZeroOne() < 0.2f) {
            flag = 1;
        } else {
            flag = 0;
        }
    }

    this->actor.shape.unk_08 = 300.0f;
    func_80A15310(this);
    this->actionFunc = func_80A16200;
    this->unk_250 = 5;
    if (flag && (this->actor.draw != NULL)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_FISH_LEAP);
    }
}

void func_80A16200(EnFish* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 frames = globalCtx->state.frames;
    s16 tmp;

    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, Math_Rand_ZeroOne() * 0.2f, 0.1f, 0.1f, 0.0f);
    tmp = (((frames >> 5) & 2) | ((frames >> 2) & 1)) * 2048;
    tmp *= 0.3f;
    if ((frames & 4) != 0) {
        tmp = -tmp;
    }

    func_80077B58(&this->actor.posRot.rot.x, tmp, 0xFA0);
    func_80077B58(&this->actor.posRot.rot.z, 0x4000, 0x3E8);
    this->actor.posRot.rot.y +=
        (s16)(((Math_Sins(this->unk_24C) * 2000.0f) + (Math_Sins(this->unk_24E) * 1000.0f)) * Math_Rand_ZeroOne());
    this->actor.shape.rot = this->actor.posRot.rot;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_248 <= 0) {
        Actor_Kill(&this->actor);
    } else if (this->unk_248 < 0x3D) {
        if ((frames & 4) != 0) {
            this->actor.draw = EnFish_Draw;
        } else {
            this->actor.draw = NULL;
        }
    } else if (this->actor.bgCheckFlags & 0x20) {
        func_80A163DC(this);
    } else if (this->actor.bgCheckFlags & 1) {
        func_80A160BC(this);
    }
}

void func_80A163DC(EnFish* this) {
    this->actor.initPosRot.pos = this->actor.posRot.pos;
    this->actor.flags |= 0x10;
    this->unk_248 = 0xC8;
    this->actor.gravity = 0.0f;
    this->actor.minVelocityY = 0.0f;
    this->actor.shape.unk_08 = 0.0f;
    func_80A152AC(this);
    this->actionFunc = func_80A16450;
    this->unk_250 = 5;
}

void func_80A16450(EnFish* this, GlobalContext* globalCtx) {
    s32 pad;

    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 2.8f, 0.1f, 0.4f, 0.0f);
    if ((this->actor.bgCheckFlags & 8) || !(this->actor.bgCheckFlags & 0x20)) {
        this->actor.initPosRot.rot.y = Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.initPosRot.pos);
        this->actor.speedXZ *= 0.5f;
    }

    func_80077B58(&this->actor.posRot.rot.x, 0, 0x5DC);
    func_80077B58(&this->actor.posRot.rot.y, this->actor.initPosRot.rot.y, 0xBB8);
    func_80077B58(&this->actor.posRot.rot.z, 0, 0x3E8);
    this->actor.shape.rot = this->actor.posRot.rot;
    if ((this->actor.bgCheckFlags & 1) != 0) {
        Math_ApproxF(&this->actor.posRot.pos.y, this->actor.initPosRot.pos.y - 4.0f, 2.0f);
    } else {
        Math_ApproxF(&this->actor.posRot.pos.y, this->actor.initPosRot.pos.y - 10.0f, 2.0f);
    }

    if (this->unk_248 < 0x64) {
        Actor_SetScale(&this->actor, this->actor.scale.x * 0.982f);
    }

    this->skelAnime.animPlaybackSpeed = CLAMP_MAX((this->actor.speedXZ * 1.5f) + 1.0f, 4.0f);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_248 <= 0) {
        Actor_Kill(&this->actor);
    }
}

void func_80A16618(EnFish* this) {
    this->actor.gravity = 0.0f;
    this->actor.minVelocityY = 0.0f;
    this->unk_248 = Math_Rand_S16Offset(5, 0x23);
    this->unk_250 = 0;
    func_80A152AC(this);
    this->actionFunc = func_80A16670;
}

void func_80A16670(EnFish* this, GlobalContext* globalCtx) {
    static Vec3f D_80A17080 = { 0.0f, 0.0399999991059f, 0.0900000035763f };
    static Vec3f D_80A1708C = { 0.5f, 0.10000000149f, 0.15000000596f };
    s32 pad;
    u32 sp50 = globalCtx->gameplayFrames;
    Vec3f* sp4C;
    f32 sp48;
    f32 sp44;
    s32 pad2;

    if (this->actor.xzDistFromLink < 60.0f) {
        if (this->unk_248 < 0xC) {
            sp4C = &D_80A1708C;
        } else {
            sp4C = &D_80A17080;
        }
    } else {
        if (this->unk_248 < 4) {
            sp4C = &D_80A1708C;
        } else {
            sp4C = &D_80A17080;
        }
    }

    func_80A155D0(this);
    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, sp4C->x, sp4C->y, sp4C->z, 0.0f);
    sp44 = 0.0f;
    if (func_80A15280(&this->actor.posRot.pos, &this->actor.initPosRot.pos) > 225.0f) {
        if (Math_ApproxUpdateScaledS(&this->actor.posRot.rot.y,
                                     Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.initPosRot.pos), 0xC8) == 0) {
            sp44 = 0.5f;
        }
    } else if (this->unk_248 < 4) {
        if (Math_ApproxUpdateScaledS(&this->actor.posRot.rot.y, sp50 * 128, 0x64) == 0) {
            sp44 = 0.5f;
        }
    }

    this->actor.shape.rot.y = this->actor.posRot.rot.y;

    sp48 = ((this->actor.speedXZ * 1.2f) + 0.2f) + sp44;
    this->skelAnime.animPlaybackSpeed = CLAMP(sp48, 1.5f, 0.5);

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_248 <= 0) {
        this->unk_248 = Math_Rand_S16Offset(5, 0x50);
    }
}

void func_80A16898(EnFish* this, GlobalContext* globalCtx) {
    f32 sp24;
    f32 sp20;

    sp24 = Math_Sins(this->unk_24C);
    sp20 = Math_Sins(this->unk_24E);
    D_80A17014 += D_80A17018;
    if (D_80A17014 <= 1.0f) {
        D_80A17014 = 1.0f;
        if (Math_Rand_ZeroOne() < 0.1f) {
            D_80A17018 = (Math_Rand_ZeroOne() * 3.0f) + 2.0f;
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_FISH_LEAP);
        } else {
            D_80A17018 = 0.0f;
        }
    } else {
        D_80A17018 -= 0.4f;
    }

    this->skelAnime.animPlaybackSpeed = ((sp24 + sp20) * 0.5f) + 2.0f;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

void func_80A169C8(EnFish* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 sp28;
    f32 sp24;

    sp28 = Math_Sins(this->unk_24C);
    sp24 = Math_Sins(this->unk_24E);
    this->actor.shape.rot.x -= 0x1F4;
    this->actor.shape.rot.z += 0x64;
    Math_ApproxF(&D_80A17014, 0.0f, 1.0f);
    this->skelAnime.animPlaybackSpeed = ((sp28 + sp24) * 0.5f) + 2.0f;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

void func_80A16A64(EnFish* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 tmpf1;
    CsCmdActorAction* action = globalCtx->csCtx.npcActions[1];
    Vec3f sp40;
    Vec3f sp34;
    s32 pad2;
    CollisionPoly* sp2C;

    if (action == NULL) {
        // Cutscene ended without action 3 destroy being called
        osSyncPrintf("Warning : dousa 3 消滅 が呼ばれずにデモが終了した(%s %d)(arg_data 0x%04x)\n", "../z_en_sakana.c",
                     0x491, this->actor.params);
        func_80A15444(this);
        Actor_Kill(&this->actor);
        return;
    }

    this->unk_24C += 0x111;
    this->unk_24E += 0x500;

    switch (action->action) {
        case 1:
            func_80A16898(this, globalCtx);
            break;

        case 2:
            func_80A169C8(this, globalCtx);
            break;

        case 3:
            // Cutscene fish destruction
            osSyncPrintf("デモ魚消滅\n");
            func_80A15444(this);
            Actor_Kill(&this->actor);
            return;

        default:
            // Unknown action
            osSyncPrintf("不正なデモ動作(%s %d)(arg_data 0x%04x)\n", "../z_en_sakana.c", 0x4B0, this->actor.params);
            break;
    }

    sp40.x = action->startPos.x;
    sp40.y = action->startPos.y;
    sp40.z = action->startPos.z;

    sp34.x = action->endPos.x;
    sp34.y = action->endPos.y;
    sp34.z = action->endPos.z;

    tmpf1 = func_8006F93C(action->endFrame, action->startFrame, globalCtx->csCtx.frames);
    this->actor.posRot.pos.x = ((sp34.x - sp40.x) * tmpf1) + sp40.x;
    this->actor.posRot.pos.y = (((sp34.y - sp40.y) * tmpf1) + sp40.y) + D_80A17014;
    this->actor.posRot.pos.z = ((sp34.z - sp40.z) * tmpf1) + sp40.z;

    this->actor.groundY =
        func_8003C9A4(&globalCtx->colCtx, &this->actor.floorPoly, &sp2C, &this->actor, &this->actor.posRot.pos);
}

void func_80A16C68(EnFish* this, GlobalContext* globalCtx) {
    if (this->unk_248 > 0) {
        this->unk_248--;
    }

    this->unk_24C += 0x111;
    this->unk_24E += 0x500;
    if ((this->actor.attachedB != NULL) && (this->actor.attachedB->update == NULL) &&
        (this->actor.attachedB != &this->actor)) {
        this->actor.attachedB = NULL;
    }

    if (this->actionFunc != NULL) {
        this->actionFunc(this, globalCtx);
        if (this->actor.update == NULL) {
            return;
        }
    }

    Actor_MoveForward(&this->actor);
    if (this->unk_250 != 0) {
        func_8002E4B4(globalCtx, &this->actor, 17.5f, 4.0f, 0.0f, this->unk_250);
    }

    if (this->actor.xzDistFromLink < 70.0f) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    Actor_SetHeight(&this->actor, this->actor.shape.unk_08 * 0.01f);
    if (func_8002F410(&this->actor, globalCtx) != 0) {
        this->actor.attachedA = NULL;
        if (this->actor.params == 0) {
            Actor_Kill(&this->actor);
        } else {
            func_80A15374(this);
        }
    } else if (func_80A15688(this, globalCtx) != 0) {
        func_8002F434(&this->actor, globalCtx, 0x7E, 80.0f, 20.0f);
    }
}

#ifdef NON_MATCHING
// Second SetScale not using 0.01f in rodata
// Only 0.001f generates correct code but is wrong data
void func_80A16DEC(EnFish* this, GlobalContext* globalCtx) {

    if (this->actor.params == 1) {
        Actor_Kill(&this->actor);
        return;
    }

    if ((this->actor.attachedB != NULL) && (this->actor.attachedB->update == NULL) &&
        (this->actor.attachedB != &this->actor)) {
        this->actor.attachedB = NULL;
    }

    if (this->actionFunc != NULL) {
        this->actionFunc(this, globalCtx);
        if (this->actor.update == NULL) {
            return;
        }
    }

    Actor_MoveForward(&this->actor);
    if (this->unk_24A == 20) {
        this->actor.draw = EnFish_Draw;
    } else if (this->unk_24A == 0) {
        Actor_SetScale(&this->actor, 0.01000000001f);
    } else if (this->unk_24A < 20) {
        Actor_SetScale(&this->actor, CLAMP_MAX(this->actor.scale.x + 0.01f, 0.001f));
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fish/func_80A16DEC.s")
#endif

void EnFish_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;

    if ((D_80A17010 == NULL) && (this->actor.params == 0) && (globalCtx->csCtx.state != 0) &&
        (globalCtx->csCtx.npcActions[1] != NULL)) {
        func_80A153AC(this, globalCtx);
    }

    if ((D_80A17010 != NULL) && (D_80A17010 == this)) {
        func_80A16A64(this, globalCtx);
    } else if (this->unk_24A > 0) {
        this->unk_24A--;
        func_80A16DEC(this, globalCtx);
    } else {
        func_80A16C68(this, globalCtx);
    }
}

void EnFish_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;

    func_80093D18(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL,
                     NULL, NULL);
    func_800628A4(0, &this->collider);
}
