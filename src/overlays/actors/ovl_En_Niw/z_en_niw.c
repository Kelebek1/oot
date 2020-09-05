/*
 * File: z_en_niw.c
 * Overlay: ovl_En_Niw
 * Description: Cucco
 */

#include "z_en_niw.h"
#include "vt.h"

#define FLAGS 0x00800010

#define THIS ((EnNiw*)thisx)

void EnNiw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AB8168(EnNiw* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4);
void func_80AB627C(EnNiw* this, GlobalContext* globalCtx);
void func_80AB6450(EnNiw* this, GlobalContext* globalCtx);
void func_80AB6324(EnNiw* this, GlobalContext* globalCtx);
void func_80AB6570(EnNiw* this, GlobalContext* globalCtx);
void func_80AB6BF8(EnNiw* this, GlobalContext* globalCtx);
void func_80AB7290(EnNiw* this, GlobalContext* globalCtx);
void func_80AB63A8(EnNiw* this, GlobalContext* globalCtx);
void func_80AB6A38(EnNiw* this, GlobalContext* globalCtx);
void func_80AB6EB4(EnNiw* this, GlobalContext* globalCtx);
void func_80AB6D08(EnNiw* this, GlobalContext* globalCtx);
void func_80AB7328(EnNiw* this, GlobalContext* globalCtx);
void func_80AB840C(EnNiw* this, GlobalContext* globalCtx);
void func_80AB8258(EnNiw* this, GlobalContext* globalCtx);
void func_80AB70F8(EnNiw* this, GlobalContext* globalCtx);
void func_80AB7204(EnNiw* this, GlobalContext* globalCtx);
void func_80AB714C(EnNiw* this, GlobalContext* globalCtx);

extern SkeletonHeader D_06002530;
extern AnimationHeader D_060000E8;
extern Gfx D_060023B0[];
extern Gfx D_06002428[];

static s16 D_80AB85E0 = 0;

const ActorInit En_Niw_InitVars = {
    ACTOR_EN_NIW,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_NIW,
    sizeof(EnNiw),
    (ActorFunc)EnNiw_Init,
    (ActorFunc)EnNiw_Destroy,
    (ActorFunc)EnNiw_Update,
    (ActorFunc)EnNiw_Draw,
};

static f32 D_80AB8604[] = { 5000.0f, -5000.0f };

static f32 D_80AB860C[] = { 5000.0f, 3000.0f, 4000.0f };

static Vec3f D_80AB8618[] = {
    { -1697.0f, 80.0f, 870.0f }, { 57.0f, 320.0f, -673.0f }, { 796.0f, 80.0f, 1639.0f }, { 1417.0f, 465.0f, 169.0f },
    { -60.0f, 0.0f, -46.0f },    { -247.0f, 80.0f, 854.0f }, { 1079.0f, 80.0f, -47.0f },
};

static s16 D_80AB866C[] = { 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 };

static u8 D_80AB867C = 0;
static u8 D_80AB8680 = 0;

static ColliderCylinderInit sCylinderInit2 = {
    { COLTYPE_UNK5, 0x00, 0x09, 0x01, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x01, 0x01 },
    { 15, 25, 4, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit1 = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 15, 25, 4, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(unk_1F, 6, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, 63536, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 0, ICHAIN_STOP),
};

void EnNiw_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnNiw* this = THIS;
    s32 i;
    s32 pad;

    if (this->actor.params < 0) {
        this->actor.params = 0;
    }

    if (this->actor.params == 0xB) {
        if (D_80AB867C != 0) {
            Actor_Kill(&this->actor);
            osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ もういてる原 Ver.1 ☆☆☆☆☆ \n" VT_RST);
            return;
        }
        D_80AB867C = 1;
        this->actor.room = -1;
    }

    if (this->actor.params == 0xC) {
        if (D_80AB8680 != 0) {
            Actor_Kill(&this->actor);
            osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ もういてる原 Ver.2 ☆☆☆☆☆ \n" VT_RST);
            return;
        }
        D_80AB8680 = 1;
        this->actor.room = -1;
    }

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.flags |= 1;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 25.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06002530, &D_060000E8, this->limbDrawTable,
                     this->transitionDrawTable, 16);
    if (globalCtx->sceneNum == SCENE_SPOT01) {
        for (i = 0; i < 7; i++) {
            if (fabsf(this->actor.posRot.pos.x - D_80AB8618[i].x) < 40.0f) {
                if (fabsf(this->actor.posRot.pos.z - D_80AB8618[i].z) < 40.0f) {
                    this->unk_2AA = i;
                    // Regular cucco index
                    osSyncPrintf(VT_FGCOL(YELLOW) " 通常鶏index %d\n" VT_RST, this->unk_2AA);
                    if (gSaveContext.infTable[25] & D_80AB866C[i]) {
                        this->actor.posRot.pos.x = 300.0f;
                        this->actor.posRot.pos.y = 100.0f;
                        this->actor.posRot.pos.z = 1530.0f;
                        this->actor.params = 0;
                    }
                }
            }
        }
    }

    Math_Vec3f_Copy(&this->unk_2AC, &this->actor.posRot.pos);
    Math_Vec3f_Copy(&this->unk_2B8, &this->actor.posRot.pos);
    this->unk_304 = 10.0f;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_2A4 = (s16)Math_Rand_ZeroFloat(3.99f) + 5;
    if (this->unk_2A4 < 0) {
        this->unk_2A4 = 1;
    }

    switch (this->actor.params) {
        case 2:
            if (gSaveContext.nightFlag == 0) {
                Actor_Kill(&this->actor);
            }
            break;
        case 1:
            if (gSaveContext.eventChkInf[1] & 0x10) {
                Actor_Kill(&this->actor);
            }
            break;
        case 3:
            if (!(gSaveContext.eventChkInf[1] & 0x10)) {
                Actor_Kill(&this->actor);
            }
            break;
        case 5:
            if (gSaveContext.eventChkInf[1] & 0x100) {
                Actor_Kill(&this->actor);
            }
            break;
        case 7:
            if (!(gSaveContext.eventChkInf[1] & 0x100)) {
                Actor_Kill(&this->actor);
            }
            break;
        case 13:
            this->actor.gravity = 0.0f;
        case 14:
            this->actor.colChkInfo.mass = 0;
            this->actor.flags &= ~1;
            break;
        case 4:
            this->actor.gravity = 0.0f;
            break;
    }

    Collider_InitCylinder(globalCtx, &this->collider);
    switch (this->actor.params) {
        case 10:
            this->actor.colChkInfo.mass = 0xFF;
        case 13:
        case 14:
            Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit1);
            if ((globalCtx->sceneNum == SCENE_LINK_HOME) && !(gSaveContext.eventChkInf[1] & 0x4000)) {
                Actor_Kill(&this->actor);
            }
            break;

        default:
            Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit2);
            break;
    }

    // Who we dealin' with here?
    osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ どんな奴？ ☆☆☆☆☆ %d\n" VT_RST, this->actor.params);
    osSyncPrintf("\n\n");
    this->actionFunc = func_80AB627C;
}

