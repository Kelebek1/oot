/*
 * File: z_en_jj.c
 * Overlay: ovl_En_Jj
 * Description: Lord Jabu-Jabu
 */

#include "overlays/actors/ovl_Eff_Dust/z_eff_dust.h"
#include "z_en_jj.h"
#include "z64cutscene_commands.h"

#define FLAGS 0x00000030

#define THIS ((EnJj*)thisx)

void EnJj_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJj_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJj_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJj_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A87F44(Actor* thisx, GlobalContext* globalCtx);

void func_80A87BEC(EnJj* this, GlobalContext* globalCtx);
void func_80A87C30(EnJj* this, GlobalContext* globalCtx);
void func_80A87CEC(EnJj* this, GlobalContext* globalCtx);
void func_80A87EF0(EnJj* this, GlobalContext* globalCtx);

extern UNK_TYPE D_06000A1C;
extern UNK_TYPE D_06001830;
extern UNK_TYPE D_0600BA8C;
extern SkeletonHeader D_0600B9A8;
extern AnimationHeader D_06001F4C;

const ActorInit En_Jj_InitVars = {
    ACTOR_EN_JJ,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_JJ,
    sizeof(EnJj),
    (ActorFunc)EnJj_Init,
    (ActorFunc)EnJj_Destroy,
    (ActorFunc)EnJj_Update,
    (ActorFunc)EnJj_Draw,
};

static s32 padding = 0;

