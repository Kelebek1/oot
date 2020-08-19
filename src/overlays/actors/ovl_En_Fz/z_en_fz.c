/*
 * File: z_en_fz.c
 * Overlay: ovl_En_Freezer
 * Description: Frezzard
 */

#include "z_en_fz.h"

#define FLAGS 0x00000415

#define THIS ((EnFz*)thisx)

void EnFz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFz_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A21500(EnFz* this, Vec3f* a, Vec3f* b, Vec3f* c, f32 arg4, f32 arg5, s16 arg6, u8 arg7);
void func_80A2145C(EnFz* this, Vec3f* a, Vec3f* b, Vec3f* c, f32 arg4);
void func_80A207F4(EnFz* this);
void func_80A20E84(EnFz* this);
void func_80A20880(EnFz* this);
void func_80A20938(EnFz* this);
void func_80A209B4(EnFz* this);
void func_80A20A20(EnFz* this);
void func_80A20748(EnFz* this);
void func_80A20D7C(EnFz* this);

void func_80A1FF8C(EnFz* this, GlobalContext* globalCtx);
void func_80A20830(EnFz* this, GlobalContext* globalCtx);
void func_80A20EC4(EnFz* this, GlobalContext* globalCtx);
void func_80A208A8(EnFz* this, GlobalContext* globalCtx);
void func_80A20978(EnFz* this, GlobalContext* globalCtx);
void func_80A209E4(EnFz* this, GlobalContext* globalCtx);
void func_80A20A4C(EnFz* this, GlobalContext* globalCtx);
void func_80A20A88(EnFz* this, GlobalContext* globalCtx);
void func_80A20AC0(EnFz* this, GlobalContext* globalCtx);
void func_80A20774(EnFz* this, GlobalContext* globalCtx);
void func_80A218A8(EnFz* this, GlobalContext* globalCtx);
void func_80A215BC(EnFz* this, GlobalContext* globalCtx);
void func_80A20CAC(EnFz* this, GlobalContext* globalCtx);
void func_80A20DBC(EnFz* this, GlobalContext* globalCtx);
void func_80A20D4C(EnFz* this, GlobalContext* globalCtx);

extern Gfx D_060030A0[];
extern Gfx D_06003158[];

const ActorInit En_Fz_InitVars = {
    ACTOR_EN_FZ,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_FZ,
    sizeof(EnFz),
    (ActorFunc)EnFz_Init,
    (ActorFunc)EnFz_Destroy,
    (ActorFunc)EnFz_Update,
    (ActorFunc)EnFz_Draw,
};

static ColliderCylinderInit_Set3 sCylinderInit1 = {
    { COLTYPE_UNK10, 0x11, 0x09, 0x39, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x00 }, { 0xFFCE0FDB, 0x00, 0x00 }, 0x01, 0x05, 0x01 },
    { 30, 80, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit_Set3 sCylinderInit2 = {
    { COLTYPE_METAL_SHIELD, 0x00, 0x0D, 0x00, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x00 }, { 0x0001F024, 0x00, 0x00 }, 0x00, 0x01, 0x00 },
    { 35, 80, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit_Set3 sCylinderInit3 = {
    { COLTYPE_UNK10, 0x11, 0x00, 0x00, COLSHAPE_CYLINDER },
    { 0x00, { 0x20000000, 0x02, 0x08 }, { 0x00000000, 0x00, 0x00 }, 0x01, 0x00, 0x00 },
    { 20, 30, -15, { 0, 0, 0 } },
};

DamageTable D_80A21C14 = { 0x00, 0xF0, 0xF0, 0xF2, 0xF0, 0xF0, 0xF2, 0xF2, 0xF0, 0xF2, 0xF4,
                           0x24, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x24, 0x00, 0x00, 0x00, 0x00,
                           0xF0, 0xF4, 0xF2, 0xF0, 0xF8, 0xF4, 0x00, 0x00, 0x00, 0x00 };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(naviEnemyId, 59, ICHAIN_CONTINUE),
    ICHAIN_U8(unk_1F, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 30, ICHAIN_STOP),
};

void EnFz_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFz* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.colChkInfo.damageTable = &D_80A21C14;
    this->actor.colChkInfo.health = 6;
    Collider_InitCylinder(globalCtx, &this->collider1);
    Collider_SetCylinder_Set3(globalCtx, &this->collider1, &this->actor, &sCylinderInit1);
    Collider_InitCylinder(globalCtx, &this->collider2);
    Collider_SetCylinder_Set3(globalCtx, &this->collider2, &this->actor, &sCylinderInit2);
    Collider_InitCylinder(globalCtx, &this->collider3);
    Collider_SetCylinder_Set3(globalCtx, &this->collider3, &this->actor, &sCylinderInit3);
    Actor_SetScale(&this->actor, 0.008f);
    this->actor.colChkInfo.mass = 0xFF;
    this->actor.flags &= ~1;
    this->unk_242 = 0;
    this->unk_249 = 0;
    this->unk_246 = 1;
    this->unk_247 = 0;
    this->unk_248 = 0;
    this->unk_261 = 1;
    this->unk_262 = 0;

    this->actor.speedXZ = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;

    this->unk_234.y = this->actor.posRot.pos.y;
    this->unk_234.x = this->actor.posRot.pos.x;
    this->unk_234.z = this->actor.posRot.pos.z;

    this->unk_24C = this->actor.posRot.pos.y;
    this->unk_250 = 135.0f;
    if (this->actor.params < 0) {
        this->unk_258 = 0;
        this->actor.scale.y = 0.0f;
        func_80A207F4(this);
    } else {
        this->unk_258 = 0xFF;
        func_80A20E84(this);
    }

    func_80A1FF8C(this, globalCtx);
}

