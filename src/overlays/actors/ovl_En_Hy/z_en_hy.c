/*
 * File: z_en_hy.c
 * Overlay: ovl_En_Hy
 * Description: Market NPCs
 */

#include "z_en_hy.h"

#define FLAGS 0x00000019

#define THIS ((EnHy*)thisx)

void EnHy_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHy_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHy_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHy_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A70E34(EnHy* this, GlobalContext* globalCtx);
void func_80A711B4(EnHy* this, GlobalContext* globalCtx);
void func_80A712C0(EnHy* this, GlobalContext* globalCtx);
void func_80A710F8(EnHy* this, GlobalContext* globalCtx);
void func_80A7127C(EnHy* this, GlobalContext* globalCtx);
void func_80A712B4(EnHy* this, GlobalContext* globalCtx);
void func_80A7134C(EnHy* this, GlobalContext* globalCtx);
void func_80A714C4(EnHy* this, GlobalContext* globalCtx);
void func_80A71530(EnHy* this, GlobalContext* globalCtx);

extern AnimationHeader D_06000BFC;
extern AnimationHeader D_06000FE4;
extern AnimationHeader D_060012E8;
extern AnimationHeader D_06002160;
extern AnimationHeader D_0600265C;
extern AnimationHeader D_060033B4;
extern Gfx D_06005BC8[];

const ActorInit En_Hy_InitVars = {
    ACTOR_EN_HY,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnHy),
    (ActorFunc)EnHy_Init,
    (ActorFunc)EnHy_Destroy,
    (ActorFunc)EnHy_Update,
    (ActorFunc)EnHy_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 20, 46, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 D_80A71EEC = { 0x00, 0x0000, 0x0000, 0x0000, 0xFF };

static s32 D_80A71EF8[] = {
    0x060005C8,
    0x06000DC8,
    0x060015C8,
    0x00000000,
};

static s32 D_80A71F08[] = {
    0x0600057C,
    0x0600067C,
    0x0600077C,
    0x00000000,
};

static s32 D_80A71F18[] = {
    0x060004C8,
    0x00000000,
};

static s32 D_80A71F20[] = {
    0x060005FC,
    0x060009FC,
    0x06000DFC,
    0x00000000,
};

static s32 D_80A71F30[] = {
    0x060005FC,
    0x060006FC,
    0x060007FC,
    0x00000000,
};

static s32 D_80A71F40[] = {
    0x060007C8,
    0x06000FC8,
    0x060017C8,
    0x00000000,
};

typedef struct {
    s16 objId;
    Gfx* unk_4;
    s32* unk_8;
} EnHyStruct3;

EnHyStruct3 D_80A71F50[] = {
    { OBJECT_AOB, 0x06003C88, D_80A71EF8 }, { OBJECT_BOB, 0x06003B78, D_80A71F40 },
    { OBJECT_BOJ, 0x060026F0, D_80A71F30 }, { OBJECT_BOJ, 0x060052E0, NULL },
    { OBJECT_BOJ, 0x06005528, NULL },       { OBJECT_BOJ, 0x06005738, NULL },
    { OBJECT_BOJ, 0x060059B0, NULL },       { OBJECT_AHG, 0x060030F0, D_80A71F08 },
    { OBJECT_AHG, 0x06005508, NULL },       { OBJECT_AHG, 0x06005728, NULL },
    { OBJECT_BBA, 0x06002948, D_80A71F18 }, { OBJECT_CNE, 0x06001300, NULL },
    { OBJECT_CNE, 0x06002860, NULL },       { OBJECT_BJI, 0x06002560, D_80A71F20 },
    { OBJECT_BJI, 0x06003F68, NULL },       { OBJECT_COB, 0x06001300, NULL },
};

typedef struct {
    s16 objId;
    SkeletonHeader* skelHdr;
} EnHyStruct2;

static EnHyStruct2 D_80A72010[] = {
    { OBJECT_AOB, 0x060000F0 }, { OBJECT_BOB, 0x060000F0 }, { OBJECT_BOJ, 0x060000F0 }, { OBJECT_AHG, 0x060000F0 },
    { OBJECT_BBA, 0x060000F0 }, { OBJECT_CNE, 0x060000F0 }, { OBJECT_BJI, 0x060000F0 }, { OBJECT_COB, 0x060021F8 },
};

