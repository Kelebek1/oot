/*
 * File: z_en_horse.c
 * Overlay: ovl_En_Horse
 * Description: Epona
 */

#include "overlays/actors/ovl_En_In/z_en_in.h"
#include "z_en_horse.h"

#define FLAGS 0x00000010

#define THIS ((EnHorse*)thisx)

// Copied from Glitch's repo, maybe wrong
typedef struct {
    /* 0x00 */ char unk[0x4];
    /* 0x04 */ MtxF mf;
} HorseStruct;
void func_800A6408(HorseStruct* horseStruct, s32 arg1, Vec3f* colliderSphereCenter, Vec3f* dest);

void EnHorse_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A5F5F8(EnHorse* this, s32 arg1, f32 arg2, f32 arg3);
void func_80A5F380(EnHorse* this, s32 arg1, f32 arg2);
void func_80A63148(EnHorsePadXY* pad, f32* arg1, s16* arg2);
s32 func_80A65014(EnHorse* this, GlobalContext* globalCtx);
void func_80A5F044(EnHorse* this);
void func_80A5FCAC(EnHorse* this);
void func_80A6140C(EnHorse* this);
void func_80A61A04(EnHorse* this);
void func_80A5F3A8(EnHorse* this);
void func_80A5F3DC(EnHorse* this);
void func_80A5FDD4(EnHorse* this);
void func_80A61440(EnHorse* this);
void func_80A5CF28(EnHorse* this);
void func_80A5CF64(EnHorse* this);
void func_80A5DCB0(EnHorse* this);
void func_80A5E588(EnHorse* this);
void func_80A5D3C0(EnHorse* this);
void func_80A5D628(EnHorse* this);
void func_80A5D1A0(EnHorse* this);
void func_80A5E5AC(EnHorse* this);
void func_80A5D678(EnHorse* this);
void func_80A5D1C4(EnHorse* this);
void func_80A5D69C(EnHorse* this);
void func_80A5DA68(EnHorse* this);
void func_80A5DC8C(EnHorse* this);

void func_80A61058(EnHorse* this, GlobalContext* globalCtx);
void func_80A624AC(EnHorse* this, GlobalContext* globalCtx);
void func_80A5EA1C(EnHorse* this, GlobalContext* globalCtx);
void func_80A5ED3C(EnHorse* this, GlobalContext* globalCtx);
void func_80A5F760(EnHorse* this, GlobalContext* globalCtx);
void func_80A5C97C(EnHorse* this, GlobalContext* globalCtx);
void func_80A5F08C(EnHorse* this, GlobalContext* globalCtx);
void func_80A5F414(EnHorse* this, GlobalContext* globalCtx);
void func_80A5F890(EnHorse* this, GlobalContext* globalCtx);
void func_80A600E8(EnHorse* this, GlobalContext* globalCtx);
void func_80A5D0A0(EnHorse* this, GlobalContext* globalCtx);
void func_80A5D2C0(EnHorse* this, GlobalContext* globalCtx);
void func_80A5D468(EnHorse* this, GlobalContext* globalCtx);
void func_80A5D79C(EnHorse* this, GlobalContext* globalCtx);
void func_80A5DB58(EnHorse* this, GlobalContext* globalCtx);
void func_80A5DE38(EnHorse* this, GlobalContext* globalCtx);
void func_80A5E2A8(EnHorse* this, GlobalContext* globalCtx);
void func_80A5E12C(EnHorse* this, GlobalContext* globalCtx);
void func_80A5E39C(EnHorse* this, GlobalContext* globalCtx);
void func_80A5E650(EnHorse* this, GlobalContext* globalCtx);
void func_80A5EB54(EnHorse* this, GlobalContext* globalCtx);
void func_80A5EE80(EnHorse* this, GlobalContext* globalCtx);
void func_80A627A4(EnHorse* this, GlobalContext* globalCtx);
void func_80A610C8(EnHorse* this, GlobalContext* globalCtx);
void func_80A61778(EnHorse* this, GlobalContext* globalCtx);
void func_80A61A28(EnHorse* this, GlobalContext* globalCtx);
void func_80A60470(EnHorse* this, GlobalContext* globalCtx);

