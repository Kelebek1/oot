#include "z_boss_fd.h"

#define FLAGS 0x00000035

#define THIS ((BossFd*)thisx)

void BossFd_Init(Actor* thisx, GlobalContext* globalCtx);
void BossFd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BossFd_Update(Actor* thisx, GlobalContext* globalCtx);
void BossFd_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808D08F8(GlobalContext* globalCtx, BossFd* this);
void func_808CDE30(BossFd* this, GlobalContext* globalCtx);
void func_808CB6A8(BossFd* this, GlobalContext* globalCtx);


extern SkeletonHeader D_06011660;
extern SkeletonHeader D_060115A0;
extern SkeletonHeader D_060114E0;
extern AnimationHeader D_060115E4;
extern AnimationHeader D_06011524;
extern AnimationHeader D_06011464;

extern Gfx D_0600A900[];
extern Gfx D_0600A880[];
extern Gfx D_0600D3A0[];
extern Gfx D_0600D420[];
extern Gfx D_0600B3A8[];
extern Gfx D_0600B3C8[];
extern Gfx D_0600D668[];
extern Gfx D_0600D6E8[];
extern Gfx D_0600B2F8[];

const ActorInit Boss_Fd_InitVars = {
    ACTOR_BOSS_FD,
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_FD,
    sizeof(BossFd),
    (ActorFunc)BossFd_Init,
    (ActorFunc)BossFd_Destroy,
    (ActorFunc)BossFd_Update,
    (ActorFunc)BossFd_Draw,
};

