/*
 * File: z_en_gb.c
 * Overlay: ovl_En_Gb
 * Description: Poe Collector and surroundings
 */

#include "z_en_gb.h"

#define FLAGS 0x00000009

#define THIS ((EnGb*)thisx)

void EnGb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGb_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A2F83C(EnGb* this, GlobalContext* globalCtx);
void func_80A30350(EnGb* this, GlobalContext* globalCtx);
void func_80A2F94C(EnGb* this, GlobalContext* globalCtx);
void func_80A2F9C0(EnGb* this, GlobalContext* globalCtx);
void func_80A2FA50(EnGb* this, GlobalContext* globalCtx);
void func_80A2FC70(EnGb* this, GlobalContext* globalCtx);
void func_80A2FB40(EnGb* this, GlobalContext* globalCtx);
void func_80A2FBB0(EnGb* this, GlobalContext* globalCtx);
void func_80A2FC0C(EnGb* this, GlobalContext* globalCtx);
void func_80A2FFFC(EnGb* this, GlobalContext* globalCtx);

extern SkeletonHeader D_0600C220;
extern AnimationHeader D_0600049C;
extern AnimationHeader D_0600C8EC;
extern UNK_TYPE D_0600C2D0;
extern Gfx D_0600C0B0[];

const ActorInit En_Gb_InitVars = {
    ACTOR_EN_GB,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_PS,
    sizeof(EnGb),
    (ActorFunc)EnGb_Init,
    (ActorFunc)EnGb_Destroy,
    (ActorFunc)EnGb_Update,
    (ActorFunc)EnGb_Draw,
};

typedef struct {
    Color_RGBA8_n unk_00;
    Color_RGBA8_n unk_04;
    UNK_PTR unk_08;
    s16 unk_0C;
} EnGbStruct2; // size = 0x10

EnGbStruct2 D_80A30660[] = {
    { { 255, 255, 170, 255 }, { 255, 200, 0, 255 }, 0x0600A870, -15 },
    { { 255, 255, 170, 255 }, { 0, 150, 0, 255 }, 0x0600B070, -12 },
    { { 255, 170, 255, 255 }, { 100, 0, 150, 255 }, 0x0600B870, -8 },
};

static ColliderCylinderInit_Set3 sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 40, 75, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit_Set3 sCollidersInit[3] = {
    {
        { COLTYPE_UNK10, 0x00, 0x00, 0x39, COLSHAPE_CYLINDER },
        { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 4, 20, 0, { 0, 0, 0 } },
    },
    {
        { COLTYPE_UNK10, 0x00, 0x00, 0x39, COLSHAPE_CYLINDER },
        { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 4, 20, 0, { 0, 0, 0 } },
    },
    {
        { COLTYPE_UNK10, 0x00, 0x00, 0x39, COLSHAPE_CYLINDER },
        { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 10, 20, 0, { 0, 0, 0 } },
    },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(unk_1F, 6, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 2200, ICHAIN_STOP),
};

void func_80A2F180(EnGb* this) {
    if (gSaveContext.infTable[11] & 0x40) {
        this->unk_37E = 0x70F5;
    } else {
        this->unk_37E = 0x70F4;
    }
}

