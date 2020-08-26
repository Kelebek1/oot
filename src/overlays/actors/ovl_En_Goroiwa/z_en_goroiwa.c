/*
 * File: z_en_goroiwa.c
 * Overlay: ovl_En_Goroiwa
 * Description: Rolling Boulder
 */

#include "z_en_goroiwa.h"
#include "vt.h"

#define FLAGS 0x00000010

#define THIS ((EnGoroiwa*)thisx)

void EnGoroiwa_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGoroiwa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGoroiwa_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGoroiwa_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80A4C814(EnGoroiwa* this, GlobalContext* globalCtx);
s32 func_80A4C6C8(EnGoroiwa* this, GlobalContext* globalCtx);

void func_80A4D5E0(EnGoroiwa* this);
void func_80A4D9DC(EnGoroiwa* this);
void func_80A4D8CC(EnGoroiwa* this);
void func_80A4DA7C(EnGoroiwa* this);
void func_80A4DB90(EnGoroiwa* this);

void func_80A4D624(EnGoroiwa* this, GlobalContext* globalCtx);
void func_80A4DA3C(EnGoroiwa* this, GlobalContext* globalCtx);
void func_80A4D944(EnGoroiwa* this, GlobalContext* globalCtx);
void func_80A4DAD0(EnGoroiwa* this, GlobalContext* globalCtx);
void func_80A4DC00(EnGoroiwa* this, GlobalContext* globalCtx);

extern Gfx D_060006B0[];
extern Gfx D_0400D340[];

const ActorInit En_Goroiwa_InitVars = {
    ACTOR_EN_GOROIWA,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(EnGoroiwa),
    (ActorFunc)EnGoroiwa_Init,
    (ActorFunc)EnGoroiwa_Destroy,
    (ActorFunc)EnGoroiwa_Update,
    (ActorFunc)EnGoroiwa_Draw,
};

static ColliderJntSphItemInit sJntSphItemsInit[1] = {
    {
        { 0x00, { 0x20000000, 0x00, 0x04 }, { 0x00000000, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 58 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_UNK10, 0x11, 0x00, 0x39, 0x20, COLSHAPE_JNTSPH },
    1,
    sJntSphItemsInit,
};

static CollisionCheckInfoInit D_80A4DEB4 = { 0x00, 0x000C, 0x003C, 0xFE };

// Unused?
static f32 D_80A4DEBC[] = { 10.0f, 9.2f };

static f32 D_80A4DEC4[] = { 0.0f, 59.5f };
static Vec3f D_80A4DECC = { 0.0f, 0.0f, 0.0f };
static Vec3f D_80A4DED8 = { 0.0f, 0.3f, 0.0f };
static Vec3f D_80A4DEE4 = { 0.0f, 1.0f, 0.0f };
static f32 D_80A4DEF0[] = { 0.0f, 59.5f };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(gravity, 64676, ICHAIN_CONTINUE), ICHAIN_F32_DIV1000(minVelocityY, 50536, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),   ICHAIN_F32(uncullZoneForward, 1500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 150, ICHAIN_CONTINUE),   ICHAIN_F32(uncullZoneDownward, 1500, ICHAIN_STOP),
};

void func_80A4BCA0(EnGoroiwa* this) {
    Sphere16* sphere = &this->collider.list[0].dim.worldSphere;

    sphere->center.x = this->actor.posRot.pos.x;
    sphere->center.y = D_80A4DEC4[(this->actor.params >> 0xA) & 1] + this->actor.posRot.pos.y;
    sphere->center.z = this->actor.posRot.pos.z;
}

void func_80A4BD04(EnGoroiwa* this, GlobalContext* globalCtx) {
    s32 pad;

    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderItems);
    func_80A4BCA0(this);
    this->collider.list[0].dim.worldSphere.radius = 58;
}

void func_80A4BD70(EnGoroiwa* this, u8 arg0) {
    this->unk_1D3 &= ~3;
    this->unk_1D3 |= arg0;
}

