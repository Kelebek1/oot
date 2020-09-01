/*
 * File: z_en_in.c
 * Overlay: ovl_En_In
 * Description: Ingo
 */

#include "z_en_in.h"

#define FLAGS 0x00000019

#define THIS ((EnIn*)thisx)

void EnIn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnIn_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A79FB0(EnIn* this, GlobalContext* globalCtx);
void func_80A7A4C8(EnIn* this, GlobalContext* globalCtx);
void func_80A7A568(EnIn* this, GlobalContext* globalCtx);
void func_80A7A770(EnIn* this, GlobalContext* globalCtx);
void func_80A7A940(EnIn* this, GlobalContext* globalCtx);
void func_80A7AA40(EnIn* this, GlobalContext* globalCtx);
void func_80A7A848(EnIn* this, GlobalContext* globalCtx);
void func_80A7A4BC(EnIn* this, GlobalContext* globalCtx);
void func_80A7A304(EnIn* this, GlobalContext* globalCtx);
void func_80A7B024(EnIn* this, GlobalContext* globalCtx);
void func_80A7ABD4(EnIn* this, GlobalContext* globalCtx);
void func_80A7AE84(EnIn* this, GlobalContext* globalCtx);
void func_80A7AEF0(EnIn* this, GlobalContext* globalCtx);
void func_80A7B018(EnIn* this, GlobalContext* globalCtx);

extern SkeletonHeader D_06013B88;
extern AnimationHeader D_06015814;
extern AnimationHeader D_0601646C;
extern AnimationHeader D_06018C38;
extern AnimationHeader D_06001BE0;
extern AnimationHeader D_060003B4;
extern AnimationHeader D_06001BE0;
extern AnimationHeader D_06013D60;
extern AnimationHeader D_06014CA8;
extern UNK_TYPE D_060034D0;
extern Gfx D_06007A20[];
extern Gfx D_06007BF8[];

