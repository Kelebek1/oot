/*
 * File: z_en_ko.c
 * Overlay: ovl_En_Ko
 * Description: Kokiri Children
 */

#include "z_en_ko.h"

#define FLAGS 0x00000019

#define THIS ((EnKo*)thisx)

void EnKo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKo_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A99048(EnKo* this, GlobalContext* globalCtx);
void func_80A99384(EnKo* this, GlobalContext* globalCtx);
void func_80A99438(EnKo* this, GlobalContext* globalCtx);
void func_80A99504(EnKo* this, GlobalContext* globalCtx);
void func_80A995CC(EnKo* this, GlobalContext* globalCtx);
void func_80A99560(EnKo* this, GlobalContext* globalCtx);

s32 func_80A98ECC(EnKo* this, GlobalContext* globalCtx);

extern AnimationHeader D_06008F6C;
extern AnimationHeader D_0600879C;
extern AnimationHeader D_06006A60;
extern AnimationHeader D_06007830;
extern AnimationHeader D_06007D94;

const ActorInit En_Ko_InitVars = {
    ACTOR_EN_KO,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnKo),
    (ActorFunc)EnKo_Init,
    (ActorFunc)EnKo_Destroy,
    (ActorFunc)EnKo_Update,
    (ActorFunc)EnKo_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 20, 46, 0, { 0, 0, 0 } },
};

CollisionCheckInfoInit2 D_80A9A12C = { 0x00, 0x0000, 0x0000, 0x0000, 0xFF };

u32 D_80A9A138[] = { 0x06000240, 0x06000D40, 0x06001140, 0x00000000 };

u32 D_80A9A148[] = { 0x06000F4C, 0x06001A0C, 0x06001E0C, 0x00000000 };

typedef struct {
    s16 objIdx;
    Gfx* unk_04;
    u32* unk_08;
} EnKoStruct2;

EnKoStruct2 D_80A9A158[] = {
    { OBJECT_KM1, 0x06001890, NULL },
    { OBJECT_KW1, 0x06002C10, D_80A9A148 },
    { OBJECT_FA, 0x06002940, D_80A9A138 },
};

typedef struct {
    s16 objIdx;
    SkeletonHeader* skeleton;
} EnKoStruct3;

EnKoStruct3 D_80A9A17C[] = {
    { OBJECT_KM1, 0x060000F0 },
    { OBJECT_KW1, 0x060000F0 },
};

struct_80034EC0_Entry D_80A9A18C[] = {
    { 0x06008F6C, 1.0f, 2.0f, 14.0f, 0x04, 0.0f },   { 0x06008F6C, 0.0f, 1.0f, 1.0f, 0x04, 0.0f },
    { 0x06009B64, 0.0f, 0.0f, 0.0f, 0x02, 0.0f },    { 0x06009B64, 0.0f, 1.0f, 1.0f, 0x02, 0.0f },
    { 0x06009B64, 0.0f, 2.0f, 2.0f, 0x02, 0.0f },    { 0x060062DC, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },
    { 0x060062DC, 1.0f, 0.0f, -1.0f, 0x00, -10.0f }, { 0x06005808, 1.0f, 0.0f, -1.0f, 0x00, -10.0f },
    { 0x06007830, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },   { 0x06008178, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },
    { 0x060065E0, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },   { 0x0600879C, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },
    { 0x06007FFC, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },   { 0x060080B4, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },
    { 0x060091AC, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },   { 0x06006F9C, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },
    { 0x06007064, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },   { 0x06007120, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },
    { 0x06007F38, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },   { 0x06007D94, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },
    { 0x06006EE0, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },   { 0x060098EC, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },
    { 0x060090EC, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },   { 0x0600982C, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },
    { 0x06009274, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },   { 0x060099A4, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },
    { 0x06009028, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },   { 0x06007E64, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },
    { 0x06007454, 1.0f, 0.0f, -1.0f, 0x00, 0.0f },   { 0x06008F6C, 0.0f, 1.0f, 1.0f, 0x04, -8.0f },
    { 0x06007D94, 1.0f, 0.0f, -1.0f, 0x00, -8.0f },  { 0x0600879C, 1.0f, 0.0f, -1.0f, 0x00, -8.0f },
    { 0x06006A60, 1.0f, 0.0f, -1.0f, 0x00, -8.0f },  { 0x06007830, 1.0f, 0.0f, -1.0f, 0x00, -8.0f },
};

u8 D_80A9A4BC[][5] = {
    { 0x08, 0x09, 0x09, 0x0E, 0x0B }, { 0x02, 0x0C, 0x02, 0x0D, 0x0D }, { 0x0B, 0x0B, 0x0B, 0x0F, 0x09 },
    { 0x00, 0x10, 0x10, 0x11, 0x12 }, { 0x13, 0x13, 0x14, 0x0A, 0x09 }, { 0x03, 0x03, 0x03, 0x03, 0x03 },
    { 0x04, 0x16, 0x16, 0x04, 0x17 }, { 0x18, 0x10, 0x10, 0x19, 0x10 }, { 0x1A, 0x0F, 0x0F, 0x1A, 0x0F },
    { 0x03, 0x03, 0x03, 0x1B, 0x1B }, { 0x02, 0x02, 0x02, 0x02, 0x16 }, { 0x0E, 0x0E, 0x0E, 0x0E, 0x0E },
    { 0x05, 0x05, 0x05, 0x05, 0x05 },
};

typedef struct {
    u8 unk_00;
    u8 unk_01;
    Color_RGBA8_n unk_02;
    u8 unk_06;
    Color_RGBA8_n unk_07;
} EnKoStruct1;

