/*
 * File: z_en_honotrap.c
 * Overlay: ovl_En_Honotrap
 * Description: Stone Eye (Fire Trap)
 */

#include "z_en_honotrap.h"

#define FLAGS 0x00000010

#define THIS ((EnHonotrap*)thisx)

void EnHonotrap_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A5A0E4(EnHonotrap* this);
void func_80A5A378(EnHonotrap* this);
void func_80A5A1B4(EnHonotrap* this);
void func_80A5A2D8(EnHonotrap* this);
void func_80A5A31C(EnHonotrap* this);
void func_80A5A5C8(EnHonotrap* this);
void func_80A5A41C(EnHonotrap* this);
void func_80A5AA14(EnHonotrap* this);
void func_80A5A824(EnHonotrap* this);

void func_80A5A0FC(EnHonotrap* this, GlobalContext* globalCtx);
void func_80A5A388(EnHonotrap* this, GlobalContext* globalCtx);
void func_80A5A208(EnHonotrap* this, GlobalContext* globalCtx);
void func_80A5A2EC(EnHonotrap* this, GlobalContext* globalCtx);
void func_80A5A32C(EnHonotrap* this, GlobalContext* globalCtx);
void func_80A5A658(EnHonotrap* this, GlobalContext* globalCtx);
void func_80A5A484(EnHonotrap* this, GlobalContext* globalCtx);
void func_80A5AA24(EnHonotrap* this, GlobalContext* globalCtx);
void func_80A5A860(EnHonotrap* this, GlobalContext* globalCtx);

extern Gfx D_05006810[];
extern Gfx D_0404D4E0[];

const ActorInit En_Honotrap_InitVars = {
    ACTOR_EN_HONOTRAP,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_GAMEPLAY_DANGEON_KEEP,
    sizeof(EnHonotrap),
    (ActorFunc)EnHonotrap_Init,
    (ActorFunc)EnHonotrap_Destroy,
    (ActorFunc)EnHonotrap_Update,
    (ActorFunc)EnHonotrap_Draw,
};

