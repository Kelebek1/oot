#include "z_en_fr.h"
#include "vt.h"

#define FLAGS 0x02000019

#define THIS ((EnFr*)thisx)

void EnFr_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFr_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFr_Update(Actor* thisx, GlobalContext* globalCtx);
void func_80A1CB58(Actor* thisx, GlobalContext* globalCtx);
void func_80A1BB34(Actor* thisx, GlobalContext* globalCtx);
void func_80A1CD24(Actor* thisx, GlobalContext* globalCtx);

void func_80A1B19C(EnFr* this);
void func_80A1C718(EnFr* this, GlobalContext* globalCtx, u8 arg2);

void func_80A1C524(EnFr* this, GlobalContext* globalCtx);
void func_80A1BCB4(EnFr* this, GlobalContext* globalCtx);
void func_80A1B22C(EnFr* this, GlobalContext* globalCtx);
void func_80A1BD94(EnFr* this, GlobalContext* globalCtx);
void func_80A1B2C8(EnFr* this, GlobalContext* globalCtx);
void func_80A1BDFC(EnFr* this, GlobalContext* globalCtx);
void func_80A1B464(EnFr* this, GlobalContext* globalCtx);
void func_80A1BE98(EnFr* this, GlobalContext* globalCtx);
void func_80A1C1E4(EnFr* this, GlobalContext* globalCtx);
void func_80A1B524(EnFr* this, GlobalContext* globalCtx);
void func_80A1BF10(EnFr* this, GlobalContext* globalCtx);
void func_80A1C400(EnFr* this, GlobalContext* globalCtx);
void func_80A1B778(EnFr* this, GlobalContext* globalCtx);
void func_80A1B638(EnFr* this, GlobalContext* globalCtx);
void func_80A1C05C(EnFr* this, GlobalContext* globalCtx);
void func_80A1C944(EnFr* this, GlobalContext* globalCtx);
void func_80A1C580(EnFr* this, GlobalContext* globalCtx);
void func_80A1C18C(EnFr* this, GlobalContext* globalCtx);
void func_80A1CAAC(EnFr* this, GlobalContext* globalCtx);
void func_80A1C790(EnFr* this, GlobalContext* globalCtx);
void func_80A1CB08(EnFr* this, GlobalContext* globalCtx);
void func_80A1C7CC(EnFr* this, GlobalContext* globalCtx);
void func_80A1C830(EnFr* this, GlobalContext* globalCtx);

extern SkeletonHeader D_0600B498;
extern SkeletonHeader D_050036F0;
extern AnimationHeader D_06001534;
extern AnimationHeader D_05002470;
extern AnimationHeader D_060007BC;
extern AnimationHeader D_060011C0;

extern u8* D_80131854;

typedef struct {
    u8 unk_00;
    EnFr* unk_04[5];
} EnFrStruct1;

EnFrStruct1 D_80A1CFF0 = { 0, { NULL, NULL, NULL, NULL, NULL } };

u16 D_80A1D008[] = { 0x0002, 0x0004, 0x0010, 0x0008, 0x0020, 0x0040, 0x0001, 0x0000 };

u8 D_80A1D018[] = { 0x02, 0x03, 0x04, 0x00, 0x01, 0x00 };

s32 D_80A1D020[] = { 0x00000003, 0x00000004, 0x00000000, 0x00000001, 0x00000002 };

const ActorInit En_Fr_InitVars = {
    ACTOR_EN_FR,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_FR,
    sizeof(EnFr),
    (ActorFunc)EnFr_Init,
    (ActorFunc)EnFr_Destroy,
    (ActorFunc)EnFr_Update,
    NULL,
};

Color_RGBA8_n D_80A1D054[] = { { 200, 170, 0, 255 },
                               { 0, 170, 200, 255 },
                               { 210, 120, 100, 255 },
                               { 120, 130, 230, 255 },
                               { 190, 190, 190, 255 } };

Vec3f D_80A1D068[] = { { 0.0f, 0.0f, 0.0f },
                       { 80.0f, -1.1780972480773926f, -80.0f },
                       { 80.0f, -1.5707963705062866f, -80.0f },
                       { 80.0f, -0.7853981852531433f, -80.0f },
                       { 80.0f, 2.7488937377929688f, -80.0f },
                       { 80.0f, 1.5707963705062866f, -80.0f } };

s16 D_80A1D0B0[] = { 0x0028, 0x0014, 0x000F, 0x000C, 0x000C };

// D_80A1D0BC
static InitChainEntry sInitChain[] = {
    ICHAIN_U8(unk_1F, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 30, ICHAIN_STOP),
};

u8 D_80A1D0C4[] = { 0x05, 0x01, 0x07, 0x03, 0x09, 0x00, 0x00, 0x00 };

f32 D_80A1D0CC[] = { 180.0f, 210.0f, 240.0f, 270.0f };

u8 D_80A1D0DC[] = { 0x05, 0x02, 0x09, 0x0B, 0x0E };