s32 func_80A4BD8C(Vec3f* velocity, Vec3f* arg2) {
    f32 magnitude = Math3D_Vec3fMagnitude(arg2);

    if (magnitude < 0.001f) {
        return 0;
    }

    velocity->x = arg2->x * (1.0f / magnitude);
    velocity->y = arg2->y * (1.0f / magnitude);
    velocity->z = arg2->z * (1.0f / magnitude);
    return 1;
}

void func_80A4BE10(EnGoroiwa* this, GlobalContext* globalCtx) {
    if (globalCtx->sceneNum == SCENE_SPOT04) {
        this->unk_1D2 = 1;
        mREG(12) = 0x398;
    } else {
        this->unk_1D2 = 0;
        mREG(12) = 0x3E8;
    }
}

void func_80A4BE54(EnGoroiwa* this, GlobalContext* globalCtx) {
    Path* path = &globalCtx->setupPathList[this->actor.params & 0xFF];
    Vec3s* pos = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points) + this->unk_1CE;
    Vec3f sp1C;

    sp1C.x = pos->x;
    sp1C.y = pos->y;
    sp1C.z = pos->z;
    this->actor.posRot.rot.y = Math_Vec3f_Yaw(&this->actor.posRot.pos, &sp1C);
}

void func_80A4BF28(EnGoroiwa* this, GlobalContext* globalCtx, Vec3f* arg2) {
    s16 params2 = (this->actor.params >> 8) & 3;
    Path* path = &globalCtx->setupPathList[this->actor.params & 0xFF];
    s16 idx = this->unk_1CC - this->unk_1D0;
    Vec3s* pos1;
    Vec3s* pos2;

    if (idx < 0) {
        if ((params2 == 0) || (params2 == 1)) {
            idx = this->unk_1CA;
        } else if (params2 == 3) {
            idx = 1;
        }
    } else if (this->unk_1CA < idx) {
        if ((params2 == 0) || (params2 == 1)) {
            idx = 0;
        } else if (params2 == 3) {
            idx = this->unk_1CA - 1;
        }
    }

    pos1 = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points) + this->unk_1CC;
    pos2 = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points) + idx;

    arg2->x = pos1->x - pos2->x;
    arg2->y = pos1->x - pos2->y;
    arg2->z = pos1->x - pos2->z;
}

void func_80A4C080(EnGoroiwa* this) {
    s16 params = (this->actor.params >> 8) & 3;

    if (this->unk_1CE < 0) {
        if ((params == 0) || (params == 1)) {
            this->unk_1CE = this->unk_1CA - 1;
            this->unk_1CC = this->unk_1CA;
            this->unk_1D0 = -1;
        } else if (params == 3) {
            this->unk_1CC = 0;
            this->unk_1CE = 1;
            this->unk_1D0 = 1;
        }
    } else if (this->unk_1CA < this->unk_1CE) {
        if ((params == 0) || (params == 1)) {
            this->unk_1CC = 0;
            this->unk_1CE = 1;
            this->unk_1D0 = 1;
        } else if (params == 3) {
            this->unk_1CC = this->unk_1CA;
            this->unk_1CE = this->unk_1CA - 1;
            this->unk_1D0 = -1;
        }
    }
}

void func_80A4C134(EnGoroiwa* this) {
    this->unk_1CC = this->unk_1CE;
    this->unk_1CE += this->unk_1D0;
    func_80A4C080(this);
}

void func_80A4C164(EnGoroiwa* this) {
    this->unk_1D0 = -this->unk_1D0;
    this->unk_1CC = this->unk_1CE;
    this->unk_1CE += this->unk_1D0;
}

void func_80A4C188(EnGoroiwa* this, GlobalContext* globalCtx) {
    this->unk_1CA = globalCtx->setupPathList[this->actor.params & 0xFF].count - 1;
    this->unk_1CC = 0;
    this->unk_1CE = 1;
    this->unk_1D0 = 1;
}

