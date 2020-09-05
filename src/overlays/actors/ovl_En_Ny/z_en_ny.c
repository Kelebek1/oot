/*
 * File: z_en_ny.c
 * Overlay: ovl_En_Ny
 * Description: Spike Enemy (Water Temple)
 */

#include "z_en_ny.h"

#define FLAGS 0x00000005

#define THIS ((EnNy*)thisx)

void EnNy_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNy_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNy_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNy_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80ABDBF8(Actor* thisx, GlobalContext* globalCtx);
void func_80ABDBB8(Actor* thisx, GlobalContext* globalCtx);
void func_80ABE040(Actor* thisx, GlobalContext* globalCtx);

void func_80ABCDBC(EnNy* this);

void func_80ABCF4C(EnNy* this, GlobalContext* globalCtx);
void func_80ABD05C(EnNy* this, GlobalContext* globalCtx);
void func_80ABD11C(EnNy* this, GlobalContext* globalCtx);
void func_80ABCE50(EnNy* this, GlobalContext* globalCtx);
void func_80ABCE90(EnNy* this, GlobalContext* globalCtx);
void func_80ABCEEC(EnNy* this, GlobalContext* globalCtx);
void func_80ABD728(EnNy* this, GlobalContext* globalCtx);
void func_80ABD9AC(EnNy* this, GlobalContext* globalCtx);

extern Gfx D_06001EA8[];
extern Gfx D_06001DD0[];
extern Gfx D_06001FC8[];

const ActorInit En_Ny_InitVars = {
    ACTOR_EN_NY,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_NY,
    sizeof(EnNy),
    (ActorFunc)EnNy_Init,
    (ActorFunc)EnNy_Destroy,
    (ActorFunc)EnNy_Update,
    (ActorFunc)EnNy_Draw,
};

static ColliderJntSphItemInit sJntSphItemsInit[1] = {
    {
        { 0x00, { 0xFFCFFFFF, 0x04, 0x08 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_UNK10, 0x11, 0x09, 0x39, 0x10, COLSHAPE_JNTSPH },
    1,
    sJntSphItemsInit,
};

DamageTable D_80ABE364 = {
    0x00, 0x00, 0x00, 0xF2, 0x00, 0xF2, 0xF2, 0x12, 0x00, 0xF2, 0xF4, 0x24, 0xF2, 0xF2, 0xE4, 0x00,
    0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF4, 0xF2, 0x00, 0xF8, 0xF4, 0x00, 0x00, 0x00, 0x00,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(naviEnemyId, 40, ICHAIN_CONTINUE),
    ICHAIN_U8(unk_1F, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 30, ICHAIN_STOP),
};

void EnNy_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnNy* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.colChkInfo.damageTable = &D_80ABE364;
    this->actor.colChkInfo.health = 2;
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderItems);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 20.0f);
    this->unk_1CA = 0;
    this->unk_1D0 = 0;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.shape.rot.y = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = -0.4f;
    this->unk_1CC = 0;
    this->unk_1CE = 2;
    this->unk_1D4 = 0xFF;
    this->unk_1D8 = 0;
    this->actor.velocity.y = 0.0f;
    this->unk_1E8 = 0.0f;
    this->unk_1E0 = 0.25f;
    if (this->actor.params == 0) {
        // New initialisation
        osSyncPrintf("ニュウ イニシャル[ %d ] ！！\n", this->actor.params);
        this->actor.colChkInfo.mass = 0;
        this->unk_1D4 = 0;
        this->unk_1D8 = 0xFF;
        this->unk_1E0 = 1.0f;
        func_80ABCDBC(this);
    } else {
        // Dummy new initialisation
        osSyncPrintf("ダミーニュウ イニシャル[ %d ] ！！\n", this->actor.params);
        osSyncPrintf("En_Ny_actor_move2[ %x ] ！！\n", func_80ABDBF8);
        this->actor.colChkInfo.mass = 0xFF;
        this->collider.base.type = 9;
        this->actor.update = func_80ABDBF8;
    }
}

void EnNy_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnNy* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80ABCD40(EnNy* this) {
    f32 tmpf1 = (this->actor.waterY > 0.0f) ? 0.7f : 1.0f;

    this->unk_1E8 = 2.8f * tmpf1;
}

void func_80ABCD84(EnNy* this) {
    this->actionFunc = func_80ABCE50;
}

void func_80ABCD94(EnNy* this) {
    this->unk_1DC = 0x14;
    this->actionFunc = func_80ABCE90;
}