u8 D_80A1D0E4[] = { 0xF9, 0xF6, 0xFD, 0xFF, 0x02 };

u8 D_80A1D0EC[] = { 0x01, 0x00, 0x02, 0x03, 0x04, 0x01, 0x00, 0x02 };

u8 D_80A1D0F4[] = { 0x00, 0x01, 0x02, 0x03, 0x04 };

UNK_TYPE D_80A1D0FC[] = { 0x060059A0, 0x06005BA0 };

void func_80A1A9A0(EnFr* this) {
    Vec3f sp2C;
    Vec3f sp20;
    s16 tmp;

    sp2C.y = 0.0f;
    sp2C.x = 0.0f;
    sp2C.z = this->unk_398 = D_80A1D068[this->actor.params].x;

    Matrix_RotateY(D_80A1D068[this->actor.params].y, MTXMODE_NEW);
    Matrix_MultVec3f(&sp2C, &sp20);

    this->actor.posRot.pos.x = this->unk_38C.x + sp20.x;
    this->actor.posRot.pos.z = this->unk_38C.z + sp20.z;
    this->actor.posRot.pos.y = D_80A1D068[this->actor.params].z + this->unk_38C.y;

    tmp = (s16)(D_80A1D068[this->actor.params].y * 10430.378f) + 0x8000;

    this->actor.speedXZ = this->actor.velocity.y = this->actor.gravity = 0.0f;

    this->actor.shape.rot.y = tmp;
    this->actor.posRot.rot.y = tmp;
}

void EnFr_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFr* this = THIS;
    s16 params = thisx->params;

    if (params == 0) {
        thisx->draw = thisx->destroy = NULL;
        thisx->update = func_80A1CB58;
        thisx->flags &= ~0x11;
        thisx->flags = thisx->flags;
        Actor_ChangeType(globalCtx, &globalCtx->actorCtx, &this->actor, 6);
        thisx->textId = 0x40AC;
        this->actionFunc = func_80A1BCB4;
        return;
    }

    if ((params >= 6) || (params < 0)) {
        osSyncPrintf(VT_COL(RED, WHITE));
        // Args are wrong!
        osSyncPrintf("%s[%d] : 引数が間違っている！！(%d)\n", "../z_en_fr.c", 370, thisx->params);
        osSyncPrintf(VT_RST);
        __assert("0", "../z_en_fr.c", 372);
    }

    this->unk_36A = Object_GetIndex(&globalCtx->objectCtx, 2);
    if (this->unk_36A < 0) {
        Actor_Kill(&this->actor);
        osSyncPrintf(VT_COL(RED, WHITE));
        // No bank mate
        osSyncPrintf("%s[%d] : バンクが無いよ！！\n", "../z_en_fr.c", 380);
        osSyncPrintf(VT_RST);
        __assert("0", "../z_en_fr.c", 382);
    }
}

void func_80A1AC0C(EnFr* this) {
    if (this->actor.params != 4) {
        this->actor.draw = NULL;
    } else {
        this->actor.draw = func_80A1CD24;
    }
}

void func_80A1AC34(EnFr* this) {
    this->actor.draw = func_80A1CD24;
}

#ifdef NON_MATCHING
// Regalloc
void EnFr_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFr* this = THIS;
    // s32 pad2;
    s32 pad;
    s32 params;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_36A) != 0) {
        this->actor.flags &= ~0x10;
        params = this->actor.params - 1;
        D_80A1CFF0.unk_04[params] = this;
        Actor_ProcessInitChain(&this->actor, sInitChain);
        SkelAnime_InitSV(globalCtx, &this->skelAnime1, &D_0600B498, &D_06001534, this->limbDrawTable1,
                         this->transitionDrawTable1, 24);
        SkelAnime_Init(globalCtx, &this->skelAnime2, &D_050036F0, &D_05002470, this->limbDrawTable2,
                       this->transitionDrawTable2, 8);
        this->unk_358 = Lights_Insert(globalCtx, &globalCtx->lightCtx, &this->unk_35C);
        Lights_InitType0PositionalLight(&this->unk_35C, this->actor.initPosRot.pos.x, this->actor.initPosRot.pos.y,
                                        this->actor.initPosRot.pos.z, 0xFF, 0xFF, 0xFF, -1);

        if (gSaveContext.eventChkInf[13] & D_80A1D008[D_80A1D018[params]]) {
            this->unk_3A0 = 270.0f;
        } else {
            this->unk_3A0 = 150.0f;
        }

        Actor_SetScale(&this->actor, this->unk_3A0 * 0.0001f);
        this->actor.minVelocityY = -9999.0f;
        Actor_SetHeight(&this->actor, 10.0f);

        this->unk_378 = 1;
        this->unk_370 = (s16)(Math_Rand_ZeroFloat(60.0f) + 20.0f);
        this->unk_374 = func_80A1B19C;

        this->unk_379 = this->unk_37B = this->unk_37A = 0;

        this->actionFunc = func_80A1B22C;

        this->unk_37C = 0;
        this->unk_37D = this->unk_37E = 0;

        this->unk_38C = this->actor.posRot.pos;

        this->unk_383 = 0;
        this->unk_382 = 7;
        this->unk_3A4 = NULL;

        func_80A1A9A0(this);
        func_80A1AC0C(this);

        this->actor.update = func_80A1BB34;
        this->unk_3A8 = 0;
        this->unk_3AA = (s32)Math_Rand_ZeroFloat(255.0f) * 4096;

        this->unk_3B8.x = this->unk_3AC.x = this->unk_38C.x;
        this->unk_3B8.y = this->unk_3AC.y = this->unk_38C.y + 50.0f;
        this->unk_3B8.z = this->unk_3AC.z = this->unk_38C.z;

        this->actor.flags &= ~1;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fr/EnFr_Update.s")
#endif

void EnFr_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFr* this = THIS;

    Lights_Remove(globalCtx, &globalCtx->lightCtx, this->unk_358);
}