const ActorInit En_In_InitVars = {
    ACTOR_EN_IN,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_IN,
    sizeof(EnIn),
    (ActorFunc)EnIn_Init,
    (ActorFunc)EnIn_Destroy,
    (ActorFunc)EnIn_Update,
    (ActorFunc)EnIn_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 18, 46, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 D_80A7B86C = { 0x00, 0x0000, 0x0000, 0x0000, 0xFF };

static struct_D_80AA1678 D_80A7B878[] = {
    { 0x06001CC0, 1.0f, 0x00, 0.0f },   { 0x06001CC0, 1.0f, 0x00, -10.0f }, { 0x06013C6C, 1.0f, 0x00, 0.0f },
    { 0x06013C6C, 1.0f, 0x00, -10.0f }, { 0x06000CB0, 1.0f, 0x00, 0.0f },   { 0x060003B4, 1.0f, 0x00, -10.0f },
    { 0x06001BE0, 1.0f, 0x00, 0.0f },   { 0x06013D60, 1.0f, 0x00, 0.0f },   { 0x0601431C, 1.0f, 0x00, 0.0f },
    { 0x06014CA8, 1.0f, 0x00, 0.0f },
};

static AnimationHeader* D_80A7B918[] = {
    0x060151C8, 0x06015DF0, 0x06016B3C, 0x06015814, 0x0601646C, 0x060175D0, 0x06017B58, 0x06018C38,
};

static Gfx* D_80A7B938[] = {
    0x00000000, 0x00000000, 0x06013688, 0x060137C0, 0x06013910, 0x060132B8, 0x060133F0,
    0x06013540, 0x06013100, 0x06011758, 0x06012AC0, 0x06012BF0, 0x06012D20, 0x06012480,
    0x060125B0, 0x060126E0, 0x06011AD8, 0x06012350, 0x06012220, 0x06012120,
};

s32 func_80A78FB0(GlobalContext* globalCtx) {
    if (gSaveContext.eventChkInf[1] & 0x10) {
        if (gSaveContext.infTable[9] & 0x80) {
            return 0x2046;
        } else {
            return 0x2045;
        }
    }

    if (gSaveContext.infTable[9] & 0x10) {
        return 0x2040;
    } else {
        return 0x203F;
    }
}

s32 func_80A79010(GlobalContext* globalCtx) {
    Player* player = PLAYER;
    u16 reaction = Text_GetFaceReaction(globalCtx, 0x19);
    if (reaction != 0) {
        return reaction;
    }

    if (gSaveContext.eventChkInf[1] & 0x100) {
        if (gSaveContext.nightFlag == 0) {
            return 0x205F;
        } else {
            return 0x2057;
        }
    }

    if (gSaveContext.nightFlag == 1) {
        return 0x204E;
    }

    switch (gSaveContext.eventInf[0] & 0xF) {
        case 1:
            if (!(player->stateFlags1 & 0x800000)) {
                return 0x2036;
            } else if (gSaveContext.eventChkInf[1] & 0x800) {
                if (gSaveContext.infTable[10] & 4) {
                    return 0x2036;
                } else {
                    return 0x2038;
                }
            } else {
                return 0x2037;
            }
            break;

        case 3:
            if ((gSaveContext.eventInf[0] & 0x40) || (gSaveContext.eventInf[0] & 0x20)) {
                return 0x203E;
            } else {
                return 0x203D;
            }
            break;

        case 4:
            return 0x203A;

        case 5:
        case 6:
            return 0x203C;

        case 7:
            return 0x205B;
    }

    if (gSaveContext.infTable[9] & 0x400) {
        return 0x2031;
    } else {
        return 0x2030;
    }
}

s32 func_80A79168(GlobalContext* globalCtx, EnIn* this) {
    u16 reaction = Text_GetFaceReaction(globalCtx, 0x19);
    if (reaction != 0) {
        return reaction;
    } else if (LINK_IS_CHILD) {
        return func_80A78FB0(globalCtx);
    } else {
        return func_80A79010(globalCtx);
    }
}

s16 func_80A791CC(GlobalContext* globalCtx, EnIn* this) {
    s32 ret = 0;

    switch (this->actor.textId) {
        case 0x2045:
            gSaveContext.infTable[9] |= 0x80;
            break;
        case 0x203E:
            ret = 2;
            break;
        case 0x203F:
            gSaveContext.eventChkInf[1] |= 2;
            gSaveContext.infTable[9] |= 0x10;
            break;
    }

    return ret;
}

s16 func_80A7924C(GlobalContext* globalCtx, EnIn* this) {
    s32 pad;
    s32 ret = 1;

    switch (this->actor.textId) {
        case 0x2030:
        case 0x2031:
            if (globalCtx->msgCtx.choiceIndex == 1) {
                this->actor.textId = 0x2032;
            } else if (gSaveContext.rupees < 10) {
                this->actor.textId = 0x2033;
            } else {
                this->actor.textId = 0x2034;
            }
            func_8010B720(globalCtx, this->actor.textId);
            gSaveContext.infTable[9] |= 0x400;
            break;

        case 0x2034:
            if (globalCtx->msgCtx.choiceIndex == 1) {
                Rupees_ChangeBy(-10);
                this->actor.textId = 0x205C;
            } else {
                this->actor.textId = 0x2035;
            }
            func_8010B720(globalCtx, this->actor.textId);
            break;

        case 0x2036:
        case 0x2037:
            if (globalCtx->msgCtx.choiceIndex == 1) {
                ret = 2;
                break;
            }

            this->actor.textId = 0x201F;
            func_8010B720(globalCtx, this->actor.textId);
            break;

        case 0x2038:
            if ((globalCtx->msgCtx.choiceIndex == 0) && (gSaveContext.rupees >= 50)) {
                ret = 2;
                break;
            }

            this->actor.textId = 0x2039;
            func_8010B720(globalCtx, this->actor.textId);
            gSaveContext.infTable[10] |= 4;
            break;

        case 0x205B:
            if ((globalCtx->msgCtx.choiceIndex == 0) && (gSaveContext.rupees >= 50)) {
                ret = 2;
                break;
            }

            this->actor.textId = 0x2039;
            func_8010B720(globalCtx, this->actor.textId);
            gSaveContext.eventInf[0] &= ~0xF;
            gSaveContext.eventInf[0] &= ~0x20;
            gSaveContext.eventInf[0] &= ~0x40;
            this->actionFunc = func_80A7A4C8;
            break;
    }

    return ret;
}

s16 func_80A7949C(GlobalContext* globalCtx, EnIn* this) {
    s32 ret = 1;

    if (this->actor.textId == 0x2035) {
        Rupees_ChangeBy(-10);
        this->actor.textId = 0x205C;
        func_8010B720(globalCtx, this->actor.textId);
    } else {
        ret = 2;
    }
    return ret;
}

s16 func_80A79500(GlobalContext* globalCtx, EnIn* this) {
    s16 ret = 1;

    osSyncPrintf("message_check->(%d[%x])\n", func_8010BDBC(&globalCtx->msgCtx), this->actor.textId);
    switch (func_8010BDBC(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 3:
        case 6:
        case 7:
        case 8:
        case 9:
            break;

        case 2:
            ret = func_80A791CC(globalCtx, this);
            break;
        case 4:
            if (func_80106BC8(globalCtx) != 0) {
                ret = func_80A7924C(globalCtx, this);
            }
            break;
        case 5:
            if (func_80106BC8(globalCtx) != 0) {
                ret = func_80A7949C(globalCtx, this);
                break;
            }
    }

    return ret;
}

void func_80A795C8(EnIn* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 val;

    if ((this->skelAnime.animCurrentSeg == &D_060003B4) || (this->skelAnime.animCurrentSeg == &D_06001BE0) ||
        (this->skelAnime.animCurrentSeg == &D_06013D60)) {
        val = 1;
    } else {
        val = 0;
    }

    if (this->actionFunc == func_80A7A568) {
        val = 4;
    }

    if (this->actionFunc == func_80A7B024) {
        this->unk_308.unk_18 = globalCtx->view.eye;
        this->unk_308.unk_14 = 60.0f;
    } else {
        this->unk_308.unk_18 = player->actor.posRot.pos;
        this->unk_308.unk_14 = 16.0f;
    }
    func_80034A14(&this->actor, &this->unk_308, 1, val);
}

void func_80A79690(SkelAnime* skelAnime, EnIn* this, GlobalContext* globalCtx) {
    if (skelAnime->unk_3E.y < skelAnime->limbDrawTbl[0].y) {
        skelAnime->flags |= 3;
        SkelAnime_LoadAnimationType5(globalCtx, &this->actor, skelAnime, 1.0f);
    }
}

void func_80A796EC(EnIn* this, s32 arg1) {
    SkelAnime_ChangeAnim(&this->skelAnime, D_80A7B878[arg1].animation, 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A7B878[arg1].animation->genericHeader), D_80A7B878[arg1].unk_08,
                         D_80A7B878[arg1].transitionRate);
}

s32 func_80A7975C(EnIn* this, GlobalContext* globalCtx) {
    if ((this->actor.params != 1) || (this->actor.shape.rot.z != 1) || (LINK_IS_CHILD)) {
        return 0;
    }

    this->unk_1E6 = 1;
    this->collider.base.maskA &= ~1;
    SkelAnime_ChangeAnim(&this->skelAnime, D_80A7B918[this->unk_1E6], 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A7B918[this->unk_1E6]->genericHeader), 2, 0.0f);
    this->actionFunc = func_80A7A304;
    return 1;
}