void func_80A4C1C4(EnGoroiwa* this, GlobalContext* globalCtx, s32 arg2) {
    Path* path = &globalCtx->setupPathList[this->actor.params & 0xFF];
    Vec3s* pos = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points) + arg2;

    this->actor.posRot.pos.x = pos->x;
    this->actor.posRot.pos.y = pos->y;
    this->actor.posRot.pos.z = pos->z;
}

void func_80A4C264(EnGoroiwa* this) {
    this->unk_1B0.x = 1.0f;
    this->unk_1C0 = 1.0f;
}

s32 func_80A4C27C(EnGoroiwa* this, GlobalContext* globalCtx) {
    s32 pad;
    Path* path = &globalCtx->setupPathList[this->actor.params & 0xFF];
    Vec3s* pos1 = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points) + this->unk_1CE;
    Vec3s* pos2 = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points) + this->unk_1CC;

    if ((pos1->x == pos2->x) && (pos1->z == pos2->z)) {
        if (pos1->y == pos2->y) {
            // Error: rail data incorrect (points are stacking up)
            osSyncPrintf("Error : レールデータ不正(点が重なっている)");
            osSyncPrintf("(%s %d)(arg_data 0x%04x)\n", "../z_en_gr.c", 0x22F, this->actor.params);
        }

        if (pos1->y > pos2->y) {
            return 1;
        } else {
            return -1;
        }
    }

    return 0;
}

void func_80A4C3A4(GlobalContext* globalCtx, Vec3f* arg1) {
    Vec3f sp7C;
    s16 inc = 0;
    s32 i;

    for (i = 0; i < 8; i++) {
        inc += 0x4E20;
        sp7C.x = ((47.0f * ((Math_Rand_ZeroOne() * 0.5f) + 0.5f)) * Math_Sins(inc)) + arg1->x;
        sp7C.y = ((Math_Rand_ZeroOne() - 0.5f) * 40.0f) + arg1->y;
        sp7C.z = ((47.0f * ((Math_Rand_ZeroOne() * 0.5f) + 0.5f)) * Math_Coss(inc)) + arg1->z;
        func_800286CC(globalCtx, &sp7C, &D_80A4DECC, &D_80A4DED8, (s16)(Math_Rand_ZeroOne() * 30.0f) + 0x64, 0x50);
        func_800286CC(globalCtx, &sp7C, &D_80A4DECC, &D_80A4DED8, (s16)(Math_Rand_ZeroOne() * 20.0f) + 0x50, 0x50);
    }
}

void func_80A4C594(GlobalContext* globalCtx, Vec3f* arg1) {
    Vec3f sp4C;
    s16 inc = 0;
    s32 i;

    for (i = 0; i < 11; i++) {
        inc += 0x1746;
        sp4C.x = (Math_Sins(inc) * 55.0f) + arg1->x;
        sp4C.y = arg1->y;
        sp4C.z = (Math_Coss(inc) * 55.0f) + arg1->z;
        func_8002949C(globalCtx, &sp4C, 0, 0, 0, 0x15E);
    }

    func_80029444(globalCtx, arg1, 0x12C, 0x2BC, 0);
    func_80029444(globalCtx, arg1, 0x1F4, 0x384, 4);
    func_80029444(globalCtx, arg1, 0x1F4, 0x514, 8);
}

s32 func_80A4C6C8(EnGoroiwa* this, GlobalContext* globalCtx) {
    Path* path;
    s32 ret;
    s32 pad;
    Vec3s* pos;

    Math_ApproxF(&this->actor.speedXZ, mREG(12) * 0.01f, 0.3f);
    func_8002D868(&this->actor);

    path = &globalCtx->setupPathList[this->actor.params & 0xFF];
    pos = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points) + this->unk_1CE;

    ret = 1;
    ret &= Math_ApproxF(&this->actor.posRot.pos.x, pos->x, fabsf(this->actor.velocity.x));
    ret &= Math_ApproxF(&this->actor.posRot.pos.z, pos->z, fabsf(this->actor.velocity.z));
    this->actor.posRot.pos.y += this->actor.velocity.y;
    return ret;
}

