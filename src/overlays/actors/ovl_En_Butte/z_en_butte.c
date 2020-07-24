#include "z_en_butte.h"

#define FLAGS 0x00000000

#define THIS ((EnButte*)thisx)

void EnButte_Init(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Update(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809CD79C(EnButte* this);
void func_809CE0D0(EnButte* this);
void func_809CE014(EnButte* this, GlobalContext* globalCtx);
void func_809CD7E8(EnButte* this, GlobalContext* globalCtx);
void func_809CE0EC(EnButte* this, GlobalContext* globalCtx);

extern AnimationHeader D_05002470;
extern SkeletonHeader D_050036F0;

static ColliderJntSphItemInit sJntSphItemsInit[1] = {
    {
        { 0x00, { 0x00000000, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
        { 0, { { 0, 0, 0 }, 5 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit =
{
    { COLTYPE_UNK10, 0x00, 0x00, 0x19, 0x10, COLSHAPE_JNTSPH },
    1, sJntSphItemsInit,
};

const ActorInit En_Butte_InitVars = {
    ACTOR_EN_BUTTE,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_FIELD_KEEP,
    sizeof(EnButte),
    (ActorFunc)EnButte_Init,
    (ActorFunc)EnButte_Destroy,
    (ActorFunc)EnButte_Update,
    (ActorFunc)EnButte_Draw,
};

EnButteStruct1 D_809CE344[] = {
    {0x0005, 0x0023, {0.0f, 0.1f,  0.5f}, 0x0000},
    {0x000A, 0x002D, {1.1f, 0.1f, 0.25f}, 0x03E8},
    {0x000A, 0x0028, {1.5f, 0.1f,  0.3f}, 0x07D0}
};

f32 D_809CE3BC = 0.0f;
s16 D_809CE3C0 = 0;
Vec3f D_809CE3C4 = { 0.0f, 0.0f, -3.0 };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 700, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 20, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_STOP),
};

void func_809CD070(EnButte* this, EnButteStruct1* arg1) {
    if (this->unk_256 == 0) {
        if (Math_Rand_ZeroOne() < 0.6f) {
            this->unk_256 = 1;
        } else {
            this->unk_256 = 2;
        }
    } else {
        this->unk_256 = 0;
    }
    this->unk_254 = Math_Rand_S16Offset(arg1->unk_00, arg1->unk_02);
}

void func_809CD0F8(void) {
    D_809CE3BC = 0.0f;
    D_809CE3C0 = 0;
}

void func_809CD110(void) {
    D_809CE3BC += 0.003f;
    D_809CE3C0 += 0xFA0;
}

void func_809CD144(EnButte* this, GlobalContext* globalCtx) {
    Vec3f sp5C;
    s32 tmp;
    Vec3s sp50;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_choo.c", 0x127);

        func_80093C14(globalCtx->state.gfxCtx);
        tmp = Math_Sins(D_809CE3C0) * 250.0f;
        tmp = CLAMP(tmp, 0, 0xFF);

        func_8005A970(&sp50, ACTIVE_CAM);
        Matrix_RotateY(sp50.y * 0.0000958738f, 0);
        Matrix_RotateX(sp50.x * 0.0000958738f, 1);
        Matrix_RotateZ(sp50.z * 0.0000958738f, 1);
        Matrix_MultVec3f(&D_809CE3C4, &sp5C);
        func_800D1694(this->actor.posRot2.pos.x + sp5C.x, this->actor.posRot2.pos.y + sp5C.y, this->actor.posRot2.pos.z + sp5C.z, &sp50);
        Matrix_Scale(D_809CE3BC, D_809CE3BC, D_809CE3BC, 1);

        gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_choo.c", 0x13D), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(gfxCtx->polyXlu.p++, 0x80, 0x80, 0xC8, 0xC8, 0xB4, tmp);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xC8, 0xC8, 0xD2, 0xFF);
        gSPDisplayList(gfxCtx->polyXlu.p++, SEGMENTED_TO_VIRTUAL(&D_04010130));

        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_choo.c", 0x146);
    }
}

void EnButte_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnButte* this = THIS;

    if (this->actor.params == -1) {
        this->actor.params = 0;
    }
    Actor_ProcessInitChain(&this->actor, sInitChain);
    if ((this->actor.params & 1) == 1) {
        this->actor.uncullZoneScale = 200.0f;
    }
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_050036F0, &D_05002470, this->limbDrawTable, this->transitionDrawTable, 8);
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderItems);
    this->actor.colChkInfo.mass = 0;
    this->unk_25C = Math_Rand_ZeroOne() * 65535.0f;
    this->unk_25E = Math_Rand_ZeroOne() * 65535.0f;
    this->unk_260 = Math_Rand_ZeroOne() * 65535.0f;
    SkelAnime_ChangeAnim(&this->skelAnime, &D_05002470, 1.0f, 0.0f, 0.0f, 1, 0.0f);
    func_809CD79C(this);
    this->actor.shape.rot.x -= 0x2320;
    this->unk_258 = 1;
    osSyncPrintf("(field keep 蝶)(%x)(arg_data 0x%04x)\n", &this->actor, this->actor.params);
}

void EnButte_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    Collider_DestroyJntSph(globalCtx, &THIS->collider);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Butte/func_809CD56C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Butte/func_809CD634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Butte/func_809CD6FC.s")

void func_809CD79C(EnButte* this) {
    func_809CD070(this, &D_809CE344[this->unk_256]);
    this->actionFunc = func_809CD7E8;
}

void func_809CD56C(EnButte*);
void func_809CD6FC(EnButte*);

void func_809CD7E8(EnButte* this, GlobalContext* globalCtx) {
    EnButteStruct1* sp4C = &D_809CE344[this->unk_256];
    Player* player = PLAYER;
    f32 sp40;
    f32 tmpf1;
    s16 tmpf2;
    f32 tmpf3;
    f32 tmpf4;


    sp40 = func_800CB594(this->actor.posRot.pos.x, this->actor.posRot.pos.z, this->actor.initPosRot.pos.x, this->actor.initPosRot.pos.z);
    func_809CD56C(this);
    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, sp4C->a.x, sp4C->a.y, sp4C->a.z, 0.0f);
    if (this->unk_257 == 1) {
        tmpf1 = 10000.0f;
        tmpf2 = 0x3E8;
    } else {
        tmpf1 = 1225.0f;
        tmpf2 = 0x258;
    }

    tmpf3 = 0.0f;
    this->unk_264 = this->actor.initPosRot.pos.y;
    if ((this->unk_256 != 0) && ((tmpf1 < sp40) || (this->unk_254 < 4))) {
        if (Math_ApproxUpdateScaledS(&this->actor.posRot.rot.y, Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.initPosRot.pos), sp4C->d) == 0) {
            tmpf3 = 0.5f;
        }
    } else if (((this->unk_257 == 0) && (this->actor.attachedB != 0)) && (&this->actor != this->actor.attachedB)) {
        if (Math_ApproxUpdateScaledS(&this->actor.posRot.rot.y, Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.attachedB->posRot.pos), tmpf2) == 0) {
            tmpf3 = 0.3f;
        }
    } else if ((this->unk_257 == 1) && (Math_ApproxUpdateScaledS(&this->actor.posRot.rot.y, (s32)((Math_Rand_ZeroOne() - 0.5f) * 24576.0f) + this->actor.yawTowardsLink + 0x8000, tmpf2) == 0)) {
        tmpf3 = 0.4f;
    } else {
        this->actor.posRot.rot.y += (s16)(sinf(this->unk_25C) * 100.0f);
    }

    func_809CD6FC(this);
    tmpf1 = Math_Sins(this->unk_260);
    tmpf3 = Math_Rand_ZeroOne();
    tmpf4 = ((1.0f - Math_Sins(this->unk_25E)) * 0.3f) + (this->actor.speedXZ * 0.5f) + (tmpf3 * 0.2f) + ((1.0f - tmpf1) * 0.15f) + tmpf3;
    if (tmpf4 < 0.2f) {
        this->skelAnime.animPlaybackSpeed = 0.2f;
    } else if (1.5f < tmpf4) {
        this->skelAnime.animPlaybackSpeed = 1.5f;
    } else {
        this->skelAnime.animPlaybackSpeed = tmpf4;
    }
    
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_254 <= 0) {
        func_809CD070(this, &D_809CE344[this->unk_256]);
    }

    if (
        ((((this->actor.params & 1) == 1) && (player->heldItemActionParam == 6)) || 
        ((this->unk_25A <= 0) && (func_800CB594(player->actor.posRot.pos.x, player->actor.posRot.pos.z, this->actor.initPosRot.pos.x, this->actor.initPosRot.pos.z) < 14400.0f)) &&
        (this->actor.xzDistFromLink < 60.0f))
       ) {
        func_809CDBCC(this);
        this->unk_257 = 2;
    } else if (this->actor.xzDistFromLink < 120.0) {
        this->unk_257 = 1;
    } else {
        this->unk_257 = 0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Butte/func_809CDBCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Butte/func_809CDC18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Butte/func_809CDFC4.s")

void func_809CE014(EnButte* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_809CD110();
    if (this->unk_254 == 5) {
        Audio_PlaySoundAtPosition(globalCtx, &this->actor.posRot.pos, 0x3C, NA_SE_EV_BUTTERFRY_TO_FAIRY);
    } else if (this->unk_254 == 4) {
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ELF, this->actor.posRot2.pos.x, this->actor.posRot2.pos.y, this->actor.posRot2.pos.z, 0, this->actor.shape.rot.y, 0, 2);
        this->unk_258 = 0;
    } else if (this->unk_254 <= 0) {
        func_809CE0D0(this);
    }
}