void func_80ABCDAC(EnNy* this) {
    this->actionFunc = func_80ABCEEC;
}

void func_80ABCDBC(EnNy* this) {
    this->unk_1F4 = 0.0f;
    func_80ABCD40(this);
    this->unk_1DC = 0xB4;
    this->actionFunc = func_80ABCF4C;
}

void func_80ABCDFC(EnNy* this) {
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_NYU_HIT_STOP);
    this->actionFunc = func_80ABD05C;
    this->unk_1E8 = 0.0f;
}

void func_80ABCE38(EnNy* this) {
    this->unk_1DC = 0x3C;
    this->actionFunc = func_80ABD11C;
}

void func_80ABCE50(EnNy* this, GlobalContext* globalCtx) {
    if (this->actor.xyzDistFromLinkSq <= 25600.0f) {
        func_80ABCD94(this);
    }
}

void func_80ABCE90(EnNy* this, GlobalContext* globalCtx) {
    s32 sp1C = this->unk_1D4;
    s32 sp18 = this->unk_1D8;

    sp18 += 0x40;
    sp1C -= 0x40;
    if (sp18 >= 0xFF) {
        sp18 = 0xFF;
        sp1C = 0;
        func_80ABCDAC(this);
    }
    this->unk_1D4 = sp1C;
    this->unk_1D8 = sp18;
}

void func_80ABCEEC(EnNy* this, GlobalContext* globalCtx) {
    f32 sp1C = this->unk_1E0;

    sp1C += 2.0f;
    if (sp1C >= 1.0f) {
        sp1C = 1.0f;
        func_80ABCDBC(this);
    }
    this->unk_1E0 = sp1C;
}

void func_80ABCF4C(EnNy* this, GlobalContext* globalCtx) {
    f32 sp2C;
    s32 tmp;

    if (!(this->unk_1F0 < this->actor.waterY)) {
        func_8002F974(&this->actor, NA_SE_EN_NYU_MOVE - SFX_FLAG);
    }

    func_80ABCD40(this);
    tmp = this->unk_1DC;
    this->unk_1DC = tmp - 1;
    if ((tmp <= 0) || (this->unk_1CC != 0)) {
        func_80ABCDFC(this);
        return;
    }

    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 0xA, this->unk_1F4, 0);
    Math_SmoothScaleMaxF(&this->unk_1F4, 2000.0f, 1.0f, 100.0f);
    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    sp2C = Math_atan2f(this->actor.yDistFromLink, this->actor.xzDistFromLink);
    this->actor.speedXZ = fabsf(cosf(sp2C) * this->unk_1E8);
    if (this->unk_1F0 < this->actor.waterY) {
        this->unk_1EC = sinf(sp2C) * this->unk_1E8;
    }
}

void func_80ABD05C(EnNy* this, GlobalContext* globalCtx) {
    f32 sp1C = this->unk_1E0;

    sp1C -= 2.0f;
    if (sp1C <= 0.25f) {
        sp1C = 0.25f;
        if ((this->actor.bgCheckFlags & 2) != 0) {
            if (!(this->unk_1F0 < this->actor.waterY)) {
                sp1C = 0.25f;
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_DODO_M_GND);
            }
            this->actor.bgCheckFlags &= ~2;
            this->actor.speedXZ = 0.0f;
            this->actor.posRot.rot.y = this->actor.shape.rot.y;
            sp1C = 0.25f;
            func_80ABCE38(this);
            sp1C = 0.25f;
        }
    }
    this->unk_1E0 = sp1C;
}

void func_80ABD11C(EnNy* this, GlobalContext* globalCtx) {
    s32 sp1C = this->unk_1D4;
    s32 sp18 = this->unk_1D8;

    sp1C += 0x40;
    sp18 -= 0x40;

    if (sp1C >= 0xFF) {
        sp1C = 0xFF;
        sp18 = 0;
        if (this->unk_1DC != 0) {
            this->unk_1DC--;
        } else {
            func_80ABCD84(this);
        }
    }
    this->unk_1D4 = sp1C;
    this->unk_1D8 = sp18;
}