s32 func_80A4C814(EnGoroiwa* this, GlobalContext* globalCtx) {
    Path* path = &globalCtx->setupPathList[this->actor.params & 0xFF];
    Vec3s* pos1 = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points) + this->unk_1CE;
    s32 pad;
    Vec3s* pos2 = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points) + this->unk_1CC;
    s32 ret;
    Vec3f sp38;
    Vec3f sp2C;

    sp2C.x = pos1->x;
    sp2C.y = pos1->y;
    sp2C.z = pos1->z;
    Math_ApproxF(&this->actor.speedXZ, mREG(12) * 0.01f, 0.3f);
    if (Math3D_Vec3fDistSq(&sp2C, &this->actor.posRot.pos) < 25.0f) {
        Math_Vec3f_Diff(&sp2C, &this->actor.posRot.pos, &sp38);
    } else {
        sp38.x = sp2C.x - pos2->x;
        sp38.y = sp2C.y - pos2->y;
        sp38.z = sp2C.z - pos2->z;
    }

    func_80A4BD8C(&this->actor.velocity, &sp38);
    this->actor.velocity.x = this->actor.velocity.x * this->actor.speedXZ;
    this->actor.velocity.y = this->actor.velocity.y * this->actor.speedXZ;
    this->actor.velocity.z = this->actor.velocity.z * this->actor.speedXZ;

    ret = 1;
    ret &= Math_ApproxF(&this->actor.posRot.pos.x, sp2C.x, fabsf(this->actor.velocity.x));
    ret &= Math_ApproxF(&this->actor.posRot.pos.y, sp2C.y, fabsf(this->actor.velocity.y));
    ret &= Math_ApproxF(&this->actor.posRot.pos.z, sp2C.z, fabsf(this->actor.velocity.z));
    return ret;
}

s32 func_80A4CA50(EnGoroiwa* this, GlobalContext* globalCtx) {
    s32 pad;
    Path* path = &globalCtx->setupPathList[this->actor.params & 0xFF];
    Vec3s* pos = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points) + this->unk_1CE;

    Math_ApproxF(&this->actor.velocity.y, (mREG(12) * 0.01f) * 0.5f, 0.18f);
    this->actor.posRot.pos.x = pos->x;
    this->actor.posRot.pos.z = pos->z;
    return Math_ApproxF(&this->actor.posRot.pos.y, pos->y, fabsf(this->actor.velocity.y));
}