EnKoStruct1 D_80A9A500[] = {
    { 0x00, 0x00, 0x00, 0x82, 0x46, 0xFF, 0x00, 0x6E, 0xAA, 0x14, 0xFF },
    { 0x01, 0x01, 0x46, 0xBE, 0x3C, 0xFF, 0x01, 0x64, 0x1E, 0x00, 0xFF },
    { 0x00, 0x00, 0x00, 0x82, 0x46, 0xFF, 0x00, 0x6E, 0xAA, 0x14, 0xFF },
    { 0x00, 0x00, 0x00, 0x82, 0x46, 0xFF, 0x00, 0x6E, 0xAA, 0x14, 0xFF },
    { 0x00, 0x00, 0x00, 0x82, 0x46, 0xFF, 0x00, 0x6E, 0xAA, 0x14, 0xFF },
    { 0x01, 0x01, 0x46, 0xBE, 0x3C, 0xFF, 0x01, 0x64, 0x1E, 0x00, 0xFF },
    { 0x01, 0x01, 0x46, 0xBE, 0x3C, 0xFF, 0x01, 0x64, 0x1E, 0x00, 0xFF },
    { 0x00, 0x00, 0x00, 0x82, 0x46, 0xFF, 0x00, 0x6E, 0xAA, 0x14, 0xFF },
    { 0x00, 0x00, 0x00, 0x82, 0x46, 0xFF, 0x00, 0x6E, 0xAA, 0x14, 0xFF },
    { 0x01, 0x01, 0x46, 0xBE, 0x3C, 0xFF, 0x01, 0x64, 0x1E, 0x00, 0xFF },
    { 0x01, 0x01, 0x46, 0xBE, 0x3C, 0xFF, 0x01, 0x64, 0x1E, 0x00, 0xFF },
    { 0x00, 0x00, 0x00, 0x82, 0x46, 0xFF, 0x00, 0x6E, 0xAA, 0x14, 0xFF },
    { 0x02, 0x01, 0x46, 0xBE, 0x3C, 0xFF, 0x01, 0x64, 0x1E, 0x00, 0xFF },
};

typedef struct {
    s8 unk_00;
    f32 unk_04;
    f32 unk_08;
} EnKoStruct4;

EnKoStruct4 D_80A9A590[] = {
    { 0x06, 30.0f, 180.0f }, { 0x06, 30.0f, 180.0f }, { 0x06, 30.0f, 180.0f }, { 0x06, 30.0f, 180.0f },
    { 0x06, 30.0f, 180.0f }, { 0x01, 30.0f, 240.0f }, { 0x06, 30.0f, 180.0f }, { 0x06, 30.0f, 180.0f },
    { 0x06, 30.0f, 180.0f }, { 0x06, 30.0f, 180.0f }, { 0x06, 30.0f, 180.0f }, { 0x06, 30.0f, 180.0f },
    { 0x06, 30.0f, 180.0f },
};

s32 func_80A96DB0(EnKo* this, GlobalContext* globalCtx) {
    u8 idx3 = D_80A9A500[this->actor.params & 0xFF].unk_00;
    u8 idx2 = D_80A9A500[this->actor.params & 0xFF].unk_01;
    u8 idx1 = D_80A9A500[this->actor.params & 0xFF].unk_06;

    this->unk_196 = Object_GetIndex(&globalCtx->objectCtx, D_80A9A17C[idx1].objIdx);
    if (this->unk_196 < 0) {
        return 0;
    }

    this->unk_195 = Object_GetIndex(&globalCtx->objectCtx, D_80A9A17C[idx2].objIdx);
    if (this->unk_195 < 0) {
        return 0;
    }

    this->unk_194 = Object_GetIndex(&globalCtx->objectCtx, D_80A9A158[idx3].objIdx);
    if (this->unk_194 < 0) {
        return 0;
    }

    return 1;
}

s32 func_80A96EC4(EnKo* this, GlobalContext* globalCtx) {
    if (!Object_IsLoaded(&globalCtx->objectCtx, this->unk_196)) {
        return 0;
    }
    if (!Object_IsLoaded(&globalCtx->objectCtx, this->unk_195)) {
        return 0;
    }
    if (!Object_IsLoaded(&globalCtx->objectCtx, this->unk_194)) {
        return 0;
    }
    return 1;
}

s32 func_80A96F48(EnKo* this, GlobalContext* globalCtx) {
    this->unk_197 = Object_GetIndex(&globalCtx->objectCtx, OBJECT_OS_ANIME);
    if (this->unk_197 < 0) {
        return 0;
    }
    return 1;
}

s32 func_80A96F94(EnKo* this, GlobalContext* globalCtx) {
    if (!Object_IsLoaded(&globalCtx->objectCtx, this->unk_197)) {
        return 0;
    }
    return 1;
}

u16 func_80A96FD0(GlobalContext* globalCtx, EnKo* this) {
    switch (this->actor.params & 0xFF) {
        case 12:
            if (gSaveContext.eventChkInf[4] & 1) {
                return 0x10DA;
            }
            if (CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
                return 0x10D9;
            }
            return (gSaveContext.infTable[11] & 0x80) ? 0x10D8 : 0x10D7;

        case 0:
            if (gSaveContext.eventChkInf[4] & 1) {
                return 0x1025;
            }
            if (CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
                return 0x1042;
            }
            return 0x1004;

        case 1:
            if (gSaveContext.eventChkInf[4] & 1) {
                return 0x1023;
            }
            if (CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
                return 0x1043;
            }
            if (gSaveContext.infTable[1] & 0x4000) {
                return 0x1006;
            }
            return 0x1005;

        case 2:
            if (gSaveContext.eventChkInf[4] & 1) {
                return 0x1022;
            }
            return 0x1007;

        case 3:
            if (gSaveContext.eventChkInf[4] & 1) {
                return 0x1021;
            }
            if (CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
                return 0x1044;
            }
            if (gSaveContext.infTable[2] & 4) {
                return 0x1009;
            }
            return 0x1008;

        case 4:
            if (gSaveContext.eventChkInf[4] & 1) {
                return 0x1097;
            }
            if (CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
                return 0x1042;
            }
            if (gSaveContext.infTable[2] & 0x10) {
                return 0x100B;
            }
            return 0x100A;

        case 5:
            if (gSaveContext.eventChkInf[4] & 1) {
                return 0x10B0;
            }
            if (CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
                return 0x1043;
            }
            if (gSaveContext.infTable[2] & 0x40) {
                return 0x100D;
            }
            return 0x100C;

        case 6:
            if (gSaveContext.eventChkInf[4] & 1) {
                return 0x10B5;
            }
            if (CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
                return 0x1043;
            }
            if (gSaveContext.infTable[2] & 0x100) {
                return 0x1019;
            }
            return 0x100E;

        case 7:
            return 0x1035;

        case 8:
            return 0x1038;

        case 9:
            if (CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
                return 0x104B;
            }
            return 0x103C;

        case 10:
            if (CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
                return 0x104C;
            }
            return 0x103D;

        case 11:
            return 0x103E;
    }
    return 0;
}

