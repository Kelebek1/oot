/*
 * File: z_en_go2.c
 * Overlay: ovl_En_Go2
 * Description: Gorons
 */

#include "z_en_go2.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"

#define FLAGS 0x00000039

#define THIS ((EnGo2*)thisx)

void EnGo2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGo2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGo2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGo2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A4696C(EnGo2* this, GlobalContext* globalCtx);
void func_80A46DBC(EnGo2* this, GlobalContext* globalCtx);
void func_80A46B40(EnGo2* this, GlobalContext* globalCtx);
void func_80A46E54(EnGo2* this, GlobalContext* globalCtx);
void func_80A47578(EnGo2* this, GlobalContext* globalCtx);
void func_80A46CD8(EnGo2* this, GlobalContext* globalCtx);
void func_80A46D5C(EnGo2* this, GlobalContext* globalCtx);
void func_80A47024(EnGo2* this, GlobalContext* globalCtx);
void func_80A46F88(EnGo2* this, GlobalContext* globalCtx);
void func_80A47490(EnGo2* this, GlobalContext* globalCtx);
void func_80A45E48(EnGo2* this, GlobalContext* globalCtx);
void func_80A47158(EnGo2* this, GlobalContext* globalCtx);
void func_80A470E8(EnGo2* this, GlobalContext* globalCtx);
void func_80A4725C(EnGo2* this, GlobalContext* globalCtx);

extern SkeletonHeader D_0600FEF0;
extern AnimationHeader D_06000D5C;
extern AnimationHeader D_06000750;
extern AnimationHeader D_06004930;
extern Gfx D_0600FD40[];
extern Gfx D_0600FD50[];
extern Gfx D_0600BD80[];
extern Gfx D_0600C140[];

static UNK_TYPE D_80A480D0[] = { 0x040539B0, 0x040535B0, 0x040531B0, 0x04052DB0,
                                 0x040529B0, 0x040525B0, 0x040521B0, 0x04051DB0 };

static Vec3f D_80A480F0 = { 0.0f, 0.0f, 0.0f };
static Vec3f D_80A480FC = { 0.0f, 0.0f, 0.0f };
static Vec3f D_80A48108 = { 0.0f, 0.3f, 0.0f };

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x09, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000008, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 40, 65, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 D_80A48140 = { 0x00, 0x0000, 0x0000, 0x0000, 0xFF };

const ActorInit En_Go2_InitVars = {
    ACTOR_EN_GO2,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnGo2),
    (ActorFunc)EnGo2_Init,
    (ActorFunc)EnGo2_Destroy,
    (ActorFunc)EnGo2_Update,
    (ActorFunc)EnGo2_Draw,
};

static s16 D_80A4816C[][5] = {
    { 0x0000, 0x0000, 0x0000, 0x0044, 0x0094 }, { 0x0000, 0x0000, 0x0000, 0x0018, 0x0034 },
    { 0x0000, 0x0140, 0x017C, 0x0190, 0x0078 }, { 0x0000, 0x0000, 0x0000, 0x001E, 0x0044 },
    { 0x0000, 0x0000, 0x0000, 0x002E, 0x005A }, { 0x0000, 0x0000, 0x0000, 0x001E, 0x0044 },
    { 0x0000, 0x0000, 0x0000, 0x001E, 0x0044 }, { 0x0000, 0x0000, 0x0000, 0x001E, 0x0044 },
    { 0x0000, 0x0000, 0x0000, 0x001E, 0x0044 }, { 0x0000, 0x0000, 0x0000, 0x001E, 0x0044 },
    { 0x0000, 0x0000, 0x0000, 0x001E, 0x0044 }, { 0x0000, 0x0000, 0x0000, 0x001E, 0x0044 },
    { 0x0000, 0x0000, 0x0000, 0x001E, 0x0044 }, { 0x0000, 0x0000, 0x0000, 0x001E, 0x0044 },
};

typedef struct {
    f32 unk_00;
    f32 unk_04;
    s8 unk_08;
    f32 unk_0C;
} EnGo2Struct1;

typedef struct {
    u8 unk_00;
    f32 unk_04;
    f32 unk_08;
    s32 unk_0C;
    f32 unk_10;
    f32 unk_14;
} EnGo2Struct2;

static EnGo2Struct1 D_80A481F8[] = {
    { 30.0f, 0.026f, 0x06, 60.0f }, { 24.0f, 0.008f, 0x06, 30.0f }, { 28.0f, 0.16f, 0x05, 380.0f },
    { 28.0f, 0.01f, 0x07, 40.0f },  { 30.0f, 0.015f, 0x06, 30.0f }, { 28.0f, 0.01f, 0x06, 30.0f },
    { 28.0f, 0.01f, 0x06, 30.0f },  { 28.0f, 0.01f, 0x06, 30.0f },  { 28.0f, 0.01f, 0x06, 30.0f },
    { 28.0f, 0.01f, 0x06, 30.0f },  { 28.0f, 0.01f, 0x06, 30.0f },  { 28.0f, 0.01f, 0x06, 30.0f },
    { 28.0f, 0.01f, 0x06, 30.0f },  { 28.0f, 0.01f, 0x06, 30.0f },
};

static f32 D_80A482D8[][2] = {
    { 80.0f, 80.0f }, { -10.0f, -10.0f }, { 800.0f, 800.0f }, { 0.0f, 0.0f },   { 20.0f, 40.0f },
    { 20.0f, 20.0f }, { 20.0f, 20.0f },   { 20.0f, 20.0f },   { 20.0f, 20.0f }, { 20.0f, 20.0f },
    { 20.0f, 20.0f }, { 20.0f, 20.0f },   { 20.0f, 20.0f },   { 20.0f, 20.0f },
};

static struct_80034EC0_Entry D_80A48348[] = {
    { 0x06004930, 0.0f, 0.0f, -1.0f, 0x00, 0.0f },  { 0x06004930, 0.0f, 0.0f, -1.0f, 0x00, -8.0f },
    { 0x060029A8, 1.0f, 0.0f, -1.0f, 0x00, -8.0f }, { 0x06010590, 1.0f, 0.0f, -1.0f, 0x00, -8.0f },
    { 0x06003768, 1.0f, 0.0f, -1.0f, 0x00, -8.0f }, { 0x060038E4, 1.0f, 0.0f, -1.0f, 0x02, -8.0f },
    { 0x06002D80, 1.0f, 0.0f, -1.0f, 0x02, -8.0f }, { 0x0600161C, 1.0f, 0.0f, -1.0f, 0x00, -8.0f },
    { 0x06001A00, 1.0f, 0.0f, -1.0f, 0x00, -8.0f }, { 0x060021D0, 1.0f, 0.0f, -1.0f, 0x00, -8.0f },
    { 0x06004930, 0.0f, 0.0f, -1.0f, 0x01, -8.0f }, { 0x06000750, 1.0f, 0.0f, -1.0f, 0x00, -8.0f },
    { 0x06000D5C, 1.0f, 0.0f, -1.0f, 0x00, -8.0f },
};

void func_80A42D30(EnGo2* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, u8 arg4, f32 arg5, f32 arg6) {
    s16 i;
    EnGoStruct3* ptr = this->unk_270;

    for (i = 0; i < 10; i++, ptr++) {
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

void func_80A42DD4(EnGo2* this) {
    EnGoStruct3* ptr = this->unk_270;
    s16 i;

    for (i = 0; i < 10; i++, ptr++) {
        if (ptr->unk_00 != 0) {
            ptr->unk_01--;
            if (ptr->unk_01 == 0) {
                ptr->unk_00 = 0;
            }

            ptr->unk_2C.x = (Math_Rand_ZeroOne() * 0.4f) - 0.2f;
            ptr->unk_2C.z = (Math_Rand_ZeroOne() * 0.4f) - 0.2f;

            ptr->unk_14.x += ptr->unk_20.x;
            ptr->unk_14.y += ptr->unk_20.y;
            ptr->unk_14.z += ptr->unk_20.z;

            ptr->unk_20.x += ptr->unk_2C.x;
            ptr->unk_20.y += ptr->unk_2C.y;
            ptr->unk_20.z += ptr->unk_2C.z;
            ptr->unk_04 = ptr->unk_04 + ptr->unk_08;
        }
    }
}

void func_80A42EE0(EnGo2* this, GlobalContext* globalCtx) {
    EnGoStruct3* ptr = this->unk_270;
    s16 i;
    u8 flag;
    s16 idx;
    s16 idx2;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go2_eff.c", 111);
    flag = 0;
    func_80093D84(globalCtx->state.gfxCtx);
    if (1) {};

    for (i = 0; i < 10; i++, ptr++) {
        if (ptr->unk_00 != 0) {
            if (!flag) {
                gfxCtx->polyXlu.p = Gfx_CallSetupDL(gfxCtx->polyXlu.p, 0);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_0600FD40);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 100, 60, 20, 0);
                flag = true;
            }

            idx2 = ptr->unk_01 * (255.0f / ptr->unk_02);
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 170, 130, 90, idx2);
            gDPPipeSync(gfxCtx->polyXlu.p++);

            Matrix_Translate(ptr->unk_14.x, ptr->unk_14.y, ptr->unk_14.z, MTXMODE_NEW);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_Scale(ptr->unk_04, ptr->unk_04, 1.0f, MTXMODE_APPLY);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_go2_eff.c", 137),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            idx = ptr->unk_01 * (8.0f / ptr->unk_02);
            gSPSegment(gfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A480D0[idx]));
            gSPDisplayList(gfxCtx->polyXlu.p++, D_0600FD50);
        }
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go2_eff.c", 151);
}

