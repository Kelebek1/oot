#include "z_en_fd_fire.h"

#define FLAGS 0x00000015

#define THIS ((EnFdFire*)thisx)

void EnFdFire_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFdFire_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFdFire_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFdFire_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A0E70C(EnFdFire* this, GlobalContext* globalCtx);
void func_80A0EA34(EnFdFire* this, GlobalContext* globalCtx);
void func_80A0E884(EnFdFire* this, GlobalContext* globalCtx);
void func_80A0E848(EnFdFire* this, GlobalContext* globalCtx);

extern Gfx D_0404D4E0[];

const ActorInit En_Fd_Fire_InitVars = {
    ACTOR_EN_FD_FIRE,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_GAMEPLAY_DANGEON_KEEP,
    sizeof(EnFdFire),
    (ActorFunc)EnFdFire_Init,
    (ActorFunc)EnFdFire_Destroy,
    (ActorFunc)EnFdFire_Update,
    (ActorFunc)EnFdFire_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x11, 0x09, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x01, 0x08 }, { 0x0D840008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
    { 12, 46, 0, { 0, 0, 0 } },
};

CollisionCheckInfoInit2 D_80A0F05C = { 0x01, 0x0000, 0x0000, 0x0000, 0xFF };

DamageTable D_80A0F068 = { 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

void func_80A0E4B0(EnFdFire* this, Vec3f* arg1) {
    f32 tmpf1;
    f32 tmpf2;
    f32 tmpf3;
    f32 tmpf4;
    f32 abs;

    tmpf1 = arg1->x - this->actor.posRot.pos.x;
    tmpf2 = arg1->y - this->actor.posRot.pos.y;
    tmpf3 = arg1->z - this->actor.posRot.pos.z;
    tmpf4 = sqrtf(SQ(tmpf1) + SQ(tmpf2) + SQ(tmpf3));
    abs = fabsf(tmpf4);
    if (fabsf(this->actor.speedXZ) < abs) {
        this->actor.velocity.x = (tmpf1 / tmpf4) * this->actor.speedXZ;
        this->actor.velocity.z = (tmpf3 / tmpf4) * this->actor.speedXZ;
    } else {
        this->actor.velocity.x = 0.0f;
        this->actor.velocity.z = 0.0f;
    }

    this->actor.velocity.y += this->actor.gravity;
    if (!(this->actor.minVelocityY <= this->actor.velocity.y)) {
        this->actor.velocity.y = this->actor.minVelocityY;
    }
}

s32 func_80A0E578(EnFdFire* this, GlobalContext* globalCtx) {
    if (this->actionFunc == func_80A0EA34) {
        return 0;
    }

    if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= ~2;
        return 1;
    }

    if (this->collider.base.maskB & 1) {
        this->collider.base.maskB &= ~1;
        return 1;
    }

    return 0;
}

void EnFdFire_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFdFire* this = THIS;
    s32 pad;
    Player* player = PLAYER;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 20.0f);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    func_80061EFC(&this->actor.colChkInfo, &D_80A0F068, &D_80A0F05C);
    this->actor.flags &= ~1;
    this->actor.gravity = -0.6f;
    this->actor.speedXZ = 5.0f;
    this->actor.velocity.y = 12.0f;
    this->unk_19C = Math_Vec3f_DistXYZ(&this->actor.posRot.pos, &player->actor.posRot.pos);
    this->unk_1A0 = 3.0f;
    this->unk_1A8 = (s16)Math_Rand_ZeroFloat(5.0f) - 0x19;
    this->actionFunc = func_80A0E70C;
}

void EnFdFire_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFdFire* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A0E70C(EnFdFire* this, GlobalContext* globalCtx) {
    Vec3f sp34 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp28 = this->actor.attachedA->posRot.pos;

    sp28.x += this->unk_19C * Math_Sins(this->actor.posRot.rot.y);
    sp28.z += this->unk_19C * Math_Coss(this->actor.posRot.rot.y);
    func_80A0E4B0(this, &sp28);
    if ((this->actor.bgCheckFlags & 1) && !(0.0f < this->actor.velocity.y)) {
        this->actor.velocity = sp34;
        this->actor.speedXZ = 0.0f;
        this->actor.bgCheckFlags &= ~1;
        if (this->actor.params & 0x8000) {
            this->unk_1A6 = 0xC8;
            this->actionFunc = func_80A0E884;
        } else {
            this->unk_1A6 = 0x12C;
            this->actionFunc = func_80A0E848;
        }
    }
}

void func_80A0E848(EnFdFire* this, GlobalContext* globalCtx) {
    s32 tmp;

    if (this->unk_1A6 == 0) {
        tmp = 0;
    } else {
        this->unk_1A6--;
        tmp = this->unk_1A6;
    }

    if (tmp == 0) {
        this->actionFunc = func_80A0EA34;
    }
}