u16 func_80A97338(GlobalContext* globalCtx, EnKo* this) {
    Player* player = PLAYER;

    switch (this->actor.params & 0xFF) {
        case 12:
            player->exchangeItemId = 9;
            return 0x10B9;

        case 0:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                return 0x1072;
            }
            if (gSaveContext.infTable[4] & 2) {
                return 0x1056;
            }
            return 0x1055;

        case 1:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                return 0x1073;
            }
            return 0x105A;

        case 2:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                return 0x1074;
            }
            if (gSaveContext.infTable[4] & 0x80) {
                return 0x105E;
            }
            return 0x105D;

        case 3:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                return 0x1075;
            }
            return 0x105B;

        case 4:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                return 0x1076;
            }
            return 0x105F;

        case 5:
            return 0x1057;

        case 6:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                return 0x1077;
            }
            if (gSaveContext.infTable[5] & 2) {
                return 0x1059;
            }
            return 0x1058;

        case 7:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                return 0x1079;
            }
            return 0x104E;

        case 8:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                return 0x107A;
            }
            if (gSaveContext.infTable[5] & 0x200) {
                return 0x1050;
            }
            return 0x104F;

        case 9:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                return 0x107B;
            }
            return 0x1051;

        case 10:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                return 0x107C;
            }
            return 0x1052;

        case 11:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                return 0x107C;
            }
            if (gSaveContext.infTable[6] & 2) {
                return 0x1054;
            }
            return 0x1053;
    }
    return 0;
}

u16 func_80A97610(GlobalContext* globalCtx, EnKo* this) {
    u16 reaction;

    if (((this->actor.params & 0xFF) == 0) || ((this->actor.params & 0xFF) == 2) ||
        ((this->actor.params & 0xFF) == 3) || ((this->actor.params & 0xFF) == 4) ||
        ((this->actor.params & 0xFF) == 7) || ((this->actor.params & 0xFF) == 8) ||
        ((this->actor.params & 0xFF) == 11)) {
        reaction = Text_GetFaceReaction(globalCtx, 0x13);
    }

    if (((this->actor.params & 0xFF) == 1) || ((this->actor.params & 0xFF) == 5) ||
        ((this->actor.params & 0xFF) == 6) || ((this->actor.params & 0xFF) == 9) ||
        ((this->actor.params & 0xFF) == 10)) {
        reaction = Text_GetFaceReaction(globalCtx, 0x14);
    }

    if ((this->actor.params & 0xFF) == 12) {
        reaction = Text_GetFaceReaction(globalCtx, 0x12);
    }

    if (reaction != 0) {
        return reaction;
    }

    if (LINK_IS_ADULT) {
        return func_80A97338(globalCtx, this);
    }

    return func_80A96FD0(globalCtx, this);
}

s16 func_80A97738(GlobalContext* globalCtx, EnKo* this) {

    switch (func_8010BDBC(&globalCtx->msgCtx)) {
        case 2:
            switch (this->actor.textId) {
                case 0x1005:
                    gSaveContext.itemGetInf[5] |= 0x4000;
                    break;

                case 0x1008:
                    gSaveContext.infTable[2] |= 4;
                    break;

                case 0x100A:
                    gSaveContext.infTable[2] |= 0x10;
                    break;

                case 0x100C:
                    gSaveContext.infTable[2] |= 0x40;
                    break;

                case 0x100E:
                    gSaveContext.infTable[2] |= 0x100;
                    break;

                case 0x104F:
                    gSaveContext.infTable[5] |= 0x200;
                    break;

                case 0x1053:
                    gSaveContext.infTable[6] |= 2;
                    break;

                case 0x1055:
                    gSaveContext.infTable[4] |= 2;
                    break;

                case 0x1058:
                    gSaveContext.infTable[5] |= 2;
                    break;

                case 0x105D:
                    gSaveContext.infTable[4] |= 0x80;
                    break;

                case 0x10D7:
                    gSaveContext.infTable[11] |= 0x80;
                    break;

                case 0x10BA:
                    return 1;
            }
            return 0;
        case 3:
            switch (this->actor.textId) {
                case 0x10B7:
                case 0x10B8:
                    if (this->unk_210 == 0) {
                        Audio_PlaySoundGeneral(NA_SE_SY_TRE_BOX_APPEAR, &D_801333D4, 4, &D_801333E0, &D_801333E0,
                                               &D_801333E8);
                        this->unk_210 = 1;
                    }
                    break;
            }
            return 1;

        case 4:
            if (func_80106BC8(globalCtx) != 0) {
                switch (this->actor.textId) {
                    case 0x1035:
                        this->actor.textId = (globalCtx->msgCtx.choiceIndex == 0) ? 0x1036 : 0x1037;
                        func_8010B720(globalCtx, this->actor.textId);
                        break;

                    case 0x1038:
                        this->actor.textId = (globalCtx->msgCtx.choiceIndex != 0)
                                                 ? (globalCtx->msgCtx.choiceIndex == 1) ? 0x103A : 0x103B
                                                 : 0x1039;
                        func_8010B720(globalCtx, this->actor.textId);
                        break;

                    case 0x103E:
                        this->actor.textId = (globalCtx->msgCtx.choiceIndex == 0) ? 0x103F : 0x1040;
                        func_8010B720(globalCtx, this->actor.textId);
                        break;

                    case 0x10B7:
                        gSaveContext.infTable[11] |= 0x1000;
                    case 0x10B8:
                        this->actor.textId = (globalCtx->msgCtx.choiceIndex == 0) ? 0x10BA : 0x10B9;
                        return (globalCtx->msgCtx.choiceIndex == 0) ? 2 : 1;

                    default:
                        return 1;
                }
            }
            break;

        case 6:
            if (func_80106BC8(globalCtx) != 0) {
                return 3;
            }
            break;
    }

    return 1;
}

