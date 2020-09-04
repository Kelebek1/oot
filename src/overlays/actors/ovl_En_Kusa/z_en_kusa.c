/*
 * File: z_en_kusa.c
 * Overlay: ovl_En_Kusa
 * Description: Single Bush/Grass
 */

#include "z_en_kusa.h"
#include "vt.h"

#define FLAGS 0x00800010

#define THIS ((EnKusa*)thisx)

void EnKusa_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKusa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKusa_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A9C164(Actor* thisx, GlobalContext* globalCtx);

void func_80A9B7EC(EnKusa* this);
void func_80A9BEAC(EnKusa* this);
void func_80A9B89C(EnKusa* this);
void func_80A9C00C(EnKusa* this);
void func_80A9BA98(EnKusa* this);
void func_80A9BBB0(EnKusa* this);
void func_80A9BF3C(EnKusa* this);

void func_80A9B810(EnKusa* this, GlobalContext* globalCtx);
void func_80A9BF30(EnKusa* this, GlobalContext* globalCtx);
void func_80A9BEFC(EnKusa* this, GlobalContext* globalCtx);
void func_80A9B8D8(EnKusa* this, GlobalContext* globalCtx);
void func_80A9C068(EnKusa* this, GlobalContext* globalCtx);
void func_80A9BAD8(EnKusa* this, GlobalContext* globalCtx);
void func_80A9BC1C(EnKusa* this, GlobalContext* globalCtx);
void func_80A9BFA8(EnKusa* this, GlobalContext* globalCtx);

extern Gfx D_060002E0[];
extern Gfx D_040355E0[];
extern Gfx D_040356A0[];

static s16 D_80A9C1D0 = 0;
static s16 D_80A9C1D4 = 0;
static s16 D_80A9C1D8 = 0;
static s16 D_80A9C1DC = 0;

const ActorInit En_Kusa_InitVars = {
    ACTOR_EN_KUSA,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnKusa),
    (ActorFunc)EnKusa_Init,
    (ActorFunc)EnKusa_Destroy,
    (ActorFunc)EnKusa_Update,
    NULL,
};

static s16 D_80A9C200[] = { OBJECT_GAMEPLAY_FIELD_KEEP, OBJECT_KUSA, OBJECT_KUSA };

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x09, 0x29, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x4FC00758, 0x00, 0x00 }, 0x00, 0x01, 0x01 },
    { 12, 44, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit D_80A9C234 = { 0x00, 0x000C, 0x001E, 0xFF };

static Vec3f D_80A9C23C[] = {
    { 0.0f, 0.707099974155426f, 0.707099974155426f },
    { 0.707099974155426f, 0.707099974155426f, 0.0f },
    { 0.0f, 0.707099974155426f, -0.707099974155426f },
    { -0.707099974155426f, 0.707099974155426f, 0.0f },
};

static s16 D_80A9C26C[] = {
    0x006C, 0x0066, 0x0060, 0x0054, 0x0042, 0x0037, 0x002A, 0x0026,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 400, ICHAIN_CONTINUE),        ICHAIN_F32_DIV1000(gravity, 62336, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, 48536, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneForward, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),        ICHAIN_F32(uncullZoneDownward, 120, ICHAIN_STOP),
};

void EnKusa_SetupAction(EnKusa* this, EnKusaActionFunc actionFunc) {
    this->unk_19C = 0;
    this->actionFunc = actionFunc;
}

s32 func_80A9AFAC(EnKusa* this, GlobalContext* globalCtx, f32 arg2) {
    s32 pad;
    CollisionPoly* sp38;
    Vec3f sp2C;
    UNK_TYPE sp28;
    f32 tmp;

    sp2C.x = this->actor.posRot.pos.x;
    sp2C.y = this->actor.posRot.pos.y + 30.0f;
    sp2C.z = this->actor.posRot.pos.z;

    tmp = func_8003C9A4(&globalCtx->colCtx, &sp38, &sp28, &this->actor, &sp2C);
    if (tmp > -32000.0f) {
        this->actor.posRot.pos.y = tmp + arg2;
        Math_Vec3f_Copy(&this->actor.initPosRot.pos, &this->actor.posRot.pos);
        return 1;
    } else {
        osSyncPrintf(VT_COL(YELLOW, BLACK));
        // Failed to stay on the ground
        osSyncPrintf("地面に付着失敗(%s %d)\n", "../z_en_kusa.c", 323);
        osSyncPrintf(VT_RST);
        return 0;
    }
}

