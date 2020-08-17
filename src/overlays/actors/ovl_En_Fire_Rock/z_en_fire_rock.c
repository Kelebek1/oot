#include "z_en_fire_rock.h"
#include "vt.h"

#define FLAGS 0x00000030

#define THIS ((EnFireRock*)thisx)

void EnFireRock_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFireRock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFireRock_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFireRock_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A125B8(EnFireRock* this, GlobalContext* globalCtx);
void func_80A12730(EnFireRock* this, GlobalContext* globalCtx);
void func_80A120CC(EnFireRock* this, GlobalContext* globalCtx);
void func_80A1241C(EnFireRock* this, GlobalContext* globalCtx);

extern Gfx D_06000DE0[];

const ActorInit En_Fire_Rock_InitVars = {
    ACTOR_EN_FIRE_ROCK,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_EFC_STAR_FIELD,
    sizeof(EnFireRock),
    (ActorFunc)EnFireRock_Init,
    (ActorFunc)EnFireRock_Destroy,
    (ActorFunc)EnFireRock_Update,
    (ActorFunc)EnFireRock_Draw,
};

static ColliderCylinderInit sCylinderInit1 = {
    { COLTYPE_UNK12, 0x11, 0x09, 0x00, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x09, 0x08 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x01, 0x01, 0x00 },
    { 30, 30, -10, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    { COLTYPE_UNK12, 0x11, 0x09, 0x00, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x01, 0x08 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x01, 0x01, 0x00 },
    { 30, 30, -10, { 0, 0, 0 } },
};

void EnFireRock_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFireRock* this = THIS;
    Player* player = PLAYER;
    s32 pad;

    this->unk_18C = this->actor.params;
    if (this->unk_18C != 5) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 15.0f);
        if (this->unk_18C != 6) {
            this->unk_14C = Math_Rand_ZeroFloat(10.0f) + 15.0f;
            this->unk_150 = Math_Rand_ZeroFloat(10.0f) + 15.0f;
            this->unk_154 = Math_Rand_ZeroFloat(10.0f) + 15.0f;
        }
    }

    switch (this->unk_18C) {
        case 5:
            this->actor.draw = NULL;
            // Ceiling rock
            osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ 天井待ち岩 ☆☆☆☆☆ \n" VT_RST);
            this->actionFunc = func_80A125B8;
            break;

        case 6:
            Actor_SetScale(&this->actor, 0.03f);
            Collider_InitCylinder(globalCtx, &this->collider);
            Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit2);
            // Floor rock
            osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ 床岩 ☆☆☆☆☆ \n" VT_RST);
            this->collider.dim.radius = 0x17;
            this->collider.dim.height = 0x25;
            this->collider.dim.yShift = -10;
            Actor_ChangeType(globalCtx, &globalCtx->actorCtx, &this->actor, 6);
            this->actor.colChkInfo.mass = 0xFF;
            this->actionFunc = func_80A12730;
            break;

        case 0:
            this->unk_17C = Math_Rand_CenteredFloat(50.0f) + player->actor.posRot.pos.x;
            this->unk_184 = Math_Rand_CenteredFloat(50.0f) + player->actor.posRot.pos.z;

        case 3:
            this->unk_16C = (Math_Rand_ZeroFloat(2.0f) / 100.0f) + 0.02f;
            Actor_SetScale(&this->actor, this->unk_16C);
            Collider_InitCylinder(globalCtx, &this->collider);
            Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit1);
            this->actor.posRot.rot.y = this->actor.shape.rot.y = Math_Rand_CenteredFloat(65535.0f);
            this->actor.shape.unk_10 = 15.0f;
            this->actionFunc = func_80A120CC;
            break;

        case 1:
            this->actor.velocity.y = Math_Rand_ZeroFloat(3.0f) + 4.0f;
            this->actor.speedXZ = Math_Rand_ZeroFloat(3.0f) + 3.0f;
            this->unk_16C = (Math_Rand_ZeroFloat(1.0f) / 100.0f) + 0.02f;
            Actor_SetScale(&this->actor, this->unk_16C);
            this->actor.gravity = -1.5f;
            Collider_InitCylinder(globalCtx, &this->collider);
            Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit1);
            this->actor.shape.unk_10 = 10.0f;
            this->actor.posRot.rot.y = this->actor.shape.rot.y = Math_Rand_CenteredFloat(65535.0f);
            this->actionFunc = func_80A120CC;
            break;

        case 2:
            this->actor.velocity.y = Math_Rand_ZeroFloat(3.0f) + 4.0f;
            this->actor.speedXZ = Math_Rand_ZeroFloat(3.0f) + 2.0f;
            this->unk_16C = (Math_Rand_ZeroFloat(1.0f) / 500.0f) + 0.01f;
            Actor_SetScale(&this->actor, this->unk_16C);
            this->actor.gravity = -1.2f;
            this->actor.shape.unk_10 = 5.0f;
            this->actor.posRot.rot.y = this->actor.shape.rot.y = Math_Rand_CenteredFloat(65535.0f);
            this->actionFunc = func_80A120CC;
            break;

        default:
            // That rock doesn't exist! ERR!
            osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ そんな岩はねぇ！ERR!!!!!! ☆☆☆☆☆ \n" VT_RST);
            Actor_Kill(&this->actor);
            break;
    }
}

