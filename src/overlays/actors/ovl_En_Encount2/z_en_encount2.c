#include "z_en_encount2.h"
#include "overlays/actors/ovl_En_Fire_Rock/z_en_fire_rock.h"
#include "vt.h"

#define FLAGS 0x00000030

#define THIS ((EnEncount2*)thisx)

void EnEncount2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A07A4C(EnEncount2 *this, GlobalContext* globalCtx);
void func_80A07CA4(EnEncount2 *this, GlobalContext* globalCtx);
void func_80A0891C(EnEncount2 *this, GlobalContext* globalCtx);
void func_80A08748(EnEncount2 *this, GlobalContext* globalCtx);
void func_80A08694(EnEncount2 *this, Vec3f* arg1, f32 arg2);


extern Gfx D_06000DE0[];

const ActorInit En_Encount2_InitVars = {
    ACTOR_EN_ENCOUNT2,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_EFC_STAR_FIELD,
    sizeof(EnEncount2),
    (ActorFunc)EnEncount2_Init,
    NULL,
    (ActorFunc)EnEncount2_Update,
    (ActorFunc)EnEncount2_Draw,
};

void EnEncount2_Init(Actor* thisx, GlobalContext *globalCtx) {
    EnEncount2 *this = THIS;

    if (globalCtx->sceneNum != 0x60) {
        this->unk_15A = 1;
    }

    if (this->unk_15A == 0) {
        osSyncPrintf("\n\n");
        // Death Mountain encounter 2 has been set up.
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ デスマウンテンエンカウント２セットされました ☆☆☆☆☆ %d\n" VT_RST, this->actor.params);
        if (LINK_IS_ADULT && (gSaveContext.eventChkInf[4] & 0x200)) {
            Actor_Kill(&this->actor);
        }
    } else {
        osSyncPrintf("\n\n");
        // Ganon Tower encounter 2 has been set up.
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ ガノンタワー脱出エンカウント２セットされました ☆☆☆☆☆ %d\n" VT_RST, this->actor.params);
    }

    this->actionFunc = func_80A07A4C;
}

