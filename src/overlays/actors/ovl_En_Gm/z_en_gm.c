/*
 * File: z_en_gm.c
 * Overlay: ovl_En_Gm
 * Description: Medigoron
 */

#include "z_en_gm.h"
#include "vt.h"

#define FLAGS 0x00000019

#define THIS ((EnGm*)thisx)

void EnGm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGm_Update(Actor* thisx, GlobalContext* globalCtx);
void func_80A3E1EC(Actor* thisx, GlobalContext* globalCtx);

void func_80A3D838(EnGm* this, GlobalContext* globalCtx);
void func_80A3DFBC(EnGm* this, GlobalContext* globalCtx);
void func_80A3DB04(EnGm* this, GlobalContext* globalCtx);
void func_80A3DC44(EnGm* this, GlobalContext* globalCtx);
void func_80A3DBF4(EnGm* this, GlobalContext* globalCtx);
void func_80A3DD7C(EnGm* this, GlobalContext* globalCtx);
void func_80A3DE10(EnGm* this, GlobalContext* globalCtx);
void func_80A3DF00(EnGm* this, GlobalContext* globalCtx);
void func_80A3DF60(EnGm* this, GlobalContext* globalCtx);

extern SkeletonHeader D_0600FEF0;
extern AnimationHeader D_060002B8;
extern UNK_TYPE D_0600DE80;

const ActorInit En_Gm_InitVars = {
    ACTOR_EN_GM,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnGm),
    (ActorFunc)EnGm_Init,
    (ActorFunc)EnGm_Destroy,
    (ActorFunc)EnGm_Update,
    NULL,
};

static ColliderCylinderInit_Set3 sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 100, 120, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(unk_1F, 5, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 30, ICHAIN_STOP),
};

void EnGm_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGm* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    osSyncPrintf(VT_FGCOL(GREEN) "%s[%d] : 中ゴロン[%d]" VT_RST "\n", "../z_en_gm.c", 0x85, this->actor.params);
    this->unk_2BC = Object_GetIndex(&globalCtx->objectCtx, 0x126);
    if (this->unk_2BC < 0) {
        osSyncPrintf(VT_COL(RED, WHITE));
        // No model bank! (middle Goron)
        osSyncPrintf("モデル バンクが無いよ！！（中ゴロン）\n");
        osSyncPrintf(VT_RST);
        __assert("0", "../z_en_gm.c", 0x91);
    }

    this->unk_268 = func_80A3D838;
}

void EnGm_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGm* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

s32 func_80A3D7C8(void) {
    if (LINK_AGE_IN_YEARS == YEARS_CHILD) {
        return 0;
    }

    if (!(gBitFlags[2] & gSaveContext.equipment)) {
        return 1;
    }

    if ((gBitFlags[3] & gSaveContext.equipment)) {
        return 2;
    }

    return 3;
}

void func_80A3D838(EnGm* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_2BC) != 0) {
        this->actor.flags &= ~0x10;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600FEF0, NULL, this->limbDrawTable, this->transitionDrawTable,
                         18);
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_2BC].segment);
        SkelAnime_ChangeAnim(&this->skelAnime, &D_060002B8, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_060002B8.genericHeader), 0, 0.0f);
        this->actor.draw = func_80A3E1EC;
        Collider_InitCylinder(globalCtx, &this->collider);
        Collider_SetCylinder_Set3(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 35.0f);
        Actor_SetScale(&this->actor, 0.05f);
        this->actor.colChkInfo.mass = 0xFF;
        this->unk_2C2 = 0;
        this->unk_2C0 = 20;
        this->actor.textId = 0x3049;
        this->unk_268 = func_80A3DFBC;
        this->unk_26C = func_80A3DB04;
        this->actor.speedXZ = 0.0f;
        this->actor.gravity = -1.0f;
        this->actor.velocity.y = 0.0f;
    }
}

void func_80A3D9D8(EnGm* this) {
    if (this->unk_2C0 != 0) {
        this->unk_2C0--;
        return;
    }

    this->unk_2C2++;
    if (this->unk_2C2 >= 3) {
        this->unk_2C2 = 0;
        this->unk_2C0 = Math_Rand_ZeroFloat(60.0f) + 20.0f;
    }
}

void func_80A3DA50(EnGm* this) {
    switch (func_80A3D7C8()) {
        case 0:
            if (gSaveContext.infTable[11] & 1) {
                this->actor.textId = 0x304B;
            } else {
                this->actor.textId = 0x304A;
            }
            break;

        case 1:
            if (gSaveContext.infTable[11] & 2) {
                this->actor.textId = 0x304F;
            } else {
                this->actor.textId = 0x304C;
            }
            break;

        case 2:
            this->actor.textId = 0x304E;
            break;

        case 3:
            this->actor.textId = 0x304D;
            break;
    }
}

void func_80A3DB04(EnGm* this, GlobalContext* globalCtx) {
    f32 sp24 = this->unk_2C4.x - PLAYER->actor.posRot.pos.x;
    f32 sp20 = this->unk_2C4.z - PLAYER->actor.posRot.pos.z;

    if (Flags_GetSwitch(globalCtx, this->actor.params)) {
        func_80A3DA50(this);
        this->unk_26C = func_80A3DC44;
    } else if (func_8002F194(&this->actor, globalCtx)) {
        this->unk_26C = func_80A3DBF4;
    } else if ((this->collider.base.maskA & 2) || ((SQ(sp24) + SQ(sp20)) < 10000.0f)) {
        this->collider.base.acFlags &= ~2;
        func_8002F2CC(&this->actor, globalCtx, 415.0f);
    }
}

void func_80A3DBF4(EnGm* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 6) && (func_80106BC8(globalCtx) != 0)) {
        this->unk_26C = func_80A3DB04;
    }
}