void func_809CE0D0(EnButte* this) {
    this->unk_254 = 0x40;
    this->actionFunc = func_809CE0EC;
    this->actor.draw = NULL;
}

void func_809CE0EC(EnButte* this, GlobalContext* globalCtx) {
    if (this->unk_254 <= 0) {
        Actor_Kill(&this->actor);
    }
}

void EnButte_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnButte* this = THIS;

    if (this->actor.attachedB != NULL) {
        if ((this->actor.attachedB->update == NULL) && (this->actor.attachedB != &this->actor)) {
            this->actor.attachedB = NULL;
        }
    }

    if (this->unk_254 > 0) {
        this->unk_254--;
    }

    this->unk_25C += 0x222;
    this->unk_25E += 0x1000;
    this->unk_260 += 0x600;
    if ((this->actor.params & 1) == 1) {
        if (PLAYER->swordState == 0) {
            if (this->unk_25A > 0) {
                this->unk_25A--;
            }
        } else {
            this->unk_25A = 0x50;
        }
    }
    this->actionFunc(this, globalCtx);
    if (this->actor.update != NULL) {
        Actor_MoveForward(&this->actor);
        Math_ApproxF(&this->actor.posRot.pos.y, this->unk_264, 0.6f);
        if (this->actor.xyzDistFromLinkSq < 5000.0f) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
        Actor_SetHeight(&this->actor, this->actor.shape.unk_08 * this->actor.scale.y);
    }
}

void EnButte_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnButte* this = THIS;

    if (this->unk_258 != 0) {
        func_80093D18(globalCtx->state.gfxCtx);
        SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, NULL, NULL, NULL);
        func_800628A4(0, &this->collider);
    }
    if (((thisx->params & 1) == 1) && (this->actionFunc == func_809CE014)) {
        func_809CD144(this, globalCtx);
    }
}