s32 func_80A97B38(EnKo* this) {
    if (LINK_IS_CHILD) {
        if (gSaveContext.eventChkInf[4] & 1) {
            return 2;
        }
        if (CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
            return 1;
        }
        return 0;
    } else {
        return CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST) ? 4 : 3;
    }
}

f32 func_80A97BC0(EnKo* this) {
    f32 sp1C[][5] = {
        { 0.0f, 0.0f, 0.0f, -30.0f, -20.0f },       { 0.0f, 0.0f, 0.0f, -20.0f, -10.0f },
        { 0.0f, 0.0f, 0.0f, -30.0f, -20.0f },       { -10.0f, 10.0f, 10.0f, -10.0f, -30.0f },
        { 0.0f, 0.0f, 0.0f, -10.0f, -20.0f },       { 0.0f, 0.0f, 0.0f, -20.0f, -20.0f },
        { 0.0f, 0.0f, 0.0f, -10.0f, -20.0f },       { 10.0f, 10.0f, 10.0f, -60.0f, -20.0f },
        { -10.0f, -10.0f, -20.0f, -30.0f, -30.0f }, { -10.0f, -10.0f, -10.0f, -40.0f, -40.0f },
        { 0.0f, 0.0f, 0.0f, -10.0f, -20.0f },       { -10.0f, -10.0f, -20.0f, -30.0f, -30.0f },
        { 0.0f, 0.0f, 0.0f, -20.0f, -20.0f },
    };

    if (LINK_IS_ADULT && ((this->actor.params & 0xFF) == 12)) {
        return -20.0f;
    }

    return sp1C[this->actor.params & 0xFF][func_80A97B38(this)];
}

s32 func_80A97C7C(EnKo* this) {
    u8 sp1C[][5] = {
        { 0x01, 0x01, 0x01, 0x00, 0x01 }, { 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x01, 0x01, 0x01, 0x00, 0x01 },
        { 0x01, 0x01, 0x01, 0x00, 0x01 }, { 0x01, 0x01, 0x01, 0x00, 0x01 }, { 0x00, 0x00, 0x00, 0x00, 0x00 },
        { 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x01, 0x01, 0x01, 0x00, 0x01 }, { 0x00, 0x00, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x00, 0x00, 0x00, 0x00, 0x00 },
        { 0x01, 0x01, 0x01, 0x01, 0x01 },
    };
    return sp1C[this->actor.params & 0xFF][func_80A97B38(this)];
}

s32 func_80A97D00(EnKo* this) {
    s16 abs = ABS((s16)((f32)this->actor.yawTowardsLink - this->actor.shape.rot.y));

    return (abs < 0x3FFC) ? 1 : 0;
}

s32 func_80A97D68(EnKo* this, GlobalContext* globalCtx) {
    s16 phi_a3;

    if (this->unk_1E8.unk_00 != 0) {
        if ((this->skelAnime.animCurrentSeg == &D_06006A60) == 0) {
            func_80034EC0(&this->skelAnime, D_80A9A18C, 0x20);
        }
        phi_a3 = 2;
    } else {
        if ((this->skelAnime.animCurrentSeg == &D_06007830) == 0) {
            func_80034EC0(&this->skelAnime, D_80A9A18C, 0x21);
        }
        phi_a3 = 1;
    }
    func_80034A14(&this->actor, &this->unk_1E8, 2, phi_a3);
    return func_80A97D00(this);
}

s32 func_80A97E18(EnKo* this, GlobalContext* globalCtx) {
    s16 phi_a3;

    func_80034F54(globalCtx, this->unk_2E4, this->unk_304, 0x10);
    if (func_80A97D00(this) == 1) {
        phi_a3 = 2;
    } else {
        phi_a3 = 1;
    }
    if (this->unk_1E8.unk_00 != 0) {
        phi_a3 = 4;
    } else if (this->unk_21C < this->actor.xzDistFromLink) {
        phi_a3 = 1;
    }
    func_80034A14(&this->actor, &this->unk_1E8, 2, phi_a3);
    return 1;
}

s32 func_80A97EB0(EnKo* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 sp20;
    s16 phi_a3;

    func_80034F54(globalCtx, this->unk_2E4, this->unk_304, 0x10);
    sp20 = func_80A97D00(this);
    if (sp20 == 1) {
        phi_a3 = 2;
    } else {
        phi_a3 = 1;
    }
    func_80034A14(&this->actor, &this->unk_1E8, 2, phi_a3);
    return sp20;
}

s32 func_80A97F20(EnKo* this, GlobalContext* globalCtx) {
    func_80034F54(globalCtx, this->unk_2E4, this->unk_304, 0x10);
    func_80034A14(&this->actor, &this->unk_1E8, 2, 4);
    return 1;
}

s32 func_80A97F70(EnKo* this, GlobalContext* globalCtx) {
    s16 phi_a3;

    if (this->unk_1E8.unk_00 != 0) {
        if ((this->skelAnime.animCurrentSeg == &D_06008F6C) == 0) {
            func_80034EC0(&this->skelAnime, D_80A9A18C, 0x1D);
        }
        func_80034F54(globalCtx, this->unk_2E4, this->unk_304, 0x10);
        phi_a3 = 2;
    } else {
        if ((this->skelAnime.animCurrentSeg == &D_06007D94) == 0) {
            func_80034EC0(&this->skelAnime, D_80A9A18C, 0x1E);
        }
        phi_a3 = 1;
    }
    func_80034A14(&this->actor, &this->unk_1E8, 5, phi_a3);
    return func_80A97D00(this);
}