s32 func_80ABD190(EnNy* this, GlobalContext* globalCtx) {
    u8 sp3F;
    Vec3f sp30;

    sp3F = 0;
    this->unk_1CC = 0;

    if (this->collider.base.atFlags & 4) {
        this->collider.base.atFlags &= ~4;
        this->unk_1CC = 1;
        this->actor.posRot.rot.y = this->actor.yawTowardsLink;
        this->actor.speedXZ = -4.0f;
        return 0;
    }

    if (this->collider.base.atFlags & 2) {
        this->collider.base.atFlags &= ~2;
        this->unk_1CC = 1;
        return 0;
    }

    if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= ~2;
        sp30.x = this->collider.list[0].body.bumper.unk_06.x;
        sp30.y = this->collider.list[0].body.bumper.unk_06.y;
        sp30.z = this->collider.list[0].body.bumper.unk_06.z;

        if ((this->unk_1E0 == 0.25f) && (this->unk_1D4 == 0xFF)) {
            switch (this->actor.colChkInfo.damageEffect) {
                case 14:
                    sp3F = 1;
                case 15:
                    Actor_ApplyDamage(&this->actor);
                    func_8003426C(&this->actor, 0x4000, 0xFF, 0x2000, 0x50);
                    break;

                case 1:
                    Actor_ApplyDamage(&this->actor);
                    func_8003426C(&this->actor, 0x4000, 0xFF, 0x2000, 0x50);
                    break;

                case 2:
                    this->unk_1CA = 4;
                    Actor_ApplyDamage(&this->actor);
                    func_8003426C(&this->actor, 0x4000, 0xFF, 0x2000, 0x50);
                    break;
            }
        }

        this->unk_1DC = 0;
        if (this->actor.colChkInfo.health == 0) {
            this->actor.shape.unk_14 = 0;
            this->actor.flags &= ~1;
            this->unk_1D0 = sp3F;
            func_80032C7C(globalCtx, &this->actor);
            return 1;
        }

        func_80029CA4(globalCtx, 0, &sp30);
        return 0;
    }

    return 0;
}

void func_80ABD3B8(EnNy* this, f32 arg1, f32 arg2) {
    if (this->unk_1E8 == 0.0f) {
        this->actor.gravity = -0.4f;
        return;
    }

    if (!(arg1 < this->actor.waterY)) {
        this->actor.gravity = -0.4f;
        return;
    }

    if (arg2 < this->actor.waterY) {
        this->actor.gravity = 0;
        if (this->unk_1EC < this->actor.velocity.y) {
            this->actor.velocity.y -= 0.4f;
            if (this->actor.velocity.y < this->unk_1EC) {
                this->actor.velocity.y = this->unk_1EC;
            }
        } else if (this->actor.velocity.y < this->unk_1EC) {
            this->actor.velocity.y += 0.4f;
            if (this->unk_1EC < this->actor.velocity.y) {
                this->actor.velocity.y = this->unk_1EC;
            }
        }
    }
}

