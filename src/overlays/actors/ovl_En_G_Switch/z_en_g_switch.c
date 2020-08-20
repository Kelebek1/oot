#include "z_en_g_switch.h"
#include "vt.h"

#define FLAGS 0x00000030

#define THIS ((EnGSwitch*)thisx)

void EnGSwitch_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGSwitch_Update(Actor* thisx, GlobalContext* globalCtx);
void func_80A230A8(Actor* thisx, GlobalContext* globalCtx);
void func_80A22FDC(Actor* thisx, GlobalContext* globalCtx);

void func_80A23204(EnGSwitch* this, Vec3f* arg1, s16 arg2, s16 arg3);
void func_80A2248C(EnGSwitch* this, GlobalContext* globalCtx);
void func_80A22598(EnGSwitch* this, GlobalContext* globalCtx);
void func_80A223F8(EnGSwitch* this, GlobalContext* globalCtx);
void func_80A22764(EnGSwitch* this, GlobalContext* globalCtx);
void func_80A22680(EnGSwitch* this, GlobalContext* globalCtx);
void func_80A22B1C(EnGSwitch* this, GlobalContext* globalCtx);
void func_80A22E00(EnGSwitch* this, GlobalContext* globalCtx);
void func_80A234D4(EnGSwitch* this, GlobalContext* globalCtx);
void func_80A23314(EnGSwitch* this, GlobalContext* globalCtx);

extern Gfx D_06001960[];
extern Gfx D_060017C0[];
extern Gfx G_SWITCH_D_04042440[];

typedef struct {
    Actor actor;
    char unk_14C[0xA];
    s16 unk_156;
    char unk_158[0xE];
    s16 unk_166[1];
} EnGSwitchFakeActor;

static s16 D_80A236E0 = 0;

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x09, 0x00, 0x20, COLSHAPE_CYLINDER },
    { 0x02, { 0x00000000, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x01, 0x00 },
    { 13, 40, 0, { 0, 0, 0 } },
};

const ActorInit En_G_Switch_InitVars = {
    ACTOR_EN_G_SWITCH,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnGSwitch),
    (ActorFunc)EnGSwitch_Init,
    (ActorFunc)EnGSwitch_Destroy,
    (ActorFunc)EnGSwitch_Update,
    NULL,
};

Vec3f D_80A2373C = { 0.0f, 0.0f, 0.0f };
Vec3f D_80A23748 = { 0.0f, 0.0f, 0.0f };
s8 D_80A23754[] = { 0x00, 0x02, 0x04, 0x05, 0x07 };

UNK_TYPE D_80A2375C[] = {
    0x04042140, 0x04042160, 0x04042180, 0x040421C0, 0x040421A0, 0x040421E0,
};