static CutsceneData D_80A88164[] = {
    CS_BEGIN_CUTSCENE(26, 1629),
    CS_PLAYER_ACTION_LIST(4),
    CS_PLAYER_ACTION(0x0005, 0, 240, 0x0000, 0x4000, 0x0000, -1732, 52, -44, -1732, 52, -44, 1.1393037197548209e-29f,
                     0.0f, 1.401298464324817e-45f),
    CS_PLAYER_ACTION(0x0003, 240, 255, 0x0000, 0x4000, 0x0000, -1732, 52, -44, -1732, 52, -44, 1.1393037197548209e-29f,
                     0.0f, 1.401298464324817e-45f),
    CS_PLAYER_ACTION(0x0006, 255, 285, 0x0000, 0x4000, 0x0000, -1732, 52, -44, -1732, 52, -44, 1.1393037197548209e-29f,
                     0.0f, 1.401298464324817e-45f),
    CS_PLAYER_ACTION(0x0020, 285, 300, 0x0000, 0xC000, 0x0000, -1732, 52, -44, -1537, 109, -44, 1.1393037197548209e-29f,
                     0.0f, 1.401298464324817e-45f),
    CS_NPC_ACTION_LIST(68, 4),
    CS_NPC_ACTION(0x0001, 0, 234, 0x0000, 0x4000, 0x0000, -1665, 52, -44, -1665, 52, -44, 1.1393037197548209e-29f, 0.0f,
                  1.401298464324817e-45f),
    CS_NPC_ACTION(0x0002, 234, 241, 0x41F8, 0x0000, 0x0000, -1665, 52, -44, -1603, 130, -47, 8.857142448425293f,
                  11.142857551574707f, -8.857142448425293f),
    CS_NPC_ACTION(0x0002, 241, 280, 0x4031, 0x0000, 0x0000, -1603, 130, -47, -549, 130, -52, 27.0256404876709f, 0.0f,
                  -27.0256404876709f),
    CS_NPC_ACTION(0x0003, 280, 300, 0x0000, 0x0000, 0x0000, -549, 130, -52, -549, 130, -52, 0.0f, 0.0f, 0.0f),
    CS_NPC_ACTION_LIST(67, 5),
    CS_NPC_ACTION(0x0001, 0, 93, 0x0000, 0x0000, 0x0000, 0, 51, 124, 0, 51, 124, 0.0f, 0.0f, 0.0f),
    CS_NPC_ACTION(0x0003, 93, 121, 0x0000, 0x0000, 0x0000, 0, 51, 124, 0, 51, 124, 0.0f, 0.0f, 0.0f),
    CS_NPC_ACTION(0x0001, 121, 146, 0x0000, 0x0000, 0x0000, 0, 51, 124, 0, 51, 124, 0.0f, 0.0f, 0.0f),
    CS_NPC_ACTION(0x0002, 146, 241, 0x0000, 0x0000, 0x0000, 0, 51, 124, 0, 51, 124, 0.0f, 0.0f, 0.0f),
    CS_NPC_ACTION(0x0001, 241, 441, 0x0000, 0x0000, 0x0000, 0, 51, 124, 0, 51, 124, 0.0f, 0.0f, 0.0f),
    CS_NPC_ACTION_LIST(69, 3),
    CS_NPC_ACTION(0x0001, 0, 90, 0x0000, 0x0000, 0x0000, 0, -33, 9, 0, -33, 9, 0.0f, 0.0f, 0.0f),
    CS_NPC_ACTION(0x0002, 90, 330, 0x0000, 0x0000, 0x0000, 0, -33, 9, 0, -62, 22, 0.0f, -0.12083332985639572f, 0.0f),
    CS_NPC_ACTION(0x0003, 330, 380, 0x0000, 0x0000, 0x0000, 0, -62, 22, 0, -62, 22, 0.0f, 0.0f, 0.0f),
    CS_MISC_LIST(1),
    CS_MISC(0x000C, 1095, 1161, 0x0000, 0x00000000, 0xFFFFFFD2, 0x00000000, 0xFFFFFFD0, 0xFFFFFFD2, 0x00000000,
            0xFFFFFFD0, 0x00000000, 0x00000000, 0x00000000),
    CS_SCENE_TRANS_FX(0x0009, 0, 10),
    CS_PLAYER_ACTION_LIST(1),
    CS_PLAYER_ACTION(0x0035, 300, 1629, 0x0000, 0x0000, 0x0000, -1630, 52, -52, -1630, 52, -52, 0.0f, 0.0f, 0.0f),
    CS_CAM_POS_LIST(0, 1091),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0x015C),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0x016D),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0x017E),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0x0223),
    CS_CAM_POS(CS_CMD_STOP, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0x7065),
    CS_CAM_POS_LIST(60, 1151),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1532, 251, 222, 0x015C),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1532, 251, 222, 0x016D),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1532, 251, 222, 0x017E),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1532, 251, 222, 0x0223),
    CS_CAM_POS(CS_CMD_STOP, 0x00, 0, 45.39994430541992f, -1532, 251, 222, 0x7065),
    CS_CAM_POS_LIST(90, 351),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1698, 382, 455, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1698, 382, 455, 0xAC34),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1698, 382, 455, 0x4428),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1694, 380, 451, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 32.99989700317383f, -1694, 380, 451, 0xAC10),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 32.99989700317383f, -1694, 380, 451, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 32.99989700317383f, -1694, 380, 451, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 32.99989700317383f, -1694, 380, 451, 0x0164),
    CS_CAM_POS(CS_CMD_STOP, 0x00, 0, 32.99989700317383f, -1694, 380, 451, 0xAD78),
    CS_CAM_POS_LIST(220, 392),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0xAC34),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0x4428),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0xAC10),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0x0000),
    CS_CAM_POS(CS_CMD_STOP, 0x00, 0, 45.39994430541992f, -1641, 95, -41, 0x0000),
    CS_CAM_POS_LIST(240, 1331),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.599945068359375f, -1810, 65, -15, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.599945068359375f, -1810, 65, -15, 0xAC34),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.599945068359375f, -1810, 65, -15, 0x4428),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.599945068359375f, -1810, 65, -15, 0x0000),
    CS_CAM_POS(CS_CMD_STOP, 0x00, 0, 45.599945068359375f, -1810, 65, -15, 0xAC10),
    CS_CAM_POS_LIST(280, 1371),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.599945068359375f, -1531, 95, -7, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.599945068359375f, -1531, 95, -7, 0xAC34),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.599945068359375f, -1531, 95, -7, 0x4428),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.599945068359375f, -1531, 95, -7, 0x0000),
    CS_CAM_POS(CS_CMD_STOP, 0x00, 0, 45.599945068359375f, -1531, 95, -7, 0xAC10),
    CS_CAM_POS_LIST(310, 1421),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1717, 83, -59, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1717, 83, -59, 0xAC34),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1649, 177, -59, 0x4428),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1533, 224, -59, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -1243, 180, -59, 0xAC10),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -953, 71, -55, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -953, 71, -55, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 45.39994430541992f, -953, 71, -55, 0x0164),
    CS_CAM_POS(CS_CMD_STOP, 0x00, 0, 45.39994430541992f, -953, 71, -55, 0xAD78),
    CS_CAM_POS_LIST(355, 1466),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 60.60000228881836f, -1830, 103, 18, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 60.60000228881836f, -1830, 103, 18, 0xAC34),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 60.60000228881836f, -1830, 103, 18, 0x4428),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 60.60000228881836f, -1830, 103, 18, 0x0000),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 60.60000228881836f, -1830, 103, 18, 0xAC10),
    CS_CAM_POS(CS_CMD_CONTINUE, 0x00, 0, 60.60000228881836f, -1830, 103, 18, 0x0000),
    CS_CAM_POS(CS_CMD_STOP, 0x00, 0, 60.60000228881836f, -1830, 103, 18, 0x0000),
    CS_CAM_FOCUS_POINT_LIST(0, 1120),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -1724, -5, -45, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -1724, -5, -45, 0xAC34),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 1000, 45.39994430541992f, -1724, -5, -45, 0x4428),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -1724, -5, -45, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_STOP, 0x00, 30, 45.39994430541992f, -1724, -5, -45, 0xAC10),
    CS_CAM_FOCUS_POINT_LIST(60, 1180),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -1440, 241, 134, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -1440, 241, 134, 0xAC34),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 1000, 45.39994430541992f, -1440, 241, 134, 0x4428),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -1440, 241, 134, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_STOP, 0x00, 30, 45.39994430541992f, -1440, 241, 134, 0xAC10),
    CS_CAM_FOCUS_POINT_LIST(90, 380),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -1610, 348, 373, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -1610, 348, 373, 0xAC34),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 50, 45.39994430541992f, -1610, 348, 373, 0x4428),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 35.399906158447266f, -1614, 338, 367, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 32.99989700317383f, -1614, 338, 367, 0xAC10),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 32.99989700317383f, -1614, 338, 367, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 32.99989700317383f, -1614, 338, 367, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 32.99989700317383f, -1614, 338, 367, 0x0164),
    CS_CAM_FOCUS_POINT(CS_CMD_STOP, 0x00, 30, 32.99989700317383f, -1614, 338, 367, 0xAD78),
    CS_CAM_FOCUS_POINT_LIST(220, 421),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -1724, -5, -45, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 70, 45.39994430541992f, -1724, -5, -45, 0xAC34),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 5, 45.39994430541992f, -1724, -5, -45, 0x4428),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 6, 45.79994583129883f, -1593, 150, -146, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -1531, 152, -75, 0xAC10),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -1531, 152, -75, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_STOP, 0x00, 30, 45.39994430541992f, -1531, 152, -75, 0x0000),
    CS_CAM_FOCUS_POINT_LIST(240, 1360),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.599945068359375f, -1712, 74, -37, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.599945068359375f, -1712, 74, -37, 0xAC34),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 1000, 45.599945068359375f, -1712, 74, -37, 0x4428),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.599945068359375f, -1712, 74, -37, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_STOP, 0x00, 30, 45.599945068359375f, -1712, 74, -37, 0xAC10),
    CS_CAM_FOCUS_POINT_LIST(280, 1400),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.599945068359375f, -1619, 99, -50, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.599945068359375f, -1619, 99, -50, 0xAC34),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 1000, 45.599945068359375f, -1619, 99, -50, 0x4428),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.599945068359375f, -1619, 99, -50, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_STOP, 0x00, 30, 45.599945068359375f, -1619, 99, -50, 0xAC10),
    CS_CAM_FOCUS_POINT_LIST(310, 1450),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x0B, 30, 90.99960327148438f, -1610, 141, -59, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x09, 10, 90.79960632324219f, -1599, 114, -57, 0xAC34),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0xFC, 10, 90.39961242675781f, -1528, 192, -54, 0x4428),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 10, 90.599609375f, -1427, 164, -54, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0xCB, 10, 90.39961242675781f, -1138, 119, -37, 0xAC10),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x20, 10, 90.39961242675781f, -832, 50, -51, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 1000, 45.39994430541992f, -836, 35, -51, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 45.39994430541992f, -836, 35, -51, 0x0164),
    CS_CAM_FOCUS_POINT(CS_CMD_STOP, 0x00, 30, 45.39994430541992f, -836, 35, -51, 0xAD78),
    CS_CAM_FOCUS_POINT_LIST(355, 1495),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 60.60000228881836f, -1706, 111, -6, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 60.60000228881836f, -1706, 111, -6, 0xAC34),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 10, 60.60000228881836f, -1706, 111, -6, 0x4428),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 10, 60.60000228881836f, -1721, 82, -42, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 1000, 60.60000228881836f, -1721, 82, -42, 0xAC10),
    CS_CAM_FOCUS_POINT(CS_CMD_CONTINUE, 0x00, 30, 60.60000228881836f, -1721, 82, -42, 0x0000),
    CS_CAM_FOCUS_POINT(CS_CMD_STOP, 0x00, 30, 60.60000228881836f, -1721, 82, -42, 0x0000),
    CS_SCENE_TRANS_FX(0x000B, 335, 342),
    CS_TERMINATOR(JABU_JABU_INTRO, 345, 395),
    CS_NPC_ACTION_LIST(62, 1),
    CS_NPC_ACTION(0x0001, 305, 494, 0x0000, 0x0000, 0x0000, -1399, 452, -53, -1399, 452, -53, 0.0f, 0.0f, 0.0f),
    CS_END(),
};