void func_80A1AF6C(EnFr* this, GlobalContext* globalCtx) {
    WaterBox* sp2C;
    f32 sp28;

    if (func_80042244(globalCtx, &globalCtx->colCtx, this->actor.posRot.pos.x, this->actor.posRot.pos.z, &sp28,
                      &sp2C)) {
        this->unk_37B = this->unk_37A;
        if (this->actor.posRot.pos.y <= sp28) {
            this->unk_37A = 1;
        } else {
            this->unk_37A = 0;
        }
    }
}

void func_80A1AFF0(EnFr* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    if (this->unk_37A != this->unk_37B) {
        sp2C.x = this->actor.posRot.pos.x;
        sp2C.y = this->actor.posRot.pos.y - 10.0f;
        sp2C.z = this->actor.posRot.pos.z;
        func_8002949C(globalCtx, &sp2C, 0, 0, 1, 1);
        if (this->unk_37A == 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_DIVE_INTO_WATER_L);
        } else {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_BOMB_DROP_WATER);
        }
    }
}

s32 func_80A1B09C(EnFr* this, f32* arg1) {
    *arg1 = this->actor.posRot.pos.y - this->unk_38C.y;
    if ((this->actor.velocity.y < 0.0f) && (*arg1 <= 0.0f)) {
        this->actor.velocity.y = 0.0f;
        this->actor.posRot.pos.y = this->unk_38C.y;
        return 1;
    }

    return 0;
}

s32 func_80A1B0F8(Player* player, EnFr* this) {
    Vec3f vec;

    vec.x = player->actor.posRot.pos.x - this->actor.posRot.pos.x;
    vec.z = player->actor.posRot.pos.z - this->actor.posRot.pos.z;
    vec.y = player->actor.posRot.pos.y - this->actor.posRot.pos.y;

    return ((SQ(vec.x) + SQ(vec.z)) <= 900.0f) && (vec.y >= 0.0f);
}

void func_80A1B174(EnFr* this) {
    if (this->unk_370 != 0) {
        this->unk_370--;
    } else {
        this->unk_374 = func_80A1B19C;
    }
}

void func_80A1B19C(EnFr* this) {
    if (this->unk_370 != 0) {
        this->unk_370--;
    } else if (this->unk_378 != 0) {
        this->unk_378 = 0;
        this->unk_370 = (s16)(Math_Rand_ZeroFloat(60.0f) + 20.0f);
        this->unk_374 = func_80A1B174;
    } else {
        this->unk_378 = 1;
        this->unk_370 = 1;
    }
}

void func_80A1B22C(EnFr* this, GlobalContext* globalCtx) {
    if (D_80A1CFF0.unk_00 == D_80A1D0C4[this->actor.params - 1]) {
        SkelAnime_ChangeAnim(&this->skelAnime1, &D_060007BC, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_060007BC.genericHeader), 2, 0.0f);
        func_80A1AC34(this);
        this->actionFunc = func_80A1B2C8;
    }
}

void func_80A1B2C8(EnFr* this, GlobalContext* globalCtx) {
    Vec3f sp3C;
    Vec3f sp30;

    if (this->skelAnime1.animCurrentFrame == 6.0f) {
        D_80A1CFF0.unk_00++;
        this->skelAnime1.animPlaybackSpeed = 0.0f;
    } else if (this->skelAnime1.animCurrentFrame == 3.0f) {
        this->actor.gravity = -10.0f;
        this->actor.speedXZ = 0.0f;
        this->actor.velocity.y = 47.0f;
    }

    sp3C.x = sp3C.y = 0.0f;
    sp3C.z = this->unk_398;
    Matrix_RotateY(((this->actor.posRot.rot.y + 0x8000) / 32768.0f) * M_PI, 0);
    Matrix_MultVec3f(&sp3C, &sp30);
    this->actor.posRot.pos.x = this->unk_38C.x + sp30.x;
    this->actor.posRot.pos.z = this->unk_38C.z + sp30.z;
    if (this->skelAnime1.animCurrentFrame >= 3.0f) {
        Math_SmoothScaleMaxF(&this->unk_398, 0.0f, 1.0f, 10.0f);
    }

    if (func_80A1B09C(this, &sp30.y) != 0) {
        this->actor.gravity = 0.0f;
        this->actionFunc = func_80A1B464;
        this->unk_39C = 0.0f;
    }

    if ((this->actor.velocity.y <= 0.0f) && (sp30.y < 40.0f)) {
        this->skelAnime1.animPlaybackSpeed = 1.0f;
    }
}