void EnFz_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFz* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
    Collider_DestroyCylinder(globalCtx, &this->collider3);
}

void func_80A1FF8C(EnFz* this, GlobalContext* globalCtx) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    u32 sp40;
    CollisionPoly* sp3C;

    sp5C.x = this->actor.posRot.pos.x;
    sp5C.y = this->actor.posRot.pos.y + 20.0f;
    sp5C.z = this->actor.posRot.pos.z;
    Matrix_Translate(sp5C.x, sp5C.y, sp5C.z, MTXMODE_NEW);
    Matrix_RotateRPY(this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z, MTXMODE_APPLY);
    sp44.x = sp44.y = 0.0f;
    sp44.z = 220.0f;
    Matrix_MultVec3f(&sp44, &this->unk_264);
    if (func_8003DE84(&globalCtx->colCtx, &sp5C, &this->unk_264, &sp50, &sp3C, 1, 0, 0, 1, &sp40) != 0) {
        Math_Vec3f_Copy(&this->unk_264, &sp50);
    }

    sp5C.x = this->actor.posRot.pos.x - this->unk_264.x;
    sp5C.z = this->actor.posRot.pos.z - this->unk_264.z;
    this->unk_270 = SQ(sp5C.x) + SQ(sp5C.z);
}

s32 func_80A200B0(EnFz* this, Vec3f* arg1) {
    if (this->unk_270 <= (SQ(this->actor.posRot.pos.x - arg1->x) + SQ(this->actor.posRot.pos.z - arg1->z))) {
        return 1;
    }

    return 0;
}

void func_80A20100(EnFz* this, GlobalContext* globalCtx, Vec3f* arg2, s32 arg3, f32 arg4) {
    s32 tmp;
    Vec3f spA8;
    Vec3f sp9C;
    Vec3f sp90;
    Color_RGBA8 sp8C;
    Color_RGBA8 sp88;
    f32 tmpf1;
    s32 i;

    sp8C.r = 155;
    sp8C.g = 255;
    sp8C.b = 255;
    sp8C.a = 255;
    sp88.r = 200;
    sp88.g = 200;
    sp88.b = 200;

    sp90.x = sp90.z = 0.0f;
    sp90.y = -1.0f;
    for (i = 0; i < arg3; i++) {
        tmpf1 = Math_Rand_CenteredFloat(0.3f) + 0.6f;
        tmp = (s32)Math_Rand_CenteredFloat(5.0f) + 0xC;

        spA8.x = Math_Rand_CenteredFloat(arg4) + arg2->x;
        spA8.y = Math_Rand_ZeroFloat(arg4) + arg2->y;
        spA8.z = Math_Rand_CenteredFloat(arg4) + arg2->z;

        sp9C.x = Math_Rand_CenteredFloat(10.0f);
        sp9C.y = Math_Rand_ZeroFloat(10.0f) + 2.0f;
        sp9C.z = Math_Rand_CenteredFloat(10.0f);

        func_8002A2A4(globalCtx, &spA8, tmpf1, &sp9C, &sp90, &sp8C, &sp88, tmp);
    }

    func_80062CD4(globalCtx, arg2);
}

