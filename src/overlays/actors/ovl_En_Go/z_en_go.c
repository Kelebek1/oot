/*
 * File: z_en_go.c
 * Overlay: ovl_En_Go
 * Description: Goron (cutscenes)
 */

#include "z_en_go.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"

#define FLAGS 0x00000039

#define THIS ((EnGo*)thisx)

void EnGo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGo_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A41604(EnGo* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, u8 arg4, f32 arg5, f32 arg6);
void func_80A416A8(EnGo* this);

void func_80A4011C(EnGo* this, GlobalContext* globalCtx);
void func_80A4020C(EnGo* this, GlobalContext* globalCtx);
void func_80A40218(EnGo* this, GlobalContext* globalCtx);
void func_80A3FEB4(EnGo* this, GlobalContext* globalCtx);
void func_80A40318(EnGo* this, GlobalContext* globalCtx);
void func_80A3FEF8(EnGo* this, GlobalContext* globalCtx);
void func_80A4008C(EnGo* this, GlobalContext* globalCtx);
void func_80A405CC(EnGo* this, GlobalContext* globalCtx);
void func_80A40494(EnGo* this, GlobalContext* globalCtx);
void func_80A40B1C(EnGo* this, GlobalContext* globalCtx);
void func_80A406E0(EnGo* this, GlobalContext* globalCtx);
void func_80A40B74(EnGo* this, GlobalContext* globalCtx);
void func_80A40D5C(EnGo* this, GlobalContext* globalCtx);
void func_80A408D8(EnGo* this, GlobalContext* globalCtx);
void func_80A40C78(EnGo* this, GlobalContext* globalCtx);
void func_80A40DCC(EnGo* this, GlobalContext* globalCtx);
void func_80A417B4(EnGo* this, GlobalContext* globalCtx);

extern UNK_TYPE D_0600CE80;
extern UNK_TYPE D_0600DE80;
extern Gfx D_0600BD80[];
extern Gfx D_0600C140[];
extern Gfx D_0600FD40[];
extern Gfx D_0600FD50[];
extern SkeletonHeader D_0600FEF0;
extern AnimationHeader D_06004930;
extern AnimationHeader D_06010590;

typedef struct {
    AnimationHeader* unk_00;
    f32 playbackSpeed;
    u8 unk_08;
    f32 transitionRate;
} EnGoStruct2;

const ActorInit En_Go_InitVars = {
    ACTOR_EN_GO,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnGo),
    (ActorFunc)EnGo_Init,
    (ActorFunc)EnGo_Destroy,
    (ActorFunc)EnGo_Update,
    (ActorFunc)EnGo_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 20, 46, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 D_80A41B2C = { 0x00, 0x0000, 0x0000, 0x0000, 0xFF };

void func_80A3E570(EnGo* this, EnGoActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

s32 func_80A3E578(GlobalContext* globalCtx, EnGo* this) {
    Player* player = PLAYER;

    switch (this->actor.params & 0xF0) {
        case 144:
            if (gSaveContext.bgsFlag != 0) {
                return 0x305E;
            } else if (INV_CONTENT(ITEM_TRADE_ADULT) > ITEM_EYEDROPS) {
                if (func_800775CC() >= 3) {
                    return 0x305E;
                } else {
                    return 0x305D;
                }
            } else if (INV_CONTENT(ITEM_TRADE_ADULT) >= ITEM_EYEDROPS) {
                player->exchangeItemId = 14;
                return 0x3059;
            } else if (INV_CONTENT(ITEM_TRADE_ADULT) >= ITEM_PRESCRIPTION) {
                return 0x3058;
            } else {
                player->exchangeItemId = 11;
                return 0x3053;
            }
            break;

        case 0:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FIRE)) {
                if (gSaveContext.infTable[16] & 0x8000) {
                    return 0x3042;
                } else {
                    return 0x3041;
                }
            } else if (CHECK_OWNED_EQUIP(EQUIP_TUNIC, 1) || (gSaveContext.infTable[16] & 0x2000)) {
                if (gSaveContext.infTable[16] & 0x4000) {
                    return 0x3038;
                } else {
                    return 0x3037;
                }
            } else if (gSaveContext.infTable[16] & 0x200) {
                if (gSaveContext.infTable[16] & 0x400) {
                    return 0x3033;
                } else {
                    return 0x3032;
                }
            } else {
                return 0x3030;
            }
            break;

        case 16:
            if (Flags_GetSwitch(globalCtx, this->actor.params >> 8)) {
                return 0x3052;
            } else {
                return 0x3051;
            }
            break;

        case 32:
            if (CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
                return 0x3027;
            } else if (gSaveContext.eventChkInf[2] & 8) {
                return 0x3021;
            } else if (gSaveContext.infTable[14] & 1) {
                return 0x302A;
            } else {
                return 0x3008;
            }
            break;

        case 48:
            if (CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
                return 0x3027;
            } else if (gSaveContext.eventChkInf[2] & 8) {
                return 0x3026;
            } else {
                return 0x3009;
            }
            break;

        case 64:
            if (CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
                return 0x3027;
            } else if (gSaveContext.eventChkInf[2] & 8) {
                return 0x3026;
            } else {
                return 0x300A;
            }
            break;

        case 80:
            if (CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
                return 0x3027;
            } else if (gSaveContext.infTable[15] & 1) {
                return 0x3015;
            } else {
                return 0x3014;
            }
            break;

        case 96:
            if (CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
                return 0x3027;
            } else if (gSaveContext.infTable[15] & 0x10) {
                return 0x3017;
            } else {
                return 0x3016;
            }
            break;

        case 112:
            if (CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
                return 0x3027;
            } else if (gSaveContext.infTable[15] & 0x100) {
                return 0x3019;
            } else {
                return 0x3018;
            }
            break;
    }

    return 0;
}

