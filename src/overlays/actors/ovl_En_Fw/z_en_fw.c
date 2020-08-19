#include "z_en_fw.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"

#define FLAGS 0x00000215

#define THIS ((EnFw*)thisx)

void EnFw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFw_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A1F664(EnFw* this, Vec3f* a, Vec3f* b, Vec3f* c, u8 arg4, f32 arg5, f32 arg6);

void func_80A1F708(EnFw* this);
void func_80A1EC70(EnFw* this, GlobalContext* globalCtx);
void func_80A1F2A8(EnFw* this, GlobalContext* globalCtx);
void func_80A1ECD4(EnFw* this, GlobalContext* globalCtx);
void func_80A1F39C(EnFw* this, GlobalContext* globalCtx);
void func_80A1F814(EnFw* this, GlobalContext* globalCtx);

extern SkeletonHeader D_06007C30;
extern AnimationHeader D_06006CF8;
extern Gfx D_06007928[];
extern Gfx D_06007938[];

const ActorInit En_Fw_InitVars = {
    ACTOR_EN_FW,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_FW,
    sizeof(EnFw),
    (ActorFunc)EnFw_Init,
    (ActorFunc)EnFw_Destroy,
    (ActorFunc)EnFw_Update,
    (ActorFunc)EnFw_Draw,
};

static ColliderJntSphItemInit sJntSphItemsInit[1] = {
    {
        { 0x00, { 0x00000000, 0x00, 0x04 }, { 0xFFCFFFFE, 0x00, 0x00 }, 0x00, 0x05, 0x01 },
        { 2, { { 1200, 0, 0 }, 16 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_UNK6, 0x11, 0x09, 0x39, 0x10, COLSHAPE_JNTSPH },
    1,
    sJntSphItemsInit,
};

static CollisionCheckInfoInit2 D_80A1FB94 = { 0x08, 0x0002, 0x0019, 0x0019, 0xFF };

static struct_80034EC0_Entry D_80A1FBA0[] = { { 0x06006CF8, 0.0f, 0.0f, -1.0f, 0x03, 0.0f },
                                              { 0x06007CD0, 1.0f, 0.0f, -1.0f, 0x03, -8.0f },
                                              { 0x06007DC8, 1.0f, 0.0f, -1.0f, 0x01, -8.0f } };

s32 func_80A1E5A0(EnFw* this, s32 arg1, f32 arg2) {
    if (!(this->actor.bgCheckFlags & 1) || (this->actor.velocity.y > 0.0f)) {
        return 0;
    }

    Audio_PlayActorSound2(&this->actor, NA_SE_EN_DODO_M_GND);
    this->unk_204--;
    if (this->unk_204 <= 0) {
        if (this->unk_204 == 0) {
            this->unk_204 = 0;
            this->actor.velocity.y = 0.0f;
            return 1;
        }

        this->unk_204 = arg1;
    }

    this->actor.velocity.y = arg2;
    this->actor.velocity.y *= ((f32)this->unk_204 / arg1);

    return 1;
}

s32 func_80A1E668(EnFw* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    CollisionPoly* sp48;
    u32 sp44;
    Vec3f sp38;

    if (this->actor.xzDistFromLink > 300.0f) {
        return 0;
    }

    if (ABS((s16)((f32)this->actor.yawTowardsLink - this->actor.shape.rot.y)) >= 0x1C71) {
        return 0;
    }

    if (func_8003DE84(&globalCtx->colCtx, &this->actor.posRot.pos, &player->actor.posRot.pos, &sp38, &sp48, 1, 0, 0, 1,
                      &sp44)) {
        return 0;
    }

    return 1;
}

Vec3f* func_80A1E760(Vec3f* arg0, EnFw* this, f32 arg2, s16 arg3) {
    s16 rot;
    Vec3f sp28;

    rot = Math_Vec3f_Yaw(&this->actor.attachedA->initPosRot.pos, &this->actor.posRot.pos) + (arg3 * 0x1554);
    sp28.x = (Math_Sins(rot) * arg2) + this->actor.attachedA->initPosRot.pos.x;
    sp28.z = (Math_Coss(rot) * arg2) + this->actor.attachedA->initPosRot.pos.z;

    sp28.x -= this->actor.posRot.pos.x;
    sp28.z -= this->actor.posRot.pos.z;

    *arg0 = sp28;
    return arg0;
}

s32 func_80A1E838(EnFw* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & 2) {
        ColliderJntSphItem* item = &this->collider.list[0];
        if ((item->body.acHitItem->toucher.flags & 0x80) != 0) {
            this->unk_200 = 1;
        } else {
            this->unk_200 = 0;
        }

        this->collider.base.acFlags &= ~2;
        if (Actor_ApplyDamage(&this->actor) <= 0) {
            Actor* refActor = this->actor.attachedA;
            if (refActor->colChkInfo.health < 9) {
                func_80032C7C(globalCtx, &this->actor);
                this->actor.attachedA->colChkInfo.health = 0;
            } else {
                refActor->colChkInfo.health -= 8;
            }

            this->unk_212 = 0;
        }
        return 1;
    }
    return 0;
}

s32 func_80A1E8F8(EnFw* this, u8 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    Vec3f sp9C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp90 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp84 = { 0.0f, 0.0f, 0.0f };
    s16 rand;
    s32 i;

    sp9C = this->actor.posRot.pos;
    sp9C.y = this->actor.groundY + 2.0f;
    rand = (Math_Rand_ZeroOne() - 0.5f) * 65536.0f;
    for (i = arg4; i >= 0; i--, rand += (s16)(0x10000 / arg4)) {
        sp84.x = (Math_Rand_ZeroOne() - 0.5f) * arg6;
        sp84.y = arg7;
        sp84.z = (Math_Rand_ZeroOne() - 0.5f) * arg6;
        sp9C.x = (Math_Sins(rand) * arg5) + this->actor.posRot.pos.x;
        sp9C.z = (Math_Coss(rand) * arg5) + this->actor.posRot.pos.z;
        func_80A1F664(this, &sp9C, &sp90, &sp84, arg1, arg2, arg3);
    }

    return 0;
}

void EnFw_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFw* this = THIS;

    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06007C30, NULL, this->limbDrawTable, this->transitionDrawTable,
                     11);
    func_80034EC0(&this->skelAnime, D_80A1FBA0, 0);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 20.0f);
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderItems);
    func_80061EFC(&this->actor.colChkInfo, DamageTable_Get(0x10), &D_80A1FB94);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_202 = -this->actor.params;
    this->actionFunc = func_80A1EC70;
    this->actor.gravity = -1.0f;
}