void func_80A202F4(EnFz* this) {
}

void func_80A202FC(EnFz* this) {
    Vec3f sp44;
    Vec3f sp38;
    Vec3f sp2C;

    if ((this->unk_240 & 0xF) == 0) {
        sp44.x = Math_Rand_CenteredFloat(40.0f) + this->actor.posRot.pos.x;
        sp44.y = (Math_Rand_CenteredFloat(40.0f) + this->actor.posRot.pos.y) + 30.0f;
        sp44.z = Math_Rand_CenteredFloat(40.0f) + this->actor.posRot.pos.z;
        sp2C.x = sp2C.z = 0.0f;
        sp2C.y = 0.1f;
        sp38.x = sp38.y = sp38.z = 0.0f;
        func_80A2145C(this, &sp44, &sp38, &sp2C, Math_Rand_ZeroFloat(7.5f) + 15.0f);
    }
}

void func_80A203DC(EnFz* this) {
    Vec3f sp44;
    Vec3f sp38;
    Vec3f sp2C;

    if (!(this->unk_240 & 3)) {
        sp44.x = Math_Rand_CenteredFloat(40.0f) + this->actor.posRot.pos.x;
        sp44.y = this->unk_24C;
        sp44.z = Math_Rand_CenteredFloat(40.0f) + this->actor.posRot.pos.z;
        sp2C.x = sp2C.z = 0.0f;
        sp2C.y = 0.1f;
        sp38.x = sp38.y = sp38.z = 0.0f;
        func_80A2145C(this, &sp44, &sp38, &sp2C, Math_Rand_ZeroFloat(7.5f) + 15.0f);
    }
}

void func_80A204A0(EnFz* this, GlobalContext* globalCtx) {
    Vec3f sp34;

    if ((this->unk_247 != 0) &&
        ((this->actor.bgCheckFlags & 8) || !func_800339B8(&this->actor, globalCtx, 60.0f, this->actor.posRot.rot.y))) {
        this->actor.bgCheckFlags &= ~8;
        this->unk_247 = 0;
        this->unk_254 = 0.0f;
        this->actor.speedXZ = 0.0f;
    }

    if (this->unk_248 != 0) {
        if (this->actor.params < 0) {
            if ((this->collider1.base.atFlags & 2) != 0) {
                this->unk_247 = 0;
                this->unk_254 = 0.0f;
                this->collider1.base.acFlags &= ~2;
                this->actor.speedXZ = 0.0f;
                this->unk_244 = 0xA;
                func_80A20748(this);
                return;
            }
        }

        if (this->collider2.base.acFlags & 0x80) {
            this->collider2.base.acFlags &= ~0x80;
            this->collider1.base.acFlags &= ~2;
            return;
        }

        if ((this->collider1.base.acFlags & 2) != 0) {
            this->collider1.base.acFlags &= ~2;
            if (this->actor.colChkInfo.damageEffect != 2) {
                if (this->actor.colChkInfo.damageEffect == 0xF) {
                    Actor_ApplyDamage(&this->actor);
                    func_8003426C(&this->actor, 0x4000, 0xFF, 0x2000, 8);
                    if (this->actor.colChkInfo.health != 0) {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FREEZAD_DAMAGE);
                        sp34.x = this->actor.posRot.pos.x;
                        sp34.y = this->actor.posRot.pos.y;
                        sp34.z = this->actor.posRot.pos.z;
                        func_80A20100(this, globalCtx, &sp34, 0xA, 0.0f);
                        this->unk_249++;

                    } else {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FREEZAD_DEAD);
                        Audio_PlayActorSound2(&this->actor, NA_SE_EV_ICE_BROKEN);
                        sp34.x = this->actor.posRot.pos.x;
                        sp34.y = this->actor.posRot.pos.y;
                        sp34.z = this->actor.posRot.pos.z;
                        func_80A20100(this, globalCtx, &sp34, 0x1E, 10.0f);
                        func_80A20CAC(this, globalCtx);
                    }
                }
            } else {
                Actor_ApplyDamage(&this->actor);
                func_8003426C(&this->actor, 0x4000, 0xFF, 0x2000, 8);
                if (this->actor.colChkInfo.health == 0) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FREEZAD_DEAD);
                    func_80A20D7C(this);
                } else {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FREEZAD_DAMAGE);
                }
            }
        }
    }
}

