#include "z_en_fd.h"

#define FLAGS 0x00000215

#define THIS ((EnFd*)thisx)

void EnFd_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFd_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFd_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A0D40C(EnFd* this, u8 arg1, Vec3f* arg2, Vec3f* arg3, Vec3f* arg4, u8 arg5, f32 arg6, f32 arg7);

void func_80A0C310(EnFd* this, GlobalContext* globalCtx);
void func_80A0DB44(EnFd* this, GlobalContext* globalCtx);
void func_80A0D730(EnFd* this, GlobalContext* globalCtx);
void func_80A0C3A0(EnFd* this, GlobalContext* globalCtx);


extern SkeletonHeader D_06005810;
extern Gfx D_060079F8[];
extern Gfx D_06007A78[];

const ActorInit En_Fd_InitVars = {
    ACTOR_EN_FD,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_FW,
    sizeof(EnFd),
    (ActorFunc)EnFd_Init,
    (ActorFunc)EnFd_Destroy,
    (ActorFunc)EnFd_Update,
    (ActorFunc)EnFd_Draw,
};

static ColliderJntSphItemInit sJntSphItemsInit[12] = {
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040088, 0x00, 0x00 }, 0x01, 0x05, 0x01 },
        { 21, { { 1600, 0, 0 }, 5 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 12, { { 1600, 0, 0 }, 5 }, 400 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 14, { { 800, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 15, { { 1600, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 16, { { 2000, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 17, { { 800, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 18, { { 1600, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 19, { { 2000, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 4, { { 2200, 0, 0 }, 4 }, 400 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 4, { { 5000, 0, 0 }, 4 }, 300 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 8, { { 2200, 0, 0 }, 4 }, 400 },
    },
    {
        { 0x00, { 0xFFCFFFFF, 0x01, 0x04 }, { 0x00040008, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
        { 8, { { 5000, 0, 0 }, 4 }, 300 },
    },
};

static ColliderJntSphInit sJntSphInit =
{
    { COLTYPE_UNK10, 0x11, 0x09, 0x39, 0x10, COLSHAPE_JNTSPH },
    12, sJntSphItemsInit,
};

CollisionCheckInfoInit2 D_80A0DFE0 = {
    0x18, 0x0002, 0x0019, 0x0019, 0xFF
};

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0B6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0B7B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0B8D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0BA44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0BAE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0BC70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0BD78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0BE34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0BEA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0BF6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0C0A0.s")

void EnFd_Init(Actor* thisx, GlobalContext *globalCtx) {
    EnFd *this = THIS;

    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06005810, NULL, this->limbDrawTable, this->transitionDrawTable, 27);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 32.0f);
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderItems);
    func_80061EFC(&this->actor.colChkInfo, DamageTable_Get(15), &D_80A0DFE0);
    this->actor.flags &= ~1;
    this->actor.flags |= 0x1000000;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_4BC = 1;
    this->actor.gravity = -1.0f;
    this->unk_4BA = (Math_Rand_ZeroOne() < 0.5f) ? -1 : 1;
    this->actor.naviEnemyId = 0x22;
    this->actionFunc = func_80A0C310;
}

void EnFd_Destroy(Actor* thisx, GlobalContext *globalCtx) {
    EnFd *this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80A0C310(EnFd *this, GlobalContext *globalCtx) {
    static struct_80034EC0_Entry D_80A0DFEC[] = {
        {0x060010B4, 1.0f, 0.0f, -1.0f, 0x03, 0.0f}, 
        {0x06005C64, 1.0f, 0.0f, -1.0f, 0x03, -10.0f}, 
        {0x06006044, 0.0f, 0.0f, -1.0f, 0x03, -10.0f}, 
        {0x06006A18, 1.0f, 0.0f, -1.0f, 0x01, -10.0f},
        {0x06006B64, 0.0f, 0.0f, -1.0f, 0x03, -10.0f}
    };

    this->actor.posRot.pos = this->actor.initPosRot.pos;
    this->actor.params = 0;
    this->actor.shape.unk_14 = 0xFF;
    this->unk_4B4 = 0;
    this->actor.scale.y = 0.0f;
    this->unk_4CC = 255.0f;
    func_80034EC0(&this->skelAnime, D_80A0DFEC, 0);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLAME_LAUGH);
    this->actionFunc = func_80A0C3A0;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0C3A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0C474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0C4F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0C5D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0C7EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0CA44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/EnFd_Update.s")

s32 func_80A0CCB8(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor* thisx, Gfx **gfx) {
    EnFd *this = THIS;

    if ((this->unk_4C2 != 0) &&
       ((limbIndex == 13) || (limbIndex == 21))) {
        *dList = NULL;
    }

    return 0;
}

void func_80A0CCF0(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx, Gfx **gfx) {
    EnFd* this = THIS;
    Vec3f spC0 = { 6800.0f, 0.0f, 0.0f };
    Vec3f spB4 = { 6800.0f, 0.0f, 0.0f };
    Vec3f spA8 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp9C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp90 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp84 = { 0.0f, 0.0f, 0.0f };
    s32 i;

    if (limbIndex == 21) {
        Matrix_MultVec3f(&spA8, &this->unk_4D0);
    }

    if (limbIndex == 13) {
        Matrix_MultVec3f(&spA8, &this->actor.posRot2.pos);
    }

    if ((limbIndex == 3) || (limbIndex == 6) || (limbIndex == 7) || 
        (limbIndex == 0xA) || (limbIndex == 0xE) || (limbIndex == 0xF) || 
        (limbIndex == 0x11) || (limbIndex == 0x12) || (limbIndex == 0x14) || 
        (limbIndex == 0x16) || (limbIndex == 0x17) || (limbIndex == 0x18) || 
        (limbIndex == 0x19) || (limbIndex == 0x1A)) {
        if ((globalCtx->state.frames & 1) != 0) {
            for (i = 0; i < 1; i++) {
                Matrix_MultVec3f(&spA8, &sp9C);
                sp9C.x += (Math_Rand_ZeroOne() - 0.5f) * 20.0f;
                sp9C.y += (Math_Rand_ZeroOne() - 0.5f) * 40.0f;
                sp9C.z += (Math_Rand_ZeroOne() - 0.5f) * 20.0f;
                sp90.x = (Math_Rand_ZeroOne() - 0.5f) * 0.4f;
                sp90.y = ((Math_Rand_ZeroOne() - 0.5f) * 0.2f) + 0.6f;
                sp90.z = (Math_Rand_ZeroOne() - 0.5f) * 0.4f;
                func_80A0D40C(this, 2, &sp9C, &sp84, &sp90, 0, 0.006f, 0.0f);
            }
        }
    }

    func_800628A4(limbIndex, &this->collider);
}

#ifdef NON_MATCHING
void EnFd_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnFd* this = THIS;
    Color_RGBA8_n sp8C[] = { {0xFF, 0xFF, 0xC8, 0xFF}, 
                             {0xC8, 0xC8, 0xC8, 0xFF}, 
                             {0xFF, 0xFF, 0x00, 0xFF},
                           };
    Color_RGBA8_n sp80[] = { {0x00, 0xFF, 0x00, 0xFF}, 
                             {0x00, 0x00, 0xFF, 0xFF}, 
                             {0xFF, 0x00, 0x00, 0xFF}, 
                           };

    u32 sp7C = globalCtx->state.frames;
    GraphicsContext* localGfxCtx = globalCtx->state.gfxCtx;
    s32 tmp;
    GraphicsContext *gfxCtx = localGfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, gfxCtx, "../z_en_fd.c", 0x6D7);
    Matrix_Push();
    func_80A0DB44(this, globalCtx);
    func_80A0D730(this, globalCtx);
    Matrix_Pull();
    if ((this->actionFunc != func_80A0C310) && !(this->unk_4CC < 0.9f)) {

        func_80093D84(globalCtx->state.gfxCtx);

        tmp = this->actor.colChkInfo.health - 1;
        tmp = CLAMP(tmp, 0, 0x17) / 8;

        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0x80, sp8C[tmp].r, sp8C[tmp].g, sp8C[tmp].b, (u8)this->unk_4CC);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, sp80[tmp].r, sp80[tmp].g, sp80[tmp].b, (u8)this->unk_4CC);

        gSPSegment(gfxCtx->polyXlu.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 
            0, 0, 
            0x20, 0x40, 1, 
            0, 255 - ((sp7C * 6) % 256), 
            8, 0x40));
        gDPPipeSync(gfxCtx->polyXlu.p++);
        gSPSegment(gfxCtx->polyXlu.p++, 0x09, D_80116280);

        gfxCtx->polyXlu.p = SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, func_80A0CCB8, func_80A0CCF0, &this->actor, gfxCtx->polyXlu.p);
    }

    Graph_CloseDisps(dispRefs, gfxCtx, "../z_en_fd.c", 0x71E);
}
#else
Color_RGBA8 D_80A0E0D0[] = {
    {0xFF, 0xFF, 0xC8, 0xFF},
    {0xC8, 0xC8, 0xC8, 0xFF},
    {0xFF, 0xFF, 0x00, 0xFF},
};
Color_RGBA8 D_80A0E0DC[] = {
    {0x00, 0xFF, 0x00, 0xFF},
    {0x00, 0x00, 0xFF, 0xFF},
    {0xFF, 0x00, 0x00, 0xFF},
};
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/EnFd_Draw.s")
#endif

void func_80A0D40C(EnFd *this, u8 arg1, Vec3f *arg2, Vec3f *arg3, Vec3f *arg4, u8 arg5, f32 arg6, f32 arg7) {
    EnFdStruct1 *ptr = this->unk_620;
    s16 i;

    for (i = 0; i < 200; i++, ptr++) {
        if (ptr->unk_00 == 0) {

            ptr->unk_04 = arg6;
            ptr->unk_08 = arg7;

            ptr->unk_01[1] = ptr->unk_01[0] = arg5;
            ptr->unk_00 = arg1;

            ptr->unk_14 = *arg2;
            ptr->unk_2C = *arg4;
            ptr->unk_20 = *arg3;

            if ((arg1 & 0xFF) == 2) {
                ptr->unk_0C.a = 0xFF;
                ptr->unk_01[0] = (s16)(Math_Rand_ZeroOne() * 10.0f);
            }
            break;
        }
    }
}


#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0D4FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0D614.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fd/func_80A0D730.s")

void func_80A0DB44(EnFd *this, GlobalContext *globalCtx) {
    EnFdStruct1* ptr = this->unk_620;
    s16 i;
    u8 flag;
    GraphicsContext *gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];
    

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fd.c", 0x7F2);

    flag = 0;
    func_80093D84(globalCtx->state.gfxCtx);

    for (i = 0; i < 200; i++, ptr++) {
        if (ptr->unk_00 == 2) {
            if (flag == 0) {
                func_80093D84(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_060079F8);
                flag = 1;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, ptr->unk_0C.r, ptr->unk_0C.g, ptr->unk_0C.b, ptr->unk_0C.a * (this->unk_4CC / 255.0f));
            gDPPipeSync(gfxCtx->polyXlu.p++);

            Matrix_Translate(ptr->unk_14.x, ptr->unk_14.y, ptr->unk_14.z, 0);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_Scale(ptr->unk_04, ptr->unk_04, 1.0f, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_fd.c", 0x810), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06007A78);
        }
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fd.c", 0x817);
}