s32 func_80A79830(EnIn* this, GlobalContext* globalCtx) {
    if ((globalCtx->sceneNum == SCENE_SPOT20) && (gSaveContext.linkAge == 1) && (gSaveContext.nightFlag == 0) &&
        (this->actor.shape.rot.z == 1) && !(gSaveContext.eventChkInf[1] & 0x10)) {
        return 1;
    }

    if ((globalCtx->sceneNum == SCENE_MALON_STABLE) && (gSaveContext.linkAge == 1) && (gSaveContext.nightFlag == 0) &&
        (this->actor.shape.rot.z == 3) && (gSaveContext.eventChkInf[1] & 0x10)) {
        return 1;
    }

    if ((globalCtx->sceneNum == SCENE_MALON_STABLE) && (gSaveContext.linkAge == 1) && (gSaveContext.nightFlag == 1)) {
        if ((this->actor.shape.rot.z == 2) && !(gSaveContext.eventChkInf[1] & 0x10)) {
            return 1;
        }
        if ((this->actor.shape.rot.z == 4) && (gSaveContext.eventChkInf[1] & 0x10)) {
            return 1;
        }
    }

    if ((globalCtx->sceneNum == SCENE_SPOT20) && (LINK_IS_ADULT) && (gSaveContext.nightFlag == 0)) {
        if ((this->actor.shape.rot.z == 5) && !(gSaveContext.eventChkInf[1] & 0x100)) {
            return 2;
        }
        if ((this->actor.shape.rot.z == 7) && (gSaveContext.eventChkInf[1] & 0x100)) {
            return 4;
        }
    }

    if ((globalCtx->sceneNum == SCENE_SOUKO) && (LINK_IS_ADULT) && (gSaveContext.nightFlag == 1)) {
        if ((this->actor.shape.rot.z == 6) && !(gSaveContext.eventChkInf[1] & 0x100)) {
            return 3;
        }
        if ((this->actor.shape.rot.z == 8) && (gSaveContext.eventChkInf[1] & 0x100)) {
            return 3;
        }
    }

    return 0;
}

void func_80A79A2C(EnIn* this) {
    if ((this->unk_1EE != 3) && (DECR(this->unk_1EA) == 0)) {
        this->unk_1EE++;
        if (this->unk_1EE >= 3) {
            this->unk_1EA = Math_Rand_S16Offset(0x1E, 0x1E);
            this->unk_1EE = 0;
        }
    }
}

void func_80A79AB4(EnIn* this, GlobalContext* globalCtx) {
    s32 i;
    u32 mult;

    mult = 0;
    if (this->skelAnime.animCurrentSeg != &D_06014CA8) {
        mult = globalCtx->gameplayFrames;
    }

    for (i = 0; i < 5; i++) {
        this->unk_330[i].unk_02 = (0x814 + (i * 200)) * mult;
        this->unk_330[i].unk_04 = (0x940 + (i * 200)) * mult;
        this->unk_330[i].unk_08 = (0x846 + (i * 200)) * mult;
        this->unk_330[i].unk_0A = (0x972 + (i * 200)) * mult;
        this->unk_330[i].unk_0E = (0x878 + (i * 200)) * mult;
        this->unk_330[i].unk_10 = (0x9A4 + (i * 200)) * mult;
        this->unk_330[i].unk_14 = (0x8AA + (i * 200)) * mult;
        this->unk_330[i].unk_16 = (0x9D6 + (i * 200)) * mult;
    }
}