static s32 padding2[] = { 0, 0 };

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x00, 0x09, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000004, 0x00, 0x00 }, 0x00, 0x01, 0x01 },
    { 170, 150, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 87, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 3300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1100, ICHAIN_STOP),
};

void func_80A87800(EnJj* this, EnJjActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnJj_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnJj* this = THIS;
    s32 pad;
    s32 sp4C = 0;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    ActorShape_Init(&this->dyna.actor.shape, 0.0f, NULL, 0.0f);

    switch (this->dyna.actor.params) {
        case -1:
            SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600B9A8, &D_06001F4C, this->limbDrawTable,
                             this->transitionDrawTable, 22);
            SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06001F4C);
            this->unk_30A = 0;
            this->unk_30E = 0;
            this->unk_30F = 0;
            this->unk_310 = 0;
            this->unk_311 = 0;
            if (gSaveContext.eventChkInf[3] & 0x400) {
                func_80A87800(this, func_80A87BEC);
            } else {
                func_80A87800(this, func_80A87C30);
            }

            this->unk_300 = (EnJj*)Actor_SpawnAsChild(
                &globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_EN_JJ, this->dyna.actor.posRot.pos.x - 10.0f,
                this->dyna.actor.posRot.pos.y, this->dyna.actor.posRot.pos.z, 0, this->dyna.actor.posRot.rot.y, 0, 0);
            DynaPolyInfo_SetActorMove(&this->dyna, 0);
            DynaPolyInfo_Alloc(&D_06000A1C, &sp4C);
            this->dyna.dynaPolyId =
                DynaPolyInfo_RegisterActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, sp4C);
            Collider_InitCylinder(globalCtx, &this->collider);
            Collider_SetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);
            this->dyna.actor.colChkInfo.mass = 0xFF;
            break;

        case 0:
            DynaPolyInfo_SetActorMove(&this->dyna, 0);
            DynaPolyInfo_Alloc(&D_06001830, &sp4C);
            this->dyna.dynaPolyId =
                DynaPolyInfo_RegisterActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, sp4C);
            func_8003ECA8(globalCtx, &globalCtx->colCtx.dyna, this->dyna.dynaPolyId);
            this->dyna.actor.update = func_80A87F44;
            this->dyna.actor.draw = NULL;
            Actor_SetScale(&this->dyna.actor, 0.087f);
            break;

        case 1:
            DynaPolyInfo_SetActorMove(&this->dyna, 0);
            DynaPolyInfo_Alloc(&D_0600BA8C, &sp4C);
            this->dyna.dynaPolyId =
                DynaPolyInfo_RegisterActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, sp4C);
            this->dyna.actor.update = func_80A87F44;
            this->dyna.actor.draw = NULL;
            Actor_SetScale(&this->dyna.actor, 0.087f);
            break;
    }
}