void EnNiw_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnNiw* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80AB5BF8(EnNiw* this, GlobalContext* globalCtx, s16 arg2) {
    f32 tmpf1 = 1.0f;

    if (this->actor.params == 0xD) {
        tmpf1 = 2.0f;
    }

    if (this->unk_254 == 0) {
        if (arg2 == 0) {
            this->unk_26C[0] = 0.0f;
        } else {
            this->unk_26C[0] = -10000.0f * tmpf1;
        }
        this->unk_298++;
        this->unk_254 = 3;
        if ((this->unk_298 & 1) == 0) {
            this->unk_26C[0] = 0.0f;
            if (arg2 == 0) {
                this->unk_254 = Math_Rand_ZeroFloat(30.0f);
            }
        }
    }

    if (this->unk_256 == 0) {
        this->unk_29C++;
        this->unk_29C &= 1;
        switch (arg2) {
            case 0:
                this->unk_26C[2] = 0.0f;
                this->unk_26C[1] = 0.0f;
                break;
            case 1:
                this->unk_256 = 3;
                this->unk_26C[2] = 7000.0f * tmpf1;
                this->unk_26C[1] = 7000.0f * tmpf1;
                if (this->unk_29C == 0) {
                    this->unk_26C[2] = 0.0f;
                    this->unk_26C[1] = 0.0f;
                }
                break;
            case 2:
                this->unk_256 = 2;
                this->unk_26C[1] = this->unk_26C[2] = -10000.0f;
                this->unk_26C[7] = this->unk_26C[5] = 25000.0f;
                this->unk_26C[8] = this->unk_26C[6] = 6000.0f;
                if (this->unk_29C == 0) {
                    this->unk_26C[5] = this->unk_26C[7] = 8000.0f;
                }
                break;
            case 3:
                this->unk_256 = 2;
                this->unk_26C[5] = 10000.0f;
                this->unk_26C[7] = 10000.0f;
                if (this->unk_29C == 0) {
                    this->unk_26C[5] = 3000.0f;
                    this->unk_26C[7] = 3000.0f;
                }
                break;
            case 4:
                this->unk_254 = 5;
                break;
            case 5:
                this->unk_256 = 5;
                this->unk_26C[5] = 14000.0f;
                this->unk_26C[7] = 14000.0f;
                if (this->unk_29C == 0) {
                    this->unk_26C[5] = 10000.0f;
                    this->unk_26C[7] = 10000.0f;
                }
                break;
        }
    }

    if (this->unk_26C[9] != this->unk_2E0) {
        Math_SmoothScaleMaxF(&this->unk_2E0, this->unk_26C[9], 0.5f, 4000.0f);
    }
    if (this->unk_26C[0] != this->unk_2DC) {
        Math_SmoothScaleMaxF(&this->unk_2DC, this->unk_26C[0], 0.5f, 4000.0f);
    }
    if (this->unk_26C[2] != this->unk_2C4) {
        Math_SmoothScaleMaxF(&this->unk_2C4, this->unk_26C[2], 0.8f, 7000.0f);
    }
    if (this->unk_26C[7] != this->unk_2C8) {
        Math_SmoothScaleMaxF(&this->unk_2C8, this->unk_26C[7], 0.8f, 7000.0f);
    }
    if (this->unk_26C[8] != this->unk_2CC) {
        Math_SmoothScaleMaxF(&this->unk_2CC, this->unk_26C[8], 0.8f, 7000.0f);
    }
    if (this->unk_26C[1] != this->unk_2D0) {
        Math_SmoothScaleMaxF(&this->unk_2D0, this->unk_26C[1], 0.8f, 7000.0f);
    }
    if (this->unk_26C[5] != this->unk_2D4) {
        Math_SmoothScaleMaxF(&this->unk_2D4, this->unk_26C[5], 0.8f, 7000.0f);
    }
    if (this->unk_26C[6] != this->unk_2D8) {
        Math_SmoothScaleMaxF(&this->unk_2D8, this->unk_26C[6], 0.8f, 7000.0f);
    }
}

void func_80AB5FA0(EnNiw* this, GlobalContext* globalCtx) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    s32 pad;
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    if (this->unk_25C == 0) {
        if (this->unk_296 < 7) {
            sp54 = globalCtx->view.lookAt.x - globalCtx->view.eye.x;
            sp50 = globalCtx->view.lookAt.y - globalCtx->view.eye.y;
            sp4C = globalCtx->view.lookAt.z - globalCtx->view.eye.z;
            sp40 = ((Math_Rand_ZeroOne() - 0.5f) * sp54) + globalCtx->view.eye.x;
            sp44 = Math_Rand_CenteredFloat(0.3f) + ((globalCtx->view.eye.y + 50.0f) + (sp50 * 0.5f));
            sp3C = ((Math_Rand_ZeroOne() - 0.5f) * sp4C) + globalCtx->view.eye.z;
            if (Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_ATTACK_NIW, sp40, sp44, sp3C,
                                   0, 0, 0, 0) != NULL) {
                this->unk_296++;
                this->unk_25C = 10;
            } else {
                osSyncPrintf("\n\n");
                // Couldn't spawn
                osSyncPrintf(VT_FGCOL(GREEN) " ☆☆☆☆☆ 発生できず  ☆☆☆☆☆ \n" VT_RST);
            }
        }
    }
}