static ColliderTrisItemInit sTrisItemsInit[2] = {
    {
        { 0x04, { 0x00000000, 0x00, 0x00 }, { 0x0001F824, 0x00, 0x00 }, 0x00, 0x01, 0x00 },
        { { { 0.0f, 23.0f, 8.5f }, { -23.0f, 0.0f, 8.5f }, { 0.0f, -23.0f, 8.5f } } },
    },
    {
        { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x0001F824, 0x00, 0x00 }, 0x00, 0x01, 0x00 },
        { { { 0.0f, 23.0f, 8.5f }, { 0.0f, -23.0f, 8.5f }, { 23.0f, 0.0f, 8.5f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    { COLTYPE_UNK10, 0x00, 0x09, 0x00, 0x00, COLSHAPE_TRIS },
    2,
    sTrisItemsInit,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x11, 0x09, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00100000, 0x00, 0x00 }, 0x19, 0x01, 0x01 },
    { 10, 25, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit D_80A5B034 = {
    0x00,
    0x0009,
    0x0017,
    0x01,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_STOP),
};

void func_80A59C30(EnHonotrap* this, GlobalContext* globalCtx) {
    s32 pad[3];

    Collider_CylinderUpdate(&this->actor, &this->colliderCylinder);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    this->unk_240 |= 1;
    this->unk_240 |= 2;
    this->unk_240 |= 4;
}

void func_80A59CC0(Vec3f* arg0, Vec3f* arg1) {
    f32 magnitude = Math3D_Vec3fMagnitude(arg1);

    if (magnitude < 0.001f) {
        osSyncPrintf("Warning : vector size zero (%s %d)\n", "../z_en_honotrap.c", 328);
        arg0->x = arg0->y = 0.0f;
        arg0->z = 1.0f;
    } else {
        arg0->x = arg1->x * (1.0f / magnitude);
        arg0->y = arg1->y * (1.0f / magnitude);
        arg0->z = arg1->z * (1.0f / magnitude);
    }
}

void func_80A59D70(EnHonotrap* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 coss;
    f32 sins;
    s32 i;
    s32 j;
    Vec3f sp70[3];
    Vec3f* vec;
    Vec3f* ptr2;

    Actor_SetScale(&this->actor, 0.1f);
    sins = Math_Sins(this->actor.initPosRot.rot.y);
    coss = Math_Coss(this->actor.initPosRot.rot.y);
    Collider_InitTris(globalCtx, &this->colliderTris);
    Collider_SetTris(globalCtx, &this->colliderTris, &this->actor, &sTrisInit, this->colliderTrisItems);

    for (i = 0; i < 2; i++) {
        vec = &sp70[0];
        for (j = 0; j < 3; j++, vec++) {
            ptr2 = &sTrisInit.list[i].dim.vtx[j];
            vec->x = (ptr2->z * sins) + (ptr2->x * coss);
            if (1) {};
            vec->y = ptr2->y;
            vec->z = (ptr2->z * coss) - (ptr2->x * sins);
            Math_Vec3f_Sum(vec, &this->actor.posRot.pos, vec);
        }

        func_800627A0(&this->colliderTris, i, &sp70[0], &sp70[1], &sp70[2]);
        if (this) {};
    }

    func_80A5A0E4(this);
    Actor_SetHeight(&this->actor, 0.0f);
}

void func_80A59F08(EnHonotrap* this, GlobalContext* globalCtx) {
    s32 pad[2];

    Actor_SetScale(&this->actor, 0.0001f);
    Collider_InitCylinder(globalCtx, &this->colliderCylinder);
    Collider_SetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    Collider_CylinderUpdate(&this->actor, &this->colliderCylinder);
    this->actor.minVelocityY = -1.0f;
    func_80061ED4(&this->actor.colChkInfo, NULL, &D_80A5B034);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 30.0f);
    this->actor.shape.unk_14 = 0x80;
    this->unk_22C = PLAYER->actor.posRot.pos;
    this->unk_22C.y += 10.0f;
    this->unk_23E = Math_Rand_ZeroOne() * 511.0f;
    func_80A5A378(this);
    Audio_PlayActorSound2(&this->actor, NA_SE_EV_FLAME_IGNITION);
    if (this->actor.params == 2) {
        this->actor.room = -1;
        this->colliderCylinder.dim.radius = 12;
        this->colliderCylinder.dim.height = 30;
        this->actor.shape.unk_08 = -1000.0f;
    }
}

void EnHonotrap_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHonotrap* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    if (this->actor.params == 0) {
        func_80A59D70(this, globalCtx);
    } else {
        func_80A59F08(this, globalCtx);
    }
}

void EnHonotrap_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHonotrap* this = THIS;

    if (this->actor.params == 0) {
        Collider_DestroyTris(globalCtx, &this->colliderTris);
    } else {
        Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
    }
}

void func_80A5A0E4(EnHonotrap* this) {
    this->actionFunc = func_80A5A0FC;
    this->unk_22A = 3;
}

void func_80A5A0FC(EnHonotrap* this, GlobalContext* globalCtx) {
    if (this->actor.attachedB != NULL) {
        this->unk_228 = 200;
        return;
    }

    if ((this->unk_228 <= 0) && (this->actor.xzDistFromLink < 750.0f) && (this->actor.yDistFromLink < 0.0f) &&
        (-700.0f < this->actor.yDistFromLink) && ((this->actor.yawTowardsLink - this->actor.shape.rot.y) > -0x4000) &&
        ((this->actor.yawTowardsLink - this->actor.shape.rot.y) < 0x4000)) {
        func_80A5A1B4(this);
    }
}

void func_80A5A1B4(EnHonotrap* this) {
    this->actionFunc = func_80A5A208;
    func_8003426C(&this->actor, 0x4000, 0xFF, 0, 0x28);
    this->unk_228 = 30;
    Audio_PlayActorSound2(&this->actor, NA_SE_EV_RED_EYE);
}