s32 func_80A4320C(EnGo2* this, u8 arg0, f32 arg1, f32 arg2, s32 arg3, f32 arg4, f32 arg5) {
    Vec3f sp94 = D_80A480F0;
    Vec3f sp88 = D_80A480FC;
    Vec3f sp7C = D_80A48108;
    s32 i;
    s16 rand;

    sp94 = this->actor.posRot.pos;
    sp94.y = this->actor.groundY;
    rand = (Math_Rand_ZeroOne() - 0.5f) * 65536.0f;
    for (i = arg3; i >= 0; i--, rand += (s16)(0x10000 / arg3)) {
        sp7C.y += (Math_Rand_ZeroOne() * arg5);
        sp94.x = (Math_Sins(rand) * arg4) + this->actor.posRot.pos.x;
        sp94.z = (Math_Coss(rand) * arg4) + this->actor.posRot.pos.z;
        func_80A42D30(this, &sp94, &sp88, &sp7C, arg0, arg1, arg2);
    }

    return 0;
}

void func_80A43424(EnGo2* this, GlobalContext* globalCtx, s32 arg2) {
    this->unk_594 = arg2;
    func_8002F434(&this->actor, globalCtx, arg2, this->actor.xzDistFromLink + 1.0f,
                  fabsf(this->actor.yDistFromLink) + 1.0f);
}

s16 func_80A43468(EnGo2* this, GlobalContext* globalCtx) {
    s16 ret = func_8010BDBC(&globalCtx->msgCtx);

    if (((this->unk_20D == 0xA) || (this->unk_20D == 5) || (this->unk_20D == 2) || (this->unk_20D == 1)) &&
        (ret != this->unk_20D)) {
        this->unk_20C++;
    }

    this->unk_20D = ret;
    return ret;
}

s32 func_80A434E8(EnGo2* this) {
    switch ((this->actor.params & 0xFC00) >> 0xA) {
        case 3:
            return 0x3069;

        case 5:
            return 0x306A;

        case 4:
            return 0x306B;

        case 2:
            return 0x306C;

        case 10:
            return 0x306D;

        case 8:
            return 0x306E;

        case 11:
            return 0x306F;

        case 1:
            return 0x3070;

        default:
            return 0x3052;
    }
}

u16 func_80A43564(GlobalContext* globalCtx, EnGo2* this) {
    if (gSaveContext.infTable[17] & 0x4000) {
        return 0x3013;
    }

    if ((CUR_CAPACITY(UPG_BOMB_BAG) >= 20) && ((this->unk_210 >= 8) && (this->unk_210 < 12))) {
        return 0x3012;
    }

    return 0x3011;
}

s16 func_80A435E8(GlobalContext* globalCtx, EnGo2* this) {
    s32 tmp;

    switch (func_8010BDBC(&globalCtx->msgCtx)) {
        case 2:
            return 2;
        case 5:
            if (func_80106BC8(globalCtx) != 0) {
                if (this->actor.textId == 0x3012) {
                    this->actionFunc = func_80A470E8;
                    tmp = (CUR_CAPACITY(UPG_BOMB_BAG) == 30) ? 0x34 : 0x33;
                    func_80A43424(this, globalCtx, tmp);
                    func_80106CCC(globalCtx);
                    gSaveContext.infTable[17] |= 0x4000;
                    return 2;
                }
                return 2;
            }
            break;
    }

    return 1;
}

u16 func_80A436DC(GlobalContext* globalCtx, EnGo2* this) {
    return CHECK_QUEST_ITEM(QUEST_GORON_RUBY) ? 0x3027 : 0x300A;
}

s16 func_80A43714(GlobalContext* globalCtx, EnGo2* this) {
    switch (func_8010BDBC(&globalCtx->msgCtx)) {
        case 2:
            if ((this->actor.textId == 0x300B) && !(gSaveContext.infTable[14] & 0x800)) {
                gSaveContext.infTable[14] |= 0x800;
                return 2;
            }
            return 0;

        case 4:
            if (func_80106BC8(globalCtx) != 0) {
                if (this->actor.textId == 0x300A) {
                    if (globalCtx->msgCtx.choiceIndex == 0) {
                        this->actor.textId = (CUR_UPG_VALUE(UPG_STRENGTH) != 0) ? 0x300B : 0x300C;
                    } else {
                        this->actor.textId = 0x300D;
                    }

                    func_8010B720(globalCtx, this->actor.textId);
                }
                return 1;
            }
            break;
    }

    return 1;
}

u16 func_80A43824(GlobalContext* globalCtx, EnGo2* this) {
    if (CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
        return 0x3027;
    }

    return (gSaveContext.eventChkInf[2] & 8) ? 0x3026 : 0x3009;
}

s16 func_80A4387C(GlobalContext* globalCtx, EnGo2* this) {
    if (func_8010BDBC(&globalCtx->msgCtx) == 2) {
        return 0;
    }

    return 1;
}

u16 func_80A438B4(GlobalContext* globalCtx, EnGo2* this) {
    if ((CHECK_QUEST_ITEM(QUEST_MEDALLION_FIRE)) && (LINK_IS_ADULT)) {
        return 0x3043;
    }

    if (CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
        return 0x3027;
    }

    return (gSaveContext.eventChkInf[2] & 8) ? 0x3021 : (gSaveContext.infTable[14] & 1) ? 0x302A : 0x3008;
}

s16 func_80A43950(GlobalContext* globalCtx, EnGo2* this) {
    if (func_8010BDBC(&globalCtx->msgCtx) == 2) {
        if (this->actor.textId == 0x3008) {
            gSaveContext.infTable[14] |= 1;
        }

        return 0;
    }

    return 1;
}

u16 func_80A439AC(GlobalContext* globalCtx, EnGo2* this) {
    if ((CHECK_QUEST_ITEM(QUEST_MEDALLION_FIRE)) && (LINK_IS_ADULT)) {
        return 0x3043;
    }

    if (CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
        return 0x3027;
    }

    return (gSaveContext.infTable[15] & 1) ? 0x3015 : 0x3014;
}

s16 func_80A43A2C(GlobalContext* globalCtx, EnGo2* this) {
    if (func_8010BDBC(&globalCtx->msgCtx) == 2) {
        if (this->actor.textId == 0x3014) {
            gSaveContext.infTable[15] |= 1;
        }

        return 0;
    }

    return 1;
}

u16 func_80A43A88(GlobalContext* globalCtx, EnGo2* this) {
    if ((CHECK_QUEST_ITEM(QUEST_MEDALLION_FIRE)) && (LINK_IS_ADULT)) {
        return 0x3043;
    }

    if (CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
        return 0x3067;
    }

    return (gSaveContext.infTable[15] & 0x10) ? 0x3017 : 0x3016;
}

s16 func_80A43B08(GlobalContext* globalCtx, EnGo2* this) {
    if (func_8010BDBC(&globalCtx->msgCtx) == 2) {
        if (this->actor.textId == 0x3016) {
            gSaveContext.infTable[15] |= 0x10;
        }

        return 0;
    }

    return 1;
}

u16 func_80A43B64(GlobalContext* globalCtx, EnGo2* this) {
    if ((CHECK_QUEST_ITEM(QUEST_MEDALLION_FIRE)) && (LINK_IS_ADULT)) {
        return 0x3043;
    }

    if (CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
        return 0x3027;
    }

    return CUR_UPG_VALUE(UPG_STRENGTH)
               ? 0x302C
               : !Flags_GetSwitch(globalCtx, 0x1B) ? 0x3017 : (gSaveContext.infTable[15] & 0x100) ? 0x3019 : 0x3018;
}

s16 func_80A43C40(GlobalContext* globalCtx, EnGo2* this) {
    if (func_8010BDBC(&globalCtx->msgCtx) == 2) {
        if (this->actor.textId == 0x3018) {
            gSaveContext.infTable[15] |= 0x100;
        }

        return 0;
    }

    return 1;
}

u16 func_80A43C9C(GlobalContext* globalCtx, EnGo2* this) {
    if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FIRE)) {
        return (gSaveContext.infTable[16] & 0x8000) ? 0x3042 : 0x3041;
    }

    if (CHECK_OWNED_EQUIP(EQUIP_TUNIC, 1)) {
        return (gSaveContext.infTable[16] & 0x4000) ? 0x3038 : 0x3037;
    }

    if (gSaveContext.infTable[16] & 0x1000) {
        this->unk_20C = 0;
        this->unk_20D = 0;
        return (gSaveContext.infTable[16] & 0x400) ? 0x3033 : 0x3032;
    }

    return 0x3030;
}