void EnFireRock_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFireRock* this = THIS;

    if ((this->actor.attachedA != NULL) && (this->actor.attachedA == this->unk_190)) {
        EnFireRockFakeActor* refActor = (EnFireRockFakeActor*)this->actor.attachedA;
        if ((refActor->actor.update != NULL) && (refActor->unk_158 > 0)) {
            refActor->unk_158 -= 1;
            osSyncPrintf("\n\n");
            // Spawn count restored
            osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 発生数回復 ☆☆☆☆☆%d\n" VT_RST, refActor->unk_158);
            osSyncPrintf("\n\n");
        }
    }

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A120CC(EnFireRock* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f sp58;
    s32 i;

    if ((this->actor.groundY == -10000.0f) || (this->actor.posRot.pos.y < (player->actor.posRot.pos.y - 200.0f))) {
        Actor_Kill(&this->actor);
        return;
    }

    switch (this->unk_18C) {
        case 0:
            if ((player->actor.posRot.pos.y < this->actor.posRot.pos.y) &&
                ((-700.0f < player->actor.posRot.pos.x) || (player->actor.posRot.pos.x < 100.0f) ||
                 (-1290.0f < player->actor.posRot.pos.z) || (player->actor.posRot.pos.z < -3880.0f))) {
                Math_SmoothScaleMaxF(&this->actor.posRot.pos.x, player->actor.posRot.pos.x, 1.0f, 10.0f);
                Math_SmoothScaleMaxF(&this->actor.posRot.pos.z, player->actor.posRot.pos.z, 1.0f, 10.0f);
            }

        case 3:
            sp58.x = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.x;
            sp58.y = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.y;
            sp58.z = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.z;
            func_8002A4D4(globalCtx, &this->actor, &sp58, 0x64, 0, 0, -1);
            break;

        case 1:
            if ((globalCtx->gameplayFrames & 3) == 0) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_VALVAISA_ROCK);
            }
            break;
    }

    if ((this->actor.bgCheckFlags & 1) && (this->unk_188 == 0)) {
        switch (this->unk_18C) {
            case 0:
            case 3:
                func_80033E88(&this->actor, globalCtx, 5, 2);
            case 1:
                func_80033260(globalCtx, &this->actor, &this->actor.posRot.pos, this->actor.shape.unk_10, 1, 8.0f,
                              0x1F4, 0xA, 0);
                for (i = 0; i < 5; i++) {
                    sp58.x = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.x;
                    sp58.y = this->actor.groundY;
                    sp58.z = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.z;
                    func_8002A4D4(globalCtx, &this->actor, &sp58, 0x12C, 0, 0, -1);
                }
                this->actionFunc = func_80A1241C;
                break;

            default:
                func_80033260(globalCtx, &this->actor, &this->actor.posRot.pos, this->actor.shape.unk_10, 3, 8.0f, 0xC8,
                              0xA, 0);
                Audio_PlaySoundAtPosition(globalCtx, &this->actor.posRot.pos, 0x28, 0x2802);
                Actor_Kill(&this->actor);
                break;
        }
    }
}

void func_80A1241C(EnFireRock* this, GlobalContext* globalCtx) {
    s32 i;
    s32 flag = 0;

    switch (this->unk_18C) {
        case 0:
        case 3:
            flag = 1;
            break;
        case 1:
            flag = 2;
    }

    if (flag) {
        EnFireRock* refRock;

        for (i = 0; i < 2; i++) {
            refRock = (EnFireRock*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_FIRE_ROCK,
                                               Math_Rand_CenteredFloat(3.0f) + this->actor.posRot.pos.x,
                                               Math_Rand_CenteredFloat(3.0f) + (this->actor.posRot.pos.y + 10.0f),
                                               Math_Rand_CenteredFloat(3.0f) + this->actor.posRot.pos.z, 0, 0, 0, flag);
            if (refRock != NULL) {
                refRock->actor.posRot.rot.y = this->actor.posRot.rot.y;
                if (i == 0) {
                    refRock->actor.shape.rot.y = this->actor.shape.rot.y;
                }

                refRock->unk_16C = this->unk_16C - 0.01f;
            } else {
                // Loooooots
                osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ イッパイデッス ☆☆☆☆☆ \n" VT_RST);
            }
        }

        Audio_PlayActorSound2(&this->actor, NA_SE_EN_VALVAISA_ROCK);
    }

    Actor_Kill(&this->actor);
}