void EnGSwitch_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGSwitch* this = THIS;
    s32 pad;

    this->unk_150 = (this->actor.params >> 0xC) & 0xF;
    this->unk_154 = this->actor.params & 0x3F;
    this->unk_15C = 100;
    // Index
    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ インデックス ☆☆☆☆☆ %x\n" VT_RST, this->unk_150);
    // Save
    osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ セーブ\t     ☆☆☆☆☆ %x\n" VT_RST, this->unk_154);
    switch (this->unk_150) {
        case 0:
            osSyncPrintf("\n\n");
            // Parent switch spawn
            osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 親スイッチ発生 ☆☆☆☆☆ %x\n" VT_RST, this->actor.params);
            D_80A236E0 = 0;
            this->unk_152 = this->actor.params >> 6;
            this->unk_152 &= 0x3F;
            // Largest check count
            osSyncPrintf(VT_FGCOL(PURPLE) "☆☆☆☆☆ 最大チェック数 ☆☆☆☆☆ %d\n" VT_RST, this->unk_152);
            osSyncPrintf("\n\n");
            if (Flags_GetSwitch(globalCtx, this->unk_154)) {
                // The developers would like you to be informed that you
                // have made unfortunate contact with an event that has taken you aback.
                osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ Ｙｏｕ ａｒｅ Ｓｈｏｃｋ！  ☆☆☆☆☆ %d\n" VT_RST, this->unk_154);
                Actor_Kill(&this->actor);
                return;
            }

            this->actionFunc = func_80A2248C;
            break;

        case 1:
            osSyncPrintf("\n\n");
            // Child switch spawn
            osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 子スイッチ発生 ☆☆☆☆☆ %x\n" VT_RST, this->actor.params);
            this->unk_158 = 5;
            this->unk_15C = 20;
            Collider_InitCylinder(globalCtx, &this->collider);
            Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
            this->actor.draw = func_80A230A8;
            this->actor.shape.unk_08 = 700.0f;
            if (Flags_GetSwitch(globalCtx, this->unk_154)) {
                // "
                osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ Ｙｏｕ ａｒｅ Ｓｈｏｃｋ！  ☆☆☆☆☆ %d\n" VT_RST, this->unk_154);
                Actor_Kill(&this->actor);
                return;
            }

            Actor_SetScale(&this->actor, 0.03f);
            this->actionFunc = func_80A22598;
            break;

        case 2:
            osSyncPrintf("\n\n");
            // Horseback archery pot
            osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ やぶさめぶち抜き壷 ☆☆☆☆☆ \n" VT_RST);
            this->actor.gravity = -3.0f;
            this->unk_158 = Math_Rand_ZeroFloat(2.99f);
            Collider_InitCylinder(globalCtx, &this->collider);
            Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
            this->actor.scale.x = 0.25f;
            this->actor.scale.y = 0.45f;
            this->actor.scale.z = 0.25f;
            this->collider.body.bumper.flags = 0x1F820;
            this->unk_15E = 0x12C;
            this->unk_178 = Object_GetIndex(&globalCtx->objectCtx, this->unk_15E);
            if (this->unk_178 < 0) {
                Actor_Kill(&this->actor);
                // Wat
                osSyncPrintf(VT_FGCOL(PURPLE) " なにみの？ %d\n" VT_RST "\n", this->unk_178);
                // Bank's screwy!
                osSyncPrintf(VT_FGCOL(CYAN) " バンクおかしいしぞ！%d\n" VT_RST "\n", this->actor.params);
            }

            this->collider.dim.radius = 0x18;
            this->collider.dim.height = 0x4A;
            this->collider.dim.yShift = 0;
            this->actionFunc = func_80A223F8;
            break;

        case 3:
            this->actor.shape.unk_08 = 700.0f;
            Actor_SetScale(&this->actor, 0.05f);
            Collider_InitCylinder(globalCtx, &this->collider);
            Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
            this->actor.draw = func_80A230A8;
            this->collider.dim.radius = 0x14;
            this->collider.dim.height = 0x3C;
            this->collider.dim.yShift = 5;
            this->actionFunc = func_80A22764;
            break;
    }
}

void EnGSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGSwitch* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A22250(EnGSwitch* this, GlobalContext* globalCtx) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44 = D_80A2373C;
    Vec3f sp38 = D_80A23748;
    s32 i;

    sp5C.x = Math_Rand_CenteredFloat(40.0f) + this->actor.posRot.pos.x;
    sp5C.y = Math_Rand_CenteredFloat(35.0f) + (this->actor.posRot.pos.y + 30.0f);
    sp5C.z = Math_Rand_CenteredFloat(40.0f) + this->actor.posRot.pos.z;
    sp50.x = this->collider.body.bumper.unk_06.x;
    sp50.y = this->collider.body.bumper.unk_06.y;
    sp50.z = this->collider.body.bumper.unk_06.z;
    func_80029CC8(globalCtx, 0, 0x2BC, &sp50);
    if (this->unk_150 == 2) {
        sp38.y = 15.0f;
        func_8002A5F4(globalCtx, &sp50, &sp38, &sp44, 5, 2);
    }
    if (this->unk_150 == 3) {
        for (i = 0; i < this->unk_15C; i++) {
            func_80A23204(this, &sp5C, 100, this->unk_158);
        }
    }
}