void func_80A5A208(EnHonotrap* this, GlobalContext* globalCtx) {
    this->unk_22A--;
    if (this->unk_22A <= 0) {
        func_80A5A2D8(this);
        Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_HONOTRAP,
                            (Math_Sins(this->actor.shape.rot.y) * 12.0f) + this->actor.initPosRot.pos.x,
                            this->actor.initPosRot.pos.y - 10.0f,
                            (Math_Coss(this->actor.shape.rot.y) * 12.0f) + this->actor.initPosRot.pos.z,
                            this->actor.initPosRot.rot.x, this->actor.initPosRot.rot.y, this->actor.initPosRot.rot.z,
                            1);
    }
}

void func_80A5A2D8(EnHonotrap* this) {
    this->actionFunc = func_80A5A2EC;
    this->unk_22A = 0;
}

void func_80A5A2EC(EnHonotrap* this, GlobalContext* globalCtx) {
    if (this->unk_228 <= 0) {
        func_80A5A31C(this);
    }
}

void func_80A5A31C(EnHonotrap* this) {
    this->actionFunc = func_80A5A32C;
}

void func_80A5A32C(EnHonotrap* this, GlobalContext* globalCtx) {
    this->unk_22A++;
    if (this->unk_22A >= 3) {
        func_80A5A0E4(this);
        this->unk_228 = 0xC8;
    }
}

void func_80A5A378(EnHonotrap* this) {
    this->actionFunc = func_80A5A388;
}

void func_80A5A388(EnHonotrap* this, GlobalContext* globalCtx) {
    s32 ret = Math_ApproxF(&this->actor.scale.x, (this->actor.params == 1) ? 0.004f : 0.0048f, 0.0006f);
    this->actor.scale.y = this->actor.scale.x;
    this->actor.scale.z = this->actor.scale.x;
    if (ret != 0) {
        if (this->actor.params == 1) {
            func_80A5A5C8(this);
        } else {
            func_80A5A41C(this);
        }
    }
}

void func_80A5A41C(EnHonotrap* this) {
    f32 sins;
    f32 coss;

    this->unk_228 = 0x28;
    this->actor.velocity.y = 1.0f;
    sins = Math_Sins(this->actor.posRot.rot.y);
    this->actor.velocity.x = sins + sins;
    coss = Math_Coss(this->actor.posRot.rot.y);
    this->actor.velocity.z = coss + coss;
    this->actionFunc = func_80A5A484;
}

void func_80A5A484(EnHonotrap* this, GlobalContext* globalCtx) {
    if ((this->colliderTris.base.atFlags & 2) || (this->unk_228 <= 0)) {
        if ((this->colliderTris.base.atFlags & 2) && (!(this->colliderTris.base.atFlags & 4))) {
            func_8002F71C(globalCtx, &this->actor, 5.0f, this->actor.yawTowardsLink, 0.0f);
        }

        this->actor.velocity.z = 0.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.velocity.x = 0.0f;
        func_80A5AA14(this);
        return;
    }

    if (this->actor.velocity.y > 0.0f) {
        this->actor.posRot.pos.x += this->actor.velocity.x;
        this->actor.posRot.pos.z += this->actor.velocity.z;
        func_8002E4B4(globalCtx, &this->actor, 7.0f, 12.0f, 0.0f, 5);
    }

    if (Math_ApproxF(&this->actor.posRot.pos.y, this->actor.groundY + 1.0f, this->actor.velocity.y) == 0) {
        this->actor.velocity.y += 1.0f;
    } else {
        this->actor.velocity.y = 0.0f;
    }

    func_80A59C30(this, globalCtx);
}

void func_80A5A5C8(EnHonotrap* this) {
    f32 tmpf1;

    this->actionFunc = func_80A5A658;
    tmpf1 = 1.0f / (func_8002DB6C(&this->actor, &this->unk_22C) + 1.0f);

    this->unk_228 = 0xA0;
    this->actor.velocity.x = (this->unk_22C.x - this->actor.posRot.pos.x) * tmpf1;
    this->actor.velocity.y = (this->unk_22C.y - this->actor.posRot.pos.y) * tmpf1;
    this->actor.velocity.z = (this->unk_22C.z - this->actor.posRot.pos.z) * tmpf1;
    this->unk_238 = 0.0f;
}