s16 func_80A3E908(GlobalContext* globalCtx, EnGo* this) {
    s16 sp2E = 1;
    f32 sp28;
    f32 sp24 = fabsf(this->actor.yDistFromLink) + 1.0f;
    sp28 = this->actor.xzDistFromLink + 1.0f;

    switch (func_8010BDBC(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 3:
        case 7:
        case 8:
        case 9:
            break;

        case 2:
            switch (this->actor.textId) {
                case 0x3008:
                    gSaveContext.infTable[14] |= 1;
                    sp2E = 0;
                    break;

                case 0x300B:
                    gSaveContext.infTable[14] |= 0x800;
                    sp2E = 0;
                    break;

                case 0x3014:
                    gSaveContext.infTable[15] |= 1;
                    sp2E = 0;
                    break;

                case 0x3016:
                    gSaveContext.infTable[15] |= 0x10;
                    sp2E = 0;
                    break;

                case 0x3018:
                    gSaveContext.infTable[15] |= 0x100;
                    sp2E = 0;
                    break;

                case 0x3036:
                    func_8002F434(&this->actor, globalCtx, GI_TUNIC_GORON, sp28, sp24);
                    gSaveContext.infTable[16] |= 0x2000;
                    sp2E = 2;
                    break;

                case 0x3037:
                    gSaveContext.infTable[16] |= 0x4000;
                    sp2E = 0;
                    break;

                case 0x3041:
                    gSaveContext.infTable[16] |= 0x8000;
                    sp2E = 0;
                    break;

                case 0x3059:
                    sp2E = 2;
                    break;

                case 0x3052:
                case 0x3054:
                case 0x3055:
                case 0x305A:
                    sp2E = 2;
                    break;

                case 0x305E:
                    sp2E = 2;
                    break;

                default:
                    sp2E = 0;
                    break;
            }
            break;

        case 4:
            sp2E = 1;
            if (func_80106BC8(globalCtx) != 0) {
                switch (this->actor.textId) {
                    case 0x300A:
                        if (globalCtx->msgCtx.choiceIndex == 0) {
                            if ((CUR_UPG_VALUE(UPG_STRENGTH) != 0) || (gSaveContext.infTable[14] & 0x800)) {
                                this->actor.textId = 0x300B;
                            } else {
                                this->actor.textId = 0x300C;
                            }
                        } else {
                            this->actor.textId = 0x300D;
                        }

                        sp2E = 1;
                        func_8010B720(globalCtx, this->actor.textId);
                        break;

                    case 0x3034:
                        if (globalCtx->msgCtx.choiceIndex == 0) {
                            if (gSaveContext.infTable[16] & 0x800) {
                                this->actor.textId = 0x3033;
                            } else {
                                this->actor.textId = 0x3035;
                            }
                        } else if (gSaveContext.infTable[16] & 0x800) {
                            this->actor.textId = 0x3036;
                        } else {
                            this->actor.textId = 0x3033;
                        }

                        sp2E = 1;
                        func_8010B720(globalCtx, this->actor.textId);
                        break;

                    case 0x3054:
                    case 0x3055:
                        if (globalCtx->msgCtx.choiceIndex == 0) {
                            sp2E = 2;
                        } else {
                            this->actor.textId = 0x3056;
                            func_8010B720(globalCtx, this->actor.textId);
                        }

                        gSaveContext.infTable[11] |= 0x10;
                        break;
                }
            }
            break;

        case 5:
            sp2E = 1;
            if (func_80106BC8(globalCtx) != 0) {
                switch (this->actor.textId) {
                    case 0x3035:
                        gSaveContext.infTable[16] |= 0x800;

                    case 0x3032:
                    case 0x3033:
                        this->actor.textId = 0x3034;
                        sp2E = 1;
                        func_8010B720(globalCtx, this->actor.textId);
                        break;

                    default:
                        sp2E = 2;
                        break;
                }
            }
            break;

        case 6:
            sp2E = 1;
            if (func_80106BC8(globalCtx) != 0) {
                sp2E = 3;
            }
            break;
    }

    return sp2E;
}

s32 func_80A3ED24(GlobalContext* globalCtx, EnGo* this, s16* arg2, f32 arg3,
                  u16 (*unkFunc1)(GlobalContext* globalCtx, EnGo* this),
                  s16 (*unkFunc2)(GlobalContext* globalCtx, EnGo* this)) {
    if (*arg2 != 0) {
        *arg2 = unkFunc2(globalCtx, this);
        return 0;
    } else {
        if (func_8002F194(&this->actor, globalCtx)) {
            *arg2 = 1;
            return 1;
        }

        if (!func_8002F2CC(&this->actor, globalCtx, arg3)) {
            return 0;
        }

        this->actor.textId = unkFunc1(globalCtx, this);
    }

    return 0;
}

void func_80A3EDE0(EnGo* this, s32 arg1) {
    static EnGoStruct2 D_80A41B38[] = {
        { 0x06004930, 0.0f, 1, 0.0f },
        { 0x06004930, 0.0f, 1, -10.0f },
        { 0x060029A8, 1.0f, 1, -10.0f },
        { 0x06010590, 1.0f, 1, -10.0f },
    };

    SkelAnime_ChangeAnim(&this->skelAnime, D_80A41B38[arg1].unk_00,
                         D_80A41B38[arg1].playbackSpeed * (((this->actor.params & 0xF0) == 0x90) ? 0.5f : 1.0f), 0.0f,
                         SkelAnime_GetFrameCount(&D_80A41B38[arg1].unk_00->genericHeader), D_80A41B38[arg1].unk_08,
                         D_80A41B38[arg1].transitionRate);
}

s32 func_80A3EE8C(EnGo* this, GlobalContext* globalCtx) {
    if ((this->actor.params & 0xF0) == 0x90) {
        return 1;
    }

    if ((globalCtx->sceneNum == 4) && !Flags_GetSwitch(globalCtx, this->actor.params >> 8) && (LINK_IS_ADULT) &&
        ((this->actor.params & 0xF0) == 0x10)) {
        return 1;
    }

    if ((globalCtx->sceneNum == 0x62) && (LINK_IS_ADULT) && ((this->actor.params & 0xF0) == 0)) {
        return 1;
    }

    if ((globalCtx->sceneNum == 0x60) && (gSaveContext.linkAge == 1) &&
        (((this->actor.params & 0xF0) == 0x20) || ((this->actor.params & 0xF0) == 0x30) ||
         ((this->actor.params & 0xF0) == 0x40))) {
        return 1;
    }

    if ((globalCtx->sceneNum == 0x62) && (gSaveContext.linkAge == 1) &&
        (((this->actor.params & 0xF0) == 0x50) || ((this->actor.params & 0xF0) == 0x60) ||
         ((this->actor.params & 0xF0) == 0x70))) {
        return 1;
    }

    return 0;
}

f32 func_80A3EFE8(EnGo* this) {
    switch (this->actor.params & 0xF0) {
        case 0:
            return 10.0f;

        case 32:
        case 48:
        case 80:
        case 96:
        case 112:
            return 20.0f;

        case 64:
            return 60.0f;

        default:
            return 20.0f;
    }
}

void func_80A3F060(EnGo* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 sp1A;

    if ((this->actionFunc != func_80A406E0) && (this->actionFunc != func_80A4020C) &&
        (this->actionFunc != func_80A40B1C)) {
        sp1A = 1;
    }

    this->unk_1E0.unk_18 = player->actor.posRot.pos;
    this->unk_1E0.unk_14 = func_80A3EFE8(this);
    func_80034A14(&this->actor, &this->unk_1E0, 4, sp1A);
}

void func_80A3F0E4(EnGo* this) {
    if (DECR(this->unk_214) == 0) {
        this->unk_216++;
        if (this->unk_216 >= 3) {
            this->unk_214 = Math_Rand_S16Offset(0x1E, 0x1E);
            this->unk_216 = 0;
        }
    }
}

s32 func_80A3F15C(EnGo* this, GlobalContext* globalCtx) {
    f32 sp24;
    s32 pad;
    Camera* cameraPtr = globalCtx->cameraPtrs[0];
    s16 tmp = this->actor.yawTowardsLink - this->actor.shape.rot.y;

    if (fabsf(tmp) > 10920.0f) {
        return 0;
    }

    sp24 = (this->actor.scale.x / 0.01f) * 10000.0f;
    if ((this->actor.params & 0xF0) == 0x90) {
        func_8005A77C(cameraPtr, 0x3F);
        sp24 *= 4.8f;
    }

    if (sp24 < fabsf(this->actor.xyzDistFromLinkSq)) {
        if (cameraPtr->setting == 0x3F) {
            func_8005A77C(cameraPtr, 1);
        }

        return 0;
    }

    return 1;
}

void func_80A3F260(EnGo* this) {
    f32 oldFrame = this->skelAnime.initialFrame;

    this->skelAnime.initialFrame = this->skelAnime.animFrameCount;
    this->skelAnime.animFrameCount = oldFrame;
}

void func_80A3F274(EnGo* this) {
    s16 save;
    s16 tmp;
    f32 frame = this->skelAnime.animCurrentFrame;

    if (((this->skelAnime.animCurrentSeg == &D_06004930) && (frame > 32.0f)) ||
        (this->skelAnime.animCurrentSeg != &D_06004930)) {
        tmp = 0xFF;
    } else {
        tmp = 0;
    }

    save = this->actor.shape.unk_14;
    Math_SmoothScaleMaxMinS(&save, tmp, 0xA, 0x3C, 1);
    this->actor.shape.unk_14 = save;
}

s32 func_80A3F300(EnGo* this, GlobalContext* globalCtx) {
    Path* path;
    Vec3s* pos;
    f32 sp2C;
    f32 sp28;

    if ((this->actor.params & 0xF) == 0xF) {
        return 0;
    }

    path = &globalCtx->setupPathList[this->actor.params & 0xF];
    pos = (Vec3s*)SEGMENTED_TO_VIRTUAL(&path->points[0]);
    pos += this->unk_218;

    sp2C = pos->x - this->actor.posRot.pos.x;
    sp28 = pos->z - this->actor.posRot.pos.z;

    Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, Math_atan2f(sp2C, sp28) * 10430.3779f, 0xA, 0x3E8, 1);
    if ((SQ(sp2C) + SQ(sp28)) < 600.0f) {
        this->unk_218++;
        if (this->unk_218 >= path->count) {
            this->unk_218 = 0;
        }

        if ((this->actor.params & 0xF0) != 0) {
            return 1;
        }

        if (Flags_GetSwitch(globalCtx, this->actor.params >> 8)) {
            return 1;
        }

        if (this->unk_218 >= this->actor.shape.rot.z) {
            this->unk_218 = 0;
        }

        return 1;
    }

    return 0;
}