void func_80A9B07C(EnKusa* this, GlobalContext* globalCtx) {
    s16 tmp;

    switch (this->actor.params & 3) {
        case 0:
        case 2:
            tmp = (this->actor.params >> 8) & 0xF;
            if (tmp >= 0xD) {
                tmp = 0;
            }
            Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.posRot.pos, tmp * 16);
            break;

        case 1:
            if (Math_Rand_ZeroOne() < 0.5f) {
                Item_DropCollectible(globalCtx, &this->actor.posRot.pos, 0x10);
            } else {
                Item_DropCollectible(globalCtx, &this->actor.posRot.pos, 3);
            }
            break;
    }
}

void func_80A9B140(EnKusa* this) {
    this->actor.velocity.y += this->actor.gravity;
    if (this->actor.velocity.y < this->actor.minVelocityY) {
        this->actor.velocity.y = this->actor.minVelocityY;
    }
}

void func_80A9B174(Vec3f* arg0, f32 arg1) {
    arg1 += ((Math_Rand_ZeroOne() * 0.2f) - 0.1f) * arg1;

    arg0->x -= arg0->x * arg1;
    arg0->y -= arg0->y * arg1;
    arg0->z -= arg0->z * arg1;
}

void func_80A9B1FC(EnKusa* this) {
    this->actor.scale.y = 0.16000001f;
    this->actor.scale.x = this->actor.scale.z = 0.120000005f;
}

void func_80A9B21C(EnKusa* this, GlobalContext* globalCtx) {
    Vec3f spC4;
    Vec3f spB8;
    Vec3f* ptr;
    s32 pad;
    s32 i;

    for (i = 0; i < 4; i++) {
        ptr = &D_80A9C23C[i];

        spB8.x = this->actor.posRot.pos.x + ((ptr->x * this->actor.scale.x) * 20.0f);
        spB8.y = (this->actor.posRot.pos.y + ((ptr->y * this->actor.scale.y) * 20.0f)) + 10.0f;
        spB8.z = this->actor.posRot.pos.z + ((ptr->z * this->actor.scale.z) * 20.0f);

        spC4.x = (Math_Rand_ZeroOne() - 0.5f) * 8.0f;
        spC4.y = Math_Rand_ZeroOne() * 10.0f;
        spC4.z = (Math_Rand_ZeroOne() - 0.5f) * 8.0f;

        func_80029E8C(globalCtx, &spB8, &spC4, &spB8, -0x64, 0x40, 0x28, 3, 0,
                      D_80A9C26C[(s32)(Math_Rand_ZeroOne() * 111.1f) & 7], 0, 0, 0x50, -1, 1, D_040355E0);

        spB8.x = this->actor.posRot.pos.x + ((ptr->x * this->actor.scale.x) * 40.0f);
        spB8.y = (this->actor.posRot.pos.y + ((ptr->y * this->actor.scale.y) * 40.0f)) + 10.0f;
        spB8.z = this->actor.posRot.pos.z + ((ptr->z * this->actor.scale.z) * 40.0f);

        spC4.x = (Math_Rand_ZeroOne() - 0.5f) * 6.0f;
        spC4.y = Math_Rand_ZeroOne() * 10.0f;
        spC4.z = (Math_Rand_ZeroOne() - 0.5f) * 6.0f;

        func_80029E8C(globalCtx, &spB8, &spC4, &spB8, -0x64, 0x40, 0x28, 3, 0,
                      D_80A9C26C[(s32)(Math_Rand_ZeroOne() * 111.1f) % 7], 0, 0, 0x50, -1, 1, D_040356A0);
    }
}

void func_80A9B574(EnKusa* this, GlobalContext* globalCtx) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_INSECT, this->actor.posRot.pos.x,
                        this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0, Math_Rand_ZeroOne() * 65535.0f, 0,
                        1) == NULL) {
            break;
        }
    }
}

void func_80A9B630(Actor* thisx, GlobalContext* globalCtx) {
    EnKusa* this = THIS;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    Collider_CylinderUpdate(&this->actor, &this->collider);
}

void EnKusa_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnKusa* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    if (globalCtx->csCtx.state != 0) {
        this->actor.uncullZoneForward += 1000.0f;
    }

    func_80A9B630(thisx, globalCtx);
    func_80061ED4(&this->actor.colChkInfo, NULL, &D_80A9C234);

    if (this->actor.shape.rot.y == 0) {
        this->actor.shape.rot.y = this->actor.initPosRot.rot.y = this->actor.posRot.rot.y =
            Math_Rand_ZeroFloat(65536.0f);
    }

    if (func_80A9AFAC(this, globalCtx, 0) == 0) {
        Actor_Kill(&this->actor);
        return;
    }

    this->unk_19E = Object_GetIndex(&globalCtx->objectCtx, D_80A9C200[this->actor.params & 3]);
    if (this->unk_19E < 0) {
        // Bank danger!
        osSyncPrintf("Error : バンク危険！ (arg_data 0x%04x)(%s %d)\n", this->actor.params, "../z_en_kusa.c", 561);
        Actor_Kill(&this->actor);
        return;
    }

    func_80A9B7EC(this);
}