void func_80AB6100(EnNiw* this, GlobalContext* globalCtx, s32 arg2) {
    f32 phi_f2;
    f32 tmpf1;
    const s32 idx = 1;

    if (this->unk_25A == 0) {
        this->unk_25A = 3;
        if (this->actor.bgCheckFlags & 1) {
            this->actor.velocity.y = 3.5f;
        }
    }

    if (this->unk_258 == 0) {
        this->unk_2A0++;
        this->unk_2A0 &= 1;
        this->unk_258 = 5;
    }

    if (this->unk_2A0 == 0) {
        phi_f2 = D_80AB860C[arg2];
    } else {
        phi_f2 = -D_80AB860C[arg2];
    }

    if (&D_80AB860C[idx] == &D_80AB860C[arg2]) {
        if ((this->unk_25E == 0) || (this->actor.bgCheckFlags & 8)) {
            this->unk_25E = 0x96;
            if (this->unk_268 == 0) {
                this->unk_268 = 0x46;
                this->unk_2E4 = this->actor.yawTowardsLink;
            }
        }
    }

    tmpf1 = this->unk_2E4 + phi_f2;
    Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, tmpf1, 3, this->unk_2FC, 0);
    Math_SmoothScaleMaxF(&this->unk_2FC, 3000.0f, 1.0f, 500.0f);
    func_80AB5BF8(this, globalCtx, 5);
}

void func_80AB627C(EnNiw* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_060000E8, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_060000E8.genericHeader),
                         0, -10.0f);

    switch (this->actor.params) {
        case 4:
            this->actionFunc = func_80AB6450;
            break;
        case 13:
            this->actionFunc = func_80AB6324;
            break;
        default:
            this->actionFunc = func_80AB6570;
            break;
    }
}

void func_80AB6324(EnNiw* this, GlobalContext* globalCtx) {
    if (this->unk_308 != 0) {
        this->actor.velocity.y = Math_Rand_ZeroFloat(2.0f) + 4.0f;
        this->actor.speedXZ = Math_Rand_ZeroFloat(2.0f) + 3.0f;
        this->actionFunc = func_80AB63A8;
    }
    func_80AB5BF8(this, globalCtx, 1);
}

void func_80AB63A8(EnNiw* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 1) {
        if (this->actor.velocity.y < 0.0f) {
            this->unk_29E = 0;

            this->unk_2AC.x = this->unk_2B8.x = this->actor.posRot.pos.x;
            this->unk_2AC.y = this->unk_2B8.y = this->actor.posRot.pos.y;
            this->unk_2AC.z = this->unk_2B8.z = this->actor.posRot.pos.z;

            this->unk_2FC = this->unk_300 = 0.0f;
            this->actor.speedXZ = 0.0f;
            this->unk_26C[5] = this->unk_26C[6] = this->unk_26C[8] = 0.0f;
            this->unk_26C[7] = 0.0f;
            this->unk_25A = this->unk_29E;
            this->unk_25C = this->unk_29E;
            this->actionFunc = func_80AB6570;
            return;
        }
    }
    func_80AB5BF8(this, globalCtx, 2);
}

void func_80AB6450(EnNiw* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((this->actor.xzDistFromLink < 30.0f) && (fabsf(this->actor.posRot.pos.y - player->actor.posRot.pos.y) < 5.0f)) {
        this->unk_25E = 0x64;
        this->actor.gravity = -2.0f;
        this->actionFunc = func_80AB7290;
    } else if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.gravity = -2.0f;
        Audio_PlayActorSound2(&this->actor, 0x2813);
        this->unk_260 = 30;
        this->unk_2E8 = 0;
        this->unk_25A = 30;
        this->actor.flags &= ~1;
        this->actionFunc = func_80AB6BF8;
        this->actor.speedXZ = 0.0f;
    } else {
        func_8002F434(&this->actor, globalCtx, 0, 25.0f, 10.0f);
        func_80AB5BF8(this, globalCtx, 1);
    }
}