void EnNy_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnNy* this = THIS;
    f32 temp_f20;
    f32 temp_f22;
    s32 i;

    this->unk_1C8++;
    temp_f20 = this->unk_1E0 - 0.25f;
    if (this->unk_1CA != 0) {
        this->unk_1CA--;
    }

    Actor_SetHeight(&this->actor, 0.0f);
    Actor_SetScale(&this->actor, 0.01f);
    this->collider.list->dim.scale = (1.33f * temp_f20) + 1.0f;
    this->actor.shape.rot.x += (s16)(this->unk_1E8 * 1000.0f);
    temp_f22 = (24.0f * temp_f20) + 12.0f;
    func_80ABD3B8(this, temp_f22 + 10.0f, temp_f22 - 10.0f);
    Actor_MoveForward(&this->actor);
    Math_ApproxF(&this->unk_1E4, this->unk_1E8, 0.1f);
    this->actionFunc(this, globalCtx);
    this->actor.pos4.y = this->actor.pos4.y - temp_f22;
    this->actor.posRot.pos.y = this->actor.posRot.pos.y - temp_f22;
    func_8002E4B4(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 7);
    this->unk_1F0 = temp_f22;
    this->actor.posRot.pos.y += temp_f22;
    if (func_80ABD190(this, globalCtx) != 0) {
        for (i = 0; i < 8; i++) {
            this->unk_1F8[i].x = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.x;
            this->unk_1F8[i].y = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.y;
            this->unk_1F8[i].z = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.z;
        }

        this->unk_1C8 = 0;
        this->actor.update = func_80ABDBB8;
        this->actor.draw = func_80ABE040;
        this->actionFunc = func_80ABD728;
        return;
    }

    if (this->unk_1E0 > 0.25f) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80ABD728(EnNy* this, GlobalContext* globalCtx) {
    s32 i;
    s16 tmp;
    Vec3f sp74;
    Vec3f sp68 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp5C = { 0.0f, 0.1f, 0.0f };

    if (this->unk_1C8 < 2) {
        return;
    }

    if (this->actor.waterY > 0.0f) {
        for (i = 0; i < 10; i++) {
            sp74.x = Math_Rand_CenteredFloat(30.0f) + this->actor.posRot.pos.x;
            sp74.y = Math_Rand_CenteredFloat(30.0f) + this->actor.posRot.pos.y;
            sp74.z = Math_Rand_CenteredFloat(30.0f) + this->actor.posRot.pos.z;
            tmp = Math_Rand_S16Offset(80, 100);
            func_80029618(globalCtx, &sp74, &sp68, &sp5C, tmp, 0x19, 0, 1);
        }

        for (i = 0; i < 20; i++) {
            sp74.x = Math_Rand_CenteredFloat(30.0f) + this->actor.posRot.pos.x;
            sp74.y = Math_Rand_CenteredFloat(30.0f) + this->actor.posRot.pos.y;
            sp74.z = Math_Rand_CenteredFloat(30.0f) + this->actor.posRot.pos.z;
            func_800293E4(globalCtx, &sp74, 10.0f, 10.0f, 30.0f, 0.25f);
        }
    }

    for (i = 0; i < 8; i++) {
        this->unk_258[i].x = Math_Rand_CenteredFloat(10.0f);
        this->unk_258[i].z = Math_Rand_CenteredFloat(10.0f);
        this->unk_258[i].y = Math_Rand_ZeroFloat(4.0f) + 4.0f;
    }

    this->unk_1C8 = 0;
    if (this->unk_1D0 == 0) {
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.posRot.pos, 0xA0);
    } else {
        Item_DropCollectible(globalCtx, &this->actor.posRot.pos, 8);
    }

    Audio_PlayActorSound2(&this->actor, NA_SE_EN_NYU_DEAD);
    this->actionFunc = func_80ABD9AC;
}

void func_80ABD9AC(EnNy* this, GlobalContext* globalCtx) {
    s32 i;

    if (this->actor.waterY > 0.0f) {
        for (i = 0; i < 8; i++) {
            this->unk_1F8[i].x += this->unk_258[i].x;
            this->unk_1F8[i].y += this->unk_258[i].y;
            this->unk_1F8[i].z += this->unk_258[i].z;
            Math_ApproxF(&this->unk_258[i].x, 0.0f, 0.1f);
            Math_ApproxF(&this->unk_258[i].y, -1.0f, 0.4f);
            Math_ApproxF(&this->unk_258[i].z, 0.0f, 0.1f);
        }

        if (this->unk_1C8 >= 0x1F) {
            Actor_Kill(&this->actor);
            return;
        }
    } else {
        for (i = 0; i < 8; i++) {
            this->unk_1F8[i].x += this->unk_258[i].x;
            this->unk_1F8[i].y += this->unk_258[i].y;
            this->unk_1F8[i].z += this->unk_258[i].z;
            Math_ApproxF(&this->unk_258[i].x, 0.0f, 0.15f);
            Math_ApproxF(&this->unk_258[i].y, -1.0f, 0.6f);
            Math_ApproxF(&this->unk_258[i].z, 0.0f, 0.15f);
        }

        if (this->unk_1C8 >= 0x10) {
            Actor_Kill(&this->actor);
            return;
        }
    }
}

void func_80ABDBB8(Actor* thisx, GlobalContext* globalCtx) {
    EnNy* this = THIS;

    this->unk_1C8++;
    DECR(this->unk_1CA);
    this->actionFunc(this, globalCtx);
}

void func_80ABDBF8(Actor* thisx, GlobalContext* globalCtx) {
    EnNy* this = THIS;
    s32 pad;
    f32 sp3C;
    s32 pad2;

    sp3C = this->unk_1E0 - 0.25f;
    this->unk_1C8++;
    Actor_SetHeight(&this->actor, 0.0f);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.pos4.y = this->actor.pos4.y - ((24.0f * sp3C) + 12.0f);
    this->actor.posRot.pos.y = this->actor.posRot.pos.y - ((24.0f * sp3C) + 12.0f);
    func_8002E4B4(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 7);
    this->unk_1F0 = ((24.0f * sp3C) + 12.0f);
    this->actor.posRot.pos.y += ((24.0f * sp3C) + 12.0f);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_MoveForward(&this->actor);
    Math_ApproxF(&this->unk_1E4, this->unk_1E8, 0.1f);
    if (globalCtx) {};
}