void func_80A20704(EnFz* this) {
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 0xA, 0x7D0, 0);
    this->actor.posRot.rot.y = this->actor.shape.rot.y;
}

void func_80A20748(EnFz* this) {
    this->unk_260 = 2;
    this->unk_248 = 0;
    this->actor.flags &= ~1;
    this->actionFunc = func_80A20774;
}

void func_80A20774(EnFz* this, GlobalContext* globalCtx) {
    this->unk_258 -= 16;
    if (this->unk_258 >= 0x100) {
        this->unk_258 = 0;
    }

    if (Math_SmoothScaleMaxMinF(&this->actor.scale.y, 0, 1.0f, 0.0005f, 0.0f) == 0.0f) {
        func_80A207F4(this);
    }
}

void func_80A207F4(EnFz* this) {
    this->unk_260 = 0;
    this->unk_25E = 0;
    this->unk_25C = 0;
    this->unk_244 = 0x64;
    this->actionFunc = func_80A20830;
    this->actor.posRot.pos.x = this->unk_234.x;
    this->actor.posRot.pos.y = this->unk_234.y;
    this->actor.posRot.pos.z = this->unk_234.z;
}

void func_80A20830(EnFz* this, GlobalContext* globalCtx) {
    if ((this->unk_244 == 0) && (this->actor.xzDistFromLink < 400.0f)) {
        func_80A20880(this);
    }
}

void func_80A20880(EnFz* this) {
    this->unk_260 = 2;
    this->unk_244 = 0x14;
    this->unk_25E = 0xFA0;
    this->actionFunc = func_80A208A8;
}

void func_80A208A8(EnFz* this, GlobalContext* globalCtx) {
    if (this->unk_244 == 0) {
        this->unk_258 += 8;
        if (this->unk_258 > 0xFF) {
            this->unk_258 = 0xFF;
        }

        if (Math_SmoothScaleMaxMinF(&this->actor.scale.y, 0.008f, 1.0f, 0.0005f, 0.0f) == 0.0f) {
            func_80A20938(this);
        }
    }
}

void func_80A20938(EnFz* this) {
    this->unk_260 = 1;
    this->unk_244 = 0x28;
    this->unk_246 = 1;
    this->unk_248 = 1;
    this->actor.flags |= 1;
    this->actionFunc = func_80A20978;
    this->actor.gravity = -1.0f;
}

void func_80A20978(EnFz* this, GlobalContext* globalCtx) {
    func_80A20704(this);
    if (this->unk_244 == 0) {
        func_80A209B4(this);
    }
}

void func_80A209B4(EnFz* this) {
    this->unk_260 = 1;
    this->unk_247 = 1;
    this->unk_244 = 0x64;
    this->actionFunc = func_80A209E4;
    this->unk_254 = 4.0f;
}

void func_80A209E4(EnFz* this, GlobalContext* globalCtx) {
    if ((this->unk_244 == 0) || (this->unk_247 == 0)) {
        func_80A20A20(this);
    }
}

void func_80A20A20(EnFz* this) {
    this->unk_260 = 1;
    this->unk_244 = 0x28;
    this->actionFunc = func_80A20A4C;
    this->unk_254 = 0.0f;
    this->actor.speedXZ = 0.0f;
}

void func_80A20A4C(EnFz* this, GlobalContext* globalCtx) {
    func_80A20704(this);
    if (this->unk_244 == 0) {
        func_80A20A88(this, globalCtx);
    }
}

void func_80A20A88(EnFz* this, GlobalContext* globalCtx) {
    this->unk_260 = 1;
    this->unk_244 = 0x50;
    this->actionFunc = func_80A20AC0;
    func_80A1FF8C(this, globalCtx);
}

