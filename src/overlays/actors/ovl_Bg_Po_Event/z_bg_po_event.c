#include "z_bg_po_event.h"

#define FLAGS 0x00000000

#define THIS ((BgPoEvent*)thisx)

void BgPoEvent_Init(Actor* thisx, GlobalContext* globalCtx);
void BgPoEvent_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgPoEvent_Update(Actor* thisx, GlobalContext* globalCtx);
void BgPoEvent_Draw(Actor* thisx, GlobalContext* globalCtx);

extern UNK_PTR D_06007860;

const ActorInit Bg_Po_Event_InitVars = {
    ACTOR_BG_PO_EVENT,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_PO_SISTERS,
    sizeof(BgPoEvent),
    (ActorFunc)BgPoEvent_Init,
    (ActorFunc)BgPoEvent_Destroy,
    (ActorFunc)BgPoEvent_Update,
    (ActorFunc)BgPoEvent_Draw,
};

ColliderTrisItemInit D_808A7CD0[2] = {
    {
        { 0x04, { 0x00000000, 0x00, 0x00 }, { 0x0001F820, 0x00, 0x00 }, 0x00, 0x01, 0x00 },
        { { { 25.0f, 33.0f, 0.0f }, { -25.0f, 33.0f, 0.0f }, { -25.0f, -33.0f, 0.0f } } },
    },
    {
        { 0xC1, { 0x42040000, 0x00, 0x00 }, { 0xC1C80000, 0xC2, 0x04 }, 0x00, 0x00, 0x00 },
        { { { 1.504632769052528e-36f, 0.0f, 0.0f }, { 1.808459746119036e-40f, 0.0f, 9.183549615799121e-41f }, { 25.0f, 33.0f, 0.0f } } },
    },
};

ColliderTrisInit D_808A7D48 =
{
    { COLTYPE_UNK10, 0x00, 0x09, 0x00, 0x20, COLSHAPE_TRIS },
    2, D_808A7CD0,
};

s16 D_808A7D78[] = {
    0x0865, 0x07B1, 0x0775, 0x0000
};

s16 D_808A7D80[] = {
    0xFA7E, 0xFABA, 0xFA06, 0x0000
};

InitChainEntry D_808A7D88[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};


u32 D_808A7D94[] = {
    0x060075A0, 
    0x060079E0, 
    0x06006830, 
    0x06006D60, 
    0x06007230
};

static u8 D_808A80A0;

//#define A
#ifdef A
void func_808A6210(BgPoEvent* this, GlobalContext* globalCtx) {
    s32 i;
    f32 tmpf1;
    f32 tmpf2;
    Vec3s tmpvecs1;

    tmpf1 = Math_Sins(this->dyna.actor.shape.rot.y);
    tmpf2 = Math_Coss(this->dyna.actor.shape.rot.y);
    if (arg0->unk_168 == 4) {
        tmpvecs1.y = tmpf2 * 2.4f;
        tmpvecs1.z = 1.818f;
        tmpvecs1.x = tmpf1 * 2.4f;
    } else {
        tmpvecs1.y = tmpf2;
        tmpvecs1.z = 1.0f;
        tmpvecs1.x = tmpf1;
    }

    for (i = 0; i < D_808A7D48.count; i++) {

    }

}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A6210.s")
#endif
#undef A

void func_808A68D0(BgPoEvent* this, GlobalContext* globalCtx);