// D_808D1660
static ColliderJntSphItemInit sJntSphItemsInit[19] = {
    {
        { 0x03, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 1, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 2, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 3, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 4, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 5, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 6, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 7, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 8, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 9, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 10, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 11, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 12, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 13, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 14, { { 0, 0, 0 }, 18 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 15, { { 0, 0, 0 }, 16 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 16, { { 0, 0, 0 }, 14 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 17, { { 0, 0, 0 }, 12 }, 100 },
    },
    {
        { 0x02, { 0xFFCFFFFF, 0x00, 0x10 }, { 0xFFCDFFFE, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
        { 18, { { 0, 0, 0 }, 10 }, 100 },
    },
};

// D_808D190C
static ColliderJntSphInit sJntSphInit =
{
    { COLTYPE_METAL_SHIELD, 0x11, 0x09, 0x09, 0x10, COLSHAPE_JNTSPH },
    19, sJntSphItemsInit,
};

// D_808D191C
static InitChainEntry sInitChain[] = {
    ICHAIN_U8(unk_1F, 5, ICHAIN_CONTINUE),
    ICHAIN_S8(naviEnemyId, 33, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 0, ICHAIN_STOP),
};

UNK_TYPE D_808D1A9C[] = {
    0x04051DB0, 0x04051DB0, 0x040521B0, 
    0x040525B0, 0x040529B0, 0x04052DB0, 
    0x040531B0, 0x040535B0, 0x040539B0
};

s8 D_808D1AC2[] = {
    0x00, 0x5F
};

s16 D_808D1AC4[] = {
    0x005A, 0x0055, 0x0050, 0x004B, 0x0046, 0x0041, 0x003C, 0x0037, 
    0x0032, 0x002D, 0x0028, 0x0023, 0x001E, 0x0019, 0x0014, 0x000F, 
    0x000A, 0x0005, 0x0000, 0x001C, 0x001A, 0x0018, 0x0016, 0x0014, 
    0x0012, 0x0010, 0x000E, 0x000C, 0x000A, 0x0000
};

Gfx* D_808D1BC4[] = {
    0x060079A0, 0x06007AC0, 0x06007B70, 0x06007BD0, 
    0x06007C30, 0x06007C90, 0x06007CF0, 0x06007D50, 
    0x06007DB0, 0x06007E10, 0x06007E70, 0x06007ED0, 
    0x06007F30, 0x06007F90, 0x06007FF0, 0x06008038, 
    0x06008080, 0x060080D8
};

Vec3f D_808D1C0C = { 0.0f, 0.0f, 0.0f };
Vec3f D_808D1C18 = { 0.0f, 1700.0f, 7000.0f };
Vec3f D_808D1C24 = { -1000.0f, 700.0f, 7000.0f };

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CADC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CAE8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CAF5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CAFF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CB100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CB198.s")

void BossFd_Init(Actor* thisx, GlobalContext *globalCtx) {
    BossFd *this = THIS;
    s16 i;

    Flags_SetSwitch(globalCtx, 0x14);
    Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BG_VB_SIMA, 680.0f, -100.0f, 0.0f, 0, 0, 0, 0x64);
    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    Actor_SetScale(&this->actor, 0.05f);
    SkelAnime_Init(globalCtx, &this->skelAnime1, &D_06011660, &D_060115E4, 0, 0, 0);
    SkelAnime_Init(globalCtx, &this->skelAnime2, &D_060115A0, &D_06011524, 0, 0, 0);
    SkelAnime_Init(globalCtx, &this->skelAnime3, &D_060114E0, &D_06011464, 0, 0, 0);
    this->unk_1402 = 1;
    if (this->unk_1402 == 0) {
        Audio_SetBGM(0x6B);
    }

    this->actor.posRot.pos.z = 0.0f;
    this->actor.posRot.pos.x = 0.0f;
    this->actor.posRot.pos.y = -200.0f;
    Collider_InitJntSph(globalCtx, &this->collider1);
    Collider_SetJntSph(globalCtx, &this->collider1, &this->actor, &sJntSphInit, this->colliderItems);
    
    for (i = 0; i < 100; i++) {
        this->unk_078C[i].x = this->actor.posRot.pos.x;
        this->unk_078C[i].y = this->actor.posRot.pos.y;
        this->unk_078C[i].z = this->actor.posRot.pos.z;
        if (i < 30) {
            this->unk_0E04[i].x = this->actor.posRot.pos.x;
            this->unk_0E04[i].y = this->actor.posRot.pos.y;
            this->unk_0E04[i].z = this->actor.posRot.pos.z;
        }
    }

    this->actor.colChkInfo.health = 0x18;
    this->unk_21E = 0x12;
    if (this->unk_1402 == 0) {
        this->actionFunc = func_808CDE30;
    } else {
        func_808CB6A8(this, globalCtx);
    }

    if (Flags_GetClear(globalCtx, globalCtx->roomCtx.curRoom.num) != 0) {
        Actor_Kill(&this->actor);
        Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_DOOR_WARP1, 0.0f, 100.0f, 0.0f, 0, 0, 0, -1);
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_ITEM_B_HEART, 0.0f, 100.0f, 200.0f, 0, 0, 0, 0);
        return;
    }

    Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_FD2, this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0, 0, 0, this->unk_1402);
}

void BossFd_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    BossFd *this = THIS;

    SkelAnime_Free(&this->skelAnime1, globalCtx);
    SkelAnime_Free(&this->skelAnime2, globalCtx);
    SkelAnime_Free(&this->skelAnime3, globalCtx);
    Collider_DestroyJntSph(globalCtx, &this->collider1);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CB67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CB6A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CB718.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CDE30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CE01C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CEC34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/BossFd_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CF448.s")

#ifdef NON_MATCHING
// gfxCtx on the stack
void func_808CF898(BossFdStruct1 *arg0, GlobalContext *globalCtx) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    u8 flag = 0;
    s16 i;
    BossFdStruct1* ptr = arg0;
    
    

    GraphicsContext* localGfxCtx = gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, localGfxCtx, "../z_boss_fd.c", 0xFB7);

    for (i = 0; i < 180; i++, ptr++) {
        if (ptr->unk_24 == 1) {
            if (flag == 0) {
                func_80093D84(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_0600A880);
                flag += 1;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, ptr->unk_26.r, ptr->unk_26.g, ptr->unk_26.b, ptr->unk_2A);
            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_Scale(ptr->unk_30, ptr->unk_30, 1.0f, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(gfxCtx, "../z_boss_fd.c", 0xFCE), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_0600A900);
        }
    }

    ptr = arg0;
    flag = 0;
    for (i = 0; i < 180; i++, ptr++) {
        if (ptr->unk_24 == 2) {
            if (flag == 0) {
                func_80093D18(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyOpa.p++, D_0600D3A0);
                flag += 1;
            }

            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            Matrix_RotateY(ptr->unk_38, 1);
            Matrix_RotateX(ptr->unk_34, 1);
            Matrix_Scale(ptr->unk_30, ptr->unk_30, 1.0f, 1);

            gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(gfxCtx, "../z_boss_fd.c", 0xFE4), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyOpa.p++, D_0600D420);
        }
    }

    ptr = arg0;
    flag = 0;
    for (i = 0; i < 180; i++, ptr++) {
        if (ptr->unk_24 == 3) {
            if (flag == 0) {
                gfxCtx->polyXlu.p = Gfx_CallSetupDL(gfxCtx->polyXlu.p, 0);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_0600B3A8);
                gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x5A, 0x1E, 0x00, 0xFF);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x5A, 0x1E, 0x00, 0x00);
                flag += 1;
            }

            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            Matrix_Scale(ptr->unk_30, ptr->unk_30, ptr->unk_30, 1);
            func_800D1FD4(&globalCtx->mf_11DA0);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(gfxCtx, "../z_boss_fd.c", 0x1008), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPSegment(gfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_808D1A9C[ptr->unk_2C]));
            gSPDisplayList(gfxCtx->polyXlu.p++, D_0600B3C8);
        }
    }

    ptr = arg0;
    flag = 0;
    for (i = 0; i < 180; i++, ptr++) {
        if (ptr->unk_24 == 4) {
            if (flag == 0) {
                gfxCtx->polyXlu.p = Gfx_CallSetupDL(gfxCtx->polyXlu.p, 0);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_0600B3A8);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0x0A, 0x00, 0xFF);
                flag += 1;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0x00, ptr->unk_2A);
            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            Matrix_Scale(ptr->unk_30, ptr->unk_30, ptr->unk_30, 1);
            func_800D1FD4(&globalCtx->mf_11DA0);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(gfxCtx, "../z_boss_fd.c", 0x103A), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPSegment(gfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_808D1A9C[ptr->unk_2C]));
            gSPDisplayList(gfxCtx->polyXlu.p++, D_0600B3C8);
        }
    }

    ptr = arg0;
    flag = 0;
    for (i = 0; i < 180; i++, ptr++) {
        if (ptr->unk_24 == 5) {
            if (flag == 0) {
                func_80093D84(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_0600D668);
                flag += 1;
            }

            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            Matrix_RotateY(ptr->unk_38, 1);
            Matrix_RotateX(ptr->unk_34, 1);
            Matrix_Scale(ptr->unk_30, ptr->unk_30, 1.0f, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(gfxCtx, "../z_boss_fd.c", 0x1060), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_0600D6E8);
        }
    }

    Graph_CloseDisps(dispRefs, localGfxCtx, "../z_boss_fd.c", 0x1066);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808CF898.s")