void func_80A1B464(EnFr* this, GlobalContext* globalCtx) {
    s16 ret = Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 2, 0x2710, 0x64);

    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    if (!ret && (this->skelAnime1.animCurrentFrame == this->skelAnime1.animFrameCount)) {
        D_80A1CFF0.unk_00++;
        this->actionFunc = func_80A1B524;
        SkelAnime_ChangeAnim(&this->skelAnime1, &D_06001534, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_06001534.genericHeader), 0, 0.0f);
    }
}

void func_80A1B524(EnFr* this, GlobalContext* globalCtx) {
    if (D_80A1CFF0.unk_00 == 12) {
        this->actor.posRot.rot.y = D_80A1D068[this->actor.params].y * 10430.378f;
        SkelAnime_ChangeAnim(&this->skelAnime1, &D_060007BC, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_060007BC.genericHeader), 2, 0.0f);
        this->actionFunc = func_80A1B778;
    } else if (this->unk_379 != 0) {
        SkelAnime_ChangeAnim(&this->skelAnime1, &D_060007BC, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_060007BC.genericHeader), 2, 0.0f);
        this->actionFunc = func_80A1B638;
    }
}

void func_80A1B638(EnFr* this, GlobalContext* globalCtx) {
    f32 sp3C;

    if (this->skelAnime1.animCurrentFrame == 6.0f) {
        this->skelAnime1.animPlaybackSpeed = 0.0f;
    } else if (this->skelAnime1.animCurrentFrame == 3.0f) {
        this->actor.gravity = -10.0f;
        this->actor.velocity.y = 25.0f;
        if (this->unk_383 != 0) {
            this->unk_383 = 0;
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DODO_M_EAT);
        }
    }

    if (func_80A1B09C(this, &sp3C) != 0) {
        this->unk_379 = 0;
        this->actor.gravity = 0.0f;
        SkelAnime_ChangeAnim(&this->skelAnime1, &D_060011C0, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_060011C0.genericHeader), 0, 0.0f);
        this->actionFunc = func_80A1B524;
    } else if ((this->actor.velocity.y <= 0.0f) && (sp3C < 40.0f)) {
        this->skelAnime1.animPlaybackSpeed = 1.0f;
    }
}

void func_80A1B778(EnFr* this, GlobalContext* globalCtx) {
    f32 sp34 = D_80A1D068[this->actor.params].z + this->unk_38C.y;

    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.posRot.rot.y, 2, 0x2710, 0x64);
    if (this->skelAnime1.animCurrentFrame == 6.0f) {
        this->skelAnime1.animPlaybackSpeed = 0.0f;
    } else if (this->skelAnime1.animCurrentFrame == 3.0f) {
        this->actor.speedXZ = 6.0f;
        this->actor.gravity = -10.0f;
        this->actor.velocity.y = 25.0f;
    }

    if ((this->actor.velocity.y < 0.0f) && (this->actor.posRot.pos.y < sp34)) {
        SkelAnime_ChangeAnim(&this->skelAnime1, &D_06001534, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_06001534.genericHeader), 0, 0.0f);
        this->actionFunc = func_80A1B22C;
        func_80A1AC0C(this);
        this->unk_37C = 1;
        func_80A1A9A0(this);
    }
}

void func_80A1B8D0(EnFr* this, GlobalContext* globalCtx) {
    switch (this->unk_37F) {
        case 0:
            Math_SmoothScaleMaxF(&this->unk_3A0, D_80A1D0CC[this->unk_37E], 2.0f, 25.0f);
            if (D_80A1D0CC[this->unk_37E] <= this->unk_3A0) {
                this->unk_3A0 = D_80A1D0CC[this->unk_37E];
                if (this->unk_37E < 3) {
                    this->unk_37F = 1;
                } else {
                    this->unk_379 = 0;
                    this->unk_37D = 0;
                }
            }
            break;

        case 1:
            Math_SmoothScaleMaxF(&this->unk_3A0, 150.0f, 2.0f, 25.0f);
            if (this->unk_3A0 <= 150.0f) {
                this->unk_3A0 = 150.0f;
                this->unk_37E++;
                if (this->unk_37E >= 4) {
                    this->unk_37E = 3;
                }
                this->unk_37F = 0;
            }
            break;
    }
}

