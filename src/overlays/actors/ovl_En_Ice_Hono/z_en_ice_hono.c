/*
 * File: z_en_ice_hono.c
 * Overlay: ovl_En_Ice_Hono
 * Description: Blue Fire Flames
 */

#include "z_en_ice_hono.h"

#define FLAGS 0x00000000

#define THIS ((EnIceHono*)thisx)

void EnIceHono_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIceHono_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIceHono_Update(Actor* thisx, GlobalContext* globalCtx);
void EnIceHono_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A734D4(EnIceHono* this);
void func_80A739FC(EnIceHono* this);
void func_80A735A0(EnIceHono* this);
void func_80A73780(EnIceHono* this);

void func_80A734F8(EnIceHono* this, GlobalContext* globalCtx);
void func_80A73AD0(EnIceHono* this, GlobalContext* globalCtx);
void func_80A735C0(EnIceHono* this, GlobalContext* globalCtx);
void func_80A737A0(EnIceHono* this, GlobalContext* globalCtx);

extern Gfx D_0404D4E0[];

const ActorInit En_Ice_Hono_InitVars = {
    ACTOR_EN_ICE_HONO,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnIceHono),
    (ActorFunc)EnIceHono_Init,
    (ActorFunc)EnIceHono_Destroy,
    (ActorFunc)EnIceHono_Update,
    (ActorFunc)EnIceHono_Draw,
};

static ColliderCylinderInit sCylinderInit1 = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 25, 80, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    { COLTYPE_UNK10, 0x21, 0x00, 0x21, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
    { 12, 60, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain1[] = {
    ICHAIN_U8(unk_1F, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 60, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_STOP),
};

static InitChainEntry sInitChain2[] = {
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_STOP),
};

static InitChainEntry sInitChain3[] = {
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_STOP),
};

f32 func_80A72FF0(Vec3f* arg0, Vec3f* arg1) {
    return SQ(arg0->x - arg1->x) + SQ(arg0->z - arg1->z);
}

void func_80A7301C(EnIceHono* this, GlobalContext* globalCtx) {
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sInitChain1);
    Actor_SetScale(&this->actor, 0.0074f);
    this->actor.flags |= 1;
    Actor_SetHeight(&this->actor, 10.0f);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit1);
    Collider_CylinderUpdate(&this->actor, &this->collider);
    this->actor.colChkInfo.mass = 0xFF;
    func_80A734D4(this);
}

void func_80A730BC(EnIceHono* this, GlobalContext* globalCtx) {
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sInitChain2);
    this->actor.scale.x = this->actor.scale.z = this->actor.scale.y = 0.00002f;
    this->actor.gravity = -0.3f;
    this->actor.minVelocityY = -4.0f;
    this->actor.shape.unk_08 = 0.0f;
    this->actor.shape.rot.x = this->actor.shape.rot.y = this->actor.shape.rot.z = this->actor.posRot.rot.x =
        this->actor.posRot.rot.y = this->actor.posRot.rot.z = 0;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit2);
    Collider_CylinderUpdate(&this->actor, &this->collider);

    this->collider.dim.radius = this->actor.scale.x * 4000.4f;
    this->collider.dim.height = this->actor.scale.y * 8000.2f;
    this->actor.colChkInfo.mass = 0xFD;
    func_80A735A0(this);
}

void func_80A731C0(EnIceHono* this, GlobalContext* globalCtx) {
    Actor_ProcessInitChain(&this->actor, sInitChain3);
    this->actor.scale.x = this->actor.scale.z = this->actor.scale.y = 0.0008f;
    this->actor.gravity = -0.3f;
    this->actor.minVelocityY = -4.0f;
    this->actor.shape.unk_08 = 0.0f;
    func_80A739FC(this);
}

void EnIceHono_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnIceHono* this = THIS;
    s32 params = this->actor.params;

    switch (params) {
        case -1:
            func_80A7301C(this, globalCtx);
            break;

        case 0:
            func_80A730BC(this, globalCtx);
            break;

        case 1:
        case 2:
            func_80A731C0(this, globalCtx);
            break;
    }

    params = this->actor.params;
    if ((params == -1) || (params == 0)) {
        Lights_InitType0PositionalLight(&this->unk_1AC, this->actor.posRot.pos.x, (s16)this->actor.posRot.pos.y + 0xA,
                                        this->actor.posRot.pos.z, 0x9B, 0xD2, 0xFF, 0);
        this->unk_1A8 = Lights_Insert(globalCtx, &globalCtx->lightCtx, &this->unk_1AC);
        this->unk_154 = Math_Rand_ZeroOne() * 65535.5f;
        this->unk_156 = Math_Rand_ZeroOne() * 65535.5f;
        // (ice fire)(arg_data %x)
        osSyncPrintf("(ice 炎)(arg_data 0x%04x)\n", this->actor.params);
    }
}