void EnGb_Init(Actor* thisx, GlobalContext* globalCtx) {
    static Vec3f D_80A30748[] = {
        { -8.0f, 112.0f, -8.0f },
        { -3.0f, 112.0f, 29.0f },
        { 31.0f, 112.0f, 29.0f },
        { 31.0f, 112.0f, -8.0f },
    };

    s32 pad;
    EnGb* this = THIS;
    UNK_TYPE sp84 = 0;
    s32 i;
    f32 tmpf1;
    Vec3f sp70;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyInfo_SetActorMove(&this->dyna, DPM_UNK);
    DynaPolyInfo_Alloc(&D_0600C2D0, &sp84);
    this->dyna.dynaPolyId = DynaPolyInfo_RegisterActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, sp84);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600C220, &D_0600049C, this->limbDrawTable,
                     this->transitionDrawTable, 12);
    Collider_InitCylinder(globalCtx, &this->collider1);
    Collider_SetCylinder_Set3(globalCtx, &this->collider1, &this->dyna.actor, &sCylinderInit);

    for (i = 0; i < 3; i++) {
        Collider_InitCylinder(globalCtx, &this->colliders[i]);
        Collider_SetCylinder_Set3(globalCtx, &this->colliders[i], &this->dyna.actor, &sCollidersInit[i]);
    }

    this->light = Lights_Insert(globalCtx, &globalCtx->lightCtx, &this->lightInfo);
    Lights_InitType0PositionalLight(&this->lightInfo, this->dyna.actor.initPosRot.pos.x,
                                    this->dyna.actor.initPosRot.pos.y, this->dyna.actor.initPosRot.pos.z, 255, 255,
                                    255, 200);
    ActorShape_Init(&this->dyna.actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 35.0f);
    Actor_SetScale(&this->dyna.actor, 0.01f);
    this->dyna.actor.colChkInfo.mass = 0xFF;
    this->dyna.actor.speedXZ = 0.0f;
    this->dyna.actor.velocity.y = 0.0f;
    this->dyna.actor.gravity = -1.0f;
    this->unk_382 = (s16)Math_Rand_ZeroFloat(100.0f) + 100;

    for (i = 0; i < 4; i++) {
        this->unk_388[i].unk_00 = (s32)Math_Rand_ZeroFloat(30.0f) % 3;
        this->unk_388[i].unk_14.x = this->unk_388[i].unk_08.x = this->dyna.actor.posRot.pos.x + D_80A30748[i].x;
        this->unk_388[i].unk_14.y = this->unk_388[i].unk_08.y = this->dyna.actor.posRot.pos.y + D_80A30748[i].y;
        this->unk_388[i].unk_14.z = this->unk_388[i].unk_08.z = this->dyna.actor.posRot.pos.z + D_80A30748[i].z;
        this->unk_388[i].unk_01 = 1;
        this->unk_388[i].unk_03 = this->unk_388[i].unk_02 = 0;
        this->unk_388[i].unk_20 = this->unk_388[i].unk_24 = 0.0f;
        this->unk_388[i].unk_06 = (s16)Math_Rand_ZeroFloat(40.0f);
        this->unk_388[i].unk_28 = 0.2f;
        this->unk_388[i].unk_04 = this->unk_388[i].unk_06 & 1;
    }

    tmpf1 = Math_Rand_ZeroOne();
    this->unk_384.r = (s8)(tmpf1 * 30.0f) + 225;
    this->unk_384.g = (s8)(tmpf1 * 100.0f) + 155;
    this->unk_384.b = (s8)(tmpf1 * 160.0f) + 95;
    this->unk_384.a = 200;

    Matrix_Translate(this->dyna.actor.posRot.pos.x, this->dyna.actor.posRot.pos.y, this->dyna.actor.posRot.pos.z,
                     MTXMODE_NEW);
    Matrix_RotateRPY(this->dyna.actor.posRot.rot.x, this->dyna.actor.posRot.rot.y, this->dyna.actor.posRot.rot.z,
                     MTXMODE_APPLY);
    sp70.x = sp70.y = 0.0f;
    sp70.z = 44.0f;
    Matrix_MultVec3f(&sp70, &this->dyna.actor.posRot2.pos);
    this->dyna.actor.posRot2.pos.y += 62.5f;
    func_80A2F180(this);
    this->actionFunc = func_80A2F83C;
}

void EnGb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGb* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Lights_Remove(globalCtx, &globalCtx->lightCtx, this->light);
    DynaPolyInfo_Free(globalCtx, &globalCtx->colCtx.dyna, this->dyna.dynaPolyId);
}