void func_80A60294(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80A605A4(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80A60838(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80A60AFC(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80A60D28(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80A60300(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80A605E0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80A60954(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80A60BDC(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);
void func_80A60EB0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action);

extern UNK_TYPE D_06006530;
extern UNK_TYPE D_02002AC0;
extern UNK_TYPE D_02000230;

AnimationHeader* D_80A65E10[] = {
    0x06006D50, 0x06005584, 0x06004DEC, 0x06003CEC, 0x060075F0, 0x060032B0, 0x06001E2C, 0x06002470, 0x06002C38,
};

AnimationHeader* D_80A65E34[] = {
    0x06009FC4, 0x0600A6B4, 0x0600901C, 0x060085E0, 0x0600AF60, 0x06007B54, 0x0600506C, 0x06005684, 0x06005E20,
};

AnimationHeader** D_80A65E58[] = { D_80A65E10, D_80A65E34 };

f32 D_80A65E60[] = {
    0.6666666865348816f, 0.6666666865348816f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.666666686535f, 0.666666686535f,
};

SkeletonHeader* D_80A65E84[] = { 0x06009D74, 0x06004A24 };

const ActorInit En_Horse_InitVars = {
    ACTOR_EN_HORSE,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_HORSE,
    sizeof(EnHorse),
    (ActorFunc)EnHorse_Init,
    (ActorFunc)EnHorse_Destroy,
    (ActorFunc)EnHorse_Update,
    (ActorFunc)EnHorse_Draw,
};

// sCylinderInit1
ColliderCylinderInit D_80A65EAC = {
    { COLTYPE_UNK10, 0x08, 0x00, 0x39, 0x12, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000400, 0x00, 0x04 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x19, 0x00, 0x01 },
    { 20, 70, 0, { 0, 0, 0 } },
};

// sCylinderInit2
ColliderCylinderInit D_80A65ED8 = {
    { COLTYPE_UNK10, 0x00, 0x00, 0x39, 0x12, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 20, 70, 0, { 0, 0, 0 } },
};

ColliderJntSphItemInit sJntSph3ItemsInit[1] = {
    {
        { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x0001F824, 0x00, 0x00 }, 0x00, 0x79, 0x01 },
        { 13, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// sJntSphInit3
ColliderJntSphInit D_80A65F28 = {
    { COLTYPE_UNK10, 0x00, 0x09, 0x39, 0x12, COLSHAPE_JNTSPH },
    1,
    sJntSph3ItemsInit,
};

CollisionCheckInfoInit D_80A65F38 = {
    0xA,
    0x0023,
    0x0064,
    0xFE,
};

typedef struct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
} EnHorseStruct2; // size = 0xA

EnHorseStruct2 D_80A65F40[] = {
    { 0x0051, 0x0010, 0x0000, 0x053D, 0x0000 }, { 0x0051, 0xFAEF, 0x0000, 0x05B3, 0x0000 },
    { 0x0051, 0xEAD8, 0xFED4, 0x0510, 0x0000 }, { 0x0051, 0xEDC5, 0xFED4, 0x0E24, 0x0000 },
    { 0x0051, 0xF103, 0x0051, 0x15A1, 0x0000 }, { 0x0051, 0xEC1B, 0xFF1E, 0x1A05, 0x0000 },
    { 0x0051, 0xE644, 0xFFB1, 0x13BD, 0x0000 }, { 0x0051, 0xE460, 0xFE0C, 0x1D72, 0x0000 },
    { 0x0051, 0xE805, 0xFE0C, 0x22CE, 0x0000 }, { 0x0051, 0xDECF, 0xFED4, 0x1E7A, 0x0000 },
    { 0x0051, 0xEA97, 0xFE0D, 0x2F5F, 0x0000 }, { 0x0051, 0xED38, 0xFD44, 0x350F, 0x0000 },
    { 0x0051, 0xF2A8, 0xFE16, 0x2F3C, 0x0000 }, { 0x0051, 0xF49D, 0x0064, 0x2093, 0x0000 },
    { 0x0051, 0xF71B, 0xFE0C, 0x33BF, 0x0000 }, { 0x0051, 0xFBFE, 0xFE0C, 0x2F45, 0x0000 },
    { 0x0051, 0x0593, 0xFE0C, 0x341D, 0x0000 }, { 0x0051, 0xFF38, 0xFE1A, 0x27DD, 0x0000 },
    { 0x0051, 0xFA43, 0x0064, 0x1D48, 0x0000 }, { 0x0051, 0xFC1D, 0x00A8, 0x1614, 0x0000 },
    { 0x0051, 0x0792, 0x0059, 0x1858, 0x0000 }, { 0x0051, 0x056B, 0xFF97, 0x23F6, 0x0000 },
    { 0x0051, 0x0623, 0xFF21, 0x1E15, 0x0000 }, { 0x0051, 0x0F35, 0xFF87, 0x1B9C, 0x0000 },
    { 0x0051, 0x0C6B, 0x0175, 0x1465, 0x0000 }, { 0x0051, 0x1246, 0xFFEC, 0x0F1D, 0x0000 },
    { 0x0051, 0x0D84, 0x00F6, 0x106F, 0x0000 }, { 0x0051, 0x0E66, 0x0080, 0x093E, 0x0000 },
    { 0x0051, 0x06FF, 0x0012, 0x0098, 0x0000 }, { 0x0051, 0x0E53, 0xFFF0, 0x0577, 0x0000 },
    { 0x0051, 0x0723, 0xFFF1, 0x03D7, 0x0000 }, { 0x0051, 0x0626, 0x018F, 0x10DE, 0x0000 },
    { 0x0051, 0x02CC, 0x005F, 0x0D3F, 0x0000 }, { 0x0051, 0xFB5B, 0xFFD7, 0x1283, 0x0000 },
    { 0x0051, 0xF848, 0xFF55, 0x104C, 0x0000 }, { 0x0051, 0x0522, 0x0187, 0x1621, 0x0000 },
    { 0x0051, 0x0070, 0x0000, 0x07A7, 0x0000 }, { 0x0051, 0xF43D, 0xFF91, 0x24B5, 0x0000 },
    { 0x0051, 0xE9D6, 0xFEF2, 0x2189, 0x0000 }, { 0x0051, 0xDD63, 0xFED4, 0x1E9C, 0x0000 },
    { 0x0051, 0xE858, 0xFE0C, 0x1E82, 0x0000 }, { 0x0051, 0xE376, 0xFE0C, 0x176A, 0x0000 },
    { 0x0051, 0xE377, 0xFE0C, 0x1DB5, 0x0000 }, { 0x0051, 0xE2F1, 0xFED4, 0x1DB0, 0x0000 },
    { 0x0051, 0xE2D8, 0xFED4, 0x187C, 0x0000 }, { 0x0051, 0xE070, 0xFED4, 0x1D81, 0x0000 },
    { 0x0051, 0xE065, 0xFED4, 0x1CB5, 0x0000 }, { 0x0051, 0xDDAF, 0xFED4, 0x1CD7, 0x0000 },
    { 0x0051, 0xDDD7, 0xFED4, 0x1D54, 0x0000 }, { 0x0051, 0xDDB7, 0xFED4, 0x1E6C, 0x0000 },
    { 0x0051, 0xE090, 0xFED5, 0x1E3A, 0x0000 }, { 0x0051, 0xE353, 0xFF48, 0x1E32, 0x0000 },
    { 0x0051, 0xE6F6, 0xFEE0, 0x1E90, 0x0000 }, { 0x0051, 0xE74A, 0xFEDE, 0x200D, 0x0000 },
    { 0x0051, 0xE66E, 0xFEDC, 0x20D0, 0x0000 }, { 0x0051, 0xE293, 0xFF4C, 0x210B, 0x0000 },
    { 0x0051, 0xE0A8, 0xFED9, 0x1EDF, 0x0000 }, { 0x0051, 0xE072, 0xFECC, 0x1F3A, 0x0000 },
    { 0x0051, 0xDB2F, 0xFEE1, 0x1E10, 0x0000 }, { 0x0051, 0xDB96, 0xFEDC, 0x1D99, 0x0000 },
    { 0x0051, 0xDA7E, 0xFF39, 0x1BF8, 0x0000 }, { 0x0051, 0xDBA5, 0xFED4, 0x1E4E, 0x0000 },
    { 0x0051, 0xDBF2, 0xFED4, 0x1DDA, 0x0000 }, { 0x0051, 0xE27C, 0xFE0D, 0x21F7, 0x0000 },
    { 0x0051, 0xE6DA, 0xFE0C, 0x219E, 0x0000 }, { 0x0051, 0xE842, 0xFE0C, 0x2042, 0x0000 },
    { 0x0051, 0xE7A7, 0xFE0C, 0x1DBD, 0x0000 }, { 0x0051, 0xEC55, 0xFF33, 0x1E86, 0x0000 },
    { 0x0051, 0xE8AD, 0xFE0C, 0x2135, 0x0000 }, { 0x0051, 0xE9A4, 0xFE0E, 0x278B, 0x0000 },
    { 0x0051, 0xEC1A, 0xFE78, 0x2B62, 0x0000 }, { 0x0051, 0xEC0F, 0xFE77, 0x2C30, 0x0000 },
    { 0x0051, 0xEE83, 0xFEC6, 0x2B7C, 0x0000 }, { 0x0051, 0xF0E5, 0xFE84, 0x2C9B, 0x0000 },
    { 0x0051, 0xF478, 0xFE0C, 0x2EA8, 0x0000 }, { 0x0051, 0xF4C9, 0xFE18, 0x2DDF, 0x0000 },
    { 0x0051, 0xF10B, 0xFE8C, 0x2C3F, 0x0000 }, { 0x0051, 0xEEA9, 0xFEDB, 0x2AED, 0x0000 },
    { 0x0051, 0xEC6A, 0xFE83, 0x2B4E, 0x0000 }, { 0x0051, 0xEC07, 0xFF44, 0x2AD8, 0x0000 },
    { 0x0051, 0xEB6B, 0xFF44, 0x2B94, 0x0000 }, { 0x0051, 0xEA24, 0xFF4E, 0x26F4, 0x0000 },
    { 0x0051, 0xE957, 0xFEE0, 0x2146, 0x0000 }, { 0x0051, 0xECD2, 0xFF4E, 0x1EFB, 0x0000 },
    { 0x0051, 0xF1FE, 0x0049, 0x1FCC, 0x0000 }, { 0x0051, 0xEE79, 0xFF96, 0x2492, 0x0000 },
    { 0x0051, 0xEF0D, 0xFF90, 0x190C, 0x0000 }, { 0x0051, 0xF2A7, 0x0069, 0x2002, 0x0000 },
    { 0x0051, 0xEE67, 0xFFEC, 0x19D0, 0x0000 }, { 0x0051, 0xEC52, 0xFF39, 0x19CB, 0x0000 },
    { 0x0051, 0xEE7F, 0x0001, 0x1930, 0x0000 }, { 0x0051, 0xEC58, 0xFF58, 0x1912, 0x0000 },
    { 0x0051, 0xEB78, 0xFD44, 0x37F9, 0x0000 }, { 0x0051, 0xE98B, 0xFCCC, 0x3C14, 0x0000 },
    { 0x0051, 0xF3CE, 0xFD44, 0x3528, 0x0000 }, { 0x0051, 0xF152, 0xFDF3, 0x33AC, 0x0000 },
    { 0x0051, 0xF1AA, 0xFE0C, 0x3343, 0x0000 }, { 0x0051, 0xF494, 0xFE0C, 0x34D6, 0x0000 },
    { 0x0051, 0x056D, 0xFF8D, 0x249A, 0x0000 }, { 0x0051, 0x0224, 0xFF8C, 0x22B9, 0x0000 },
    { 0x0051, 0xFF96, 0xFF95, 0x2152, 0x0000 }, { 0x0051, 0xF9B8, 0x0055, 0x1DDE, 0x0000 },
    { 0x0051, 0xEB4C, 0xFD44, 0x35CC, 0x0000 }, { 0x0051, 0xEC06, 0xFD44, 0x3458, 0x0000 },
    { 0x0051, 0xEE2F, 0xFD44, 0x3584, 0x0000 }, { 0x0051, 0xED66, 0xFD44, 0x3704, 0x0000 },
    { 0x0051, 0xF476, 0x0064, 0x2018, 0x0000 }, { 0x0051, 0x05B4, 0xFF98, 0x241E, 0x0000 },
    { 0x0051, 0x0275, 0xFF97, 0x2257, 0x0000 }, { 0x0051, 0xFFF6, 0xFFA6, 0x20E3, 0x0000 },
    { 0x0051, 0xFA4A, 0x0064, 0x1D50, 0x0000 }, { 0x0051, 0xF436, 0xFE0C, 0x30CD, 0x0000 },
    { 0x0051, 0xF44E, 0xFEC9, 0x285B, 0x0000 }, { 0x0051, 0xF05A, 0xFD44, 0x3748, 0x0000 },
    { 0x0051, 0xEF0B, 0xFE0C, 0x31C7, 0x0000 }, { 0x0051, 0xE909, 0xFE0F, 0x1A8F, 0x0000 },
    { 0x0051, 0x0016, 0xFE27, 0x2777, 0x0000 }, { 0x0051, 0xFA93, 0xFF40, 0x22AA, 0x0000 },
    { 0x0051, 0xFFFC, 0x005C, 0x1AD2, 0x0000 }, { 0x0051, 0x01E3, 0x0068, 0x19ED, 0x0000 },
    { 0x0051, 0x062C, 0x00B7, 0x1763, 0x0000 }, { 0x0051, 0x060C, 0x0134, 0x13D5, 0x0000 },
    { 0x0051, 0x05E7, 0x018F, 0x10AB, 0x0000 }, { 0x0051, 0x054E, 0x0181, 0x10AF, 0x0000 },
    { 0x0051, 0x0563, 0x018B, 0x13C7, 0x0000 }, { 0x0051, 0x0550, 0x018A, 0x16EE, 0x0000 },
    { 0x0051, 0x032D, 0x011B, 0x1832, 0x0000 }, { 0x0051, 0xFFC7, 0x0065, 0x1A57, 0x0000 },
    { 0x0051, 0x005B, 0x0145, 0x1417, 0x0000 }, { 0x0051, 0x0591, 0xFF2A, 0x1DEB, 0x0000 },
    { 0x0051, 0x0D9F, 0xFFED, 0x0370, 0x0000 }, { 0x0051, 0x0B75, 0x0098, 0x082E, 0x0000 },
    { 0x0051, 0x0B48, 0xFF6F, 0x1ACE, 0x0000 }, { 0x0051, 0x05E7, 0x0043, 0x1947, 0x0000 },
    { 0x0051, 0x0FD3, 0xFFD1, 0x06BA, 0x0000 }, { 0x0051, 0xE359, 0xFE0C, 0x21B3, 0x0000 },
    { 0x0051, 0xE1D0, 0xFE32, 0x2132, 0x0000 }, { 0x0051, 0xE191, 0xFE42, 0x2280, 0x0000 },
    { 0x0051, 0xF49D, 0xFE4D, 0x2C46, 0x0000 }, { 0x0051, 0x00A5, 0xFEEA, 0x0D18, 0x0000 },
    { 0x0057, 0xF7C3, 0xFC8E, 0x06BC, 0x0000 }, { 0x0057, 0xFEB8, 0xFB2A, 0x0A91, 0x0000 },
    { 0x0057, 0xF3EC, 0xFBF7, 0x0DC7, 0x0000 }, { 0x005A, 0x0A7F, 0xFEF3, 0x02F1, 0x0000 },
    { 0x005A, 0x0812, 0xFF7C, 0x013D, 0x0000 }, { 0x005A, 0x020B, 0xFFF8, 0x027B, 0x0000 },
    { 0x005A, 0x022E, 0x0024, 0xFEBD, 0x0000 }, { 0x005A, 0x0267, 0x0033, 0xFCB9, 0x0000 },
    { 0x005A, 0xFD9A, 0x0020, 0x001D, 0x0000 }, { 0x005A, 0xFD81, 0xFFFD, 0x0229, 0x0000 },
    { 0x005A, 0xFDE4, 0x000A, 0xFC87, 0x0000 }, { 0x005A, 0xF97E, 0x003A, 0x017A, 0x0000 },
    { 0x005A, 0xF41C, 0x00D2, 0xFD78, 0x0000 }, { 0x005D, 0xFD5A, 0x0015, 0xFD91, 0x0000 },
    { 0x005D, 0x0095, 0x014D, 0xF63D, 0x0000 }, { 0x005D, 0x01F3, 0x0245, 0xFDDD, 0x0000 },
    { 0x005D, 0x0C73, 0x0585, 0xF141, 0x0000 }, { 0x005D, 0x0C7E, 0x0585, 0x0133, 0x0000 },
    { 0x005D, 0x0D34, 0x0585, 0xFB50, 0x0000 }, { 0x005D, 0xFC3A, 0x0001, 0xFFC8, 0x0000 },
    { 0x005D, 0xFC3A, 0x0018, 0xFD07, 0x0000 }, { 0x005D, 0xFD4A, 0x00AE, 0xF4FC, 0x0000 },
    { 0x0063, 0x040F, 0x0000, 0x0803, 0x0000 }, { 0x0063, 0xFA5D, 0x0000, 0x0595, 0x0000 },
    { 0x0063, 0x0358, 0x0000, 0xFC6A, 0x0000 }, { 0x0063, 0x0372, 0x0000, 0xF730, 0x0000 },
    { 0x0063, 0xFC15, 0x0000, 0xFD0D, 0x0000 }, { 0x0063, 0xF732, 0x0000, 0xFD8B, 0x0000 },
    { 0x0063, 0x038B, 0x0000, 0xF6E0, 0x0000 },
};

typedef struct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} EnHorseStruct1; // size = 0x14

EnHorseStruct1 D_80A665DC[] = {
    { 0xFF3D, 0xFFD8, 0x00E1, 0x0078, 0x0168, 0xC000, 0x07D0, 0xFEF2, 0xFFCC, 0xFF8B },
    { 0xFF3D, 0xFFD8, 0xFF10, 0xFF88, 0xFE98, 0x4000, 0x07D0, 0x010E, 0xFFCC, 0xFF8B },
};

typedef struct {
    Vec3s unk_0;
    s16 unk_6;
    s16 unk_8;
} EnHorseStruct4; // size = 0xA

EnHorseStruct4 D_80A66604[] = {
    { 0x0420, 0x0001, 0xF9FC, 0x000B, 0x2A8D }, { 0x0639, 0x0001, 0xFC27, 0x000A, 0xFC27 },
    { 0x066D, 0x0001, 0xFF23, 0x000B, 0xE891 }, { 0x03D9, 0x0001, 0x0193, 0x000A, 0xBB9C },
    { 0xFC01, 0x0001, 0x0162, 0x000B, 0xA37D }, { 0xF971, 0x0001, 0xFF2B, 0x000A, 0x889C },
    { 0xF9F0, 0x0001, 0xFC10, 0x000B, 0x638D }, { 0xFC4D, 0xFFFF, 0xF9BC, 0x000A, 0x4002 },
};

typedef struct {
    s32 count;
    EnHorseStruct4* data;
} EnHorseStruct3; // size = 0x8

EnHorseStruct3 D_80A66654 = { 0x00000008, D_80A66604 };

s32 D_80A6665C[] = {
    0x00000000,
    0x00000010,
};

// sInitChain
InitChainEntry D_80A66664[] = {
    ICHAIN_F32(uncullZoneScale, 600, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

u8 D_80A6666C[] = {
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
};

s32 D_80A66678[] = {
    0x00000001, 0x00000003, 0x00000000, 0x00000003, 0x00000001, 0x00000000,
};

s16 D_80A66690[] = {
    0x0007, 0x0006, 0x0002, 0x0002, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000,
};

EnHorseFuncs1 D_80A666A4[] = {
    NULL, func_80A60294, func_80A605A4, func_80A60838, func_80A60AFC, func_80A60D28,
};

EnHorseFuncs1 D_80A666BC[] = {
    NULL, func_80A60300, func_80A605E0, func_80A60954, func_80A60BDC, func_80A60EB0,
};

typedef struct {
    s32 unk_0;
    s32 unk_4;
} EnHorseStruct5; // size = 0x8

EnHorseStruct5 D_80A666D4[] = {
    { 0x00000024, 0x00000001 }, { 0x00000025, 0x00000002 }, { 0x00000026, 0x00000003 },
    { 0x00000040, 0x00000004 }, { 0x00000041, 0x00000005 },
};

EnHorseStruct4 D_80A666FC[] = {
    { 0x0E10, 0x0585, 0xEC41, 0x000B, 0x8001 }, { 0x0D20, 0x0585, 0xEB9C, 0x0005, 0xC000 },
    { 0x0C1C, 0x0585, 0xECDC, 0x0005, 0x0000 }, { 0x0E10, 0x0585, 0xEFFC, 0x000B, 0x0000 },
    { 0x0E10, 0x0585, 0x0168, 0x000B, 0x0000 },
};

EnHorseStruct3 D_80A66730 = { 0x00000005, D_80A666FC };

EnHorseActionFunc D_80A66738[] = {
    func_80A5C97C, func_80A5F08C, func_80A5F414, func_80A5F890, func_80A600E8, func_80A5D0A0, func_80A5D2C0,
    func_80A5D468, func_80A5D79C, func_80A5DB58, func_80A5DE38, func_80A5E12C, func_80A5E39C, func_80A5E650,
    func_80A5EB54, func_80A5EE80, func_80A627A4, func_80A610C8, func_80A61778, func_80A61A28,
};

Vec3f D_80A66788 = { 0.0f, 0.0f, 0.0f };
Vec3f D_80A66794 = { 0.0f, 1.0f, 0.0f };
Vec3f D_80A667A0 = { 0.0f, 0.0f, 0.0f };
Vec3f D_80A667AC = { 5.0f, -4.0f, 5.0f };
Vec3f D_80A667B8 = { 600.0f, -1670.0f, 0.0f };
Vec3f D_80A667C4 = { 0.0f, 0.0f, 0.0f };
Vec3f D_80A667D0 = { 0.0f, -1.0f, 0.0f };

static s32 UNUSED_DATA[] = { 0x00000000, 0x00000003, 0x00000007, 0x0000000E };

UNK_TYPE D_80A667EC[] = { 0x06009F80, 0x0600A180, 0x0600A380 };
u8 D_80A667F8[] = { 0x00, 0x01, 0x02, 0x01 };

s32 func_80A5B2F0(EnHorse* this, GlobalContext* globalCtx) {
    s32 i;
    f32 tmp;
    f32 tmp2;

    if (globalCtx->sceneNum != SCENE_SPOT09) {
        return 0;
    }

    if (this->actor.speedXZ < 12.8f) {
        return 0;
    }

    if ((gSaveContext.eventChkInf[9] & 0xF) == 0xF) {
        return 0;
    }

    for (i = 0; i < 2; i++) {
        tmp2 = D_80A665DC[i].unk_04;
        tmp = (tmp2 + D_80A665DC[i].unk_06) + D_80A665DC[i].unk_08;
        if (tmp < tmp2) {
            f32 oldTmp = tmp2;
            tmp2 = tmp;
            tmp = oldTmp;
        }

        if ((D_80A665DC[i].unk_00 < this->actor.posRot.pos.z) && (this->actor.posRot.pos.z < D_80A665DC[i].unk_02) &&
            (tmp2 < this->actor.posRot.pos.x) && (this->actor.posRot.pos.x < tmp) &&
            ((D_80A665DC[i].unk_0A - D_80A665DC[i].unk_0C) < this->actor.posRot.rot.y) &&
            (this->actor.posRot.rot.y < (D_80A665DC[i].unk_0A + D_80A665DC[i].unk_0C))) {
            return 1;
        }
    }
    return 0;
}

s32 func_80A5B450(EnHorse* this, GlobalContext* globalCtx) {
    s32 i;
    f32 tmp;
    f32 tmp2;

    if (this->actor.speedXZ < 12.8f) {
        return 0;
    }

    for (i = 0; i < 2; i++) {
        tmp2 = D_80A665DC[i].unk_04;
        tmp = tmp2 + D_80A665DC[i].unk_06;
        if (tmp < tmp2) {
            f32 oldTmp = tmp2;
            tmp2 = tmp;
            tmp = oldTmp;
        }

        if ((D_80A665DC[i].unk_00 < this->actor.posRot.pos.z) && (this->actor.posRot.pos.z < D_80A665DC[i].unk_02) &&
            (tmp2 < this->actor.posRot.pos.x) && (this->actor.posRot.pos.x < tmp)) {
            if (((D_80A665DC[i].unk_0A - D_80A665DC[i].unk_0C) < this->actor.posRot.rot.y) &&
                (this->actor.posRot.rot.y < (D_80A665DC[i].unk_0A + D_80A665DC[i].unk_0C))) {
                this->unk_3AC = i;
                func_80A624AC(this, globalCtx);
                return 1;
            }
        }
    }
    return 0;
}

void func_80A5B590(EnHorseStruct4* arg0, s32 idx, Vec3f* dest) {
    dest->x = arg0[idx].unk_0.x;
    dest->y = arg0[idx].unk_0.y;
    dest->z = arg0[idx].unk_0.z;
}

void func_80A5B5E0(EnHorse* this, GlobalContext* globalCtx, Vec3f* arg2, s16 arg3) {
    func_8006DD9C(&this->actor, arg2, arg3);
}

void func_80A5B61C(EnHorse* this, GlobalContext* globalCtx, EnHorseStruct3* arg2) {
    Vec3f sp64;
    Vec3f sp58;
    s32 tmp;
    f32 ret;
    s16 sp4E;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    func_80A5B590(arg2->data, this->unk_204, &sp64);
    Math3D_RotateXZPlane(&sp64, arg2->data[this->unk_204].unk_8, &sp48, &sp44, &sp40);
    if ((((this->actor.posRot.pos.x * sp48) + (sp44 * this->actor.posRot.pos.z)) + sp40) > 0.0f) {
        this->unk_204++;
        if (this->unk_204 >= arg2->count) {
            this->unk_204 = 0;
        }
    }

    func_80A5B590(arg2->data, this->unk_204, &sp64);
    tmp = this->unk_204 - 1;
    if (tmp < 0) {
        tmp = arg2->count - 1;
    }

    func_80A5B590(arg2->data, tmp, &sp58);
    Math3D_PointDistToLine2D(this->actor.posRot.pos.x, this->actor.posRot.pos.z, sp58.x, sp58.z, sp64.x, sp64.z, &sp3C);
    func_80A5B5E0(this, globalCtx, &sp64, 0x190);

    if (sp3C < 90000.0f) {
        if ((this->actor.xzDistFromLink < 130.0f) || ((this->collider3.list->body.ocFlags & 2) != 0)) {
            if (Math_Sins(this->actor.yawTowardsLink - this->actor.posRot.rot.y) > 0.0f) {
                this->actor.posRot.rot.y -= 0x118;
            } else {
                this->actor.posRot.rot.y += 0x118;
            }
        } else if (this->actor.xzDistFromLink < 300.0f) {
            if (Math_Sins(this->actor.yawTowardsLink - this->actor.posRot.rot.y) > 0.0f) {
                this->actor.posRot.rot.y += 0x118;
            } else {
                this->actor.posRot.rot.y -= 0x118;
            }
        }
        this->actor.shape.rot.y = this->actor.posRot.rot.y;
    }

    ret = func_8002DB8C(&this->actor, &PLAYER->actor);
    sp4E = func_8002DA78(&this->actor, &PLAYER->actor) - this->actor.posRot.rot.y;

    if ((ret <= 200.0f) || ((fabsf(Math_Sins(sp4E)) < 0.8f) && (Math_Coss(sp4E) > 0.0f))) {
        if (this->actor.speedXZ < this->unk_398) {
            this->actor.speedXZ += 0.47f;
        } else {
            this->actor.speedXZ -= 0.47f;
        }
        this->unk_394 |= 1;
    } else {
        if (this->actor.speedXZ < arg2->data[this->unk_204].unk_6) {
            this->actor.speedXZ += 0.4f;
        } else {
            this->actor.speedXZ -= 0.4f;
        }
        this->unk_394 &= ~1;
    }
}

void func_80A5B9C8(EnHorse* this) {
    if ((D_80A6665C[this->unk_218] < this->unk_214) && ((this->unk_218 != 0) || !(D_80A6665C[1] < this->unk_214))) {
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_WALK, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        this->unk_218++;
        if (this->unk_218 > 1) {
            this->unk_218 = 0;
        }
    }
}

void func_80A5BA84(EnHorse* this) {
    Audio_PlaySoundGeneral(NA_SE_EV_HORSE_RUN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
}

void func_80A5BACC(EnHorse* this) {
    Audio_PlaySoundGeneral(NA_SE_EV_HORSE_RUN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
}

f32 func_80A5BB14(EnHorse* this, GlobalContext* globalCtx) {
    f32 sp1C = 1.0f;

    if ((Math_Coss(this->actor.shape.rot.x) < 0.939262f) && (Math_Sins(this->actor.shape.rot.x) < 0.0f)) {
        sp1C = 0.7f;
    }

    return sp1C;
}

void func_80A5BB90(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, f32* arg3) {
    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->mf_11D60, arg1, arg2, arg3);
}

s32 func_80A5BBBC(GlobalContext* globalCtx, EnHorse* this, Vec3f* arg2) {
    Vec3f sp24;
    f32 sp20;
    f32 tmp;

    func_80A5BB90(globalCtx, arg2, &sp24, &sp20);
    if (fabsf(sp20) < 0.008f) {
        return 0;
    }

    tmp = Math3D_Vec3f_DistXYZ(arg2, &globalCtx->view.eye);
    return func_800314D4(globalCtx, &this->actor, &sp24, sp20) || (tmp < 100.0f);
}

void func_80A5BC68(EnHorse* this, GlobalContext* globalCtx) {
    if ((this->unk_210 == 0) &&
        (((this->unk_214 > 35.0f) && (this->unk_158 == 0)) || ((this->unk_214 > 28.0f) && (this->unk_158 == 1))) &&
        ((this->unk_1F0 & 0x1000) == 0)) {
        this->unk_1F0 |= 0x1000;
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_SANDDUST, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        return;
    }

    if ((this->unk_210 == 3) && (this->unk_214 > 25.0f) && ((this->unk_1F0 & 0x800) == 0)) {
        this->unk_1F0 |= 0x800;
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_LAND2, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
    }
}

s32 func_80A5BD94(EnHorse* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 i;
    f32 dist = 1.0e38f;
    f32 newDist;
    s32 ret = 0;
    Vec3f sp68;
    if (0) {};

    for (i = 0; i < 169; i++) {
        if (globalCtx->sceneNum == D_80A65F40[i].unk_00) {
            Player* player = PLAYER;
            if ((globalCtx->sceneNum != SCENE_SPOT20) ||
                (Flags_GetEventChkInf(0x18) &&
                 (((gSaveContext.eventInf[0] & 0xF) != 6) || Flags_GetEventChkInf(0x18))) ||
                ((D_80A65F40[i].unk_02 == 0x358) && (D_80A65F40[i].unk_04 == 0) && (D_80A65F40[i].unk_06 == -0x396)) ||
                ((D_80A65F40[i].unk_02 == -0x3EB) && (D_80A65F40[i].unk_04 == 0) && (D_80A65F40[i].unk_06 == -0x2F3))) {
                sp68.x = D_80A65F40[i].unk_02;
                sp68.y = D_80A65F40[i].unk_04;
                sp68.z = D_80A65F40[i].unk_06;
                newDist = Math3D_Vec3f_DistXYZ(&player->actor.posRot.pos, &sp68);
                if (!(dist < newDist) && (func_80A5BBBC(globalCtx, this, &sp68) == 0)) {
                    dist = newDist;
                    this->actor.posRot.pos.x = D_80A65F40[i].unk_02;
                    this->actor.posRot.pos.y = D_80A65F40[i].unk_04;
                    this->actor.posRot.pos.z = D_80A65F40[i].unk_06;
                    this->actor.pos4 = this->actor.posRot.pos;
                    this->actor.posRot.rot.y = D_80A65F40[i].unk_08;
                    this->actor.shape.rot.y = func_8002DA78(&this->actor, &PLAYER->actor);
                    ret = 1;
                    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->mf_11D60, &this->actor.posRot.pos,
                                                 &this->actor.projectedPos, &this->actor.projectedW);
                }
            }
        }
    }
    return ret;
}

void func_80A5BFD8(EnHorse* this, GlobalContext* globalCtx) {
    this->unk_380 = -1;
    this->unk_384 = 0;
}

void func_80A5BFEC(EnHorse* this, GlobalContext* globalCtx) {
    this->unk_388 = 0;
}

s32 func_80A5BFF8(EnHorse* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (((player->stateFlags1 & 1) != 0) || (func_8002DD78(PLAYER) == 1) || ((player->stateFlags1 & 0x100000) != 0) ||
        (((this->unk_1F0 & 0x80000) != 0) && (this->unk_388 == 0)) || (this->unk_14C == 0x12) ||
        ((player->actor.flags & 0x100) != 0) || (globalCtx->csCtx.state != 0)) {
        return 0;
    }

    return 1;
}

void func_80A5C0B4(EnHorse* this, GlobalContext* globalCtx) {
    this->unk_39C = 0;
    this->unk_3A0 = 0;
    this->unk_3A4 = 0;
}

void func_80A5C0C8(u16* arg0) {
    *arg0 = 0;
}

#ifdef NON_MATCHING
// globalCtx on the stack
void EnHorse_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHorse* this = THIS;

    AREG(6) = 0;
    Actor_ProcessInitChain(&this->actor, D_80A66664);
    func_80A5C0C8(&this->unk_3C8);
    DREG(53) = 0;
    this->unk_258 = this->actor.posRot.pos;
    this->unk_258.y += 70.0f;
    this->unk_150 = 0;
    this->unk_154 = 0;
    if (DREG(4) == 0) {
        DREG(4) = 0x46;
    }

    if ((this->actor.params & 0x8000) != 0) {
        s8 objIdx;
        s32 ret;

        this->actor.params &= ~0x8000;
        this->unk_158 = 1;
        objIdx = Object_GetIndex(&globalCtx->objectCtx, OBJECT_HNI);
        this->unk_15C = objIdx;
        if (objIdx < 0) {
            Actor_Kill(&this->actor);
            return;
        }

        do {
            ret = Object_IsLoaded(&globalCtx->objectCtx, this->unk_15C);
        } while (ret == 0);

        this->actor.objBankIndex = this->unk_15C;
        Actor_SetObjectDependency(globalCtx, &this->actor);
        this->unk_208 = 0xC;
    } else {
        this->unk_158 = 0;
        this->unk_208 = 0xE;
    }

    if (this->actor.params == 0x7FFF) {
        this->actor.params = 1;
    }

    if (globalCtx->sceneNum == SCENE_SOUKO) {
        this->unk_1F0 = 0x10000;
    } else if ((globalCtx->sceneNum == SCENE_SPOT12) && (this->unk_158 == 1)) {
        this->unk_1F0 = 0x50000;
    } else if (this->actor.params == 3) {
        this->unk_1F0 = 0xB0000;
    } else if (this->actor.params == 6) {
        this->unk_1F0 = 0xA0000;
        if (Flags_GetEventChkInf(0x18) || (DREG(1) != 0)) {
            this->unk_1F0 &= ~0x20000;
            this->unk_1F0 |= 0x4000000;
        } else if ((gSaveContext.eventInf[0] & 0x40) && (this->unk_158 == 1)) {
            this->unk_1F0 |= 0x300000;
        }
    } else if (this->actor.params == 1) {
        this->unk_1F0 = 0x80;
    } else {
        this->unk_1F0 = 0;
    }

    if ((globalCtx->sceneNum == SCENE_SPOT20) && ((gSaveContext.eventInf[0] & 0xF) == 6) &&
        !Flags_GetEventChkInf(0x18) && (DREG(1) == 0)) {
        this->unk_1F0 |= 0x2000000;
    }

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.gravity = -3.5f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFunc_Squiggly, 20.0f);
    this->unk_14C = 2;
    this->actor.speedXZ = 0.0f;
    Collider_InitCylinder(globalCtx, &this->collider1);
    Collider_SetCylinder(globalCtx, &this->collider1, &this->actor, &D_80A65EAC);
    Collider_InitCylinder(globalCtx, &this->collider2);
    Collider_SetCylinder(globalCtx, &this->collider2, &this->actor, &D_80A65ED8);
    Collider_InitJntSph(globalCtx, &this->collider3);
    Collider_SetJntSph(globalCtx, &this->collider3, &this->actor, &D_80A65F28, this->collider3Items);
    func_80061ED4(&this->actor.colChkInfo, DamageTable_Get(11), &D_80A65F38);
    this->actor.posRot2.pos = this->actor.posRot.pos;
    this->actor.posRot2.pos.y += 70.0f;
    this->unk_20C = 0;
    if ((globalCtx->sceneNum == SCENE_SPOT20) && (gSaveContext.sceneSetupIndex < 4)) {
        if (this->unk_158 == 1) {
            if ((this->actor.posRot.rot.z == 0) || (gSaveContext.nightFlag != 0)) {
                Actor_Kill(&this->actor);
                return;
            } else if (Flags_GetEventChkInf(0x18) != 0) {
                Actor_Kill(&this->actor);
                return;
            } else if (this->actor.posRot.rot.z != 5) {
                Actor_Kill(&this->actor);
                return;
            }
        } else if (!Flags_GetEventChkInf(0x18) && (DREG(1) == 0) && (gSaveContext.nightFlag != 0)) {
            Actor_Kill(&this->actor);
            return;
        }
    } else if (globalCtx->sceneNum == SCENE_MALON_STABLE) {
        if ((gSaveContext.nightFlag == 0) || Flags_GetEventChkInf(0x18) || (DREG(1) != 0) || (LINK_IS_CHILD)) {
            Actor_Kill(&this->actor);
            return;
        }
        this->unk_1F0 |= 0x10000;
    }

    func_800A663C(globalCtx, &this->unk_160, D_80A65E84[this->unk_158], D_80A65E58[this->unk_158][0]);
    this->unk_210 = 0;
    SkelAnime_ChangeAnimDefaultStop(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210]);
    this->unk_238 = 6;
    this->unk_23C = 0;
    this->actionFunc = NULL;
    this->unk_37A = 0;
    func_80A5BFD8(this, globalCtx);
    func_80A5BFEC(this, globalCtx);
    func_80A5C0B4(this, globalCtx);
    if (this->actor.params == 2) {
        func_80A5F044(this);
    } else if (this->actor.params == 3) {
        func_80A5FCAC(this);
        this->unk_38C = (EnIn*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_IN, this->actor.posRot.pos.x,
                                           this->actor.posRot.pos.y, this->actor.posRot.pos.z, this->actor.shape.rot.x,
                                           this->actor.shape.rot.y, 1, 1);
        if (this->unk_38C == NULL) {
            __assert("this->race.rider != NULL", "../z_en_horse.c", 3077);
        }

        if (!(gSaveContext.eventInf[0] & 0x40)) {
            this->unk_398 = 12.07f;
        } else {
            this->unk_398 = 12.625f;
        }
    } else if (this->actor.params == 7) {
        func_80A61058(this, globalCtx);
    } else if (this->actor.params == 8) {
        func_80A6140C(this);
        Interface_InitHorsebackArchery(globalCtx);
    } else if ((globalCtx->sceneNum == SCENE_SPOT20) && !Flags_GetEventChkInf(0x18) && (DREG(1) == 0)) {
        func_80A61A04(this);
    } else if (globalCtx->sceneNum == SCENE_SOUKO) {
        func_80A5F3A8(this);
    } else if ((globalCtx->sceneNum == SCENE_SPOT12) && (this->unk_158 == 1)) {
        func_80A5F3A8(this);
    } else {
        func_80A5F3DC(this);
    }

    this->actor.shape.rot.z = 0;
    this->actor.posRot.rot.z = this->actor.shape.rot.z;
    this->actor.initPosRot.rot.z = this->actor.shape.rot.z;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Horse/EnHorse_Init.s")
#endif

void EnHorse_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHorse* this = THIS;

    if ((this->unk_1F0 & 0x8000000) != 0) {
        func_800F89E8(&this->unk_21C);
    }
    func_800A6888(globalCtx, &this->unk_160);
    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
    Collider_DestroyJntSph(globalCtx, &this->collider3);
}

void func_80A5C888(EnHorse* this, GlobalContext* globalCtx) {
    func_80A5B5E0(this, globalCtx, &PLAYER->actor.posRot.pos, 0x190);
    if ((this->unk_1F0 & 0x4000) != 0) {
        this->actor.posRot.rot.y += 800.0f;
    }
    this->actor.shape.rot.y = this->actor.posRot.rot.y;
}

void func_80A5C8FC(EnHorse* this) {
    if ((this->unk_14C != 0x11) && (this->unk_14C != 0x12)) {
        if ((D_80A6666C[this->actor.params] != 0) && (this->actor.params != 4)) {
            this->unk_150 = 0;
            this->unk_154 = 0;
        }

        this->unk_254 = this->unk_14C;
        this->unk_14C = 0;
        this->collider1.base.maskA &= ~1;
        this->collider2.base.maskA &= ~1;
        this->collider3.base.maskA &= ~1;
        this->unk_210 = 0;
    }
}

void func_80A5C97C(EnHorse* this, GlobalContext* globalCtx) {
    this->unk_150--;
    this->actor.speedXZ = 0.0f;
    if (this->unk_150 < 0) {
        this->collider1.base.maskA |= 1;
        this->collider2.base.maskA |= 1;
        this->collider3.base.maskA |= 1;
        if (this->unk_20C == 1) {
            this->unk_1F0 &= ~0x80;
            if (this->actor.params == 4) {
                func_80A5CF28(this);
            } else if (this->actor.params == 9) {
                this->actor.params = 5;
                if (globalCtx->csCtx.state != 0) {
                    func_80A5CF64(this);
                } else {
                    this->actor.speedXZ = 8.0f;
                    func_80A5DCB0(this);
                }
            } else if (this->unk_254 == 2) {
                func_80A5CF64(this);
            } else {
                func_80A5CF28(this);
            }

            if (this->actor.params != 0) {
                this->actor.params = 0;
            }
        } else if (this->unk_254 == 5) {
            func_80A5F380(this, 0, 0);
        } else if (this->unk_254 == 6) {
            func_80A5F380(this, 0, 0);
        } else {
            func_80A5F380(this, 0, 0);
        }
    }
}

void func_80A5CAEC(EnHorse* this, GlobalContext* globalCtx, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                   s16 arg7) {
    f32 tmpf1;
    f32 sp40;
    s16 sp3E;
    s16 tmp16;
    s16 tmp17;

    if (func_80A5BFF8(this, globalCtx) == 0) {
        if (this->actor.speedXZ > 8.0f) {
            this->actor.speedXZ -= arg5;
        } else if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ = 0.0f;
        }
    } else {
        arg6 *= func_80A5BB14(this, globalCtx);
        func_80A63148(&this->pad1, &sp40, &sp3E);
        if (Math_Coss(sp3E) <= arg3) {
            this->actor.speedXZ = this->actor.speedXZ - arg2;
            this->actor.speedXZ = CLAMP_MIN(this->actor.speedXZ, 0.0f);
            return;
        } else if (sp40 < arg4) {
            this->unk_1F0 &= ~1;
            this->unk_1F0 &= ~2;
            this->actor.speedXZ -= arg5;
            if (this->actor.speedXZ < 0.0f) {
                this->actor.speedXZ = 0.0f;
            }
            return;
        } else if ((this->unk_1F0 & 1) != 0) {
            if ((0x10 - this->unk_240) > 0) {
                this->actor.speedXZ = (((func_80A5BB14(this, globalCtx) * this->unk_208) - this->actor.speedXZ) /
                                       (0x10 - this->unk_240)) +
                                      this->actor.speedXZ;
            } else {
                this->actor.speedXZ = func_80A5BB14(this, globalCtx) * this->unk_208;
            }
            if ((func_80A5BB14(this, globalCtx) * this->unk_208) <= this->actor.speedXZ) {
                this->unk_1F0 &= ~1;
                this->unk_1F0 |= 2;
            }
        } else if ((this->unk_1F0 & 2) != 0) {
            if (arg6 < this->actor.speedXZ) {
                this->actor.speedXZ -= 0.06f;
            } else if (this->actor.speedXZ < arg6) {
                this->actor.speedXZ = arg6;
                this->unk_1F0 &= ~2;
            }
        } else {
            if (this->actor.speedXZ <= ((arg6 * 0.018518519f) * sp40)) {
                tmpf1 = 1.0f;
            } else {
                tmpf1 = -1.0f;
            }
            this->actor.speedXZ += (tmpf1 * 50.0f) * 0.01f;
            if (arg6 < this->actor.speedXZ) {
                this->actor.speedXZ -= arg5;
                if (this->actor.speedXZ < arg6) {
                    this->actor.speedXZ = arg6;
                }
            }
        }

        tmp17 = ((sp3E * (sp3E * 0.00003102122f)) * (sp3E * 0.00003102122f)) *
                (2.2f - (this->actor.speedXZ * (1.0f / this->unk_208)));

        tmp16 = (tmp17 < (-arg7 * (2.2f - (this->actor.speedXZ * (1.0f / this->unk_208)))))
                    ? (-arg7 * (2.2f - (this->actor.speedXZ * (1.0f / this->unk_208))))
                    : ((arg7 * (2.2f - (this->actor.speedXZ * (1.0f / this->unk_208)))) < tmp17)
                          ? arg7 * (2.2f - (this->actor.speedXZ * (1.0f / this->unk_208)))
                          : tmp17;

        this->actor.posRot.rot.y += tmp16;
        this->actor.shape.rot.y = this->actor.posRot.rot.y;
    }
}

void func_80A5CF28(EnHorse* this) {
    this->unk_160.skelAnime.animCurrentFrame = 0.0f;
    func_80A5CF64(this);
    this->unk_1F0 &= ~0x1000;
}

void func_80A5CF64(EnHorse* this) {
    f32 frame;

    this->unk_14C = 5;
    this->unk_210 = 0;
    if (((this->unk_214 > 35.0f) && (this->unk_158 == 0)) || ((this->unk_214 > 28.0f) && (this->unk_158 == 1))) {
        if ((this->unk_1F0 & 0x1000) == 0) {
            this->unk_1F0 |= 0x1000;
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_SANDDUST, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                   &D_801333E8);
        }
    }

    frame = this->unk_160.skelAnime.animCurrentFrame;
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, frame,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2, -3.0f);
}

void func_80A5D0A0(EnHorse* this, GlobalContext* globalCtx) {
    f32 sp24;
    s16 sp22;

    sp22 = 0;
    this->actor.speedXZ = 0.0f;
    func_80A63148(&this->pad1, &sp24, &sp22);
    if ((sp24 > 10.0f) && (func_80A5BFF8(this, globalCtx) == 1)) {
        if (Math_Coss(sp22) <= -0.5f) {
            func_80A5E588(this);
        } else if (Math_Coss(sp22) <= 0.7071) {
            func_80A5D3C0(this);
        } else {
            func_80A5D628(this);
        }
    }

    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        func_80A5D1A0(this);
    }
}

void func_80A5D1A0(EnHorse* this) {
    this->unk_160.skelAnime.animCurrentFrame = 0.0f;
    func_80A5D1C4(this);
}

void func_80A5D1C4(EnHorse* this) {
    f32 frame;

    this->unk_14C = 6;
    this->unk_210 = 1;
    frame = this->unk_160.skelAnime.animCurrentFrame;
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, frame,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][1]->genericHeader), 2, -3.0f);
    this->unk_21C = this->unk_228;
    if ((this->unk_1F0 & 0x8000000) != 0) {
        Audio_PlaySoundGeneral(0x2816, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    }
}