s32 func_80A3F4BC(EnGo* this, GlobalContext* globalCtx) {
    Path* path;
    Vec3s* pos;

    if ((this->actor.params & 0xF) == 0xF) {
        return 0;
    }

    path = &globalCtx->setupPathList[this->actor.params & 0xF];
    pos = (Vec3s*)SEGMENTED_TO_VIRTUAL(&path->points[0]);
    pos += path->count - 1;

    this->actor.posRot.pos.x = pos->x;
    this->actor.posRot.pos.y = pos->y;
    this->actor.posRot.pos.z = pos->z;
    this->actor.initPosRot.pos = this->actor.posRot.pos;
    return 1;
}

s32 func_80A3F594(EnGo* this, u8 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, f32 arg6) {
    Vec3f sp94 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp88 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp7C = { 0.0f, 0.3f, 0.0f };
    s16 rand;
    s32 i;

    sp94 = this->actor.posRot.pos;
    sp94.y = this->actor.groundY;
    rand = (Math_Rand_ZeroOne() - 0.5f) * 65536.0f;

    for (i = arg4; i >= 0; i--, rand += (s16)(0x10000 / arg4)) {
        sp7C.x = (Math_Rand_ZeroOne() - 0.5f) * arg6;
        sp7C.z = (Math_Rand_ZeroOne() - 0.5f) * arg6;
        sp94.x = (Math_Sins(rand) * arg5) + this->actor.posRot.pos.x;
        sp94.z = (Math_Coss(rand) * arg5) + this->actor.posRot.pos.z;
        func_80A41604(this, &sp94, &sp88, &sp7C, arg1, arg2, arg3);
    }

    return 0;
}