s32 func_80A4CB78(EnGoroiwa* this, GlobalContext* globalCtx) {
    s32 pad;
    Path* path = &globalCtx->setupPathList[this->actor.params & 0xFF];
    Vec3s* pos = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points) + this->unk_1CE;
    f32 sp78;
    f32 oldY;
    f32 pad2;
    s32 sp6C;
    CollisionPoly* sp68;
    Vec3f sp5C;
    f32 tmpf1;
    f32 tmpf2;
    u32 sp50;
    Vec3f sp44;
    WaterBox* sp40;
    f32 sp3C;
    Vec3f sp30;

    sp78 = pos->y;
    Math_ApproxF(&this->actor.velocity.y, -14.0f, 1.0f);
    this->actor.posRot.pos.x = pos->x;
    this->actor.posRot.pos.z = pos->z;
    oldY = this->actor.posRot.pos.y;
    if (1) {};
    this->actor.posRot.pos.y += this->actor.velocity.y;

    if ((this->actor.velocity.y < 0.0f) && (sp78 >= this->actor.posRot.pos.y)) {
        if (this->unk_1C6 == 0) {
            if (this->actor.xzDistFromLink < 600.0f) {
                sp6C = Quake_Add(ACTIVE_CAM, 3);
                Quake_SetSpeed(sp6C, -0x3CB0);
                Quake_SetQuakeValues(sp6C, 3, 0, 0, 0);
                Quake_SetCountdown(sp6C, 7);
            }

            this->unk_1C0 = 0.0f;
            if ((this->unk_1D3 & 0x10) == 0) {
                sp5C.x = this->actor.posRot.pos.x;
                sp5C.y = this->actor.posRot.pos.y + 50.0f;
                sp5C.z = this->actor.posRot.pos.z;
                tmpf1 = func_8003CA0C(globalCtx, &globalCtx->colCtx, &sp68, &sp50, &this->actor, &sp5C);
                tmpf2 = (tmpf1 - (this->actor.posRot.pos.y - 59.5f));
                if (fabsf(tmpf2) < 15.0f) {
                    sp44.x = this->actor.posRot.pos.x;
                    sp44.y = tmpf1 + 10.0f;
                    sp44.z = this->actor.posRot.pos.z;
                    func_80A4C3A4(globalCtx, &sp44);
                }
            }
        }

        if (this->unk_1C6 > 0) {
            return 1;
        }

        this->unk_1C6++;
        this->actor.velocity.y *= -0.3f;
        this->actor.posRot.pos.y = sp78 - ((this->actor.posRot.pos.y - sp78) * 0.3f);
    }

    if ((this->unk_1C6 == 0) &&
        (func_80042244(globalCtx, &globalCtx->colCtx, this->actor.posRot.pos.x, this->actor.posRot.pos.z, &sp3C,
                       &sp40) != 0) &&
        (this->actor.posRot.pos.y <= sp3C)) {
        this->unk_1D3 |= 0x10;
        if (oldY > sp3C) {
            sp30.x = this->actor.posRot.pos.x;
            sp30.y = sp3C;
            sp30.z = this->actor.posRot.pos.z;
            func_80A4C594(globalCtx, &sp30);
            this->actor.velocity.y *= 0.2f;
        }

        if (this->actor.velocity.y < -8.0f) {
            this->actor.velocity.y = -8.0f;
        }
    }

    return 0;
}

void func_80A4CED8(EnGoroiwa* this, GlobalContext* globalCtx) {
    s32 pad[2];
    f32 sp8C;
    Vec3f sp80;
    Vec3f sp74;
    MtxF sp34;
    Vec3f sp28;

    if ((this->unk_1D3 & 8) != 0) {
        sp8C = this->unk_1BC;
    } else {
        this->unk_1BC = Math3D_Vec3f_DistXYZ(&this->actor.posRot.pos, &this->actor.pos4) * 0.016806724f;
        sp8C = this->unk_1BC;
    }
    sp8C *= this->unk_1C0;

    if ((this->unk_1D3 & 8) != 0) {
        func_80A4BF28(this, globalCtx, &sp28);
        Math3D_Vec3f_Cross(&D_80A4DEE4, &this->actor.velocity, &sp80);
    } else {
        Math3D_Vec3f_Cross(&D_80A4DEE4, &this->actor.velocity, &sp80);
    }

    if (func_80A4BD8C(&sp74, &sp80) != 0) {
        this->unk_1B0 = sp74;
    } else {
        sp74 = this->unk_1B0;
    }

    func_800D23FC(sp8C, &sp74, MTXMODE_NEW);
    Matrix_RotateY(this->actor.shape.rot.y * 0.0000958738f, MTXMODE_APPLY);
    Matrix_RotateX(this->actor.shape.rot.x * 0.0000958738f, MTXMODE_APPLY);
    Matrix_RotateZ(this->actor.shape.rot.z * 0.0000958738f, MTXMODE_APPLY);
    Matrix_Get(&sp34);
    func_800D20CC(&sp34, &this->actor.shape.rot, 0);
}

void func_80A4D074(EnGoroiwa* this, GlobalContext* globalCtx) {
    s16 params = (this->actor.params >> 8) & 3;

    func_80A4C134(this);
    if (((params == 0) || (params == 1)) && (((this->unk_1CC == 0) || (this->unk_1CC == this->unk_1CA)))) {
        func_80A4C1C4(this, globalCtx, this->unk_1CC);
    }
    func_80A4BE54(this, globalCtx);
}