void func_80A20AC0(EnFz* this, GlobalContext* globalCtx) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    u8 sp37;
    s16 sp34;

    if (this->unk_244 == 0) {
        func_80A20748(this);
        return;
    }

    if (this->unk_244 >= 0xB) {
        sp37 = 0;
        sp34 = 0x96;
        func_8002F974(&this->actor, NA_SE_EN_FREEZAD_BREATH - SFX_FLAG);
        if ((this->unk_244 - 0xA) < 0x10) {
            sp34 = (this->unk_244 * 0xA) - 0x64;
        }

        sp38.x = sp38.z = 0.0f;
        sp38.y = 0.6f;
        sp50.x = this->actor.posRot.pos.x;
        sp50.y = this->actor.posRot.pos.y + 20.0f;
        sp50.z = this->actor.posRot.pos.z;
        Matrix_RotateY((this->actor.shape.rot.y / 32768.0f) * M_PI, MTXMODE_NEW);
        sp5C.x = 0.0f;
        sp5C.y = -2.0f;
        sp5C.z = 20.0f;
        Matrix_MultVec3f(&sp5C, &sp44);
        if ((this->unk_244 & 7) == 0) {
            sp37 = 1;
        }

        func_80A21500(this, &sp50, &sp44, &sp38, 2.0f, 25.0f, sp34, sp37);
        sp50.x += sp44.x * 0.5f;
        sp50.y += sp44.y * 0.5f;
        sp50.z += sp44.z * 0.5f;
        func_80A21500(this, &sp50, &sp44, &sp38, 2.0f, 25.0f, sp34, 0);
    }
}

void func_80A20CAC(EnFz* this, GlobalContext* globalCtx) {
    this->unk_260 = 0;
    this->unk_246 = 1;
    this->unk_248 = 0;
    this->unk_262 = 1;
    this->actor.flags &= ~1;
    this->unk_261 = 0;
    this->unk_244 = 0x3C;
    this->unk_254 = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.speedXZ = 0.0f;
    Actor_ChangeType(globalCtx, &globalCtx->actorCtx, &this->actor, 6);
    Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.posRot.pos, 0x60);
    this->actionFunc = func_80A20D4C;
}

void func_80A20D4C(EnFz* this, GlobalContext* globalCtx) {
    if (this->unk_244 == 0) {
        Actor_Kill(&this->actor);
    }
}

void func_80A20D7C(EnFz* this) {
    this->unk_260 = 3;
    this->unk_248 = 0;
    this->unk_262 = 1;
    this->actor.flags &= ~1;
    this->actionFunc = func_80A20DBC;
    this->actor.speedXZ = 0.0f;
    this->unk_254 = 0.0f;
}

void func_80A20DBC(EnFz* this, GlobalContext* globalCtx) {
    Math_ApproxF(&this->actor.scale.y, 0.0006f, 0.0002f);
    if (this->actor.scale.y < 0.006f) {
        this->actor.scale.x += 0.0004f;
        this->actor.scale.z += 0.0004f;
    }

    if (this->actor.scale.y < 0.004f) {
        this->unk_258 -= 8;
        if (this->unk_258 > 255) {
            this->unk_258 = 0;
        }
    }

    if (this->unk_258 == 0) {
        func_80A20CAC(this, globalCtx);
    }
}

void func_80A20E84(EnFz* this) {
    this->unk_260 = 1;
    this->unk_244 = 0x28;
    this->unk_246 = 1;
    this->unk_248 = 1;
    this->actor.flags |= 1;
    this->actionFunc = func_80A20EC4;
    this->actor.gravity = -1.0f;
}

void func_80A20EC4(EnFz* this, GlobalContext* globalCtx) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    u8 sp37;
    s16 sp34;

    if (this->unk_240 & 0xC0) {
        func_80A20704(this);
        func_80A1FF8C(this, globalCtx);
        return;
    }

    sp37 = 0;
    sp34 = 0x96;
    func_8002F974(&this->actor, NA_SE_EN_FREEZAD_BREATH - SFX_FLAG);
    if ((this->unk_240 & 0x3F) >= 0x30) {
        sp34 = 0x276 - ((this->unk_240 & 0x3F) * 0xA);
    }

    sp38.x = sp38.z = 0.0f;
    sp38.y = 0.6f;

    sp50.x = this->actor.posRot.pos.x;
    sp50.y = this->actor.posRot.pos.y + 20.0f;
    sp50.z = this->actor.posRot.pos.z;
    Matrix_RotateY((this->actor.shape.rot.y / 32768.0f) * M_PI, 0);
    sp5C.x = 0.0f;
    sp5C.y = -2.0f;
    sp5C.z = 20.0f;
    Matrix_MultVec3f(&sp5C, &sp44);
    if (!(this->unk_240 & 7)) {
        sp37 = 1;
    }

    func_80A21500(this, &sp50, &sp44, &sp38, 2.0f, 25.0f, sp34, sp37);
    sp50.x += sp44.x * 0.5f;
    sp50.y += sp44.y * 0.5f;
    sp50.z += sp44.z * 0.5f;
    func_80A21500(this, &sp50, &sp44, &sp38, 2.0f, 25.0f, sp34, 0);
}