s32 func_80A3F7C0(EnGo* this, s16 arg1, f32 arg2) {
    if (!(this->actor.bgCheckFlags & 1) || (this->actor.velocity.y > 0.0f)) {
        return 0;
    }

    if (this->unk_1E0.unk_00 != 0) {
        return 1;
    }

    if (DECR(this->unk_21C) != 0) {
        if ((this->unk_21C & 1) != 0) {
            this->actor.posRot.pos.y += 1.5f;
        } else {
            this->actor.posRot.pos.y -= 1.5f;
        }

        return 1;
    }

    this->unk_21A--;
    if (this->unk_21A <= 0) {
        if (this->unk_21A == 0) {
            this->unk_21C = Math_Rand_S16Offset(0x3C, 0x1E);
            this->unk_21A = 0;
            this->actor.velocity.y = 0.0f;
            return 1;
        }

        this->unk_21A = arg1;
    }

    this->actor.velocity.y = ((f32)this->unk_21A / arg1) * arg2;
    return 1;
}

void func_80A3F908(EnGo* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    f32 tmpf1;
    s32 ret;

    if ((this->actionFunc == func_80A406E0) || (this->actionFunc == func_80A4011C) ||
        (this->actionFunc == func_80A4020C) || (this->actionFunc == func_80A40D5C) ||
        (this->actionFunc == func_80A40DCC) || (this->actionFunc == func_80A40B74) ||
        (this->actionFunc == func_80A40C78) || (this->actionFunc == func_80A40B1C)) {
        tmpf1 = this->collider.dim.radius + 30.0f;
        tmpf1 *= this->actor.scale.x / 0.01f;
        if ((this->actor.params & 0xF0) == 0x90) {
            tmpf1 *= 4.8f;
        }

        if ((this->actor.params & 0xF0) == 0x90) {
            ret = func_80A3ED24(globalCtx, this, &this->unk_1E0.unk_00, tmpf1, func_80A3E578, func_80A3E908);
        } else {
            ret = func_800343CC(globalCtx, &this->actor, &this->unk_1E0.unk_00, tmpf1, func_80A3E578, func_80A3E908);
        }

        if (((this->actor.params & 0xF0) == 0x90) && (ret == 1)) {
            if (INV_CONTENT(ITEM_TRADE_ADULT) == ITEM_SWORD_BROKEN) {
                if (func_8002F368(globalCtx) == 0xB) {
                    if ((gSaveContext.infTable[11]) & 0x10) {
                        this->actor.textId = 0x3055;
                    } else {
                        this->actor.textId = 0x3054;
                    }
                } else {
                    this->actor.textId = 0x3053;
                }

                player->actor.textId = this->actor.textId;
            }

            if (INV_CONTENT(ITEM_TRADE_ADULT) == ITEM_EYEDROPS) {
                if (func_8002F368(globalCtx) == 0xE) {
                    this->actor.textId = 0x3059;
                } else {
                    this->actor.textId = 0x3058;
                }

                player->actor.textId = this->actor.textId;
            }
        }
    }
}

void EnGo_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGo* this = THIS;
    s32 pad;
    Vec3f sp44 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp38 = { 0.0f, 0.0f, 0.0f };

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 30.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600FEF0, NULL, 0, 0, 0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    func_80061EFC(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80A41B2C);
    if (!func_80A3EE8C(this, globalCtx)) {
        Actor_Kill(&this->actor);
        return;
    }

    if (((this->actor.params & 0xF0) != 0) && ((this->actor.params & 0xF0) != 144)) {
        this->actor.flags &= ~0x10;
        this->actor.flags &= ~0x20;
    }

    func_80A3EDE0(this, 0);
    this->actor.unk_1F = 6;
    this->unk_1E0.unk_00 = 0;
    this->actor.gravity = -1.0f;

    switch (this->actor.params & 0xF0) {
        case 0:
            Actor_SetScale(&this->actor, 0.008f);
            if (CHECK_OWNED_EQUIP(EQUIP_TUNIC, 1)) {
                func_80A3F4BC(this, globalCtx);
                func_80A3E570(this, func_80A40218);
            } else {
                this->actor.shape.unk_08 = 1400.0f;
                this->actor.speedXZ = 3.0f;
                func_80A3E570(this, func_80A4011C);
            }
            break;

        case 16:
            this->skelAnime.animCurrentFrame = SkelAnime_GetFrameCount(&D_06004930.genericHeader);
            Actor_SetScale(&this->actor, 0.01f);
            func_80A3E570(this, func_80A4020C);
            break;

        case 64:
            if (gSaveContext.infTable[14] & 0x800) {
                func_80A3F4BC(this, globalCtx);
            }

            Actor_SetScale(&this->actor, 0.015f);
            func_80A3E570(this, func_80A40218);
            break;

        case 48:
            this->actor.shape.unk_08 = 1400.0f;
            Actor_SetScale(&this->actor, 0.01f);
            func_80A3E570(this, func_80A3FEB4);
            break;

        case 144:
            this->actor.unk_1F = 5;
            Actor_SetScale(&this->actor, 0.16f);
            func_80A3E570(this, func_80A40218);
            break;

        case 32:
        case 80:
        case 96:
        case 112:
            Actor_SetScale(&this->actor, 0.01f);
            func_80A3E570(this, func_80A40218);
            break;

        default:
            Actor_Kill(&this->actor);
            break;
    }
}