void func_80AB6570(EnNiw* this, GlobalContext* globalCtx) {
    s32 pad[2];
    f32 sp34 = Math_Rand_CenteredFloat(100.0f);
    f32 sp30 = Math_Rand_CenteredFloat(100.0f);
    s16 sp2E;

    if (this->actor.params != 10) {
        if (Actor_HasParent(&this->actor, globalCtx) != 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M);
            this->unk_260 = 30;
            this->unk_2E8 = 0;
            this->unk_25A = 30;
            this->actor.flags &= ~1;
            this->actionFunc = func_80AB6BF8;
            this->actor.speedXZ = 0.0f;
            return;
        }
        func_8002F580(&this->actor, globalCtx);
    } else if (this->unk_2E8 != 0) {
        this->unk_2A6 = 1;
        if (this->unk_264 == 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M);
            this->unk_264 = 100;
        }
        this->unk_2A0 = Math_Rand_ZeroFloat(1.99f);
        this->actor.speedXZ = 4;
        this->unk_300 = 0;
        this->unk_2FC = 0;
        this->actionFunc = func_80AB6A38;
        return;
    }

    sp2E = 0;
    if (this->unk_25C != 0) {
        if (Math_Rand_ZeroFloat(3.99f) < 1.0f) {
            this->unk_2E6++;
            this->unk_2E6 &= 1;
        }
        Math_SmoothScaleMaxF(&this->unk_26C[9], D_80AB8604[this->unk_2E6], 0.5f, 4000.0f);
    }

    if (this->unk_25C == 0) {
        if (this->unk_25A == 0) {
            this->unk_29E++;
            if (this->unk_29E >= 8) {
                this->unk_25C = Math_Rand_ZeroFloat(30.0f);
                this->unk_29E = Math_Rand_ZeroFloat(3.99f);
                if ((this->actor.params != 10) && (this->actor.params != 8)) {
                    if (sp34 < 0) {
                        sp34 -= 100.0f;
                    } else {
                        sp34 += 100.0f;
                    }

                    if (sp30 < 0) {
                        sp30 -= 100.0f;
                    } else {
                        sp30 += 100.0f;
                    }
                } else {
                    sp34 = Math_Rand_CenteredFloat(30.0f);
                    sp30 = Math_Rand_CenteredFloat(30.0f);

                    if (sp34 < 0) {
                        sp34 -= 20.0f;
                    } else {
                        sp34 += 20.0f;
                    }

                    if (sp30 < 0) {
                        sp30 -= 20.0f;
                    } else {
                        sp30 += 20.0f;
                    }
                }
                this->unk_2B8.x = this->unk_2AC.x + sp34;
                this->unk_2B8.z = this->unk_2AC.z + sp30;
            } else {
                this->unk_25A = 4;
                if (this->actor.bgCheckFlags & 1) {
                    this->actor.speedXZ = 0.0f;
                    this->actor.velocity.y = 3.5f;
                }
            }
        }
    }

    if (this->unk_25A != 0) {
        f32 tmpf1;
        f32 tmpf2;

        Math_SmoothDownscaleMaxF(&this->unk_26C[9], 0.5f, 4000.0f);
        sp2E = 1;
        Math_SmoothScaleMaxF(&this->actor.posRot.pos.x, this->unk_2B8.x, 1.0f, this->unk_2FC);
        Math_SmoothScaleMaxF(&this->actor.posRot.pos.z, this->unk_2B8.z, 1.0f, this->unk_2FC);
        Math_SmoothScaleMaxF(&this->unk_2FC, 3.0f, 1.0f, 0.3f);

        tmpf1 = this->unk_2B8.x - this->actor.posRot.pos.x;
        tmpf2 = this->unk_2B8.z - this->actor.posRot.pos.z;
        if (fabsf(tmpf1) < 10.0f) {
            tmpf1 = 0;
        }
        if (fabsf(tmpf2) < 10.0f) {
            tmpf2 = 0;
        }
        if ((tmpf1 == 0.0f) && (tmpf2 == 0.0f)) {
            this->unk_25A = 0;
            this->unk_29E = 7;
        }
        Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, Math_atan2f(tmpf1, tmpf2) * 10430.378f, 3, this->unk_300, 0);
        Math_SmoothScaleMaxF(&this->unk_300, 10000.0f, 1.0f, 1000.0f);
    }

    func_80AB5BF8(this, globalCtx, sp2E);
}

void func_80AB6A38(EnNiw* this, GlobalContext* globalCtx) {
    Path* path;
    Vec3s* point;
    f32 sp1C;
    f32 sp18;
    s16 idx = this->unk_2E8 - 1;

    if (this->unk_2E8 == 0) {
        this->unk_29E = 0;
        this->unk_2AC.x = this->unk_2B8.x = this->actor.posRot.pos.x;
        this->unk_2AC.y = this->unk_2B8.y = this->actor.posRot.pos.y;
        this->unk_2AC.z = this->unk_2B8.z = this->actor.posRot.pos.z;
        this->unk_25A = this->unk_29E;
        this->unk_25C = this->unk_29E;
        this->unk_300 = 0.0f;
        this->unk_2FC = 0.0f;
        this->actor.speedXZ = 0.0f;
        this->unk_26C[5] = this->unk_26C[6] = this->unk_26C[8] = 0.0f;
        this->unk_26C[7] = 0.0f;
        this->actionFunc = func_80AB627C;
        return;
    }
    path = &globalCtx->setupPathList[idx];
    point = (Vec3s*)SEGMENTED_TO_VIRTUAL(path->points);
    point += this->unk_2EA;

    sp1C = point->x - this->actor.posRot.pos.x;
    sp18 = point->z - this->actor.posRot.pos.z;
    this->unk_2E4 = Math_atan2f(sp1C, sp18) * 10430.378f;
    func_80AB6100(this, globalCtx, 2);
    if ((fabsf(sp1C) < 30.0f) && (fabsf(sp18) < 30.0f)) {
        this->unk_2EA++;
        if (this->unk_2EA >= this->unk_2EC) {
            this->unk_2EA = 0;
        }
    }
    func_80AB5BF8(this, globalCtx, 2);
}

void func_80AB6BF8(EnNiw* this, GlobalContext* globalCtx) {
    if (this->unk_25A == 0) {
        this->unk_2A6 = 2;
        this->unk_25A = 0xA;
    }

    this->actor.shape.rot.x = Math_Rand_CenteredFloat(5000.0f);
    this->actor.shape.rot.y = Math_Rand_CenteredFloat(5000.0f);
    this->actor.shape.rot.z = Math_Rand_CenteredFloat(5000.0f);
    if (Actor_HasNoParent(&this->actor, globalCtx)) {
        if (this->actor.params == 13) {
            this->unk_260 = 0;
            this->unk_2A6 = 1;
            this->actionFunc = func_80AB6EB4;
            this->actor.velocity.y = 4.0f;
            return;
        }
        this->actor.shape.rot.z = 0;
        this->actor.shape.rot.x = this->actor.shape.rot.y = this->actor.shape.rot.z;
        this->actor.flags |= 1;
        this->actionFunc = func_80AB6D08;
    }
    func_80AB5BF8(this, globalCtx, 2);
}