void func_80A2F608(EnGb* this) {
    static Vec3f D_80A30778[] = {
        { -48.0f, 0.0f, 34.0f },
        { -55.0f, 0.0f, 49.0f },
        { -48.0f, 0.0f, 60.0f },
    };

    s32 i;
    Vec3f sp48;
    Vec3f sp3C;

    Matrix_Translate(this->dyna.actor.posRot.pos.x, this->dyna.actor.posRot.pos.y, this->dyna.actor.posRot.pos.z,
                     MTXMODE_NEW);
    Matrix_RotateRPY(this->dyna.actor.posRot.rot.x, this->dyna.actor.posRot.rot.y, this->dyna.actor.posRot.rot.z,
                     MTXMODE_APPLY);
    sp48.x = sp48.y = 0.0f;
    sp48.z = 25.0f;
    Matrix_MultVec3f(&sp48, &sp3C);
    this->collider1.dim.pos.x = sp3C.x;
    this->collider1.dim.pos.y = sp3C.y;
    this->collider1.dim.pos.z = sp3C.z;

    for (i = 0; i < 3; i++) {
        Matrix_Translate(this->dyna.actor.posRot.pos.x, this->dyna.actor.posRot.pos.y, this->dyna.actor.posRot.pos.z,
                         MTXMODE_NEW);
        Matrix_RotateRPY(this->dyna.actor.posRot.rot.x, this->dyna.actor.posRot.rot.y, this->dyna.actor.posRot.rot.z,
                         MTXMODE_APPLY);
        Matrix_MultVec3f(&D_80A30778[i], &sp3C);
        this->colliders[i].dim.pos.x = sp3C.x;
        this->colliders[i].dim.pos.y = sp3C.y;
        this->colliders[i].dim.pos.z = sp3C.z;
    }
}

s32 func_80A2F760(EnGb* this) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (this->unk_388[i].unk_03) {
            return 1;
        }
    }

    return 0;
}

void func_80A2F7C0(EnGb* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600C8EC, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_0600C8EC.genericHeader),
                         2, 0.0f);
    Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_NALE_MAGIC);
    this->actionFunc = func_80A2FC70;
}

void func_80A2F83C(EnGb* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (!func_80A2F760(this)) {
        if (this->unk_382 != 0) {
            this->unk_382--;
        } else {
            func_80A2F7C0(this);
            return;
        }
    }

    if (func_8002F194(&this->dyna.actor, globalCtx)) {
        switch (func_8002F368(globalCtx)) {
            case 0:
                func_80A2F180(this);
                this->actionFunc = func_80A2F94C;
                break;

            case 27:
                player->actor.textId = 0x70F6;
                this->actionFunc = func_80A2F9C0;
                break;

            case 28:
                player->actor.textId = 0x70F7;
                this->actionFunc = func_80A2FA50;
                break;
        }
    } else if (this->dyna.actor.xzDistFromLink < 100.0f) {
        func_8002F298(&this->dyna.actor, globalCtx, 100.0f, 0x1B);
    }
}

void func_80A2F94C(EnGb* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 6) && func_80106BC8(globalCtx)) {
        if (!(gSaveContext.infTable[11] & 0x40)) {
            gSaveContext.infTable[11] |= 0x40;
        }

        func_80A2F180(this);
        this->actionFunc = func_80A2F83C;
    }
}

void func_80A2F9C0(EnGb* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 6) && func_80106BC8(globalCtx)) {
        if (!(gSaveContext.infTable[11] & 0x40)) {
            gSaveContext.infTable[11] |= 0x40;
        }

        func_80A2F180(this);
        func_8008ED9C(globalCtx, PLAYER, 20, 30);
        Rupees_ChangeBy(10);
        this->actionFunc = func_80A2F83C;
    }
}

void func_80A2FA50(EnGb* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 6) && func_80106BC8(globalCtx)) {
        if (!(gSaveContext.infTable[11] & 0x40)) {
            gSaveContext.infTable[11] |= 0x40;
        }

        func_80A2F180(this);
        func_8008ED9C(globalCtx, PLAYER, 20, 30);
        Rupees_ChangeBy(50);
        gSaveContext.unk_EBC += 100;
        if (gSaveContext.unk_EBC != 0x3E8) {
            if (gSaveContext.unk_EBC > 0x44C) {
                gSaveContext.unk_EBC = 0x44C;
            }

            this->actionFunc = func_80A2F83C;
        } else {
            Player* player = PLAYER;

            player->exchangeItemId = 0;
            this->unk_37E = 0x70F8;
            func_8010B720(globalCtx, this->unk_37E);
            this->actionFunc = func_80A2FB40;
        }
    }
}

void func_80A2FB40(EnGb* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 6) && func_80106BC8(globalCtx)) {
        func_8002F434(&this->dyna.actor, globalCtx, GI_BOTTLE, 100.0f, 10.0f);
        this->actionFunc = func_80A2FBB0;
    }
}