void func_80A4D0FC(EnGoroiwa* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f* pos = &this->actor.posRot.pos;
    s16 params = (this->actor.params >> 0xA) & 1;
    Vec3f spD0;
    Vec3f spC4;
    s32 i;
    s16 inc;
    f32 sins;
    f32 coss;
    s16 rand;

    for (i = 0, inc = 0; i < 16; i++, inc += 0x4E20) {
        sins = Math_Sins(inc);
        coss = Math_Coss(inc);
        rand = Math_Rand_ZeroOne() * 65535.0f;

        spD0.x = ((Math_Rand_ZeroOne() * 50.0f) * sins) * Math_Sins(rand);
        spD0.y = (((Math_Rand_ZeroOne() - 0.5f) * 100.0f) * Math_Sins(rand)) + D_80A4DEF0[params];
        spD0.z = ((Math_Rand_ZeroOne() * 50.0f) * coss) * Math_Sins(rand);

        spC4.x = spD0.x * 0.2f;
        spC4.y = (Math_Rand_ZeroOne() * 15.0f) + 2.0f;
        spC4.z = spD0.z * 0.2f;

        Math_Vec3f_Sum(&spD0, pos, &spD0);
        func_80029E8C(globalCtx, &spD0, &spC4, &spD0, -0x154, 0x21, 0x1C, 2, 0, (Math_Rand_ZeroOne() * 7.0f) + 1.0f, 1,
                      0, 0x46, -1, 1, D_0400D340);
    }

    spD0.x = pos->x;
    spD0.y = pos->y + D_80A4DEF0[params];
    spD0.z = pos->z;
    func_80033480(globalCtx, &spD0, 80.0f, 5, 0x46, 0x6E, 1);
    func_80033480(globalCtx, &spD0, 90.0f, 5, 0x6E, 0xA0, 1);
}

void EnGoroiwa_Init(Actor* thisx, GlobalContext* globalCtx) {
    static f32 D_80A4DF10[] = { 0.0f, 595.0f };

    EnGoroiwa* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    func_80A4BD04(this, globalCtx);

    if ((this->actor.params & 0xFF) == 0xFF) {
        // Error, arg_data incorrect
        osSyncPrintf("Ｅｒｒｏｒ : arg_data が不正(%s %d)(arg_data 0x%04x)\n", "../z_en_gr.c", 0x409,
                     this->actor.params);
        Actor_Kill(&this->actor);
        return;
    }

    if (globalCtx->setupPathList[this->actor.params & 0xFF].count < 2) {
        // Error, rail data incorrect
        osSyncPrintf("Ｅｒｒｏｒ : レールデータ が不正(%s %d)\n", "../z_en_gr.c", 0x413);
        Actor_Kill(&this->actor);
        return;
    }

    func_80061ED4(&this->actor.colChkInfo, NULL, &D_80A4DEB4);
    ActorShape_Init(&this->actor.shape, D_80A4DF10[(this->actor.params >> 0xA) & 1], ActorShadow_DrawFunc_Circle, 9.4f);
    this->actor.shape.unk_14 = 0xC8;
    func_80A4BE10(this, globalCtx);
    func_80A4C188(this, globalCtx);
    func_80A4C1C4(this, globalCtx, 0);
    func_80A4C264(this);
    func_80A4BE54(this, globalCtx);
    func_80A4D5E0(this);
    osSyncPrintf("(ごろ岩)(arg 0x%04x)(rail %d)(end %d)(bgc %d)(hit %d)\n", this->actor.params,
                 this->actor.params & 0xFF, (this->actor.params >> 8) & 3, (this->actor.params >> 0xA) & 1,
                 this->actor.initPosRot.rot.z & 1);
}

void EnGoroiwa_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    Collider_DestroyJntSph(globalCtx, &THIS->collider);
}