void EnGo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGo* this = THIS;

    SkelAnime_Free(&this->skelAnime, globalCtx);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A3FEB4(EnGo* this, GlobalContext* globalCtx) {
    if (!(this->actor.xyzDistFromLinkSq > 1440000.0f)) {
        func_80A3E570(this, func_80A3FEF8);
    }
}

void func_80A3FEF8(EnGo* this, GlobalContext* globalCtx) {
    if ((DECR(this->unk_20E) == 0) && (this->collider.base.maskB & 1)) {
        this->collider.base.maskB &= ~1;
        globalCtx->unk_11D58(globalCtx, -4);
        func_8002F71C(globalCtx, &this->actor, 4.0f, this->actor.yawTowardsLink, 6.0f);
        this->unk_20E = 0x10;
    }

    this->actor.speedXZ = 3.0f;
    if ((func_80A3F300(this, globalCtx) == 1) && (this->unk_218 == 0)) {
        EnBom* refB00m = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.posRot.pos.x,
                                             this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0, 0, 0, 0);
        if (refB00m != NULL) {
            refB00m->timer = 0;
        }

        this->actor.speedXZ = 0.0f;
        func_80A3E570(this, func_80A4008C);
    }

    this->actor.shape.rot = this->actor.posRot.rot;
    if (func_80A3F7C0(this, 3, 6.0f)) {
        func_80A3F594(this, 0xC, 0.16f, 0.1f, 1, 10.0f, 20.0f);
    }
}

void func_80A4008C(EnGo* this, GlobalContext* globalCtx) {
    if (func_80A3F7C0(this, 3, 6.0f) != 0) {
        if (this->unk_21A == 0) {
            this->actor.shape.unk_08 = 0.0f;
            func_80A3E570(this, func_80A40218);
        } else {
            func_80A3F594(this, 0xC, 0.16f, 0.1f, 1, 10.0f, 20.0f);
        }
    }
}

void func_80A4011C(EnGo* this, GlobalContext* globalCtx) {
    if ((func_80A3F300(this, globalCtx) == 1) && Flags_GetSwitch(globalCtx, this->actor.params >> 8) &&
        (this->unk_218 == 0)) {
        this->actor.speedXZ = 0.0f;
        func_80A3E570(this, func_80A4008C);
        gSaveContext.infTable[16] |= 0x200;
    }

    this->actor.shape.rot = this->actor.posRot.rot;
    if (func_80A3F7C0(this, 3, 6.0f) != 0) {
        func_80A3F594(this, 0xC, 0.18f, 0.2f, 2, 13.0f, 20.0f);
    }
}

void func_80A4020C(EnGo* this, GlobalContext* globalCtx) {
}

void func_80A40218(EnGo* this, GlobalContext* globalCtx) {
    f32 tmpf1;

    if (DECR(this->unk_210) == 0) {
        if (func_80A3F15C(this, globalCtx)) {
            Audio_PlaySoundGeneral(NA_SE_EN_GOLON_WAKE_UP, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                   &D_801333E8);
            this->skelAnime.animPlaybackSpeed = 0.1f;
            if ((this->actor.params & 0xF0) == 0x90) {
                tmpf1 = 0.5f;
            } else {
                tmpf1 = 1.0f;
            }

            this->skelAnime.animPlaybackSpeed *= tmpf1;
            func_80A3E570(this, func_80A40318);
            if ((this->actor.params & 0xF0) == 0x90) {
                func_800800F8(globalCtx, 0x1068, -0x63, &this->actor, 0);
            }
        }
    }
}