void EnIceHono_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnIceHono* this = THIS;

    if ((this->actor.params == -1) || (this->actor.params == 0)) {
        Lights_Remove(globalCtx, &globalCtx->lightCtx, this->unk_1A8);
        Collider_DestroyCylinder(globalCtx, &this->collider);
    }
}

s32 func_80A733E8(EnIceHono* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f sp18;

    if (this->actor.xzDistFromLink < 60.0f) {
        sp18.x = (Math_Sins(this->actor.yawTowardsLink + 0x8000) * 40.0f) + player->actor.posRot.pos.x;
        sp18.y = player->actor.posRot.pos.y;
        sp18.z = (Math_Coss(this->actor.yawTowardsLink + 0x8000) * 40.0f) + player->actor.posRot.pos.z;
        if (func_80A72FF0(&sp18, &this->actor.posRot.pos) <= 1600.0f) {
            return 1;
        }
    }

    return 0;
}

void func_80A734D4(EnIceHono* this) {
    this->actionFunc = func_80A734F8;
    this->unk_150 = 0xFF;
    this->actor.shape.unk_08 = -1000.0f;
}

void func_80A734F8(EnIceHono* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
    } else if (func_80A733E8(this, globalCtx)) {
        func_8002F434(&this->actor, globalCtx, 0x7E, 60.0f, 100.0f);
    }

    if (this->actor.xzDistFromLink < 200.0f) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    func_8002F8F0(&this->actor, NA_SE_EV_FIRE_PILLAR_S - SFX_FLAG);
}

void func_80A735A0(EnIceHono* this) {
    this->actionFunc = func_80A735C0;
    this->unk_152 = 0xC8;
    this->unk_150 = 0xFF;
}

void func_80A735C0(EnIceHono* this, GlobalContext* globalCtx) {
    s32 i;
    s32 flag = this->actor.bgCheckFlags & 1;

    Math_ApproxF(&this->actor.scale.x, 0.0017f, 0.00008f);
    this->actor.scale.z = this->actor.scale.x;
    Math_ApproxF(&this->actor.scale.y, 0.0017f, 0.00008f);

    if (flag) {
        for (i = 0; i < 0x10000; i += 0x2000) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ICE_HONO, this->actor.posRot.pos.x,
                        this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0,
                        ((s32)(Math_Rand_ZeroOne() * 1000.0f) + i) - 0x1F4, 0, 1);
        }

        func_80A73780(this);
    }

    Actor_MoveForward(&this->actor);
    func_8002E4B4(globalCtx, &this->actor, 10.0f, this->actor.scale.x * 3500.0f, 0.0f, 5);
    Collider_CylinderUpdate(&this->actor, &this->collider);
    this->collider.dim.radius = this->actor.scale.x * 4000.0f;
    this->collider.dim.height = this->actor.scale.y * 8000.0f;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    if (this->unk_152 <= 0) {
        Actor_Kill(&this->actor);
    }
}

void func_80A73780(EnIceHono* this) {
    this->actionFunc = func_80A737A0;
    this->unk_152 = 0x3C;
    this->unk_150 = 0xFF;
}

void func_80A737A0(EnIceHono* this, GlobalContext* globalCtx) {
    s32 i;

    if (this->unk_152 >= 0x15) {
        Math_ApproxF(&this->actor.scale.x, 0.011f, 0.00014f);
        Math_ApproxF(&this->actor.scale.y, 0.006f, 0.00012f);
    } else {
        Math_ApproxF(&this->actor.scale.x, 0.0001f, 0.00015f);
        Math_ApproxF(&this->actor.scale.y, 0.0001f, 0.00015f);
    }
    this->actor.scale.z = this->actor.scale.x;

    Actor_MoveForward(&this->actor);
    func_8002E4B4(globalCtx, &this->actor, 10.0f, this->actor.scale.x * 3500.0f, 0.0f, 4);
    if (this->unk_152 < 0x19) {
        this->unk_150 -= 10;
        this->unk_150 = CLAMP(this->unk_150, 0, 255);
    }

    if ((this->unk_150 >= 0x65) && (this->unk_152 < 0x28)) {
        Collider_CylinderUpdate(&this->actor, &this->collider);
        this->collider.dim.radius = this->actor.scale.x * 6000.0f;
        this->collider.dim.height = this->actor.scale.y * 8000.0f;
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    if (this->unk_152 == 0x2E) {
        for (i = 0; i < 0xFFFA; i += 0x1999) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ICE_HONO, this->actor.posRot.pos.x,
                        this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0,
                        ((s32)(Math_Rand_ZeroOne() * 1000.0f) + i) - 0x1F4, 0, 2);
        }
    }

    if (this->unk_152 <= 0) {
        Actor_Kill(&this->actor);
    }
}