void func_80AB6D08(EnNiw* this, GlobalContext* globalCtx) {
    if (this->unk_2E8 == 0) {
        if (this->actor.bgCheckFlags & 1) {
            if (this->actor.params == 14) {
                this->unk_29E = 0;
                this->unk_2AC.x = this->unk_2B8.x = this->actor.posRot.pos.x;
                this->unk_2AC.y = this->unk_2B8.y = this->actor.posRot.pos.y;
                this->unk_2AC.z = this->unk_2B8.z = this->actor.posRot.pos.z;
                this->unk_25A = this->unk_29E;
                this->unk_25C = this->unk_29E;
                this->unk_300 = 0.0f;
                this->unk_2FC = 0.0f;
                this->actor.speedXZ = 0.0f;
                this->unk_26C[5] = this->unk_26C[6] = this->unk_26C[8] = 0.0f;
                this->unk_26C[7] = 0.0f;
                this->actionFunc = func_80AB627C;
                return;
            }
            this->unk_2E8 = 1;
            this->unk_25C = 0x50;
            this->actor.speedXZ = 0.0f;
            this->actor.velocity.y = 4.0f;
        } else {
            return;
        }
    } else {
        if (this->actor.bgCheckFlags & 1) {
            this->unk_260 = 0;
            this->actor.velocity.y = 4.0f;
            this->unk_2A6 = 1;
        }
        if (this->unk_25C == 0) {
            this->unk_25E = 0x64;
            this->unk_25A = 0;
            this->unk_2E8 = 0;
            this->actionFunc = func_80AB7290;
            return;
        }
    }

    if (Actor_HasParent(&this->actor, globalCtx)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M);
        this->unk_260 = 30;
        this->unk_2E8 = 0;
        this->unk_25A = 30;
        this->actor.flags &= ~1;
        this->actionFunc = func_80AB6BF8;
        this->actor.speedXZ = 0.0f;
        return;
    }

    if (this->unk_25C >= 6) {
        func_8002F580(&this->actor, globalCtx);
    }
    func_80AB5BF8(this, globalCtx, 2);
}

void func_80AB6EB4(EnNiw* this, GlobalContext* globalCtx) {
    if (this->actor.posRot.pos.y > 400.0f) {
        Actor_Kill(&this->actor);
    }
    func_80AB5BF8(this, globalCtx, 2);
}

void func_80AB6F04(EnNiw* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    if (this->unk_2A8 != 0) {
        func_80AB5FA0(this, globalCtx);
    }

    this->actor.speedXZ = 2.0f;
    if ((this->actor.bgCheckFlags & 0x20) != 0) {
        this->actor.gravity = 0.0f;
        if (this->actor.waterY > 15.0f) {
            this->actor.posRot.pos.y += 2.0f;
        }

        if (this->unk_25A == 0) {
            this->unk_25A = 0x1E;
            Math_Vec3f_Copy(&sp2C, &this->actor.posRot.pos);
            sp2C.y += this->actor.waterY;
            func_80029444(globalCtx, &sp2C, 0x64, 0x1F4, 0x1E);
        }

        if (this->actor.bgCheckFlags & 8) {
            this->actor.velocity.y = 10.0f;
            this->actor.speedXZ = 1.0f;
        }
    } else {
        this->actor.gravity = -2.0f;
        if (this->actor.bgCheckFlags & 8) {
            this->actor.velocity.y = 10.0f;
            this->actor.speedXZ = 1.0f;
            this->actor.gravity = 0.0f;
        } else {
            this->actor.speedXZ = 4.0f;
        }

        if (this->actor.bgCheckFlags & 1) {
            this->actor.gravity = -2.0f;
            this->unk_25E = 0x64;
            this->unk_25A = 0;
            this->actor.velocity.y = 0.0f;
            if (this->unk_2A8 == 0) {
                this->actionFunc = func_80AB7290;
            } else {
                this->actionFunc = func_80AB7204;
            }
        }
    }
    func_80AB5BF8(this, globalCtx, 2);
}

void func_80AB70A0(EnNiw* this, GlobalContext* globalCtx) {
    func_800800F8(globalCtx, 0x8F2, -0x63, &this->actor, 0);
    this->unk_25C = 100;
    this->unk_2A2 = 1;
    this->actionFunc = func_80AB70F8;
}

void func_80AB70F8(EnNiw* this, GlobalContext* globalCtx) {
    this->unk_260 = 100;
    if (this->unk_25C == 0) {
        this->unk_25C = 0x3C;
        this->unk_254 = 0xA;
        this->unk_2A2 = 4;
        this->actionFunc = func_80AB714C;
    }
    func_80AB5BF8(this, globalCtx, this->unk_2A2);
}

void func_80AB714C(EnNiw* this, GlobalContext* globalCtx) {
    this->unk_260 = 0x64;
    if (this->unk_25C == 0x28) {
        this->unk_26C[0] = 10000.0f;
        this->unk_26C[7] = 14000.0f;
        this->unk_26C[5] = 14000.0f;
        this->unk_26C[6] = 0.0f;
        this->unk_26C[8] = 0.0f;
        this->unk_26C[1] = 0.0f;
        this->unk_26C[2] = 0.0f;
        this->unk_254 = 10;
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M);
    }

    if (this->unk_25C == 0) {
        this->unk_266 = 10;
        this->unk_2E4 = this->actor.yawTowardsLink;
        this->actor.flags &= ~1;
        this->actionFunc = func_80AB7204;
    }

    func_80AB5BF8(this, globalCtx, this->unk_2A2);
}

void func_80AB7204(EnNiw* this, GlobalContext* globalCtx) {
    func_80AB5FA0(this, globalCtx);
    if (this->unk_266 < 2) {
        if (this->unk_266 == 1) {
            this->actor.speedXZ = 3.0f;
            this->unk_2A0 = Math_Rand_ZeroFloat(1.99f);
            this->unk_25A = 0;
            this->unk_258 = this->unk_25A;
            this->unk_256 = this->unk_25A;
            this->unk_254 = this->unk_25A;
        } else {
            func_80AB6100(this, globalCtx, 1);
        }
    }
}