void func_80A4D5E0(EnGoroiwa* this) {
    this->actionFunc = func_80A4D624;
    func_80A4BD70(this, 3);
    this->unk_1C0 = 1.0f;
}

void func_80A4D624(EnGoroiwa* this, GlobalContext* globalCtx) {
    static EnGoroiwaFunc1 D_80A4DF18[] = { func_80A4C814, func_80A4C6C8 };

    static EnGoroiwaFunc2 D_80A4DF20[] = { func_80A4D9DC, func_80A4D8CC };

    s32 pad;
    s16 tmp;

    if ((this->collider.base.atFlags & 2) != 0) {
        this->collider.base.atFlags &= ~2;
        this->unk_1D3 &= ~4;
        tmp = this->actor.yawTowardsLink - this->actor.posRot.rot.y;
        if ((tmp >= -0x3FFF) && (tmp < 0x4000)) {
            this->unk_1D3 |= 4;
            if ((((this->actor.params >> 0xA) & 1) != 0) || ((this->actor.initPosRot.rot.z & 1) != 1)) {
                func_80A4C164(this);
                func_80A4BE54(this, globalCtx);
            }
        }

        func_8002F6D4(globalCtx, &this->actor, 2.0f, this->actor.yawTowardsLink, 0.0f, 0);
        osSyncPrintf(VT_FGCOL(CYAN));
        // Knock the player away
        osSyncPrintf("Player ぶっ飛ばし\n");
        osSyncPrintf(VT_RST);
        D_80A4DF20[(this->actor.params >> 0xA) & 1](this);
        func_8002F7DC(&PLAYER->actor, NA_SE_PL_BODY_HIT);
        if ((this->actor.initPosRot.rot.z & 1) == 1) {
            this->unk_1C8 = 50;
        }
    } else if (D_80A4DF18[(this->actor.params >> 0xA) & 1](this, globalCtx) != 0) {
        s16 params = (this->actor.params >> 8) & 3;
        if ((params == 1) && ((this->unk_1CE == 0) || (this->unk_1CE == this->unk_1CA))) {
            func_80A4D0FC(this, globalCtx);
        }

        func_80A4D074(this, globalCtx);
        if ((params == 3) && ((this->unk_1CC == 0) || (this->unk_1CC == this->unk_1CA))) {
            func_80A4D9DC(this);
        } else if ((((this->actor.params >> 0xA) & 1) == 0) && (this->unk_1CC != 0) &&
                   (this->unk_1CC != this->unk_1CA)) {
            s32 ret = func_80A4C27C(this, globalCtx);
            if (ret > 0) {
                func_80A4DA7C(this);
            } else if (ret < 0) {
                func_80A4DB90(this);
            } else {
                func_80A4D5E0(this);
            }
        } else {
            func_80A4D5E0(this);
        }
    }

    Audio_PlayActorSound2(&this->actor, NA_SE_EV_BIGBALL_ROLL - SFX_FLAG);
}

void func_80A4D8CC(EnGoroiwa* this) {
    this->actionFunc = func_80A4D944;
    func_80A4BD70(this, 2);
    this->actor.gravity = -0.86f;
    this->actor.minVelocityY = -15.0f;
    this->actor.speedXZ *= 0.15f;
    this->actor.velocity.y = 5.0f;
    this->unk_1C0 = 1.0f;
}

void func_80A4D944(EnGoroiwa* this, GlobalContext* globalCtx) {
    func_80A4C6C8(this, globalCtx);
    if ((this->actor.bgCheckFlags & 1) && (this->actor.velocity.y < 0.0f)) {
        if (((this->unk_1D3 & 4) != 0) && ((this->actor.initPosRot.rot.z & 1) == 1)) {
            func_80A4C164(this);
            func_80A4BE54(this, globalCtx);
        }
        func_80A4D9DC(this);
    }
}