void func_80A223F8(EnGSwitch* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_178)) {
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_178].segment);
        this->actor.objBankIndex = this->unk_178;
        this->actor.draw = func_80A22FDC;
        this->actionFunc = func_80A22B1C;
    }
}

void func_80A2248C(EnGSwitch* this, GlobalContext* globalCtx) {

    if ((this->unk_16A < D_80A236E0) && (D_80A236E0 < 5)) {
        // Sound?
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 音？ ☆☆☆☆☆ %d\n" VT_RST, this->unk_16A);
        func_800F4BF4(&D_801333D4, NA_SE_EV_FIVE_COUNT_LUPY, D_80A23754[this->unk_16A]);
        this->unk_16A = D_80A236E0;
    }

    if (D_80A236E0 >= this->unk_152) {
        // It's the end of the world
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 時はまさに世紀末〜  ☆☆☆☆☆ %d\n" VT_RST, this->unk_154);
        // LAST
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ らすとぉ！          ☆☆☆☆☆ \n" VT_RST);
        if ((globalCtx->sceneNum == 0xB) && (this->actor.room == 2)) {
            Flags_SetTempClear(globalCtx, this->actor.room);
        } else {
            func_80078884(NA_SE_SY_CORRECT_CHIME);
            Flags_SetSwitch(globalCtx, this->unk_154);
        }

        func_80078884(NA_SE_SY_GET_RUPY);
        Actor_Kill(&this->actor);
    }
}

void func_80A22598(EnGSwitch* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->actor.shape.rot.y += 0x800;
    if (this->actor.xyzDistFromLinkSq < 900.0f) {
        Rupees_ChangeBy(5);
        D_80A236E0++;
        func_80078884(NA_SE_SY_GET_RUPY);
        this->actor.posRot.pos = player->actor.posRot.pos;
        this->actor.posRot.pos.y += 40.0f;
        if (LINK_IS_ADULT) {
            this->actor.posRot.pos.y += 20.0f;
        }

        this->actor.gravity = 0.0f;
        this->unk_156 = 0xF;
        this->actionFunc = func_80A22680;
    }
}

void func_80A22680(EnGSwitch* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->actor.shape.rot.y += 0x3C0;
    if (this->unk_156 == 0) {
        Actor_Kill(&this->actor);
        return;
    }

    this->actor.posRot.pos = player->actor.posRot.pos;
    this->actor.posRot.pos.y =
        (Math_Sins(this->unk_156 * 0x3A98) * (this->unk_156 * 0.3f)) + (player->actor.posRot.pos.y + 40.0f);
    if (LINK_IS_ADULT) {
        this->actor.posRot.pos.y += 20.0f;
    }
}