void func_80A2FBB0(EnGb* this, GlobalContext* globalCtx) {
    if (func_8002F410(&this->dyna.actor, globalCtx)) {
        this->dyna.actor.attachedA = NULL;
        this->actionFunc = func_80A2FC0C;
    } else {
        func_8002F434(&this->dyna.actor, globalCtx, GI_BOTTLE, 100.0f, 10.0f);
    }
}

void func_80A2FC0C(EnGb* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 6) && func_80106BC8(globalCtx)) {
        func_8002F194(&this->dyna.actor, globalCtx);
        func_80A2F180(this);
        this->actionFunc = func_80A2F83C;
    }
}

void func_80A2FC70(EnGb* this, GlobalContext* globalCtx) {
    if (this->skelAnime.animCurrentFrame == SkelAnime_GetFrameCount(&D_0600C8EC.genericHeader)) {
        SkelAnime_ChangeAnim(&this->skelAnime, &D_0600049C, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_0600049C.genericHeader), 0, 0.0f);
        this->actionFunc = func_80A2F83C;
    } else if (this->skelAnime.animCurrentFrame == 18.0f) {
        s32 i;

        for (i = 0; i < 4; i++) {
            this->unk_388[i].unk_01 = 3;
            this->unk_388[i].unk_03 = 1;
        }

        this->unk_382 = (s16)Math_Rand_ZeroFloat(600.0f) + 0x258;
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_WOOD_HIT);
    }
}

void EnGb_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGb* this = THIS;
    s32 i;
    f32 rand;

    this->unk_380++;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actionFunc(this, globalCtx);
    this->dyna.actor.textId = this->unk_37E;
    func_80A2F608(this);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    for (i = 0; i < 3; i++) {
        if (globalCtx) {};
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliders[i].base);
        if (1) {};
    }

    rand = Math_Rand_ZeroOne();
    this->unk_384.r = (s8)(rand * 30.0f) + 225;
    this->unk_384.g = (s8)(rand * 100.0f) + 155;
    this->unk_384.b = (s8)(rand * 160.0f) + 95;
    this->unk_384.a = 200;
    func_80A2FFFC(this, globalCtx);
}

void EnGb_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnGb* this = THIS;
    s32 pad;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_gb.c", 763);
    func_80093D18(globalCtx->state.gfxCtx);
    gDPPipeSync(gfxCtx->polyOpa.p++);
    gDPSetEnvColor(gfxCtx->polyOpa.p++, this->unk_384.r, this->unk_384.g, this->unk_384.b, 255);
    Lights_InitType0PositionalLight(&this->lightInfo, this->dyna.actor.posRot.pos.x, this->dyna.actor.posRot.pos.y,
                                    this->dyna.actor.posRot.pos.z, this->unk_384.r, this->unk_384.g, this->unk_384.b,
                                    this->unk_384.a);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL,
                     NULL, &this->dyna.actor);
    func_80A30350(this, globalCtx);
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_gb.c", 796);
}