void EnFw_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFw* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80A1EC70(EnFw* this, GlobalContext* globalCtx) {
    if (func_80A1E5A0(this, 3, 8.0f) && (this->unk_204 == 0)) {
        this->unk_212 = Math_Rand_S16Offset(0x12C, 0x96);
        this->actionFunc = func_80A1ECD4;
    }
}

void func_80A1ECD4(EnFw* this, GlobalContext* globalCtx) {
    s32 pad;

    Math_SmoothScaleMaxMinF(&this->skelAnime.animPlaybackSpeed, 1.0f, 0.1f, 1.0f, 0.0f);
    if (this->skelAnime.animCurrentSeg == &D_06006CF8) {
        if (func_800A56C8(&this->skelAnime, this->skelAnime.animFrameCount) == 0) {
            this->unk_218 = Math_Vec3f_DistXYZ(&this->actor.posRot.pos, &this->actor.attachedA->posRot.pos);
            func_80034EC0(&this->skelAnime, D_80A1FBA0, 2);
            return;
        }
    } else {
        if ((this->unk_208 == 0) && (this->unk_20A == 0) && func_80A1E838(this, globalCtx)) {
            if (this->actor.attachedA->colChkInfo.health > 0) {
                if (this->unk_200 == 0) {
                    this->actor.velocity.y = 6.0f;
                }

                Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLAME_MAN_DAMAGE);
                this->unk_208 = 0x14;
            } else {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLAME_MAN_DAMAGE);
                this->unk_20A = 6;
            }
            this->actor.speedXZ = 0.0f;
        }

        if (this->unk_20A != 0) {
            this->skelAnime.animPlaybackSpeed = 0.0f;
            Math_SmoothScaleMaxMinF(&this->actor.scale.x, 0.024999999f, 0.08f, 0.6f, 0.0f);
            Actor_SetScale(&this->actor, this->actor.scale.x);
            if (this->actor.dmgEffectTimer == 0) {
                func_8003426C(&this->actor, 0x4000, 0xC8, 0, this->unk_20A);
                this->unk_20A--;
            }

            if (this->unk_20A == 0) {
                EnBom* b00m = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->unk_1F4.x,
                                                  this->unk_1F4.y, this->unk_1F4.z, 0, 0, 0x600, 0);
                if (b00m != NULL) {
                    b00m->timer = 0;
                }

                b00m = (EnBom*)this->actor.attachedA;
                b00m->actor.params |= 0x4000;
                Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.posRot.pos, 0xA0);
                Actor_Kill(&this->actor);
            }
        } else {
            if (!(this->actor.bgCheckFlags & 1) || (this->actor.velocity.y > 0.0f)) {
                func_8003426C(&this->actor, 0x4000, 0xC8, 0, this->unk_208);
                return;
            }

            if (this->unk_208 != 0) {
                this->unk_208--;
            }

            if (((200.0f - this->unk_218) < 0.9f) && (DECR(this->unk_212) == 0)) {
                this->actor.speedXZ = 0.0f;
                this->actionFunc = func_80A1F2A8;
                return;
            }

            Math_SmoothScaleMaxMinF(&this->unk_218, 200.0f, 0.3f, 100.0f, 0.0f);
            if (this->unk_214 != 0) {
                f32 saved;
                f32 tmp2;
                f32 arg2;

                Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 0.1f, 1.0f, 0.0f);
                arg2 = (s16)(this->actor.posRot.rot.y ^ 0x8000);
                saved = this->actor.shape.rot.y;
                tmp2 = Math_SmoothScaleMaxMinF(&saved, arg2, 0.1f, 10000.0f, 0.0f);
                this->actor.shape.rot.y = saved;
                if (tmp2 > 5460.0f) {
                    return;
                }

                this->unk_214 = 0;
            } else {
                Vec3f sp48;

                func_80A1E760(&sp48, this, this->unk_218, this->unk_202);
                Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, Math_atan2f(sp48.x, sp48.z) * 10430.378f, 4, 0xFA0,
                                        1);
            }

            this->actor.posRot.rot = this->actor.shape.rot;
            if ((this->unk_20E == 0) && func_80A1E668(this, globalCtx)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLAME_MAN_SURP);
                this->unk_210 = 8;
                this->unk_20E = 8;
            }

            if (this->unk_20E != 0) {
                if (DECR(this->unk_210) == 0) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLAME_MAN_SLIDE);
                    this->unk_210 = 4;
                }

                Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 0.1f, 1.0f, 0.0f);
                this->skelAnime.animPlaybackSpeed = 0.0f;
                func_80A1E8F8(this, 8, 0.159999996424f, 0.2f, 3, 8.0f, 20.0f,
                              ((Math_Rand_ZeroOne() - 0.5f) * 0.2f) + 0.3f);
                this->unk_20E--;
                if (this->unk_20E == 0) {
                    this->unk_214 = 1;
                    this->unk_202 = -this->unk_202;
                }
            } else {
                Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 6.0f, 0.1f, 1.0f, 0.0f);
                if (((s16)this->skelAnime.animCurrentFrame == 1) || ((s16)this->skelAnime.animCurrentFrame == 4)) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLAME_MAN_RUN);
                    func_80A1E8F8(this, 8, 0.159999996424f, 0.10000000149f, 1, 0.0f, 20.0f, 0.0f);
                }
            }
        }
    }
}