void func_80A79BAC(EnIn* this, GlobalContext* globalCtx, s32 arg2, s32 arg3) {
    s16 sp20[] = { 0x0558, 0x04CA, 0x0157 };

    globalCtx->nextEntranceIndex = sp20[arg2];
    if (arg2 == 2) {
        gSaveContext.nextCutsceneIndex = 0xFFF0;
    }

    globalCtx->fadeTransition = arg3;
    globalCtx->sceneLoadFlag = 0x14;

    func_8002DF54(globalCtx, &this->actor, 8);
    Interface_ChangeAlpha(1);
    if (&sp20[0] == &sp20[arg2]) {
        AREG(6) = 0;
    }

    gSaveContext.timer1State = 0;
}

void func_80A79C78(EnIn* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f sp48;
    Vec3f sp3C;
    Vec3s sp34 = { 0x0000, 0x0000, 0x0000 };

    this->unk_1F0 = Gameplay_CreateSubCamera(globalCtx);
    Gameplay_ChangeCameraStatus(globalCtx, 0, 1);
    Gameplay_ChangeCameraStatus(globalCtx, this->unk_1F0, 7);
    sp48.x = this->actor.posRot.pos.x;
    sp48.y = this->actor.posRot.pos.y + 60.0f;
    sp48.z = this->actor.posRot.pos.z;

    sp3C.x = sp48.x;
    sp3C.y = sp48.y - 22.0f;
    sp3C.z = sp48.z + 40.0f;
    func_800C04D8(globalCtx, this->unk_1F0, &sp48, &sp3C);
    this->actor.shape.rot.y = Math_Vec3f_Yaw(&this->actor.posRot.pos, &sp3C);
    this->unk_308.unk_08 = sp34;
    this->unk_308.unk_0E = sp34;
    func_8010B680(globalCtx, 0x2025, NULL);
    this->unk_308.unk_00 = 1;
    player->actor.posRot.pos = this->actor.posRot.pos;
    player->actor.posRot.pos.x += 100.0f * Math_Sins(this->actor.shape.rot.y);
    player->actor.posRot.pos.z += 100.0f * Math_Coss(this->actor.shape.rot.y);
    if (player->rideActor != NULL) {
        player->rideActor->posRot.pos = player->actor.posRot.pos;
        player->rideActor->freezeTimer = 10;
    }

    player->actor.freezeTimer = 10;
    this->actor.flags &= ~1;
    ShrinkWindow_SetVal(0x20);
    Interface_ChangeAlpha(2);
}

s32 D_80A7B998 = 0;

void EnIn_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnIn* this = THIS;
    s32 pad;
    Vec3f sp1C;

    this->unk_1E4 = Object_GetIndex(&globalCtx->objectCtx, 0xC0);
    if ((this->unk_1E4 < 0) && (this->actor.params > 0)) {
        this->actionFunc = NULL;
        Actor_Kill(&this->actor);
        return;
    }

    sp1C = gSaveContext.respawn->pos;
    if ((D_80A7B998 == 0) && (sp1C.x == 1107.0f) && (sp1C.y == 0.0f) && (sp1C.z == -3740.0f)) {
        gSaveContext.eventInf[0] = 0;
        D_80A7B998 = 1;
    }

    this->actionFunc = func_80A79FB0;
}

void EnIn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnIn* this = THIS;

    if ((this->actionFunc != NULL) && (this->actionFunc != func_80A79FB0)) {
        Collider_DestroyCylinder(globalCtx, &this->collider);
    }
}