s32 func_80A98034(EnKo* this, GlobalContext* globalCtx) {
    s16 phi_a3;
    s32 sp20;

    if (this->unk_1E8.unk_00 != 0) {
        if ((this->skelAnime.animCurrentSeg == &D_06008F6C) == 0) {
            func_80034EC0(&this->skelAnime, D_80A9A18C, 0x1D);
        }
        func_80034F54(globalCtx, this->unk_2E4, this->unk_304, 0x10);
        sp20 = func_80A97D00(this);
        if (sp20 == 1) {
            phi_a3 = 2;
        } else {
            phi_a3 = 1;
        }
    } else {
        if ((this->skelAnime.animCurrentSeg == &D_0600879C) == 0) {
            func_80034EC0(&this->skelAnime, D_80A9A18C, 0x1F);
        }
        phi_a3 = 1;
        sp20 = func_80A97D00(this);
    }

    func_80034A14(&this->actor, &this->unk_1E8, 5, phi_a3);
    return sp20;
}

s32 func_80A98124(EnKo* this, GlobalContext* globalCtx) {
    func_80034F54(globalCtx, this->unk_2E4, this->unk_304, 0x10);
    func_80034A14(&this->actor, &this->unk_1E8, 2, 4);
    return 1;
}

s32 func_80A98174(EnKo* this, GlobalContext* globalCtx) {
    if (this->unk_1E8.unk_00 != 0) {
        if (func_800A56C8(&this->skelAnime, 18.0f) != 0) {
            this->skelAnime.animPlaybackSpeed = 0.0f;
        }
    } else if (this->skelAnime.animPlaybackSpeed != 1.0f) {
        this->skelAnime.animPlaybackSpeed = 1.0f;
    }

    if (this->skelAnime.animPlaybackSpeed == 0.0f) {
        func_80034F54(globalCtx, this->unk_2E4, this->unk_304, 0x10);
    }

    func_80034A14(&this->actor, &this->unk_1E8, 2, (this->skelAnime.animPlaybackSpeed == 0.0f) ? 2 : 1);
    return func_80A97D00(this);
}

s32 func_80A98254(EnKo* this, GlobalContext* globalCtx) {
    switch (this->actor.params & 0xFF) {
        case 0:
            return func_80A97D68(this, globalCtx);
        case 1:
            return func_80A97E18(this, globalCtx);
        case 2:
            return func_80A98034(this, globalCtx);
        case 3:
            return func_80A97E18(this, globalCtx);
        case 4:
            return func_80A97F70(this, globalCtx);
        case 5:
            return func_80A97EB0(this, globalCtx);
        case 6:
            return func_80A97F20(this, globalCtx);
        case 7:
            return func_80A97EB0(this, globalCtx);
        case 8:
            return func_80A97EB0(this, globalCtx);
        case 9:
            return func_80A97EB0(this, globalCtx);
        case 10:
            return func_80A97E18(this, globalCtx);
        case 11:
            return func_80A97EB0(this, globalCtx);
        case 12:
            return func_80A97E18(this, globalCtx);
    }
}

s32 func_80A9835C(EnKo* this, GlobalContext* globalCtx) {
    switch (this->actor.params & 0xFF) {
        case 0:
            return func_80A98124(this, globalCtx);
        case 1:
            return func_80A98124(this, globalCtx);
        case 2:
            return func_80A98034(this, globalCtx);
        case 3:
            return func_80A97EB0(this, globalCtx);
        case 4:
            return func_80A97F70(this, globalCtx);
        case 5:
            return func_80A97EB0(this, globalCtx);
        case 6:
            return func_80A97F20(this, globalCtx);
        case 7:
            return func_80A97EB0(this, globalCtx);
        case 8:
            return func_80A97EB0(this, globalCtx);
        case 9:
            return func_80A97EB0(this, globalCtx);
        case 10:
            return func_80A97E18(this, globalCtx);
        case 11:
            return func_80A97EB0(this, globalCtx);
        case 12:
            return func_80A97E18(this, globalCtx);
    }
}

s32 func_80A98464(EnKo* this, GlobalContext* globalCtx) {
    switch (this->actor.params & 0xFF) {
        case 0:
            return func_80A98124(this, globalCtx);
        case 1:
            return func_80A98124(this, globalCtx);
        case 2:
            return func_80A98034(this, globalCtx);
        case 3:
            return func_80A97EB0(this, globalCtx);
        case 4:
            return func_80A98174(this, globalCtx);
        case 5:
            return func_80A97EB0(this, globalCtx);
        case 6:
            return func_80A97F20(this, globalCtx);
        case 7:
            return func_80A97EB0(this, globalCtx);
        case 8:
            return func_80A97EB0(this, globalCtx);
        case 9:
            return func_80A97EB0(this, globalCtx);
        case 10:
            return func_80A97E18(this, globalCtx);
        case 11:
            return func_80A97EB0(this, globalCtx);
        case 12:
            return func_80A97E18(this, globalCtx);
    }
}

s32 func_80A9856C(EnKo* this, GlobalContext* globalCtx) {
    switch (this->actor.params & 0xFF) {
        case 0:
            return func_80A97EB0(this, globalCtx);
        case 1:
            return func_80A98124(this, globalCtx);
        case 2:
            return func_80A97EB0(this, globalCtx);
        case 3:
            return func_80A97EB0(this, globalCtx);
        case 4:
            return func_80A97EB0(this, globalCtx);
        case 5:
            return func_80A97EB0(this, globalCtx);
        case 6:
            return func_80A97F20(this, globalCtx);
        case 7:
            return func_80A97EB0(this, globalCtx);
        case 8:
            return func_80A97EB0(this, globalCtx);
        case 9:
            return func_80A97EB0(this, globalCtx);
        case 10:
            return func_80A97E18(this, globalCtx);
        case 11:
            return func_80A97EB0(this, globalCtx);
        case 12:
            return func_80A97E18(this, globalCtx);
    }
}