#endif

void BossFd_Draw(Actor *thisx, GlobalContext *globalCtx) {
    BossFd *this = THIS;
    s32 pad;

    osSyncPrintf("FD DRAW START\n");
    if (this->actionFunc != func_808CDE30) {
        GraphicsContext *gfxCtx = globalCtx->state.gfxCtx;
        Gfx *dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_fd.c", 0x1079);
        func_80093D18(globalCtx->state.gfxCtx);
        if (this->unk_230 & 2) {
            gfxCtx->polyOpa.p = Gfx_SetFog(gfxCtx->polyOpa.p, 0xFF, 0xFF, 0xFF, 0, 0x384, 0x44B);
        }

        func_808D08F8(globalCtx, this);
        gfxCtx->polyOpa.p = func_800BC8A0(globalCtx, gfxCtx->polyOpa.p);
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_fd.c", 0x1093);
    }

    osSyncPrintf("FD DRAW END\n");
    func_808CF898(this->unk_1970, globalCtx);
    osSyncPrintf("FD DRAW END2\n");
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808D00A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808D01C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808D02DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808D07A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Fd/func_808D08A4.s")

s32 func_808D00A4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor)
s32 func_808D01C0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor)
s32 func_808D07A4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor)

void func_808D08F8(GlobalContext *globalCtx, BossFd *this) {
    s16 idx;
    f32 tmpf1;
    Vec3f spB0;
    Vec3f spA4;

    Mtx* mat = Graph_Alloc(globalCtx->state.gfxCtx, 18 * sizeof(Mtx));
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_fd.c", 0x11ED);
    if (this->unk_230 != 0) {
        gSPSegment(gfxCtx->polyOpa.p++, 0x09, SEGMENTED_TO_VIRTUAL(D_808D1BB8[this->unk_2D5]));
    }

    gSPSegment(gfxCtx->polyOpa.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
        this->unk254, this->unk258, 0x20, 0x20, 1, this->unk25C, this->unk260, 0x20, 0x20));
    gDPSetPrimColor(gfxCtx->polyOpa.p++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPSetEnvColor(gfxCtx->polyOpa.p++, 0xFF, 0xFF, 0xFF, this->unk270);

    osSyncPrintf("LH\n");
    Matrix_Push();
    idx = D_808D1AC4[this->unk_228] % 0x64;
    Matrix_Translate(this->unk_0E04[idx].x, this->unk_0E04[idx].y, this->unk_0E04[idx].z, 0);
    Matrix_RotateY(this->unk_078C[idx].y, 1);
    Matrix_RotateX(-this->unk_078C[idx].x, 1);
    Matrix_Translate(-13.0f, -5.0f, 13.0f, 1);
    Matrix_Scale(this->actor.scale.x * 0.1f, this->actor.scale.y * 0.1f, this->actor.scale.z * 0.1f, 1);
    SkelAnime_Draw(globalCtx, this->skelAnime2.skeleton, this->skelAnime2.limbDrawTbl, func_808D00A4, 0, &this->actor);
    Matrix_Pull();
    osSyncPrintf("RH\n");
    Matrix_Push();
    idx = D_808D1AC4[this->unk_228] % 0x64;
    Matrix_Translate(this->unk_0E04[idx].x, this->unk_0E04[idx].y, this->unk_0E04[idx].z, 0);
    Matrix_RotateY(this->unk_078C[idx].y, 1);
    Matrix_RotateX(-this->unk_078C[idx].x, 1);
    Matrix_Translate(13.0f, -5.0f, 13.0f, 1);
    Matrix_Scale(this->actor.scale.x * 0.1f, this->actor.scale.y * 0.1f, this->actor.scale.z * 0.1f, 1);
    SkelAnime_Draw(globalCtx, this->skelAnime3.skeleton, this->skelAnime3.limbDrawTbl, func_808D01C0, 0, &this->actor);
    Matrix_Pull();
    osSyncPrintf("BD\n");

    gSPSegment(gfxCtx->polyOpa.p++, 0x0D, mat);
    Matrix_Push();

    for (i = 0; i < 18; i++) {
        idx = (D_808D1AC2[i] + this->unk_228) % 0x64;
        Matrix_Translate(this->unk_0E04[idx].x, this->unk_0E04[idx].y, this->unk_0E04[idx].z, 0);
        Matrix_RotateY(this->unk_078C[idx].y, 1);
        Matrix_RotateX(-this->unk_078C[idx].z, 1);
        Matrix_Translate(0.0f, 0.0f, 35.0f, 1);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1);
        if (i < this->unk_230) {
            Matrix_Scale((this->unk280 * Math_Sins((this->unk_228 * 5000.0f) + (i * 7000.0f))) + 1.0f, (this->unk280 * Math_Sins((this->unk_228 * 5000.0f) + (i * 7000.0f))) + 1.0f, 1.0f, 1);
            Matrix_RotateY(1.5707964f, 1);
            Matrix_ToMtx(mat, "../z_boss_fd.c", 0x126F);

            gSPMatrix(gfxCtx->polyOpa.p++, mat, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyOpa.p++, D_808D1BC4[i]);
        } else {
            Vec3f spFC;
            Vec3f spF0 = D_808D1C0C;
            Vec3f spE4;
            Vec3s spDC;
            f32 spD4;
            Actor* actorBall;

            if (this->unk_13D0[i] < 2) {
                spD4 = 0.1f;
                Matrix_Translate(0.0f, 0.0f, -1100.0f, 1);
                Matrix_RotateY(-M_PI, 1);
                if (i >= 14) {
                    Matrix_Scale(1.0f - ((i - 14) * 0.2f), 1.0f - ((pi - 14) * 0.2f), 1.0f, 1);
                    spD4 = 0.1f * (i * 2);
                }

                Matrix_Scale(0.1f, 0.1f, 0.1f, 1);
                gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_fd.c", 0x12A0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gfxCtx->polyOpa.p++, D_0600B2F8);
                if (temp_s2->unk13D0 == 1) {
                    temp_s2->unk13D0 = 2;
                    Matrix_MultVec3f(&spF0, &spE4);
                    Matrix_Get(&spFC);
                    func_800D20CC(&spFC, &spDC, 0);
                    actorBall = Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_VB_BALL, spE4, spE8, spEC, spDC, spDE, spE0, phi_s1 + 0xC8);
                    actorBall->actor.scale.x *= spD4;
                    actorBall->actor.scale.y *= spD4;
                    actorBall->actor.scale.z *= 0.1f;
                }
            }
        }

        if (i > 0) {
            func_800628A4(i + 1, &this->collider1);
        }
    }

    Matrix_Pull();
    osSyncPrintf("BH\n");

    gDPPipeSync(gfxCtx->polyOpa.p++);
    gDPSetEnvColor(gfxCtx->polyOpa.p++, 0xFF, 0xFF, 0xFF, this->unk_274);

    Matrix_Push();
    if (this->unk_222 >= 0xCC) {
        tmpf1 = -20.0f;
    } else {
        tmpf1 = -10.0f - ((this->actor.speedXZ - 5.0f) * 10.0f);
    }

    idx = D_808D1AC0[this->unk_228] % 0x64;
    Matrix_Translate(this->unk_0E04[idx].x, this->unk_0E04[idx].y, this->unk_0E04[idx].z, 0);
    Matrix_RotateY(this->unk_078C[idx].y, 1);
    Matrix_RotateX(-this->unk_078C[idx].x, 1);
    Matrix_RotateZ((this->actor.shape.rot.z / 32768.0f) * 3.1415927f, 1);
    Matrix_Translate(0.0f, 0.0f, tmpf1, 1);
    Matrix_Push();
    Matrix_Translate(0.0f, 0.0f, 25.0f, 1);
    osSyncPrintf("BHC\n");
    func_800628A4(0, sp7C);
    Matrix_Pull();
    osSyncPrintf("BHCE\n");
    Matrix_Scale(this->actor.scale.x * 0.1f, this->actor.scale.y * 0.1f, this->actor.scale.z * 0.1f, 1);
    SkelAnime_Draw(globalCtx, this->skelAnime1.skeleton, this->skelAnime1.limbDrawTbl, func_808D07A4, &func_808D08A4, &this->actor);
    osSyncPrintf("SK\n");
    spB0 = D_808D1C18;
    spA4 = D_808D1C24;
    func_80093D84(globalCtx->state.gfxCtx);

    gSPDisplayList(gfxCtx->polyOpa.p++, 0x06009168);
    gDPSetPrimColor(gfxCtx->polyOpa.p++, 0, 0, 0xFF, this->unk_284, 0x00, 0xFF);

    Matrix_Push();
    Matrix_MultVec3f(&spB0, &this->unk_0E04[0x28]);
    temp_s0_2 = this + 0xC9C;
    func_808D02DC(globalCtx, this, this->unk_0E04, temp_s0_2, this + 0xF6C, 0);
    Matrix_Pull();
    temp_v1_3 = temp_s4->polyXlu.p;
    temp_s4->polyXlu.p = temp_v1_3 + 8;
    temp_v1_3->words.w0 = 0xFA000000;
    temp_v1_3->words.w1 = (((this->unk288 & 0xFF) << 0x10) | 0xFF000000) | 0xFF;
    Matrix_Push();
    Matrix_MultVec3f(&spA4, this + 0x11D0);
    func_808D02DC(globalCtx, this, this + 0xFF0, temp_s0_2, this + 0x1158, 1);
    Matrix_Pull();
    temp_v1_4 = temp_s4->polyXlu.p;
    temp_s4->polyXlu.p = temp_v1_4 + 8;
    temp_v1_4->words.w0 = 0xFA000000;
    temp_v1_4->words.w1 = (((this->unk28C & 0xFF) << 0x10) | 0xFF000000) | 0xFF;
    Matrix_Push();
    temp_a0_2 = &spA4;
    spA4 = spA4 * -1.0f;
    Matrix_MultVec3f(temp_a0_2, this + 0x13BC);
    func_808D02DC(globalCtx, this, this + 0x11DC, temp_s0_2, this + 0x1344, 2);
    Matrix_Pull();
    Matrix_Pull();
    osSyncPrintf("END\n");
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_fd.c", 0x137B);
}