void func_808A658C(BgPoEvent* this, GlobalContext* globalCtx) {
    s32 tmp;
    s32 sp58 = 0;
    u32 sp54;

    this->dyna.actor.flags |= 0x30;
    DynaPolyInfo_Alloc(&D_06007860, &sp58);
    this->dyna.dynaPolyId = DynaPolyInfo_RegisterActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, sp58);
    if (this->unk_168 == 0) {
        if (this->unk_169 != 3) {
            if (Actor_SpawnAttached(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_BG_PO_EVENT, 
                D_808A7D78[this->unk_169], 
                this->dyna.actor.posRot.pos.y, 
                D_808A7D80[this->unk_169], 
                0, 
                this->dyna.actor.shape.rot.y, 
                this->dyna.actor.shape.rot.z - 0x4000, 
                ((this->unk_169 + 1) << 0xC) + (this->unk_168 << 8) + this->dyna.actor.params) == NULL) {
                    Actor_Kill(&this->dyna.actor);
                    return;
            }
            if (this->unk_169 == 0) {
                if (this->dyna.actor.attachedB->attachedB == NULL) {
                    Actor_Kill(&this->dyna.actor);
                    return;
                }
                if (this->dyna.actor.attachedB->attachedB->attachedB == NULL) {
                    Actor_Kill(&this->dyna.actor);
                    Actor_Kill(this->dyna.actor.attachedB);
                    return;
                }
                this->dyna.actor.attachedA = this->dyna.actor.attachedB->attachedB->attachedB;
                this->dyna.actor.attachedB->attachedB->attachedB->attachedB = &this->dyna.actor;
            }
        }
    }
    this->dyna.actor.posRot.pos.y = 833.0f;
    this->dyna.actor.groundY = func_8003C9A4(&globalCtx->colCtx, &this->dyna.actor.floorPoly, &sp54, &this->dyna.actor, &this->dyna.actor.posRot.pos);
    this->actionFunc = func_808A68D0;
}

//#define A
void func_808A6210(BgPoEvent*, GlobalContext*);
void func_808A658C(BgPoEvent*, GlobalContext*);
#ifdef A
void BgPoEvent_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgPoEvent* this = THIS;
    u8 tmp;

    Actor_ProcessInitChain(&this->dyna.actor, D_808A7D88);
    tmp = (this->dyna.actor.params >> 8) & 0xF;
    this->unk_168 = tmp & 0xFF;
    this->unk_169 = (thisx->params >> 0xC) & 0xF;
    thisx->params &= 0x3F;
    if (tmp >= 2) {
        Collider_InitTris(globalCtx, &this->unk_170);
        Collider_SetTris(globalCtx, &this->unk_170, &this->dyna.actor, &D_808A7D48, this->unk_190);
        if (Flags_GetSwitch(globalCtx, this->dyna.actor.params)) {
            Actor_Kill(&this->dyna.actor);
        } else {
            func_808A6210(this, globalCtx);
        }
    } else {
        DynaPolyInfo_SetActorMove(&this->dyna, 0);
        if (Flags_GetSwitch(globalCtx, this->dyna.actor.params)) {
            Actor_Kill(&this->dyna.actor);
        } else {
            func_808A658C(this, globalCtx);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/BgPoEvent_Init.s")
#endif
#undef A

void BgPoEvent_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgPoEvent* this = THIS;

    if (this->unk_168 >= 2) {
        Collider_DestroyTris(globalCtx, &this->unk_170);
        return;
    }
    DynaPolyInfo_Free(globalCtx, &globalCtx->colCtx.dyna, this->dyna.dynaPolyId);
    if (this->unk_168 == 1) {
        if (gSaveContext.timer1Value > 0) {
            gSaveContext.timer1State = 10;
        }
    }
}

void func_808A69DC(BgPoEvent*, GlobalContext*);

void func_808A68D0(BgPoEvent* this, GlobalContext* globalCtx) {
    this->dyna.actor.posRot.pos.y = 833.0f;

    if (D_808A80A0 == 0x3F) {
        if (this->unk_168 == 1) {
            func_800800F8(globalCtx, 0xC4E, 0x41, NULL, 0);
        }
        this->unk_16C.word = 0x2D;
        this->actionFunc = func_808A69DC;
        return;
    }
    if (50.0f < this->dyna.actor.xzDistFromLink) {
        if (this->unk_168 != 1) {
            D_808A80A0 |= (1 << this->unk_169);
        } else {
            D_808A80A0 |= 0x10;
        }
    } else if (this->unk_168 != 1) {
        D_808A80A0 &= ~(1 << this->unk_169);
    } else {
        D_808A80A0 &= 0xFFEF;
    }
}

void func_808A6BC8(BgPoEvent*, GlobalContext*);

void func_808A69DC(BgPoEvent* this, GlobalContext* globalCtx) {
    s32 tmp1;
    f32 tmpf1;

    if (this->unk_16C.word) {
        this->unk_16C.word--;
    }

    if (this->unk_16C.word < 15) {
        tmpf1 = (this->unk_16C.word % 3) - 1;
        this->dyna.actor.posRot.pos.x = this->dyna.actor.initPosRot.pos.x + (tmpf1 + tmpf1);
        
        tmp1 = this->unk_16C.word & 3;
        if ((this->unk_16C.word < 0) && (tmp1 != 0)) {
            tmp1 -= 4;
        }
        
        if (tmp1 == 0) {
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_BLOCK_SHAKE);
        }
    }
    if (this->unk_16C.word == 0) {
        this->dyna.actor.posRot.pos.x = this->dyna.actor.initPosRot.pos.x;
        D_808A80A0 = 0;
        this->unk_16C.word = 0x3C;
        this->actionFunc = func_808A6BC8;
    }
}