void func_80A5D2C0(EnHorse* this, GlobalContext* globalCtx) {
    f32 sp24;
    s16 sp22;

    sp22 = 0;
    this->actor.speedXZ = 0.0f;
    func_80A63148(&this->pad1, &sp24, &sp22);
    if ((sp24 > 10.0f) && (func_80A5BFF8(this, globalCtx) == 1)) {
        if (Math_Coss(sp22) <= -0.5f) {
            func_80A5E588(this);
        } else if (Math_Coss(sp22) <= 0.7071) {
            func_80A5D3C0(this);
        } else {
            func_80A5D628(this);
        }
    }

    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        func_80A5CF28(this);
    }
}

void func_80A5D3C0(EnHorse* this) {
    this->unk_14C = 7;
    this->unk_218 = 0;
    this->unk_210 = 4;
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][4]->genericHeader), 2, -3.0f);
}

void func_80A5D468(EnHorse* this, GlobalContext* globalCtx) {
    f32 sp2C;
    s16 sp2A;
    s16 sp28;

    this->actor.speedXZ = 0.0f;
    func_80A5B9C8(this);
    func_80A63148(&this->pad1, &sp2C, &sp28);
    if (sp2C > 10.0f) {
        if (func_80A5BFF8(this, globalCtx) == 0) {
            func_80A5CF28(this);
        } else if (Math_Coss(sp28) <= -0.5f) {
            func_80A5E588(this);
        } else if (Math_Coss(sp28) <= 0.7071) {
            sp2A = (sp28 < -800.0f) ? -800.0f : (sp28 > 800.0f) ? 800.0f : sp28;
            this->actor.posRot.rot.y += sp2A;
            this->actor.shape.rot.y = this->actor.posRot.rot.y;
        } else {
            func_80A5D678(this);
        }
    }

    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        if (Math_Coss(sp28) <= 0.7071) {
            func_80A5D3C0(this);
        } else {
            func_80A5CF28(this);
        }
    }
}

void func_80A5D628(EnHorse* this) {
    func_80A5D678(this);
    if (((this->unk_1F0 & 0x100) == 0) && ((this->unk_1F0 & 0x200) == 0)) {
        this->unk_1F0 |= 0x200;
        this->unk_37C = 8;
    } else {
        this->unk_37C = 0;
    }
}

void func_80A5D678(EnHorse* this) {
    this->unk_150 = 0;
    this->unk_154 = 0;
    func_80A5D69C(this);
}

void func_80A5D69C(EnHorse* this) {
    this->unk_14C = 8;
    this->unk_218 = 0;
    this->unk_210 = 4;
    this->unk_37C = 0;
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][4]->genericHeader), 2, -3.0f);
}

void func_80A5D748(EnHorse* this) {
    this->unk_14C = 8;
    this->unk_218 = 0;
    this->unk_210 = 4;
    this->unk_37C = 0;
    SkelAnime_ChangeAnimDefaultStop(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][4]);
}