void func_80A1F2A8(EnFw* this, GlobalContext* globalCtx) {
    s16 sp36 = Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.attachedA->initPosRot.pos);

    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, sp36, 4, 0xFA0, 1);
    if (ABS(sp36 - this->actor.shape.rot.y) < 101) {
        this->actor.posRot.rot = this->actor.shape.rot;
        this->actor.velocity.y = 14.0f;
        this->actor.initPosRot.pos = this->actor.posRot.pos;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL_JUMP);
        func_80034EC0(&this->skelAnime, D_80A1FBA0, 1);
        this->actionFunc = func_80A1F39C;
    }
}

void func_80A1F39C(EnFw* this, GlobalContext* globalCtx) {
    if ((this->actor.bgCheckFlags & 1) && (this->actor.velocity.y <= 0.0f)) {
        this->actor.attachedA->params |= 0x8000;
        Actor_Kill(&this->actor);
    } else {
        Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.x, this->actor.attachedA->initPosRot.pos.x, 0.6f, 8.0f, 0.0f);
        Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.z, this->actor.attachedA->initPosRot.pos.z, 0.6f, 8.0f, 0.0f);
    }
}

void EnFw_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFw* this = THIS;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if ((this->actor.flags & 0x2000) != 0x2000) {
        Actor_MoveForward(&this->actor);
        func_8002E4B4(globalCtx, &this->actor, 10.0f, 20.0f, 0.0f, 5);
        this->actionFunc(this, globalCtx);
        if ((this->unk_208 == 0) && (this->unk_20A == 0) && (this->actionFunc == func_80A1ECD4)) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

s32 func_80A1F52C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return 0;
}