void func_80A40318(EnGo* this, GlobalContext* globalCtx) {
    f32 tmpf1;

    if (this->skelAnime.animPlaybackSpeed != 0.0f) {
        Math_SmoothScaleMaxMinF(&this->skelAnime.animPlaybackSpeed,
                                (((this->actor.params & 0xF0) == 0x90) ? 0.5f : 1.0f) * 0.5f, 0.1f, 1000.0f, 0.1f);
        tmpf1 = this->skelAnime.animCurrentFrame;
        tmpf1 += this->skelAnime.animPlaybackSpeed;
        if (tmpf1 <= 12.0f) {
            return;
        }

        this->skelAnime.animCurrentFrame = 12.0f;
        this->skelAnime.animPlaybackSpeed = 0.0f;
        if ((this->actor.params & 0xF0) != 0x90) {
            this->unk_212 = 30;
            return;
        }
    }

    if (DECR(this->unk_212) == 0) {
        Audio_PlaySoundGeneral(NA_SE_EN_GOLON_SIT_DOWN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        func_80A3E570(this, func_80A405CC);
    } else if (func_80A3F15C(this, globalCtx) == 0) {
        func_80A3F260(this);
        this->skelAnime.animPlaybackSpeed = 0.0f;
        func_80A3E570(this, func_80A40494);
    }
}

void func_80A40494(EnGo* this, GlobalContext* globalCtx) {
    f32 tmpf1;

    Math_SmoothScaleMaxMinF(&this->skelAnime.animPlaybackSpeed,
                            (((this->actor.params & 0xF0) == 0x90) ? 0.5f : 1.0f) * -0.5f, 0.1f, 1000.0f, 0.1f);
    tmpf1 = this->skelAnime.animCurrentFrame;
    tmpf1 += this->skelAnime.animPlaybackSpeed;
    if (tmpf1 >= 0.0f) {
        return;
    }

    Audio_PlaySoundGeneral(NA_SE_EN_DODO_M_GND, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    func_80A3F594(this, 10, 0.4f, 0.1f, 0x10, 26.0f, 2.0f);
    func_80A3F260(this);
    this->skelAnime.animPlaybackSpeed = 0.0f;
    this->skelAnime.animCurrentFrame = 0.0f;
    this->unk_210 = Math_Rand_S16Offset(30, 30);
    func_80A3E570(this, func_80A40218);
}

void func_80A405CC(EnGo* this, GlobalContext* globalCtx) {
    f32 frame = SkelAnime_GetFrameCount(&D_06004930.genericHeader);
    f32 tmpf1;

    Math_SmoothScaleMaxMinF(&this->skelAnime.animPlaybackSpeed, ((this->actor.params & 0xF0) == 0x90) ? 0.5f : 1.0f,
                            0.1f, 1000.0f, 0.1f);
    tmpf1 = this->skelAnime.animCurrentFrame;
    tmpf1 += this->skelAnime.animPlaybackSpeed;
    if (!(tmpf1 < frame)) {
        this->skelAnime.animCurrentFrame = frame;
        this->skelAnime.animPlaybackSpeed = 0.0f;
        this->unk_212 = Math_Rand_S16Offset(30, 30);
        if (((this->actor.params & 0xF0) == 0x40) && !(gSaveContext.infTable[14] & 0x800)) {
            func_80A3E570(this, func_80A40B1C);
        } else {
            func_80A3E570(this, func_80A406E0);
        }
    }
}

void func_80A406E0(EnGo* this, GlobalContext* globalCtx) {
    if (((this->actor.params & 0xF0) == 0x90) && (this->unk_1E0.unk_00 == 2)) {
        if (gSaveContext.bgsFlag) {
            this->unk_1E0.unk_00 = 0;
        } else if (INV_CONTENT(ITEM_TRADE_ADULT) == ITEM_EYEDROPS) {
            func_80A3EDE0(this, 2);
            this->unk_21E = 100;
            this->unk_1E0.unk_00 = 0;
            func_80A3E570(this, func_80A40D5C);
            globalCtx->msgCtx.msgMode = 0x37;
            gSaveContext.timer2State = 0;
            func_800800F8(globalCtx, 0x105E, -0x63, &this->actor, 0);
        } else {
            this->unk_1E0.unk_00 = 0;
            func_80A3E570(this, func_80A40B74);
            func_80106CCC(globalCtx);
            func_80A40B74(this, globalCtx);
        }
    } else if (((this->actor.params & 0xF0) == 0) && (this->unk_1E0.unk_00 == 2)) {
        func_80A3E570(this, func_80A40B74);
        globalCtx->msgCtx.unk_E3E7 = 4;
        globalCtx->msgCtx.msgMode = 0x36;
    } else if ((DECR(this->unk_212) == 0) && (func_80A3F15C(this, globalCtx) == 0)) {
        func_80A3F260(this);
        this->skelAnime.animPlaybackSpeed = -0.1f;
        this->skelAnime.animPlaybackSpeed *= ((this->actor.params & 0xF0) == 0x90) ? 0.5f : 1.0f;
        func_80A3E570(this, func_80A408D8);
    }
}

void func_80A408D8(EnGo* this, GlobalContext* globalCtx) {
    f32 tmpf1;

    if (this->skelAnime.animPlaybackSpeed != 0.0f) {
        Math_SmoothScaleMaxMinF(&this->skelAnime.animPlaybackSpeed,
                                (((this->actor.params & 0xF0) == 0x90) ? 0.5f : 1.0f) * -1.0f, 0.1f, 1000.0f, 0.1f);
        tmpf1 = this->skelAnime.animCurrentFrame;
        tmpf1 += this->skelAnime.animPlaybackSpeed;
        if (tmpf1 >= 12.0f) {
            return;
        }

        this->skelAnime.animCurrentFrame = 12.0f;
        this->skelAnime.animPlaybackSpeed = 0.0f;
        if ((this->actor.params & 0xF0) != 0x90) {
            this->unk_212 = 30;
            return;
        }
    }

    if (DECR(this->unk_212) == 0) {
        func_80A3E570(this, func_80A40494);
    } else if (func_80A3F15C(this, globalCtx)) {
        func_80A3F260(this);
        Audio_PlaySoundGeneral(NA_SE_EN_GOLON_SIT_DOWN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        this->skelAnime.animPlaybackSpeed = 0.0f;
        func_80A3E570(this, func_80A405CC);
    }
}

void func_80A40A54(EnGo* this, GlobalContext* globalCtx) {
    f32 frame = 32768.0f / SkelAnime_GetFrameCount(&D_06010590.genericHeader);

    frame = this->skelAnime.animCurrentFrame * frame;
    this->actor.speedXZ = Math_Sins(frame);
    if (func_80A3F300(this, globalCtx) && (this->unk_218 == 0)) {
        func_80A3EDE0(this, 1);
        this->skelAnime.animCurrentFrame = SkelAnime_GetFrameCount(&D_06004930.genericHeader);
        this->actor.speedXZ = 0.0f;
        func_80A3E570(this, func_80A406E0);
    }
}

void func_80A40B1C(EnGo* this, GlobalContext* globalCtx) {
    if (gSaveContext.infTable[14] & 0x800) {
        func_80A3EDE0(this, 3);
        func_80A3E570(this, func_80A40A54);
    } else {
        func_80A406E0(this, globalCtx);
    }
}

void func_80A40B74(EnGo* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 pad2;
    s32 itemId;
    f32 fabs;
    f32 tmpf1;

    if (func_8002F410(&this->actor, globalCtx) != 0) {
        this->unk_1E0.unk_00 = 2;
        this->actor.attachedA = NULL;
        func_80A3E570(this, func_80A40C78);
        return;
    }

    this->unk_20C = 0;
    if ((this->actor.params & 0xF0) == 0x90) {
        if (INV_CONTENT(ITEM_TRADE_ADULT) == ITEM_CLAIM_CHECK) {
            itemId = GI_SWORD_BGS;
            this->unk_20C = 1;
        }

        if (INV_CONTENT(ITEM_TRADE_ADULT) == ITEM_EYEDROPS) {
            itemId = GI_CLAIM_CHECK;
        }

        if (INV_CONTENT(ITEM_TRADE_ADULT) == ITEM_SWORD_BROKEN) {
            itemId = GI_PERSCRIPTION;
        }
    }

    if ((this->actor.params & 0xF0) == 0) {
        itemId = GI_TUNIC_GORON;
    }

    fabs = fabsf(this->actor.yDistFromLink) + 1.0f;
    tmpf1 = this->actor.xzDistFromLink + 1.0f;
    func_8002F434(&this->actor, globalCtx, itemId, tmpf1, fabs);
}

void func_80A40C78(EnGo* this, GlobalContext* globalCtx) {
    if (this->unk_1E0.unk_00 == 3) {
        func_80A3E570(this, func_80A406E0);
        if ((this->actor.params & 0xF0) != 0x90) {
            this->unk_1E0.unk_00 = 0;
            return;
        }

        if (this->unk_20C != 0) {
            this->unk_1E0.unk_00 = 0;
            gSaveContext.bgsFlag = 1;
            return;
        }

        if (INV_CONTENT(ITEM_TRADE_ADULT) == ITEM_PRESCRIPTION) {
            this->actor.textId = 0x3058;
            func_8010B720(globalCtx, this->actor.textId);
            this->unk_1E0.unk_00 = 1;
        } else if (INV_CONTENT(ITEM_TRADE_ADULT) == ITEM_CLAIM_CHECK) {
            this->actor.textId = 0x305C;
            func_8010B720(globalCtx, this->actor.textId);
            this->unk_1E0.unk_00 = 1;
            func_800775D8();
        }
    }
}

void func_80A40D5C(EnGo* this, GlobalContext* globalCtx) {
    if (DECR(this->unk_21E) == 0) {
        this->actor.textId = 0x305A;
        func_8010B720(globalCtx, this->actor.textId);
        this->unk_1E0.unk_00 = 1;
        func_80A3E570(this, func_80A40DCC);
    }
}

void func_80A40DCC(EnGo* this, GlobalContext* globalCtx) {
    if (this->unk_1E0.unk_00 == 2) {
        func_80A3EDE0(this, 1);
        this->skelAnime.animCurrentFrame = SkelAnime_GetFrameCount(&D_06004930.genericHeader);
        func_80106CCC(globalCtx);
        func_80A3E570(this, func_80A40B74);
        func_80A40B74(this, globalCtx);
    }
}

void EnGo_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGo* this = THIS;
    s32 pad;

    Collider_CylinderUpdate(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if ((this->actionFunc == func_80A406E0) || (this->actionFunc == func_80A4020C) ||
        (this->actionFunc == func_80A40B1C)) {
        func_80034F54(globalCtx, this->unk_220, this->unk_244, 0x12);
    }

    func_80A3F274(this);
    if (this->unk_1E0.unk_00 == 0) {
        Actor_MoveForward(&this->actor);
    }

    func_8002E4B4(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    func_80A3F0E4(this);
    func_80A3F908(this, globalCtx);
    this->actionFunc(this, globalCtx);
    func_80A3F060(this, globalCtx);
}

void func_80A40F58(EnGo* this, GlobalContext* globalCtx) {
    Vec3f sp44 = { 0.0f, 0.0f, 0.0f };
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go.c", 2320);
    Matrix_Push();
    func_80093D18(globalCtx->state.gfxCtx);
    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_go.c", 2326),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, D_0600BD80);
    Matrix_MultVec3f(&sp44, &this->actor.posRot2.pos);
    Matrix_Pull();
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go.c", 2341);
}

void func_80A41068(EnGo* this, GlobalContext* globalCtx) {
    Vec3f sp44 = { 0.0f, 0.0f, 0.0f };
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go.c", 2355);
    Matrix_Push();
    func_80093D18(globalCtx->state.gfxCtx);
    Matrix_RotateRPY(globalCtx->state.frames * ((s16)this->actor.speedXZ * 0x578), 0, this->actor.shape.rot.z, 1);
    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_go.c", 2368),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, D_0600C140);
    Matrix_MultVec3f(&sp44, &this->actor.posRot2.pos);
    Matrix_Pull();
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go.c", 2383);
}

s32 func_80A411C8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGo* this = THIS;
    Vec3s sp2C;

    if (limbIndex == 17) {
        Matrix_Translate(2800.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        sp2C = this->unk_1E0.unk_08;
        Matrix_RotateX((sp2C.y / 32768.0f) * M_PI, MTXMODE_APPLY);
        Matrix_RotateZ((sp2C.x / 32768.0f) * M_PI, MTXMODE_APPLY);
        Matrix_Translate(-2800.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == 10) {
        sp2C = this->unk_1E0.unk_0E;
        Matrix_RotateY((sp2C.y / 32768.0f) * M_PI, MTXMODE_APPLY);
        Matrix_RotateX((sp2C.x / 32768.0f) * M_PI, MTXMODE_APPLY);
    }

    if ((limbIndex == 10) || (limbIndex == 11) || (limbIndex == 14)) {
        rot->y += Math_Sins(this->unk_220[limbIndex]) * 200.0f;
        rot->z += Math_Coss(this->unk_244[limbIndex]) * 200.0f;
    }

    return 0;
}

void func_80A413DC(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnGo* this = THIS;
    Vec3f sp18 = { 600.0f, 0.0f, 0.0f };

    if (limbIndex == 17) {
        Matrix_MultVec3f(&sp18, &this->actor.posRot2.pos);
    }
}

void EnGo_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnGo* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go.c", 2479);
    func_80A416A8(this);
    Matrix_Push();
    func_80A417B4(this, globalCtx);
    Matrix_Pull();
    if (this->actionFunc == func_80A40218) {
        func_80A40F58(this, globalCtx);
    } else if ((this->actionFunc == func_80A4011C) || (this->actionFunc == func_80A3FEB4) ||
               (this->actionFunc == func_80A3FEF8) || (this->actionFunc == func_80A3FEB4)) {
        func_80A41068(this, globalCtx);
    } else {
        func_800943C8(globalCtx->state.gfxCtx);
        gSPSegment(gfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(&D_0600CE80));
        gSPSegment(gfxCtx->polyOpa.p++, 0x09, SEGMENTED_TO_VIRTUAL(&D_0600DE80));
        SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                         func_80A411C8, func_80A413DC, &this->actor);
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go.c", 2525);
        func_80A417B4(this, globalCtx);
    }
}

void func_80A41604(EnGo* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, u8 arg4, f32 arg5, f32 arg6) {
    s16 i;
    EnGoStruct1* ptr = this->unk_268;

    for (i = 0; i < 20; i++, ptr++) {
        if (ptr->unk_00 != 1) {
            ptr->unk_04 = arg5;
            ptr->unk_08 = arg6;

            ptr->unk_02 = ptr->unk_01 = arg4;
            ptr->unk_00 = 1;

            ptr->unk_14 = *arg1;
            ptr->unk_2C = *arg3;
            ptr->unk_20 = *arg2;
            return;
        }
    }
}

void func_80A416A8(EnGo* this) {
    EnGoStruct1* ptr = this->unk_268;
    s16 i;

    for (i = 0; i < 20; i++, ptr++) {
        if (ptr->unk_00 != 0) {
            ptr->unk_01--;
            if (ptr->unk_01 == 0) {
                ptr->unk_00 = 0;
            }

            ptr->unk_2C.x = (Math_Rand_ZeroOne() * 0.4f) - 0.2f;
            ptr->unk_2C.z = (Math_Rand_ZeroOne() * 0.4f) - 0.2f;

            ptr->unk_14.x = ptr->unk_14.x + ptr->unk_20.x;
            ptr->unk_14.y = ptr->unk_14.y + ptr->unk_20.y;
            ptr->unk_14.z = ptr->unk_14.z + ptr->unk_20.z;

            ptr->unk_20.x = ptr->unk_20.x + ptr->unk_2C.x;
            ptr->unk_20.y = ptr->unk_20.y + ptr->unk_2C.y;
            ptr->unk_20.z = ptr->unk_20.z + ptr->unk_2C.z;

            ptr->unk_04 += ptr->unk_08;
        }
    }
}

void func_80A417B4(EnGo* this, GlobalContext* globalCtx) {
    static UNK_TYPE D_80A41BD8[] = { 0x040539B0, 0x040535B0, 0x040531B0, 0x04052DB0,
                                     0x040529B0, 0x040525B0, 0x040521B0, 0x04051DB0 };

    EnGoStruct1* ptr = this->unk_268;
    s16 i;
    u8 flag = 0;
    s16 idx;
    s16 idx2;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go.c", 2626);
    flag = 0;
    func_80093D84(globalCtx->state.gfxCtx);
    if (1) {};

    for (i = 0; i < 20; i++, ptr++) {
        if (ptr->unk_00 != 0) {
            if (!flag) {
                gfxCtx->polyXlu.p = Gfx_CallSetupDL(gfxCtx->polyXlu.p, 0);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_0600FD40);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 100, 60, 20, 0);
                flag = true;
            }

            idx = ptr->unk_01 * (255.0f / ptr->unk_02);
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 170, 130, 90, idx);
            gDPPipeSync(gfxCtx->polyXlu.p++);

            Matrix_Translate(ptr->unk_14.x, ptr->unk_14.y, ptr->unk_14.z, MTXMODE_NEW);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_Scale(ptr->unk_04, ptr->unk_04, 1.0f, MTXMODE_APPLY);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_go.c", 2664),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            idx2 = ptr->unk_01 * (8.0f / ptr->unk_02);
            gSPSegment(gfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A41BD8[idx2]));
            gSPDisplayList(gfxCtx->polyXlu.p++, D_0600FD50);
        }
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go.c", 2678);
}