static struct_80034EC0_Entry D_80A72050[] = {
    { 0x0600092C, 1.0f, 0.0f, -1.0f, 0, 0.0f },   { 0x06000228, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { 0x06004CF4, 1.0f, 0.0f, -1.0f, 0, 0.0f },   { 0x060016EC, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { 0x0600265C, 1.0f, 0.0f, -1.0f, 0, 0.0f },   { 0x060042AC, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { 0x060028DC, 1.0f, 0.0f, -1.0f, 0, 0.0f },   { 0x06002160, 1.0f, 0.0f, -1.0f, 0, -10.0f },
    { 0x0600265C, 1.0f, 0.0f, -1.0f, 0, -10.0f }, { 0x06004E90, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { 0x06001E7C, 1.0f, 0.0f, -1.0f, 0, 0.0f },   { 0x06000170, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { 0x060000B4, 1.0f, 0.0f, -1.0f, 0, 0.0f },   { 0x06003D84, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { 0x060041F8, 1.0f, 0.0f, -1.0f, 0, 0.0f },   { 0x0600300C, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { 0x060031B0, 1.0f, 0.0f, -1.0f, 0, 0.0f },   { 0x060031B0, 1.0f, 0.0f, -1.0f, 0, -8.0f },
    { 0x06002D0C, 1.0f, 0.0f, -1.0f, 0, 0.0f },   { 0x06002DC0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { 0x06004408, 1.0f, 0.0f, -1.0f, 0, 0.0f },   { 0x06001F18, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { 0x06004F28, 1.0f, 0.0f, -1.0f, 0, 0.0f },   { 0x060033B4, 1.0f, 0.0f, -1.0f, 0, -8.0f },
    { 0x060012E8, 1.0f, 0.0f, -1.0f, 0, -8.0f },  { 0x06000FE4, 1.0f, 0.0f, -1.0f, 0, -8.0f },
    { 0x06000BFC, 1.0f, 0.0f, -1.0f, 0, -8.0f },
};

typedef struct {
    u8 unk_0;
    u8 unk_1;
    Color_RGBA8_n unk_2;
    u8 unk_6;
    Color_RGBA8_n unk_7;
    u8 unk_B;
} EnHyStruct1;

EnHyStruct1 D_80A722D8[] = {
    { 0x00, 0x00, { 255, 255, 255, 255 }, 0x00, { 255, 255, 255, 255 }, 0x00 },
    { 0x0F, 0x07, { 255, 255, 255, 255 }, 0x07, { 255, 255, 255, 255 }, 0x16 },
    { 0x07, 0x03, { 255, 255, 255, 255 }, 0x03, { 255, 255, 255, 255 }, 0x01 },
    { 0x03, 0x02, { 255, 255, 255, 0 }, 0x02, { 55, 55, 255, 0 }, 0x0F },
    { 0x08, 0x03, { 0, 0, 0, 0 }, 0x03, { 255, 0, 0, 0 }, 0x0B },
    { 0x04, 0x02, { 50, 80, 0, 0 }, 0x02, { 50, 80, 0, 0 }, 0x10 },
    { 0x0A, 0x04, { 255, 255, 255, 255 }, 0x04, { 255, 255, 255, 255 }, 0x0A },
    { 0x0D, 0x06, { 0, 50, 160, 0 }, 0x06, { 255, 255, 255, 0 }, 0x04 },
    { 0x0B, 0x05, { 160, 180, 255, 0 }, 0x05, { 160, 180, 255, 0 }, 0x09 },
    { 0x02, 0x02, { 220, 0, 80, 0 }, 0x02, { 255, 255, 255, 0 }, 0x0D },
    { 0x02, 0x02, { 0, 130, 220, 0 }, 0x02, { 255, 255, 255, 0 }, 0x0E },
    { 0x0C, 0x05, { 70, 160, 230, 0 }, 0x05, { 255, 255, 100, 0 }, 0x14 },
    { 0x05, 0x02, { 150, 60, 90, 0 }, 0x02, { 255, 240, 150, 0 }, 0x12 },
    { 0x09, 0x03, { 200, 180, 255, 0 }, 0x03, { 200, 180, 255, 0 }, 0x0C },
    { 0x06, 0x02, { 140, 255, 110, 0 }, 0x02, { 255, 255, 255, 0 }, 0x13 },
    { 0x0E, 0x06, { 130, 70, 20, 0 }, 0x06, { 130, 180, 255, 0 }, 0x15 },
    { 0x02, 0x02, { 255, 255, 255, 255 }, 0x02, { 255, 255, 255, 255 }, 0x05 },
    { 0x08, 0x03, { 90, 100, 20, 255 }, 0x03, { 100, 140, 50, 255 }, 0x0B },
    { 0x01, 0x01, { 255, 255, 255, 255 }, 0x01, { 255, 255, 255, 255 }, 0x06 },
    { 0x0E, 0x06, { 160, 0, 100, 0 }, 0x06, { 70, 130, 210, 0 }, 0x15 },
    { 0x09, 0x03, { 160, 230, 0, 0 }, 0x03, { 0, 150, 110, 0 }, 0x0C },
};

static s16 D_80A723D4[][5] = {
    { 0x0000, 0x0000, 0x0004, 0x0018, 0x0046 }, { 0x0000, 0x0000, 0x0008, 0x001C, 0x003E },
    { 0x0000, 0x0000, 0x0004, 0x0014, 0x003C }, { 0x0000, 0x0000, 0x0002, 0x0014, 0x003C },
    { 0x0000, 0x0000, 0xFFFE, 0x0014, 0x003C }, { 0x0000, 0x0000, 0x0008, 0x0018, 0x0028 },
    { 0x0000, 0x0000, 0x000A, 0x001A, 0x0028 }, { 0x0000, 0x0000, 0x000C, 0x001A, 0x003A },
    { 0x0000, 0x0000, 0x0002, 0x0012, 0x0044 }, { 0x0000, 0x0000, 0x0004, 0x0014, 0x003C },
    { 0x0000, 0x0000, 0x0004, 0x0014, 0x003C }, { 0x0000, 0x0000, 0x0006, 0x0014, 0x0040 },
    { 0x0000, 0x0000, 0x0000, 0x0012, 0x003C }, { 0x0000, 0x0000, 0x0000, 0x0010, 0x003C },
    { 0x0000, 0x0000, 0x0000, 0x0010, 0x0040 }, { 0x0000, 0x0000, 0x0008, 0x0014, 0x003A },
    { 0x0004, 0x0000, 0x0000, 0x0012, 0x003E }, { 0x0004, 0x0000, 0x0000, 0x0012, 0x003E },
    { 0x0000, 0x0000, 0x0008, 0x001C, 0x003E }, { 0x0000, 0x0000, 0x0000, 0x0010, 0x003C },
    { 0x0000, 0x0000, 0x0008, 0x0014, 0x003A },
};

typedef struct {
    u8 unk_0;
    f32 unk_4;
    f32 unk_8;
} EnHyStruct5;

static EnHyStruct5 D_80A724A8[] = {
    { 0x06, 20.0f, 10.0f }, { 0x06, 20.0f, 10.0f }, { 0x07, 40.0f, 20.0f }, { 0x06, 20.0f, 10.0f },
    { 0x07, 40.0f, 20.0f }, { 0x08, 0.0f, -20.0f }, { 0x09, 20.0f, 0.0f },  { 0x09, 20.0f, 0.0f },
    { 0x06, 20.0f, 10.0f }, { 0x06, 20.0f, 10.0f }, { 0x06, 20.0f, 10.0f }, { 0x06, 20.0f, 10.0f },
    { 0x00, 0.0f, 0.0f },   { 0x06, 20.0f, 10.0f }, { 0x06, 20.0f, 10.0f }, { 0x0A, 20.0f, 0.0f },
    { 0x06, 20.0f, 10.0f }, { 0x06, 20.0f, 10.0f }, { 0x06, 20.0f, 10.0f }, { 0x06, 20.0f, 10.0f },
    { 0x0A, 20.0f, 0.0f },
};

typedef struct {
    f32 unk_00;
    Vec3f unk_04;
    f32 unk_10;
    s8 unk_14;
    f32 unk_18;
} EnHyStruct4;

static EnHyStruct4 D_80A725A4[] = {
    { 36.0f, 0.0f, 0.0f, 600.0f, 0.01f, 0x06, 30.0f },     { 40.0f, -100.0f, 0.0f, 400.0f, 0.01f, 0x06, 30.0f },
    { 22.0f, 0.0f, 0.0f, -200.0f, 0.01f, 0x06, 30.0f },    { 20.0f, -100.0f, 0.0f, 0.0f, 0.01f, 0x06, 30.0f },
    { 22.0f, 0.0f, 0.0f, 0.0f, 0.01f, 0x06, 30.0f },       { 21.0f, 0.0f, 0.0f, 0.0f, 0.01f, 0x06, 30.0f },
    { 25.0f, -100.0f, 0.0f, 600.0f, 0.01f, 0x06, 30.0f },  { 28.0f, -100.0f, 0.0f, 800.0f, 0.01f, 0x06, 30.0f },
    { 17.0f, 0.0f, 0.0f, 700.0f, 0.01f, 0x06, 30.0f },     { 18.0f, 0.0f, 0.0f, 100.0f, 0.01f, 0x06, 30.0f },
    { 18.0f, 0.0f, 0.0f, -200.0f, 0.01f, 0x06, 30.0f },    { 17.0f, 0.0f, 0.0f, 700.0f, 0.01f, 0x06, 30.0f },
    { 21.0f, 0.0f, 0.0f, -300.0f, 0.01f, 0x06, 30.0f },    { 20.0f, 0.0f, 0.0f, -200.0f, 0.01f, 0x06, 30.0f },
    { 18.0f, -200.0f, 0.0f, -200.0f, 0.01f, 0x06, 30.0f }, { 27.0f, -100.0f, 0.0f, 800.0f, 0.01f, 0x06, 30.0f },
    { 19.0f, 400.0f, 0.0f, 0.0f, 0.01f, 0x04, 30.0f },     { 19.0f, 400.0f, 0.0f, 0.0f, 0.01f, 0x06, 30.0f },
    { 40.0f, -100.0f, 0.0f, 400.0f, 0.01f, 0x06, 30.0f },  { 17.0f, 0.0f, 0.0f, 700.0f, 0.01f, 0x06, 30.0f },
    { 20.0f, 0.0f, 0.0f, -200.0f, 0.01f, 0x06, 30.0f },
};

typedef struct {
    s16 unk_0[4];
} EnHyStruct6;

static EnHyStruct6 D_80A727F0 = { 0x001C, 0x0019, 0x001D, 0x0018 };
static EnHyStruct6 D_80A727F8 = { 0x0096, 0x0064, 0x0032, 0x0019 };

s32 func_80A6F5B0(EnHy* this, GlobalContext* globalCtx) {
    u8 sp1F = D_80A722D8[this->actor.params & 0x7F].unk_0;
    u8 sp1E = D_80A722D8[this->actor.params & 0x7F].unk_1;
    u8 sp1D = D_80A722D8[this->actor.params & 0x7F].unk_6;

    this->unk_198 = Object_GetIndex(&globalCtx->objectCtx, D_80A72010[sp1D].objId);
    if (this->unk_198 < 0) {
        return 0;
    }

    this->unk_197 = Object_GetIndex(&globalCtx->objectCtx, D_80A72010[sp1E].objId);
    if (this->unk_197 < 0) {
        return 0;
    }

    this->unk_196 = Object_GetIndex(&globalCtx->objectCtx, D_80A71F50[sp1F].objId);
    if (this->unk_196 < 0) {
        return 0;
    }

    return 1;
}

s32 func_80A6F6C0(EnHy* this, GlobalContext* globalCtx) {
    if (!Object_IsLoaded(&globalCtx->objectCtx, this->unk_198)) {
        return 0;
    }

    if (!Object_IsLoaded(&globalCtx->objectCtx, this->unk_197)) {
        return 0;
    }

    if (!Object_IsLoaded(&globalCtx->objectCtx, this->unk_196)) {
        return 0;
    }

    return 1;
}

s32 func_80A6F744(EnHy* this, GlobalContext* globalCtx) {
    this->unk_199 = Object_GetIndex(&globalCtx->objectCtx, OBJECT_OS_ANIME);
    if (this->unk_199 < 0) {
        return 0;
    }
    return 1;
}

s32 func_80A6F790(EnHy* this, GlobalContext* globalCtx) {
    if (!Object_IsLoaded(&globalCtx->objectCtx, this->unk_199)) {
        return 0;
    }
    return 1;
}

void func_80A6F7CC(EnHy* this, GlobalContext* globalCtx, s32 arg2) {
    this->unk_260 = arg2;
    func_8002F434(&this->actor, globalCtx, arg2, this->actor.xzDistFromLink + 1.0f,
                  fabsf(this->actor.yDistFromLink) + 1.0f);
}

u16 func_80A6F810(GlobalContext* globalCtx, Actor* thisx) {
    Player* player = PLAYER;
    EnHy* this = THIS;
    s16 ret;
    s16 tmp2;
    u16 tmp = Text_GetFaceReaction(globalCtx, (this->actor.params & 0x7F) + 0x25);

    if (tmp != 0) {
        if ((this->actor.params & 0x7F) == 5) {
            player->exchangeItemId = 0x19;
        }
        return tmp;
    }

    switch (this->actor.params & 0x7F) {
        case 0:
            if (globalCtx->sceneNum == SCENE_KAKARIKO) {
                return ((this->unk_330 & 0x800) != 0) ? 0x508D
                                                      : ((gSaveContext.infTable[12] & 0x800) != 0) ? 0x508C : 0x508B;
            } else if (globalCtx->sceneNum == SCENE_MARKET_DAY) {
                if (gSaveContext.eventInf[3] & 1) {
                    ret = 0x709B;
                } else {
                    ret = 0x709C;
                }
                return ret;
            } else if (gSaveContext.dogIsLost != 0) {
                tmp2 = (gSaveContext.dogParams & 0xF00) >> 8;
                if (tmp2 != 0) {
                    this->unk_215 = 0;
                    if (tmp2 == 1) {
                        ret = 0x709F;
                    } else {
                        ret = 0x709E;
                    }
                    return ret;
                } else {
                    return 0x709D;
                }
            }
            return 0x70A0;

        case 1:
            if (gSaveContext.eventChkInf[8] & 1) {
                if (gSaveContext.infTable[12] & 2) {
                    ret = 0x7017;
                } else {
                    ret = 0x7045;
                }
                return ret;
            } else if (gSaveContext.infTable[12] & 1) {
                ret = 0x7017;
            } else {
                ret = 0x7016;
            }
            return ret;

        case 2:
            if (globalCtx->sceneNum == SCENE_KAKARIKO) {
                return 0x5086;
            } else if (globalCtx->sceneNum == SCENE_SPOT01) {
                return 0x5085;
            }

            if (gSaveContext.eventChkInf[8] & 1) {
                if (gSaveContext.infTable[12] & 8) {
                    ret = 0x701A;
                } else {
                    ret = 0x7047;
                }
                return ret;
            } else if (gSaveContext.eventChkInf[1] & 0x10) {
                return 0x701A;
            } else if (gSaveContext.eventChkInf[1] & 1) {
                return 0x701B;
            } else if (gSaveContext.infTable[12] & 4) {
                return 0x701C;
            }
            return 0x701A;

        case 3:
            return (gSaveContext.eventChkInf[8] & 1) ? (gSaveContext.infTable[12] & 0x10) ? 0x7001 : 0x70EB : 0x7001;

        case 4:
            return (gSaveContext.eventChkInf[8] & 1) ? 0x704B : ((gSaveContext.infTable[12] & 0x20) ? 0x7024 : 0x7023);

        case 5:
            player->exchangeItemId = 0x19;
            return 0x700C;

        case 6:
            return (gSaveContext.eventChkInf[8] & 1) ? 0x704A : (gSaveContext.infTable[12] & 0x40) ? 0x7022 : 0x7021;

        case 7:
            if (globalCtx->sceneNum == SCENE_KAKARIKO) {
                return 0x5088;
            } else if (globalCtx->sceneNum == SCENE_SPOT01) {
                return 0x5087;
            }
            return (gSaveContext.eventChkInf[8] & 1) ? 0x704D : (gSaveContext.infTable[12] & 0x80) ? 0x7028 : 0x7027;

        case 8:
            if (gSaveContext.eventChkInf[8] & 1) {
                if (gSaveContext.infTable[12] & 0x200) {
                    ret = 0x701E;
                } else {
                    ret = 0x7048;
                }
            } else if (gSaveContext.infTable[12] & 0x100) {
                ret = 0x701E;
            } else {
                ret = 0x701D;
            }
            return ret;

        case 9:
            if (globalCtx->sceneNum == SCENE_KAKARIKO) {
                if (gSaveContext.eventChkInf[10] & 0x400) {
                    ret = 0x5082;
                } else {
                    ret = 0x5081;
                }
            } else if (globalCtx->sceneNum == SCENE_SPOT01) {
                if (CHECK_QUEST_ITEM(QUEST_MEDALLION_SHADOW)) {
                    ret = 0x5080;
                } else {
                    ret = 0x507F;
                }
            } else {
                return (gSaveContext.eventChkInf[8] & 1) ? 0x7049
                                                         : (gSaveContext.infTable[12] & 0x400) ? 0x7020 : 0x701F;
            }
            return ret;

        case 10:
            if (globalCtx->sceneNum == SCENE_LABO) {
                if (gSaveContext.eventChkInf[10] & 0x400) {
                    ret = 0x507E;
                } else {
                    ret = 0x507D;
                }
                return ret;
            } else if (globalCtx->sceneNum == SCENE_SPOT01) {
                if (CHECK_QUEST_ITEM(QUEST_MEDALLION_SHADOW)) {
                    ret = 0x507C;
                } else {
                    ret = 0x507B;
                }
                return ret;
            } else {
                return (gSaveContext.eventChkInf[8] & 1) ? 0x7046
                                                         : (gSaveContext.infTable[12] & 0x2000) ? 0x7019 : 0x7018;
            }

        case 11:
            return (gSaveContext.infTable[8] & 0x800) ? (gSaveContext.infTable[12] & 0x1000) ? 0x7014 : 0x70A4 : 0x7014;

        case 12:
            if (globalCtx->sceneNum == SCENE_SPOT01) {
                if (gSaveContext.nightFlag != 0) {
                    ret = 0x5084;
                } else {
                    ret = 0x5083;
                }
            } else if (gSaveContext.eventChkInf[8] & 1) {
                ret = 0x7044;
            } else {
                ret = 0x7015;
            }
            return ret;

        case 13:
            return 0x7055;

        case 14:
            return 0x7089;

        case 15:
            return 0x708A;

        case 16:
            return 0x700E;

        case 17:
            if (LINK_IS_CHILD) {
                if (gSaveContext.nightFlag == 0) {
                    if (gSaveContext.infTable[22] & 1) {
                        ret = 0x5058;
                    } else {
                        ret = 0x5057;
                    }
                } else if (gSaveContext.infTable[22] & 2) {
                    ret = 0x505A;
                } else {
                    ret = 0x5059;
                }
                return ret;
            } else if (gSaveContext.nightFlag == 0) {
                if (gSaveContext.infTable[22] & 4) {
                    ret = 0x505C;
                } else {
                    ret = 0x505B;
                }
                return ret;
            }
            return 0x5058;

        case 18:
            if (LINK_IS_CHILD) {
                return (gSaveContext.eventChkInf[8] & 1) ? 0x505F : (gSaveContext.infTable[22] & 8) ? 0x505E : 0x505D;
            } else {
                return (this->unk_330 & 0x800) ? 0x5062 : (gSaveContext.infTable[22] & 0x10) ? 0x5061 : 0x5060;
            }

        case 19:
            return 0x7120;

        case 20:
            return 0x7121;
    }

    return 0;
}

s16 func_80A70058(GlobalContext* globalCtx, Actor* thisx) {
    EnHy* this = THIS;
    EnHyStruct6 sp3C = D_80A727F0;
    EnHyStruct6 sp34 = D_80A727F8;

    switch (func_8010BDBC(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 4:
        case 6:
        case 7:
        case 8:
        case 9:
            return 1;

        case 3:
            switch (this->actor.textId) {
                case 0x709E:
                case 0x709F:
                    if (this->unk_215 == 0) {
                        Audio_PlaySoundGeneral((this->actor.textId == 0x709F) ? NA_SE_SY_CORRECT_CHIME : NA_SE_SY_ERROR,
                                               &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
                        this->unk_215 = 1;
                        return 1;
                    }
                    break;
                case 0x70F0:
                case 0x70F1:
                case 0x70F2:
                case 0x70F3:
                    if (this->skelAnime.animCurrentSeg != &D_060033B4) {
                        func_80034EC0(&this->skelAnime, D_80A72050, 0x17);
                        func_800F5C64(0x922);
                    }
                    break;
            }
            return 1;

        case 2:
            switch (this->actor.textId) {
                case 0x70F0:
                case 0x70F1:
                case 0x70F2:
                case 0x70F3:
                    Rupees_ChangeBy(sp34.unk_0[this->actor.textId - 0x70F0]);
                    func_80034EC0(&this->skelAnime, D_80A72050, 0x11);
                    func_8008ED9C(globalCtx, PLAYER, 0x14, 0x1E);
                    return 0;
                case 0x7016:
                    gSaveContext.infTable[12] |= 1;
                    break;
                case 0x7045:
                    gSaveContext.infTable[12] |= 2;
                    break;
                case 0x701B:
                    gSaveContext.infTable[12] |= 4;
                    break;
                case 0x7047:
                    gSaveContext.infTable[12] |= 8;
                    break;
                case 0x70EB:
                    gSaveContext.infTable[12] |= 0x10;
                    break;
                case 0x7023:
                    gSaveContext.infTable[12] |= 0x20;
                    break;
                case 0x7021:
                    gSaveContext.infTable[12] |= 0x40;
                    break;
                case 0x7027:
                    gSaveContext.infTable[12] |= 0x80;
                    break;
                case 0x701D:
                    gSaveContext.infTable[12] |= 0x100;
                    break;
                case 0x7048:
                    gSaveContext.infTable[12] |= 0x200;
                    break;
                case 0x701F:
                    gSaveContext.infTable[12] |= 0x400;
                    break;
                case 0x7018:
                    gSaveContext.infTable[12] |= 0x2000;
                    break;
                case 0x70A4:
                    gSaveContext.infTable[12] |= 0x1000;
                    break;
                case 0x5057:
                    gSaveContext.infTable[22] |= 1;
                    break;
                case 0x5059:
                    gSaveContext.infTable[22] |= 2;
                    break;
                case 0x505B:
                    gSaveContext.infTable[22] |= 4;
                    break;
                case 0x505D:
                    gSaveContext.infTable[22] |= 8;
                    break;
                case 0x5060:
                    gSaveContext.infTable[22] |= 0x10;
                    break;
                case 0x508B:
                    gSaveContext.infTable[12] |= 0x800;
                    break;
                case 0x709E:
                    gSaveContext.dogParams = 0;
                    break;
                case 0x709F:
                    func_80A6F7CC(this, globalCtx, (gSaveContext.infTable[25] & 2) ? GI_RUPEE_BLUE : GI_HEART_PIECE);
                    this->actionFunc = func_80A714C4;

                case 0x7017:
                case 0x7019:
                case 0x701A:
                case 0x701C:
                case 0x701E:
                case 0x7020:
                case 0x7022:
                case 0x7024:
                case 0x7025:
                case 0x7026:
                case 0x70EC:
                case 0x70ED:
                case 0x70EE:
                case 0x70EF:
                case 0x5058:
                case 0x505A:
                case 0x505C:
                case 0x505E:
                case 0x505F:
                    break;
            }
            return 0;

        case 5:
            if (func_80106BC8(globalCtx) == 0) {
                return 1;
            }
            return 2;
    }

    return 1;
}

void func_80A705A4(EnHy* this) {
    u8 idx;
    s32* ptr;

    if (DECR(this->unk_21A) == 0) {
        idx = D_80A722D8[this->actor.params & 0x7F].unk_0;
        this->unk_218++;
        ptr = D_80A71F50[idx].unk_8;

        if ((ptr != NULL) && (ptr[this->unk_218] == 0)) {
            this->unk_21A = Math_Rand_S16Offset(0x1E, 0x1E);
            this->unk_218 = 0;
        }
    }
}

void func_80A70660(EnHy* this) {
    s32 idx = (this->actor.params & 0x7F) & 0xFF;

    this->collider.dim.radius = D_80A723D4[idx][3];
    this->collider.dim.height = D_80A723D4[idx][4];
}

void func_80A70698(EnHy* this) {
    s32 idx = (this->actor.params & 0x7F) & 0xFF;

    this->actor.shape.unk_10 = D_80A725A4[idx].unk_00;
    Actor_SetScale(&this->actor, D_80A725A4[idx].unk_10);
    this->actor.unk_1F = D_80A725A4[idx].unk_14;
    this->unk_264 = D_80A725A4[idx].unk_04;
    this->unk_25C = D_80A725A4[idx].unk_18;
    this->unk_25C += this->collider.dim.radius;
}

void func_80A70734(EnHy* this, GlobalContext* globalCtx) {
    Vec3s sp18;

    sp18.x = this->actor.posRot.pos.x;
    sp18.y = this->actor.posRot.pos.y;
    sp18.z = this->actor.posRot.pos.z;

    sp18.x += D_80A723D4[this->actor.params & 0x7F][0];
    sp18.y += D_80A723D4[this->actor.params & 0x7F][1];
    sp18.z += D_80A723D4[this->actor.params & 0x7F][2];

    this->collider.dim.pos = sp18;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80A70834(EnHy* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 ret;

    if ((this->actor.params & 0x7F) == 5) {
        if ((Inventory_HasSpecificBottle(0x1C) == 0) && (Inventory_HasSpecificBottle(0x1D) == 0) &&
            (Inventory_HasSpecificBottle(0x19) == 0)) {
            ret = func_8002F368(globalCtx);
            if ((ret == 0x1B) || (ret == 0x1C) || (ret == 0x1D)) {
                this->actor.textId = 0x70EF;
            } else if (func_8008F080(globalCtx) == 0) {
                this->actor.textId = 0x70ED;
            }
        } else {
            switch (func_8002F368(globalCtx)) {
                case 0x19:
                    this->actor.textId = 0x70F0;
                    break;

                case 0x18:
                    this->actor.textId = 0x70F1;
                    break;

                case 0x1A:
                    this->actor.textId = 0x70F2;
                    break;

                default:
                    if (func_8008F080(globalCtx) == 0) {
                        this->actor.textId = 0x700C;
                    }
                    break;
            }
        }
        player->actor.textId = this->actor.textId;
    }
}

void func_80A70978(EnHy* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 tmp;
    s16 tmp2;

    switch (this->actor.params & 0x7F) {
        case 3:
        case 7:
        case 9:
        case 10:
            if (this->unk_1E8.unk_00 == 0) {
                tmp = 1;
            } else {
                tmp = 2;
            }
            break;

        case 12:
            tmp = 1;
            break;

        case 2:
        case 17:
            tmp = 4;
            break;

        case 0:
        case 18:
            if (this->unk_1E8.unk_00 == 0) {
                tmp = 2;
            } else {
                tmp = 4;
            }
            break;

        default:
            tmp = 2;
            break;
    }

    this->unk_1E8.unk_18 = player->actor.posRot.pos;
    if (gSaveContext.linkAge == 0) {
        this->unk_1E8.unk_14 = D_80A724A8[this->actor.params & 0x7F].unk_8;
    } else {
        this->unk_1E8.unk_14 = D_80A724A8[this->actor.params & 0x7F].unk_4;
    }

    func_80034A14(&this->actor, &this->unk_1E8, D_80A724A8[this->actor.params & 0x7F].unk_0, tmp);
    if (func_800343CC(globalCtx, &this->actor, &this->unk_1E8.unk_00, this->unk_25C, func_80A6F810, func_80A70058) !=
        0) {
        func_80A70834(this, globalCtx);
    }
}

s32 func_80A70AE4(EnHy* this, GlobalContext* globalCtx) {
    s32 params;
    s16 tmpParams;

    switch (globalCtx->sceneNum) {
        case 82:

            if (((this->actor.params & 0x7F) != 9) && ((this->actor.params & 0x7F) != 10) &&
                ((this->actor.params & 0x7F) != 12) && ((this->actor.params & 0x7F) != 2) &&
                ((this->actor.params & 0x7F) != 7)) {
                return 1;
            }

            if (LINK_IS_CHILD) {
                return 1;
            }

            if (((this->actor.params & 0x7F) != 12) && (gSaveContext.nightFlag == 1)) {
                return 0;
            }

            return 1;

        case 55:
            if ((this->actor.params & 0x7F) != 10) {
                return 1;
            }

            if (gSaveContext.linkAge == 1) {
                return 0;
            }

            if (((this->actor.params & 0x7F) == 10) && (gSaveContext.nightFlag == 0)) {
                return 0;
            }

            return 1;

        case 53:
            if ((this->actor.params & 0x7F) != 0) {
                return 1;
            }

            if (gSaveContext.nightFlag == 0) {
                return 0;
            }

            return 1;

        case 42:
            if ((this->actor.params & 0x7F) == 0) {
                return (LINK_IS_CHILD) ? 0 : 1;
            }

            if (((this->actor.params & 0x7F) != 9) && ((this->actor.params & 0x7F) != 2) &&
                ((this->actor.params & 0x7F) != 7)) {
                return 1;
            }

            if (gSaveContext.nightFlag == 0) {
                return 0;
            }

            if (gSaveContext.linkAge == 1) {
                return 0;
            }

            return 1;

        case 30:
        case 31:
            if ((this->actor.params & 0x7F) != 14) {
                return 1;
            }

            if (gSaveContext.nightFlag == 1) {
                return 0;
            }

            if ((gSaveContext.eventChkInf[8] & 1) && !(gSaveContext.eventChkInf[4] & 0x20)) {
                return 0;
            }

            return 1;
    }

    tmpParams = this->actor.params;
    params = tmpParams & 0xFFFF;
    if (((params & 0x7F) == 19) || ((params & 0x7F) == 20)) {
        if (gSaveContext.linkAge == 0) {
            return 0;
        }
    }

    return 1;
}

void EnHy_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHy* this = THIS;

    if (((this->actor.params & 0x7F) >= 0x15) || (func_80A6F744(this, globalCtx) == 0) ||
        (func_80A6F5B0(this, globalCtx) == 0)) {
        Actor_Kill(&this->actor);
    }

    if (func_80A70AE4(this, globalCtx) == 0) {
        Actor_Kill(&this->actor);
    }

    this->actionFunc = func_80A70E34;
}

void EnHy_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHy* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A70E34(EnHy* this, GlobalContext* globalCtx) {
    if ((func_80A6F790(this, globalCtx) != 0) && (func_80A6F6C0(this, globalCtx) != 0)) {
        this->actor.objBankIndex = this->unk_198;
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->actor.objBankIndex].segment);
        SkelAnime_InitSV(globalCtx, &this->skelAnime, D_80A72010[D_80A722D8[this->actor.params & 0x7F].unk_6].skelHdr,
                         NULL, this->limbDrawTable, this->transitionDrawTable, 16);
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Circle, 0.0f);
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_199].segment);
        Collider_InitCylinder(globalCtx, &this->collider);
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        func_80A70660(this);
        func_80061EFC(&this->actor.colChkInfo, NULL, &D_80A71EEC);
        func_80034EC0(&this->skelAnime, D_80A72050, D_80A722D8[this->actor.params & 0x7F].unk_B);

        if ((globalCtx->sceneNum == SCENE_MARKET_ALLEY) || (globalCtx->sceneNum == SCENE_MARKET_DAY)) {
            this->actor.flags &= ~0x10;
            this->actor.uncullZoneScale = 0.0f;
        }

        if (globalCtx->sceneNum == SCENE_KAKARIKO) {
            this->unk_330 = gSaveContext.eventChkInf[6];
        }

        func_80A70698(this);
        this->unk_210 = Path_GetByIndex(globalCtx, (this->actor.params & 0x780) >> 7, 0xF);

        switch (this->actor.params & 0x7F) {
            case 3:
                if (this->unk_210 != NULL) {
                    this->actor.speedXZ = 3.0f;
                }
                this->actionFunc = func_80A711B4;
                break;

            case 7:
                this->unk_195 = 0;
                this->actionFunc = func_80A712C0;
                break;

            case 0:
                if (globalCtx->sceneNum == SCENE_MARKET_DAY) {
                    this->actionFunc = func_80A710F8;
                    break;
                }

            case 1:
            case 2:
            case 4:
            case 6:
            case 8:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
                this->actionFunc = func_80A7127C;
                break;

            case 5:
            case 9:
            case 10:
            case 11:
            case 12:
                this->actionFunc = func_80A712B4;
                break;

            default:
                Actor_Kill(&this->actor);
                break;
        }
    }
}

void func_80A710F8(EnHy* this, GlobalContext* globalCtx) {
    if (this->unk_1E8.unk_00 != 0) {
        if (this->skelAnime.animCurrentSeg != &D_06000BFC) {
            func_80034EC0(&this->skelAnime, D_80A72050, 0x1A);
        }
    } else if (gSaveContext.eventInf[3] & 1) {
        if (this->skelAnime.animCurrentSeg != &D_06000FE4) {
            func_80034EC0(&this->skelAnime, D_80A72050, 0x19);
        }
    } else if (this->skelAnime.animCurrentSeg != &D_060012E8) {
        func_80034EC0(&this->skelAnime, D_80A72050, 0x18);
    }
}

void func_80A711B4(EnHy* this, GlobalContext* globalCtx) {
    s16 sp2E;
    f32 sp28 = Path_OrientAndGetDistSq(&this->actor, this->unk_210, this->unk_214, &sp2E);

    Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, sp2E, 0xA, 0x3E8, 1);
    this->actor.shape.rot = this->actor.posRot.rot;
    if ((sp28 > 0.0f) && (sp28 < 1000.0f)) {
        this->unk_214++;
        if ((this->unk_210->count - 1) < this->unk_214) {
            this->unk_214 = 0;
        }
    }
}

void func_80A7127C(EnHy* this, GlobalContext* globalCtx) {
    func_80034F54(globalCtx, this->unk_21C, this->unk_23C, 16);
}

void func_80A712B4(EnHy* this, GlobalContext* globalCtx) {
}

void func_80A712C0(EnHy* this, GlobalContext* globalCtx) {
    if ((this->actor.xzDistFromLink <= 100.0f) && (this->unk_210 != NULL)) {
        func_80034EC0(&this->skelAnime, D_80A72050, 7);
        this->actor.speedXZ = 0.4f;
        this->actionFunc = func_80A7134C;
    }
    func_80034F54(globalCtx, this->unk_21C, this->unk_23C, 16);
}

void func_80A7134C(EnHy* this, GlobalContext* globalCtx) {
    s16 sp36;
    f32 sp30;

    if ((this->skelAnime.animCurrentSeg == &D_06002160) && (this->unk_1E8.unk_00 != 0)) {
        func_80034EC0(&this->skelAnime, D_80A72050, 8);
    }

    if ((this->skelAnime.animCurrentSeg == &D_0600265C) && (this->unk_1E8.unk_00 == 0)) {
        func_80034EC0(&this->skelAnime, D_80A72050, 7);
    }

    this->actor.speedXZ = 0.4f;
    sp30 = Path_OrientAndGetDistSq(&this->actor, this->unk_210, this->unk_214, &sp36);
    Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, sp36, 0xA, 0x3E8, 1);
    this->actor.shape.rot = this->actor.posRot.rot;
    if (!(sp30 <= 0.0f) && !(sp30 >= 1000.0f)) {
        if (this->unk_195 == 0) {
            this->unk_214++;
            if ((this->unk_210->count - 1) < this->unk_214) {
                this->unk_195 = 1;
                this->unk_214 = this->unk_210->count - 2;
            }
        } else {
            this->unk_214--;
            if (this->unk_214 < 0) {
                this->unk_195 = 0;
                this->unk_214 = 1;
            }
        }
    }
}

void func_80A714C4(EnHy* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actionFunc = func_80A71530;
    } else {
        func_8002F434(&this->actor, globalCtx, this->unk_260, this->actor.xzDistFromLink + 1.0f,
                      fabsf(this->actor.yDistFromLink) + 1.0f);
    }
}

void func_80A71530(EnHy* this, GlobalContext* globalCtx) {
    if ((func_8010BDBC(&globalCtx->msgCtx) == 6) && (func_80106BC8(globalCtx) != 0)) {
        switch (this->unk_260) {
            case 0x3E:
                gSaveContext.dogParams = 0;
                gSaveContext.dogIsLost = 0;
                gSaveContext.infTable[25] |= 2;
                break;

            case 0x4D:
                Rupees_ChangeBy(5);
                gSaveContext.dogParams = 0;
                gSaveContext.dogIsLost = 0;
                break;
        }
        this->actionFunc = func_80A7127C;
    }
}

void EnHy_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHy* this = THIS;

    if (this->actionFunc != func_80A70E34) {
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_199].segment);
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        func_80A705A4(this);
        if (this->unk_1E8.unk_00 == 0) {
            Actor_MoveForward(&this->actor);
        }
        func_8002E4B4(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    }
    this->actionFunc(this, globalCtx);
    func_80A70978(this, globalCtx);
    func_80A70734(this, globalCtx);
}

#ifdef NON_MATCHING
// Hacked up via permuter to try and match
// currently only missing a stack var
// without the hacks it's pretty bad,
// a lot caused by the reused 0x80000000 for PHYSICAL_TO_VIRTUAL()
s32 func_80A716B8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnHy* this = THIS;
    s32 new_var;
    Vec3s sp48;
    u8 idx;
    s32* ptr;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_hy.c", 2170);

    if (limbIndex == 15) {

        gSPSegment(oGfxCtx->polyOpa.p++, 0x06, globalCtx->objectCtx.status[this->unk_196].segment);
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_196].segment);
        new_var = 0x80000000;
        idx = D_80A722D8[this->actor.params & 0x7F].unk_0;
        *dList = D_80A71F50[idx].unk_4;

        ptr = D_80A71F50[idx].unk_8;
        if (ptr != NULL) {
            void* val = ptr[this->unk_218];
            gSPSegment(oGfxCtx->polyOpa.p++, 0x0A,
                       (void*)((((u32)gSegments[(((unsigned int)val) << 4) >> 28]) + new_var) +
                               (((unsigned int)val) & 0x00ffffff)));
        }
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_198].segment);
    }

    if (limbIndex == 15) {
        Matrix_Translate(1400.0f, 0.0f, 0.0f, 1);
        sp48 = this->unk_1E8.unk_08;
        Matrix_RotateX((sp48.y / 32768.0f) * M_PI, 1);
        Matrix_RotateZ((sp48.x / 32768.0f) * M_PI, 1);
        Matrix_Translate(-1400.0f, 0.0f, 0.0f, 1);
    }

    if (limbIndex == 8) {
        sp48 = this->unk_1E8.unk_0E;
        Matrix_RotateX((-sp48.y / 32768.0f) * M_PI, 1);
        Matrix_RotateZ((sp48.x / 32768.0f) * M_PI, 1);
    }

    if ((limbIndex == 8) || (limbIndex == 9) || (limbIndex == 12)) {
        rot->y += Math_Sins(this->unk_21C[limbIndex]) * 200.0f;
        rot->z += Math_Coss(this->unk_23C[limbIndex]) * 200.0f;
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_hy.c", 2228);
    if (1) {};

    return 0;
}
#else
s32 func_80A716B8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Hy/func_80A716B8.s")
#endif