void func_80A1F544(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnFw* this = THIS;
    Vec3f sp18 = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == 2) {
        Matrix_MultVec3f(&sp18, &this->unk_1F4);
    }

    if (limbIndex == 3) {
        Matrix_MultVec3f(&sp18, &this->actor.posRot2.pos);
    }

    func_800628A4(limbIndex, &this->collider);
}

void EnFw_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFw* this = THIS;

    func_80A1F708(this);
    Matrix_Push();
    func_80A1F814(this, globalCtx);
    Matrix_Pull();
    func_80093D18(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80A1F52C, func_80A1F544, &this->actor);
}

void func_80A1F664(EnFw* this, Vec3f* a, Vec3f* b, Vec3f* c, u8 arg4, f32 arg5, f32 arg6) {
    EnFwStruct1* ptr = &this->unk_2A0[0];
    s16 i;

    for (i = 0; i < 20; i++, ptr++) {
        if (ptr->unk_00 != 1) {
            ptr->unk_04 = arg5;
            ptr->unk_08 = arg6;
            ptr->unk_02 = ptr->unk_01 = arg4;
            ptr->unk_00 = 1;
            ptr->unk_14 = *a;
            ptr->unk_2C = *c;
            ptr->unk_20 = *b;
            return;
        }
    }
}

void func_80A1F708(EnFw* this) {
    EnFwStruct1* ptr = &this->unk_2A0[0];
    s16 i;
    f32 tmpf1;

    for (i = 0; i < 20; i++, ptr++) {
        if (ptr->unk_00 != 0) {
            ptr->unk_01--;
            if (ptr->unk_01 == 0) {
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

void func_80A1F814(EnFw* this, GlobalContext* globalCtx) {
    static UNK_TYPE D_80A1FC18[] = { 0x040539B0, 0x040535B0, 0x040531B0, 0x04052DB0,
                                     0x040529B0, 0x040525B0, 0x040521B0, 0x04051DB0 };
    EnFwStruct1* ptr = &this->unk_2A0[0];
    u8 flag;
    s16 i;
    s16 idx;
    s16 idx2;

    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fw.c", 1191);
    flag = 0;
    do {
        func_80093D84(globalCtx->state.gfxCtx);
    } while (0);

    for (i = 0; i < 20; i++, ptr++) {
        if (ptr->unk_00 != 0) {
            if (flag == 0) {
                gfxCtx->polyXlu.p = Gfx_CallSetupDL(gfxCtx->polyXlu.p, 0);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_06007928);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 100, 60, 20, 0);
                flag = 1;
            }

            idx2 = ptr->unk_01 * (255.0f / ptr->unk_02);

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 170, 130, 90, idx2);
            gDPPipeSync(gfxCtx->polyXlu.p++);
            Matrix_Translate(ptr->unk_14.x, ptr->unk_14.y, ptr->unk_14.z, 0);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_Scale(ptr->unk_04, ptr->unk_04, 1.0f, MTXMODE_APPLY);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_fw.c", 1229),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            idx = ptr->unk_01 * (8.0f / ptr->unk_02);

            gSPSegment(gfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A1FC18[idx]));
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06007938);
        }
    }
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fw.c", 1243);
}