s16 func_80A43D78(GlobalContext* globalCtx, EnGo2* this) {
    switch (func_80A43468(this, globalCtx)) {
        case 2:
            switch (this->actor.textId) {
                case 0x3036:
                    func_80A43424(this, globalCtx, 0x2C);
                    this->actionFunc = func_80A470E8;
                    return 2;

                case 0x3037:
                    gSaveContext.infTable[16] |= 0x4000;
            }

            return 0;

        case 4:
            if (func_80106BC8(globalCtx) != 0) {
                if (this->actor.textId == 0x3034) {
                    if (globalCtx->msgCtx.choiceIndex == 0) {
                        this->actor.textId = (gSaveContext.infTable[16] & 0x800) ? 0x3033 : 0x3035;
                        if (this->actor.textId == 0x3035) {
                            func_800F8D04(NA_SE_EN_GOLON_CRY);
                        }
                    } else {
                        this->actor.textId = (gSaveContext.infTable[16] & 0x800) ? 0x3036 : 0x3033;
                        if (this->actor.textId == 0x3036) {
                            func_800F8D04(NA_SE_EN_GOLON_CRY);
                        }
                    }

                    func_8010B720(globalCtx, this->actor.textId);
                    this->unk_20C = 0;
                }

                return 1;
            }
            break;

        case 5:
            if (func_80106BC8(globalCtx) != 0) {
                switch (this->actor.textId) {
                    case 0x3035:
                        gSaveContext.infTable[16] |= 0x800;

                    case 0x3032:
                    case 0x3033:
                        this->actor.textId = 0x3034;
                        func_8010B720(globalCtx, this->actor.textId);
                        return 1;

                    default:
                        return 2;
                }
            }
            break;
    }

    return 1;
}

u16 func_80A43F90(GlobalContext* globalCtx, EnGo2* this) {
    Player* player = PLAYER;

    if (gSaveContext.bgsFlag != 0) {
        player->exchangeItemId = 0xF;
        return 0x305E;
    }

    if (INV_CONTENT(ITEM_TRADE_ADULT) >= ITEM_CLAIM_CHECK) {
        player->exchangeItemId = 0xF;
        return 0x305E;
    }

    if (INV_CONTENT(ITEM_TRADE_ADULT) >= ITEM_PRESCRIPTION) {
        player->exchangeItemId = 0xE;
        return 0x3058;
    }

    player->exchangeItemId = 0xB;
    return 0x3053;
}

s16 func_80A44010(GlobalContext* globalCtx, EnGo2* this) {
    s32 pad;
    u8 sp23 = this->unk_20D;

    switch (func_80A43468(this, globalCtx)) {
        case 6:
            if (this->actor.textId == 0x305E) {
                if (!gSaveContext.bgsFlag) {
                    func_80A43424(this, globalCtx, 0x57);
                    this->actionFunc = func_80A470E8;
                    return 2;
                }
                return 0;
            }
            return 0;

        case 3:
            switch (this->actor.textId) {
                case 0x305E:
                    if (func_8002F368(globalCtx) != 0xF) {
                        break;
                    }

                case 0x3059:
                    if (sp23 == 0) {
                        func_800F4524(&D_801333D4, NA_SE_EN_GOLON_WAKE_UP, 0x3C);
                    }

                case 0x3054:
                    if (sp23 == 0) {
                        Audio_PlaySoundGeneral(NA_SE_SY_TRE_BOX_APPEAR, &D_801333D4, 4, &D_801333E0, &D_801333E0,
                                               &D_801333E8);
                    }

                default:
                    break;
            }

            return 1;

        case 4:
            if (func_80106BC8(globalCtx) != 0) {
                switch (this->actor.textId) {
                    case 0x3054:
                    case 0x3055:
                        if (globalCtx->msgCtx.choiceIndex == 0) {
                            func_80A43424(this, globalCtx, 0x23);
                            this->actionFunc = func_80A470E8;
                            return 2;
                        }

                        this->actor.textId = 0x3056;
                        func_8010B720(globalCtx, this->actor.textId);
                }

                return 1;
            }
            break;

        case 5:
            if (func_80106BC8(globalCtx) != 0) {
                if (this->actor.textId == 0x3059) {
                    globalCtx->msgCtx.msgMode = 0x37;
                    this->actionFunc = func_80A4725C;
                }
                return 2;
            }
            break;
    }

    return 1;
}

u16 func_80A44224(GlobalContext* globalCtx, EnGo2* this) {
    if (Flags_GetSwitch(globalCtx, (this->actor.params & 0xFC00) >> 0xA)) {
        return 0x3071;
    }

    return 0x3051;
}

s16 func_80A44258(GlobalContext* globalCtx, EnGo2* this) {
    switch (func_8010BDBC(&globalCtx->msgCtx)) {
        case 2:
            return 0;

        case 5:
            if (func_80106BC8(globalCtx) != 0) {
                if (this->actor.textId == 0x3071) {
                    this->actor.textId = func_80A434E8(this);
                    func_8010B720(globalCtx, this->actor.textId);
                }
                return 1;
            }
    }

    return 1;
}

u16 func_80A442F0(GlobalContext* globalCtx, EnGo2* this) {
    return (LINK_IS_CHILD) ? (gSaveContext.infTable[14] & 8) ? 0x3022 : 0x300E : 0x3043;
}

s16 func_80A4433C(GlobalContext* globalCtx, EnGo2* this) {
    if (func_8010BDBC(&globalCtx->msgCtx) == 2) {
        if (this->actor.textId == 0x300E) {
            gSaveContext.infTable[14] |= 8;
        }

        return 0;
    }

    return 1;
}

u16 func_80A44398(GlobalContext* globalCtx, EnGo2* this) {
    return 0x7122;
}

s16 func_80A443A8(GlobalContext* globalCtx, EnGo2* this) {
    if (func_8010BDBC(&globalCtx->msgCtx) == 2) {
        return 0;
    }

    return 1;
}

u16 func_80A443E0(GlobalContext* globalCtx, EnGo2* this) {
    if (LINK_IS_CHILD) {
        if (Flags_GetSwitch(globalCtx, 0x1C)) {
            return 0x302F;
        }

        return (gSaveContext.infTable[14] & 0x40) ? 0x3025 : 0x3024;
    }

    return 0x3043;
}

s16 func_80A4444C(GlobalContext* globalCtx, EnGo2* this) {
    if (func_8010BDBC(&globalCtx->msgCtx) == 2) {
        if (this->actor.textId == 0x3024) {
            gSaveContext.infTable[14] |= 0x40;
        }

        return 0;
    }

    return 1;
}

u16 func_80A444A8(GlobalContext* globalCtx, EnGo2* this) {
    if (LINK_IS_CHILD) {
        return CHECK_QUEST_ITEM(QUEST_GORON_RUBY) ? 0x3065 : 0x3064;
    }

    return 0x3043;
}

s16 func_80A444FC(GlobalContext* globalCtx, EnGo2* this) {
    if (func_8010BDBC(&globalCtx->msgCtx) == 2) {
        return 0;
    }

    return 1;
}

u16 func_80A44534(GlobalContext* globalCtx, EnGo2* this) {
    u16 reaction = Text_GetFaceReaction(globalCtx, 0x20);
    if (reaction != 0) {
        return reaction;
    }

    switch (this->actor.params & 0x1F) {
        case 0:
            return func_80A43564(globalCtx, this);
        case 1:
            return func_80A43C9C(globalCtx, this);
        case 2:
            return func_80A43F90(globalCtx, this);
        case 3:
            return func_80A44224(globalCtx, this);
        case 4:
            return func_80A436DC(globalCtx, this);
        case 5:
            return func_80A43824(globalCtx, this);
        case 6:
            return func_80A438B4(globalCtx, this);
        case 7:
            return func_80A439AC(globalCtx, this);
        case 8:
            return func_80A43A88(globalCtx, this);
        case 9:
            return func_80A43B64(globalCtx, this);
        case 10:
            return func_80A442F0(globalCtx, this);
        case 11:
            return func_80A443E0(globalCtx, this);
        case 12:
            return func_80A444A8(globalCtx, this);
        case 13:
            return func_80A44398(globalCtx, this);
    }
}

s16 func_80A44678(GlobalContext* globalCtx, EnGo2* this) {
    switch (this->actor.params & 0x1F) {
        case 0:
            return func_80A435E8(globalCtx, this);
        case 1:
            return func_80A43D78(globalCtx, this);
        case 2:
            return func_80A44010(globalCtx, this);
        case 3:
            return func_80A44258(globalCtx, this);
        case 4:
            return func_80A43714(globalCtx, this);
        case 5:
            return func_80A4387C(globalCtx, this);
        case 6:
            return func_80A43950(globalCtx, this);
        case 7:
            return func_80A43A2C(globalCtx, this);
        case 8:
            return func_80A43B08(globalCtx, this);
        case 9:
            return func_80A43C40(globalCtx, this);
        case 10:
            return func_80A4433C(globalCtx, this);
        case 11:
            return func_80A4444C(globalCtx, this);
        case 12:
            return func_80A444FC(globalCtx, this);
        case 13:
            return func_80A443A8(globalCtx, this);
    }
}

s32 func_80A44790(EnGo2* this, GlobalContext* globalCtx) {
    if (((this->actor.params & 0x1F) != 2) && ((this->actor.params & 0x1F) != 0)) {
        return func_800343CC(globalCtx, &this->actor, &this->unk_194.unk_00, this->unk_218, func_80A44534,
                             func_80A44678);
    }

    if (((this->actor.params & 0x1F) == 2) && !(this->collider.base.maskB & 1)) {
        return 0;
    }

    if (func_8002F194(&this->actor, globalCtx) != 0) {
        this->unk_194.unk_00 = 1;
        return 1;
    }

    if (this->unk_194.unk_00 != 0) {
        this->unk_194.unk_00 = func_80A44678(globalCtx, this);
        return 0;
    }

    if (func_8002F2CC(&this->actor, globalCtx, this->unk_218) != 0) {
        this->actor.textId = func_80A44534(globalCtx, this);
    }

    return 0;
}