#ifdef NON_MATCHING
// unk_180/4 need 0 in reg
void func_80A07A4C(EnEncount2 *this, GlobalContext *globalCtx) {
    Player* player = PLAYER;
    s16 tmp1 = 0;
    s16 quake;

    if (this->unk_15A == 0) {
        if ((1500.0f < player->actor.posRot.pos.y) && 
            (-700.0f < player->actor.posRot.pos.x) && (player->actor.posRot.pos.x < 100.0f) && 
            (player->actor.posRot.pos.z < -1290.0f) && (-3600.0f < player->actor.posRot.pos.z)) {
            tmp1 = 1;
        }
    } else {
        if ((this->actor.xzDistFromLink < 700.0f) && 
            (Flags_GetSwitch(globalCtx, 0x37) != 0) &&
            ((globalCtx->sceneNum == 0x4F) || (globalCtx->sceneNum == 0x1A) || (globalCtx->sceneNum == 0xE) || (globalCtx->sceneNum == 0xF)) && 
            (this->unk_15C == 0)) {
            tmp1 = 2;
        }
    }

    switch (tmp1) {
        case 0:
            this->unk_184 = this->unk_180 = (s32)0U;

            this->unk_178--;
            if (this->unk_178 <= 0) {
                this->unk_178 = 0;
            }
            break;

        case 1:
            if ((this->unk_154 == 1) || 
                ((this->unk_180 == 0) && (this->unk_184 == 0))) {
                quake = Quake_Add(ACTIVE_CAM, 1);
                Quake_SetSpeed(quake, 0x7FFF);
                Quake_SetQuakeValues(quake, 0x32, 0, 0, 0);
                Quake_SetCountdown(quake, 0x12C);
                
                this->unk_180 = 0;
                this->unk_184 = 1;
            }

        case 2:
            this->unk_178++;
            if (this->unk_178 >= 0x3D) {
                this->unk_178 = 0x3C;
            }

            if (this->unk_154 == 0) {
                this->unk_154 = 0xC8;
                this->unk_158 = 0;
                this->actionFunc = func_80A07CA4;
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Encount2/func_80A07A4C.s")
#endif

void func_80A07CA4(EnEncount2 *this, GlobalContext *globalCtx) {
    Player* player = PLAYER;
    s32 pad;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    EnFireRock* fireRock;
    f32 sp7C;
    f32 tmpf1;
    f32 sp74;
    f32 tmpf2;
    Vec3f sp64;
    s16 sp62;
    s16 sp60;
    s16 sp5E;

    this->unk_178++;
    if (this->unk_178 >= 0x3D) {
        this->unk_178 = 0x3C;
    }

    sp60 = 0;
    if (this->unk_15A == 0) {
        if (this->unk_154 == 0) {
            this->unk_154 = 0x64;
            this->actionFunc = func_80A07A4C;
            return;
        }

        if ((1500.0f < player->actor.posRot.pos.y) &&
           (-700.0f < player->actor.posRot.pos.x) &&
           (player->actor.posRot.pos.x < 100.0f) &&
           (player->actor.posRot.pos.z < -1290.0f) &&
           (-3860.0f < player->actor.posRot.pos.z)) {
            sp5E = 2;
            sp60 = 1;
        }

        Audio_PlayActorSound2(&this->actor, NA_SE_EV_VOLCANO - SFX_FLAG);
    } else if ((this->actor.xzDistFromLink < 700.0f) &&
              Flags_GetSwitch(globalCtx, 0x37) &&
              ((globalCtx->sceneNum == 0x4F) || (globalCtx->sceneNum == 0x1A) || (globalCtx->sceneNum == 0xE) || (globalCtx->sceneNum == 0xF)) &&
              (this->unk_15C == 0)) {
        sp5E = 1;
        sp60 = 2;
    }

    if (sp60 != 0) {
        sp8C = globalCtx->view.lookAt.x - globalCtx->view.eye.x;
        sp88 = globalCtx->view.lookAt.y - globalCtx->view.eye.y;
        sp84 = globalCtx->view.lookAt.z - globalCtx->view.eye.z;
        tmpf1 = sqrtf(SQ(sp8C) + SQ(sp88) + SQ(sp84));

        sp7C = sp8C / tmpf1;
        sp74 = sp84 / tmpf1;

        sp8C = globalCtx->view.eye.x + (sp7C * 300.0f);
        sp88 = (globalCtx->view.eye.y + ((sp88 / tmpf1) * 160.0f)) + 400.0f;
        sp84 = globalCtx->view.eye.z + (sp74 * 300.0f);

        sp64.x = Math_Rand_CenteredFloat(200.0f) + (globalCtx->view.eye.x + (sp7C * 200.0f));
        sp64.y = Math_Rand_CenteredFloat(50.0f) + sp88;
        sp64.z = Math_Rand_CenteredFloat(200.0f) + (globalCtx->view.eye.z + (sp74 * 200.0f));
        tmpf2 = Math_Rand_CenteredFloat(0.005f) + 0.007f;
        if (sp60 == 1) {
            func_80A08694(this, &sp64, tmpf2);
        } else if (this->unk_15E == 0) {
            func_80A08694(this, &sp64, tmpf2);
            this->unk_15E = 5;
        }

        if ((this->unk_158 < sp5E) && (this->unk_156 == 0)) {
            if (sp60 == 1) {
                this->unk_156 = 4;
                sp62 = 0;
                if ((Math_Rand_ZeroFloat(1.99f) < 1.0f) && (LINK_IS_CHILD)) {
                    sp7C = Math_Rand_CenteredFloat(10.0f) + player->actor.posRot.pos.x;
                    sp74 = Math_Rand_CenteredFloat(10.0f) + player->actor.posRot.pos.z;
                } else {
                    if (player->linearVelocity != 0.0f) {
                        sp7C = Math_Rand_CenteredFloat(200.0f) + (globalCtx->view.eye.x + (sp7C * 300.0f));
                        sp74 = Math_Rand_CenteredFloat(50.0f) + (globalCtx->view.eye.z + (sp74 * 600.0f));
                    } else {
                        sp7C = Math_Rand_CenteredFloat(10.0f) + player->actor.posRot.pos.x;
                        sp74 = Math_Rand_CenteredFloat(10.0f) + player->actor.posRot.pos.z;
                    }
                    sp62 = 3;
                }
            } else {
                this->unk_156 = 0x32;
                sp62 = 3;
                sp7C = Math_Rand_CenteredFloat(100.0f) + sp8C;
                sp74 = Math_Rand_CenteredFloat(100.0f) + sp84;
                if (Math_Rand_ZeroFloat(3.99f) < 1.0f) {
                    sp7C = Math_Rand_CenteredFloat(70.0f) + player->actor.posRot.pos.x;
                    sp74 = Math_Rand_CenteredFloat(70.0f) + player->actor.posRot.pos.z;
                }
            }

            fireRock = (EnFireRock*)Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_FIRE_ROCK, sp7C, sp88, sp74, 0, 0, 0, sp62);
            if (fireRock != NULL) {
                fireRock->unk_190 = this;
                this->unk_158++;
                return;
            }

            // Couldn't spawn
            osSyncPrintf("\x1b[32m☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n\x1b[m");
            osSyncPrintf("\x1b[32m☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n\x1b[m");
            osSyncPrintf("\x1b[32m☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n\x1b[m");
            osSyncPrintf("\x1b[32m☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n\x1b[m");
            osSyncPrintf("\x1b[32m☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n\n\x1b[m");
        }
    }
}

void EnEncount2_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnEncount2 *this = THIS;

    if (this->unk_154 != 0) {
        this->unk_154--;
    }

    if (this->unk_156 != 0) {
        this->unk_156--;
    }

    if (this->unk_15E != 0) {
        this->unk_15E--;
    }
    if (globalCtx){};

    this->actionFunc(this, globalCtx);
    func_80A08748(this, globalCtx);
    if (this->unk_15A == 0) {
        this->unk_17C = this->unk_178 / 60.0f;
        this->unk_160 = (this->unk_178 / 60.0f) * -50.0f;

        globalCtx->envCtx.unk_8C[0] = (s16)((this->unk_178 / 60.0f) * -50.0f) * -1.5f;

        globalCtx->envCtx.unk_8C[1] = globalCtx->envCtx.unk_8C[2] = this->unk_160;

        this->unk_168 = this->unk_17C * -20.0f;
        globalCtx->envCtx.unk_8C[3] = (s16)(this->unk_17C * -20.0f) * -1.5f;

        globalCtx->envCtx.unk_8C[4] = globalCtx->envCtx.unk_8C[5] = this->unk_168;

        this->unk_170 = this->unk_17C * -50.0f;
        globalCtx->envCtx.unk_9E = this->unk_17C * -50.0f;

        globalCtx->envCtx.unk_98[0] = (u8)((160.0f - globalCtx->envCtx.unk_CF[0]) * this->unk_17C);
        globalCtx->envCtx.unk_98[1] = (u8)((160.0f - globalCtx->envCtx.unk_CF[1]) * this->unk_17C);
        globalCtx->envCtx.unk_98[2] = (u8)((150.0f - globalCtx->envCtx.unk_CF[2]) * this->unk_17C);
    }
}

void EnEncount2_Draw(Actor* thisx, GlobalContext *globalCtx) {
    EnEncount2 *this = THIS;

    func_80A0891C(this, globalCtx);
}

void func_80A08694(EnEncount2 *this, Vec3f *arg1, f32 arg2) {
    EnEncount2Struct1 *ptr = this->unk_188;
    s16 i;

    for (i = 0; i < 50; i++, ptr++) {
        if (ptr->unk_10 == 0) {
            ptr->unk_00 = *arg1;
            ptr->unk_0C = arg2;
            ptr->unk_20.x = 0.0f;
            ptr->unk_20.y = 0.0f;
            ptr->unk_20.z = 0.0f;

            ptr->unk_14 = Math_Rand_CenteredFloat(20.0f);
            ptr->unk_18 = -20.0f;
            ptr->unk_1C = Math_Rand_CenteredFloat(20.0f);
            ptr->unk_10 = 1;
            break;
        }
    }
}

void func_80A08748(EnEncount2 *this, GlobalContext *globalCtx) {
    f32 tmpf1;
    f32 tmpf2;
    f32 tmpf3;
    s16 i;
    
    EnEncount2Struct1* ptr = this->unk_188;
    Player* player = PLAYER;

    for (i = 0; i < 50; i++, ptr++) {
        if (ptr->unk_10 != 0) {
            ptr->unk_20.x += Math_Rand_ZeroOne() * 500.0f;
            ptr->unk_20.y += Math_Rand_ZeroOne() * 500.0f;
            ptr->unk_20.z += Math_Rand_ZeroOne() * 500.0f;
            
            tmpf1 = ptr->unk_00.x + ptr->unk_14;
            tmpf2 = ptr->unk_00.y + ptr->unk_18;
            tmpf3 = ptr->unk_00.z + ptr->unk_1C;

            Math_SmoothScaleMaxF(&ptr->unk_00.x, tmpf1, 0.3f, 30.0f);
            Math_SmoothScaleMaxF(&ptr->unk_00.y, tmpf2, 0.8f, 250.0f);
            Math_SmoothScaleMaxF(&ptr->unk_00.z, tmpf3, 0.3f, 30.0f);
            Math_SmoothScaleMaxF(&ptr->unk_18, -20.0f, 0.9f, 1.0f);

            if (globalCtx->sceneNum != 0x60) {
                if (ptr->unk_00.y < (player->actor.groundY - 50.0f)) {
                    ptr->unk_10 = 0;
                }
            } else if (ptr->unk_00.y < 1500.0f) {
                ptr->unk_10 = 0;
            }
        }
    }
}

void func_80A0891C(EnEncount2 *this, GlobalContext *globalCtx) {
    s16 i;
    s32 objIdx;
    EnEncount2Struct1* ptr = this->unk_188;
    GraphicsContext *localGfxCtx = globalCtx->state.gfxCtx;

    GraphicsContext *gfxCtx = localGfxCtx;
    s32 pad;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, localGfxCtx, "../z_en_encount2.c", 0x282);
    objIdx = Object_GetIndex(&globalCtx->objectCtx, 0x92);
    if (objIdx >= 0) {
        gDPPipeSync(gfxCtx->polyXlu.p++);
        gSPSegment(gfxCtx->polyOpa.p++, 0x06, globalCtx->objectCtx.status[objIdx].segment);

        for (i = 0; i < 50; i++, ptr++) {
            if (ptr->unk_10 != 0) {
                Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
                Matrix_RotateX(ptr->unk_20.x * 0.017453292f, 1);
                Matrix_RotateY(ptr->unk_20.y * 0.017453292f, 1);
                Matrix_RotateZ(ptr->unk_20.z * 0.017453292f, 1);
                Matrix_Scale(ptr->unk_0C, ptr->unk_0C, ptr->unk_0C, 1);

                gDPSetPrimColor(gfxCtx->polyOpa.p++, 0, 0, 255, 155, 55, 255);
                gDPSetEnvColor(gfxCtx->polyOpa.p++, 155, 255, 55, 255);
                gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_encount2.c", 0x29D), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gfxCtx->polyOpa.p++, D_06000DE0);
            }
        }
    }

    Graph_CloseDisps(dispRefs, localGfxCtx, "../z_en_encount2.c", 0x2A6);
}