#ifdef NON_MATCHING
// Stack, looks like sp3E needs to go but can't match
void func_80A1B9D8(EnFr* this, GlobalContext* globalCtx) {
    f32 sp3C;
    f32 sp38;
    Vec3f sp2C;
    Vec3f sp20;
    s16 sp3E;

    sp3E = this->actor.shape.rot.y;
    this->unk_3AA += 0x1000;
    Matrix_Translate(this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z, MTXMODE_NEW);
    Matrix_RotateRPY(this->actor.posRot.rot.x, this->actor.posRot.rot.y, this->actor.posRot.rot.z, MTXMODE_APPLY);
    sp2C.x = sp2C.y = 0.0f;
    sp2C.z = 25.0f;
    Matrix_MultVec3f(&sp2C, &sp20);

    sp38 = Math_Sins(this->unk_3AA * 2) * 5.0f;
    this->unk_3AC.x = (Math_Sins(sp3E) * sp38) + sp20.x;

    sp3C = Math_Coss(this->unk_3AA);
    this->unk_3AC.y = (sp3C + sp3C) + (this->unk_38C.y + 50.0f);

    this->unk_3AC.z = (Math_Coss(sp3E) * sp38) + sp20.z;

    Matrix_Translate(this->unk_3AC.x, this->unk_3AC.y, this->unk_3AC.z, MTXMODE_NEW);
    Matrix_RotateRPY(this->actor.posRot.rot.x, this->actor.posRot.rot.y, this->actor.posRot.rot.z, MTXMODE_APPLY);
    sp2C.x = 0.0f;
    sp2C.y = -15.0f;
    sp2C.z = 20.0f;
    Matrix_MultVec3f(&sp2C, &this->unk_3B8);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fr/func_80A1B9D8.s")
#endif

void func_80A1BB34(Actor* thisx, GlobalContext* globalCtx) {
    EnFr* this = THIS;

    this->unk_36C++;
    Actor_SetScale(&this->actor, this->unk_3A0 * 0.0001f);
    if (this->unk_37D != 0) {
        func_80A1B8D0(this, globalCtx);
    } else {
        Actor_SetHeight(&this->actor, 10.0f);
        this->unk_374(this);
        this->actionFunc(this, globalCtx);
        func_80A1AF6C(this, globalCtx);
        func_80A1AFF0(this, globalCtx);
        SkelAnime_FrameUpdateMatrix(&this->skelAnime1);
        SkelAnime_FrameUpdateMatrix(&this->skelAnime2);
        func_80A1B9D8(this, globalCtx);
        Actor_MoveForward(&this->actor);
    }
}

s32 func_80A1BC14(EnFr* this, s32 arg1) {
    EnFr* frog = D_80A1CFF0.unk_04[arg1];
    u8 tmp;

    if ((frog != NULL) && (frog->unk_379 == 0)) {
        if (frog->unk_37E == 3) {
            tmp = D_80A1D0E4[arg1];
        } else {
            tmp = D_80A1D0DC[arg1];
        }

        if (this->unk_382 == 6) {
            frog->unk_383 = 1;
        }

        frog->unk_379 = 1;
        func_800F4BF4(&frog->actor.projectedPos, 0x28B1, tmp);
        return 1;
    }
    return 0;
}

void func_80A1BCB4(EnFr* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (player->stateFlags2 & 0x2000000) {
        if (globalCtx->msgCtx.unk_E3EE == 4) {
            globalCtx->msgCtx.unk_E3EE = 0;
        }

        func_800800F8(globalCtx, 0x100E, -0x63, &this->actor, 0);
        globalCtx->msgCtx.msgMode = 0x37;
        player->actor.posRot.pos.x = this->actor.posRot.pos.x;
        player->actor.posRot.pos.y = this->actor.posRot.pos.y;
        player->actor.posRot.pos.z = this->actor.posRot.pos.z;

        player->currentYaw = player->actor.posRot.rot.y = player->actor.shape.rot.y = this->actor.posRot.rot.y;

        this->unk_388 = 0;
        this->actionFunc = func_80A1BD94;
    } else if (func_80A1B0F8(player, this)) {
        player->unk_6A8 = &this->actor;
    }
}

void func_80A1BD94(EnFr* this, GlobalContext* globalCtx) {
    if (globalCtx->msgCtx.msgMode == 0xC) {
        globalCtx->msgCtx.msgMode = 0x37;
        D_80A1CFF0.unk_00 = 1;
        this->actionFunc = func_80A1BDFC;
    } else if (globalCtx->msgCtx.msgMode == 0x37) {
        D_80A1CFF0.unk_00 = 1;
        this->actionFunc = func_80A1BDFC;
    }
}

void func_80A1BDFC(EnFr* this, GlobalContext* globalCtx) {
    if (D_80A1CFF0.unk_00 == 0xB) {
        if ((gSaveContext.eventChkInf[13] & 2) && (gSaveContext.eventChkInf[13] & 4) &&
            (gSaveContext.eventChkInf[13] & 0x10) && (gSaveContext.eventChkInf[13] & 8) &&
            (gSaveContext.eventChkInf[13] & 0x20) && (gSaveContext.eventChkInf[13] & 0x40)) {
            this->actionFunc = func_80A1C1E4;
            this->unk_382 = 6;
            func_8010B680(globalCtx, 0x40AB, &this->actor);
        } else {
            this->unk_382 = 0;
            this->actionFunc = func_80A1BE98;
        }
    }
}

void func_80A1BE98(EnFr* this, GlobalContext* globalCtx) {
    s32 i;
    EnFr* ptr;

    for (i = 0; i < 5; i++) {
        ptr = D_80A1CFF0.unk_04[i];
        if ((ptr == NULL) || (ptr->actionFunc != func_80A1B524)) {
            return;
        }
    }

    func_8010BD58(globalCtx, 0x30);
    this->actionFunc = func_80A1BF10;
}

void func_80A1BF10(EnFr* this, GlobalContext* globalCtx) {
    this->unk_382 = 7;
    switch (globalCtx->msgCtx.unk_E3EE) {
        case 7:
            this->unk_382 = 0;
            break;
        case 6:
            this->unk_382 = 1;
            break;
        case 5:
            this->unk_382 = 2;
            break;
        case 8:
            this->unk_382 = 3;
            break;
        case 9:
            this->unk_382 = 4;
            break;
        case 10:
            this->unk_382 = 5;
            break;
        case 4:
            func_80A1C524(this, globalCtx);
            break;
        case 1:
            switch (globalCtx->msgCtx.unk_E410) {
                case 0:
                    func_80A1BC14(this, 1);
                    break;
                case 1:
                    func_80A1BC14(this, 0);
                    break;
                case 2:
                    func_80A1BC14(this, 2);
                    break;
                case 3:
                    func_80A1BC14(this, 3);
                    break;
                case 4:
                    func_80A1BC14(this, 4);
                    break;
            }
    }

    if (this->unk_382 != 7) {
        this->unk_36C = 0;
        this->actionFunc = func_80A1C05C;
    }
}

#ifdef NON_MATCHING
// regalloc
void func_80A1C05C(EnFr* this, GlobalContext* globalCtx) {
    EnFr* ptr;

    if (this->unk_36C < 0x30) {
        if (!(this->unk_36C & 3)) {
            func_80A1BC14(this, D_80A1D0EC[(this->unk_36C >> 2) & 7]);
        }
    } else if (this->unk_382 == 5) {
        this->actor.textId = 0x40AA;
        func_80A1C718(this, globalCtx, 0);
    } else if (!(gSaveContext.eventChkInf[13] & D_80A1D008[this->unk_382])) {
        ptr = D_80A1CFF0.unk_04[D_80A1D020[this->unk_382]];
        func_80078884(NA_SE_SY_CORRECT_CHIME);

        if (ptr->actionFunc == func_80A1B524) {
            ptr->unk_379 = 1;
            ptr->unk_37D = 1;
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_FROG_GROW_UP);
            this->actionFunc = func_80A1C18C;
        } else {
            this->unk_36C = 0x30;
        }
    } else {
        this->actor.textId = 0x40A9;
        func_80A1C718(this, globalCtx, 1);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Fr/func_80A1C05C.s")
#endif

void func_80A1C18C(EnFr* this, GlobalContext* globalCtx) {
    EnFr* ptr = D_80A1CFF0.unk_04[D_80A1D020[this->unk_382]];

    if (ptr->unk_37D == 0) {
        this->actor.textId = 0x40A9;
        func_80A1C718(this, globalCtx, 1);
    }
}

void func_80A1C1E4(EnFr* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 5) && func_80106BC8(globalCtx)) {
        func_80106CCC(globalCtx);
        this->unk_386 = 2;
        this->actionFunc = func_80A1C400;
    }
}