void func_80A5A658(EnHonotrap* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    s32 flag;
    s32 pad2;
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;

    Math_ApproxF(&this->unk_238, 13.0f, 0.5f);

    sp60 = fabsf(this->unk_238 * this->actor.velocity.x);
    sp64 = fabsf(this->unk_238 * this->actor.velocity.y);
    sp68 = fabsf(this->unk_238 * this->actor.velocity.z);

    flag = true;
    flag &= Math_ApproxF(&this->actor.posRot.pos.x, this->unk_22C.x, sp60);
    flag &= Math_ApproxF(&this->actor.posRot.pos.y, this->unk_22C.y, sp64);
    flag &= Math_ApproxF(&this->actor.posRot.pos.z, this->unk_22C.z, sp68);
    func_8002E4B4(globalCtx, &this->actor, 7.0f, 10.0f, 0.0f, 0x1D);
    if (this->colliderTris.base.atFlags & 4) {
        Player* player = PLAYER;
        sp34.x = -player->mf_A20.zx;
        sp34.y = -player->mf_A20.zy;
        sp34.z = -player->mf_A20.zz;
        func_80A59CC0(&sp4C, &sp34);
        sp40 = this->actor.velocity;
        Math3D_Vec3fReflect(&sp40, &sp4C, &this->actor.velocity);
        this->actor.speedXZ = this->unk_238 * 0.5f;
        this->actor.posRot.rot.y = atan2s(this->actor.velocity.z, this->actor.velocity.x);
        func_80A5AA14(this);
    } else if (this->colliderTris.base.atFlags & 2) {
        this->actor.speedXZ = 0.0f;
        this->actor.velocity.y = 0.0f;
        func_80A5AA14(this);
    } else if (this->unk_228 <= 0) {
        func_80A5AA14(this);
    } else {
        func_80A59C30(this, globalCtx);
        if (flag) {
            func_80A5A824(this);
        }
    }
}

void func_80A5A824(EnHonotrap* this) {
    this->actor.posRot.rot.z = 0;
    this->actionFunc = func_80A5A860;
    this->unk_228 = 0x64;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.z = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.velocity.x = 0.0f;
    this->actor.posRot.rot.y = this->actor.posRot.rot.z;
    this->actor.posRot.rot.x = this->actor.posRot.rot.z;
}

void func_80A5A860(EnHonotrap* this, GlobalContext* globalCtx) {
    Player* player;
    s32 pad;
    Vec3s sp30;

    Math_ApproxUpdateScaledS(&this->actor.posRot.rot.y, this->actor.yawTowardsLink, 0x300);
    Math_ApproxF(&this->actor.speedXZ, 3.0f, 0.1f);
    if (-this->actor.yDistFromLink < 10.0f) {
        this->actor.gravity = 0.08f;
    } else {
        this->actor.gravity = -0.08f;
    }

    func_8002D868(&this->actor);
    if (this->actor.velocity.y > 1.0f) {
        this->actor.velocity.y = 1.0f;
    }

    this->actor.velocity.y *= 0.95f;
    func_8002D7EC(&this->actor);
    func_8002E4B4(globalCtx, &this->actor, 7.0f, 10.0f, 0.0f, 0x1D);
    if (this->colliderTris.base.atFlags & 4) {
        player = PLAYER;
        func_800D20CC(&player->mf_A20, &sp30, 0);
        this->actor.posRot.rot.y = ((sp30.y * 2) - this->actor.posRot.rot.y) + 0x8000;
        func_80A5AA14(this);
    } else if (this->colliderTris.base.atFlags & 2) {
        this->actor.speedXZ *= 0.1f;
        this->actor.velocity.y *= 0.1f;
        func_80A5AA14(this);
    } else if ((this->actor.bgCheckFlags & 8) || (this->unk_228 <= 0)) {
        func_80A5AA14(this);
    } else {
        func_80A59C30(this, globalCtx);
    }
}