void func_80A0E884(EnFdFire* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    f32 sp4C[] = { 0.0f, 210.0f, 60.0f, 270.0f, 120.0f, 330.0f, 180.0f, 30.0f, 240.0f, 90.0f, 300.0f, 150.0f };
    Vec3f sp40;
    s16 idx;
    s32 tmp;

    idx = ((globalCtx->state.frames / 10) + (this->actor.params & 0x7FFF)) % 12;
    sp40 = player->actor.posRot.pos;
    sp40.x += 120.0f * sinf(sp4C[idx]);
    sp40.z += 120.0f * cosf(sp4C[idx]);
    if (this->unk_1A6 == 0) {
        tmp = 0;
    } else {
        this->unk_1A6--;
        tmp = this->unk_1A6;
    }

    if (tmp == 0) {
        this->actionFunc = func_80A0EA34;
    } else {
        Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, Math_Vec3f_Yaw(&this->actor.posRot.pos, &sp40), 8, 0xFA0, 1);
        Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 0.4f, 1.0f, 0.0f);
        if (this->actor.speedXZ < 0.1f) {
            this->actor.speedXZ = 5.0f;
        }

        func_8002D868(&this->actor);
    }
}

void func_80A0EA34(EnFdFire* this, GlobalContext* globalCtx) {
    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 0.6f, 9.0f, 0.0f);
    func_8002D868(&this->actor);
    Math_SmoothScaleMaxMinF(&this->unk_1A0, 0.0f, 0.3f, 0.1f, 0.0f);
    this->actor.shape.unk_10 = 20.0f;
    this->actor.shape.unk_10 *= this->unk_1A0 / 3.0f;
    if (!(this->unk_1A0 > 0.01f)) {
        Actor_Kill(&this->actor);
    }
}

void EnFdFire_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFdFire* this = THIS;
    s32 pad;

    if ((this->actionFunc != func_80A0EA34) &&
        ((this->actor.attachedA->update == NULL) || func_80A0E578(this, globalCtx))) {
        this->actionFunc = func_80A0EA34;
    }

    func_8002D7EC(&this->actor);
    this->actionFunc(this, globalCtx);
    func_8002E4B4(globalCtx, &this->actor, 12.0f, 10.0f, 0.0f, 5);
    if (this->actionFunc != func_80A0EA34) {
        Collider_CylinderUpdate(&this->actor, &this->collider);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void EnFdFire_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Color_RGBA8_n spB8[] = { { 255, 255, 0, 255 }, { 255, 255, 255, 255 } };

    Color_RGBA8_n spB0[] = { { 255, 10, 0, 255 }, { 0, 10, 255, 255 } };
    EnFdFire* this = THIS;
    s32 pad;

    Vec3f sp9C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp90 = { 0.0f, 0.0f, 0.0f };
    s16 sp8E;
    f32 sp88;
    f32 sp84;
    f32 sp80;

    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fd_fire.c", 572);
    Matrix_Translate(thisx->posRot.pos.x, thisx->posRot.pos.y, thisx->posRot.pos.z, 0);
    if (1) {};
    sp8E = Math_Vec3f_Yaw(&sp9C, &thisx->velocity) - func_8005A9F4(ACTIVE_CAM);

    sp84 = fabsf(Math_Coss(sp8E));
    sp88 = Math_Sins(sp8E);
    sp80 = Math_Vec3f_DistXZ(&sp9C, &thisx->velocity) / 1.5f;

    Matrix_RotateY((s16)(func_8005A9F4(ACTIVE_CAM) + 0x8000) * 0.0000958738f, 1);
    Matrix_RotateZ(((sp88 * -10.0f) * sp80) * 0.017453292f, 1);

    sp9C.x = sp9C.y = sp9C.z = this->unk_1A0 * 0.001f;

    Matrix_Scale(sp9C.x, sp9C.y, sp9C.z, 1);
    sp84 = ((-0.14999999f * sp84) * sp80) + 1.0f;
    if (sp84 < 0.1f) {
        sp84 = 0.1f;
    }

    Matrix_Scale(1.0f, sp84, 1.0f / sp84, 1);

    gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_fd_fire.c", 623),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    func_80093D84(globalCtx->state.gfxCtx);

    gSPSegment(gfxCtx->polyXlu.p++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0,
                                globalCtx->state.frames * this->unk_1A8, 0x20, 0x80));

    gDPSetPrimColor(gfxCtx->polyXlu.p++, 0x80, 0x80, spB8[(thisx->params & 0x8000) >> 0xF].r,
                    spB8[(thisx->params & 0x8000) >> 0xF].g, spB8[(thisx->params & 0x8000) >> 0xF].b,
                    spB8[(thisx->params & 0x8000) >> 0xF].a);

    gDPSetEnvColor(gfxCtx->polyXlu.p++, spB0[(thisx->params & 0x8000) >> 0xF].r,
                   spB0[(thisx->params & 0x8000) >> 0xF].g, spB0[(thisx->params & 0x8000) >> 0xF].b,
                   spB0[(thisx->params & 0x8000) >> 0xF].a);

    gDPPipeSync(gfxCtx->polyXlu.p++);
    gSPDisplayList(gfxCtx->polyXlu.p++, D_0404D4E0);

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fd_fire.c", 672);
}