void func_80A4488C(EnGo2* this) {
    u8 idx = this->actor.params & 0x1F;

    this->collider.dim.radius = D_80A4816C[idx][3];
    this->collider.dim.height = D_80A4816C[idx][4];
}

void func_80A448C4(EnGo2* this) {
    u8 idx = this->actor.params & 0x1F;

    this->actor.shape.unk_10 = D_80A481F8[idx].unk_00;
    Actor_SetScale(&this->actor, D_80A481F8[idx].unk_04);
    this->actor.unk_1F = D_80A481F8[idx].unk_08;
    this->unk_218 = D_80A481F8[idx].unk_0C;
    this->unk_218 += this->collider.dim.radius;
}

void func_80A44940(EnGo2* this, GlobalContext* globalCtx) {
    Vec3s sp28;
    f32 val;

    sp28.x = this->actor.posRot.pos.x;
    sp28.y = this->actor.posRot.pos.y;
    sp28.z = this->actor.posRot.pos.z;

    val = D_80A4816C[this->actor.params & 0x1F][2];
    sp28.x += (s16)(val * Math_Sins(this->actor.shape.rot.y));
    sp28.z += (s16)(val * Math_Coss(this->actor.shape.rot.y));

    sp28.y += D_80A4816C[this->actor.params & 0x1F][1];
    this->collider.dim.pos = sp28;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80A44A9C(EnGo2* this) {
    f32 oldFrame = this->skelAnime.initialFrame;

    this->skelAnime.initialFrame = this->skelAnime.animFrameCount;
    this->skelAnime.animFrameCount = oldFrame;
}

s32 func_80A44AB0(EnGo2* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    f32 sp28;

    if ((this->actor.params & 0x1F) == 2) {
        return 0;
    }

    if ((this->actionFunc != func_80A46E54) && (this->actionFunc != func_80A47024) &&
        (this->actionFunc != func_80A46DBC)) {
        return 0;
    }

    if (this->collider.base.acFlags & 2) {
        Audio_PlaySoundGeneral(NA_SE_SY_CORRECT_CHIME, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        this->actor.flags &= 0xFEFFFFFF;
        this->collider.base.acFlags &= ~2;
        func_80A45E48(this, globalCtx);
        return 1;
    }

    if (player->invincibilityTimer <= 0) {
        this->collider.base.maskA |= 8;
    } else {
        return 0;
    }

    if (this->collider.base.maskB & 1) {
        this->collider.base.maskB &= ~1;
        sp28 = (this->actionFunc == func_80A46DBC) ? 1.5f : this->actor.speedXZ * 1.5f;
        globalCtx->unk_11D58(globalCtx, -4);
        func_8002F71C(globalCtx, &this->actor, sp28, this->actor.yawTowardsLink, 6.0f);
        Audio_PlayActorSound2(&player->actor, NA_SE_PL_BODY_HIT);
        this->collider.base.maskA &= ~8;
    }

    return 0;
}

s32 func_80A44C68(EnGo2* this, GlobalContext* globalCtx) {
    Path* path = this->unk_208;
    u8 count;

    if (path == NULL) {
        return 0;
    }

    count = path->count - 1;
    if (this->unk_20E != 0) {
        this->unk_210--;
        if (this->unk_210 < 0) {
            this->unk_210 = count - 1;
        }
    } else {
        this->unk_210++;
        if (this->unk_210 >= count) {
            this->unk_210 = 0;
        }
    }

    return 1;
}

s32 func_80A44CE4(EnGo2* this, GlobalContext* globalCtx) {
    s16 yaw;
    f32 sp28 = Path_OrientAndGetDistSq(&this->actor, this->unk_208, this->unk_210, &yaw);

    Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, yaw, 6, 0xFA0, 1);
    if ((sp28 > 0.0f) && (sp28 < 900.0f)) {
        return func_80A44C68(this, globalCtx);
    }

    return 0;
}

s32 func_80A44D84(EnGo2* this) {
    s16 sp1E;

    Path_OrientAndGetDistSq(&this->actor, this->unk_208, this->unk_210, &sp1E);
    this->actor.posRot.rot.y = sp1E;
    return 1;
}

s32 func_80A44DC0(EnGo2* this) {
    f32 tmpf1;
    f32 tmpf2;
    s16 tmp;

    if ((this->actor.params & 0x1F) == 2) {
        tmpf1 = 800.0f;
    } else {
        tmpf1 = 200.0f;
    }

    if ((this->actor.params & 0x1F) == 2) {
        tmpf2 = 400.0f;
    } else {
        tmpf2 = 60.0f;
    }

    if ((this->actor.params & 0x1F) == 2) {
        if (!(this->collider.base.maskB & 1)) {
            this->actor.flags &= ~1;
            return 0;
        }

        this->actor.flags |= 1;
        return 1;
    }

    tmpf1 *= tmpf1;
    tmp = ABS((s16)((f32)this->actor.yawTowardsLink - this->actor.shape.rot.y));
    if ((this->actor.xyzDistFromLinkSq <= tmpf1) && (fabsf(this->actor.yDistFromLink) < tmpf2) && (tmp < 0x2AA8)) {
        return 1;
    }

    return 0;
}

s32 func_80A44EF0(EnGo2* this, s16 arg1, f32 arg2, s16 arg3) {
    if (!(this->actor.bgCheckFlags & 1) || (this->actor.velocity.y > 0.0f)) {
        return 0;
    }

    if (DECR(this->unk_590) != 0) {
        if (arg3 == 0) {
            return 1;
        }

        if ((this->unk_590 & 1) != 0) {
            this->actor.posRot.pos.y += 1.5f;
        } else {
            this->actor.posRot.pos.y -= 1.5f;
        }

        Audio_PlayActorSound2(&this->actor, NA_SE_EV_BIGBALL_ROLL - SFX_FLAG);
        return 1;
    }

    if (this->unk_59C >= 2) {
        Audio_PlayActorSound2(&this->actor,
                              ((this->actor.params & 0x1F) == 0) ? NA_SE_EN_GOLON_LAND_BIG : NA_SE_EN_DODO_M_GND);
    }

    this->unk_59C--;
    if (this->unk_59C <= 0) {
        if (this->unk_59C == 0) {
            this->unk_590 = Math_Rand_S16Offset(0x3C, 0x1E);
            this->unk_59C = 0;
            this->actor.velocity.y = 0.0f;
            return 1;
        }

        this->unk_59C = arg1;
    }

    this->actor.velocity.y = ((f32)this->unk_59C / arg1) * arg2;
    return 1;
}

void func_80A45088(EnGo2* this, GlobalContext* globalCtx, Player* player) {
    u16 textId;

    if ((this->actor.params & 0x1F) == 2) {
        if (gSaveContext.bgsFlag != 0) {
            if (func_8002F368(globalCtx) == 0xF) {
                this->actor.textId = 0x3003;
            } else {
                this->actor.textId = 0x305E;
            }

            player->actor.textId = this->actor.textId;
        } else if ((gSaveContext.bgsFlag == 0) && (INV_CONTENT(ITEM_TRADE_ADULT) == ITEM_CLAIM_CHECK)) {
            if (func_8002F368(globalCtx) == 0xF) {
                if (func_800775CC() >= 3) {
                    textId = 0x305E;
                } else {
                    textId = 0x305D;
                }

                this->actor.textId = textId;
            } else {
                if (func_800775CC() >= 3) {
                    textId = 0x3002;
                } else {
                    textId = 0x305D;
                }

                this->actor.textId = textId;
            }

            player->actor.textId = this->actor.textId;
        } else if ((INV_CONTENT(ITEM_TRADE_ADULT) >= ITEM_PRESCRIPTION) &&
                   (INV_CONTENT(ITEM_TRADE_ADULT) <= ITEM_CLAIM_CHECK)) {
            if (func_8002F368(globalCtx) == 0xE) {
                this->actor.textId = 0x3059;
            } else {
                this->actor.textId = 0x3058;
            }

            if (this->actor.textId == 0x3059) {
                gSaveContext.timer2State = 0;
            }

            player->actor.textId = this->actor.textId;
        } else if (INV_CONTENT(ITEM_TRADE_ADULT) < ITEM_PRESCRIPTION) {
            if (func_8002F368(globalCtx) == 0xB) {
                if (gSaveContext.infTable[11] & 0x10) {
                    textId = 0x3055;
                } else {
                    textId = 0x3054;
                }

                this->actor.textId = textId;
            } else {
                this->actor.textId = 0x3053;
            }

            player->actor.textId = this->actor.textId;
        } else {
            player->actor.textId = this->actor.textId = 0x3053;
        }
    }
}

void func_80A45288(EnGo2* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 linkAge;

    if (this->actionFunc != func_80A47578) {
        this->unk_194.unk_18 = player->actor.posRot.pos;
        linkAge = gSaveContext.linkAge;
        this->unk_194.unk_14 = D_80A482D8[this->actor.params & 0x1F][linkAge];
        func_80034A14(&this->actor, &this->unk_194, 4, this->unk_26E);
    }

    if ((this->actionFunc != func_80A47158) && (this->unk_20F == 1) && func_80A44790(this, globalCtx)) {
        func_80A45088(this, globalCtx, player);
    }
}

void func_80A45360(EnGo2* this, f32* arg1) {
    f32 tmpf1;

    if ((this->skelAnime.animCurrentSeg == &D_06004930) && (this->skelAnime.animCurrentFrame <= 32.0f)) {
        tmpf1 = 0.0f;
    } else {
        tmpf1 = 255.0f;
    }

    Math_SmoothScaleMaxF(arg1, tmpf1, 0.4f, 100.0f);
    this->actor.shape.unk_14 = *arg1;
}

void func_80A4546C(EnGo2* this) {
    f32 oldSpeed = this->actor.speedXZ;

    if (this->unk_194.unk_00 != 0) {
        this->actor.speedXZ = 0.0f;
    }

    if (this->actionFunc != func_80A46DBC) {
        Actor_MoveForward(&this->actor);
    }

    this->actor.speedXZ = oldSpeed;
}

void func_80A454CC(EnGo2* this) {
    switch (this->actor.params & 0x1F) {
        case 0:
        case 6:
        case 7:
        case 10:
        case 12:
            func_80034EC0(&this->skelAnime, D_80A48348, 9);
            return;

        case 2:
            if ((INV_CONTENT(ITEM_TRADE_ADULT) >= ITEM_SWORD_BROKEN) &&
                (INV_CONTENT(ITEM_TRADE_ADULT) < ITEM_CLAIM_CHECK)) {
                func_80034EC0(&this->skelAnime, D_80A48348, 4);
                return;
            }
    }

    this->skelAnime.animPlaybackSpeed = 0.0f;
}

f32 func_80A45578(EnGo2* this) {
    f32 tmpf1 = ((this->actor.params & 0x1F) == 2) ? 400.0f : 60.0f;
    s32 params = (this->actor.params & 0x1F);

    if ((params == 1) && (fabsf(this->actor.yDistFromLink) < tmpf1) && (this->actor.xzDistFromLink < 400.0f)) {
        return 9.0f;
    }

    return (params == 0) ? 3.6000001f : 6.0f;
}

s32 func_80A4561C(EnGo2* this, GlobalContext* globalCtx) {
    Camera* camera = globalCtx->cameraPtrs[0];
    s32 params;

    if ((this->actor.params & 0x1F) == 2) {
        if (func_80A44DC0(this)) {
            func_8005A77C(camera, 0x3F);
            func_8005AD1C(camera, 4);
        } else if (!func_80A44DC0(this) && (camera->setting == 0x3F)) {
            func_8005A77C(camera, 4);
            func_8005ACFC(camera, 4);
        }
    }

    params = (this->actor.params & 0x1F);
    if ((params == 3) || (params == 0) || (params == 10) || (params == 2) || (params == 13)) {
        return 1;
    }

    if (!CHECK_QUEST_ITEM(QUEST_MEDALLION_FIRE) && CHECK_OWNED_EQUIP(EQUIP_TUNIC, 1)) {
        return 1;
    }

    return 0;
}

void func_80A45734(EnGo2* this) {
    if (func_80A44DC0(this)) {
        this->unk_26E = 2;
    } else {
        this->unk_26E = 1;
    }

    if (this->unk_194.unk_00 != 0) {
        this->unk_26E = 4;
    }

    this->unk_20F = 1;
}

void func_80A4578C(EnGo2* this) {
    f32 tmpf1 = ((this->actor.params & 0x1F) == 2) ? 800.0f : 200.0f;

    tmpf1 = SQ(tmpf1);
    this->unk_26E = 1;
    if ((this->actor.xyzDistFromLinkSq <= tmpf1) || (this->unk_194.unk_00 != 0)) {
        this->unk_26E = 4;
    }

    this->unk_20F = 1;
}

void func_80A457F8(EnGo2* this) {
    if (func_80A44DC0(this) || (this->unk_194.unk_00 != 0)) {
        this->unk_26E = 2;
        this->unk_20F = 1;
    } else {
        this->unk_26E = 1;
        this->unk_20F = 0;
    }
}

void func_80A45848(EnGo2* this) {
    switch (this->actor.params & 0x1F) {
        case 4:
            this->unk_20F = 1;
            if (func_80A44DC0(this)) {
                this->unk_26E = 2;
            } else {
                this->unk_26E = 1;
            }
            break;

        case 3:
            func_80A4578C(this);
            break;

        case 2:
            func_80A457F8(this);
            break;

        case 1:
            if (!CHECK_QUEST_ITEM(QUEST_MEDALLION_FIRE) && CHECK_OWNED_EQUIP(EQUIP_TUNIC, 1)) {
                func_80A4578C(this);
                break;
            }

        default:
            func_80A45734(this);
            break;
    }
}

void func_80A4592C(EnGo2* this) {
    switch (this->unk_213) {
        case 1:
            this->unk_224 = 0;
            this->unk_214 = 0;
            this->unk_215 = 0;
            break;
        case 2:
            this->unk_224 = 0;
            this->unk_214 = 1;
            this->unk_215 = 0;
            break;
        case 3:
            this->unk_224 = 0;
            this->unk_214 = 0;
            this->unk_215 = 1;
            break;

        default:
            if (DECR(this->unk_224) == 0) {
                this->unk_214++;
                if (this->unk_214 >= 4) {
                    this->unk_224 = Math_Rand_S16Offset(30, 30);
                    this->unk_214 = 1;
                }
            }
            break;
    }
}

void func_80A45A00(EnGo2* this) {
    if ((this->skelAnime.animPlaybackSpeed != 0.0f) && (this->skelAnime.animCurrentSeg == &D_06004930)) {
        if ((this->skelAnime.animPlaybackSpeed > 0.0f) && (this->skelAnime.animCurrentFrame == 14.0f)) {
            if ((this->actor.params & 0x1F) != 2) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOLON_SIT_DOWN);
            } else {
                func_800F4524(&D_801333D4, NA_SE_EN_GOLON_SIT_DOWN, 0x3C);
            }
        }

        if (this->skelAnime.animPlaybackSpeed < 0.0f) {
            if (this->skelAnime.animCurrentFrame == 1.0f) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_DODO_M_GND);
            }

            if (this->skelAnime.animCurrentFrame == 40.0f) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOLON_SIT_DOWN);
            }
        }
    }
}