void func_80A125B8(EnFireRock* this, GlobalContext* globalCtx) {
    EnFireRock* refRock;

    if (this->actor.xzDistFromLink < 200.0f) {
        if ((this->unk_18E == 0) && (this->unk_18A == 0)) {
            this->unk_18A = 30;
            refRock = (EnFireRock*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_FIRE_ROCK,
                                               Math_Rand_CenteredFloat(3.0f) + this->actor.posRot.pos.x,
                                               this->actor.posRot.pos.y + 10.0f,
                                               Math_Rand_CenteredFloat(3.0f) + this->actor.posRot.pos.z, 0, 0, 0, 3);
            if (refRock != NULL) {
                refRock->unk_188 = 10;
            } else {
                // Looooots
                osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ イッパイデッス ☆☆☆☆☆ \n" VT_RST);
            }
        }
        this->unk_18E = 1;
    } else {
        this->unk_18E = 0;
    }

    if (BREG(0)) {
        DebugDisplay_AddObject(this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z,
                               this->actor.posRot.rot.x, this->actor.posRot.rot.y, this->actor.posRot.rot.z, 1.0f, 1.0f,
                               1.0f, 0, 0xFF, 0, 0xFF, 4, globalCtx->state.gfxCtx);
    }
}

void func_80A12730(EnFireRock* this, GlobalContext* globalCtx) {
    Vec3f sp34;
    s16 sp32;

    if (this->unk_18A == 0) {
        sp34.x = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.x;
        sp34.y = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.y;
        sp34.z = Math_Rand_CenteredFloat(20.0f) + this->actor.posRot.pos.z;
        sp32 = (s16)Math_Rand_CenteredFloat(60.0f) + 0x82;
        this->unk_18A = (s16)Math_Rand_ZeroFloat(3.0f) + 3;
        func_8002A4D4(globalCtx, &this->actor, &sp34, sp32, 0, 0, -1);
    }
}

void EnFireRock_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFireRock* this = THIS;
    s32 pad;
    Player* player2 = PLAYER;
    Player* player = PLAYER;
    s32 flag;

    if (this->unk_18A != 0) {
        this->unk_18A--;
    }

    if (this->unk_188 != 0) {
        this->unk_188--;
    }

    this->actionFunc(this, globalCtx);
    if (this->unk_18C != 5) {
        this->unk_158 += this->unk_14C;
        this->unk_15C += this->unk_150;
        this->unk_160 += this->unk_154;
        this->unk_174 = 3.0f;

        this->actor.shape.unk_10 = (this->unk_16C * 300.0f) + 10.0f;
        if (this->actor.shape.unk_10 < 10.0f) {
            this->actor.shape.unk_10 = 10.0f;
        }

        if (this->actor.shape.unk_10 > 20.0f) {
            this->actor.shape.unk_10 = 20.0f;
        }

        if ((this->unk_18C == 0) || (this->unk_18C == 3)) {
            this->actor.gravity = -0.3f - (this->unk_16C * 7.0f);
        }

        if (this->unk_18C != 6) {
            Actor_MoveForward(&this->actor);
            func_8002E4B4(globalCtx, &this->actor, 50.0f, 50.0f, 100.0f, 0x1C);
        }

        flag = 0;
        if ((this->actionFunc != func_80A1241C) &&
            ((this->unk_18C == 0) || (this->unk_18C == 3) || (this->unk_18C == 1))) {
            if (this->collider.base.atFlags & 4) {
                this->collider.base.atFlags &= ~4;
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_BRIDGE_OPEN_STOP);
                this->actor.velocity.y = 0.0f;
                this->actor.speedXZ = 0.0f;
                this->actionFunc = func_80A1241C;
                // Shield defence level 1
                osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ シールド防御 Lv１ ☆☆☆☆☆ \n" VT_RST);
                return;
            }
            flag = 1;
        }

        if (this->unk_18C == 6) {
            if (this->collider.base.atFlags & 2) {
                this->collider.base.atFlags &= ~2;
                if (this->collider.base.at == &player->actor) {
                    if (!(player2->stateFlags1 & 0x4000000)) {
                        func_8002F758(globalCtx, &this->actor, 2.0f, -player2->actor.posRot.rot.y, 3.0f, 4);
                    }
                    return;
                }
            }
            flag = 1;
        }

        if (flag) {
            Collider_CylinderUpdate(&this->actor, &this->collider);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void EnFireRock_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFireRock* this = THIS;
    s32 pad;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fire_rock.c", 747);
    Matrix_Translate(this->actor.posRot.pos.x + this->unk_170, this->actor.posRot.pos.y + this->unk_174,
                     this->actor.posRot.pos.z + this->unk_178, 0);
    Matrix_RotateX(this->unk_158 * 0.017453292f, 1);
    Matrix_RotateY(this->unk_15C * 0.017453292f, 1);
    Matrix_RotateZ(this->unk_160 * 0.017453292f, 1);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1);
    func_80093D18(globalCtx->state.gfxCtx);

    gDPSetPrimColor(gfxCtx->polyOpa.p++, 0, 0, 255, 155, 55, 255);
    gDPSetEnvColor(gfxCtx->polyOpa.p++, 155, 255, 55, 255);
    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_fire_rock.c", 768),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, D_06000DE0);

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fire_rock.c", 773);
}