void EnJj_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnJj* this = THIS;

    switch (this->dyna.actor.params) {
        case -1:
            DynaPolyInfo_Free(globalCtx, &globalCtx->colCtx.dyna, this->dyna.dynaPolyId);
            Collider_DestroyCylinder(globalCtx, &this->collider);
            break;

        case 0:
        case 1:
            DynaPolyInfo_Free(globalCtx, &globalCtx->colCtx.dyna, this->dyna.dynaPolyId);
            break;
    }
}

void func_80A87B1C(EnJj* this) {
    if (this->unk_30F > 0) {
        this->unk_30F--;
        return;
    }

    this->unk_30E++;
    if (this->unk_30E >= 3) {
        this->unk_30E = 0;
        if (this->unk_310 > 0) {
            this->unk_310--;
            return;
        }

        this->unk_30F = Math_Rand_S16Offset(0x14, 0x14);
        this->unk_310 = this->unk_311;
    }
}

void func_80A87B9C(EnJj* this, GlobalContext* globalCtx) {
    EnJj* otherJj = this->unk_300;

    if (this->unk_308 >= -0x1450) {
        this->unk_308 -= 0x66;
        if (this->unk_308 < -0xA28) {
            func_8003EBF8(globalCtx, &globalCtx->colCtx.dyna, otherJj->dyna.dynaPolyId);
        }
    }
}