void func_80A79FB0(EnIn* this, GlobalContext* globalCtx) {
    s32 sp3C = 0;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_1E4) || (this->actor.params <= 0)) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 36.0f);
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013B88, NULL, this->limbDrawTable, this->transitionDrawTable,
                         20);
        Collider_InitCylinder(globalCtx, &this->collider);
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        func_80061EFC(&this->actor.colChkInfo, NULL, &D_80A7B86C);

        if (func_80A7975C(this, globalCtx) != 0) {
            gSaveContext.eventInf[0] &= ~0x8000;
            return;
        }

        Actor_SetScale(&this->actor, 0.01f);
        this->actor.unk_1F = 6;
        this->unk_308.unk_00 = 0;
        this->actionFunc = func_80A7A4BC;
        switch (func_80A79830(this, globalCtx)) {
            case 1:
                func_80A796EC(this, 9);
                this->actionFunc = func_80A7A4BC;
                break;

            case 3:
                func_80A796EC(this, 7);
                this->actionFunc = func_80A7A4BC;
                if (!(gSaveContext.eventChkInf[1] & 0x100)) {
                    this->actor.params = 5;
                }
                break;

            case 4:
                func_80A796EC(this, 8);
                this->unk_1EE = 3;
                this->actionFunc = func_80A7A4BC;
                break;

            case 0:
                Actor_Kill(&this->actor);
                return;

            default:
                switch (gSaveContext.eventInf[0] & 0xF) {
                    case 0:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                        if (this->actor.params == 2) {
                            sp3C = 1;
                        }
                        break;

                    case 1:
                        if (this->actor.params == 3) {
                            sp3C = 1;
                        }
                        break;

                    case 5:
                    case 6:
                        if (this->actor.params == 4) {
                            sp3C = 1;
                        }
                        break;
                }

                if (sp3C != 1) {
                    Actor_Kill(&this->actor);
                    return;
                }

                switch (gSaveContext.eventInf[0] & 0xF) {
                    case 0:
                    case 2:
                        func_80A796EC(this, 2);
                        this->actionFunc = func_80A7A4C8;
                        gSaveContext.eventInf[0] = 0;
                        break;

                    case 1:
                        this->actor.unk_1F = 3;
                        func_80A796EC(this, 2);
                        this->actionFunc = func_80A7A568;
                        func_80088B34(0x3C);
                        break;

                    case 3:
                        func_80A796EC(this, 4);
                        this->actionFunc = func_80A7A770;
                        break;

                    case 4:
                        func_80A796EC(this, 6);
                        this->unk_1EC = 8;
                        this->actionFunc = func_80A7A940;
                        break;

                    case 5:
                    case 6:
                        this->actor.unk_1F = 3;
                        func_80A796EC(this, 6);
                        this->unk_1EC = 8;
                        this->actionFunc = func_80A7AA40;
                        break;

                    case 7:
                        func_80A796EC(this, 2);
                        this->actionFunc = func_80A7A848;
                        break;
                }
        }
    }
}

void func_80A7A304(EnIn* this, GlobalContext* globalCtx) {
    if (((this->skelAnime.animCurrentSeg == &D_06015814) || (this->skelAnime.animCurrentSeg == &D_0601646C)) &&
        (this->skelAnime.animCurrentFrame == 8.0f)) {
        func_800F41E0(&this->actor.projectedPos, NA_SE_VO_IN_LASH_0, 2);
    }

    if ((this->skelAnime.animCurrentSeg == &D_06018C38) && (this->skelAnime.animCurrentFrame == 20.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_CRY_0);
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        this->unk_1E6 %= 8;
        this->unk_1E8 = this->unk_1E6;
        if ((this->unk_1E6 == 3) || (this->unk_1E6 == 4)) {
            Audio_PlaySoundGeneral(NA_SE_IT_LASH, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            if (Math_Rand_ZeroOne() < 0.3f) {
                Audio_PlaySoundGeneral(NA_SE_IT_INGO_HORSE_NEIGH, &this->actor.projectedPos, 4, &D_801333E0,
                                       &D_801333E0, &D_801333E8);
            }
        }
        SkelAnime_ChangeAnim(&this->skelAnime, D_80A7B918[this->unk_1E6], 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_80A7B918[this->unk_1E6]->genericHeader), 2, -10.0f);
    }
}

void func_80A7A4BC(EnIn* this, GlobalContext* globalCtx) {
}

void func_80A7A4C8(EnIn* this, GlobalContext* globalCtx) {
    if (this->unk_308.unk_00 == 2) {
        func_80A79BAC(this, globalCtx, 1, 0x20);
        gSaveContext.eventInf[0] = ((gSaveContext.eventInf[0] & ~0xF) | 1);
        gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & ~0x8000) | 0x8000;
        gSaveContext.infTable[10] &= ~4;
        func_800775F0(0x40);
        globalCtx->msgCtx.unk_E3E7 = 0;
        globalCtx->msgCtx.msgMode = 0x36;
        this->unk_308.unk_00 = 0;
    }
}

// I think this may be ovl_en_horse
typedef struct {
    Actor actor;
    char unk_14C[0xC];
    s32 unk_158;
} func_80A7A568_fakeActor;