void func_80A5D79C(EnHorse* this, GlobalContext* globalCtx) {
    f32 sp3C;
    s16 sp3A;

    func_80A5B9C8(this);
    func_80A63148(&this->pad1, &sp3C, &sp3A);

    if ((this->unk_154 == 0.0f) || ((this->unk_150 > 0.0f) && (this->unk_150 < (this->unk_154 - 20.0f)))) {
        func_80A5CAEC(this, globalCtx, 0.3f, -0.5f, 10.0f, 0.06f, 3.0f, 0x190);
    } else {
        this->actor.speedXZ = 3.0f;
    }

    if (this->actor.speedXZ == 0.0f) {
        this->unk_1F0 &= ~0x200;
        func_80A5CF28(this);
        this->unk_150 = 0;
        this->unk_154 = 0;
    } else if (this->actor.speedXZ > 3.0f) {
        this->unk_1F0 &= ~0x200;
        func_80A5DA68(this);
        this->unk_150 = 0;
        this->unk_154 = 0;
    }

    if (this->unk_150 > 0.0f) {
        this->unk_150--;
        if (this->unk_150 <= 0.0f) {
            this->unk_154 = 0;
        }
    }

    if (this->unk_37C <= 0) {
        this->unk_1F0 &= ~0x200;
        this->unk_160.skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.75f;
        if ((SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) || (this->actor.speedXZ == 0.0f)) {
            if (this->unk_150 <= 0.0f) {
                if (this->actor.speedXZ > 3.0f) {
                    func_80A5DA68(this);
                    this->unk_150 = 0;
                    this->unk_154 = 0;
                } else if ((sp3C < 10.0f) || (Math_Coss(sp3A) <= -0.5f)) {
                    func_80A5CF28(this);
                    this->unk_150 = 0;
                    this->unk_154 = 0;
                } else {
                    func_80A5D748(this);
                }
            }
        }
    } else {
        this->actor.speedXZ = 0.0f;
        this->unk_37C--;
    }
}

void func_80A5DA68(EnHorse* this) {
    this->unk_14C = 9;
    this->unk_210 = 5;
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][5]->genericHeader), 2, -3.0f);
}

void func_80A5DB0C(EnHorse* this) {
    this->unk_14C = 9;
    this->unk_210 = 5;
    SkelAnime_ChangeAnimDefaultStop(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][5]);
}

void func_80A5DB58(EnHorse* this, GlobalContext* globalCtx) {
    f32 sp3C;
    s16 sp3A;

    func_80A5CAEC(this, globalCtx, 0.3f, -0.5f, 10.0f, 0.06f, 6.0f, 0x190);
    func_80A63148(&this->pad1, &sp3C, &sp3A);
    if (this->actor.speedXZ < 3.0f) {
        func_80A5D678(this);
    }

    this->unk_160.skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.375f;
    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        func_80A5BA84(this);
        func_800AA000(0.0f, 0x3C, 8, 0xFF);
        if (this->actor.speedXZ >= 6.0f) {
            func_80A5DC8C(this);
        } else if (this->actor.speedXZ < 3.0f) {
            func_80A5D678(this);
        } else {
            func_80A5DB0C(this);
        }
    }
}

void func_80A5DC8C(EnHorse* this) {
    this->unk_154 = 0;
    this->unk_150 = 0;
    func_80A5DCB0(this);
}

void func_80A5DCB0(EnHorse* this) {
    this->unk_14C = 0xA;
    this->unk_210 = 6;
    this->unk_234 = 0;
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][6]->genericHeader), 2, -3.0f);
}

void func_80A5DD58(EnHorse* this) {
    this->unk_154 = 0;
    this->unk_150 = 0;
    this->unk_14C = 0xA;
    this->unk_210 = 6;
    this->unk_234 = 0;
    SkelAnime_ChangeAnimDefaultStop(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][6]);
}

void func_80A5DDB0(EnHorse* this, GlobalContext* globalCtx) {
    Vec3s* ptr;
    f32 tmpf1;

    this->unk_14C = 0xA;
    this->unk_210 = 6;
    SkelAnime_ChangeAnimDefaultStop(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][6]);
    ptr = &this->unk_160.skelAnime.limbDrawTbl[0];
    tmpf1 = ptr->y;
    this->unk_258.y += tmpf1 * 0.01f;
    this->actionFunc = NULL;
}

void func_80A5DE38(EnHorse* this, GlobalContext* globalCtx) {
    f32 sp3C;
    s16 sp3A;
    f32 tmpf1;

    func_80A63148(&this->pad1, &sp3C, &sp3A);
    tmpf1 = this->unk_150;
    if (tmpf1 <= 0) {
        func_80A5CAEC(this, globalCtx, 0.3f, -0.5f, 10.0f, 0.06f, 8.0f, 0x190);
    } else if (tmpf1 > 0) {
        this->unk_150--;
        this->actor.speedXZ = 8.0f;
    }

    if (this->actor.speedXZ < 6.0f) {
        func_80A5DA68(this);
    }

    this->unk_160.skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.3f;
    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        func_80A5BACC(this);
        func_800AA000(0.0f, 0x78, 8, 0xFF);
        if (func_80A5BFF8(this, globalCtx) == 1) {
            if ((10.0f <= sp3C) && (Math_Coss(sp3A) <= -0.5f)) {
                func_80A5E2A8(this, globalCtx);
            } else if (this->actor.speedXZ < 6.0f) {
                func_80A5DA68(this);
            } else {
                func_80A5DD58(this);
            }
        } else {
            func_80A5DD58(this);
        }
    }
}

void func_80A5E00C(EnHorse* this) {
    this->unk_14C = 0xB;
    this->unk_210 = 3;
    this->unk_1F0 &= ~0x800;
    this->unk_21C = this->unk_228;
    if ((this->unk_1F0 * 0x10) < 0) {
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    }
    func_800AA000(0.0f, 0xB4, 0x14, 0x64);
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2, -3.0f);
}

void func_80A5E12C(EnHorse* this, GlobalContext* globalCtx) {
    f32 sp34;
    s16 sp32;

    this->actor.speedXZ = 0.0f;
    if ((this->unk_214 > 25.0f) && ((this->unk_1F0 & 0x800) == 0)) {
        this->unk_1F0 |= 0x800;
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_LAND2, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        func_800AA000(0.0f, 0xB4, 0x14, 0x64);
    }

    func_80A63148(&this->pad1, &sp34, &sp32);
    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        if (func_80A5BFF8(this, globalCtx) == 1) {
            if ((this->unk_1F0 & 0x10) != 0) {
                this->unk_150 = 0x64;
                this->unk_154 = 0x64;
                this->unk_1F0 &= ~0x10;
                func_80A5E5AC(this);
            } else if ((this->unk_1F0 & 0x20) != 0) {
                this->unk_150 = 0x64;
                this->unk_154 = 0x64;
                this->unk_1F0 &= ~0x20;
                func_80A5D69C(this);
            } else if (Math_Coss(sp32) <= -0.5f) {
                func_80A5E588(this);
            } else {
                func_80A5CF28(this);
            }
        } else {
            func_80A5CF28(this);
        }
    }
}

void func_80A5E2A8(EnHorse* this, GlobalContext* globalCtx) {
    this->unk_14C = 0xC;
    this->unk_210 = 2;
    Audio_PlaySoundGeneral(NA_SE_EV_HORSE_SLIP, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.5f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2, -3.0f);
    this->unk_1F0 |= 0x400;
    this->unk_1F0 &= ~1;
}

void func_80A5E39C(EnHorse* this, GlobalContext* globalCtx) {
    if (this->actor.speedXZ > 0.0f) {
        this->actor.speedXZ -= 0.6f;
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ = 0.0f;
        }
    }

    if ((this->unk_1F0 & 0x400) != 0) {
        if (this->unk_160.skelAnime.animCurrentFrame > 29.0f) {
            this->actor.speedXZ = 0.0f;
            if (Math_Rand_ZeroOne() > 0.5) {
                this->unk_21C = this->unk_228;
                if ((this->unk_1F0 & 0x8000000) != 0) {
                    Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_21C, 4, &D_801333E0, &D_801333E0,
                                           &D_801333E8);
                }
                func_800AA000(0.0f, 0xB4, 0x14, 0x64);
                this->unk_1F0 &= ~0x400;
            } else {
                func_80A5CF28(this);
            }
        }
    }
    if (this->unk_160.skelAnime.animCurrentFrame > 29.0f) {
        this->actor.speedXZ = 0.0f;
    } else if ((this->actor.speedXZ > 3.0f) && ((this->unk_1F0 & 0x10) != 0)) {
        this->actor.speedXZ = 3.0f;
    }

    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        if ((this->unk_1F0 & 0x10) != 0) {
            this->unk_150 = 0x64;
            this->unk_154 = 0x64;
            func_80A5E5AC(this);
            this->unk_1F0 &= ~0x10;
        } else {
            func_80A5CF28(this);
        }
    }
}

void func_80A5E588(EnHorse* this) {
    this->unk_154 = 0;
    this->unk_150 = 0;
    func_80A5E5AC(this);
}

void func_80A5E5AC(EnHorse* this) {
    this->unk_14C = 0xD;
    this->unk_210 = 4;
    this->unk_218 = 0;
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][4]->genericHeader), 0, -3.0f);
}

void func_80A5E650(EnHorse* this, GlobalContext* globalCtx) {
    f32 sp34;
    s16 sp32;
    s16 tmp;
    Player* player = PLAYER;

    func_80A5B9C8(this);
    func_80A63148(&this->pad1, &sp34, &sp32);
    if (func_80A5BFF8(this, globalCtx) == 1) {
        if ((this->unk_154 == 0.0f) || ((this->unk_150 > 0.0f) && (this->unk_150 < (this->unk_154 - 20.0f)))) {
            if ((sp34 < 10.0f) && (this->unk_150 <= 0.0f)) {
                func_80A5CF28(this);
                this->actor.speedXZ = 0.0f;
                return;
            }

            if (sp34 < 10.0f) {
                sp32 = -0x7FFF;
            } else if (Math_Coss(sp32) > -0.5f) {
                this->unk_154 = 0;
                func_80A5CF28(this);
                this->actor.speedXZ = 0.0f;
                return;
            }
        } else if (sp34 < 10.0f) {
            sp32 = -0x7FFF;
        }
    } else {
        if (player->actor.flags & 0x100) {
            func_80A5CF28(this);
            this->actor.speedXZ = 0.0f;
            return;
        }
        sp32 = -0x7FFF;
    }

    this->actor.speedXZ = -2.0f;
    tmp = 0x7FFF - sp32;
    tmp = (tmp < -1200.0f) ? -1200.0f : (1200.0f < tmp) ? 1200.0f : tmp;
    this->actor.posRot.rot.y += tmp;
    this->actor.shape.rot.y = this->actor.posRot.rot.y;

    if (this->unk_150 > 0.0f) {
        this->unk_150--;
        if (this->unk_150 <= 0.0f) {
            this->unk_154 = 0;
        }
    }

    this->unk_160.skelAnime.animPlaybackSpeed = (this->actor.speedXZ * 0.5f) * 1.5f;
    if ((SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) && (this->unk_150 <= 0.0f) &&
        (func_80A5BFF8(this, globalCtx) == 1)) {
        if ((sp34 > 10.0f) && (Math_Coss(sp32) <= -0.5f)) {
            this->unk_154 = 0;
            func_80A5E588(this);
        } else if (sp34 < 10.0f) {
            this->unk_154 = 0;
            func_80A5CF28(this);
        } else {
            func_80A5E5AC(this);
        }
    }
}

void func_80A5E9F8(EnHorse* this, GlobalContext* globalCtx) {
    this->unk_160.skelAnime.animCurrentFrame = 0.0f;
    func_80A5EA1C(this, globalCtx);
}

void func_80A5EA1C(EnHorse* this, GlobalContext* globalCtx) {
    f32 frame;
    f32 tmpf1;
    Vec3s* ptr;

    this->unk_14C = 0xE;
    this->unk_210 = 7;
    frame = this->unk_160.skelAnime.animCurrentFrame;
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.5f, frame,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][7]->genericHeader), 2, -3.0f);
    this->actionFunc = NULL;
    this->unk_274 = this->actor.posRot.pos.y;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0;
    ptr = &this->unk_160.skelAnime.limbDrawTbl[0];
    tmpf1 = ptr->y;
    this->unk_258.y -= tmpf1 * 0.01f;

    Audio_PlaySoundGeneral(NA_SE_EV_HORSE_JUMP, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    func_800AA000(0.0f, 0xAA, 0xA, 0xA);
}

void func_80A5EB4C(EnHorse* this) {
}

void func_80A5EB54(EnHorse* this, GlobalContext* globalCtx) {
    s32 pad[4];
    f32 frame = this->unk_160.skelAnime.animCurrentFrame;

    this->unk_1F0 |= 4;
    this->actor.speedXZ = 12.0f;
    if (frame > 17.0f) {
        this->actor.gravity = -3.5f;
        if (this->actor.velocity.y == 0) {
            this->actor.velocity.y = -6.0f;
        }

        this->unk_160.skelAnime.animPlaybackSpeed =
            (this->actor.posRot.pos.y < (this->actor.groundY + 90.0f)) ? 1.5f : 0;

    } else {
        Vec3s* ptr = &this->unk_160.skelAnime.limbDrawTbl[0];
        f32 tmpf1 = ptr->y;
        this->actor.posRot.pos.y = this->unk_274 + (tmpf1 * 0.01f);
    }

    if ((SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) ||
        ((frame > 17.0f) && (this->actor.posRot.pos.y < ((this->actor.groundY - this->actor.velocity.y) + 80.0f)))) {
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_LAND, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        func_800AA000(0.0f, 0xFF, 0xA, 0x50);
        this->unk_1F0 &= ~4;
        this->actor.gravity = -3.5f;
        this->actor.posRot.pos.y = this->actor.groundY;
        func_80028A54(globalCtx, 25.0f, &this->actor.posRot.pos);
        func_80A5DDB0(this, globalCtx);
    }
}

void func_80A5ED18(EnHorse* this, GlobalContext* globalCtx) {
    this->unk_160.skelAnime.animCurrentFrame = 0.0f;
    func_80A5ED3C(this, globalCtx);
}

void func_80A5ED3C(EnHorse* this, GlobalContext* globalCtx) {
    f32 frame;
    Vec3s* ptr;
    f32 tmpf1;

    this->unk_14C = 0xF;
    this->unk_210 = 8;
    frame = this->unk_160.skelAnime.animCurrentFrame;
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.5f, frame,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][8]->genericHeader), 2, -3.0f);
    this->actionFunc = NULL;
    this->unk_274 = this->actor.posRot.pos.y;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0;
    ptr = &this->unk_160.skelAnime.limbDrawTbl[0];
    tmpf1 = ptr->y;
    this->unk_258.y -= tmpf1 * 0.01f;
    this->unk_1F0 |= 8;
    Audio_PlaySoundGeneral(NA_SE_EV_HORSE_JUMP, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    func_800AA000(0.0f, 0xAA, 0xA, 0xA);
}

void func_80A5EE78(EnHorse* this) {
}

void func_80A5EE80(EnHorse* this, GlobalContext* globalCtx) {
    s32 pad[4];
    f32 frame = this->unk_160.skelAnime.animCurrentFrame;

    this->unk_1F0 |= 4;
    this->actor.speedXZ = 13.0f;
    if (frame > 23.0f) {
        this->actor.gravity = -3.5f;
        if (this->actor.velocity.y == 0) {
            this->actor.velocity.y = -10.5f;
        }
        this->unk_160.skelAnime.animPlaybackSpeed =
            (this->actor.posRot.pos.y < (this->actor.groundY + 90.0f)) ? 1.5f : 0;
    } else {
        Vec3s* ptr = &this->unk_160.skelAnime.limbDrawTbl[0];
        f32 tmpf1 = ptr->y;

        this->actor.posRot.pos.y = this->unk_274 + (tmpf1 * 0.01f);
    }

    if ((SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) ||
        ((frame > 23.0f) && (this->actor.posRot.pos.y < ((this->actor.groundY - this->actor.velocity.y) + 80.0f)))) {
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_LAND, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        func_800AA000(0.0f, 0xFF, 0xA, 0x50);
        this->unk_1F0 &= ~4;
        this->actor.gravity = -3.5f;
        this->actor.posRot.pos.y = this->actor.groundY;
        func_80028A54(globalCtx, 25.0f, &this->actor.posRot.pos);
        func_80A5DDB0(this, globalCtx);
    }
}

void func_80A5F044(EnHorse* this) {
    this->collider1.base.maskA &= ~1;
    this->collider2.base.maskA &= ~1;
    this->collider3.base.maskA &= ~1;
    this->unk_14C = 1;
    this->unk_210 = 4;
    this->unk_1F0 |= 0x2000;
    this->unk_250 = 0;
}

void func_80A5F08C(EnHorse* this, GlobalContext* globalCtx) {
    if ((DREG(53) != 0) && (this->unk_158 == 0)) {
        DREG(53) = 0;
        if (func_80A5BD94(this, globalCtx) != 0) {
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                   &D_801333E8);
            this->unk_1F0 &= ~0x2000;
            gSaveContext.horseData.scene = globalCtx->sceneNum;
            Camera_SetParam(globalCtx->cameraPtrs[0], 8, &this->actor);
            func_8005A77C(globalCtx->cameraPtrs[0], 0x38);
            Camera_SetCameraData(globalCtx->cameraPtrs[0], 4, NULL, NULL, 0x51, 0, 0);
        }
    }

    if ((this->unk_1F0 & 0x2000) == 0) {
        this->unk_250 = 0;
        func_80A5F760(this, globalCtx);
        this->actor.params = 0;
        this->collider1.base.maskA |= 1;
        this->collider2.base.maskA |= 1;
        this->collider3.base.maskA |= 1;
    }
}

void func_80A5F1B0(EnHorse* this, s32 arg1, f32 arg2, f32 arg3) {
    this->unk_14C = 2;
    this->actor.speedXZ = 0.0f;

    if ((arg1 != 0) && (arg1 != 1) && (arg1 != 3)) {
        arg1 = 0;
    }

    if (arg1 != this->unk_210) {
        this->unk_210 = arg1;
        if (this->unk_210 == 0) {
            this->unk_1F0 &= ~0x1000;
        } else if (this->unk_210 == 1) {
            this->unk_21C = this->unk_228;
            if ((this->unk_1F0 & 0x8000000) != 0) {
                Audio_PlaySoundGeneral(NA_SE_EV_HORSE_GROAN, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            }
        } else if (this->unk_210 == 3) {
            this->unk_21C = this->unk_228;
            if ((this->unk_1F0 & 0x8000000) != 0) {
                Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            }
            this->unk_1F0 &= ~0x800;
        }

        SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, arg3,
                             SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2,
                             arg2);
    }
}

void func_80A5F380(EnHorse* this, s32 arg1, f32 arg2) {
    func_80A5F1B0(this, arg1, arg2, this->unk_214);
}

void func_80A5F3A8(EnHorse* this) {
    this->unk_210 = 4;
    func_80A5F1B0(this, 4, 0.0f, 0.0f);
}

void func_80A5F3DC(EnHorse* this) {
    func_80A5F3A8(this);
    this->unk_1F0 &= ~0x10000;
}