void func_80A1C248(u8 arg0) {
    s32 i;
    s32 frog;
    EnFr* ptr;

    switch (arg0) {
        case 0:
            frog = 1;
            break;
        case 1:
            frog = 0;
            break;
        case 2:
            frog = 2;
            break;
        case 3:
            frog = 3;
            break;
        case 4:
            frog = 4;
            break;
    }

    for (i = 0; i < 5; i++) {
        ptr = D_80A1CFF0.unk_04[i];
        if (i == frog) {
            ptr->unk_3A8 = 1;
        } else {
            ptr->unk_3A8 = 0;
        }
    }
}

void func_80A1C344(void) {
    s32 i;
    EnFr* ptr;
    for (i = 0; i < 5; i++) {
        ptr = D_80A1CFF0.unk_04[i];
        ptr->unk_3A8 = 0;
    }
}

u8 func_80A1C388(u8 arg0) {
    if (!(gSaveContext.eventChkInf[13] & 1)) {
        return D_80131854[arg0];
    }
    return D_80A1D0F4[(s32)Math_Rand_ZeroFloat(60.0f) % 5];
}

void func_80A1C400(EnFr* this, GlobalContext* globalCtx) {
    u8 ret;

    if (this->unk_386 != 0) {
        this->unk_386--;
        return;
    }

    this->unk_386 = 0x28;
    this->unk_380 = 0;
    func_8010BD58(globalCtx, 0x2F);
    ret = func_80A1C388(this->unk_380);
    this->unk_381 = ret;
    func_80A1C248(ret);
    this->actionFunc = func_80A1C580;
}