void EnKusa_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    Collider_DestroyCylinder(globalCtx, &THIS->collider);
}

void func_80A9B7EC(EnKusa* this) {
    EnKusa_SetupAction(this, func_80A9B810);
}

void func_80A9B810(EnKusa* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_19E)) {
        if (this->actor.flags & 0x800) {
            func_80A9BEAC(this);
        } else {
            func_80A9B89C(this);
        }
        this->actor.draw = func_80A9C164;
        this->actor.objBankIndex = this->unk_19E;
        this->actor.flags &= ~0x10;
    }
}

void func_80A9B89C(EnKusa* this) {
    EnKusa_SetupAction(this, func_80A9B8D8);
    this->actor.flags &= ~0x10;
}

void func_80A9B8D8(EnKusa* this, GlobalContext* globalCtx) {
    s32 pad;

    if (Actor_HasParent(&this->actor, globalCtx) != 0) {
        func_80A9BA98(this);
        Audio_PlaySoundAtPosition(globalCtx, &this->actor.posRot.pos, 0x14, NA_SE_PL_PULL_UP_PLANT);
        return;
    }

    if ((this->collider.base.acFlags & 2) != 0) {
        this->collider.base.acFlags &= ~2;
        func_80A9B21C(this, globalCtx);
        func_80A9B07C(this, globalCtx);
        Audio_PlaySoundAtPosition(globalCtx, &this->actor.posRot.pos, 0x14, NA_SE_EV_PLANT_BROKEN);
        if (((this->actor.params >> 4) & 1) != 0) {
            func_80A9B574(this, globalCtx);
        }

        if ((this->actor.params & 3) == 0) {
            Actor_Kill(&this->actor);
        } else {
            func_80A9BEAC(this);
            this->actor.flags = this->actor.flags | 0x800;
        }
        return;
    }

    if ((this->collider.base.maskA & 8) == 0) {
        if (this->actor.xzDistFromLink > 12.0f) {
            this->collider.base.maskA |= 8;
        }
    }

    if (this->actor.xzDistFromLink < 600.0f) {
        Collider_CylinderUpdate(&this->actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        if (this->actor.xzDistFromLink < 400.0f) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            if (this->actor.xzDistFromLink < 100.0f) {
                func_8002F580(&this->actor, globalCtx);
            }
        }
    }
}

void func_80A9BA98(EnKusa* this) {
    EnKusa_SetupAction(this, func_80A9BAD8);
    this->actor.room = -1;
    this->actor.flags |= 0x10;
}

void func_80A9BAD8(EnKusa* this, GlobalContext* globalCtx) {
    if (Actor_HasNoParent(&this->actor, globalCtx)) {
        this->actor.room = globalCtx->roomCtx.curRoom.num;
        func_80A9BBB0(this);
        this->actor.velocity.x = Math_Sins(this->actor.posRot.rot.y) * this->actor.speedXZ;
        this->actor.velocity.z = Math_Coss(this->actor.posRot.rot.y) * this->actor.speedXZ;
        this->actor.colChkInfo.mass = 0xF0;
        this->actor.gravity = -0.1f;
        func_80A9B140(this);
        func_80A9B174(&this->actor.velocity, 0.005f);
        func_8002D7EC(&this->actor);
        func_8002E4B4(globalCtx, &this->actor, 7.5f, 35.0f, 0.0f, 0xC5);
        this->actor.gravity = -3.2f;
    }
}

void func_80A9BBB0(EnKusa* this) {
    EnKusa_SetupAction(this, func_80A9BC1C);
    D_80A9C1D0 = -0xBB8;
    D_80A9C1D8 = (Math_Rand_ZeroOne() - 0.5f) * 1600.0f;
    D_80A9C1D4 = 0;
    D_80A9C1DC = 0;
}