void func_80A7A568(EnIn* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 arg1;
    s32 arg2;

    if ((gSaveContext.eventChkInf[1] & 0x800) == 0) {
        if ((player->stateFlags1 & 0x800000) != 0) {
            gSaveContext.infTable[10] |= 0x800;
        }
    }

    if (gSaveContext.timer1State == 0xA) {
        Audio_PlaySoundGeneral(NA_SE_SY_FOUND, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        func_80A79C78(this, globalCtx);
        this->actionFunc = func_80A7B024;
        gSaveContext.timer1State = 0;
        return;
    }

    if (this->unk_308.unk_00 == 2) {
        switch (globalCtx->msgCtx.choiceIndex) {
            case 0:
                if (gSaveContext.rupees < 50) {
                    globalCtx->msgCtx.unk_E3E7 = 4;
                    globalCtx->msgCtx.msgMode = 0x36;
                    this->unk_308.unk_00 = 0;
                    return;
                } else {
                    gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & ~0x10) |
                                               (((func_80A7A568_fakeActor*)PLAYER->rideActor)->unk_158 * 0x10);
                    gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & ~0xF) | 2;
                    arg1 = 2;
                    arg2 = 2;
                }
                break;

            default:
                Audio_PlaySoundGeneral(NA_SE_SY_FOUND, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
                if (!(gSaveContext.eventChkInf[1] & 0x800) && (gSaveContext.infTable[10] & 0x800)) {
                    gSaveContext.eventChkInf[1] |= 0x800;
                    gSaveContext.infTable[10] |= 0x800;
                }

                gSaveContext.eventInf[0] &= ~0xF;
                arg1 = 0;
                arg2 = 0x20;
                break;
        }

        func_80A79BAC(this, globalCtx, arg1, arg2);
        globalCtx->msgCtx.unk_E3E7 = 0;
        gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & ~0x8000) | 0x8000;
        globalCtx->msgCtx.msgMode = 0x36;
        this->unk_308.unk_00 = 0;
    }
}

#ifdef NON_MATCHING
// Regalloc on eventInf | 0x20
void func_80A7A770(EnIn* this, GlobalContext* globalCtx) {
    if (this->unk_308.unk_00 == 0) {
        this->actor.flags |= 0x10000;
    } else if (this->unk_308.unk_00 == 2) {
        Rupees_ChangeBy(-50);
        this->actor.flags &= ~0x10000;
        func_80A796EC(this, 3);
        this->actionFunc = func_80A7A848;
        gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & ~0xF) | 7;
        this->unk_308.unk_00 = 0;
        gSaveContext.eventInf[0] |= 0x20;
        if (!(gSaveContext.eventInf[0] & 0x40)) {
            globalCtx->msgCtx.unk_E3E7 = 4;
            globalCtx->msgCtx.msgMode = 0x36;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_In/func_80A7A770.s")
#endif

void func_80A7A848(EnIn* this, GlobalContext* globalCtx) {
    if (this->unk_308.unk_00 == 2) {
        if (((globalCtx->msgCtx.choiceIndex == 0) && (gSaveContext.rupees < 50)) ||
            (globalCtx->msgCtx.choiceIndex == 1)) {
            gSaveContext.eventInf[0] &= ~0xF;
            this->actionFunc = func_80A7A4C8;
        } else {
            func_80A79BAC(this, globalCtx, 2, 0x26);
            gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & ~0xF) | 2;
            gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & ~0x8000) | 0x8000;
            globalCtx->msgCtx.unk_E3E7 = 0;
            globalCtx->msgCtx.msgMode = 0x36;
        }

        this->unk_308.unk_00 = 0;
        gSaveContext.eventInf[0] &= ~0x20;
        gSaveContext.eventInf[0] &= ~0x40;
    }
}

#ifdef NON_MATCHING
// Regalloc on eventInf | 0x40
void func_80A7A940(EnIn* this, GlobalContext* globalCtx) {
    if (this->unk_308.unk_00 == 0) {
        this->actor.flags |= 0x10000;
        return;
    }

    if (this->unk_1EC != 0) {
        this->unk_1EC--;
        if (this->unk_1EC == 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_LOST);
        }
    }

    if (this->unk_308.unk_00 == 2) {
        this->actor.flags = this->actor.flags & 0xFFFEFFFF;
        func_80A79BAC(this, globalCtx, 2, 0x26);
        gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & ~0xF) | 2;
        gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & ~0x8000) | 0x8000;
        globalCtx->msgCtx.unk_E3E7 = 0;
        globalCtx->msgCtx.msgMode = 0x36;
        this->unk_308.unk_00 = 0;
        gSaveContext.eventInf[0] |= 0x40;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_In/func_80A7A940.s")
#endif

void func_80A7AA40(EnIn* this, GlobalContext* globalCtx) {
    Vec3f sp3C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp30;
    Vec3f sp24;

    this->unk_1F0 = Gameplay_CreateSubCamera(globalCtx);
    this->unk_1F2 = globalCtx->activeCamera;
    Gameplay_ChangeCameraStatus(globalCtx, this->unk_1F2, 1);
    Gameplay_ChangeCameraStatus(globalCtx, this->unk_1F0, 7);

    this->unk_2FC.x = this->unk_2F0.z = this->unk_2F0.x = 0;
    this->unk_2FC.z = this->unk_2FC.y = this->unk_2F0.y = 50;

    sp30 = this->actor.posRot.pos;
    sp24 = this->actor.posRot.pos;

    sp30.x += this->unk_2F0.x;
    sp30.y += this->unk_2F0.y;
    sp30.z += this->unk_2F0.z;
    sp24.x += this->unk_2FC.x;
    sp24.y += this->unk_2FC.y;
    sp24.z += this->unk_2FC.z;
    func_800C04D8(globalCtx, this->unk_1F0, &sp30, &sp24);
    this->actor.textId = 0x203B;
    func_8010B680(globalCtx, this->actor.textId, NULL);
    this->unk_308.unk_00 = 1;
    this->unk_1FC = 0;
    globalCtx->csCtx.frames = 0;
    ShrinkWindow_SetVal(0x20);
    Interface_ChangeAlpha(2);
    this->actionFunc = func_80A7ABD4;
}