void func_80AB7290(EnNiw* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_060000E8, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_060000E8.genericHeader),
                         0, -10.0f);
    this->unk_2A0 = Math_Rand_ZeroFloat(1.99f);
    this->actionFunc = func_80AB7328;
    this->actor.speedXZ = 4.0f;
}

void func_80AB7328(EnNiw* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->unk_25E == 0) {
        this->unk_29E = 0;
        this->unk_2AC.x = this->unk_2B8.x = this->actor.posRot.pos.x;
        this->unk_2AC.y = this->unk_2B8.y = this->actor.posRot.pos.y;
        this->unk_2AC.z = this->unk_2B8.z = this->actor.posRot.pos.z;
        this->unk_25A = this->unk_29E;
        this->unk_25C = this->unk_29E;
        this->unk_300 = 0.0f;
        this->unk_2FC = 0.0f;
        this->actor.speedXZ = 0.0f;
        this->unk_26C[8] = 0.0f;
        this->unk_26C[6] = 0.0f;
        this->unk_26C[5] = 0.0f;
        this->unk_26C[7] = 0.0f;
        if (this->actor.params == 4) {
            this->actor.params = 0;
        }
        this->actionFunc = func_80AB627C;
        return;
    }

    this->unk_2E4 = Math_atan2f(this->actor.posRot.pos.x - player->actor.posRot.pos.x,
                                this->actor.posRot.pos.z - player->actor.posRot.pos.z) *
                    10430.378f;
    func_80AB6100(this, globalCtx, 0);
    func_80AB5BF8(this, globalCtx, 2);
}

void func_80AB7420(EnNiw* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 1) {
        this->unk_2A4 = (s16)Math_Rand_ZeroFloat(3.99f) + 5;
        this->actionFunc = func_80AB627C;
    }
}

void func_80AB747C(EnNiw* this, GlobalContext* globalCtx) {
    if ((this->unk_2A8 == 0) && (this->actor.params != 0xA) && (this->actionFunc != func_80AB6450) &&
        (this->collider.base.acFlags & 2)) {
        this->collider.base.acFlags &= ~2;
        this->unk_260 = 30;
        if (this->unk_2A4 > 0) {
            if (D_80AB85E0 == 0) {
                this->unk_2A4--;
            }
        }
        this->unk_2A6 = 1;
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M);
        this->unk_25E = 100;
        this->unk_2E8 = 0;
        this->actionFunc = func_80AB7290;
    }
}