s32 func_80A98674(EnKo* this, GlobalContext* globalCtx) {
    switch (this->actor.params & 0xFF) {
        case 0:
            return func_80A98034(this, globalCtx);
        case 1:
            return func_80A97E18(this, globalCtx);
        case 2:
            return func_80A97E18(this, globalCtx);
        case 3:
            return func_80A97EB0(this, globalCtx);
        case 4:
            return func_80A97E18(this, globalCtx);
        case 5:
            return func_80A97EB0(this, globalCtx);
        case 6:
            return func_80A97F20(this, globalCtx);
        case 7:
            return func_80A97EB0(this, globalCtx);
        case 8:
            return func_80A97EB0(this, globalCtx);
        case 9:
            return func_80A97EB0(this, globalCtx);
        case 10:
            return func_80A97E18(this, globalCtx);
        case 11:
            return func_80A97EB0(this, globalCtx);
        case 12:
            return func_80A97E18(this, globalCtx);
    }
}

void func_80A9877C(EnKo* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((globalCtx->csCtx.state != 0) || (D_8011D394 != 0)) {
        this->unk_1E8.unk_18 = globalCtx->view.eye;
        this->unk_1E8.unk_14 = 40.0f;
        if ((this->actor.params & 0xFF) != 0) {
            func_80034A14(&this->actor, &this->unk_1E8, 2, 2);
        }
    } else {
        this->unk_1E8.unk_18 = player->actor.posRot.pos;
        this->unk_1E8.unk_14 = func_80A97BC0(this);
        if (func_80A98ECC(this, globalCtx) == 0) {
            if (this->unk_1E8.unk_00 == 0) {
                return;
            }
        }
    }

    if ((func_800343CC(globalCtx, &this->actor, &this->unk_1E8.unk_00, this->unk_21C, func_80A97610, func_80A97738) !=
         0) &&
        ((this->actor.params & 0xFF) == 0xC) && (globalCtx->sceneNum == 0x5B)) {
        this->actor.textId = (INV_CONTENT(ITEM_TRADE_ADULT) >= ITEM_SAW) ? 0x10B9 : 0x10DF;
        if (func_8002F368(globalCtx) == 9) {
            this->actor.textId = (gSaveContext.infTable[11] & 0x1000) ? 0x10B8 : 0x10B7;
            this->unk_210 = 0;
        }
        player->actor.textId = this->actor.textId;
    }
}

s32 func_80A98934(EnKo* this, GlobalContext* globalCtx) {
    switch (globalCtx->sceneNum) {
        case 0x55:
            if (((this->actor.params & 0xFF) >= 7) && ((this->actor.params & 0xFF) != 0xC)) {
                return 0;
            }
            if (!CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST) && (LINK_IS_ADULT)) {
                return 0;
            }
            return 1;

        case 0x26:
            if (((this->actor.params & 0xFF) != 7) && ((this->actor.params & 0xFF) != 8) &&
                ((this->actor.params & 0xFF) != 11)) {
                return 0;
            }
            return 1;

        case 0x27:
            if ((LINK_IS_ADULT) && !CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                if (((this->actor.params & 0xFF) != 1) && ((this->actor.params & 0xFF) != 9)) {
                    return 0;
                }
                return 1;
            }
            if ((this->actor.params & 0xFF) != 9) {
                return 0;
            }
            return 1;

        case 0x28:
            if ((LINK_IS_ADULT) && !CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                if ((this->actor.params & 0xFF) != 0) {
                    if ((this->actor.params & 0xFF) != 4) {
                        return 0;
                    }
                }
                return 1;
            }
            return 0;

        case 0x29:
            if ((LINK_IS_ADULT) && !CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                if ((this->actor.params & 0xFF) != 6) {
                    return 0;
                }
                return 1;
            }
            return 0;

        case 0x2D:
            if ((LINK_IS_ADULT) && !CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                if ((this->actor.params & 0xFF) != 5) {
                    if ((this->actor.params & 0xFF) != 0xA) {
                        return 0;
                    }
                }
                return 1;
            }
            if ((this->actor.params & 0xFF) != 0xA) {
                return 0;
            }
            return 1;

        case 0x5B:
            return (INV_CONTENT(ITEM_TRADE_ADULT) == ITEM_ODD_POTION) ? 1 : 0;

        case 0x2A:
        case 0x2B:
        case 0x2C:
            break;
    }

    return 0;
}

void func_80A98C18(EnKo* this) {
    u8 idx;
    u32* ptr;

    if (DECR(this->unk_214) == 0) {
        idx = D_80A9A500[this->actor.params & 0xFF].unk_00;
        this->unk_216++;
        ptr = D_80A9A158[idx].unk_08;
        if (ptr != NULL) {
            if (ptr[this->unk_216] == 0) {
                this->unk_214 = Math_Rand_S16Offset(30, 30);
                this->unk_216 = 0;
            }
        }
    }
}

void func_80A98CD8(EnKo* this) {
    u8 idx = this->actor.params & 0xFF;

    this->actor.unk_1F = D_80A9A590[idx].unk_00;
    this->unk_21C = D_80A9A590[idx].unk_04;
    this->unk_21C += this->collider.dim.radius;
    this->unk_218 = D_80A9A590[idx].unk_08;
}

s32 func_80A98D2C(EnKo* this) {
    if (LINK_IS_ADULT) {
        return CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST) ? 4 : 3;
    }
    if (CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
        return (gSaveContext.eventChkInf[4] & 1) ? 2 : 1;
    }
    return 0;
}

void func_80A98DB4(EnKo* this, GlobalContext* globalCtx) {
    f32 phi_f2;

    if ((globalCtx->sceneNum != SCENE_SPOT10) && (globalCtx->sceneNum != SCENE_SPOT04)) {
        this->unk_220 = 255.0f;
        return;
    }

    if ((globalCtx->csCtx.state != 0) || (D_8011D394 != 0)) {
        phi_f2 = Math_Vec3f_DistXYZ(&this->actor.posRot.pos, &globalCtx->view.eye) * 0.25f;
    } else {
        phi_f2 = this->actor.xzDistFromLink;
    }

    Math_SmoothScaleMaxMinF(&this->unk_220, (this->unk_218 < phi_f2) ? 0.0f : 255.0f, 0.3f, 40.0f, 1.0f);
    if (this->unk_220 < 10.0f) {
        this->actor.flags &= ~1;
    } else {
        this->actor.flags |= 1;
    }
}