void func_80A3DC44(EnGm* this, GlobalContext* globalCtx) {
    f32 sp24;
    f32 sp20;
    s32 pad;
    Player* player = PLAYER;

    func_80A3DA50(this);
    sp24 = this->unk_2C4.x - player->actor.posRot.pos.x;
    sp20 = this->unk_2C4.z - player->actor.posRot.pos.z;
    if (func_8002F194(&this->actor, globalCtx) != 0) {
        switch (func_80A3D7C8()) {
            case 0:
                gSaveContext.infTable[11] |= 1;

            case 3:
                this->unk_26C = func_80A3DD7C;
                break;

            case 1:
                gSaveContext.infTable[11] |= 2;

            case 2:
                this->unk_26C = func_80A3DE10;
                break;
        }
    } else if ((this->collider.base.maskA & 2) || ((SQ(sp24) + SQ(sp20)) < 10000.0f)) {
        this->collider.base.acFlags &= ~2;
        func_8002F2CC(&this->actor, globalCtx, 415.0f);
    }
}

void func_80A3DD7C(EnGm* this, GlobalContext* globalCtx) {
    u8 sp1F = func_8010BDBC(&globalCtx->msgCtx);
    ;

    if (((sp1F == 6) || (sp1F == 5)) && (func_80106BC8(globalCtx) != 0)) {
        this->unk_26C = func_80A3DC44;
        if (sp1F == 5) {
            globalCtx->msgCtx.msgMode = 0x36;
            globalCtx->msgCtx.unk_E3E7 = 4;
        }
    }
}

void func_80A3DE10(EnGm* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 4) && (func_80106BC8(globalCtx) != 0)) {
        switch (globalCtx->msgCtx.choiceIndex) {
            case 0:
                if (gSaveContext.rupees < 200) {
                    func_8010B720(globalCtx, 200);
                    this->unk_26C = func_80A3DD7C;
                } else {
                    func_8002F434(&this->actor, globalCtx, 0x28, 415.0f, 10.0f);
                    this->unk_26C = func_80A3DF00;
                }
                break;

            case 1:
                func_8010B720(globalCtx, 0x3050);
                this->unk_26C = func_80A3DD7C;
                break;
        }
    }
}

void func_80A3DF00(EnGm* this, GlobalContext* globalCtx) {
    if (func_8002F410(&this->actor, globalCtx) != 0) {
        this->actor.attachedA = NULL;
        this->unk_26C = func_80A3DF60;
    } else {
        func_8002F434(&this->actor, globalCtx, 0x28, 415.0f, 10.0f);
    }
}

void func_80A3DF60(EnGm* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 6) && (func_80106BC8(globalCtx) != 0)) {
        Rupees_ChangeBy(-200);
        this->unk_26C = func_80A3DC44;
    }
}

void func_80A3DFBC(EnGm* this, GlobalContext* globalCtx) {
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_2BC].segment);
    this->unk_2BE++;
    this->unk_26C(this, globalCtx);
    this->actor.posRot2.rot.x = this->actor.posRot.rot.x;
    this->actor.posRot2.rot.y = this->actor.posRot.rot.y;
    this->actor.posRot2.rot.z = this->actor.posRot.rot.z;
    func_80A3D9D8(this);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnGm_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGm* this = THIS;
    this->unk_268(this, globalCtx);
}

void func_80A3E090(EnGm* this) {
    Vec3f sp34;
    Vec3f sp28;

    Matrix_Push();
    Matrix_Translate(0.0f, 0.0f, 2600.0f, MTXMODE_APPLY);
    Matrix_RotateRPY(this->actor.posRot.rot.x, this->actor.posRot.rot.y, this->actor.posRot.rot.z, MTXMODE_APPLY);
    sp34.x = sp34.y = sp34.z = 0.0f;
    Matrix_MultVec3f(&sp34, &sp28);
    this->collider.dim.pos.x = sp28.x;
    this->collider.dim.pos.y = sp28.y;
    this->collider.dim.pos.z = sp28.z;
    Matrix_Pull();
    Matrix_Push();
    Matrix_Translate(0.0f, 0.0f, 4300.0f, MTXMODE_APPLY);
    Matrix_RotateRPY(this->actor.posRot.rot.x, this->actor.posRot.rot.y, this->actor.posRot.rot.z, MTXMODE_APPLY);
    sp34.x = sp34.y = sp34.z = 0.0f;
    Matrix_MultVec3f(&sp34, &this->unk_2C4);
    Matrix_Pull();
    Matrix_Translate(0.0f, 0.0f, 3800.0f, MTXMODE_APPLY);
    Matrix_RotateRPY(this->actor.posRot.rot.x, this->actor.posRot.rot.y, this->actor.posRot.rot.z, MTXMODE_APPLY);
    sp34.x = sp34.y = sp34.z = 0.0f;
    Matrix_MultVec3f(&sp34, &this->actor.posRot2.pos);
    this->actor.posRot2.pos.y += 100.0f;
}

void func_80A3E1EC(Actor* thisx, GlobalContext* globalCtx) {
    static UNK_TYPE D_80A3E384[] = { 0x0600CE80, 0x0600D280, 0x0600D680 };

    EnGm* this = THIS;
    s32 pad;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_gm.c", 613);
    func_80093D18(globalCtx->state.gfxCtx);
    gSPSegment(gfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A3E384[this->unk_2C2]));
    gSPSegment(gfxCtx->polyOpa.p++, 0x09, SEGMENTED_TO_VIRTUAL(&D_0600DE80));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL,
                     NULL, &this->actor);
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_gm.c", 629);
    func_80A3E090(this);
}