void func_80A71A64(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnHy* this = THIS;
    s32 pad;
    Vec3f sp3C = { 400.0f, 0.0f, 0.0f };

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_hy.c", 2255);

    if (limbIndex == 7) {
        gSPSegment(oGfxCtx->polyOpa.p++, 0x06, globalCtx->objectCtx.status[this->unk_197].segment);
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_197].segment);
    }

    if (((this->actor.params & 0x7F) == 3) && (limbIndex == 8)) {
        gSPDisplayList(oGfxCtx->polyOpa.p++, D_06005BC8);
    }

    if (limbIndex == 15) {
        Matrix_MultVec3f(&sp3C, &this->actor.posRot2.pos);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_hy.c", 2281);
}

Gfx* func_80A71BBC(GraphicsContext* gfxCtx, u8 r, u8 g, u8 b, u8 a) {
    Gfx* dList = Graph_Alloc(gfxCtx, sizeof(Gfx) * 2);

    gDPSetEnvColor(dList, r, g, b, a);
    gSPEndDisplayList(dList + 1);

    return dList;
}

void EnHy_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHy* this = THIS;
    Color_RGBA8_n sp60;
    Color_RGBA8_n sp5C;
    Color_RGBA8_n sp58;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_hy.c", 2318);

    if (this->actionFunc != func_80A70E34) {
        func_80093D18(globalCtx->state.gfxCtx);
        Matrix_Translate(this->unk_264.x, this->unk_264.y, this->unk_264.z, 1);
        sp60 = D_80A722D8[this->actor.params & 0x7F].unk_2;
        sp5C = D_80A722D8[this->actor.params & 0x7F].unk_7;
        // -2
        switch (this->actor.params & 0x7F) {
            case 2:
            case 3:
            case 4:
            case 5:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 19:
            case 20:
                gSPSegment(oGfxCtx->polyOpa.p++, 0x08,
                           func_80A71BBC(globalCtx->state.gfxCtx, sp60.r, sp60.g, sp60.b, sp60.a));
                gSPSegment(oGfxCtx->polyOpa.p++, 0x09,
                           func_80A71BBC(globalCtx->state.gfxCtx, sp5C.r, sp5C.g, sp5C.b, sp5C.a));

                if (((this->actor.params & 0x7F) == 8) || ((this->actor.params & 0x7F) == 11)) {
                    if ((this->actor.params & 0x7F) == 8) {
                        sp58 = sp60;
                    }

                    if ((this->actor.params & 0x7F) == 11) {
                        sp58.r = sp58.g = sp58.b = 255;
                        sp58.a = 0;
                    }

                    gSPSegment(oGfxCtx->polyOpa.p++, 0x0A,
                               func_80A71BBC(globalCtx->state.gfxCtx, sp58.r, sp58.g, sp58.b, sp58.a));
                }

            case 6:
            case 18:
                break;
        }
        SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                         func_80A716B8, func_80A71A64, &this->actor);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_hy.c", 2388);
}