s32 func_80A98ECC(EnKo* this, GlobalContext* globalCtx) {
    if ((globalCtx->sceneNum == SCENE_SPOT10) && ((this->actor.params & 0xFF) == 12)) {
        func_80A97E18(this, globalCtx);
    } else {
        switch (func_80A97B38(this)) {
            case 0:
                return func_80A98254(this, globalCtx);
            case 1:
                return func_80A9835C(this, globalCtx);
            case 2:
                return func_80A98464(this, globalCtx);
            case 3:
                return func_80A9856C(this, globalCtx);
            case 4:
                return func_80A98674(this, globalCtx);
        }
    }
}

void EnKo_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnKo* this = THIS;

    if (((this->actor.params & 0xFF) >= 0xD) || (func_80A96F48(this, globalCtx) == 0) ||
        (func_80A96DB0(this, globalCtx) == 0)) {
        Actor_Kill(&this->actor);
    }
    if (func_80A98934(this, globalCtx) == 0) {
        Actor_Kill(&this->actor);
    }
    this->actionFunc = func_80A99048;
}

void EnKo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnKo* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A99048(EnKo* this, GlobalContext* globalCtx) {
    if ((func_80A96F94(this, globalCtx) != 0) && (func_80A96EC4(this, globalCtx) != 0)) {
        this->actor.flags &= ~0x10;
        this->actor.objBankIndex = this->unk_196;
        gSegments[6] = VIRTUAL_TO_PHYSICAL(globalCtx->objectCtx.status[this->actor.objBankIndex].segment);
        SkelAnime_InitSV(globalCtx, &this->skelAnime, D_80A9A17C[D_80A9A500[this->actor.params & 0xFF].unk_06].skeleton,
                         NULL, this->limbDrawTable, this->transitionDrawTable, 16);
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 18.0f);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(globalCtx->objectCtx.status[this->unk_197].segment);
        Collider_InitCylinder(globalCtx, &this->collider);
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        func_80061EFC(&this->actor.colChkInfo, NULL, &D_80A9A12C);

        if ((this->actor.params & 0xFF) == 7) {
            // Angle z
            osSyncPrintf("\x1b[44m  アングルＺ->(%d)\n\x1b[m", this->actor.shape.rot.z);
            if ((LINK_IS_ADULT) && !CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST)) {
                if (this->actor.shape.rot.z != 1) {
                    Actor_Kill(&this->actor);
                    return;
                }
            } else if (this->actor.shape.rot.z != 0) {
                Actor_Kill(&this->actor);
                return;
            }
        }

        if ((this->actor.params & 0xFF) == 5) {
            this->collider.base.maskA |= 0x40;
        }

        this->unk_212 = func_80A98D2C(this);
        func_80034EC0(&this->skelAnime, D_80A9A18C, D_80A9A4BC[this->actor.params & 0xFF][this->unk_212]);
        Actor_SetScale(&this->actor, 0.01f);
        func_80A98CD8(this);
        this->unk_220 = 0.0f;
        this->unk_1E4 = Path_GetByIndex(globalCtx, (this->actor.params & 0xFF00) >> 8, 0xFF);
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_ELF, this->actor.posRot.pos.x,
                           this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0, 0, 0, 3);
        if ((this->actor.params & 0xFF) == 3) {
            if (!CHECK_QUEST_ITEM(QUEST_KOKIRI_EMERALD)) {
                this->collider.dim.height += 200;
                this->actionFunc = func_80A995CC;
                return;
            }
            Path_CopyLastPoint(this->unk_1E4, &this->actor.posRot.pos);
        }
        this->actionFunc = func_80A99384;
    }
}

void func_80A99384(EnKo* this, GlobalContext* globalCtx) {
    if (((this->actor.params & 0xFF) == 0xC) && (this->unk_1E8.unk_00 != 0) && (this->actor.textId == 0x10B9)) {
        func_80034EC0(&this->skelAnime, D_80A9A18C, 7);
        this->actionFunc = func_80A99438;
    } else if (((this->actor.params & 0xFF) == 0xC) && (this->unk_1E8.unk_00 == 2)) {
        this->actionFunc = func_80A99504;
        globalCtx->msgCtx.unk_E3E7 = 4;
        globalCtx->msgCtx.msgMode = 0x36;
    }
}

void func_80A99438(EnKo* this, GlobalContext* globalCtx) {
    if (((this->actor.params & 0xFF) == 0xC) && (this->unk_1E8.unk_00 == 2)) {
        func_80034EC0(&this->skelAnime, D_80A9A18C, 6);
        this->actionFunc = func_80A99504;
        globalCtx->msgCtx.unk_E3E7 = 4;
        globalCtx->msgCtx.msgMode = 0x36;
    } else if ((this->unk_1E8.unk_00 == 0) || (this->actor.textId != 0x10B9)) {
        func_80034EC0(&this->skelAnime, D_80A9A18C, 6);
        this->actionFunc = func_80A99384;
    }
}

void func_80A99504(EnKo* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80A99560;
    } else {
        func_8002F434(&this->actor, globalCtx, 0x21, 120.0f, 10.0f);
    }
}

void func_80A99560(EnKo* this, GlobalContext* globalCtx) {
    if (this->unk_1E8.unk_00 == 3) {
        this->actor.textId = 0x10B9;
        func_8010B720(globalCtx, this->actor.textId);
        this->unk_1E8.unk_00 = 1;
        gSaveContext.itemGetInf[3] |= 2;
        this->actionFunc = func_80A99384;
    }
}