void func_80A9BC1C(EnKusa* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp30;

    if (this->actor.bgCheckFlags & 0xB) {
        if (!(this->actor.bgCheckFlags & 0x20)) {
            Audio_PlaySoundAtPosition(globalCtx, &this->actor.posRot.pos, 0x14, 0x284E);
        }
        func_80A9B21C(this, globalCtx);
        func_80A9B07C(this, globalCtx);
        switch (this->actor.params & 3) {
            case 0:
            case 2:
                Actor_Kill(&this->actor);
                break;

            case 1:
                func_80A9BF3C(this);
                break;
        }
    } else {
        if ((this->actor.bgCheckFlags & 0x40) != 0) {
            sp30.x = this->actor.posRot.pos.x;
            sp30.y = this->actor.posRot.pos.y + this->actor.waterY;
            sp30.z = this->actor.posRot.pos.z;
            func_8002949C(globalCtx, &sp30, 0, 0, 0, 0x190);
            func_80029444(globalCtx, &sp30, 0x96, 0x28A, 0);
            func_80029444(globalCtx, &sp30, 0x190, 0x320, 4);
            func_80029444(globalCtx, &sp30, 0x1F4, 0x44C, 8);
            this->actor.minVelocityY = -3.0f;
            D_80A9C1D4 >>= 1;
            D_80A9C1D0 >>= 1;
            D_80A9C1DC >>= 1;
            D_80A9C1D8 >>= 1;
            this->actor.bgCheckFlags &= ~0x40;
            Audio_PlaySoundAtPosition(globalCtx, &this->actor.posRot.pos, 0x28, 0x28C5);
        }
        func_80A9B140(this);
        Math_ApproxS(&D_80A9C1D4, D_80A9C1D0, 0x1F4);
        Math_ApproxS(&D_80A9C1DC, D_80A9C1D8, 0xAA);
        this->actor.shape.rot.x += D_80A9C1D4;
        this->actor.shape.rot.y += D_80A9C1DC;
        func_80A9B174(&this->actor.velocity, 0.05f);
        func_8002D7EC(&this->actor);
        func_8002E4B4(globalCtx, &this->actor, 7.5f, 35.0f, 0.0f, 0xC5);
        Collider_CylinderUpdate(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80A9BEAC(EnKusa* this) {
    if ((this->actor.params & 3) != 1) {
        if ((this->actor.params & 3) == 2) {
            EnKusa_SetupAction(this, func_80A9BF30);
        }
    } else {
        EnKusa_SetupAction(this, func_80A9BEFC);
    }
}

void func_80A9BEFC(EnKusa* this, GlobalContext* globalCtx) {
    if (this->unk_19C >= 0x78) {
        func_80A9C00C(this);
    }
}

void func_80A9BF30(EnKusa* this, GlobalContext* globalCtx) {
}

void func_80A9BF3C(EnKusa* this) {
    this->actor.posRot.pos.x = this->actor.initPosRot.pos.x;
    this->actor.posRot.pos.y = this->actor.initPosRot.pos.y - 9.0f;
    this->actor.posRot.pos.z = this->actor.initPosRot.pos.z;
    func_80A9B1FC(this);
    this->actor.shape.rot = this->actor.initPosRot.rot;
    EnKusa_SetupAction(this, func_80A9BFA8);
}

void func_80A9BFA8(EnKusa* this, GlobalContext* globalCtx) {
    if ((this->unk_19C >= 0x79) && (Math_ApproxF(&this->actor.posRot.pos.y, this->actor.initPosRot.pos.y, 0.6f) != 0) &&
        (this->unk_19C >= 0xAA)) {
        func_80A9C00C(this);
    }
}

void func_80A9C00C(EnKusa* this) {
    EnKusa_SetupAction(this, func_80A9C068);
    func_80A9B1FC(this);
    this->actor.shape.rot = this->actor.initPosRot.rot;
    this->actor.flags &= ~0x800;
}

void func_80A9C068(EnKusa* this, GlobalContext* globalCtx) {
    s32 tmp = 1;

    tmp &= Math_ApproxF(&this->actor.scale.y, 0.4f, 0.014f);
    tmp &= Math_ApproxF(&this->actor.scale.x, 0.4f, 0.011f);
    this->actor.scale.z = this->actor.scale.x;

    if (tmp != 0) {
        Actor_SetScale(&this->actor, 0.4f);
        func_80A9B89C(this);
        this->collider.base.maskA &= ~8;
    }
}

void EnKusa_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnKusa* this = THIS;

    this->unk_19C++;
    this->actionFunc(this, globalCtx);
    if (this->actor.flags & 0x800) {
        this->actor.shape.unk_08 = -6.25f;
    } else {
        this->actor.shape.unk_08 = 0.0f;
    }
}

void func_80A9C164(Actor* thisx, GlobalContext* globalCtx) {
    static Gfx* D_80A9C294[] = { 0x0500B9D0, 0x06000140, 0x06000140 };

    EnKusa* this = THIS;

    if (this->actor.flags & 0x800) {
        Gfx_DrawDListOpa(globalCtx, D_060002E0);
    } else {
        Gfx_DrawDListOpa(globalCtx, D_80A9C294[this->actor.params & 3]);
    }
}