void func_80A739FC(EnIceHono* this) {
    f32 rand;

    this->actionFunc = func_80A73AD0;
    this->unk_152 = 0x2C;
    this->unk_150 = 0xFF;
    if (this->actor.params == 1) {
        this->unk_158 = (Math_Rand_ZeroOne() * 0.005f) + 0.004f;
        this->actor.speedXZ = (Math_Rand_ZeroOne() * 1.6f) + 0.5f;
    } else {
        this->unk_158 = (Math_Rand_ZeroOne() * 0.005f) + 0.003f;
        rand = Math_Rand_ZeroOne();
        this->actor.speedXZ = (rand + rand) + 0.5f;
    }
}

void func_80A73AD0(EnIceHono* this, GlobalContext* globalCtx) {
    if (this->unk_152 >= 0x15) {
        Math_ApproxF(&this->actor.scale.x, 0.006f, 0.00016f);
        Math_ApproxF(&this->actor.scale.y, this->unk_158 * 0.667f, 0.00014f);
    } else {
        Math_ApproxF(&this->actor.scale.x, 0.0001f, 0.00015f);
        Math_ApproxF(&this->actor.scale.y, 0.0001f, 0.00015f);
    }
    this->actor.scale.z = this->actor.scale.x;

    Math_ApproxF(&this->actor.speedXZ, 0.0f, 0.06f);
    Actor_MoveForward(&this->actor);
    func_8002E4B4(globalCtx, &this->actor, 10.0f, 10.0f, 0.0f, 5);
    if (this->unk_152 < 0x19) {
        this->unk_150 -= 10;
        this->unk_150 = CLAMP(this->unk_150, 0, 0xFF);
    }

    if (this->unk_152 <= 0) {
        Actor_Kill(&this->actor);
    }
}

void EnIceHono_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnIceHono* this = THIS;
    s32 pad;
    f32 ratio;
    s32 pad2;
    f32 sins2;
    f32 sins1;

    if (this->unk_152 > 0) {
        this->unk_152--;
    }

    if (this->actor.params == 0) {
        func_8002F8F0(&this->actor, NA_SE_IT_FLAME - SFX_FLAG);
    }

    if ((this->actor.params == -1) || (this->actor.params == 0)) {
        this->unk_154 += 0x1111;
        this->unk_156 += 0x4000;

        sins1 = Math_Sins(this->unk_156);
        sins2 = Math_Sins(this->unk_154);

        ratio = ((Math_Rand_ZeroOne() * 0.05f) + ((sins2 * 0.125f) + (sins1 * 0.1f))) + 0.425f;
        if ((ratio > 0.7f) || (ratio < 0.2f)) {
            // Impossible ratio!
            osSyncPrintf("ありえない値(ratio = %f)\n", ratio);
        }
        Lights_InitType0PositionalLight(&this->unk_1AC, this->actor.posRot.pos.x, (s16)this->actor.posRot.pos.y + 10,
                                        this->actor.posRot.pos.z, (s32)(155.0f * ratio), (s32)(210.0f * ratio),
                                        (s32)(255.0f * ratio), 0x578);
    }

    if (this->actionFunc != NULL) {
        this->actionFunc(this, globalCtx);
    }
}

void EnIceHono_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnIceHono* this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_ice_hono.c", 695);
    func_80093D84(globalCtx->state.gfxCtx);

    gSPSegment(oGfxCtx->polyXlu.p++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0,
                                (globalCtx->state.frames * -20) % 512, 0x20, 0x80));
    gDPSetPrimColor(oGfxCtx->polyXlu.p++, 0x80, 0x80, 170, 255, 255, this->unk_150);
    gDPSetEnvColor(oGfxCtx->polyXlu.p++, 0, 150, 255, 0);

    Matrix_RotateY((s16)((func_8005A9F4(ACTIVE_CAM) - this->actor.shape.rot.y) + 0x8000) * 0.0000958738f,
                   MTXMODE_APPLY);

    gSPMatrix(oGfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_ice_hono.c", 718),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(oGfxCtx->polyXlu.p++, D_0404D4E0);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_ice_hono.c", 722);
}