void func_80A87BEC(EnJj* this, GlobalContext* globalCtx) {
    if (this->dyna.actor.xzDistFromLink < 300.0f) {
        func_80A87800(this, func_80A87B9C);
    }
}

void func_80A87C30(EnJj* this, GlobalContext* globalCtx) {
    static Vec3f D_80A88CF0 = { -1589.0f, 53.0f, -43.0f };

    Player* player = PLAYER;

    if ((Math_Vec3f_DistXZ(&D_80A88CF0, &player->actor.posRot.pos) < 300.0f) &&
        (globalCtx->unk_11D44(globalCtx) != 0)) {
        this->unk_30C = 0x64;
        func_80A87800(this, func_80A87CEC);
    }
    this->collider.dim.pos.x = -0x4DD;
    this->collider.dim.pos.y = 0x14;
    this->collider.dim.pos.z = -0x30;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80A87CEC(EnJj* this, GlobalContext* globalCtx) {
    struct EnJj* otherJj = this->unk_300;

    if (this->unk_30C > 0) {
        this->unk_30C--;
        return;
    }

    func_80A87800(this, func_80A87EF0);
    globalCtx->csCtx.segment = D_80A88164;
    gSaveContext.cutsceneTrigger = 1;
    func_8003EBF8(globalCtx, &globalCtx->colCtx.dyna, otherJj->dyna.dynaPolyId);
    func_8005B1A4(ACTIVE_CAM);
    gSaveContext.eventChkInf[3] |= 0x400;
    func_80078884(NA_SE_SY_CORRECT_CHIME);
}

void func_80A87D94(EnJj* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.npcActions[2]->action) {
        case 1:
            if ((this->unk_30A & 2) != 0) {
                this->unk_30E = 0;
                this->unk_30F = Math_Rand_S16Offset(0x14, 0x14);
                this->unk_310 = 0;
                this->unk_311 = 0;
                this->unk_30A ^= 2;
            }
            break;

        case 2:
            this->unk_30A |= 1;
            if ((this->unk_30A & 8) == 0) {
                this->unk_304 = (EffDust*)Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx,
                                                             ACTOR_EFF_DUST, -1100.0f, 105.0f, -27.0f, 0, 0, 0, 0);
                this->unk_30A |= 8;
            }
            break;

        case 3:
            if (!(this->unk_30A & 2)) {
                this->unk_30E = 0;
                this->unk_30F = 0;
                this->unk_310 = 1;
                this->unk_311 = 0;
                this->unk_30A |= 2;
            }
            break;
    }

    if (this->unk_30A & 1) {
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_JABJAB_BREATHE - SFX_FLAG);
        if (this->unk_308 >= -0x1450) {
            this->unk_308 -= 0x66;
        }
    }
}

void func_80A87EF0(EnJj* this, GlobalContext* globalCtx) {
    if (!(this->unk_30A & 4)) {
        this->unk_30A |= 4;
        if (this->unk_304 != NULL) {
            Actor_Kill(&this->unk_304->actor);
            this->dyna.actor.child = NULL;
        }
    }
}

void func_80A87F44(Actor* thisx, GlobalContext* globalCtx) {
}

void EnJj_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnJj* this = THIS;

    if ((globalCtx->csCtx.state != 0) && (globalCtx->csCtx.npcActions[2] != NULL)) {
        func_80A87D94(this, globalCtx);
    } else {
        this->actionFunc(this, globalCtx);
        if (this->skelAnime.animCurrentFrame == 41.0f) {
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_JABJAB_GROAN);
        }
    }

    func_80A87B1C(this);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Actor_SetScale(&this->dyna.actor, 0.087f);
    this->skelAnime.limbDrawTbl[10].z = this->unk_308;
}

void EnJj_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static UNK_TYPE D_80A88CFC[] = { 0x06007698, 0x06007A98, 0x06007E98 };

    EnJj* this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_jj.c", 879);

    func_800943C8(globalCtx->state.gfxCtx);
    Matrix_Translate(0.0f, (cosf(this->skelAnime.animCurrentFrame * 0.076624215f) * 10.0f) - 10.0f, 0.0f,
                     MTXMODE_APPLY);
    Matrix_Scale(10.0f, 10.0f, 10.0f, MTXMODE_APPLY);
    gSPSegment(oGfxCtx->polyOpa.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_80A88CFC[this->unk_30E]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL,
                     NULL, &this->dyna.actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_jj.c", 898);
}