void func_80A5F414(EnHorse* this, GlobalContext* globalCtx) {
    s32 sp34;

    this->actor.speedXZ = 0.0f;
    func_80A5BC68(this, globalCtx);
    if ((DREG(53) != 0) && (this->unk_158 == 0)) {
        DREG(53) = 0;
        if (func_80A5BBBC(globalCtx, this, &this->actor.posRot.pos) == 0) {
            if (func_80A5BD94(this, globalCtx) != 0) {
                Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                       &D_801333E8);
                this->unk_250 = 0;
                func_80A5F760(this, globalCtx);
                Camera_SetParam(globalCtx->cameraPtrs[0], 8, &this->actor);
                func_8005A77C(globalCtx->cameraPtrs[0], 0x38);
                Camera_SetCameraData(globalCtx->cameraPtrs[0], 4, NULL, NULL, 0x51, 0, 0);
            }
        } else {
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                   &D_801333E8);
            this->unk_250 = 0;
            func_80A5F5F8(this, 6, -3.0f, 0.0f);
        }
    }

    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        sp34 = 0;
        if (this->unk_210 != 0) {
            if (this->unk_210 == 1) {
                sp34 = 1;
            } else if (this->unk_210 == 3) {
                sp34 = 2;
            }
        }

        func_80A5F1B0(this, D_80A66678[(sp34 * 2) + ((Math_Rand_ZeroOne() > 0.5f) ? 0 : 1)], 0.0f, 0.0f);
    }
}

void func_80A5F5F8(EnHorse* this, s32 arg1, f32 arg2, f32 arg3) {
    this->unk_14C = 3;
    this->unk_1F0 &= ~0x8000;
    if ((arg1 != 5) && (arg1 != 6) && (arg1 != 4)) {
        arg1 = 4;
    }

    if (arg1 != this->unk_210) {
        this->unk_210 = arg1;
        SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, arg3,
                             SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][arg1]->genericHeader), 2, arg2);
    } else {
        SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, arg3,
                             SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2,
                             0.0f);
    }
}

void func_80A5F760(EnHorse* this, GlobalContext* globalCtx) {
    s32 val = 4;
    Player* player = PLAYER;
    f32 ret = func_8002DB8C(&this->actor, &player->actor);

    if (ret > 400.0f) {
        val = 6;
    } else if (!(ret <= 300.0f)) {
        val = 4;
        if (ret <= 400.0f) {
            val = 5;
        }
    }

    if (this->unk_210 == 6) {
        if (ret > 400.0f) {
            val = 6;
        } else {
            val = 5;
        }
    } else if (this->unk_210 == 5) {
        if (ret > 400.0f) {
            val = 6;
        } else if (ret < 300.0f) {
            val = 4;
        } else {
            val = 5;
        }
    } else if (this->unk_210 == 4) {
        if (ret > 300.0f) {
            val = 5;
        } else {
            val = 4;
        }
    }

    func_80A5F5F8(this, val, -3.0f, 0);
}

void func_80A5F890(EnHorse* this, GlobalContext* globalCtx) {
    f32 sp3C;
    f32 tmpf1;

    DREG(53) = 0;
    sp3C = func_8002DB8C(&this->actor, &PLAYER->actor);
    if (((this->unk_370 == 2) || (this->unk_370 == 3)) && (sp3C > 300.0f) && ((this->unk_1F0 & 0x8000) == 0)) {
        this->unk_210 = 3;
        this->unk_1F0 |= 0x8000;
        this->unk_376 = func_8002DA78(&this->actor, &PLAYER->actor);
        tmpf1 = (f32)this->unk_376 - this->actor.posRot.rot.y;
        if (tmpf1 > 32767.0f) {
            tmpf1 -= 32767;
        } else if (tmpf1 < -32767.0f) {
            tmpf1 += 32767;
        }

        this->unk_378 = tmpf1 / SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader);
        SkelAnime_ChangeAnimDefaultStop(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210]);
        this->unk_160.skelAnime.animPlaybackSpeed = 1.0f;
        this->unk_1F0 &= ~0x800;
        this->unk_21C = this->unk_228;

    } else if ((this->unk_1F0 & 0x8000) != 0) {
        this->actor.posRot.rot.y += this->unk_378;
        this->actor.shape.rot.y = this->actor.posRot.rot.y;
        if ((this->unk_214 > 25.0f) && ((this->unk_1F0 & 0x800) == 0)) {
            this->unk_1F0 |= 0x800;
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_LAND2, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                   &D_801333E8);
        }
    } else {
        func_80A5C888(this, globalCtx);
    }

    if (this->unk_210 == 6) {
        this->actor.speedXZ = 8.0f;
        this->unk_160.skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.3f;
    } else if (this->unk_210 == 5) {
        this->actor.speedXZ = 6.0f;
        this->unk_160.skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.375f;
    } else if (this->unk_210 == 4) {
        this->actor.speedXZ = 3.0f;
        func_80A5B9C8(this);
        this->unk_160.skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.75f;
    } else {
        this->actor.speedXZ = 0.0f;
        this->unk_160.skelAnime.animPlaybackSpeed = 1.0f;
    }

    if ((this->unk_1F0 & 0x8000) == 0) {
        this->unk_250++;
        if (this->unk_250 >= 0x12D) {
            func_80A5F3DC(this);
            this->unk_21C = this->unk_228;
            if ((this->unk_1F0 & 0x8000000) != 0) {
                Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            }
        }
    }

    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        if (this->unk_210 == 6) {
            func_80A5BACC(this);
        } else if (this->unk_210 == 5) {
            func_80A5BA84(this);
        }

        this->unk_1F0 &= ~0x8000;
        if (sp3C < 100.0f) {
            func_80A5F3DC(this);
        } else {
            func_80A5F760(this, globalCtx);
        }
    }
}

void func_80A5FCAC(EnHorse* this) {
    this->unk_204 = 0;
    this->unk_218 = 0;
    this->actor.speedXZ = 0.0f;
    func_80A5FDD4(this);
    this->unk_21C = this->unk_228;
    if ((this->unk_1F0 & 0x8000000) != 0) {
        Audio_PlaySoundGeneral(NA_SE_IT_INGO_HORSE_NEIGH, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    }
}

#ifdef NON_MATCHING
// comparison args flipped
void func_80A5FD30(s32 arg0, f32 arg1, s32 arg2, s16* arg3, f32* arg4) {
    *arg3 = D_80A66690[arg0];
    *arg4 = arg1;
    if ((arg0 == 3) || (&D_80A66690[arg0] == &D_80A66690[7]) || (&D_80A66690[arg0] == &D_80A66690[8]) ||
        (&D_80A66690[arg0] == &D_80A66690[4])) {
        *arg4 = 0.0f;
    }

    if (arg2 == 1) {
        if (&D_80A66690[arg0] == &D_80A66690[5]) {
            *arg3 = 4;
            *arg4 = arg1;
        } else if (&D_80A66690[arg0] == &D_80A66690[6]) {
            *arg3 = 3;
            *arg4 = arg1;
        }
    }
}
#else
void func_80A5FD30(s32 arg0, f32 arg1, s32 arg2, s16* arg3, f32* arg4);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Horse/func_80A5FD30.s")
#endif

void func_80A5FDD4(EnHorse* this) {
    s32 sp34 = 0;
    f32 sp30;

    this->unk_14C = 4;
    this->unk_1F0 &= ~0x1000;

    if (this->actor.speedXZ == 0.0f) {
        if (this->unk_210 != 0) {
            sp34 = 1;
        }
        this->unk_210 = 0;
    } else if (this->actor.speedXZ <= 3.0f) {
        if (this->unk_210 != 4) {
            sp34 = 1;
        }
        this->unk_210 = 4;
    } else if (this->actor.speedXZ <= 6.0f) {
        if (this->unk_210 != 5) {
            sp34 = 1;
        }
        this->unk_210 = 5;
    } else {
        if (this->unk_210 != 6) {
            sp34 = 1;
        }
        this->unk_210 = 6;
    }

    if (this->unk_210 == 4) {
        sp30 = this->actor.speedXZ * 0.5f;
    } else if (this->unk_210 == 5) {
        sp30 = this->actor.speedXZ * 0.25f;
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_RUN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    } else if (this->unk_210 == 6) {
        sp30 = this->actor.speedXZ * 0.2f;
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_RUN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    } else {
        sp30 = 1.0f;
    }

    if (sp34 == 1) {
        SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210],
                             (D_80A65E60[this->unk_210] * sp30) * 1.5f, 0,
                             SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2,
                             -3.0f);
    } else {
        SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210],
                             (D_80A65E60[this->unk_210] * sp30) * 1.5f, 0,
                             SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2, 0);
    }
}

void func_80A600E8(EnHorse* this, GlobalContext* globalCtx) {
    f32 tmpf1;

    if ((this->unk_210 == 0) || (this->unk_210 == 1)) {
        func_80A5BC68(this, globalCtx);
    } else if (this->unk_210 == 4) {
        func_80A5B9C8(this);
    }

    func_80A5B61C(this, globalCtx, &D_80A66654);
    if (this->unk_388 == 0) {
        this->actor.speedXZ = 0.0f;
        this->unk_38C->actor.speedXZ = 0.0f;
        if (this->unk_210 != 0) {
            func_80A5FDD4(this);
        }
    }

    if (this->unk_210 == 4) {
        tmpf1 = this->actor.speedXZ * 0.5f;
    } else if (this->unk_210 == 5) {
        tmpf1 = this->actor.speedXZ * 0.25f;
    } else if (this->unk_210 == 6) {
        tmpf1 = this->actor.speedXZ * 0.2f;
    } else {
        tmpf1 = 1.0f;
    }
    this->unk_160.skelAnime.animPlaybackSpeed = tmpf1;

    if ((SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) ||
        ((this->unk_210 == 0) && (this->actor.speedXZ != 0.0f))) {
        func_80A5FDD4(this);
    }

    if ((this->unk_1F0 << 8) < 0) {
        this->unk_38C->unk_1E6 = 7;
        this->unk_38C->unk_1E0 = 0.0f;
    } else {
        func_80A5FD30(this->unk_210, this->unk_160.skelAnime.animCurrentFrame, this->unk_394 & 1,
                      &this->unk_38C->unk_1E6, &this->unk_38C->unk_1E0);
    }
}

void func_80A60294(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->unk_210 = 6;
    this->unk_380 = 1;
    SkelAnime_ChangeAnimPlaybackStop(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][6],
                                     this->actor.speedXZ * 0.3f);
}

void func_80A60300(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    Vec3f sp2C;
    s32 pad;

    sp2C.x = action->endPos.x;
    sp2C.y = action->endPos.y;
    sp2C.z = action->endPos.z;
    if (Math3D_Vec3f_DistXYZ(&sp2C, &this->actor.posRot.pos) > 8.0f) {
        func_80A5B5E0(this, globalCtx, &sp2C, 0x190);
        this->actor.speedXZ = 8.0f;
        this->unk_160.skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.3f;
    } else {
        this->actor.posRot.pos = sp2C;
        this->actor.speedXZ = 0.0f;
    }

    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        func_80A5BACC(this);
        func_800AA000(0.0f, 0x78, 8, 0xFF);
        SkelAnime_ChangeAnimPlaybackStop(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210],
                                         this->actor.speedXZ * 0.3f);
    }
}

void func_80A6044C(EnHorse* this, GlobalContext* globalCtx) {
    this->unk_160.skelAnime.animCurrentFrame = 0.0f;
    func_80A60470(this, globalCtx);
}

void func_80A60470(EnHorse* this, GlobalContext* globalCtx) {
    f32 frame;
    Vec3s* ptr;
    f32 tmpf1;

    this->unk_210 = 8;
    frame = this->unk_160.skelAnime.animCurrentFrame;
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.5f, frame,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][8]->genericHeader), 2, -3.0f);
    this->actionFunc = NULL;
    this->unk_274 = this->actor.posRot.pos.y;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0;
    ptr = &this->unk_160.skelAnime.limbDrawTbl[0];
    tmpf1 = ptr->y;
    this->unk_258.y -= (tmpf1 * 0.01f);
    this->unk_1F0 |= 8;
    Audio_PlaySoundGeneral(NA_SE_EV_HORSE_JUMP, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    func_800AA000(0.0f, 0xAA, 0xA, 0xA);
}

void func_80A605A4(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    func_80A6044C(this, globalCtx);
    this->unk_380 = 2;
    this->unk_384 &= ~1;
}

void func_80A605E0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    f32 frame;
    Vec3s* ptr;
    f32 tmpf1;
    s32 pad[2];

    if ((this->unk_384 & 1) != 0) {
        func_80A60300(this, globalCtx, action);
        return;
    }

    this->unk_1F0 |= 4;
    this->actor.speedXZ = 13.0f;
    frame = this->unk_160.skelAnime.animCurrentFrame;
    if (frame > 19.0f) {
        this->actor.gravity = -3.5f;
        if (this->actor.velocity.y == 0.0f) {
            this->actor.velocity.y = -10.5f;
        }
        if (this->actor.posRot.pos.y < (this->actor.groundY + 90.0f)) {
            this->unk_160.skelAnime.animPlaybackSpeed = 1.5f;
        } else {
            this->unk_160.skelAnime.animPlaybackSpeed = 0.0f;
        }
    } else {
        ptr = &this->unk_160.skelAnime.limbDrawTbl[0];
        tmpf1 = ptr->y;
        this->actor.posRot.pos.y = this->unk_274 + (tmpf1 * 0.01f);
    }

    if ((SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) ||
        ((frame > 19.0f) && (this->actor.posRot.pos.y < ((this->actor.groundY - this->actor.velocity.y) + 80.0f)))) {
        this->unk_384 |= 1;
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_LAND, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        func_800AA000(0.0f, 0xFF, 0xA, 0x50);
        this->unk_1F0 &= ~4;
        this->actor.gravity = -3.5f;
        this->actor.velocity.y = 0.0f;
        this->actor.posRot.pos.y = this->actor.groundY;
        func_80028A54(globalCtx, 25.0f, &this->actor.posRot.pos);
        this->unk_210 = 6;
        SkelAnime_ChangeAnimPlaybackStop(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][6], D_80A65E60[6]);
        ptr = &this->unk_160.skelAnime.limbDrawTbl[0];
        tmpf1 = ptr->y;
        this->unk_258.y += tmpf1 * 0.01f;
        this->actionFunc = NULL;
    }
}

void func_80A60838(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->unk_210 = 3;
    this->unk_380 = 3;
    this->unk_384 &= ~4;
    this->unk_1F0 &= ~0x800;
    this->unk_21C = this->unk_228;
    if ((this->unk_1F0 & 0x8000000) != 0) {
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    }
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2, -3.0f);
}

void func_80A60954(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->actor.speedXZ = 0.0f;
    if (this->unk_214 > 25.0f) {
        if ((this->unk_1F0 & 0x800) == 0) {
            this->unk_1F0 |= 0x800;
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_LAND2, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                   &D_801333E8);
        }
    }

    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        this->unk_210 = 0;
        if ((this->unk_384 & 4) == 0) {
            this->unk_384 |= 4;
            SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2,
                                 -3.0f);
        } else {
            SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 0,
                                 0.0f);
        }
    }
}

void func_80A60AFC(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->actor.posRot.pos.x = action->startPos.x;
    this->actor.posRot.pos.y = action->startPos.y;
    this->actor.posRot.pos.z = action->startPos.z;
    this->actor.pos4 = this->actor.posRot.pos;
    this->actor.posRot.rot.y = action->urot.y;
    this->actor.shape.rot = this->actor.posRot.rot;
    this->unk_210 = 6;
    this->unk_380 = 4;
    SkelAnime_ChangeAnimPlaybackStop(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][6],
                                     this->actor.speedXZ * 0.3f);
}

void func_80A60BDC(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    Vec3f sp2C;
    s32 pad;

    sp2C.x = action->endPos.x;
    sp2C.y = action->endPos.y;
    sp2C.z = action->endPos.z;
    if (Math3D_Vec3f_DistXYZ(&sp2C, &this->actor.posRot.pos) > 8.0f) {
        func_80A5B5E0(this, globalCtx, &sp2C, 0x190);
        this->actor.speedXZ = 8.0f;
        this->unk_160.skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.3f;
    } else {
        this->actor.posRot.pos = sp2C;
        this->actor.speedXZ = 0.0f;
    }

    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        func_80A5BACC(this);
        func_800AA000(0.0f, 0x78, 8, 0xFF);
        SkelAnime_ChangeAnimPlaybackStop(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210],
                                         this->actor.speedXZ * 0.3f);
    }
}

void func_80A60D28(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->actor.posRot.pos.x = action->startPos.x;
    this->actor.posRot.pos.y = action->startPos.y;
    this->actor.posRot.pos.z = action->startPos.z;
    this->actor.pos4 = this->actor.posRot.pos;
    this->actor.posRot.rot.y = action->urot.y;
    this->actor.shape.rot = this->actor.posRot.rot;
    this->unk_210 = 3;
    this->unk_380 = 5;
    this->unk_384 &= ~4;
    this->unk_1F0 &= ~0x800;
    this->unk_21C = this->unk_228;
    if ((this->unk_1F0 & 0x8000000) != 0) {
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    }
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2, -3.0f);
}

void func_80A60EB0(EnHorse* this, GlobalContext* globalCtx, CsCmdActorAction* action) {
    this->actor.speedXZ = 0.0f;
    if (this->unk_214 > 25.0f) {
        if ((this->unk_1F0 & 0x800) == 0) {
            this->unk_1F0 |= 0x800;
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_LAND2, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                   &D_801333E8);
        }
    }

    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        this->unk_210 = 0;
        if ((this->unk_384 & 4) == 0) {
            this->unk_384 |= 4;
            SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2,
                                 -3.0f);
        } else {
            SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 0,
                                 0.0f);
        }
    }
}

void func_80A61058(EnHorse* this, GlobalContext* globalCtx) {
    this->unk_20C = 0;
    this->unk_14C = 0x11;
    this->unk_380 = 0;
    this->actor.speedXZ = 0.0f;
}

s32 func_80A61078(s32 action) {
    const s32 tmp = 5;
    s32 i = 0;

    for (i = 0; i < tmp; i++) {
        if (D_80A666D4[i].unk_0 == action) {
            return D_80A666D4[i].unk_4;
        }
        if (D_80A666D4[i].unk_0 > action) {
            return 0;
        }
    }

    return 0;
}