void func_80A5AA14(EnHonotrap* this) {
    this->actionFunc = func_80A5AA24;
}

void func_80A5AA24(EnHonotrap* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 sp28 = Math_ApproxF(&this->actor.scale.x, 0.0001f, 0.00015f);

    this->actor.scale.y = this->actor.scale.x;
    this->actor.scale.z = this->actor.scale.x;
    Actor_MoveForward(&this->actor);
    func_8002E4B4(globalCtx, &this->actor, 7.0f, 10.0f, 0.0f, 0x1D);
    if (sp28 != 0) {
        Actor_Kill(&this->actor);
    }
}

void EnHonotrap_Update(Actor* thisx, GlobalContext* globalCtx) {
    static Vec3f D_80A5B048 = { 0.0f, 0.0f, 0.0f };
    static Vec3f D_80A5B054 = { 0.0f, 0.1f, 0.0f };

    EnHonotrap* this = THIS;

    if (this->unk_228 > 0) {
        this->unk_228--;
    }

    if (this->actor.params == 0) {
        if ((this->actor.attachedB != NULL) && (this->actor.attachedB->update == 0)) {
            this->actor.attachedB = NULL;
        }
    } else {
        this->unk_240 = 0;
        this->unk_23C = this->unk_23C + 0x640;
        this->actor.shape.unk_08 = (Math_Sins(this->unk_23C) * 1000.0f) + 600.0f;
        Actor_SetHeight(&this->actor, 5.0f);
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_BURN_OUT - SFX_FLAG);
    }

    this->actionFunc(this, globalCtx);
    if (this->actor.params == 0) {
        if (this->colliderTris.base.acFlags & 2) {
            EffectSsBomb2_SpawnLayered(globalCtx, &this->actor.posRot.pos, &D_80A5B048, &D_80A5B054, 15, 8);
            Actor_Kill(&this->actor);
        } else if (this->unk_22A < 3) {
            this->colliderTris.base.acFlags &= ~2;
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
        }
    }
}

void func_80A5ABFC(EnHonotrap* this, GlobalContext* globalCtx) {
    static UNK_TYPE D_80A5B060[] = { 0x0500B0A0, 0x0500B8A0, 0x0500C0A0, 0x0500C0A0 };

    s32 pad;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_honotrap.c", 982);
    func_80093D18(globalCtx->state.gfxCtx);
    gSPSegment(gfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A5B060[this->unk_22A]));
    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_honotrap.c", 987),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, D_05006810);
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_honotrap.c", 991);
}

void func_80A5AD28(EnHonotrap* this, GlobalContext* globalCtx) {
    s32 pad;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad2;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_honotrap.c", 1000);
    func_80093D84(globalCtx->state.gfxCtx);
    this->unk_23E -= 20;
    this->unk_23E &= 0x1FF;

    gSPSegment(gfxCtx->polyXlu.p++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, this->unk_23E, 0x20, 0x80));
    gDPSetPrimColor(gfxCtx->polyXlu.p++, 0x80, 0x80, 255, 200, 0, 255);
    gDPSetEnvColor(gfxCtx->polyXlu.p++, 255, 0, 0, 0);

    Matrix_RotateY((s16)((func_8005A9F4(ACTIVE_CAM) - this->actor.shape.rot.y) + 0x8000) * 0.0000958738f,
                   MTXMODE_APPLY);

    gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_honotrap.c", 1024),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyXlu.p++, D_0404D4E0);

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_honotrap.c", 1028);
}

void EnHonotrap_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHonotrap* this = THIS;

    switch (this->actor.params) {
        case 0:
            func_80A5ABFC(this, globalCtx);
            break;

        case 1:
        case 2:
            func_80A5AD28(this, globalCtx);
            break;
    }
}