void func_80A7ABD4(EnIn* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f sp48;
    Vec3f sp3C;
    s32 var;

    if (player->rideActor != NULL) {
        player->rideActor->freezeTimer = 10;
    }
    player->actor.freezeTimer = 10;

    if ((this->actor.textId == 0x203B) && (this->unk_1EC != 0)) {
        this->unk_1EC--;
        if (this->unk_1EC == 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_LOST);
        }
    }

    var = this->unk_308.unk_00;
    switch (var) {
        case 2:
            if (this->actor.textId == 0x203B) {
                this->actor.textId = 0x203C;
                func_8010B680(globalCtx, this->actor.textId, NULL);
                this->unk_308.unk_00 = 1;
                func_80A796EC(this, 3);
            } else {
                globalCtx->msgCtx.msgMode = 0x36;
                this->unk_308.unk_00 = 0;
            }
            break;

        case 0:
            if ((globalCtx->csCtx.frames++ < 50) ^ 1) {
                this->actionFunc = func_80A7AE84;
                return;
            }

            if (globalCtx->csCtx.frames == 0x2C) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_RONRON_DOOR_CLOSE);
            }

            Math_SmoothScaleMaxMinF(&this->unk_2F0.x, 0.0f, 0.06f, 10000.0f, 0.0f);
            Math_SmoothScaleMaxMinF(&this->unk_2F0.y, 50.0f, 0.06f, 10000.0f, 0.0f);
            Math_SmoothScaleMaxMinF(&this->unk_2F0.z, 0.0f, 0.06f, 10000.0f, 0.0f);
            Math_SmoothScaleMaxMinF(&this->unk_2FC.x, 0.0f, 0.06f, 10000.0f, 0.0f);
            Math_SmoothScaleMaxMinF(&this->unk_2FC.y, 150.0f, 0.06f, 10000.0f, 0.0f);
            Math_SmoothScaleMaxMinF(&this->unk_2FC.z, 300.0f, 0.06f, 10000.0f, 0.0f);

            sp48 = this->actor.posRot.pos;
            sp3C = this->actor.posRot.pos;
            sp48.x += this->unk_2F0.x;
            sp48.y += this->unk_2F0.y;
            sp48.z += this->unk_2F0.z;
            sp3C.x += this->unk_2FC.x;
            sp3C.y += this->unk_2FC.y;
            sp3C.z += this->unk_2FC.z;
            func_800C04D8(globalCtx, this->unk_1F0, &sp48, &sp3C);
            break;
    }
}

void func_80A7AE84(EnIn* this, GlobalContext* globalCtx) {
    Gameplay_ChangeCameraStatus(globalCtx, this->unk_1F2, 7);
    Gameplay_ClearCamera(globalCtx, this->unk_1F0);
    func_8002DF54(globalCtx, &this->actor, 7);
    Interface_ChangeAlpha(0x32);
    this->actionFunc = func_80A7AEF0;
}

void func_80A7AEF0(EnIn* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 tmp;
    Vec3f sp2C;

    sp2C = this->actor.posRot.pos;
    sp2C.x += 90.0f * Math_Sins(this->actor.shape.rot.y);
    sp2C.z += 90.0f * Math_Coss(this->actor.shape.rot.y);

    tmp = Math_Vec3f_Yaw(&sp2C, &player->actor.posRot.pos);
    if (ABS(tmp) >= 0x4001) {
        globalCtx->nextEntranceIndex = 0x476;
        globalCtx->sceneLoadFlag = 0x14;
        globalCtx->fadeTransition = 5;
        this->actionFunc = func_80A7B018;
    } else if (this->unk_308.unk_00 == 2) {
        globalCtx->msgCtx.unk_E3E7 = 4;
        globalCtx->msgCtx.msgMode = 0x36;
        this->unk_308.unk_00 = 0;
    }
}

void func_80A7B018(EnIn* this, GlobalContext* globalCtx) {
}