void func_80A610C8(EnHorse* this, GlobalContext* globalCtx) {
    s32 ret;
    CsCmdActorAction* linkAction = globalCtx->csCtx.linkAction;

    if (globalCtx->csCtx.state == 3) {
        this->unk_20C = 1;
        this->actor.params = 0xA;
        this->unk_14C = 2;
        func_80A5C8FC(this);
        return;
    }

    if (linkAction != NULL) {
        ret = func_80A61078(linkAction->action);
        if (ret != 0) {
            if (ret != this->unk_380) {
                if (this->unk_380 == 0) {
                    this->actor.posRot.pos.x = linkAction->startPos.x;
                    this->actor.posRot.pos.y = linkAction->startPos.y;
                    this->actor.posRot.pos.z = linkAction->startPos.z;
                    this->actor.posRot.rot.y = linkAction->urot.y;
                    this->actor.shape.rot = this->actor.posRot.rot;
                    this->actor.pos4 = this->actor.posRot.pos;
                }

                this->unk_380 = ret;
                D_80A666A4[ret](this, globalCtx, linkAction);
            }

            D_80A666BC[this->unk_380](this, globalCtx, linkAction);
        }
    }
}

s32 func_80A6121C(EnHorse* this, GlobalContext* globalCtx, EnHorseStruct3* arg2) {
    Vec3f sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;

    func_80A5B590(arg2->data, this->unk_204, &sp3C);
    Math3D_RotateXZPlane(&sp3C, arg2->data[this->unk_204].unk_8, &sp38, &sp34, &sp30);
    if ((this->unk_204 >= (arg2->count - 1)) && (Math3D_Vec3f_DistXYZ(&sp3C, &this->actor.posRot.pos) < DREG(8))) {
        this->unk_3A4 = this->unk_3A4 | 2;
    }

    if (((this->actor.posRot.pos.x * sp38) + (sp34 * this->actor.posRot.pos.z) + sp30) > 0.0f) {
        this->unk_204++;
        if (this->unk_204 >= arg2->count) {
            this->unk_3A4 |= 1;
            return 1;
        }
    }

    if ((this->unk_3A4 & 1) == 0) {
        func_80A5B5E0(this, globalCtx, &sp3C, 0x320);
    }

    this->actor.shape.rot.y = this->actor.posRot.rot.y;
    if ((this->actor.speedXZ < arg2->data[this->unk_204].unk_6) && ((this->unk_3A4 & 1) == 0)) {
        this->actor.speedXZ += 0.4f;
    } else {
        this->actor.speedXZ -= 0.4f;
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ = 0.0f;
        }
    }

    return 0;
}

void func_80A6140C(EnHorse* this) {
    this->unk_3A0 = 0;
    this->unk_218 = 0;
    this->unk_204 = 0;
    this->unk_3A8 = 0;
    this->actor.speedXZ = 0.0f;
    func_80A61440(this);
}

void func_80A61440(EnHorse* this) {
    s32 sp34 = 0;
    f32 sp30;

    this->unk_14C = 0x12;
    if (this->actor.speedXZ == 0.0f) {
        if (this->unk_210 != 0) {
            sp34 = 1;
        }
        this->unk_210 = 0;
    } else if (this->actor.speedXZ <= 3.0f) {
        if (this->unk_210 != 4) {
            sp34 = 1;
        }
        this->unk_210 = 4;
    } else if (this->actor.speedXZ <= 6.0f) {
        if (this->unk_210 != 5) {
            sp34 = 1;
        }
        this->unk_210 = 5;
    } else {
        if (this->unk_210 != 6) {
            sp34 = 1;
        }
        this->unk_210 = 6;
    }

    if (this->unk_210 == 4) {
        sp30 = this->actor.speedXZ * 0.5f;
    } else if (this->unk_210 == 5) {
        sp30 = this->actor.speedXZ * 0.25f;
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_RUN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        func_800AA000(0.0f, 0x3C, 8, 0xFF);
    } else if (this->unk_210 == 6) {
        sp30 = this->actor.speedXZ * 0.2f;
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_RUN, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        func_800AA000(0.0f, 0x78, 8, 0xFF);
    } else {
        sp30 = 1.0f;
    }

    if (sp34 == 1) {
        SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210],
                             (D_80A65E60[this->unk_210] * sp30) * 1.5f, 0,
                             SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2,
                             -3.0f);
    } else {
        SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210],
                             (D_80A65E60[this->unk_210] * sp30) * 1.5f, 0,
                             SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2, 0);
    }
}

void func_80A61778(EnHorse* this, GlobalContext* globalCtx) {
    f32 tmpf1;
    s32 sp20;

    if (this->unk_210 == 4) {
        func_80A5B9C8(this);
    }
    if (globalCtx->interfaceCtx.hbaAmmo == 0) {
        this->unk_3A8++;
    }

    sp20 = func_800F5A58(0x41);
    func_80A6121C(this, globalCtx, &D_80A66730);
    if ((((this->unk_3A4 & 1) != 0) || (this->unk_3A8 >= 0x2E)) && ((sp20 != 1) && (gSaveContext.minigameState != 3))) {
        gSaveContext.cutsceneIndex = 0;
        globalCtx->nextEntranceIndex = 0x3B0;
        globalCtx->sceneLoadFlag = 0x14;
        globalCtx->fadeTransition = 0x20;
    }

    if ((globalCtx->interfaceCtx.hbaAmmo != 0) && ((this->unk_3A4 & 2) == 0)) {
        if (gSaveContext.infTable[25] & 1) {
            if (gSaveContext.minigameScore >= 0x5DC) {
                this->unk_3A4 |= 4;
            }
        } else if (gSaveContext.minigameScore >= 0x3E8) {
            this->unk_3A4 |= 4;
        }
    }

    if ((globalCtx->interfaceCtx.hbaAmmo == 0) || ((this->unk_3A4 & 2) != 0)) {
        if ((this->unk_3A4 & 4) != 0) {
            this->unk_3A4 &= ~4;
            Audio_SetBGM(0x41);
        }
    }

    if (this->unk_3A0 == 0) {
        this->actor.speedXZ = 0.0f;
        if (this->unk_210 != 0) {
            func_80A61440(this);
        }
    }

    if (this->unk_210 == 4) {
        tmpf1 = this->actor.speedXZ * 0.5f;
    } else if (this->unk_210 == 5) {
        tmpf1 = this->actor.speedXZ * 0.25f;
    } else if (this->unk_210 == 6) {
        tmpf1 = this->actor.speedXZ * 0.2f;
    } else {
        tmpf1 = 1.0f;
    }

    this->unk_160.skelAnime.animPlaybackSpeed = tmpf1;
    if ((SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) ||
        ((this->unk_210 == 0) && (this->actor.speedXZ != 0.0f))) {
        func_80A61440(this);
    }
}

void func_80A61A04(EnHorse* this) {
    this->unk_14C = 0x13;
    this->unk_1F0 |= 0x10000;
    this->actor.speedXZ = 0.0f;
}

void func_80A61A28(EnHorse* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s32 sp4C;
    s32 ret;

    if ((DREG(53) != 0) || (this->unk_158 == 1)) {
        func_80A5F3DC(this);
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
    }

    sp58 = Math3D_Vec3f_DistXYZ(&this->actor.initPosRot.pos, &this->actor.posRot.pos);
    sp54 = Math3D_Vec3f_DistXYZ(&player->actor.posRot.pos, &this->actor.initPosRot.pos);
    sp50 = Math3D_Vec3f_DistXYZ(&player->actor.posRot.pos, &this->actor.posRot.pos);
    if (sp54 > 300.0f) {
        if (sp58 > 150.0f) {
            this->actor.speedXZ += 0.4f;
            if (this->actor.speedXZ > 8.0f) {
                this->actor.speedXZ = 8.0f;
            }
        } else {
            this->actor.speedXZ -= 0.47f;
            if (this->actor.speedXZ < 0.0f) {
                this->actor.speedXZ = 0.0f;
            }
        }
    } else if (sp50 < 300.0f) {
        this->actor.speedXZ += 0.4f;
        if (this->actor.speedXZ > 8.0f) {
            this->actor.speedXZ = 8.0f;
        }
    } else {
        this->actor.speedXZ -= 0.47f;
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ = 0.0f;
        }
    }

    if (this->actor.speedXZ >= 6.0f) {
        this->unk_160.skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.3f;
        sp4C = 6;
    } else if (this->actor.speedXZ >= 3.0f) {
        this->unk_160.skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.375f;
        sp4C = 5;
    } else if (this->actor.speedXZ > 0.1f) {
        this->unk_160.skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.75f;
        sp4C = 4;
        func_80A5B9C8(this);
    } else {
        sp4C = (Math_Rand_ZeroOne() > 0.5f) ? 1 : 0;
        func_80A5BC68(this, globalCtx);
        this->unk_160.skelAnime.animPlaybackSpeed = 1.0f;
    }

    if ((sp4C == 6) || (sp4C == 5) || (sp4C == 4)) {
        s16 sp46;
        if (sp54 < 300.0f) {
            sp46 = player->actor.shape.rot.y;
            sp46 += (((func_8002DA78(&this->actor, &player->actor) > 0) ? 1 : -1) * 16383);
        } else {
            sp46 = Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.initPosRot.pos) - this->actor.posRot.rot.y;
        }

        if (sp46 > 0x190) {
            this->actor.posRot.rot.y += 0x190;
        } else if (sp46 < -0x190) {
            this->actor.posRot.rot.y -= 0x190;
        } else {
            this->actor.posRot.rot.y += sp46;
        }
        this->actor.shape.rot.y = this->actor.posRot.rot.y;
    }

    ret = SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime);
    if (&this->actor.initPosRot) {};

    if (((this->unk_210 == 0) || (this->unk_210 == 1)) && ((sp4C == 6) || (sp4C == 5) || (sp4C == 4))) {
        this->unk_210 = sp4C;
        SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2,
                             -3.0f);
        if (this->unk_210 == 6) {
            func_80A5BACC(this);
        } else if (this->unk_210 == 5) {
            func_80A5BA84(this);
        }
        return;
    }

    if (ret != 0) {
        if (sp4C == 6) {
            func_80A5BACC(this);
        } else if (sp4C == 5) {
            func_80A5BA84(this);
        }

        if ((this->unk_210 == 0) || (this->unk_210 == 1)) {
            if (sp4C != this->unk_210) {
                this->unk_210 = sp4C;
                SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                                     SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader),
                                     2, -3.0f);
            } else {
                if (Math_Rand_ZeroOne() > 0.5f) {
                    this->unk_210 = 0;
                    this->unk_1F0 &= ~0x1000;
                } else {
                    this->unk_210 = 1;
                    this->unk_21C = this->unk_228;
                    if ((this->unk_1F0 & 0x8000000) != 0) {
                        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_GROAN, &this->unk_21C, 4, &D_801333E0, &D_801333E0,
                                               &D_801333E8);
                    }
                }
                SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                                     SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader),
                                     2, -3.0f);
            }
        } else if (this->unk_210 != sp4C) {
            this->unk_210 = sp4C;
            SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2,
                                 -3.0f);
        } else {
            SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2,
                                 0.0f);
        }
    } else if ((this->unk_210 == 4) && ((sp4C == 0) || (sp4C == 1))) {
        this->unk_210 = sp4C;
        SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2,
                             -3.0f);
    }
}

void func_80A62278(EnHorse* this, GlobalContext* globalCtx) {
    f32 tmp;

    func_80028A54(globalCtx, 25.0f, &this->actor.posRot.pos);
    this->unk_14C = 0x10;
    this->unk_1F0 |= 4;
    this->unk_210 = 8;
    tmp = this->unk_160.skelAnime.limbDrawTbl->y;
    tmp *= 0.01f;
    this->unk_3B0 = this->actor.posRot.pos;
    this->unk_3B0.y += tmp;
    this->unk_3C0 = (((D_80A665DC[this->unk_3AC].unk_10 + 48.7f) - this->unk_3B0.y) - -360.0f) / 30.0f;
    this->unk_1F0 |= 8;
    this->unk_258.y -= tmp;
    this->unk_3C4 = this->actor.posRot.rot.y - D_80A665DC[this->unk_3AC].unk_0A;
    this->unk_3BC = 0;
    this->actor.gravity = 0.0f;
    this->actor.speedXZ = 0;
    SkelAnime_ChangeAnim(&this->unk_160.skelAnime, D_80A65E58[this->unk_158][this->unk_210], 1.5f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80A65E58[this->unk_158][this->unk_210]->genericHeader), 2, -3.0f);
    this->unk_21C = this->unk_228;
    if ((this->unk_1F0 & 0x8000000) != 0) {
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    }
    Audio_PlaySoundGeneral(NA_SE_EV_HORSE_JUMP, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    func_800AA000(0.0f, 0xAA, 0xA, 0xA);
    this->actionFunc = NULL;
}

void func_80A624AC(EnHorse* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80A62278;
    if (this->unk_3AC == 0) {
        globalCtx->csCtx.segment = SEGMENTED_TO_VIRTUAL(&D_02002AC0);
        gSaveContext.cutsceneTrigger = 1;
    } else {
        globalCtx->csCtx.segment = SEGMENTED_TO_VIRTUAL(&D_02000230);
        gSaveContext.cutsceneTrigger = 1;
    }
}

void func_80A6255C(EnHorse* this, GlobalContext* globalCtx) {
    s16 tmp;
    f32 tmpf1 = (this->unk_3BC / 30.0f);
    f32 tmpf2 = SQ(this->unk_3BC);

    this->actor.posRot.pos.x = (tmpf1 * (D_80A665DC[this->unk_3AC].unk_0E - this->unk_3B0.x)) + this->unk_3B0.x;
    this->actor.posRot.pos.z = (tmpf1 * (D_80A665DC[this->unk_3AC].unk_12 - this->unk_3B0.z)) + this->unk_3B0.z;
    this->actor.posRot.pos.y = (this->unk_3B0.y + (this->unk_3C0 * this->unk_3BC)) + (-0.4f * tmpf2);

    tmp = ((1.0f - tmpf1) * this->unk_3C4) + D_80A665DC[this->unk_3AC].unk_0A;
    this->actor.shape.rot.y = tmp;
    this->actor.posRot.rot.y = tmp;
    this->unk_160.skelAnime.animCurrentFrame = 23.0f * tmpf1;
    SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime);
    if (this->unk_3BC < 30) {
        this->unk_1F0 |= 0x1000000;
    }
}

void func_80A626B8(EnHorse* this, GlobalContext* globalCtx) {
    this->actor.speedXZ = 8.0f;
    this->unk_160.skelAnime.animPlaybackSpeed = 1.5f;
    if (SkelAnime_FrameUpdateMatrix(&this->unk_160.skelAnime) != 0) {
        this->unk_1F0 &= ~4;
        this->actor.gravity = -3.5f;
        this->actor.posRot.pos.y = D_80A665DC[this->unk_3AC].unk_10;
        func_80028A54(globalCtx, 25.0f, &this->actor.posRot.pos);
        func_80A5DDB0(this, globalCtx);
        Audio_PlaySoundGeneral(NA_SE_EV_HORSE_LAND, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                               &D_801333E8);
        func_800AA000(0.0f, 0xFF, 0xA, 0x50);
    }
}

void func_80A627A4(EnHorse* this, GlobalContext* globalCtx) {
    this->unk_3BC++;
    if (this->unk_3BC < 30) {
        func_80A6255C(this, globalCtx);
    } else {
        func_80A626B8(this, globalCtx);
    }
}

void func_80A627E8(Vec3f* arg0, s16 arg1, f32 arg2, f32 arg3, Vec3f* arg4) {
    arg4->x = (Math_Sins(arg1) * arg2) + arg0->x;
    arg4->y = arg0->y + arg3;
    arg4->z = (Math_Coss(arg1) * arg2) + arg0->z;
}

s32 func_80A62868(EnHorse* this, GlobalContext* globalCtx, Vec3f* arg2, CollisionPoly** arg3, f32* arg4) {
    s32 sp3C;
    f32 sp38;
    WaterBox* sp34;

    *arg3 = NULL;
    *arg4 = func_8003C940(&globalCtx->colCtx, arg3, &sp3C, arg2);
    if (*arg4 == -32000.0f) {
        return 1;
    }

    if ((func_80042244(globalCtx, &globalCtx->colCtx, arg2->x, arg2->z, &sp38, &sp34) == 1) && (*arg4 < sp38)) {
        return 2;
    }

    if ((((*arg3)->norm.y * 0.00003051851f) < 0.81915206f) || (func_80041EEC(&globalCtx->colCtx, *arg3, sp3C) != 0) ||
        (func_80041D4C(&globalCtx->colCtx, *arg3, sp3C) == 7)) {
        return 3;
    }
    return 0;
}

void func_80A629A4(EnHorse* this, GlobalContext* globalCtx, s32 arg2, s32 arg3) {
    if ((this->unk_14C != 0x11) && (func_80A5B2F0(this, globalCtx) == 0)) {
        this->actor.posRot.pos = this->unk_1F4;
        this->unk_1F0 |= 0x4000;
        this->actor.shape.rot.y = this->unk_200;
        this->actor.posRot.rot.y = this->unk_200;
        if (this->unk_20C == 0) {
            if (this->unk_210 != 3) {
                return;
            }
        } else if (this->unk_14C != 0xB) {
            if ((this->unk_1F0 & 4) != 0) {
                this->unk_1F0 &= ~4;
                this->actor.gravity = -3.5f;
                this->actor.posRot.pos.y = this->actor.groundY;
            }
            if ((arg2 == 1) || (arg2 == 4)) {
                this->unk_1F0 |= 0x10;
            } else if ((arg2 == 2) || (arg2 == 5)) {
                this->unk_1F0 |= 0x20;
            }

            if (arg3 == 1) {
                func_80A5E00C(this);
            }
        }
    }
}