void EnFz_Update(Actor* thisx, GlobalContext* globalCtx) {
    static void (*D_80A21C40[])(EnFz * this) = { func_80A202F4, func_80A202FC, func_80A203DC, func_80A203DC };
    EnFz* this = THIS;
    s32 pad;

    this->unk_240++;
    if (this->unk_242 != 0) {
        this->unk_242--;
    }

    if (this->unk_244 != 0) {
        this->unk_244--;
    }

    if (this->unk_263 != 0) {
        this->unk_263--;
    }

    Actor_SetHeight(&this->actor, 50.0f);
    func_80A204A0(this, globalCtx);
    this->actionFunc(this, globalCtx);
    if (this->unk_262 == 0) {
        Collider_CylinderUpdate(&this->actor, &this->collider1);
        Collider_CylinderUpdate(&this->actor, &this->collider2);
        if (this->unk_248 != 0) {
            if (this->actor.dmgEffectTimer == 0) {
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
            }
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        }
    }

    Math_ApproxF(&this->actor.speedXZ, this->unk_254, 0.2f);
    Actor_MoveForward(&this->actor);
    if (this->unk_246 != 0) {
        func_8002E4B4(globalCtx, &this->actor, 20.0f, 20.0f, 20.0f, 5);
    }

    D_80A21C40[this->unk_260](this);
    func_80A215BC(this, globalCtx);
}

void EnFz_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Gfx* D_80A21C50[] = { 0x06001130, 0x060021A0, 0x06002CA0 };
    EnFz* this = THIS;
    s32 pad;
    s32 sp74 = (6 - this->actor.colChkInfo.health) >> 1;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fz.c", 1167);
    if (this->actor.colChkInfo.health == 0) {
        sp74 = 2;
    }

    if (this->unk_261 != 0) {
        func_8002ED80(&this->actor, globalCtx, 0);
        func_80093D84(globalCtx->state.gfxCtx);
        if (1) {};
        gSPSegment(gfxCtx->polyXlu.p++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, globalCtx->state.frames & 0x7F, 0x20, 0x20, 1, 0,
                                    (globalCtx->state.frames * 2) & 0x7F, 0x20, 0x20));

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_fz.c", 1183),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetCombineLERP(gfxCtx->polyXlu.p++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIMITIVE,
                          TEXEL0, PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, ENVIRONMENT, 0);
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0x80, 155, 255, 255, 255);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 200, 200, 200, this->unk_258);
        gSPDisplayList(gfxCtx->polyXlu.p++, D_80A21C50[sp74]);
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fz.c", 1200);
    func_80A218A8(this, globalCtx);
}

void func_80A2145C(EnFz* this, Vec3f* a, Vec3f* b, Vec3f* c, f32 arg4) {
    EnFzStruct1* ptr = this->unk_274;
    s16 i;

    for (i = 0; i < 40; i++, ptr++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 1;
            ptr->unk_04 = *a;
            ptr->unk_10 = *b;
            ptr->unk_1C = *c;
            ptr->unk_2E = 0;
            ptr->unk_30 = arg4 / 1000.0f;
            ptr->unk_2C = 0;
            ptr->unk_01 = 0;
            return;
        }
    }
}

void func_80A21500(EnFz* this, Vec3f* a, Vec3f* b, Vec3f* c, f32 arg4, f32 arg5, s16 arg6, u8 arg7) {
    EnFzStruct1* ptr = this->unk_274;
    s16 i;

    for (i = 0; i < 40; i++, ptr++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 2;
            ptr->unk_04 = *a;
            ptr->unk_10 = *b;
            ptr->unk_1C = *c;
            ptr->unk_2E = 0;
            ptr->unk_30 = arg4 / 1000.0f;
            ptr->unk_34 = arg5 / 1000.0f;
            ptr->unk_2C = arg6;
            ptr->unk_01 = 0;
            ptr->unk_38 = arg7;
            return;
        }
    }
}