void func_80A22764(EnGSwitch* this, GlobalContext* globalCtx) {
    EnGSwitchFakeActor* refActor;

    this->actor.shape.rot.y += 0x3C0;
    if (this->unk_162 == 0) {
        switch (this->unk_166) {
            case 2:
                Actor_MoveForward(&this->actor);
                if (this->actor.velocity.y < 0.0f) {
                    if (this->actor.posRot.pos.y < (this->actor.initPosRot.pos.y - 50.0f)) {
                        refActor = (EnGSwitchFakeActor*)this->actor.attachedA;
                        this->actor.velocity.y = 0.0f;
                        this->actor.gravity = 0.0f;
                        if (refActor->actor.update != NULL) {
                            refActor->unk_166[this->unk_160] = 1;
                        }
                        Actor_Kill(&this->actor);
                    }
                }
                break;

            case 4:
                func_8002D7EC(&this->actor);
                if (this->actor.velocity.x < 0.0f) {
                    if (this->actor.posRot.pos.x < this->unk_16C) {
                        refActor = (EnGSwitchFakeActor*)this->actor.attachedA;
                        if (refActor->actor.update != NULL) {
                            refActor->unk_166[this->unk_160] = 1;
                        }

                        Actor_Kill(&this->actor);
                    }
                }
                break;

            case 5:
                func_8002D7EC(&this->actor);
                if (this->unk_16C < this->actor.posRot.pos.x) {
                    refActor = (EnGSwitchFakeActor*)this->actor.attachedA;
                    if (refActor->actor.update != NULL) {
                        refActor->unk_166[this->unk_160] = 1;
                    }

                    Actor_Kill(&this->actor);
                }
                break;

            default:
                switch (this->unk_168) {
                    case 0:
                        if ((fabsf(this->actor.posRot.pos.x - this->unk_16C) > 5.0f) ||
                            (fabsf(this->actor.posRot.pos.y - this->unk_170) > 5.0f)) {
                            Math_SmoothScaleMaxF(&this->actor.posRot.pos.x, this->unk_16C, 0.3f, 30.0f);
                            Math_SmoothScaleMaxF(&this->actor.posRot.pos.y, this->unk_170, 0.3f, 30.0f);
                        } else {
                            this->unk_168 = 1;
                            this->unk_164 = 0x3C;
                        }
                        break;

                    case 1:
                        if (this->unk_164 == 0) {
                            if ((fabsf(this->actor.posRot.pos.x - this->actor.initPosRot.pos.x) > 5.0f) ||
                                (fabsf(this->actor.posRot.pos.y - this->actor.initPosRot.pos.y) > 5.0f)) {
                                Math_SmoothScaleMaxF(&this->actor.posRot.pos.x, this->actor.initPosRot.pos.x, 0.3f,
                                                     30.0f);
                                Math_SmoothScaleMaxF(&this->actor.posRot.pos.y, this->actor.initPosRot.pos.y, 0.3f,
                                                     30.0f);
                            } else {
                                refActor = (EnGSwitchFakeActor*)this->actor.attachedA;
                                if (refActor->actor.update != NULL) {
                                    refActor->unk_166[this->unk_160] = 1;
                                }

                                Actor_Kill(&this->actor);
                            }
                        }
                        break;
                }
                break;
        }

        if ((this->collider.base.acFlags & 2) || BREG(8)) {
            this->collider.base.acFlags &= ~2;
            refActor = (EnGSwitchFakeActor*)this->actor.attachedA;
            if (refActor->actor.update != NULL) {
                refActor->unk_156++;
                refActor->unk_166[this->unk_160] = 2;
                func_80078884(0x28D3);
                func_80078884(0x4803);
                // Yeeeees! HIT!
                osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ いぇぇーす！ＨＩＴ！！ ☆☆☆☆☆ %d\n" VT_RST, refActor->unk_156);
                func_80A22250(this, globalCtx);
                this->unk_156 = 0x32;
                this->unk_15A = 1;
                this->actionFunc = func_80A22E00;
            }
        }
    }
}