void func_80A995CC(EnKo* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = PLAYER;
    f32 abs;
    s16 sp22 = Math_Vec3f_Yaw(&this->actor.initPosRot.pos, &player->actor.posRot.pos);

    this->actor.posRot.pos.x = this->actor.initPosRot.pos.x;
    this->actor.posRot.pos.x += 80.0f * Math_Sins(sp22);
    this->actor.posRot.pos.z = this->actor.initPosRot.pos.z;
    this->actor.posRot.pos.z += 80.0f * Math_Coss(sp22);

    this->actor.shape.rot.y = this->actor.posRot.rot.y = this->actor.yawTowardsLink;

    if ((this->unk_1E8.unk_00 == 0) || (this->actor.unk_10C == 0)) {
        abs = (fabsf((f32)this->actor.yawTowardsLink - sp22) * 0.001f) * 3.0f;
        this->skelAnime.animPlaybackSpeed = CLAMP(abs, 1.0f, 3.0f);
    } else {
        this->skelAnime.animPlaybackSpeed = 1.0f;
    }
}

void EnKo_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnKo* this = THIS;
    s32 pad[2];

    if (this->actionFunc != func_80A99048) {
        if ((s32)this->unk_220 != 0) {
            gSegments[6] = VIRTUAL_TO_PHYSICAL(globalCtx->objectCtx.status[this->unk_197].segment);
            SkelAnime_FrameUpdateMatrix(&this->skelAnime);
            func_80A98DB4(this, globalCtx);
            func_80A98C18(this);
        } else {
            func_80A98DB4(this, globalCtx);
        }
    }

    if (this->unk_1E8.unk_00 == 0) {
        Actor_MoveForward(&this->actor);
    }

    if (func_80A97C7C(this) != 0) {
        func_8002E4B4(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
        this->actor.gravity = -1.0f;
    } else {
        this->actor.gravity = 0.0f;
    }

    this->actionFunc(this, globalCtx);
    func_80A9877C(this, globalCtx);
    Collider_CylinderUpdate(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 func_80A99864(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                  Gfx** gfx) {
    s32 pad;
    EnKo* this = THIS;
    u8 idx;
    Vec3s sp40;
    s32 pad2;

    if (limbIndex == 15) {
        gSPSegment((*gfx)++, 0x06, globalCtx->objectCtx.status[this->unk_194].segment);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(globalCtx->objectCtx.status[this->unk_194].segment);

        idx = D_80A9A500[thisx->params & 0xFF].unk_00;
        *dList = D_80A9A158[idx].unk_04;

        if (D_80A9A158[idx].unk_08 != NULL) {
            u32 val = D_80A9A158[idx].unk_08[this->unk_216];
            gSPSegment((*gfx)++, 0x0A, SEGMENTED_TO_VIRTUAL(val));
        }
        gSegments[6] = VIRTUAL_TO_PHYSICAL(globalCtx->objectCtx.status[this->unk_196].segment);
    }

    if (limbIndex == 8) {
        sp40 = this->unk_1E8.unk_0E;
        Matrix_RotateX((-sp40.y / 32768.0f) * M_PI, 1);
        Matrix_RotateZ((sp40.x / 32768.0f) * M_PI, 1);
    }

    if (limbIndex == 15) {
        Matrix_Translate(1200.0f, 0.0f, 0.0f, 1);
        sp40 = this->unk_1E8.unk_08;
        Matrix_RotateX((sp40.y / 32768.0f) * M_PI, 1);
        Matrix_RotateZ((sp40.x / 32768.0f) * M_PI, 1);
        Matrix_Translate(-1200.0f, 0.0f, 0.0f, 1);
    }

    if ((limbIndex == 8) || (limbIndex == 9) || (limbIndex == 12)) {
        rot->y += Math_Sins(this->unk_2E4[limbIndex]) * 200.0f;
        rot->z += Math_Coss(this->unk_304[limbIndex]) * 200.0f;
    }

    return 0;
}

void func_80A99BC4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnKo* this = THIS;
    GlobalContext* localGlobalCtx = globalCtx;
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == 7) {
        gSPSegment((*gfx)++, 0x06, localGlobalCtx->objectCtx.status[this->unk_195].segment);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(localGlobalCtx->objectCtx.status[this->unk_195].segment);
    }

    if (limbIndex == 15) {
        Matrix_MultVec3f(&sp24, &this->actor.posRot2.pos);
    }
}

Gfx* func_80A99C94(GraphicsContext* gfxCtx, u8 r, u8 g, u8 b, u8 a) {
    Gfx* dList = Graph_Alloc(gfxCtx, 0x10);

    gDPSetEnvColor(dList, r, g, b, a);
    gSPEndDisplayList(dList + 1);
    return dList;
}

void EnKo_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnKo* this = THIS;
    Color_RGBA8_n sp60 = D_80A9A500[this->actor.params & 0xFF].unk_02;
    Color_RGBA8_n sp5C = D_80A9A500[this->actor.params & 0xFF].unk_07;

    this->actor.shape.unk_14 = this->unk_220;
    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_ko.c", 2095);

    if ((s16)this->unk_220 == 0xFF) {
        gSPSegment(oGfxCtx->polyOpa.p++, 0x08, func_80A99C94(globalCtx->state.gfxCtx, sp60.r, sp60.g, sp60.b, 255));
        gSPSegment(oGfxCtx->polyOpa.p++, 0x09, func_80A99C94(globalCtx->state.gfxCtx, sp5C.r, sp5C.g, sp5C.b, 255));
        func_80034BA0(globalCtx, &this->skelAnime, func_80A99864, func_80A99BC4, &this->actor, this->unk_220);
    } else if ((s16)this->unk_220 != 0) {
        sp60.a = this->unk_220;
        sp5C.a = this->unk_220;
        gSPSegment(oGfxCtx->polyXlu.p++, 0x08, func_80A99C94(globalCtx->state.gfxCtx, sp60.r, sp60.g, sp60.b, sp60.a));
        gSPSegment(oGfxCtx->polyXlu.p++, 0x09, func_80A99C94(globalCtx->state.gfxCtx, sp5C.r, sp5C.g, sp5C.b, sp5C.a));
        func_80034CC4(globalCtx, &this->skelAnime, func_80A99864, func_80A99BC4, &this->actor, this->unk_220);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_ko.c", 2136);
}