void func_808A6A94(BgPoEvent *this) {
    s32 tmp1;
    s32 tmp2;
    s32 tmp3;
    s32 tmp4;

    if ((this->unk_169 == 3) || (this->unk_169 == 1)) {
        tmp1 = this->dyna.actor.posRot.pos.z;
        tmp2 = this->dyna.actor.attachedB->posRot.pos.z;
        if ( this->unk_169 == 3) {
            tmp4 = this->dyna.actor.posRot.pos.x;
            tmp3 = this->dyna.actor.attachedB->posRot.pos.x;
        } else {
            tmp4 = this->dyna.actor.attachedB->posRot.pos.x;
            tmp3 = this->dyna.actor.posRot.pos.x;
        }
    } else {
        tmp1 = this->dyna.actor.posRot.pos.x;
        tmp2 = this->dyna.actor.attachedB->posRot.pos.x;
        if (this->unk_169 == 0) {
            tmp4 = this->dyna.actor.posRot.pos.z;
            tmp3 = this->dyna.actor.attachedB->posRot.pos.z;
        } else {
            tmp4 = this->dyna.actor.attachedB->posRot.pos.z;
            tmp3 = this->dyna.actor.posRot.pos.z;
        }
    }
    if (tmp1 == tmp2) {
        if ((tmp3 - tmp4) == 0x3C) {
            D_808A80A0 |= (1 << this->unk_169);
            return;
        }
    }
    D_808A80A0 &= ~(1 << this->unk_169);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A6BC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A6CCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A6F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A7138.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A7238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A72AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A7328.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A7444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A7500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A7530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A7568.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A75B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/func_808A780C.s")

void func_808A72AC(BgPoEvent*, GlobalContext*);
void func_808A75B8(BgPoEvent*, GlobalContext*);

void BgPoEvent_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgPoEvent* this = THIS;

    this->actionFunc(this, globalCtx);
    if ((this->actionFunc == func_808A72AC) || (this->actionFunc == func_808A75B8)) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_170.base);
    }
}

#define A
void func_808A7500(BgPoEvent*, GlobalContext*);
#ifdef A
void BgPoEvent_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgPoEvent* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];
    u8 tmp1;
    f32 tmp2;
    f32 tmp3;
    Vec3f a;
    Vec3f b;

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_bg_po_event.c", 0x5C9);
    func_80093D18(globalCtx->state.gfxCtx);
    if ((this->unk_168 == 3) || (this->unk_168 == 2)) {
        if (this->actionFunc == func_808A7500) {
            tmp1 = 0xFF;
        } else if (this->actionFunc == func_808A75B8) {
            tmp1 = 0;
        } else {
            tmp1 = this->unk_16C.b2;
        }
        gDPSetEnvColor(gfxCtx->polyOpa.p++, 0xFF, 0xFF, 0xFF, tmp1);
    }

    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_bg_po_event.c", 0x5DD), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, D_808A7D94[this->unk_168]);

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_bg_po_event.c", 0x5E4);

    if ((this->unk_168 == 0) || (this->unk_168 == 1)) {
        tmp2 = (833.0f - this->dyna.actor.posRot.pos.y) * 0.0025f;
        if (!(1.0f < tmp2)) {
            a.x = this->dyna.actor.posRot.pos.x;
            a.y = this->dyna.actor.posRot.pos.y - 30.0f;
            a.z = this->dyna.actor.posRot.pos.z;

            tmp3 = (tmp2 * 0.3f) + 0.4f;
            b.y = 1.0f;
            b.z = tmp3;
            b.x = tmp3;
            func_80033C30(&a, &b, (tmp2 * 100.0f) + 155.0f, globalCtx);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Bg_Po_Event/BgPoEvent_Draw.s")
#endif
#undef A