void func_80A45B14(EnGo2* this, s32 arg1) {
    static EnGo2Struct2 D_80A48480[][4] = {
        {
            { 0x0C, 0.20000000298023224f, 0.20000000298023224f, 0x00000001, 18.0f, 0.0f },
            { 0x0C, 0.10000000149011612f, 0.20000000298023224f, 0x0000000C, 26.0f, 0.0f },
            { 0x0C, 0.10000000149011612f, 0.30000001192092896f, 0x00000004, 10.0f, 0.0f },
            { 0x0C, 0.20000000298023224f, 0.20000000298023224f, 0x00000001, 18.0f, 0.0f },
        },
        {
            { 0x0C, 0.5f, 0.4000000059604645f, 0x00000003, 42.0f, 0.0f },
            { 0x0C, 0.5f, 0.4000000059604645f, 0x00000003, 42.0f, 0.0f },
            { 0x0C, 0.5f, 0.4000000059604645f, 0x00000003, 42.0f, 0.0f },
            { 0x0C, 0.5f, 0.4000000059604645f, 0x00000003, 42.0f, 0.0f },
        },
    };

    // ??? not used?
    static s32 padding[3] = { 0x00000000, 0x00000000, 0x00000000 };

    u8 idx = ((this->actor.params & 0x1F) == 0) ? 1 : 0;

    func_80A4320C(this, D_80A48480[idx][arg1].unk_00, D_80A48480[idx][arg1].unk_04, D_80A48480[idx][arg1].unk_08,
                  D_80A48480[idx][arg1].unk_0C, D_80A48480[idx][arg1].unk_10, D_80A48480[idx][arg1].unk_14);
}

void func_80A45B9C(EnGo2* this, GlobalContext* globalCtx) {
    if ((this->actor.params & 0x1F) == 2) {
        this->actor.flags &= ~1;
        func_80034EC0(&this->skelAnime, D_80A48348, 10);
        this->skelAnime.animPlaybackSpeed = -0.5f;
    } else {
        func_80034EC0(&this->skelAnime, D_80A48348, 1);
        this->skelAnime.animPlaybackSpeed = -1.0f;
    }

    func_80A44A9C(this);
    this->unk_26E = 1;
    this->unk_211 = 0;
    this->unk_20F = 0;
    this->actionFunc = func_80A4696C;
}

void func_80A45C50(EnGo2* this, GlobalContext* globalCtx) {
    if (this->skelAnime.animPlaybackSpeed == 0.0f) {
        if ((this->actor.params & 0x1F) != 2) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOLON_WAKE_UP);
        } else {
            func_800F4524(&D_801333D4, NA_SE_EN_GOLON_WAKE_UP, 0x3C);
        }
    }

    if ((this->actor.params & 0x1F) == 2) {
        func_800800F8(globalCtx, 0x1068, -0x63, &this->actor, 0);
        func_80034EC0(&this->skelAnime, D_80A48348, 10);
        this->skelAnime.animPlaybackSpeed = 0.5f;
    } else {
        func_80034EC0(&this->skelAnime, D_80A48348, 1);
        this->skelAnime.animPlaybackSpeed = 1.0f;
    }

    this->actionFunc = func_80A46B40;
}