void func_80A2FFFC(EnGb* this, GlobalContext* globalCtx) {
    s32 i;
    f32 tmpf1;

    for (i = 0; i < 4; i++) {
        switch (this->unk_388[i].unk_01) {
            case 0:
                Math_SmoothScaleMaxF(&this->unk_388[i].unk_20, 1.0f, 0.02f, this->unk_388[i].unk_24);
                Math_SmoothScaleMaxF(&this->unk_388[i].unk_24, 1.0f, 0.001f, 1.0f);
                if ((this->unk_388[i].unk_28 - 0.01f) <= this->unk_388[i].unk_20) {
                    this->unk_388[i].unk_20 = this->unk_388[i].unk_28;
                    this->unk_388[i].unk_24 = 0.0f;
                    this->unk_388[i].unk_01 = 1;
                    this->unk_388[i].unk_02 = 2;
                    this->unk_388[i].unk_06 = 0;
                }
                break;

            case 1:
                if (this->unk_388[i].unk_06) {
                    this->unk_388[i].unk_06--;
                } else {
                    this->unk_388[i].unk_03 = 0;
                    this->unk_388[i].unk_24 = 0.0f;
                    this->unk_388[i].unk_01 = this->unk_388[i].unk_02;
                }
                break;

            case 2:
                Math_SmoothScaleMaxF(&this->unk_388[i].unk_20, 0.0f, 0.02f, this->unk_388[i].unk_24);
                Math_SmoothScaleMaxF(&this->unk_388[i].unk_24, 1.0f, 0.001f, 1.0f);
                if (this->unk_388[i].unk_20 <= (1.0f / 100.0f)) {
                    this->unk_388[i].unk_28 += 0.2f;
                    if (this->unk_388[i].unk_28 > 1.0f) {
                        this->unk_388[i].unk_28 = 1.0f;
                    }

                    this->unk_388[i].unk_20 = 0.0f;
                    this->unk_388[i].unk_24 = 0.0f;
                    this->unk_388[i].unk_01 = 1;
                    this->unk_388[i].unk_02 = 0;
                    this->unk_388[i].unk_06 = 0;
                }
                break;

            case 3:
                Math_SmoothScaleMaxF(&this->unk_388[i].unk_20, 0.0f, 0.5f, 1.0f);
                if (this->unk_388[i].unk_20 <= (1.0f / 100.0f)) {
                    this->unk_388[i].unk_28 = 0.2f;
                    this->unk_388[i].unk_20 = 0.0f;
                    this->unk_388[i].unk_24 = 0.0f;

                    this->unk_388[i].unk_01 = 1;
                    this->unk_388[i].unk_02 = 0;
                    this->unk_388[i].unk_06 = (s16)Math_Rand_ZeroFloat(60.0f) + 0x3C;
                }
                break;
        }

        tmpf1 = this->unk_388[i].unk_20 * 60.0f;
        if ((i == 0) || (i == 3)) {
            this->unk_388[i].unk_08.x = this->unk_388[i].unk_14.x;
            this->unk_388[i].unk_08.y = this->unk_388[i].unk_14.y + tmpf1;
            this->unk_388[i].unk_08.z = this->unk_388[i].unk_14.z;
        } else if (i == 1) {
            s16 tmp = this->dyna.actor.posRot.rot.y - 0x4000;

            this->unk_388[i].unk_08.x = this->unk_388[i].unk_14.x + (Math_Sins(tmp) * tmpf1);
            this->unk_388[i].unk_08.z = this->unk_388[i].unk_14.z + (Math_Coss(tmp) * tmpf1);
            this->unk_388[i].unk_08.y = this->unk_388[i].unk_14.y;
        } else {
            s16 tmp = this->dyna.actor.posRot.rot.y + 0x4000;
            this->unk_388[i].unk_08.x = this->unk_388[i].unk_14.x + (Math_Sins(tmp) * tmpf1);
            this->unk_388[i].unk_08.z = this->unk_388[i].unk_14.z + (Math_Coss(tmp) * tmpf1);
            this->unk_388[i].unk_08.y = this->unk_388[i].unk_14.y;
        }
    }
}

void func_80A30350(EnGb* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 i;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_gb.c", 914);
    func_80093D84(globalCtx->state.gfxCtx);

    for (i = 0; i < 4; i++) {
        u8 num = this->unk_388[i].unk_00;

        gSPSegment(gfxCtx->polyXlu.p++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0,
                                    (D_80A30660[num].unk_0C * this->unk_380) & 0x1FF, 0x20, 0x80));
        gSPSegment(gfxCtx->polyXlu.p++, 0x09, SEGMENTED_TO_VIRTUAL(D_80A30660[num].unk_08));
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0x80, 0x80, D_80A30660[num].unk_00.r, D_80A30660[num].unk_00.g,
                        D_80A30660[num].unk_00.b, D_80A30660[num].unk_00.a);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, D_80A30660[num].unk_04.r, D_80A30660[num].unk_04.g,
                       D_80A30660[num].unk_04.b, D_80A30660[num].unk_04.a);
        Matrix_Push();
        Matrix_Translate(this->unk_388[i].unk_08.x, this->unk_388[i].unk_08.y, this->unk_388[i].unk_08.z, MTXMODE_NEW);
        func_800D1FD4(&globalCtx->mf_11DA0);
        if (this->unk_388[i].unk_04) {
            Matrix_RotateRPY(0, -0x8000, 0, MTXMODE_APPLY);
        }

        Matrix_Scale(0.007f, 0.007f, 1.0f, MTXMODE_APPLY);
        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_gb.c", 955),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, D_0600C0B0);
        Matrix_Pull();
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_gb.c", 962);
}
