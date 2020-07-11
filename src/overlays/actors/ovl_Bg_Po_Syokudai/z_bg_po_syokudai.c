#include "z_bg_po_syokudai.h"

#define FLAGS 0x00000000

#define THIS ((BgPoSyokudai*)thisx)

void BgPoSyokudai_Init(Actor* thisx, GlobalContext* globalCtx);
void BgPoSyokudai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgPoSyokudai_Update(Actor* thisx, GlobalContext* globalCtx);
void BgPoSyokudai_Draw(Actor* thisx, GlobalContext* globalCtx);

extern Gfx D_0404D4E0[];
extern Gfx D_060003A0[];

const ActorInit Bg_Po_Syokudai_InitVars = {
    ACTOR_BG_PO_SYOKUDAI,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_SYOKUDAI,
    sizeof(BgPoSyokudai),
    (ActorFunc)BgPoSyokudai_Init,
    (ActorFunc)BgPoSyokudai_Destroy,
    (ActorFunc)BgPoSyokudai_Update,
    (ActorFunc)BgPoSyokudai_Draw,
};

ColliderCylinderInit D_808A8960 =
{
    { COLTYPE_METAL_SHIELD, 0x00, 0x0D, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x01, 0x01 },
    { 12, 60, 0, { 0, 0, 0 } },
};

u8 D_808A898C[][4] = {
    {0xFF, 0xAA, 0xFF, 0xFF}, 
    {0xFF, 0xC8, 0x00, 0xFF}, 
    {0x00, 0xAA, 0xFF, 0xFF}, 
    {0xAA, 0xFF, 0x00, 0xFF}
};

u8 D_808A899C[][4] = {
    {0x64, 0x00, 0xFF, 0xFF}, 
    {0xFF, 0x00, 0x00, 0xFF}, 
    {0x00, 0x00, 0xFF, 0xFF},
    {0x00, 0x96, 0x00, 0xFF}
};

InitChainEntry D_808A89CC[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

//#define A
#ifdef A
void BgPoSyokudai_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgPoSyokudai* this = THIS;
    s32 tmp;

    Actor_ProcessInitChain(&this->actor, D_808A89CC);
    this->unk_14C = (thisx->params & 0xFFFF) >> 8;
    this->actor.params &= 0x3F;
    this->actor.colChkInfo.mass = 0xFF;
    this->unk_150 = Lights_Insert(globalCtx, &globalCtx->lightCtx, &this->unk_154);
    Lights_InitType2PositionalLight(&this->unk_154, 
        this->actor.posRot.pos.x, 
        (s16)this->actor.posRot.pos.y + 0x41, 
        this->actor.posRot.pos.z, 
        0, 0, 0, 0);
    Collider_InitCylinder(globalCtx, &this->unk_164);
    Collider_SetCylinder(globalCtx, &this->unk_164, &this->actor, &D_808A8960);
    this->unk_164.dim.pos.x = thisx->posRot.pos.x;
    this->unk_164.dim.pos.y = thisx->posRot.pos.y;
    this->unk_164.dim.pos.z = this->actor.posRot.pos.z;

    if ((this->unk_14C == 0) && 
         Flags_GetSwitch(globalCtx, 0x1F) && 
         Flags_GetSwitch(globalCtx, 0x1E) && 
         Flags_GetSwitch(globalCtx, 0x1D) && 
        !Flags_GetSwitch(globalCtx, this->actor.params)) {
        
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_PO_SISTERS, 
            119.0f, 225.0f, -1566.0f, 0, 0, 0, thisx->params);
        globalCtx->envCtx.unk_BF = 4;
    } else {
        if (!Flags_GetSwitch(globalCtx, 0x1C) && 
            !Flags_GetSwitch(globalCtx, 0x1B)) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_PO_SISTERS, 
                thisx->posRot.pos.x, 
                thisx->posRot.pos.y + 52.0f, 
                thisx->posRot.pos.z, 
                0, 0, 0, 
                ((this->unk_14C << 8) + thisx->params) + 0x1000);
        } else {
            if (!Flags_GetSwitch(globalCtx, thisx->params)) {
                if (globalCtx->envCtx.unk_BF == 0xFF) {
                    globalCtx->envCtx.unk_BF = 4;
                }
            }
        }
    }
    this->unk_14E = Math_Rand_ZeroOne() * 20.0f;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Syokudai/BgPoSyokudai_Init.s")
#endif
#undef A

void BgPoSyokudai_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgPoSyokudai* this = THIS;

    Lights_Remove(globalCtx, &globalCtx->lightCtx, this->unk_150);
    Collider_DestroyCylinder(globalCtx, &this->unk_164);
    if (globalCtx->envCtx.unk_BF != 0xFF) {
        globalCtx->envCtx.unk_BF = 0xFF;
    }
}

void BgPoSyokudai_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgPoSyokudai* this = THIS;
    s32 pad;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_164.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->unk_164.base);
    if (Flags_GetSwitch(globalCtx, this->actor.params)) {
        func_8002F974(&this->actor, 0x2031);
    }
    this->unk_14E++;
}

//#define A
#ifdef A
void BgPoSyokudai_Draw(Actor* thisx, GlobalContext* globalCtx) {
    u8* sp64;
    u8* sp60;
    f32 rand;
    Gfx* dispRefs[4];
    BgPoSyokudai* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad1;

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_bg_po_syokudai.c", 0x13B);
    func_80093D18(globalCtx->state.gfxCtx);

    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_bg_po_syokudai.c", 0x13F), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, &D_060003A0);

    if (Flags_GetSwitch(globalCtx, this->actor.params)) {
        sp60 = D_808A899C[this->unk_14C];
        sp64 = D_808A898C[this->unk_14C];
        rand = (Math_Rand_ZeroOne() * 0.3f) + 0.7f;
        Lights_SetPositionalLightColorAndRadius(&this->unk_154, 
            sp64[0] * rand, 
            sp64[1] * rand, 
            sp64[2] * rand, 
            0xC8);
        func_80093D84(globalCtx->state.gfxCtx);
        gSPSegment(gfxCtx->polyXlu.p++, 0x08, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, (-this->unk_14E * 0x14) & 0x1FF, 0x20, 0x80));
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0x80, 0x80, sp64[0], sp64[1], sp64[2], 0xFF);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, sp60[0], sp60[1], sp60[2], 0xFF);
        Matrix_Translate(0.0f, 52.0f, 0.0f, 1);
        Matrix_RotateY((s16)((func_8005A9F4(globalCtx->cameraPtrs[globalCtx->activeCamera]) - this->actor.shape.rot.y) + 0x8000) * 0.0000958738f, 1);
        Matrix_Scale(0.0027f, 0.0027f, 0.0027f, 1);
        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_bg_po_syokudai.c", 0x170), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyXlu.p++, &D_0404D4E0);
    }
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_bg_po_syokudai.c", 0x175);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Syokudai/BgPoSyokudai_Draw.s")
#endif
#undef A