void func_80A45D40(EnGo2* this, GlobalContext* globalCtx) {
    func_80034EC0(&this->skelAnime, D_80A48348, 1);
    this->unk_211 = 1;
    this->actionFunc = func_80A46B40;
    this->skelAnime.animPlaybackSpeed = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->skelAnime.animCurrentFrame = this->skelAnime.animFrameCount;
}

void func_80A45DA4(EnGo2* this, GlobalContext* globalCtx) {
    if (((this->actor.params & 0x1F) == 0) || ((this->actor.params & 0x1F) == 1)) {
        this->collider.body.bumperFlags = 1;
        if (gSaveContext.infTable[17] & 0x4000) {
            this->actor.speedXZ = 6.0f;
        } else {
            this->actor.speedXZ = 3.6000001f;
        }
    } else {
        this->actor.speedXZ = 6.0f;
    }

    this->actor.flags |= 0x1000000;
    this->unk_592 = 10;
    this->actor.shape.unk_08 = 1800.0f;
    this->actor.speedXZ += this->actor.speedXZ;
    this->actionFunc = func_80A46DBC;
}

void func_80A45E48(EnGo2* this, GlobalContext* globalCtx) {
    if (((this->actor.params & 0x1F) != 0) && ((this->actor.params & 0x1F) != 1)) {
        if ((this->actor.params & 0x1F) == 5) {
            EnBom* bomb = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.posRot.pos.x,
                                              this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0, 0, 0, 0);
            if (bomb != NULL) {
                bomb->timer = 0;
            }
        }
    } else {
        this->collider.body.bumperFlags = 0;
    }

    this->actor.shape.rot = this->actor.posRot.rot;
    this->unk_59C = 0;
    this->unk_590 = 0;
    this->actionFunc = func_80A46F88;
    this->actor.shape.unk_08 = 0.0f;
    this->actor.speedXZ = 0.0f;
}

s32 func_80A45F08(EnGo2* this, GlobalContext* globalCtx) {
    if ((this->actor.params & 0x1F) != 3) {
        return 0;
    } else {
        this->actor.posRot.pos.x += (globalCtx->state.frames & 1) ? 1.0f : -1.0f;
        if (Flags_GetSwitch(globalCtx, (this->actor.params & 0xFC00) >> 0xA)) {
            return 1;
        }
    }

    return 0;
}

s32 func_80A45F9C(EnGo2* this) {
    if (((this->actor.params & 0x1F) != 4) || (this->unk_194.unk_00 != 2)) {
        return 0;
    }

    func_80034EC0(&this->skelAnime, D_80A48348, 3);
    this->unk_194.unk_00 = 0;
    this->unk_20F = 0;
    this->unk_26E = 1;
    this->actionFunc = func_80A46CD8;
    return 1;
}

s32 func_80A4601C(EnGo2* this, GlobalContext* globalCtx) {
    if (((this->actor.params & 0x1F) != 0) || (this->unk_194.unk_00 != 2)) {
        return 0;
    }

    this->unk_194.unk_00 = 0;
    func_80A45B9C(this, globalCtx);
    this->actionFunc = func_80A46D5C;
    return 1;
}

s32 func_80A4607C(EnGo2* this) {
    if (((this->actor.params & 0x1F) != 3) || (this->unk_194.unk_00 == 0)) {
        return 0;
    } else {
        this->actionFunc = func_80A47578;
        return 1;
    }
}

s32 func_80A460B8(EnGo2* this) {
    if (((this->actor.params & 0x1F) != 1) || (this->unk_210 >= this->unk_216) || !func_80A44DC0(this)) {
        return 0;
    }

    return 1;
}

s32 func_80A46114(EnGo2* this) {
    if ((this->unk_194.unk_00 == 0) || (this->actor.speedXZ < 1.0f)) {
        return 0;
    }

    if (func_80A44EF0(this, 2, 6.6666665f, 0)) {
        if ((this->unk_590 >= 9) && (this->unk_59C == 0)) {
            this->unk_590 = 8;
        }

        func_80A45B14(this, 0);
    }

    return 1;
}

void func_80A461A8(EnGo2* this, GlobalContext* globalCtx) {
    s32 tmp = 13;

    if ((this->actor.params & 0x1F) == 1) {
        if (((this->actor.textId == 0x3035) && (this->unk_20C == 0)) ||
            ((this->actor.textId == 0x3036) && (this->unk_20C == 0))) {
            if (this->skelAnime.animCurrentSeg != &D_06000D5C) {
                tmp = 12;
                this->unk_213 = 0;
            }
        }

        if (((this->actor.textId == 0x3032) && (this->unk_20C == 12)) || (this->actor.textId == 0x3033) ||
            ((this->actor.textId == 0x3035) && (this->unk_20C == 6))) {
            if (this->skelAnime.animCurrentSeg != &D_06000750) {
                tmp = 11;
                this->unk_213 = 1;
            }
        }

        if ((this->skelAnime.animCurrentSeg == &D_06000750) && (this->skelAnime.animCurrentFrame == 20.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOLON_CRY);
        }

        if (tmp != 13) {
            func_80034EC0(&this->skelAnime, D_80A48348, tmp);
        }
    }
}

void func_80A462D8(EnGo2* this, GlobalContext* globalCtx) {
    s16 tmp;

    this->unk_59A = Gameplay_CreateSubCamera(globalCtx);
    Gameplay_ChangeCameraStatus(globalCtx, 0, 1);
    Gameplay_ChangeCameraStatus(globalCtx, this->unk_59A, 7);
    Path_CopyLastPoint(this->unk_208, &this->unk_4AC);
    tmp = Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->unk_4AC) + 0xE38;
    this->unk_4A0.x = (Math_Sins(tmp) * 100.0f) + this->actor.posRot.pos.x;
    this->unk_4A0.z = (Math_Coss(tmp) * 100.0f) + this->actor.posRot.pos.z;
    this->unk_4A0.y = this->actor.posRot.pos.y + 20.0f;
    this->unk_4AC.x = this->actor.posRot.pos.x;
    this->unk_4AC.y = this->actor.posRot.pos.y + 40.0f;
    this->unk_4AC.z = this->actor.posRot.pos.z;
    func_800C04D8(globalCtx, this->unk_59A, &this->unk_4AC, &this->unk_4A0);
}

void func_80A463D8(EnGo2* this, GlobalContext* globalCtx) {
    Gameplay_ChangeCameraStatus(globalCtx, 0, 7);
    Gameplay_ClearCamera(globalCtx, this->unk_59A);
}

void func_80A46418(EnGo2* this) {
    if ((INV_CONTENT(ITEM_TRADE_ADULT) >= ITEM_SWORD_BROKEN) && (INV_CONTENT(ITEM_TRADE_ADULT) < ITEM_CLAIM_CHECK) &&
        ((this->actor.params & 0x1F) == 2) && (this->unk_194.unk_00 == 0) && (DECR(this->unk_592) == 0)) {
        this->unk_592 = Math_Rand_S16Offset(0x1E, 0x1E);
        func_800F4524(&D_801333D4, NA_SE_EN_GOLON_EYE_BIG, 0x3C);
    }
}