void EnNiw_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnNiw* this = THIS;
    s32 pad2;
    Player* player = PLAYER;
    s16 pad16;
    s16 spD0;
    Vec3f spC4 = { 0.0f, 0.0f, 0.0f };
    Vec3f spB8 = { 0.0f, 0.0f, 0.0f };
    Vec3f spAC;
    Vec3f spA0;
    Vec3f sp94;
    s32 pad3;
    f32 sp8C;
    f32 tmpf1;
    f32 tmpf2;
    f32 tmpf3;
    f32 tmpf4;
    f32 sp78;
    f32 tmpf5;
    s16 i;
    s32 pad[11];

    this->unk_294++;
    if (this->actionFunc != func_80AB6570) {
        this->unk_26C[9] = 0.0f;
    }

    if (this->unk_2A6 != 0) {
        spD0 = 20;
        if (this->unk_2A6 == 2) {
            spD0 = 4;
        }

        for (i = 0; i < spD0; i++) {
            spAC.x = Math_Rand_CenteredFloat(10.0f) + this->actor.posRot.pos.x;
            spAC.y = Math_Rand_CenteredFloat(10.0f) + (this->actor.posRot.pos.y + this->unk_304);
            spAC.z = Math_Rand_CenteredFloat(10.0f) + this->actor.posRot.pos.z;
            sp8C = Math_Rand_ZeroFloat(6.0f) + 6;
            if ((this->unk_2A6 == 2) && (this->unk_304 != 0)) {
                spAC.y += 10.0f;
            }
            if (this->unk_304 == 0) {
                sp8C = Math_Rand_ZeroFloat(2.0f) + 2;
            }
            spA0.x = Math_Rand_CenteredFloat(3.0f);
            spA0.y = (Math_Rand_ZeroFloat(2.0f) * 0.5f) + 2;
            spA0.z = Math_Rand_CenteredFloat(3.0f);
            sp94.y = -0.15f;
            sp94.z = sp94.x = 0.0f;
            func_80AB8168(this, &spAC, &spA0, &sp94, sp8C);
        }
        this->unk_2A6 = 0;
    }

    func_80AB8258(this, globalCtx);

    DECR(this->unk_254);
    DECR(this->unk_256);
    DECR(this->unk_258);
    DECR(this->unk_25A);
    DECR(this->unk_25C);
    DECR(this->unk_266);
    DECR(this->unk_25E);
    DECR(this->unk_260);
    DECR(this->unk_262);
    DECR(this->unk_264);
    DECR(this->unk_268);
    DECR(this->unk_26A);

    this->actor.shape.rot = this->actor.posRot.rot;
    this->actor.shape.unk_10 = 15.0f;
    this->actionFunc(this, globalCtx);
    Actor_SetHeight(&this->actor, this->unk_304);
    Actor_MoveForward(&this->actor);
    if ((this->actionFunc != func_80AB6EB4) && (this->actionFunc != func_80AB6450) &&
        (globalCtx->sceneNum != SCENE_SPOT03)) {
        func_8002E4B4(globalCtx, &this->actor, 20, 20, 60.0f, 0x1F);
    }
    if (globalCtx->sceneNum == SCENE_SPOT03) {
        func_8002E4B4(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 0x1D);
    }

    if ((this->actor.groundY <= -32000.0f) || (this->actor.groundY >= 32000.0f)) {
        // Above? Below?
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 上下？ ☆☆☆☆☆ %f\n" VT_RST, this->actor.groundY);
        tmpf1 = globalCtx->view.lookAt.x - globalCtx->view.eye.x;
        tmpf2 = globalCtx->view.lookAt.y - globalCtx->view.eye.y;
        tmpf3 = globalCtx->view.lookAt.z - globalCtx->view.eye.z;
        sp78 = tmpf2 / sqrtf(SQ(tmpf1) + SQ(tmpf2) + SQ(tmpf3));
        // Out of bounds X
        osSyncPrintf(VT_FGCOL(RED) "☆☆☆☆☆ 範囲外Ｘ！ ☆☆☆☆☆ %f\n" VT_RST, this->actor.posRot.pos.x);
        // Out of bounds Y
        osSyncPrintf(VT_FGCOL(RED) "☆☆☆☆☆ 範囲外Ｙ！ ☆☆☆☆☆ %f\n" VT_RST, this->actor.posRot.pos.y);
        // Out of bounds Z
        osSyncPrintf(VT_FGCOL(RED) "☆☆☆☆☆ 範囲外Ｚ！ ☆☆☆☆☆ %f\n" VT_RST, this->actor.posRot.pos.z);
        // Init X
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ セットＸ！ ☆☆☆☆☆ %f\n" VT_RST, this->actor.initPosRot.pos.x);
        // Init Y
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ セットＹ！ ☆☆☆☆☆ %f\n" VT_RST, this->actor.initPosRot.pos.y);
        // Init Z
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ セットＺ！ ☆☆☆☆☆ %f\n" VT_RST, this->actor.initPosRot.pos.z);
        this->actor.posRot.pos.x = this->actor.initPosRot.pos.x;
        this->actor.posRot.pos.z = this->actor.initPosRot.pos.z;
        tmpf5 = sp78 * 160.0f;
        this->actor.posRot.pos.y = (this->actor.initPosRot.pos.y + globalCtx->view.eye.y) + tmpf5;
        if (this->actor.posRot.pos.y < this->actor.initPosRot.pos.y) {
            this->actor.posRot.pos.y = this->actor.initPosRot.pos.y + 300.0f;
        }
        // Post-fix X
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ 修整後Ｘ！ ☆☆☆☆☆ %f\n" VT_RST, this->actor.posRot.pos.x);
        // Post-fix Y
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ 修整後Ｙ！ ☆☆☆☆☆ %f\n" VT_RST, this->actor.posRot.pos.y);
        // Post-fix Z
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ 修整後Ｚ！ ☆☆☆☆☆ %f\n" VT_RST, this->actor.posRot.pos.z);
        osSyncPrintf("\n\n");
        this->actor.gravity = -2.0f;
        this->actor.speedXZ = 0.0f;
        Math_Vec3f_Copy(&this->unk_2AC, &this->actor.initPosRot.pos);
        Math_Vec3f_Copy(&this->unk_2B8, &this->actor.initPosRot.pos);
        this->unk_2A2 = 0;
        this->unk_300 = 0.0f;
        this->unk_2FC = 0.0f;
        this->unk_2F0 = this->unk_2F4 = this->unk_2F8 = 0.0f;
        this->unk_2D0 = this->unk_2D4 = this->unk_2D8 = 0.0f;
        this->unk_2C4 = this->unk_2C8 = this->unk_2CC = 0.0f;
        this->unk_2DC = 0.0f;
        this->unk_2E0 = 0.0f;
        this->unk_2A0 = this->unk_2A2;
        this->unk_29E = this->unk_2A2;
        this->unk_2A6 = this->unk_2A2;
        this->unk_298 = this->unk_2A2;
        this->unk_294 = this->unk_2A2;
        this->unk_2A8 = this->unk_2A2;

        for (i = 0; i < 10; i++) {
            this->unk_26C[i] = 0;
        }

        this->unk_2A8 = 0;
        this->actionFunc = func_80AB7420;
        return;
    }

    if ((this->actor.bgCheckFlags & 0x20) && (this->actor.waterY > 15.0f) && (this->actionFunc != func_80AB6F04) &&
        (this->actor.params != 13) && (this->actor.params != 14) && (this->actor.params != 10)) {
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
        Math_Vec3f_Copy(&spAC, &this->actor.posRot.pos);
        spAC.y += this->actor.waterY;
        this->unk_25A = 30;
        func_8002949C(globalCtx, &spAC, 0, 0, 0, 0x190);
        this->unk_25C = 0;
        osSyncPrintf("\n\n");
        // In water
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ ぶくぶく ☆☆☆☆☆ \n" VT_RST);
        osSyncPrintf("\n\n");
        this->actionFunc = func_80AB6F04;
        return;
    }

    if ((D_80AB85E0 == 0) && (this->unk_2A4 <= 0) && (this->actor.params != 13) && (this->actor.params != 14) &&
        (this->actor.params != 10)) {
        this->unk_25E = 100;
        if (this->actor.xzDistFromLink > 10.0f) {
            D_80AB85E0 = 1;
            this->unk_29E = 0;
            this->unk_2AC.x = this->unk_2B8.x = this->actor.posRot.pos.x;
            this->unk_2AC.y = this->unk_2B8.y = this->actor.posRot.pos.y;
            this->unk_2AC.z = this->unk_2B8.z = this->actor.posRot.pos.z;
            this->actor.speedXZ = 0.0f;
            this->unk_2FC = 0.0f;
            this->unk_300 = 0.0f;
            this->unk_26C[7] = 0.0f;
            this->unk_26C[5] = 0.0f;
            this->unk_26C[6] = 0.0f;
            this->unk_26C[8] = 0.0f;
            this->unk_260 = 10000;
            this->unk_2A8 = 1;
            this->actionFunc = func_80AB70A0;
            this->unk_25A = this->unk_29E;
            this->unk_25C = this->unk_29E;
            return;
        }
    }

    tmpf4 = (100 / 5.0f);
    tmpf4 *= 20;
    if ((this->unk_2A8 != 0) && (this->actor.xyzDistFromLinkSq < tmpf4) && (player->invincibilityTimer == 0)) {
        func_8002F6D4(globalCtx, &this->actor, 2, this->actor.posRot.rot.y, 0.0f, 0x10);
    }

    // Required to match
    if (0) {};

    func_80AB747C(this, globalCtx);
    if ((this->unk_262 == 0) && (this->actionFunc == func_80AB6BF8)) {
        this->unk_262 = 7;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_DEKU_WAKEUP);
    }

    if (this->unk_260 == 0) {
        if (this->actionFunc != func_80AB6570) {
            this->unk_260 = 30;
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_A);
        } else {
            this->unk_260 = 300;
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_N);
        }
    }

    if (this->unk_2A8 == 0) {
        Collider_CylinderUpdate(&this->actor, &this->collider);
        if ((this->actor.params != 10) && (this->actor.params != 13) && (this->actor.params != 14) &&
            (this->actor.params != 4)) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        if ((this->actionFunc != func_80AB6BF8) && (this->actionFunc != func_80AB6D08) &&
            (this->actionFunc != func_80AB6324) && (this->actionFunc != func_80AB63A8) &&
            (this->actionFunc != func_80AB6450)) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

s32 EnNiw_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnNiw* this = THIS;
    Vec3f sp0 = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == 13) {
        rot->y += (s16)this->unk_2DC;
    }
    if (limbIndex == 15) {
        rot->y += (s16)this->unk_2E0;
    }
    if (limbIndex == 11) {
        rot->x += (s16)this->unk_2D8;
        rot->y += (s16)this->unk_2D4;
        rot->z += (s16)this->unk_2D0;
    }
    if (limbIndex == 7) {
        rot->x += (s16)this->unk_2CC;
        rot->y += (s16)this->unk_2C8;
        rot->z += (s16)this->unk_2C4;
    }
    return 0;
}