s32 func_80A1C474(EnFr* this, GlobalContext* globalCtx) {
    u8 sp1F;

    if (globalCtx->msgCtx.unk_E410 == this->unk_381) {
        this->unk_380++;
        if (this->unk_380 >= 0xE) {
            this->unk_380 = 0xD;
            return 1;
        }

        sp1F = (this->unk_380 < 4) ? this->unk_380 : 4;

        this->unk_381 = func_80A1C388(this->unk_380);
        func_80A1C248(this->unk_381);
        this->unk_386 = D_80A1D0B0[sp1F];
    }
    return 0;
}

void func_80A1C524(EnFr* this, GlobalContext* globalCtx) {
    func_80106CCC(globalCtx);
    this->unk_388 = 0;
    func_80078884(NA_SE_SY_OCARINA_ERROR);
    func_800ED858(0);
    D_80A1CFF0.unk_00 = 0xC;
    func_80A1C344();
    this->actionFunc = func_80A1C944;
}

void func_80A1C580(EnFr* this, GlobalContext* globalCtx) {
    s32 i;
    s32 cnt;
    EnFr* ptr;

    if (this->unk_386 == 0) {
        func_80A1C524(this, globalCtx);
        return;
    }

    this->unk_386--;
    if (globalCtx->msgCtx.msgMode == 0x32) {
        cnt = 0;
        for (i = 0; i < 5; i++) {
            ptr = D_80A1CFF0.unk_04[i];
            if ((ptr == NULL) || (ptr->actionFunc != func_80A1B524)) {
                cnt++;
            }
        }

        if ((cnt == 0) && CHECK_PAD(globalCtx->state.input[0].press, B_BUTTON)) {
            func_80A1C524(this, globalCtx);
            return;
        }
    }

    if (globalCtx->msgCtx.msgMode == 0x33) {
        globalCtx->msgCtx.msgMode = 0x31;
        switch (globalCtx->msgCtx.unk_E410) {
            case 0:
                func_80A1BC14(this, 1);
                break;
            case 1:
                func_80A1BC14(this, 0);
                break;
            case 2:
                func_80A1BC14(this, 2);
                break;
            case 3:
                func_80A1BC14(this, 3);
                break;
            case 4:
                func_80A1BC14(this, 4);
                break;
        }

        if (func_80A1C474(this, globalCtx)) {
            this->actor.textId = 0x40AC;
            func_80A1C718(this, globalCtx, 0);
        }
    }
}

void func_80A1C718(EnFr* this, GlobalContext* globalCtx, u8 arg2) {
    func_80A1C344();
    if (arg2 != 0) {
        func_80078884(NA_SE_SY_TRE_BOX_APPEAR);
    } else {
        func_80078884(NA_SE_SY_CORRECT_CHIME);
    }
    func_800ED858(0);
    globalCtx->msgCtx.msgMode = 0x37;
    this->actionFunc = func_80A1C790;
}

void func_80A1C790(EnFr* this, GlobalContext* globalCtx) {
    func_8010B680(globalCtx, this->actor.textId, &this->actor);
    this->actionFunc = func_80A1C7CC;
}

void func_80A1C7CC(EnFr* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 5) && func_80106BC8(globalCtx)) {
        this->unk_386 = 0x64;
        func_80106CCC(globalCtx);
        this->actionFunc = func_80A1C830;
    }
}

void func_80A1C830(EnFr* this, GlobalContext* globalCtx) {
    D_80A1CFF0.unk_00 = 0xC;
    this->actionFunc = func_80A1C944;
    this->unk_388 = 0;
    if ((this->unk_382 >= 0) && (this->unk_382 < 5)) {
        if (!(gSaveContext.eventChkInf[13] & D_80A1D008[this->unk_382])) {
            gSaveContext.eventChkInf[13] |= D_80A1D008[this->unk_382];
            this->unk_388 = 0x55;
        } else {
            this->unk_388 = 0x4D;
        }
    } else if (this->unk_382 == 5) {
        if (!(gSaveContext.eventChkInf[13] & D_80A1D008[this->unk_382])) {
            gSaveContext.eventChkInf[13] |= D_80A1D008[this->unk_382];
            this->unk_388 = 0x3E;
        } else {
            this->unk_388 = 0x4D;
        }
    } else if (this->unk_382 == 6) {
        if (!(gSaveContext.eventChkInf[13] & D_80A1D008[this->unk_382])) {
            gSaveContext.eventChkInf[13] |= D_80A1D008[this->unk_382];
            this->unk_388 = 0x3E;
        } else {
            this->unk_388 = 0x55;
        }
    }
}