void func_80A22B1C(EnGSwitch* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 tmpf1;
    f32 tmpf2;
    Vec3f spD0;
    Vec3f spC4;
    f32 rand;
    s32 randResult;
    s32 i;
    s16 tmp;
    Vec3f* pos;

    this->actor.shape.rot.y += 0x3C0;
    if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= ~2;
        pos = &this->actor.posRot.pos;
        for (i = 0, tmp = 0; i < 30; i++, tmp += 0x4E20) {
            tmpf1 = Math_Sins(tmp);
            tmpf2 = Math_Coss(tmp);

            spD0.x = tmpf1 * 8.0f;
            spD0.y = Math_Rand_CenteredFloat(5.0f) + 10.0f;
            spD0.z = tmpf2 * 8.0f;

            spC4.x = spD0.x * 0.5f;
            spC4.y = (Math_Rand_ZeroOne() * 15.0f) + 10.0f;
            spC4.z = spD0.z * 0.5f;

            spD0.x += pos->x;
            spD0.y += pos->y;
            spD0.z += pos->z;

            rand = Math_Rand_ZeroOne();
            if (rand < 0.2f) {
                randResult = 0x60;
            } else if (rand < 0.6f) {
                randResult = 0x40;
            } else {
                randResult = 0x20;
            }

            func_80029E8C(globalCtx, &spD0, &spC4, &this->actor.posRot.pos, -0xF0, randResult, 0xA, 0xA, 0,
                          (Math_Rand_ZeroOne() * 130.0f) + 30.0f, 0, 0x20, 0x3C, -1, 0x12C, D_06001960);
        }

        func_80033480(globalCtx, &this->actor.posRot.pos, 30, 4, 0x14, 0x32, 0);
        Audio_PlaySoundAtPosition(globalCtx, &this->actor.posRot.pos, 0x28, NA_SE_EV_POT_BROKEN);
        func_80A22250(this, globalCtx);
        this->unk_156 = 50;
        this->unk_15A = 1;
        this->actionFunc = func_80A22E00;
    }
}

void func_80A22E00(EnGSwitch* this, GlobalContext* globalCtx) {
    if (this->unk_156 == 0) {
        Actor_Kill(&this->actor);
    }
}

void EnGSwitch_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGSwitch* this = THIS;
    s32 pad;

    this->actionFunc(this, globalCtx);
    if (this->unk_156 != 0) {
        this->unk_156--;
    }

    if (this->unk_164 != 0) {
        this->unk_164--;
    }

    if (this->unk_162 != 0) {
        this->unk_162--;
    }

    if ((this->unk_150 != 0) && (this->unk_150 != 1) && (this->unk_150 != 3)) {
        Actor_MoveForward(&this->actor);
        func_8002E4B4(globalCtx, &this->actor, 50.0f, 50.0f, 100.0f, 0x1C);
    }

    if (this->actor.draw != NULL) {
        if (this->unk_150 == 3) {
            func_80A23314(this, globalCtx);
        }

        if ((this->actionFunc != func_80A22E00) && (this->actionFunc != func_80A22598)) {
            Collider_CylinderUpdate(&this->actor, &this->collider);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }

    if ((BREG(0)) && (this->unk_150 == 0)) {
        DebugDisplay_AddObject(this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z,
                               this->actor.posRot.rot.x, this->actor.posRot.rot.y, this->actor.posRot.rot.z, 1.0f, 1.0f,
                               1.0f, 0xFF, 0, 0, 0xFF, 4, globalCtx->state.gfxCtx);
    }
}

void func_80A22FDC(Actor* thisx, GlobalContext* globalCtx) {
    EnGSwitch* this = THIS;
    s32 pad;

    if (this->unk_15A == 0) {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_g_switch.c", 918);
        func_80093D18(globalCtx->state.gfxCtx);
        if (1) {};
        gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_g_switch.c", 925),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyOpa.p++, D_060017C0);
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_g_switch.c", 928);
    }
}

void func_80A230A8(Actor* thisx, GlobalContext* globalCtx) {
    EnGSwitch* this = THIS;
    s32 pad;

    if (this->unk_15A == 0) {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_g_switch.c", 951);
        func_80093D18(globalCtx->state.gfxCtx);
        if (1) {};
        func_8002EBCC(thisx, globalCtx, 0);
        gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_g_switch.c", 957),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A2375C[this->unk_158]));
        gSPDisplayList(gfxCtx->polyOpa.p++, G_SWITCH_D_04042440);
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_g_switch.c", 961);
    }

    if (this->unk_150 == 3) {
        func_80A234D4(this, globalCtx);
    }
}