void func_80A4D9DC(EnGoroiwa* this) {
    static s16 D_80A4DF28[] = { 0x0014, 0x0006 };

    this->actionFunc = func_80A4DA3C;
    this->actor.speedXZ = 0.0f;
    func_80A4BD70(this, 2);
    this->unk_1C4 = D_80A4DF28[this->actor.initPosRot.rot.z & 1];
    this->unk_1C0 = 0.0f;
}

void func_80A4DA3C(EnGoroiwa* this, GlobalContext* globalCtx) {
    if (this->unk_1C4 > 0) {
        this->unk_1C4--;
        return;
    }

    this->collider.base.atFlags &= ~2;
    func_80A4D5E0(this);
}

void func_80A4DA7C(EnGoroiwa* this) {
    this->actionFunc = func_80A4DAD0;
    func_80A4BD70(this, 3);
    this->unk_1C0 = 0.0f;
    this->actor.velocity.y = fabsf(this->actor.speedXZ) * 0.1f;
}

void func_80A4DAD0(EnGoroiwa* this, GlobalContext* globalCtx) {
    if (this->collider.base.atFlags & 2) {
        this->collider.base.atFlags &= ~2;
        func_8002F6D4(globalCtx, &this->actor, 2.0f, this->actor.yawTowardsLink, 0.0f, 4);
        func_8002F7DC(&PLAYER->actor, NA_SE_PL_BODY_HIT);
        if ((this->actor.initPosRot.rot.z & 1) == 1) {
            this->unk_1C8 = 50;
        }
    } else if (func_80A4CA50(this, globalCtx) != 0) {
        func_80A4D074(this, globalCtx);
        func_80A4D5E0(this);
        this->actor.speedXZ = 0.0f;
    }
}

void func_80A4DB90(EnGoroiwa* this) {
    this->actionFunc = func_80A4DC00;
    func_80A4BD70(this, 3);
    this->unk_1C0 = 0.3f;
    this->unk_1C6 = 0;
    this->actor.velocity.y = fabsf(this->actor.speedXZ) * -0.3f;
    this->unk_1D3 |= 8;
    this->unk_1D3 &= ~0x10;
}

void func_80A4DC00(EnGoroiwa* this, GlobalContext* globalCtx) {
    if (this->collider.base.atFlags & 2) {
        this->collider.base.atFlags &= ~2;
        func_8002F6D4(globalCtx, &this->actor, 2.0f, this->actor.yawTowardsLink, 0.0f, 4);
        func_8002F7DC(&PLAYER->actor, NA_SE_PL_BODY_HIT);
        if ((this->actor.initPosRot.rot.z & 1) == 1) {
            this->unk_1C8 = 50;
        }
    } else if (func_80A4CB78(this, globalCtx) != 0) {
        func_80A4D074(this, globalCtx);
        func_80A4D5E0(this);
        this->unk_1D3 = this->unk_1D3 & 0xFFF7;
        this->actor.speedXZ = 0.0f;
    }
}

void EnGoroiwa_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGoroiwa* this = THIS;
    s32 pad;
    Player* player = PLAYER;
    CollisionPoly* sp30;

    if (!(player->stateFlags1 & 0x300000C0)) {
        if (this->unk_1C8 > 0) {
            this->unk_1C8--;
        }

        this->actionFunc(this, globalCtx);
        if (((this->actor.params >> 0xA) & 1) != 0) {
            if (((this->actor.params >> 0xA) & 1) == 1) {
                func_8002E4B4(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 0x1C);
            }
        } else {
            this->actor.groundY =
                func_8003C9A4(&globalCtx->colCtx, &this->actor.floorPoly, &sp30, &this->actor, &this->actor.posRot.pos);
        }

        func_80A4CED8(this, globalCtx);
        if (this->actor.xzDistFromLink < 300.0f) {
            func_80A4BCA0(this);
            if (((this->unk_1D3 & 1) != 0) && (this->unk_1C8 <= 0)) {
                CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            }

            if (((this->unk_1D3 & 2) != 0) && (this->unk_1C8 <= 0)) {
                CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            }
        }
    }
}

void EnGoroiwa_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, D_060006B0);
}