void func_80A1C944(EnFr* this, GlobalContext* globalCtx) {
    s32 i;
    EnFr* ptr;

    if (this->unk_3A4 != NULL) {
        this->unk_3A4->freezeTimer = 10;
    }

    for (i = 0; i < 5; i++) {
        ptr = D_80A1CFF0.unk_04[i];
        if (ptr)
            ;
        if (ptr == NULL) {
            osSyncPrintf(VT_COL(RED, WHITE));
            // No frog?!
            osSyncPrintf("%s[%d]カエルがいない！？\n", "../z_en_fr.c", 1604);
            osSyncPrintf(VT_RST);
            return;
        }

        if (ptr->unk_37C != 1) {
            return;
        }
    }

    for (i = 0; i < 5; i++) {
        ptr = D_80A1CFF0.unk_04[i];
        if (ptr == NULL) {
            osSyncPrintf(VT_COL(RED, WHITE));
            // No frog?!
            osSyncPrintf("%s[%d]カエルがいない！？\n", "../z_en_fr.c", 1618);
            osSyncPrintf(VT_RST);
            return;
        }

        ptr->unk_37C = 0;
    }

    globalCtx->msgCtx.unk_E3EE = 4;
    Audio_PlayActorSound2(&this->actor, NA_SE_EV_FROG_CRY_0);
    if (this->unk_388 == 0) {
        this->actionFunc = func_80A1BCB4;
    } else {
        this->actionFunc = func_80A1CAAC;
        func_8002F434(&this->actor, globalCtx, this->unk_388, 30.0f, 100.0f);
    }
}

void func_80A1CAAC(EnFr* this, GlobalContext* globalCtx) {
    if (func_8002F410(&this->actor, globalCtx)) {
        this->actor.attachedA = NULL;
        this->actionFunc = func_80A1CB08;
    } else {
        func_8002F434(&this->actor, globalCtx, this->unk_388, 30.0f, 100.0f);
    }
}

void func_80A1CB08(EnFr* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 6) && func_80106BC8(globalCtx)) {
        this->actionFunc = func_80A1BCB4;
    }
}

void func_80A1CB58(Actor* thisx, GlobalContext* globalCtx) {
    EnFr* this = THIS;

    if (BREG(0)) {
        DebugDisplay_AddObject(this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z,
                               this->actor.posRot.rot.x, this->actor.posRot.rot.y, this->actor.posRot.rot.z, 1.0f, 1.0f,
                               1.0f, 0xFF, 0, 0, 0xFF, 4, globalCtx->state.gfxCtx);
    }

    this->unk_36C++;
    this->actionFunc(this, globalCtx);
}

s32 func_80A1CC04(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if ((limbIndex == 7) || (limbIndex == 8)) {
        *dList = NULL;
    }

    return 0;
}

void func_80A1CC2C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnFr* this = THIS;

    if ((limbIndex == 7) || (limbIndex == 8)) {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fr.c", 1735);
        Matrix_Push();
        func_800D1FD4(&globalCtx->mf_11DA0);

        gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_fr.c", 1738),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyOpa.p++, *dList);

        Matrix_Pull();
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fr.c", 1741);
    }
}

void func_80A1CD24(Actor* thisx, GlobalContext* globalCtx) {
    EnFr* this = THIS;
    s32 tmp;
    s16 params = this->actor.params - 1;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fr.c", 1754);
    func_80093D18(globalCtx->state.gfxCtx);
    if (this->unk_3A8 != 0) {
        tmp = 0x5F;
    } else {
        tmp = -1;
    }

    gDPPipeSync(gfxCtx->polyOpa.p++);
    gDPSetEnvColor(gfxCtx->polyOpa.p++, 255, 255, 255, 255);

    Lights_InitType0PositionalLight(&this->unk_35C, this->unk_3B8.x, this->unk_3B8.y, this->unk_3B8.z, 0xFF, 0xFF, 0xFF,
                                    tmp);

    gDPSetEnvColor(gfxCtx->polyOpa.p++, D_80A1D054[params].r, D_80A1D054[params].g, D_80A1D054[params].b, 255);
    gSPSegment(gfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A1D0FC[this->unk_378]));
    gSPSegment(gfxCtx->polyOpa.p++, 0x09, SEGMENTED_TO_VIRTUAL(D_80A1D0FC[this->unk_378]));

    SkelAnime_DrawSV(globalCtx, this->skelAnime1.skeleton, this->skelAnime1.limbDrawTbl, this->skelAnime1.dListCount,
                     func_80A1CC04, func_80A1CC2C, &this->actor);
    if (this->unk_3A8 != 0) {
        Matrix_Translate(this->unk_3AC.x, this->unk_3AC.y, this->unk_3AC.z, MTXMODE_NEW);
        Matrix_Scale(0.015f, 0.015f, 0.015f, MTXMODE_APPLY);
        Matrix_RotateRPY(this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z, MTXMODE_APPLY);
        SkelAnime_Draw(globalCtx, this->skelAnime2.skeleton, this->skelAnime2.limbDrawTbl, NULL, NULL, NULL);
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_fr.c", 1816);
}