void func_80A215BC(EnFz* this, GlobalContext* globalCtx) {
    EnFzStruct1* ptr = this->unk_274;
    s16 i;
    Vec3f sp64;

    for (i = 0; i < 40; i++, ptr++) {
        if (ptr->unk_00 != 0) {
            ptr->unk_04.x += ptr->unk_10.x;
            ptr->unk_04.y += ptr->unk_10.y;
            ptr->unk_04.z += ptr->unk_10.z;
            ptr->unk_01++;
            ptr->unk_10.x += ptr->unk_1C.x;
            ptr->unk_10.y += ptr->unk_1C.y;
            ptr->unk_10.z += ptr->unk_1C.z;
            if (ptr->unk_00 == 1) {
                if (ptr->unk_2E == 0) {
                    ptr->unk_2C += 10;
                    if (ptr->unk_2C >= 100) {
                        ptr->unk_2E++;
                    }
                } else {
                    ptr->unk_2C -= 3;
                    if (ptr->unk_2C <= 0) {
                        ptr->unk_2C = 0;
                        ptr->unk_00 = 0;
                    }
                }
            } else if (ptr->unk_00 == 2) {
                Math_SmoothScaleMaxF(&ptr->unk_30, ptr->unk_34, 0.1f, ptr->unk_34 / 10.0f);
                if (ptr->unk_2E == 0) {
                    if (ptr->unk_01 >= 7) {
                        ptr->unk_2E++;
                    }
                } else {
                    ptr->unk_1C.y = 2.0f;
                    ptr->unk_2C -= 17;
                    ptr->unk_10.x *= 0.75f;
                    ptr->unk_10.z *= 0.75f;
                    if (ptr->unk_2C <= 0) {
                        ptr->unk_2C = 0;
                        ptr->unk_00 = 0;
                    }
                }

                if ((this->unk_263 == 0) && (ptr->unk_2C >= 0x65) && (ptr->unk_38 != 0)) {
                    this->collider3.dim.pos.x = ptr->unk_04.x;
                    this->collider3.dim.pos.y = ptr->unk_04.y;
                    this->collider3.dim.pos.z = ptr->unk_04.z;
                    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
                }

                sp64.x = ptr->unk_04.x;
                sp64.y = ptr->unk_04.y + 10.0f;
                sp64.z = ptr->unk_04.z;
                if ((ptr->unk_2E != 2) && (func_80A200B0(this, &sp64))) {
                    ptr->unk_2E = 2;
                    ptr->unk_10.x = 0.0f;
                    ptr->unk_10.z = 0.0f;
                }
            }
        }
    }
}

void func_80A218A8(EnFz* this, GlobalContext* globalCtx) {
    EnFzStruct1* ptr = &this->unk_274[0];
    GraphicsContext* localGfxCtx = globalCtx->state.gfxCtx;
    u8 flag = false;
    s16 i;
    GraphicsContext* gfxCtx = localGfxCtx;
    s32 pad;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, localGfxCtx, "../z_en_fz.c", 1384);
    func_80093D84(globalCtx->state.gfxCtx);
    for (i = 0; i < 40; i++, ptr++) {
        if (ptr->unk_00 > 0) {
            gDPPipeSync(gfxCtx->polyXlu.p++);
            if (!flag) {
                gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_060030A0));
                flag += true;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 195, 225, 235, ptr->unk_2C);
            gSPSegment(gfxCtx->polyXlu.p++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, (ptr->unk_01 + (i * 3)) * 3,
                                        (ptr->unk_01 + (i * 3)) * 15, 0x20, 0x40, 1, 0, 0, 0x20, 0x20));
            Matrix_Translate(ptr->unk_04.x, ptr->unk_04.y, ptr->unk_04.z, MTXMODE_NEW);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_Scale(ptr->unk_30, ptr->unk_30, 1.0f, MTXMODE_APPLY);
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(localGfxCtx, "../z_en_fz.c", 1424),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(D_06003158));
        }
    }

    Graph_CloseDisps(dispRefs, localGfxCtx, "../z_en_fz.c", 1430);
}