void EnNiw_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnNiw* this = THIS;
    Vec3f sp38 = { 0.15f, 0.15f, 0.15f };
    s32 pad;

    func_80093D18(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnNiw_OverrideLimbDraw, NULL, &this->actor);
    if (this->actionFunc == func_80AB6450) {
        func_80033C30(&this->actor.posRot.pos, &sp38, 0xFF, globalCtx);
    }
    func_80AB840C(this, globalCtx);
}

void func_80AB8168(EnNiw* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4) {
    s32 pad;
    EnNiwStruct1* ptr = this->unk_358;
    s16 i;

    for (i = 0; i < 20; i++, ptr++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 1;
            ptr->unk_04 = *arg1;
            ptr->unk_10 = *arg2;
            ptr->unk_1C = *arg3;
            ptr->unk_34 = 0;
            ptr->unk_2C = arg4 / 1000.0f;
            ptr->unk_28 = (s16)Math_Rand_ZeroFloat(20.0f) + 0x28;
            ptr->unk_2A = Math_Rand_ZeroFloat(1000.0f);
            break;
        }
    }
}

void func_80AB8258(EnNiw* this, GlobalContext* globalCtx) {
    EnNiwStruct1* ptr = this->unk_358;
    s16 i;

    for (i = 0; i < 20; i++, ptr++) {
        if (ptr->unk_00 != 0) {
            ptr->unk_04.x += ptr->unk_10.x;
            ptr->unk_04.y += ptr->unk_10.y;
            ptr->unk_04.z += ptr->unk_10.z;

            ptr->unk_34++;

            ptr->unk_10.x += ptr->unk_1C.x;
            ptr->unk_10.y += ptr->unk_1C.y;
            ptr->unk_10.z += ptr->unk_1C.z;

            if (ptr->unk_00 == 1) {
                ptr->unk_2A++;
                Math_SmoothScaleMaxF(&ptr->unk_10.x, 0.0f, 1.0f, 0.05f);
                Math_SmoothScaleMaxF(&ptr->unk_10.z, 0.0f, 1.0f, 0.05f);
                if (ptr->unk_10.y < -0.5f) {
                    ptr->unk_10.y = -0.5f;
                }

                ptr->unk_30 = (Math_Sins(ptr->unk_2A * 3000) * M_PI) * 0.2f;
                if (ptr->unk_28 < ptr->unk_34) {
                    ptr->unk_00 = 0;
                }
            }
        }
    }
}

void func_80AB840C(EnNiw* this, GlobalContext* globalCtx) {
    s16 i;
    EnNiwStruct1* ptr = this->unk_358;
    u8 flag = 0;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(gfxCtx, "../z_en_niw.c", 1897);

    func_80093D84(globalCtx->state.gfxCtx);

    for (i = 0; i < 20; i++, ptr++) {
        if (ptr->unk_00 == 1) {
            if (flag == 0) {
                gSPDisplayList(oGfxCtx->polyXlu.p++, D_060023B0);
                flag++;
            }
            Matrix_Translate(ptr->unk_04.x, ptr->unk_04.y, ptr->unk_04.z, MTXMODE_NEW);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_Scale(ptr->unk_2C, ptr->unk_2C, 1.0f, MTXMODE_APPLY);
            Matrix_RotateZ(ptr->unk_30, MTXMODE_APPLY);
            Matrix_Translate(0.0f, -1000.0f, 0.0f, MTXMODE_APPLY);
            gSPMatrix(oGfxCtx->polyXlu.p++, Matrix_NewMtx(gfxCtx, "../z_en_niw.c", 1913),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(oGfxCtx->polyXlu.p++, D_06002428);
        }
    }

    CLOSE_DISPS(gfxCtx, "../z_en_niw.c", 1919);
}