void func_80A7B024(EnIn* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 test;

    if (player->rideActor != NULL) {
        player->rideActor->freezeTimer = 10;
    }
    player->actor.freezeTimer = 10;

    if (this->unk_308.unk_00 == 2) {
        if (1) {};
        if (!(gSaveContext.eventChkInf[1] & 0x800) && (gSaveContext.infTable[10] & 0x800)) {
            gSaveContext.eventChkInf[1] |= 0x800;
            gSaveContext.infTable[10] |= 0x800;
        }

        func_80A79BAC(this, globalCtx, 0, 0x26);
        gSaveContext.eventInf[0] &= ~0xF;
        gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & ~0x8000) | 0x8000;
        globalCtx->msgCtx.unk_E3E7 = 4;
        globalCtx->msgCtx.msgMode = 0x36;
        this->unk_308.unk_00 = 0;
    }
}

void EnIn_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnIn* this = THIS;
    s32 pad;

    if (this->actionFunc == func_80A79FB0) {
        this->actionFunc(this, globalCtx);
        return;
    }

    Collider_CylinderUpdate(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    if (this->actionFunc != func_80A7A304) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        if ((this->skelAnime.animCurrentSeg == &D_06001BE0) && ((*gSaveContext.eventInf & 0xF) != 6)) {
            func_80A79690(&this->skelAnime, this, globalCtx);
        }
        func_8002E4B4(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    }

    func_80A79A2C(this);
    this->actionFunc(this, globalCtx);

    if (this->actionFunc == func_80A7A304) {
        return;
    }

    func_80A79AB4(this, globalCtx);
    if ((gSaveContext.timer2Value < 6) && (gSaveContext.timer2State != 0) && (this->unk_308.unk_00 == 0)) {
        // Weird empty cases here.
        if (func_8002F194(&this->actor, globalCtx)) {
        } else {
        }
    } else {
        func_800343CC(globalCtx, &this->actor, &this->unk_308.unk_00,
                      ((this->actor.unk_1F == 6) ? 80.0f : 320.0f) + this->collider.dim.radius, func_80A79168,
                      func_80A79500);
        if (this->unk_308.unk_00 != 0) {
            this->unk_1FA = this->unk_1F8;
            this->unk_1F8 = func_8010BDBC(&globalCtx->msgCtx);
        }
    }

    func_80A795C8(this, globalCtx);
}

s32 EnIn_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnIn* this = THIS;
    Vec3s sp2C;

    if ((this->actor.params > 0) && (limbIndex != 16) && (D_80A7B938[limbIndex] != 0)) {
        *dList = D_80A7B938[limbIndex];
    }

    if (limbIndex == 16) {
        Matrix_Translate(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        sp2C = this->unk_308.unk_08;
        Matrix_RotateZ((sp2C.x / 32768.0f) * M_PI, MTXMODE_APPLY);
        Matrix_RotateX((sp2C.y / 32768.0f) * M_PI, MTXMODE_APPLY);
        Matrix_Translate(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == 9) {
        sp2C = this->unk_308.unk_0E;
        Matrix_RotateX((sp2C.x / 32768.0f) * M_PI, MTXMODE_APPLY);
        Matrix_RotateY((sp2C.y / 32768.0f) * M_PI, MTXMODE_APPLY);
    }

    if ((limbIndex == 9) || (limbIndex == 10) || (limbIndex == 13)) {
        rot->y += Math_Sins(*(s16*)((u8*)this->unk_330 + (limbIndex * 6) + 2)) * 200.0f;
        rot->z += Math_Coss(*(s16*)((u8*)this->unk_330 + (limbIndex * 6) + 4)) * 200.0f;
    }

    return 0;
}

void EnIn_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnIn* this = THIS;
    Vec3f sp38 = { 1600.0f, 0.0f, 0.0f };

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_in.c", 2335);

    if (limbIndex == 16) {
        Matrix_MultVec3f(&sp38, &this->actor.posRot2.pos);
        this->actor.posRot2.rot = this->actor.posRot.rot;
    }

    if ((limbIndex == 12) && (this->skelAnime.animCurrentSeg == &D_06014CA8)) {
        gSPDisplayList(oGfxCtx->polyOpa.p++, D_06007A20);
    }

    if ((limbIndex == 15) && (this->skelAnime.animCurrentSeg == &D_06014CA8)) {
        gSPDisplayList(oGfxCtx->polyOpa.p++, D_06007BF8);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_in.c", 2365);
}

void EnIn_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static UNK_PTR D_80A7B9B4[] = { 0x06003590, 0x060047D0, 0x06004BD0, 0x06004390 };

    EnIn* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_in.c", 2384);

    if (this->actionFunc != func_80A79FB0) {
        func_80093D18(globalCtx->state.gfxCtx);
        gSPSegment(oGfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A7B9B4[this->unk_1EE]));
        gSPSegment(oGfxCtx->polyOpa.p++, 0x09, SEGMENTED_TO_VIRTUAL(&D_060034D0));
        SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                         EnIn_OverrideLimbDraw, EnIn_PostLimbDraw, &this->actor);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_in.c", 2416);
}