static Vec3f D_80ABE3A8[] = {
    { 5.0f, 0.0f, 0.0f },
    { -5.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 5.0f },
    { 0.0f, 0.0f, -5.0f },
};

void EnNy_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnNy* this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_ny.c", 837);

    func_800628A4(0, &this->collider);
    func_8002ED80(&this->actor, globalCtx, 1);
    func_80093D84(globalCtx->state.gfxCtx);

    gSPMatrix(oGfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_ny.c", 845),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(oGfxCtx->polyXlu.p++);
    gDPSetRenderMode(oGfxCtx->polyXlu.p++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);
    gDPSetEnvColor(oGfxCtx->polyXlu.p++, 0, 0, 0, this->unk_1D8);
    gSPDisplayList(oGfxCtx->polyXlu.p++, D_06001EA8);
    gDPPipeSync(oGfxCtx->polyXlu.p++);
    gDPSetRenderMode(oGfxCtx->polyXlu.p++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2);
    gDPSetEnvColor(oGfxCtx->polyXlu.p++, 0, 0, 0, this->unk_1D4);
    gSPDisplayList(oGfxCtx->polyXlu.p++, D_06001DD0);

    if (this->unk_1E0 > 0.25f) {
        Matrix_Scale(this->unk_1E0, this->unk_1E0, this->unk_1E0, MTXMODE_APPLY);
        func_8002EBCC(&this->actor, globalCtx, 1);
        func_80093D18(globalCtx->state.gfxCtx);
        gSPMatrix(oGfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_ny.c", 868),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(oGfxCtx->polyOpa.p++, D_06001FC8);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_ny.c", 872);

    if (this->unk_1CA != 0) {
        Vec3f sp3C;
        s32 pad2;
        s16 sp36 = this->unk_1CA - 1;

        this->actor.dmgEffectTimer++;
        if (sp36 == 0) {
            sp3C.x = (this->actor.posRot.pos.x + D_80ABE3A8[sp36 & 3].x) + Math_Rand_CenteredFloat(5.0f);
            sp3C.y = (this->actor.posRot.pos.y + D_80ABE3A8[sp36 & 3].y) + Math_Rand_CenteredFloat(5.0f);
            sp3C.z = (this->actor.posRot.pos.z + D_80ABE3A8[sp36 & 3].z) + Math_Rand_CenteredFloat(5.0f);
            func_8002A4D4(globalCtx, &this->actor, &sp3C, 0x64, 0, 0, -1);
        }
    }
}

void func_80ABE040(Actor* thisx, GlobalContext* globalCtx) {
    EnNy* this = THIS;
    s32 pad;
    f32 tmpf1;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_ny.c", 900);

    func_80093D18(globalCtx->state.gfxCtx);

    gDPSetEnvColor(oGfxCtx->polyOpa.p++, 0, 0, 0, 255);
    gDPSetRenderMode(oGfxCtx->polyOpa.p++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
    gDPPipeSync(oGfxCtx->polyOpa.p++);

    for (i = 0; i < 8; i++) {
        if (this->unk_1C8 < (i + 0x16)) {
            Matrix_Translate(this->unk_1F8[i].x, this->unk_1F8[i].y, this->unk_1F8[i].z, MTXMODE_NEW);
            tmpf1 = (this->actor.scale.x * 0.4f) * (1.0f + (i * 0.04f));
            Matrix_Scale(tmpf1, tmpf1, tmpf1, MTXMODE_APPLY);
            gSPMatrix(oGfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_ny.c", 912),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(oGfxCtx->polyOpa.p++, D_06001DD0);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_ny.c", 919);

    if (this->unk_1CA != 0) {
        Vec3f sp7C;
        s32 pad2[2];
        s16 tmp = this->unk_1CA - 1;

        this->actor.dmgEffectTimer++;
        if (!(tmp & 1)) {
            sp7C.x = (this->actor.posRot.pos.x + D_80ABE3A8[tmp & 3].x) + Math_Rand_CenteredFloat(5.0f);
            sp7C.y = (this->actor.posRot.pos.y + D_80ABE3A8[tmp & 3].y) + Math_Rand_CenteredFloat(5.0f);
            sp7C.z = (this->actor.posRot.pos.z + D_80ABE3A8[tmp & 3].z) + Math_Rand_CenteredFloat(5.0f);
            func_8002A4D4(globalCtx, &this->actor, &sp7C, 0x64, 0, 0, -1);
        }
    }
}