void EnGo2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGo2* this = THIS;
    s32 pad;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 28.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600FEF0, NULL, this->limbDrawTable, this->transitionDrawTable,
                     18);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    func_80061EFC(&this->actor.colChkInfo, NULL, &D_80A48140);
    switch (this->actor.params & 0x1F) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            this->actor.flags &= ~0x10;
            this->actor.flags &= ~0x20;
            break;
    }

    func_80A4488C(this);
    func_80A448C4(this);
    func_80034EC0(&this->skelAnime, D_80A48348, 0);
    this->actor.gravity = -1.0f;
    this->unk_220 = this->actor.shape.unk_14 = 0;
    this->unk_216 = this->actor.shape.rot.z;
    this->unk_20E = 0;
    this->unk_20F = 0;
    this->unk_211 = 0;
    this->unk_212 = 0;
    this->unk_210 = 0;
    this->unk_26E = 1;
    this->unk_208 = Path_GetByIndex(globalCtx, (this->actor.params & 0x3E0) >> 5, 0x1F);

    switch (this->actor.params & 0x1F) {
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            if ((!CHECK_QUEST_ITEM(QUEST_MEDALLION_FIRE)) && (LINK_IS_ADULT)) {
                Actor_Kill(&this->actor);
            }

            this->actionFunc = func_80A4696C;
            break;

        case 13:
            if ((LINK_IS_ADULT) || !CHECK_QUEST_ITEM(QUEST_GORON_RUBY)) {
                Actor_Kill(&this->actor);
            }

            func_80A45D40(this, globalCtx);
            break;

        case 1:
            if (gSaveContext.infTable[16] & 0x200) {
                Path_CopyLastPoint(this->unk_208, &this->actor.posRot.pos);
                this->actor.initPosRot.pos = this->actor.posRot.pos;
                if (!CHECK_QUEST_ITEM(QUEST_MEDALLION_FIRE) && CHECK_OWNED_EQUIP(EQUIP_TUNIC, 1)) {
                    func_80A45D40(this, globalCtx);
                } else {
                    this->actionFunc = func_80A4696C;
                }
            } else {
                gSaveContext.infTable[16] &= 0xEFFF;
                this->collider.dim.height = D_80A4816C[(this->actor.params & 0x1F)][4] * 0.6f;
                func_80A45DA4(this, globalCtx);
                this->unk_20F = 1;
            }
            break;

        case 0:
        case 5:
            this->collider.dim.height = D_80A4816C[(this->actor.params & 0x1F)][4] * 0.6f;
            func_80A45DA4(this, globalCtx);
            break;

        case 3:
            if (Flags_GetSwitch(globalCtx, (this->actor.params & 0xFC00) >> 0xA)) {
                Actor_Kill(&this->actor);
            } else {
                this->unk_20F = 1;
                this->actionFunc = func_80A4696C;
            }
            break;

        case 2:
            this->actor.shape.shadowDrawFunc = NULL;
            this->actor.flags &= ~1;
            if ((INV_CONTENT(ITEM_TRADE_ADULT) > ITEM_SAW) && (INV_CONTENT(ITEM_TRADE_ADULT) < ITEM_CLAIM_CHECK)) {
                this->unk_213 = 1;
            }

            this->collider.base.acFlags = 0;
            this->collider.base.maskA = 0xD;
            this->actionFunc = func_80A4696C;
            break;

        case 4:
            if (gSaveContext.infTable[14] & 0x800) {
                Path_CopyLastPoint(this->unk_208, &this->actor.posRot.pos);
                this->actor.initPosRot.pos = this->actor.posRot.pos;
            }

        default:
            this->actionFunc = func_80A4696C;
            break;
    }
}

void EnGo2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80A4696C(EnGo2* this, GlobalContext* globalCtx) {
    u8 sp37 = this->actor.params & 0x1F;

    if (func_800A56C8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
        if ((this->actor.params & 0x1F) == 2) {
            s32 quake = Quake_Add(globalCtx->cameraPtrs[globalCtx->activeCamera], 3);
            Quake_SetSpeed(quake, -0x3CB0);
            Quake_SetQuakeValues(quake, 8, 0, 0, 0);
            Quake_SetCountdown(quake, 0x10);
        } else {
            func_80A45B14(this, 1);
        }

        this->skelAnime.animPlaybackSpeed = 0.0f;
    }

    if ((s32)this->skelAnime.animCurrentFrame == 0) {
        this->collider.dim.height = D_80A4816C[sp37][4] * 0.6f;
    } else {
        this->collider.dim.height =
            (D_80A4816C[sp37][4] * 0.6f) +
            ((D_80A4816C[sp37][4] * 0.4f) * (this->skelAnime.animCurrentFrame / this->skelAnime.initialFrame));
    }

    if (func_80A45F08(this, globalCtx)) {
        this->unk_20F = 0;
        func_80A45C50(this, globalCtx);
    }

    if ((this->actor.params & 0x1F) != 3) {
        if (func_80A44DC0(this)) {
            func_80A45C50(this, globalCtx);
        }
    }
}

void func_80A46B40(EnGo2* this, GlobalContext* globalCtx) {
    u8 idx = this->actor.params & 0x1F;

    if (this->unk_211 == 1) {
        func_80A46418(this);
        func_80A461A8(this, globalCtx);
        func_80A45848(this);
        if (!func_80A4601C(this, globalCtx) && !func_80A4607C(this)) {
            if (func_80A45F9C(this)) {
                return;
            }
        } else {
            return;
        }
    } else if (func_800A56C8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
        if ((this->actor.params & 0x1F) == 2) {
            this->actor.flags |= 1;
        }
        func_80A454CC(this);
        this->unk_211 = 1;
        this->collider.dim.height = D_80A4816C[idx][4];
    } else {
        this->collider.dim.height =
            (D_80A4816C[idx][4] * 0.6f) +
            ((D_80A4816C[idx][4] * 0.4f) * (this->skelAnime.animCurrentFrame / this->skelAnime.animFrameCount));
    }

    if (!func_80A4561C(this, globalCtx) && !func_80A44DC0(this)) {
        func_80A45B9C(this, globalCtx);
    }
}

void func_80A46CD8(EnGo2* this, GlobalContext* globalCtx) {
    f32 frame = this->skelAnime.animFrameCount;
    f32 tmp = this->skelAnime.animCurrentFrame * (32768.0f / frame);

    this->actor.speedXZ = Math_Sins(tmp);
    if (func_80A44CE4(this, globalCtx) && (this->unk_210 == 0)) {
        func_80A45D40(this, globalCtx);
    }
}

void func_80A46D5C(EnGo2* this, GlobalContext* globalCtx) {
    if (func_800A56C8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
        func_80A45B14(this, 1);
        this->skelAnime.animPlaybackSpeed = 0.0f;
        func_80A45DA4(this, globalCtx);
    }
}

void func_80A46DBC(EnGo2* this, GlobalContext* globalCtx) {
    f32 val = 1000;
    if ((((this->actor.params & 0x1F) != 5) || !(this->actor.xyzDistFromLinkSq > SQ(val))) &&
        (DECR(this->unk_592) == 0)) {
        this->actor.speedXZ *= 0.5f;
        this->actionFunc = func_80A46E54;
    }

    func_80A45B14(this, 2);
}

void func_80A46E54(EnGo2* this, GlobalContext* globalCtx) {
    s32 ret;

    if (!func_80A46114(this)) {
        if (func_80A44EF0(this, 4, 8.0f, 1) == 1) {
            if (func_80A460B8(this)) {
                this->actionFunc = func_80A47024;
                return;
            } else {
                func_80A45B14(this, 3);
            }
        }

        ret = func_80A44CE4(this, globalCtx);
        switch (this->actor.params & 0x1F) {
            case 5:
                if ((ret == 1) && (this->unk_210 == 0)) {
                    func_80A45E48(this, globalCtx);
                    return;
                }
                break;

            case 1:
                if ((ret == 2) && (this->unk_210 == 1)) {
                    func_80A45E48(this, globalCtx);
                    return;
                }
                break;
        }

        Math_SmoothScaleMaxF(&this->actor.speedXZ, func_80A45578(this), 0.4f, 0.6f);
        this->actor.shape.rot = this->actor.posRot.rot;
    }
}

void func_80A46F88(EnGo2* this, GlobalContext* globalCtx) {
    if (func_80A44EF0(this, 4, 8.0f, 0)) {
        func_80A45B14(this, 0);
        if (this->unk_59C == 0) {
            switch (this->actor.params & 0x1F) {
                case 1:
                    this->unk_212 = 0;
                    this->actionFunc = func_80A47490;
                    break;
                case 0:
                    func_80A45C50(this, globalCtx);
                    break;
                default:
                    this->actionFunc = func_80A4696C;
            }
        }
    }
}

void func_80A47024(EnGo2* this, GlobalContext* globalCtx) {
    if (!func_80A46114(this)) {
        Math_SmoothScaleMaxF(&this->actor.speedXZ, 0.0f, 0.6f, 0.8f);
        if (this->actor.speedXZ >= 1.0f) {
            func_80A45B14(this, 3);
        }

        if ((s32)this->actor.speedXZ == 0) {
            this->actor.posRot.rot.y ^= 0x8000;
            this->actor.shape.rot.y = this->actor.posRot.rot.y;
            this->unk_20E ^= 1;
            func_80A44C68(this, globalCtx);
            func_80A45DA4(this, globalCtx);
        }
    }
}

void func_80A470E8(EnGo2* this, GlobalContext* globalCtx) {
    if (func_8002F410(&this->actor, globalCtx) != 0) {
        this->actor.attachedA = NULL;
        this->actionFunc = func_80A47158;
    } else {
        func_8002F434(&this->actor, globalCtx, this->unk_594, this->actor.xzDistFromLink + 1.0f,
                      fabsf(this->actor.yDistFromLink) + 1.0f);
    }
}

void func_80A47158(EnGo2* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 6) && (func_80106BC8(globalCtx) != 0)) {
        this->unk_194.unk_00 = 0;
        switch (this->unk_594) {
            case 38:
                func_800775D8();
                func_80A45D40(this, globalCtx);
                return;

            case 44:
                gSaveContext.infTable[16] |= 0x200;
                func_80A45D40(this, globalCtx);
                return;

            case 87:
                gSaveContext.bgsFlag = 1;
                break;

            case 51:
            case 52:
                func_80A45B9C(this, globalCtx);
                this->actionFunc = func_80A46D5C;
                return;
        }

        this->actionFunc = func_80A46B40;
    }
}