void func_80A62ACC(EnHorse* this, GlobalContext* globalCtx) {
    s32 pad84;
    CollisionPoly* sp80;
    CollisionPoly* sp7C;
    s16 sp7A;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    s32 sp44;
    s32 ret;
    f32 sp3C;
    WaterBox* sp38;
    f32 fret;

    sp44 = this->actor.speedXZ > 8.0f;
    ret =
        func_80042244(globalCtx, &globalCtx->colCtx, this->actor.posRot.pos.x, this->actor.posRot.pos.z, &sp3C, &sp38);
    if ((ret == 1) && (this->actor.groundY < sp3C)) {
        func_80A629A4(this, globalCtx, 1, sp44);
        return;
    }

    func_80A627E8(&this->actor.posRot.pos, this->actor.shape.rot.y, 30.0f, 60.0f, &sp6C);
    ret = func_80A62868(this, globalCtx, &sp6C, &sp80, &this->unk_248);
    if (ret == 1) {
        this->actor.shape.rot.x = 0;
        func_80A629A4(this, globalCtx, 4, sp44);
        return;
    } else if (ret == 2) {
        func_80A629A4(this, globalCtx, 4, sp44);
        return;
    } else if (ret == 3) {
        func_80A629A4(this, globalCtx, 4, sp44);
        return;
    }

    func_80A627E8(&this->actor.posRot.pos, this->actor.shape.rot.y, -30.0f, 60.0f, &sp60);
    ret = func_80A62868(this, globalCtx, &sp60, &sp7C, &this->unk_24C);
    if (ret == 1) {
        this->actor.shape.rot.x = 0;
        func_80A629A4(this, globalCtx, 5, sp44);
        return;
    } else if (ret == 2) {
        func_80A629A4(this, globalCtx, 5, sp44);
        return;
    } else if (ret == 3) {
        func_80A629A4(this, globalCtx, 5, sp44);
        return;
    }

    sp7A = Math_atan2f(this->unk_24C - this->unk_248, 60.0f) * 10430.378f;
    if (this->actor.floorPoly != NULL) {
        sp50 = this->actor.floorPoly->norm.x * 0.00003051851f;
        sp4C = this->actor.floorPoly->norm.y * 0.00003051851f;
        sp48 = this->actor.floorPoly->norm.z * 0.00003051851f;
        sp54 = sp6C;
        sp54.y = this->unk_248;
        fret = Math3D_DistPlaneToPos(sp50, sp4C, sp48, this->actor.floorPoly->dist, &sp54);
        if (((this->actor.floorPoly != sp80) && (this->actor.speedXZ >= 0.0f)) &&
            ((((this->unk_1F0 & 4) == 0) && (fret < -40.0f)) || (((this->unk_1F0 & 4) != 0) && (fret < -200.0f)))) {
            func_80A629A4(this, globalCtx, 4, sp44);
            return;
        }

        sp54 = sp60;
        sp54.y = this->unk_24C;
        fret = Math3D_DistPlaneToPos(sp50, sp4C, sp48, this->actor.floorPoly->dist, &sp54);
        if (((sp7C != this->actor.floorPoly) && (this->actor.speedXZ <= 0.0f) && ((this->unk_1F0 & 4) == 0) &&
             (fret < -40.0f)) ||
            (((this->unk_1F0 & 4) != 0) && (fret < -200.0f))) {
            func_80A629A4(this, globalCtx, 5, sp44);
            return;
        }

        if ((sp4C < 0.81915206f) ||
            (func_80041EEC(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorPolySource) != 0) ||
            (func_80041D4C(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorPolySource) == 7)) {
            if (this->actor.speedXZ >= 0.0f) {
                func_80A629A4(this, globalCtx, 4, sp44);
            } else {
                func_80A629A4(this, globalCtx, 5, sp44);
            }
            return;
        }

        if ((this->unk_1F0 & 4) != 0) {
            this->actor.shape.rot.x = 0;
        } else if ((this->actor.groundY + 4.0f) < this->actor.posRot.pos.y) {
            this->actor.shape.rot.x = 0;
        } else if (!(fabsf(sp7A) > 8191.0f)) {
            this->actor.shape.rot.x = sp7A;
            this->actor.shape.unk_08 =
                (this->unk_248 + (((this->unk_24C - this->unk_248) * 20.0f) / 45.0f)) - this->actor.groundY;
        }
    }
}

void func_80A6304C(EnHorse* this, GlobalContext* globalCtx) {
    s32 pad2[3];
    Player* player = PLAYER;
    s32 ret = func_80A65014(this, globalCtx);

    if ((ret != 0) && ((this->unk_1F0 & 0x10000) == 0) && (player->rideActor == NULL)) {
        func_8002F63C(globalCtx, &this->actor, ret);
    }

    if ((this->unk_20C == 0) && (func_8002F618(globalCtx, &this->actor) == 1)) {
        this->unk_150 = 0x37;
        this->unk_154 = 0x37;
        this->unk_20C = 1;
        func_80A5C8FC(this);
    } else if ((this->unk_20C == 1) && (func_8002F674(globalCtx, &this->actor) == 1)) {
        this->unk_150 = 0x23;
        this->unk_154 = 0x23;
        this->unk_1F0 &= ~0x10000;
        this->unk_20C = 0;
        func_80A5C8FC(this);
    }
}

void func_80A63148(EnHorsePadXY* pad, f32* arg1, s16* arg2) {
    *arg1 = sqrtf(SQ(pad->x) + SQ(pad->y));
    *arg1 = CLAMP_MAX(*arg1, 60.0f);
    *arg2 = Math_atan2f(-pad->x, pad->y) * 10430.378f;
}

void func_80A631D4(EnHorse* this, GlobalContext* globalCtx) {
    this->pad2 = this->pad1;
    this->pad1.x = globalCtx->state.input[0].rel.in.x;
    this->pad1.y = globalCtx->state.input[0].rel.in.y;
}

void func_80A63210(EnHorse* this, GlobalContext* globalCtx, CollisionPoly* arg2) {
    s32 pad;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 temp_f2;
    f32 tmpf1;
    f32 tmpf2;

    sp40 = arg2->norm.x * 0.00003051851f;
    sp3C = arg2->norm.y * 0.00003051851f;
    sp38 = arg2->norm.z * 0.00003051851f;
    if (!(Math_Coss((this->actor.posRot.rot.y - (s16)(Math_atan2f(arg2->norm.x, arg2->norm.z) * 10430.378f)) - 0x7FFF) <
          0.7071f)) {
        tmpf1 = Math3D_DistPlaneToPos(sp40, sp3C, sp38, arg2->dist, &this->actor.posRot.pos);
        tmpf2 = sqrtf(SQ(sp40) + SQ(sp38));
        temp_f2 = (30.0f - tmpf1) * (1.0f / tmpf2);
        this->actor.posRot.pos.x += temp_f2 * sp40;
        this->actor.posRot.pos.z += temp_f2 * sp38;
    }
}

void func_80A63364(EnHorse* this, GlobalContext* globalCtx) {
    f32 sp6C = (globalCtx->sceneNum == SCENE_SPOT20) ? 19.0f : 40.0f;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;
    CollisionPoly* sp44;
    s32 sp40;

    Math_Vec3f_Copy(&sp60, &this->actor.posRot.pos);
    sp60.y += sp6C;
    Math_Vec3f_Copy(&sp54, &sp60);
    sp54.x += 30.0f * Math_Sins(this->actor.posRot.rot.y);
    sp54.y += 30.0f * Math_Sins(-this->actor.shape.rot.x);
    sp54.z += 30.0f * Math_Coss(this->actor.posRot.rot.y);
    if (func_8003DE84(&globalCtx->colCtx, &sp60, &sp54, &sp48, &sp44, 1, 0, 0, 1, &sp40) != 0) {
        func_80A63210(this, globalCtx, sp44);
    }
}