void func_80A23204(EnGSwitch* this, Vec3f* arg1, s16 arg2, s16 arg3) {
    EnGSwitchStruct1* ptr = &this->unk_1C8[0];
    s32 pad;
    Vec3f sp34;
    f32 sp30;
    s16 i;

    for (i = 0; i < this->unk_15C; i++, ptr++) {
        if (ptr->unk_12 == 0) {
            ptr->unk_00 = *arg1;
            ptr->unk_0C = arg2;
            ptr->unk_10 = arg3;
            ptr->unk_0E = 30;
            ptr->unk_20.x = 0.0f;
            ptr->unk_20.y = 0.0f;
            ptr->unk_20.z = 0.0f;
            sp30 = Math_Rand_CenteredFloat(1000.0f) - 13000.0f;
            Matrix_RotateY(Math_Rand_CenteredFloat(65535.0f), 0);
            Matrix_RotateX(sp30, 1);
            sp34.x = sp34.y = 0.0f;
            sp34.z = 20.0f;
            Matrix_MultVec3f(&sp34, &ptr->unk_14);
            ptr->unk_12 = 1;
            return;
        }
    }
}

void func_80A23314(EnGSwitch* this, GlobalContext* globalCtx) {
    EnGSwitchStruct1* ptr = &this->unk_1C8[0];
    s16 i;
    Vec3f tmp;

    for (i = 0; i < this->unk_15C; i++, ptr++) {
        if (ptr->unk_12 != 0) {
            ptr->unk_20.x += (Math_Rand_ZeroOne() * 10.0f) + 15.0f;
            ptr->unk_20.y += (Math_Rand_ZeroOne() * 10.0f) + 15.0f;
            ptr->unk_20.z += (Math_Rand_ZeroOne() * 10.0f) + 15.0f;
            tmp.x = ptr->unk_00.x + ptr->unk_14.x;
            tmp.y = ptr->unk_00.y + ptr->unk_14.y;
            tmp.z = ptr->unk_00.z + ptr->unk_14.z;
            Math_SmoothScaleMaxF(&ptr->unk_00.x, tmp.x, 0.3f, 30.0f);
            Math_SmoothScaleMaxF(&ptr->unk_00.y, tmp.y, 0.8f, 250.0f);
            Math_SmoothScaleMaxF(&ptr->unk_00.z, tmp.z, 0.3f, 30.0f);
            Math_SmoothScaleMaxF(&ptr->unk_14.y, -20.0f, 0.9f, 1.0f);
            if (ptr->unk_0E != 0) {
                ptr->unk_0E--;
            } else if (ptr->unk_0C < 10) {
                ptr->unk_12 = 0;
            } else {
                ptr->unk_0C -= 2;
            }
        }
    }
}

void func_80A234D4(EnGSwitch* this, GlobalContext* globalCtx) {
    GraphicsContext* localGfxCtx = globalCtx->state.gfxCtx;
    s16 i;
    f32 tmpf1;
    EnGSwitchStruct1* ptr = &this->unk_1C8[0];
    s32 pad;
    GraphicsContext* gfxCtx = localGfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, localGfxCtx, "../z_en_g_switch.c", 1073);
    func_80093D18(globalCtx->state.gfxCtx);
    for (i = 0; i < this->unk_15C; i++, ptr++) {
        if (ptr->unk_12 != 0) {
            tmpf1 = ptr->unk_0C / 10000.0f;
            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, MTXMODE_NEW);
            Matrix_Scale(tmpf1, tmpf1, tmpf1, MTXMODE_APPLY);
            Matrix_RotateX(ptr->unk_20.x, MTXMODE_APPLY);
            Matrix_RotateY(ptr->unk_20.y, MTXMODE_APPLY);
            Matrix_RotateZ(ptr->unk_20.z, MTXMODE_APPLY);
            gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_g_switch.c", 1088),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPSegment(gfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A2375C[ptr->unk_10]));
            gSPDisplayList(gfxCtx->polyOpa.p++, G_SWITCH_D_04042440);
        }
    }

    Graph_CloseDisps(dispRefs, localGfxCtx, "../z_en_g_switch.c", 1095);
}
