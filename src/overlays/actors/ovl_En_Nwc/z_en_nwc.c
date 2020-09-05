/*
 * File: z_en_nwc.c
 * Overlay: ovl_En_Nwc
 * Description: Cucco Chick
 */

#include "z_en_nwc.h"

#define FLAGS 0x00000030

#define THIS ((EnNwc*)thisx)

void EnNwc_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNwc_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNwc_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNwc_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80ABC9D0(EnNwc* this, GlobalContext* globalCtx);

extern Gfx D_06000840[];
extern Gfx D_06000BF0[];
extern Gfx D_06000C88[];
extern Gfx D_060008B0[];
extern Gfx D_06000C68[];
extern Gfx D_06000CE0[];
extern Gfx D_06000D10[];
extern Gfx D_06000D50[];

const ActorInit En_Nwc_InitVars = {
    ACTOR_EN_NWC,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_NWC,
    sizeof(EnNwc),
    (ActorFunc)EnNwc_Init,
    (ActorFunc)EnNwc_Destroy,
    (ActorFunc)EnNwc_Update,
    (ActorFunc)EnNwc_Draw,
};

static ColliderJntSphItemInit sJntSphItemsInit = {
    { 0x01, { 0x00000000, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x01, 0x00 },
    { 0, { { 0, 0, 0 }, 10 }, 100 },
};

static ColliderJntSphInit_Set3 sJntSphInit = {
    { COLTYPE_UNK3, 0x00, 0x09, 0x39, COLSHAPE_JNTSPH },
    16,
    NULL,
};

void func_80ABC0E0(EnNwc* this, EnNwcActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void func_80ABC0E8(EnNwcStruct1* ptr, EnNwc* this, GlobalContext* globalCtx) {
}

void func_80ABC0F8(EnNwcStruct1* ptr, GlobalContext* globalCtx) {
    CollisionPoly* sp4C;
    s32 sp48;
    Vec3f sp3C;
    f32 tmp;

    ptr->unk_01 &= ~3;
    sp3C.x = ptr->unk_08.x;
    sp3C.y = ptr->unk_08.y;
    sp3C.z = ptr->unk_08.z;
    if (func_8003D464(&globalCtx->colCtx, &sp3C, &ptr->unk_08, &ptr->unk_1C, 10.0f, &ptr->unk_38, 20.0f) != 0) {
        ptr->unk_01 |= 2;
    }

    ptr->unk_04 = func_8003C940(&globalCtx->colCtx, &sp4C, &sp48, &sp3C);
    tmp = ptr->unk_04 - ptr->unk_08.y;
    if ((tmp >= 0.0f) && (tmp < 40.0f)) {
        ptr->unk_01 |= 1;
        ptr->unk_08.y = ptr->unk_04;
    }
}

void func_80ABC1F4(EnNwcStruct1* ptr, EnNwc* this, GlobalContext* globalCtx) {
    ptr->unk_2C -= 0.1f;
    if (ptr->unk_2C < -10.0f) {
        ptr->unk_2C = -10.0f;
    }
    ptr->unk_08.y += ptr->unk_2C;
    func_80ABC0F8(ptr, globalCtx);
    if (ptr) {};
}

void func_80ABC260(EnNwc* this, GlobalContext* globalCtx) {
    static EnNwcFunc D_80ABCAB4[] = {
        func_80ABC0E8,
        func_80ABC1F4,
    };

    ColliderJntSphItem* sphItem = &this->collider.list[0];
    EnNwcStruct1* ptr = &this->unk_170[0];
    Vec3f sp7C;
    f32 tmpf1;
    f32 tmpf2;
    f32 tmpf3;
    s32 i;

    sp7C.y = 99999.9f;

    for (i = 0; i < this->unk_16C; i++, ptr++, sphItem++) {
        Math_Vec3f_Copy(&ptr->unk_1C, &ptr->unk_08);
        D_80ABCAB4[ptr->unk_00](ptr, this, globalCtx);
        sphItem->dim.worldSphere.center.x = ptr->unk_08.x;
        sphItem->dim.worldSphere.center.y = ptr->unk_08.y;
        sphItem->dim.worldSphere.center.z = ptr->unk_08.z;
        tmpf3 = ptr->unk_08.y - sp7C.y;
        if (fabsf(tmpf3) < 10.0f) {
            tmpf1 = ptr->unk_08.x - sp7C.x;
            tmpf2 = ptr->unk_08.z - sp7C.z;
            tmpf3 = SQ(tmpf1) + SQ(tmpf2);
            if (tmpf3 < 100.0f) {
                if (tmpf3 != 0.0f) {
                    ptr->unk_08.x += tmpf1 / sqrtf(tmpf3);
                    ptr->unk_08.z += tmpf2 / sqrtf(tmpf3);
                } else {
                    ptr->unk_08.x += 1.0f;
                    ptr->unk_08.z += 1.0f;
                }
            }
        }
        sp7C = ptr->unk_08;
    }
}

#ifdef NON_MATCHING
// i and ptr assignments out of order for the second loop
void func_80ABC460(EnNwc* this, GlobalContext* globalCtx) {
    EnNwcStruct1* ptr;
    Gfx* base;
    Gfx* gfx2;
    Gfx* gfx3;
    MtxF spB0;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_nwc.c", 316);
    func_80093C80(globalCtx);

    base = oGfxCtx->polyXlu.p;
    gfx2 = (base + (this->unk_16C * 3)) + 1;
    gfx3 = (gfx2 + (this->unk_16C * 2)) + 1;

    gSPDisplayList(base++, D_06000BF0);
    gSPDisplayList(gfx2++, D_06000840);
    gSPDisplayList(gfx3++, D_06000C88);

    for (i = 0, ptr = &this->unk_170[0]; i < this->unk_16C; i++, ptr++) {
        Mtx* matrix;

        if (ptr->unk_00 != 0) {
            func_800D1694(ptr->unk_08.x, ptr->unk_08.y + ptr->unk_36, ptr->unk_08.z, &ptr->unk_30);
            Matrix_Scale(0.01f, 0.01f, 0.01f, 1);

            matrix = Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_nwc.c", 346);

            gDPSetEnvColor(base++, 0, 100, 255, 255);
            gSPMatrix(base++, matrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(base++, D_060008B0);

            gSPMatrix(gfx2++, matrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx2++, D_06000C68);

            gSPMatrix(gfx3++, matrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx3++, D_06000CE0);
        }
    }

    oGfxCtx->polyXlu.p = gfx3;
    func_80094044(globalCtx->state.gfxCtx);
    gSPDisplayList(oGfxCtx->polyXlu.p++, D_06000D10);

    ptr = &this->unk_170[0];
    for (i = 0; i < this->unk_16C; i++, ptr++) {
        if ((ptr->unk_00 != 0) && (ptr->unk_38 != 0)) {
            func_80038A28(ptr->unk_38, ptr->unk_08.x, ptr->unk_04, ptr->unk_08.z, &spB0);
            Matrix_Put(&spB0);
            Matrix_RotateY(ptr->unk_30.y * 0.0000958738f, 1);
            Matrix_Scale(1.0f, 1.0f, 1.0f, 1);

            gSPMatrix(oGfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_nwc.c", 388),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(oGfxCtx->polyXlu.p++, D_06000D50);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_nwc.c", 395);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Nwc/func_80ABC460.s")
#endif

void EnNwc_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnNwc* this = THIS;
    s32 pad;
    ColliderJntSphItemInit sp58[16];
    ColliderJntSphItemInit* itemInitPtr;
    EnNwcStruct1* ptr;
    s32 i;

    sJntSphInit.list = sp58;
    itemInitPtr = sJntSphInit.list;
    for (i = 0; i < 16; i++, itemInitPtr++) {
        *itemInitPtr = sJntSphItemsInit;
    }

    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph_Set3(globalCtx, &this->collider, &this->actor, &sJntSphInit);

    this->unk_16C = 16;
    ptr = this->unk_170;
    for (i = 0; i < this->unk_16C; i++, ptr++) {
        ptr->unk_00 = 1;
        ptr->unk_08.x = ((Math_Rand_ZeroOne() * 100.0f) - 50.0f) + thisx->posRot.pos.x;
        ptr->unk_08.y = thisx->posRot.pos.y + 20.0f;
        ptr->unk_08.z = ((Math_Rand_ZeroOne() * 100.0f) - 50.0f) + thisx->posRot.pos.z;
        ptr->unk_36 = 5;
    }
    func_80ABC0E0(this, func_80ABC9D0);
}

void EnNwc_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnNwc* this = THIS;

    Collider_FreeJntSph(globalCtx, &this->collider);
}

void func_80ABC9D0(EnNwc* this, GlobalContext* globalCtx) {
    func_80ABC260(this, globalCtx);
}

void EnNwc_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnNwc* this = THIS;

    this->actionFunc(this, globalCtx);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnNwc_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnNwc* this = THIS;

    func_80ABC460(this, globalCtx);
}