#ifdef NON_MATCHING
// posRot.pos saved at 0x40 rather than 0x44 on the stack
// 0x40 isn't shown, optimised out?
// Likely due to the bottom block ,see the if (0)
void func_80A634A0(EnHorse* this, GlobalContext* globalCtx) {
    s32 pad[2];
    Vec3f spAC;
    Vec3f spA0;
    Vec3f sp94;
    s32 pad2;
    f32 sp8C;
    CollisionPoly* sp88 = NULL;
    CollisionPoly* sp84 = NULL;
    s32 sp80;
    f32 sp7C;
    f32 sp78;
    s32 pad3;
    s32 sp70;
    DynaPolyActor* refDyna;
    f32 normY;
    Vec3f sp5C;
    Vec3f sp50;

    func_8002E4B4(globalCtx, &this->actor, (globalCtx->sceneNum == SCENE_SPOT20) ? 19.0f : 40.0f, 35.0f, 100.0f, 0x1D);
    if (func_80A5B2F0(this, globalCtx) == 0) {
        if ((this->actor.bgCheckFlags & 8) && (Math_Coss(this->actor.wallPolyRot - this->actor.posRot.rot.y) < -0.3f) &&
            (this->actor.speedXZ > 4.0f)) {
            this->actor.speedXZ -= 1.0f;
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_SANDDUST, &this->actor.projectedPos, 4, &D_801333E0, &D_801333E0,
                                   &D_801333E8);
        }

        if (((this->unk_1F0 & 4) == 0) && (this->unk_20C != 0) && !(this->actor.speedXZ < 0.0f) &&
            (this->unk_14C != 0xC) && (this->unk_14C != 0xB)) {
            s32 tmpret;
            if (this->actor.speedXZ > 8.0f) {
                if (this->actor.speedXZ < 12.8f) {
                    sp70 = 0;
                    sp8C = 160.0f;
                } else {
                    sp8C = 230.0f;
                    sp70 = 1;
                }
            } else {
                func_80A63364(this, globalCtx);
                return;
            }

            spAC = this->actor.posRot.pos;
            spAC.y += 19.0f;
            spA0 = spAC;
            spA0.x += sp8C * Math_Sins(this->actor.posRot.rot.y);
            spA0.y += sp8C * Math_Sins(-this->actor.shape.rot.x);
            spA0.z += sp8C * Math_Coss(this->actor.posRot.rot.y);
            sp5C = spA0;
            sp88 = NULL;
            tmpret = func_8003DE84(&globalCtx->colCtx, &spAC, &spA0, &sp5C, &sp88, 1, 0, 0, 1, &sp80);
            if (tmpret == 1) {
                sp8C = sqrt(Math3D_Vec3fDistSq(&spAC, &sp5C));
                this->unk_1F0 |= 0x4000;
            }

            if (sp88 != NULL) {
                if (sp8C < 30.0f) {
                    func_80A63210(this, globalCtx, sp88);
                }

                if ((Math_Coss(
                         (this->actor.posRot.rot.y - (s16)(Math_atan2f(sp88->norm.x, sp88->norm.z) * 10430.378f)) -
                         0x7FFF) < 0.5f) ||
                    (func_80041EEC(&globalCtx->colCtx, sp88, sp80) != 0)) {
                    return;
                }

                if (((sp70 == 0) && (sp8C < 80.0f)) || ((sp70 == 1) && (sp8C < 150.0f))) {
                    if (sp70 == 0) {
                        this->unk_1F0 |= 0x10;
                    } else if (sp70 == 1) {
                        this->unk_1F0 |= 0x10;
                        func_80A5E2A8(this, globalCtx);
                    }
                    return;
                } else {
                    refDyna = DynaPolyInfo_GetActor(&globalCtx->colCtx, sp80);

                    if ((this->unk_1F0 & 0x4000000) != 0) {
                        if (((refDyna != NULL) && (refDyna->actor.id != ACTOR_BG_UMAJUMP)) || (refDyna == NULL)) {

                            if (sp70 == 0) {
                                this->unk_1F0 |= 0x10;
                            } else if (sp70 == 1) {
                                this->unk_1F0 |= 0x10;
                                func_80A5E2A8(this, globalCtx);
                            }
                            return;
                        }
                    }
                }
            }

            sp8C += 5.0f;
            sp94 = spAC;
            sp94.x += sp8C * Math_Sins(this->actor.posRot.rot.y);
            sp94.y = this->actor.posRot.pos.y + 120.0f;
            sp94.z += sp8C * Math_Coss(this->actor.posRot.rot.y);
            sp50 = sp94;
            sp50.y = func_8003C940(&globalCtx->colCtx, &sp84, &sp80, &sp94);
            if (sp50.y != -32000.0f) {
                sp7C = sp50.y - this->actor.posRot.pos.y;
                if ((this->actor.floorPoly != NULL) && (sp84 != NULL)) {
                    if ((Math3D_DistPlaneToPos(this->actor.floorPoly->norm.x * 0.00003051851f,
                                               this->actor.floorPoly->norm.y * 0.00003051851f,
                                               this->actor.floorPoly->norm.z * 0.00003051851f,
                                               this->actor.floorPoly->dist, &sp50) < -40.0f) &&
                        (Math3D_DistPlaneToPos(sp84->norm.x * 0.00003051851f, sp84->norm.y * 0.00003051851f,
                                               sp84->norm.z * 0.00003051851f, sp84->dist,
                                               &this->actor.posRot.pos) > 40.0f)) {
                        if ((sp70 == 1) && (this->unk_14C != 0xC)) {
                            this->unk_1F0 = this->unk_1F0 | 0x10;
                            func_80A5E2A8(this, globalCtx);
                        }
                        this->unk_1F0 |= 0x4000;
                        return;
                    }

                    normY = sp84->norm.y * 0.00003051851f;
                    if ((normY < 0.81915206f) || (func_80041EEC(&globalCtx->colCtx, sp84, sp80) != 0) ||
                        (func_80041D4C(&globalCtx->colCtx, sp84, sp80) == 7)) {
                        if ((sp70 == 1) && (this->unk_14C != 0xC)) {
                            this->unk_1F0 |= 0x10;
                            func_80A5E2A8(this, globalCtx);
                            return;
                        }
                    } else if ((sp88 != NULL) && !(sp50.y < sp5C.y) && ((this->unk_1F0 & 0x20000) == 0)) {
                        sp94 = spAC;
                        sp94.y = this->actor.posRot.pos.y + 120.0f;
                        if (sp70 == 0) {
                            sp94.x += 276.0f * Math_Sins(this->actor.posRot.rot.y);
                            sp94.z += 276.0f * Math_Coss(this->actor.posRot.rot.y);
                        } else {
                            sp94.x += 390.0f * Math_Sins(this->actor.posRot.rot.y);
                            sp94.z += 390.0f * Math_Coss(this->actor.posRot.rot.y);
                        }

                        sp50 = sp94;
                        sp50.y = func_8003C940(&globalCtx->colCtx, &sp84, &sp80, &sp94);
                        if (sp50.y != -32000.0f) {
                            sp78 = sp50.y - this->actor.posRot.pos.y;
                            if (sp84 != NULL) {
                                if (0) {};
                                normY = sp84->norm.y * 0.00003051851f;
                                if ((normY < 0.81915206f) || (func_80041EEC(&globalCtx->colCtx, sp84, sp80) != 0) ||
                                    (func_80041D4C(&globalCtx->colCtx, sp84, sp80) == 7)) {
                                    if ((sp70 == 1) && (this->unk_14C != 0xC)) {
                                        this->unk_1F0 |= 0x10;
                                        func_80A5E2A8(this, globalCtx);
                                    }
                                } else if (sp78 < -DREG(4)) {
                                    if ((sp70 == 1) && (this->unk_14C != 0xC)) {
                                        this->unk_1F0 |= 0x10;
                                        func_80A5E2A8(this, globalCtx);
                                    }
                                } else if ((sp70 == 0) && (sp7C > 19.0f) && (sp7C <= 40.0f)) {
                                    func_80A5EB4C(this);
                                    this->actionFunc = func_80A5E9F8;
                                } else if (((sp70 == 1) && (this->actor.speedXZ < 13.8f) && (sp7C > 19.0f) &&
                                            (sp7C <= 72.0f)) ||
                                           ((this->actor.speedXZ > 13.8f) && (sp7C <= 112.0f))) {
                                    func_80A5EE78(this);
                                    this->actionFunc = func_80A5ED18;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Horse/func_80A634A0.s")
#endif

void func_80A63FA8(EnHorse* this, GlobalContext* globalCtx) {
    s32 pad[3];

    if (((this->unk_14C == 8) || (this->unk_14C == 9) || (this->unk_14C == 10)) &&
        CHECK_PAD(globalCtx->state.input[0].press, A_BUTTON) && (globalCtx->interfaceCtx.unk_1EE == 8) &&
        ((this->unk_1F0 & 1) == 0) && ((this->unk_1F0 & 0x100) == 0) && ((this->unk_1F0 & 0x200) == 0)) {
        if (this->unk_238 > 0) {
            func_800AA000(0.0f, 0xB4, 0x14, 0x64);
            this->unk_1F0 |= 1;
            this->unk_1F0 |= 0x400000;
            this->unk_1F0 |= 0x100;
            this->unk_238--;
            this->unk_240 = 0;
            if (this->unk_238 == 0) {
                this->unk_23C = 0x8C;
            } else if (this->unk_158 == 0) {
                if ((this->unk_1F0 & 0x400000) != 0) {
                    this->unk_23C = 0x3C;
                    this->unk_1F0 &= ~0x400000;
                } else {
                    this->unk_23C = 8;
                }
            } else {
                this->unk_23C = 0x46;
            }
        } else {
            this->unk_21C = this->unk_228;
            if (((this->unk_1F0 & 0x8000000) != 0) && (Math_Rand_ZeroOne() < 0.1f)) {
                Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            }
        }
    }
    if (this) {};
}

void func_80A64150(EnHorse* this, GlobalContext* globalCtx) {
    u8 flag;

    if ((this->unk_238 < 6) && (this->unk_238 > 0)) {
        this->unk_23C--;
        this->unk_240++;
        if (this->unk_23C <= 0) {
            this->unk_238++;

            if (((this->unk_14C == 5) || (this->unk_14C == 0) || (this->unk_14C == 6)) &&
                (((this->unk_1F0 & 0x80000) == 0) && ((this->unk_1F0 & 0x2000000) == 0))) {
                flag = true;
            } else {
                flag = false;
            }

            if (!flag) {
                Audio_PlaySoundGeneral(NA_SE_SY_CARROT_RECOVER, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            }

            if (this->unk_238 < 6) {
                this->unk_23C = 0xB;
            }
        }
    } else if (this->unk_238 == 0) {
        this->unk_23C--;
        this->unk_240++;
        if (this->unk_23C <= 0) {
            this->unk_23C = 0;
            this->unk_238 = 6;

            if (((this->unk_14C == 5) || (this->unk_14C == 0) || (this->unk_14C == 6)) &&
                (((this->unk_1F0 & 0x80000) == 0) && ((this->unk_1F0 & 0x2000000) == 0))) {
                flag = true;
            } else {
                flag = false;
            }

            if (!flag) {
                Audio_PlaySoundGeneral(NA_SE_SY_CARROT_RECOVER, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            }
        }
    }

    if ((this->unk_240 == 8) && (Math_Rand_ZeroOne() < 0.25f)) {
        this->unk_21C = this->unk_228;
        if ((this->unk_1F0 & 0x8000000) != 0) {
            Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
        }
    }

    globalCtx->interfaceCtx.unk_23A = this->unk_238;
}

void func_80A6437C(EnHorse* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 ret = func_8002DA78(&this->actor, &PLAYER->actor) - this->actor.posRot.rot.y;
    f32 sins = Math_Sins(ret);
    f32 coss = Math_Coss(ret);

    if (sins > 0.8660254f) {
        this->unk_370 = 5;
    } else if (sins < -0.8660254f) {
        this->unk_370 = 4;
    } else if (coss > 0) {
        this->unk_370 = (sins > 0.0f) ? 1 : 0;
    } else if (sins > 0.0f) {
        this->unk_370 = 3;
    } else {
        this->unk_370 = 2;
    }
}

void func_80A64480(EnHorse* this, GlobalContext* globalCtx) {
    f32 tmpf1 = this->actor.speedXZ / this->unk_208;
    s16 tmp = this->actor.shape.rot.y - this->unk_200;
    s16 tmp2 = (1820.0f * tmpf1) * (tmp / 480.00003f);
    f32 tmpf2 = -tmp2 - this->actor.posRot.rot.z;

    if (fabsf(-tmp2) < 100.0f) {
        this->actor.posRot.rot.z = 0;
    } else if (fabsf(tmpf2) < 100.0f) {
        this->actor.posRot.rot.z = -tmp2;
    } else if (tmpf2 > 0.0f) {
        this->actor.posRot.rot.z += 100;
    } else {
        this->actor.posRot.rot.z -= 100;
    }

    this->actor.shape.rot.z = this->actor.posRot.rot.z;
}

s32 func_80A64578(EnHorse* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 ret;

    if ((this->actor.floorPoly == 0) && (player->rideActor != &this->actor)) {
        return 0;
    }

    ret = func_800420E4(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorPolySource) * 1024;
    ret -= this->actor.posRot.rot.y;

    if (ret > 800.0f) {
        this->actor.posRot.rot.y += 800.0f;
    } else if (ret < -800.0f) {
        this->actor.posRot.rot.y -= 800.0f;
    } else {
        this->actor.posRot.rot.y += ret;
    }

    this->actor.shape.rot.y = this->actor.posRot.rot.y;
    return 1;
}

s32 func_80A6467C(f32 arg0) {
    return Math_Rand_ZeroOne() * arg0;
}

void EnHorse_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHorse* this = THIS;
    Vec3f* pos = &this->actor.posRot.pos;
    Vec3f sp5C = D_80A66788;
    Vec3f sp50 = D_80A66794;
    Player* player = PLAYER;

    this->unk_200 = this->actor.shape.rot.y;
    func_80A631D4(this, globalCtx);
    func_80A6437C(this, globalCtx);
    if ((this->unk_1F0 & 0x2000) == 0) {
        func_80A6304C(this, globalCtx);
    }

    if ((this->unk_1F0 & 0x80000) != 0) {
        if (((this->unk_1F0 & 0x100000) != 0) && (this->unk_388 == 1)) {
            this->unk_1F0 &= ~0x100000;
            func_80A5E00C(this);
        } else if (((this->unk_1F0 & 0x100000) == 0) && ((this->unk_1F0 & 0x200000) != 0) && (this->unk_14C != 0xB) &&
                   (this->unk_388 == 1)) {
            this->unk_1F0 &= ~0x200000;
            func_80A5E00C(this);
        }
    }

    D_80A66738[this->unk_14C](this, globalCtx);
    this->unk_1F0 &= ~0x4000;
    this->unk_214 = this->unk_160.skelAnime.animCurrentFrame;
    this->unk_1F4 = *pos;
    if ((this->unk_1F0 & 0x2000) == 0) {
        if (((this->unk_14C == 0xA) || (this->unk_14C == 9)) || (this->unk_14C == 8)) {
            func_80A63FA8(this, globalCtx);
        }

        if (this->unk_20C == 1) {
            func_80A64150(this, globalCtx);
        }

        Actor_MoveForward(&this->actor);
        if ((this->unk_14C == 4) && (this->unk_38C != NULL)) {
            this->unk_38C->actor.posRot.pos.x = this->actor.posRot.pos.x;
            this->unk_38C->actor.posRot.pos.y = this->actor.posRot.pos.y + 10.0f;
            this->unk_38C->actor.posRot.pos.z = this->actor.posRot.pos.z;
            this->unk_38C->actor.shape.rot.x = this->actor.shape.rot.x;
            this->unk_38C->actor.shape.rot.y = this->actor.shape.rot.y;
        }

        if ((this->collider3.list->body.ocFlags & 2) && (this->actor.speedXZ > 6.0f)) {
            this->actor.speedXZ -= 1.0f;
        }

        if (this->collider3.base.acFlags & 2) {
            this->unk_21C = this->unk_228;
            if ((this->unk_1F0 & 0x8000000) != 0) {
                Audio_PlaySoundGeneral(NA_SE_EV_HORSE_NEIGH, &this->unk_21C, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            }
        }

        if (this->unk_14C != 4) {
            func_80A64480(this, globalCtx);
        }

        Collider_CylinderUpdate(&this->actor, &this->collider1);
        Collider_CylinderUpdate(&this->actor, &this->collider2);
        this->collider1.dim.pos.x = this->collider1.dim.pos.x + (s16)(Math_Sins(this->actor.shape.rot.y) * 11.0f);
        this->collider1.dim.pos.z = this->collider1.dim.pos.z + (s16)(Math_Coss(this->actor.shape.rot.y) * 11.0f);
        this->collider2.dim.pos.x = this->collider2.dim.pos.x + (s16)(Math_Sins(this->actor.shape.rot.y) * -18.0f);
        this->collider2.dim.pos.z = this->collider2.dim.pos.z + (s16)(Math_Coss(this->actor.shape.rot.y) * -18.0f);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        if ((player->stateFlags1 & 1) && (player->rideActor != NULL) &&
            ((globalCtx->sceneNum != SCENE_SPOT20) ||
             ((globalCtx->sceneNum == SCENE_SPOT20) && (this->actor.posRot.pos.z < -2400.0f)))) {
            func_80A64578(this, globalCtx);
        }

        if ((this->unk_1F0 & 0x1000000) == 0) {
            func_80A634A0(this, globalCtx);
            func_80A62ACC(this, globalCtx);
            if ((this->actor.posRot.pos.y < this->unk_248) && (this->actor.posRot.pos.y < this->unk_24C)) {
                if (this->unk_24C < this->unk_248) {
                    this->actor.posRot.pos.y = this->unk_24C;
                } else {
                    this->actor.posRot.pos.y = this->unk_248;
                }
            }
        } else {
            this->unk_1F0 &= ~0x1000000;
        }

        if ((globalCtx->sceneNum == SCENE_SPOT09) && ((gSaveContext.eventChkInf[9] & 0xF) != 0xF)) {
            func_80A5B450(this, globalCtx);
        }

        this->actor.posRot2.pos = this->actor.posRot.pos;
        this->actor.posRot2.pos.y += 70.0f;

        if ((Math_Rand_ZeroOne() < 0.025f) && (this->unk_37A == 0)) {
            this->unk_37A++;
        } else if (this->unk_37A > 0) {
            this->unk_37A++;
            if (this->unk_37A >= 4) {
                this->unk_37A = 0;
            }
        }

        if ((this->actor.speedXZ == 0.0f) && ((this->unk_1F0 & 0x80000) == 0)) {
            this->actor.colChkInfo.mass = 0xFF;
        } else {
            this->actor.colChkInfo.mass = 0xFE;
        }

        if (this->actor.speedXZ >= 5.0f) {
            this->collider1.base.atFlags |= 1;
        } else {
            this->collider1.base.atFlags &= ~1;
        }

        if ((gSaveContext.entranceIndex != 0x157) || (gSaveContext.sceneSetupIndex != 9)) {
            if ((this->unk_3C8 & 1) != 0) {
                this->unk_3C8 &= ~1;
                func_800287AC(globalCtx, &this->unk_3CC, &sp50, &sp5C, func_80A6467C(100.0f) + 200,
                              func_80A6467C(10.0f) + 30, func_80A6467C(20.0f) + 30);
            } else if ((this->unk_3C8 & 2) != 0) {
                this->unk_3C8 &= ~2;
                func_800287AC(globalCtx, &this->unk_3D8, &sp50, &sp5C, func_80A6467C(100.0f) + 200,
                              func_80A6467C(10.0f) + 30, func_80A6467C(20.0f) + 30);
            } else if ((this->unk_3C8 & 4) != 0) {
                this->unk_3C8 &= ~4;
                func_800287AC(globalCtx, &this->unk_3E4, &sp50, &sp5C, func_80A6467C(100.0f) + 200,
                              func_80A6467C(10.0f) + 30, func_80A6467C(20.0f) + 30);
            } else if ((this->unk_3C8 & 8) != 0) {
                this->unk_3C8 &= ~8;
                func_800287AC(globalCtx, &this->unk_3F0, &sp50, &sp5C, func_80A6467C(100.0f) + 200,
                              func_80A6467C(10.0f) + 30, func_80A6467C(20.0f) + 30);
            }
        }

        this->unk_1F0 &= ~0x8000000;
    }
}

s32 func_80A64ED4(EnHorse* this, GlobalContext* globalCtx, Player* player) {
    if (this->unk_370 == 5) {
        return -1;
    } else if (this->unk_370 == 4) {
        return 1;
    }

    return 0;
}

s32 func_80A64F14(EnHorse* this, GlobalContext* globalCtx, Player* player) {
    s32 ret;

    if (func_8002DB8C(&this->actor, &player->actor) > 75.0f) {
        return 0;
    }

    if (fabsf(this->actor.posRot.pos.y - player->actor.posRot.pos.y) > 30.0f) {
        return 0;
    }

    if (Math_Coss(func_8002DA78(&player->actor, &this->actor) - player->actor.posRot.rot.y) < 0.17364818f) {
        return 0;
    }

    ret = func_80A64ED4(this, globalCtx, player);
    if (ret == -1) {
        return -1;
    } else if (ret == 1) {
        return 1;
    }

    return 0;
}

s32 func_80A65014(EnHorse* this, GlobalContext* globalCtx) {
    if (this->unk_14C != 2) {
        return 0;
    }

    if ((this->unk_210 != 0) && (this->unk_210 != 1)) {
        return 0;
    }

    return func_80A64F14(this, globalCtx, PLAYER);
}

void func_80A6506C(Vec3f* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = ((Math_Rand_ZeroOne() * (arg1 + arg1)) + arg0->x) - arg1;
    arg2->y = ((Math_Rand_ZeroOne() * (arg1 + arg1)) + arg0->y) - arg1;
    arg2->z = ((Math_Rand_ZeroOne() * (arg1 + arg1)) + arg0->z) - arg1;
}

void func_80A65108(Actor* thisx, GlobalContext* globalCtx, HorseStruct* horse) {
    EnHorse* this = THIS;
    s32 pad;
    Vec3f sp94 = D_80A667A0;
    Vec3f sp88 = D_80A667AC;
    Vec3f sp7C = D_80A667B8;
    Vec3f sp70;
    Vec3f sp64 = D_80A667C4;
    Vec3f sp58 = D_80A667D0;
    f32 sp54;
    Vec3f sp48;
    Vec3f sp3C;
    s32 i;
    Vec3f sp2C;
    f32 sp28;

    sp54 = this->unk_160.skelAnime.animCurrentFrame;
    if ((this->unk_1F0 & 8) == 0) {
        func_800A6408(horse, 30, &sp7C, &this->unk_258);
        this->unk_258.x -= this->actor.posRot.pos.x;
        this->unk_258.y -= this->actor.posRot.pos.y;
        this->unk_258.z -= this->actor.posRot.pos.z;
    } else {
        this->unk_1F0 &= ~8;
    }

    func_800A6408(horse, 0xD, &sp94, &sp2C);
    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->mf_11D60, &sp2C, &this->unk_228, &sp28);

    if (((this->unk_210 == 0) && (this->unk_14C != 0)) &&
        ((((sp54 > 40.0f) && (sp54 < 45.0f) && (this->unk_158 == 0)) ||
          ((sp54 > 28.0f) && (sp54 < 33.0f) && (this->unk_158 == 1))))) {
        if (Math_Rand_ZeroOne() < 0.6f) {
            this->unk_3C8 |= 1;
            func_800A6408(horse, 0x1C, &sp88, &this->unk_3CC);
            this->unk_3CC.y -= 5.0f;
        }
    } else if (this->unk_14C == 0xC) {
        if (((sp54 > 10.0f) && (sp54 < 13.0f)) || ((sp54 > 25.0f) && (sp54 < 33.0f))) {
            if (Math_Rand_ZeroOne() < 0.7f) {
                this->unk_3C8 |= 2;
                func_800A6408(horse, 20, &sp88, &sp70);
                func_80A6506C(&sp70, 10.0f, &this->unk_3D8);
            }
            if (Math_Rand_ZeroOne() < 0.7f) {
                this->unk_3C8 |= 1;
                func_800A6408(horse, 28, &sp88, &sp70);
                func_80A6506C(&sp70, 10.0f, &this->unk_3CC);
            }
        }

        if (((sp54 > 6.0f) && (sp54 < 10.0f)) || ((sp54 > 23.0f) && (sp54 < 29.0f))) {
            if (Math_Rand_ZeroOne() < 0.7f) {
                this->unk_3C8 |= 8;
                func_800A6408(horse, 0x25, &sp88, &sp70);
                func_80A6506C(&sp70, 10.0f, &this->unk_3F0);
            }
        }

        if (((sp54 > 7.0f) && (sp54 < 14.0f)) || ((sp54 > 26.0f) && (sp54 < 30.0f))) {
            if (Math_Rand_ZeroOne() < 0.7f) {
                this->unk_3C8 |= 4;
                func_800A6408(horse, 0x2D, &sp88, &sp70);
                func_80A6506C(&sp70, 10.0f, &this->unk_3E4);
            }
        }
    } else if (this->unk_210 == 6) {
        if ((sp54 > 14.0f) && (sp54 < 16.0f)) {
            this->unk_3C8 |= 1;
            func_800A6408(horse, 0x1C, &sp88, &sp70);
            func_80A6506C(&sp70, 5.0f, &this->unk_3CC);
        } else if ((sp54 > 8.0f) && (sp54 < 10.0f)) {
            this->unk_3C8 |= 2;
            func_800A6408(horse, 0x14, &sp88, &sp70);
            func_80A6506C(&sp70, 10.0f, &this->unk_3D8);
        } else if ((sp54 > 1.0f) && (sp54 < 3.0f)) {
            this->unk_3C8 |= 4;
            func_800A6408(horse, 0x2D, &sp88, &sp70);
            func_80A6506C(&sp70, 10.0f, &this->unk_3E4);
        } else if ((sp54 > 26.0f) && (sp54 < 28.0f)) {
            this->unk_3C8 |= 8;
            func_800A6408(horse, 0x25, &sp88, &sp70);
            func_80A6506C(&sp70, 10.0f, &this->unk_3F0);
        }
    } else if ((this->unk_14C == 0xE) && (6.0f < sp54) &&
               (Math_Rand_ZeroOne() < (1.0f - ((sp54 - 6.0f) * 0.05882353f)))) {
        if (Math_Rand_ZeroOne() < 0.5f) {
            this->unk_3C8 |= 8;
            func_800A6408(horse, 0x25, &sp88, &sp70);
            func_80A6506C(&sp70, 10.0f, &this->unk_3F0);
        }
        if (Math_Rand_ZeroOne() < 0.5f) {
            this->unk_3C8 |= 4;
            func_800A6408(horse, 0x2D, &sp88, &sp70);
            func_80A6506C(&sp70, 10.0f, &this->unk_3E4);
        }
    } else if ((this->unk_14C == 0xF) && (sp54 > 5.0f) && (Math_Rand_ZeroOne() < (1.0f - ((sp54 - 5.0f) * 0.04f)))) {
        if (Math_Rand_ZeroOne() < 0.5f) {
            this->unk_3C8 |= 8;
            func_800A6408(horse, 0x25, &sp88, &sp70);
            func_80A6506C(&sp70, 10.0f, &this->unk_3F0);
        }
        if (Math_Rand_ZeroOne() < 0.5f) {
            this->unk_3C8 |= 4;
            func_800A6408(horse, 0x2D, &sp88, &sp70);
            func_80A6506C(&sp70, 10.0f, &this->unk_3E4);
        }
    } else if ((this->unk_14C == 0x10) && (Math_Rand_ZeroOne() < 0.5f)) {
        if (Math_Rand_ZeroOne() < 0.5f) {
            this->unk_3C8 |= 8;
            func_800A6408(horse, 0x25, &sp88, &sp70);
            func_80A6506C(&sp70, 10.0f, &this->unk_3F0);
        } else {
            this->unk_3C8 |= 4;
            func_800A6408(horse, 0x2D, &sp88, &sp70);
            func_80A6506C(&sp70, 10.0f, &this->unk_3E4);
        }
    }

    for (i = 0; i < this->collider3.count; i++) {
        sp48.x = this->collider3.list[i].dim.modelSphere.center.x;
        sp48.y = this->collider3.list[i].dim.modelSphere.center.y;
        sp48.z = this->collider3.list[i].dim.modelSphere.center.z;

        func_800A6408(horse, this->collider3.list[i].dim.joint, &sp48, &sp3C);

        this->collider3.list[i].dim.worldSphere.center.x = sp3C.x;
        this->collider3.list[i].dim.worldSphere.center.y = sp3C.y;
        this->collider3.list[i].dim.worldSphere.center.z = sp3C.z;
        this->collider3.list[i].dim.worldSphere.radius =
            this->collider3.list[i].dim.modelSphere.radius * this->collider3.list[i].dim.scale;
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
}

s32 func_80A65C00(Actor* thisx, GlobalContext* globalCtx, s32 arg2, s32 arg3) {
    EnHorse* this = THIS;
    s32 ret = true;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_horse.c", 8582);

    if ((arg2 == 0xD) && (this->unk_158 == 0)) {
        u8 idx = D_80A667F8[this->unk_37A];

        gSPSegment(gfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A667EC[idx]));

    } else if ((this->unk_158 == 1) && ((this->unk_1F0 & 0x40000) != 0) && (arg2 == 30)) {
        func_800A5F60(globalCtx->state.gfxCtx, &this->unk_160, arg2, &D_06006530, 0);
        ret = false;
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_horse.c", 8601);
    return ret;
}

void EnHorse_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHorse* this = THIS;

    if ((this->unk_1F0 & 0x2000) == 0) {
        func_80093D18(globalCtx->state.gfxCtx);
        this->unk_1F0 |= 0x8000000;
        if ((this->unk_1F0 & 4) != 0) {
            func_800A6360(&this->actor, globalCtx, &this->unk_160, func_80A65108, func_80A65C00, 0);
        } else {
            func_800A6360(&this->actor, globalCtx, &this->unk_160, func_80A65108, func_80A65C00, 1);
        }
        if (this->actionFunc != NULL) {
            this->actionFunc(this, globalCtx);
        }
    }
}