void func_80A4725C(EnGo2* this, GlobalContext* globalCtx) {
    switch (this->unk_212) {
        case 0:
            func_80034EC0(&this->skelAnime, D_80A48348, 5);
            this->actor.flags &= ~1;
            this->actor.shape.rot.y += 0x5B0;
            this->unk_26E = 1;
            this->unk_592 = (this->skelAnime.animFrameCount + 60.0f) + 60.0f;
            this->unk_213 = 2;
            this->unk_20C = 0;
            this->unk_212++;
            func_800F483C(0x28, 5);
            func_800800F8(globalCtx, 0x105E, -0x63, &this->actor, 0);
            break;

        case 1:
            if (DECR(this->unk_592) != 0) {
                if ((this->unk_592 == 0x3C) || (this->unk_592 == 0x78)) {
                    func_8005B1A4(ACTIVE_CAM);
                    func_800F4524(&D_801333D4, NA_SE_EV_GORON_WATER_DROP, 0x3C);
                }
            } else {

                func_800F4524(&D_801333D4, NA_SE_EN_GOLON_GOOD_BIG, 0x3C);
                func_80034EC0(&this->skelAnime, D_80A48348, 6);
                func_8010B720(globalCtx, 0x305A);
                this->unk_213 = 3;
                this->unk_212++;
                func_800F483C(0x7F, 5);
            }
            break;

        case 2:
            if (func_800A56C8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
                this->unk_213 = 0;
            }

            if (func_8010BDBC(&globalCtx->msgCtx) == 2) {
                func_80034EC0(&this->skelAnime, D_80A48348, 1);
                this->actor.flags |= 1;
                this->unk_26E = 2;
                this->skelAnime.animPlaybackSpeed = 0.0f;
                this->skelAnime.animCurrentFrame = this->skelAnime.animFrameCount;
                func_80A43424(this, globalCtx, 0x26);
                this->actionFunc = func_80A470E8;
                this->unk_212 = 0;
            }
            break;
    }
}

void func_80A47490(EnGo2* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    switch (this->unk_212) {
        case 0:
            if (func_8010BDBC(&globalCtx->msgCtx) != 0) {
                return;
            }

            func_8010B680(globalCtx, 0x3031, NULL);
            player->actor.freezeTimer = 10;
            this->unk_212++;

        case 1:
            if (func_8010BDBC(&globalCtx->msgCtx) != 2) {
                player->actor.freezeTimer = 10;
                return;
            }

            gSaveContext.infTable[16] |= 0x1000;
            this->unk_26E = 1;
            this->unk_211 = 0;
            this->unk_20F = 0;
            this->actionFunc = func_80A4696C;
            break;
    }
}

void func_80A47578(EnGo2* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3s sp2C = { 0, 0, 0 };
    s32 params;

    switch (this->unk_212) {
        case 0:
            if (func_8010BDBC(&globalCtx->msgCtx) == 2) {
                func_80A462D8(this, globalCtx);
                globalCtx->msgCtx.msgMode = 0x37;
                func_80034EC0(&this->skelAnime, D_80A48348, 2);
                this->unk_210 = 1;
                this->skelAnime.animPlaybackSpeed = 2.0f;
                func_80A44D84(this);
                this->actor.shape.rot = this->actor.posRot.rot;
                this->unk_592 = 0x3C;
                this->actor.gravity = 0.0f;
                this->actor.speedXZ = 2.0f;
                this->unk_194.unk_08 = sp2C;
                this->unk_194.unk_0E = sp2C;

                this->unk_212++;
                this->unk_212++;

                player->actor.posRot.rot.y = this->actor.posRot.rot.y;
                player->actor.shape.rot.y = this->actor.posRot.rot.y;

                player->actor.posRot.pos.x = this->actor.posRot.pos.x + Math_Sins(this->actor.posRot.rot.y) * -30.0f;
                player->actor.posRot.pos.z = this->actor.posRot.pos.z + Math_Coss(this->actor.posRot.rot.y) * -30.0f;

                func_8002DF54(globalCtx, &this->actor, 8);
                func_800F5C64(0x51);
            }
            break;

        case 2:
            if (DECR(this->unk_592) != 0) {
                if (!(this->unk_592 % 8)) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_MORIBLIN_WALK);
                }

                Actor_MoveForward(&this->actor);
                return;
            }

            this->unk_592 = 0;
            this->actor.speedXZ = 0.0f;

            params = (this->actor.params & 0xFC00) >> 0xA;
            if ((params != 1) && (params != 2) && (params != 4) && (params != 5) && (params != 9) && (params != 11)) {
                this->unk_212++;
            }

            this->unk_212++;
            break;

        case 3:
            this->unk_592++;

            if (!(this->unk_592 % 8) && (this->unk_592 < 10)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_MORIBLIN_WALK);
            }

            if (this->unk_592 == 10) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_IRON_DOOR_OPEN);
            }

            if (this->unk_592 < 45) {
                break;
            }

            Audio_PlaySoundAtPosition(globalCtx, &this->actor.posRot.pos, 0x14, NA_SE_EV_IRON_DOOR_CLOSE);

        case 4:
            func_80106CCC(globalCtx);
            func_80A463D8(this, globalCtx);
            func_8002DF54(globalCtx, &this->actor, 7);
            Actor_Kill(&this->actor);
            break;

        case 1:
            break;
    }
}

void EnGo2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGo2* this = THIS;

    func_80A45360(this, &this->unk_220);
    func_80A45A00(this);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80A4546C(this);
    func_8002E4B4(globalCtx, &this->actor, this->collider.dim.height * 0.5f, this->collider.dim.radius * 0.6f, 0.0f, 5);
    if (this->unk_194.unk_00 == 0) {
        func_80A44AB0(this, globalCtx);
    }

    this->actionFunc(this, globalCtx);
    if (this->unk_211 == 1) {
        func_80034F54(globalCtx, this->unk_226, this->unk_24A, 0x12);
    }

    func_80A45288(this, globalCtx);
    func_80A4592C(this);
    func_80A44940(this, globalCtx);
}

s32 func_80A479B0(EnGo2* this, GlobalContext* globalCtx) {
    Vec3f sp44 = { 0.0f, 0.0f, 0.0f };
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go2.c", 2881);
    func_80093D18(globalCtx->state.gfxCtx);
    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_go2.c", 2884),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, D_0600BD80);
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go2.c", 2889);
    Matrix_MultVec3f(&sp44, &this->actor.posRot2.pos);
    return 1;
}

s32 func_80A47AB0(EnGo2* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp48 = { 0.0f, 0.0f, 0.0f };
    f32 tmpf1;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go2.c", 2914);
    func_80093D18(globalCtx->state.gfxCtx);
    if (this->actionFunc == func_80A47024) {
        tmpf1 = 0.0f;
    } else {
        tmpf1 = this->actor.speedXZ;
    }

    Matrix_RotateRPY(globalCtx->state.frames * ((s16)tmpf1 * 1400), 0, this->actor.shape.rot.z, 1);
    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_go2.c", 2926),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, D_0600C140);
    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go2.c", 2930);
    Matrix_MultVec3f(&sp48, &this->actor.posRot2.pos);
    return 1;
}

s32 EnGo2_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGo2* this = THIS;
    Vec3s sp2C;

    if (limbIndex == 17) {
        Matrix_Translate(2800.0f, 0.0f, 0.0f, 1);
        sp2C = this->unk_194.unk_08;
        Matrix_RotateX((sp2C.y / 32768.0f) * M_PI, 1);
        Matrix_RotateZ((sp2C.x / 32768.0f) * M_PI, 1);
        Matrix_Translate(-2800.0f, 0.0f, 0.0f, 1);
    }

    if (limbIndex == 10) {
        sp2C = this->unk_194.unk_0E;
        Matrix_RotateY((sp2C.y / 32768.0f) * M_PI, 1);
        Matrix_RotateX((sp2C.x / 32768.0f) * M_PI, 1);
    }

    if (((limbIndex == 10) || (limbIndex == 11)) || (limbIndex == 14)) {
        rot->y += Math_Sins(this->unk_226[limbIndex]) * 200.0f;
        rot->z += Math_Coss(this->unk_24A[limbIndex]) * 200.0f;
    }

    return 0;
}

void EnGo2_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnGo2* this = THIS;
    Vec3f sp18 = { 600.0f, 0.0f, 0.0f };

    if (limbIndex == 17) {
        Matrix_MultVec3f(&sp18, &this->actor.posRot2.pos);
    }
}

void EnGo2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnGo2* this = THIS;
    UNK_TYPE sp5C[] = { 0x0600DA80, 0x0600CE80, 0x0600D280, 0x0600D680 };

    UNK_TYPE sp54[] = { 0x0600DE80, 0x0600E680 };

    // Required
    if (1) {};

    func_80A42DD4(this);
    Matrix_Push();
    func_80A42EE0(this, globalCtx);
    Matrix_Pull();
    if ((this->actionFunc == func_80A4696C) && (this->skelAnime.animPlaybackSpeed == 0.0f) &&
        (this->skelAnime.animCurrentFrame == 0.0f)) {
        func_80A479B0(this, globalCtx);
    } else if ((this->actionFunc == func_80A46E54) || (this->actionFunc == func_80A47024) ||
               (this->actionFunc == func_80A46DBC)) {
        func_80A47AB0(this, globalCtx);
    } else {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];
        s32 pad2;

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go2.c", 3063);
        func_80093D18(globalCtx->state.gfxCtx);
        gSPSegment(gfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(sp5C[this->unk_214]));
        gSPSegment(gfxCtx->polyOpa.p++, 0x09, SEGMENTED_TO_VIRTUAL(sp54[this->unk_215]));

        SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                         EnGo2_OverrideLimbDraw, EnGo2_PostLimbDraw, &this->actor);
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_go2.c", 3081);
    }
}
