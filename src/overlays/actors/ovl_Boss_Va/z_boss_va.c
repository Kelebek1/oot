#include "z_boss_va.h"
#include "overlays/actors/ovl_En_Boom/z_en_boom.h"

#define FLAGS 0x00000035

#define THIS ((BossVa*)thisx)

void BossVa_Init(Actor* thisx, GlobalContext* globalCtx);
void BossVa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BossVa_Update(Actor* thisx, GlobalContext* globalCtx);
void BossVa_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809506F0(BossVa* this);
void func_809517A0(BossVa* this);
void func_80957C10(BossVa* this);
void func_80952100(BossVa* this);
void func_809597F4(GlobalContext* globalCtx);
void func_8095A188(BossVaEffect* ptr, GlobalContext* globalCtx);
void func_8095BD24(GlobalContext* globalCtx, s16 arg1);
void func_8094FBB4(GlobalContext* globalCtx);

void func_80953F4C(BossVa* this, GlobalContext* globalCtx);
void func_809540E4(BossVa* this, GlobalContext* globalCtx);
void func_80954A3C(BossVa* this, GlobalContext* globalCtx);
void func_80954B8C(BossVa* this, GlobalContext* globalCtx);
void func_80954924(BossVa* this, GlobalContext* globalCtx);
void func_80957C9C(BossVa* this, GlobalContext* globalCtx);
void func_809567D0(BossVa* this, GlobalContext* globalCtx);
void func_80956E38(BossVa* this, GlobalContext* globalCtx);
void func_809572DC(BossVa* this, GlobalContext* globalCtx);
void func_80950780(BossVa* this, GlobalContext* globalCtx);
void func_80951844(BossVa* this, GlobalContext* globalCtx);
void func_80953FC4(BossVa* this, GlobalContext* globalCtx);
void func_8095438C(BossVa* this, GlobalContext* globalCtx);
void func_80954168(BossVa* this, GlobalContext* globalCtx);
void func_80954AD0(BossVa* this, GlobalContext* globalCtx);
void func_80954C20(BossVa* this, GlobalContext* globalCtx);
void func_809549A8(BossVa* this, GlobalContext* globalCtx);
void func_80954454(BossVa* this, GlobalContext* globalCtx);
void func_80957CEC(BossVa* this, GlobalContext* globalCtx);
void func_809568E0(BossVa* this, GlobalContext* globalCtx);
void func_80956EE0(BossVa* this, GlobalContext* globalCtx);
void func_80957384(BossVa* this, GlobalContext* globalCtx);
void func_80951AD8(BossVa* this, GlobalContext* globalCtx);
void func_80955E64(BossVa* this, GlobalContext* globalCtx);
void func_80955658(BossVa* this, GlobalContext* globalCtx);
void func_80956644(BossVa* this, GlobalContext* globalCtx);
void func_80957998(BossVa* this, GlobalContext* globalCtx);
void func_8094FC70(BossVa* this, GlobalContext* globalCtx);
void func_80951C04(BossVa* this, GlobalContext* globalCtx);
void func_80955EEC(BossVa* this, GlobalContext* globalCtx);
void func_8095575C(BossVa* this, GlobalContext* globalCtx);
void func_809566C4(BossVa* this, GlobalContext* globalCtx);
void func_809579F4(BossVa* this, GlobalContext* globalCtx);
void func_80957C68(BossVa* this, GlobalContext* globalCtx);
void func_8095213C(BossVa* this, GlobalContext* globalCtx);
void func_80955940(BossVa* this, GlobalContext* globalCtx);
void func_809527A4(BossVa* this, GlobalContext* globalCtx);
void func_80952858(BossVa* this, GlobalContext* globalCtx);
void func_8095335C(BossVa* this, GlobalContext* globalCtx);
void func_809533F4(BossVa* this, GlobalContext* globalCtx);

void func_8095B670(GlobalContext* globalCtx, BossVaEffect* ptr, Vec3f* arg2, s16 arg3, s16 arg4);
void func_8095B9B0(GlobalContext* globalCtx, BossVaEffect* ptr, Vec3f* arg2, s16 arg3, s16 arg4);
void func_8095B028(GlobalContext* globalCtx, BossVaEffect* ptr, BossVa* this, Vec3f* arg3, s16 arg4, u8 arg5);
void func_8095BBD0(GlobalContext* globalCtx, BossVaEffect* ptr, BossVa* this, Vec3f* arg3, Vec3s* arg4, s16 arg5,
                   u8 arg6);
void func_8095B80C(GlobalContext* globalCtx, BossVaEffect* ptr, BossVa* this, Vec3f* arg3, s16 arg4, u8 arg5);
void func_8095B318(GlobalContext* globalCtx, BossVaEffect* ptr, BossVa* this, Vec3f* arg3, s16 arg4, u8 arg5);
void func_8095B4A4(GlobalContext* globalCtx, BossVaEffect* ptr, Vec3f* arg2, s16 arg3, s16 arg4, s16 arg5);
void func_8094F9E8(GlobalContext* globalCtx, BossVa* this, s32 arg2, s16 arg3, f32 arg4, f32 arg5, u8 arg6, f32 arg7,
                   u8 arg8);

extern SkeletonHeader D_06015B18;
extern SkeletonHeader D_06017498;
extern SkeletonHeader D_060199A0;
extern SkeletonHeader D_06018870;
extern SkeletonHeader D_06004E70;
extern AnimationHeader D_06005184;
extern AnimationHeader D_060166A8;
extern AnimationHeader D_06018D18;
extern AnimationHeader D_06018150;
extern AnimationHeader D_06000024;
extern AnimationHeader D_060162AC;
extern AnimationHeader D_060164B0;
extern AnimationHeader D_06017694;
extern AnimationHeader D_060177F4;
extern SkeletonHeader D_06017FC8;
extern AnimationHeader D_06018A68;
extern AnimationHeader D_06018B90;
extern Gfx D_06008D70[];
extern Gfx D_06008BB8[];
extern Gfx D_06000FA0[];
extern Gfx D_060156A0[];
extern Gfx D_06015710[];
extern Gfx D_06011738[];
extern Gfx D_06011768[];
extern Gfx D_06009430[];
extern Gfx D_06009468[];
extern Gfx D_060128B8[];
extern Gfx D_06012948[];
extern Gfx D_06012BA0[];
extern Gfx D_06012C50[];
extern Gfx D_060135B0[];
extern Gfx D_06013638[];
extern Gfx D_06008F08[];
extern Gfx D_06008F70[];
extern UNK_TYPE D_04055DB0;
extern UNK_TYPE D_06001230;

/*
const ActorInit Boss_Va_InitVars = {
    ACTOR_BOSS_VA,
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_BV,
    sizeof(BossVa),
    (ActorFunc)BossVa_Init,
    (ActorFunc)BossVa_Destroy,
    (ActorFunc)BossVa_Update,
    (ActorFunc)BossVa_Draw,
};
*/

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_UNK10, 0x11, 0x09, 0x39, 0x20, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFEF, 0x03, 0x08 }, { 0x00000010, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
    { 85, 120, 0, { 0, 0, 0 } },
};

static ColliderJntSphItemInit sJntSphItemsInit[1] = {
    {
        { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000010, 0x00, 0x00 }, 0x00, 0x01, 0x00 },
        { 0, { { 0, 0, 0 }, 25 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_UNK6, 0x00, 0x09, 0x00, 0x10, COLSHAPE_JNTSPH },
    1,
    sJntSphItemsInit,
};

static ColliderQuadInit sQuadInit = {
    { COLTYPE_METAL_SHIELD, 0x11, 0x09, 0x00, 0x00, COLSHAPE_QUAD },
    { 0x00, { 0x20000000, 0x03, 0x04 }, { 0x00000010, 0x00, 0x00 }, 0x81, 0x01, 0x00 },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

Vec3f D_8095C044[] = { { 0.0f, 175.35000610351562f, 0.0f },
                       { 0.0f, 175.35000610351562f, 0.0f },
                       { 0.0f, 175.35000610351562f, 0.0f },
                       { 120.0f, 103.42500305175781f, -67.0f },
                       { 0.0f, 103.42500305175781f, 140.0f },
                       { -120.0f, 103.42500305175781f, -70.0f },
                       { -2.0f, 16.0f, 50.0f },
                       { 48.0f, 16.0f, 15.0f },
                       { 25.0f, 16.0f, -36.0f },
                       { -29.0f, 16.0f, -36.0f },
                       { -63.0f, 16.0f, 22.0f },
                       { 0.0f, -10.0f, -64.0f },
                       { 63.0f, -10.0f, -22.0f },
                       { 35.0f, -10.0f, 46.0f },
                       { -36.0f, -10.0f, 46.0f },
                       { -49.0f, -10.0f, -17.0f } };

Vec3s D_8095C17C[] = { { 0x1FFE, 0x0000, 0x0000 }, { 0x1FFE, 0x5550, 0x0000 }, { 0x1FFE, 0xAAB0, 0x0000 },
                       { 0xD558, 0x5550, 0x0000 }, { 0xD558, 0x0000, 0x0000 }, { 0xD558, 0xAAB0, 0x0000 },
                       { 0x2AA8, 0xFCCC, 0x0000 }, { 0x2AA8, 0x3330, 0x0000 }, { 0x2AA8, 0x6660, 0x0000 },
                       { 0x2AA8, 0x99A0, 0x0000 }, { 0x2AA8, 0xCCD0, 0x0000 }, { 0x4C98, 0x81D0, 0x0000 },
                       { 0x4C98, 0x4F70, 0x0000 }, { 0x4C98, 0x1758, 0x0000 }, { 0x4C98, 0xE8A8, 0x0000 },
                       { 0x4C98, 0xB648, 0x0000 } };

Vec3f D_8095C1DC[] = { { 10.0f, 0.0f, 30.0f }, { 260.0f, 0.0f, -470.0f }, { -240.0f, 0.0f, -470.0f } };

DamageTable D_8095C200[] = { 0x10, 0x02, 0x01, 0x02, 0x10, 0x02, 0x02, 0x10, 0x01, 0x02, 0x04,
                             0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xE0, 0x60, 0xD0, 0x00, 0x00,
                             0x01, 0x04, 0x02, 0x02, 0x08, 0x04, 0x00, 0x00, 0x04, 0x00 };

Vec3f D_8095C220 = { 0.0f, 0.0f, 0.0f };
u8 D_8095C226[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_8095C22C = 0x00;
u8 D_8095C230[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
s16 D_8095C23C = 0x0000;
Vec3f D_8095C240 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C24C = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C258 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C264 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C270 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C27C = { 15.0f, 0.0f, 0.0f };
Vec3f D_8095C288 = { -15.0f, 0.0f, 0.0f };
Vec3f D_8095C294 = { 15.0f, 0.0f, 0.0f };
Vec3f D_8095C2A0 = { -15.0f, 0.0f, 0.0f };
Vec3f D_8095C2AC = { 0.0f, 45.0f, 0.0f };
Vec3f D_8095C2B8 = { 0.4f, 0.4f, 0.4f };
Vec3f D_8095C2C4 = { 15.0f, 40.0f, 0.0f };
Vec3f D_8095C2D0 = { -15.0f, 40.0f, 0.0f };
Vec3f D_8095C2DC = { 15.0f, 40.0f, 0.0f };
Vec3f D_8095C2E8 = { -15.0f, 40.0f, 0.0f };
Color_RGBA8 D_8095C2F4 = { 0xFA, 0xFA, 0xE6, 0xC8 };
Color_RGBA8 D_8095C2F8 = { 0x00, 0x00, 0xFF, 0xFF };
// Some data here

UNK_PTR D_8095C300[] = {
    0x060096F8, 0x0600A6F8, 0x0600B6F8, 0x0600C6F8, 0x0600D6F8, 0x0600E6F8, 0x0600F6F8, 0x060106F8
};

Vec3f D_8095C320 = { 0.0f, -1000.0f, 0.0f };
Vec3f D_8095C32C = { 0.0f, -1000.0f, 0.0f };
Vec3f D_8095C338 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C344 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C350 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C35C = { 0.0f, -1000.0f, 0.0f };
Vec3f D_8095C368 = { 0.0f, 0.0f, 0.0f };
Vec3f D_8095C374 = { 0.0f, -1000.0f, 0.0f };
Gfx* D_8095C380[] = { 0x0601A3E8, 0x0601AEE8, 0x0601B9E8, 0x0601C4E8, 0x0601CFE8, 0x0601DAE8, 0x0601E5E8, 0x0601F0E8 };

s16 D_8095C3A0[] = { 0x0344, 0x0384, 0x0344, 0x03F8, 0x0320, 0x03F8, 0x0344, 0x0384 };

BossVaEffect D_8095DF50[400];

u8 D_809668D0;
u8 D_809668D1;
s8 D_809668D2;
Vec3f D_809668D8;
Vec3f D_809668E8;
Vec3f D_809668F8;
Vec3f D_80966908;
Vec3f D_80966918;
Vec3f D_80966928;
s16 D_80966934;
u8 D_80966936;
Vec3s D_80966938;
u16 D_8096693E;
s8 D_80966940;

void func_8094F2C0(BossVa* this, BossVaActionFunc func) {
    this->actionFunc = func;
}

void func_8094F2C8(BossVa* this) {
    BossVa* refActor = (BossVa*)this->actor.attachedA;

    Matrix_Translate(refActor->actor.posRot.pos.x, refActor->actor.posRot.pos.y, refActor->actor.posRot.pos.z, 0);
    Matrix_RotateRPY(refActor->actor.shape.rot.x, 0, refActor->actor.shape.rot.z, 1);
    Matrix_MultVec3f(&D_8095C044[this->actor.params], &this->actor.posRot.pos);

    switch (this->actor.params) {
        case 0:
        case 1:
        case 2:
            if (this->unk_194 == 0) {
                this->actor.shape.rot.x = D_8095C17C[this->actor.params].x + refActor->actor.shape.rot.x;
                this->actor.shape.rot.y = D_8095C17C[this->actor.params].y;
                this->actor.shape.rot.z = D_8095C17C[this->actor.params].z + refActor->actor.shape.rot.z;
            }
            break;

        case 3:
        case 4:
        case 5:
            this->actor.shape.rot.y = D_8095C17C[this->actor.params].y;
            this->actor.shape.rot.x =
                (D_8095C17C[this->actor.params].x +
                 (s16)(Math_Coss(D_8095C17C[this->actor.params].y) * refActor->actor.shape.rot.x)) -
                (s16)(Math_Sins(D_8095C17C[this->actor.params].y) * refActor->actor.shape.rot.z);
            this->actor.shape.rot.z =
                (s16)(Math_Coss(D_8095C17C[this->actor.params].y) * refActor->actor.shape.rot.z) +
                (D_8095C17C[this->actor.params].z +
                 (s16)(Math_Sins(D_8095C17C[this->actor.params].y) * refActor->actor.shape.rot.x));
            break;
    }

    this->actor.posRot.rot = this->actor.shape.rot;
    this->actor.shape.unk_08 = ((BossVa*)this->actor.attachedA)->actor.shape.unk_08;
}

void func_8094F50C(GlobalContext* globalCtx, Vec3f* arg1, s16 arg2, s16 arg3) {
    s32 i;
    Vec3f sp50;

    for (i = 2; i > 0; i--) {
        sp50.x = Math_Rand_CenteredFloat(10.0f) + arg1->x;
        sp50.y = arg1->y - (Math_Rand_ZeroOne() * 15.0f);
        sp50.z = Math_Rand_CenteredFloat(10.0f) + arg1->z;
        func_8095B4A4(globalCtx, D_8095DF50, &sp50, 0x41, arg2, arg3);
    }
}

void func_8094F60C(GlobalContext* globalCtx, BossVaEffect* arg1, s16 arg2, s16 arg3, s32 arg4) {
    s32 i;
    Vec3f sp60;

    for (i = arg4; i > 0; i--) {
        sp60.x = Math_Rand_CenteredFloat(10.0f) + arg1->unk_00.x;
        sp60.y = arg1->unk_00.y - (Math_Rand_ZeroOne() * 15.0f);
        sp60.z = Math_Rand_CenteredFloat(10.0f) + arg1->unk_00.z;
        func_8095B670(globalCtx, D_8095DF50, &sp60, (s16)Math_Rand_CenteredFloat(26000.0f) + arg2, arg3);
    }
}

void func_8094F734(GlobalContext* globalCtx, BossVaEffect* arg1, s16 arg2, s16 arg3) {
    s32 i;
    Vec3f sp58;

    i = (D_809668D2 < 0x14) ? 2 : 1;

    for (; i > 0; i--) {
        sp58.x = Math_Rand_CenteredFloat(10.0f) + arg1->unk_00.x;
        sp58.y = Math_Rand_CenteredFloat(10.0f) + arg1->unk_00.y;
        sp58.z = Math_Rand_CenteredFloat(10.0f) + arg1->unk_00.z;
        func_8095B9B0(globalCtx, D_8095DF50, &sp58, (s16)Math_Rand_CenteredFloat(26000.0f) + arg2, arg3);
    }
}

void func_8094F864(GlobalContext* globalCtx, BossVa* this, s32 arg2, s16 arg3, f32 arg4, f32 arg5, u8 arg6, f32 arg7,
                   u8 arg8) {
    s32 i;
    s16 tmp;
    Vec3f sp6C;

    for (i = arg2; i > 0; i--) {
        tmp = !arg8 ? Math_Rand_ZeroOne() * (arg7 - 0.6f) : arg7 - 0.6f;
        sp6C.x = (Math_Rand_CenteredFloat(arg4) + this->unk_1FC[tmp].x) - this->actor.posRot.pos.x;
        sp6C.y = (Math_Rand_CenteredFloat(arg5) + this->unk_1FC[tmp].y) - this->actor.posRot.pos.y;
        sp6C.z = (Math_Rand_CenteredFloat(arg4) + this->unk_1FC[tmp].z) - this->actor.posRot.pos.z;
        func_8095B028(globalCtx, D_8095DF50, this, &sp6C, arg3, arg6);
    }
}

void func_8094F9E8(GlobalContext* globalCtx, BossVa* this, s32 arg2, s16 arg3, f32 arg4, f32 arg5, u8 arg6, f32 arg7,
                   u8 arg8) {
    s16 tmp;
    s32 i;
    Vec3f sp6C;

    for (i = arg2; i > 0; i--) {
        if (!arg8) {
            tmp = Math_Rand_ZeroOne() * (arg7 - 0.6f);
        } else {
            tmp = arg7 - 0.6f;
        }

        sp6C.x = (Math_Rand_CenteredFloat(arg4) + this->unk_1FC[tmp].x) - this->actor.posRot.pos.x;
        sp6C.y = (Math_Rand_CenteredFloat(arg5) + this->unk_1FC[tmp].y) - this->actor.posRot.pos.y;
        sp6C.z = (Math_Rand_CenteredFloat(arg4) + this->unk_1FC[tmp].z) - this->actor.posRot.pos.z;
        func_8095B80C(globalCtx, D_8095DF50, this, &sp6C, arg3, arg6);
    }
}

void func_8094FB6C(GlobalContext* globalCtx) {
    globalCtx->envCtx.unk_8C[0] = 0xA;
    globalCtx->envCtx.unk_8C[1] = 0xA;
    globalCtx->envCtx.unk_8C[2] = 0xA;
    globalCtx->envCtx.unk_8C[3] = 0x73;
    globalCtx->envCtx.unk_8C[4] = 0x41;
    globalCtx->envCtx.unk_8C[5] = 0x64;
    globalCtx->envCtx.unk_8C[6] = 0x78;
    globalCtx->envCtx.unk_8C[7] = 0x78;
    globalCtx->envCtx.unk_8C[8] = 0x46;
}

void func_8094FBB4(GlobalContext* globalCtx) {
    globalCtx->envCtx.unk_8C[6] = 0xDC;
    globalCtx->envCtx.unk_8C[7] = 0xDC;
    globalCtx->envCtx.unk_8C[8] = 0x96;
    globalCtx->envCtx.unk_9E = -0x3E8;
    globalCtx->envCtx.unk_A0 = -0x384;
    globalCtx->envCtx.unk_8C[0] = 0xC8;
    globalCtx->envCtx.unk_8C[1] = 0xC8;
    globalCtx->envCtx.unk_8C[2] = 0xC8;
    globalCtx->envCtx.unk_8C[3] = 0xD7;
    globalCtx->envCtx.unk_8C[4] = 0xA5;
    globalCtx->envCtx.unk_8C[5] = 0xC8;
    globalCtx->envCtx.unk_E2[0] = 0xDC;
    globalCtx->envCtx.unk_E2[1] = 0xDC;
    globalCtx->envCtx.unk_E2[2] = 0x96;
    globalCtx->envCtx.unk_E2[3] = 0x64;
}

EnBoom* func_8094FC30(GlobalContext* globalCtx) {
    Actor* refActor = globalCtx->actorCtx.actorList[ACTORTYPE_MISC].first;

    while (refActor != NULL) {
        if (refActor->id != ACTOR_EN_BOOM) {
            refActor = refActor->next;
            continue;
        }
        return (EnBoom*)refActor;
    }
    return NULL;
}

void func_8094FC70(BossVa* this, GlobalContext* globalCtx) {
    s32 i;
    s16 tmp;
    Vec3f sp84;
    Vec3f sp78 = D_8095C240;
    Vec3f sp6C = D_8095C24C;

    for (i = 7; i >= 0; i--) {
        sp84.x = Math_Rand_CenteredFloat(60.0f) + this->actor.posRot.pos.x;
        sp84.y = Math_Rand_CenteredFloat(50.0f) +
                 (this->actor.posRot.pos.y + (this->actor.shape.unk_08 * this->actor.scale.y));
        sp84.z = Math_Rand_CenteredFloat(60.0f) + this->actor.posRot.pos.z;
        sp78.y = Math_Rand_ZeroOne() + 1.0f;
        tmp = Math_Rand_S16Offset(0x50, 0x64);
        if (Math_Rand_ZeroOne() < 0.7f) {
            func_80029618(globalCtx, &sp84, &sp78, &sp6C, tmp, 0x19, 2, 1);
        } else {
            func_80029618(globalCtx, &sp84, &sp78, &sp6C, tmp, 0x19, 0, 1);
        }
    }

    D_809668D1 = D_809668D1 + 1;
    func_80957C10(this);
}

#ifdef NON_MATCHING
// Regalloc, stack
void BossVa_Init(Actor* thisx, GlobalContext* globalCtx) {
    BossVa* this = THIS;
    s32 pad;
    s32 i;
    s16 tmp16;
    Vec3f sp5C;

    Actor_SetScale(thisx, 0.1f);
    this->actor.unk_1F = 5;
    this->actor.colChkInfo.mass = 0xFF;

    switch (this->actor.params) {
        case -1:
            SkelAnime_Init(globalCtx, &this->skelAnime, &D_06015B18, &D_06005184, NULL, NULL, 0);
            this->actor.flags |= 0x1000000;
            break;
        case 0:
        case 1:
        case 2:
            SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06017498, &D_060166A8, NULL, NULL, 0);
            break;
        case 3:
        case 4:
        case 5:
            SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060199A0, &D_06018D18, NULL, NULL, 0);
            break;
        case 16:
        case 17:
        case 18:
            SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06018870, &D_06018150, NULL, NULL, 0);
            break;

        default:
            this->actor.flags |= 0x1000000;
            SkelAnime_Init(globalCtx, &this->skelAnime, &D_06004E70, &D_06000024, NULL, NULL, 0);
            this->actor.shape.unk_08 = 400.0f;
            break;

        case 19:
            break;
    }

    this->actor.posRot2.pos = this->actor.posRot.pos;
    this->unk_194 = 0;
    this->actor.naviEnemyId = 0x14;

    switch (this->actor.params) {
        case -1:
            Actor_SpawnAttached(&globalCtx->actorCtx, thisx, globalCtx, ACTOR_BOSS_VA, 0.0f, 80.0f, 400.0f, 0, 0, 0,
                                0x13);
            if (Flags_GetClear(globalCtx, globalCtx->roomCtx.curRoom.num)) {
                tmp16 = ACTOR_EN_RU1;
                if (gSaveContext.eventChkInf[3] & 0x80) {
                    tmp16 = ACTOR_DOOR_WARP1;
                }
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, tmp16, this->actor.posRot.pos.x, this->actor.posRot.pos.y,
                            this->actor.posRot.pos.z, 0, 0, 0, 0);
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_ITEM_B_HEART, this->actor.posRot.pos.x + 160.0f,
                            this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0, 0, 0, 0);
                D_80966934 = 100;
                Actor_Kill(thisx);
            } else {
                this->actor.colChkInfo.damageTable = D_8095C200;
                D_8096693E = 0xFFFF;
                if (gSaveContext.eventChkInf[7] & 0x40) {
                    D_809668D2 = 8;
                    D_80966934 = 100;
                    func_8002DF54(globalCtx, thisx, 1);
                    globalCtx->envCtx.unk_E2[0] = 0xDC;
                    globalCtx->envCtx.unk_E2[1] = 0xDC;
                    globalCtx->envCtx.unk_E2[2] = 0xBE;
                    globalCtx->envCtx.unk_E2[3] = 0xD2;
                    func_80064520(globalCtx, &globalCtx->csCtx);
                    D_8095C23C = Gameplay_CreateSubCamera(globalCtx);
                    Gameplay_ChangeCameraStatus(globalCtx, 0, 1);
                    Gameplay_ChangeCameraStatus(globalCtx, D_8095C23C, 7);
                    D_809668F8.x = D_809668D8.x = 140.0f;
                    D_809668F8.y = D_809668D8.y = 205.0f;
                    D_809668F8.z = D_809668D8.z = -20.0f;
                    D_80966908.x = D_809668E8.x = 10.0f;
                    D_80966908.y = D_809668E8.y = 50.0f;
                    D_80966908.z = D_809668E8.z = -220.0f;
                    func_800C04D8(globalCtx, D_8095C23C, &D_809668E8, &D_809668D8);
                    this->unk_198 = 0x14;

                    for (i = 15; i > 5; i--) {
                        Actor_SpawnAttached(
                            &globalCtx->actorCtx, thisx, globalCtx, ACTOR_BOSS_VA,
                            D_8095C044[i].x + this->actor.posRot.pos.x, D_8095C044[i].y + this->actor.posRot.pos.y,
                            D_8095C044[i].z + this->actor.posRot.pos.z, D_8095C17C[i].x + this->actor.posRot.rot.x,
                            D_8095C17C[i].y + this->actor.posRot.rot.y, D_8095C17C[i].z + this->actor.posRot.rot.z, i);
                    }

                    sp5C = D_8095C220;
                    D_80966918 = sp5C;
                    D_80966928 = sp5C;

                } else {
                    D_809668D2 = -4;
                    D_80966934 = 5;
                }

                this->unk_1CC.x = 1.0f;
                Collider_InitCylinder(globalCtx, &this->collider1);
                Collider_SetCylinder(globalCtx, &this->collider1, thisx, &sCylinderInit);

                for (i = 5; i >= 0; i--) {
                    Actor_SpawnAttached(
                        &globalCtx->actorCtx, thisx, globalCtx, ACTOR_BOSS_VA,
                        D_8095C044[i].x + this->actor.posRot.pos.x, D_8095C044[i].y + this->actor.posRot.pos.y,
                        D_8095C044[i].z + this->actor.posRot.pos.z, D_8095C17C[i].x + this->actor.posRot.rot.x,
                        D_8095C17C[i].y + this->actor.posRot.rot.y, D_8095C17C[i].z + this->actor.posRot.rot.z, i);
                }

                Lib_MemSet((u8*)D_8095DF50, 0x8980, 0);
                if (D_809668D2 < 0xD) {
                    func_809506F0(this);
                } else {
                    func_809517A0(this);
                }
            }
            break;

        case 0:
        case 1:
        case 2:
            Collider_InitJntSph(globalCtx, &this->collider2);
            Collider_SetJntSph(globalCtx, &this->collider2, thisx, &sJntSphInit, this->unk_2F8);
            if (D_809668D2 < 0xD) {
                func_80953F4C(this, globalCtx);
            } else {
                func_809540E4(this, globalCtx);
            }
            this->unk_194++;
            break;

        case 3:
        case 4:
        case 5:
            Collider_InitQuad(globalCtx, &this->collider3);
            Collider_SetQuad(globalCtx, &this->collider3, thisx, &sQuadInit);
            if (D_809668D2 < 0xD) {
                func_80954A3C(this, globalCtx);
            } else {
                func_80954B8C(this, globalCtx);
            }
            break;

        case 16:
        case 17:
        case 18:
            func_80954924(this, globalCtx);
            break;

        case 19:
            func_80957C9C(this, globalCtx);
            break;

        default:
            Collider_InitJntSph(globalCtx, &this->collider2);
            Collider_SetJntSph(globalCtx, &this->collider2, thisx, &sJntSphInit, this->unk_2F8);
            Collider_InitQuad(globalCtx, &this->collider3);
            Collider_SetQuad(globalCtx, &this->collider3, thisx, &sQuadInit);
            this->unk_1D8.x = 1.0f;
            this->unk_1D8.y = 1.0f;
            if (D_809668D2 < 0xD) {
                func_809567D0(this, globalCtx);
            } else if (D_809668D1 >= 9) {
                func_80956E38(this, globalCtx);
            } else {
                func_809572DC(this, globalCtx);
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/BossVa_Init.s")
#endif

void BossVa_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BossVa* this = THIS;

    SkelAnime_Free(&this->skelAnime, globalCtx);
    Collider_DestroyJntSph(globalCtx, &this->collider2);
    Collider_DestroyCylinder(globalCtx, &this->collider1);
}

void func_809506F0(BossVa* this) {
    f32 frames = SkelAnime_GetFrameCount(&D_06005184.genericHeader);

    SkelAnime_ChangeAnim(&this->skelAnime, &D_06005184, 1.0f, frames, frames, 2, 0.0f);
    this->actor.shape.unk_08 = -450.0f;
    this->actor.flags &= -2;
    func_8094F2C0(this, func_80950780);
}

#ifdef NON_MATCHING
// stack var 0x44 missing
// something weird with the sp5C loads too for regalloc
void func_80950780(BossVa* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = PLAYER; // sp68
    Vec3f sp5C;
    s32 i;
    s16 tmp16;

    this->unk_1AC += 0xC31;
    this->unk_1A0 = (Math_Coss(this->unk_1AC) * 0.1f) + 1.0f;
    this->unk_1A4 = (Math_Sins(this->unk_1AC) * 0.05f) + 1.0f;

    switch (D_809668D2) {
        case -5:
            this->unk_198--;
            if (this->unk_198 == 0) {
                D_809668D2 = -2;
                this->unk_198 = 10;
            }
            break;

        case -4:
            globalCtx->envCtx.unk_E2[0] = 0xDC;
            globalCtx->envCtx.unk_E2[1] = 0xDC;
            globalCtx->envCtx.unk_E2[2] = 0xBE;
            globalCtx->envCtx.unk_E2[3] = 0xD2;
            func_8002DF54(globalCtx, &this->actor, 8);
            player->actor.shape.rot.y = 0x7FFF;
            player->actor.posRot.rot.y = player->actor.shape.rot.y;
            D_809668D2++;
            break;

        case -3:
            func_80064520(globalCtx, &globalCtx->csCtx);
            if (D_8095C23C == 0) {
                D_8095C23C = Gameplay_CreateSubCamera(globalCtx);
            }
            Gameplay_ChangeCameraStatus(globalCtx, 0, 1);
            Gameplay_ChangeCameraStatus(globalCtx, D_8095C23C, 7);

            D_809668F8.x = D_809668D8.x = 13.0f;
            D_809668F8.y = D_809668D8.y = 124.0f;
            D_809668F8.z = D_809668D8.z = 167.0f;

            D_80966908.x = D_809668E8.x = player->actor.posRot.pos.x;
            D_80966908.y = D_809668E8.y = player->actor.posRot.pos.y;
            D_80966908.z = D_809668E8.z = player->actor.posRot.pos.z;

            sp5C = D_8095C220;
            D_80966918 = sp5C;
            D_80966928 = sp5C;

            this->unk_198 = 10;
            D_809668D2++;
            break;

        case -2:
            this->unk_198--;
            if (this->unk_198 == 0) {
                func_8002DF54(globalCtx, &this->actor, 2);
                D_809668D2++;
                this->unk_198 = 30;
            }
            break;

        case -1:
            this->unk_198--;
            if (this->unk_198 == 0) {
                D_809668D2++;
            }
            if (Math_Rand_ZeroOne() < 0.1f) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
            }
            break;

        case 0:
            func_8002DF54(globalCtx, &this->actor, 1);
            D_809668D2++;
            break;

        case 1:
            func_80064520(globalCtx, &globalCtx->csCtx);
            if (D_8095C23C == 0) {
                D_8095C23C = Gameplay_CreateSubCamera(globalCtx);
            }
            Gameplay_ChangeCameraStatus(globalCtx, 0, 1);
            Gameplay_ChangeCameraStatus(globalCtx, D_8095C23C, 7);

            D_809668F8.x = D_809668D8.x = 13.0f;
            D_809668F8.y = D_809668D8.y = 124.0f;
            D_809668F8.z = D_809668D8.z = 167.0f;

            D_80966908.x = D_809668E8.x = player->actor.posRot.pos.x;
            D_80966908.y = D_809668E8.y = player->actor.posRot.pos.y;
            D_80966908.z = D_809668E8.z = player->actor.posRot.pos.z;

            sp5C = D_8095C220;
            D_80966918 = sp5C;
            D_80966928 = sp5C;

            for (i = 15; i > 5; i--) {
                Actor_SpawnAttached(
                    &globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_VA,
                    D_8095C044[i].x + this->actor.posRot.pos.x, D_8095C044[i].y + this->actor.posRot.pos.y,
                    D_8095C044[i].z + this->actor.posRot.pos.z, D_8095C17C[i].x + this->actor.posRot.rot.x,
                    D_8095C17C[i].y + this->actor.posRot.rot.y, D_8095C17C[i].z + this->actor.posRot.rot.z, i);
            }

            this->unk_198 = 0x5A;
            D_809668D2++;
            break;

        case 3:
            D_809668F8.x = -92.0f;
            D_809668F8.y = 22.0f;
            D_809668F8.z = 360.0f;
            D_80966908.x = 63.0f;
            D_80966908.y = 104.0f;
            D_80966908.z = 248.0f;
            Math_SmoothScaleMaxMinF(&D_80966918.x, 7.0f, 0.3f, 0.7f, 0.05f);
            D_80966918.z = D_80966918.x;
            D_80966918.y = D_80966918.z;
            D_80966928 = D_80966918;

            this->unk_198--;
            if (this->unk_198 == 0) {
                D_809668D2++;
                this->unk_198 = 0x3C;
            }
            break;

        case 4:
            D_809668F8.x = D_809668D8.x = 140.0f;
            D_809668F8.y = D_809668D8.y = 205.0f;
            D_809668F8.z = D_809668D8.z = -20.0f;

            D_80966908.x = D_809668E8.x = 10.0f;
            D_80966908.y = D_809668E8.y = 247.0f;
            D_80966908.z = D_809668E8.z = -220.0f;

            D_809668D2++;
            this->unk_198 = 1;
            break;

        case 5:
            D_80966908.x = 10.0f;
            D_80966908.y = 247.0f;
            D_80966908.z = -220.0f;
            Math_SmoothScaleMaxMinF(&D_80966918.x, 7.0f, 0.3f, 0.7f, 0.05f);
            D_80966918.z = D_80966918.x;
            D_80966918.y = D_80966918.z;
            D_80966928 = D_80966918;

            this->unk_198--;
            if (this->unk_198 == 0) {
                D_809668D2++;
                this->unk_198 = 0x28;
            }
            break;

        case 6:
            this->unk_198--;
            if (this->unk_198 == 0) {
                D_80966908.x = 10.0f;
                D_80966908.y = 50.0f;
                D_80966908.z = -220.0f;

                sp5C = D_8095C220;
                D_80966918 = sp5C;
                D_80966928 = sp5C;

                D_809668D2++;
                D_809668D2++;
                this->unk_198 = 20;
            }
            break;

        case 8:
            Math_SmoothScaleMaxMinF(&D_80966918.x, 14.0f, 0.3f, 1.0f, 0.25f);

            D_80966918.y = D_80966918.x * 0.7f;
            D_80966918.z = D_80966918.x;

            D_80966928 = D_80966918;
            D_80966928.z = D_80966928.z * 1.75f;

            this->unk_198--;
            if (this->unk_198 == 0) {
                D_809668D2++;
                this->unk_198 = 0x1D4C;
                this->unk_1F2 = 0;
            }
            break;

        case 9:
            for (i = 10; i > 0; i--) {
                if (D_8095C230[i - 1]) {
                    if (D_8095C230[i - 1] == 1) {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_STICK);
                        func_8094FB6C(globalCtx);
                        if (this->unk_194 == 0) {
                            this->unk_194 = 2;
                        }
                    } else {
                        if (D_8095C230[i - 1] == 2) {
                            func_8094F864(globalCtx, this, 6, 0x8C, 50.0f, 30.0f, 2, i, 1);
                        }
                    }

                    if (D_8095C230[i - 1] < 3) {
                        D_8095C230[i - 1]++;
                    }
                }
            }

            Math_SmoothScaleMaxMinS(&this->unk_1F2, 0x280, 1, 0x32, 0);
            Math_SmoothScaleMaxMinF(&D_80966918.x, 14.0f, 0.3f, 1.0f, 0.25f);
            D_80966918.z = D_80966918.x;
            D_80966928 = D_80966918;
            if (this->unk_198 >= 0xAFC8) {
                globalCtx->envCtx.unk_BF = 1;
                func_8002DF54(globalCtx, &this->actor, 8);
            } else if (this->unk_198 >= 0x88B8) {
                Audio_SetBGM(0x1B);
            }

            this->unk_198 += this->unk_1F2;
            if (this->unk_198 >= 0x10000) {
                D_80966918.y = D_80966928.y = 9.8f;
                D_809668D2++;

                D_809668F8.x = 10.0f;
                D_809668F8.z = 0.0f;

                D_80966908.x = 10.0f;
                D_80966908.y = 140.0f;
                D_80966908.z = -200.0f;

                if (!(gSaveContext.eventChkInf[7] & 0x40)) {
                    TitleCard_InitBossName(globalCtx, &globalCtx->actorCtx.titleCtx, SEGMENTED_TO_VIRTUAL(&D_06001230),
                                           0xA0, 0xB4, 0x80, 0x28);
                }

                if (Math_Rand_ZeroOne() < 0.1f) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
                }

                this->unk_198 = 0x28;
            } else {
                D_80966918.y = 1.6f;
                D_809668F8.y = 5.0f;
                D_809668F8.x = Math_Sins(this->unk_198) * 200.0f;
                D_809668F8.z = (Math_Coss(this->unk_198) * 200.0f) + -200.0f;
            }
            break;

        case 10:
            func_8094F864(globalCtx, this, 3, 0x8C, 50.0f, 30.0f, 2, 10.0f, 0);
            this->unk_198--;
            if (this->unk_198 == 0) {
                D_809668D2++;
                this->unk_198 = 0x2D;
            }
            break;

        case 11:
            func_8094F864(globalCtx, this, 3, 0x8C, 50.0f, 30.0f, 2, 10.0f, 0);
            this->unk_198--;
            if (this->unk_198 == 0) {
                D_809668D2++;
                this->unk_198 = 0xB;
            }
            break;

        case 12:
            this->unk_198--;
            if (this->unk_198 == 0) {
                Gameplay_ClearCamera(globalCtx, D_8095C23C);
                D_8095C23C = 0;
                func_80064534(globalCtx, &globalCtx->csCtx);
                Gameplay_ChangeCameraStatus(globalCtx, 0, 7);
                func_8002DF54(globalCtx, &this->actor, 7);
                D_809668D2++;
                gSaveContext.eventChkInf[7] |= 0x40;
                tmp16 = this->actor.yawTowardsLink + 0x8000;
                player->actor.posRot.rot.y = tmp16;
                player->actor.shape.rot.y = tmp16;
            }
            break;

        case 13:
            func_809517A0(this);
            break;
    }

    if (D_809668D2 >= 5) {
        func_800F436C(&this->actor.projectedPos, 0x313C, 1.0f);
        if ((D_809668D2 >= 8) && ((globalCtx->gameplayFrames % 4) == 0)) {
            func_8094F864(globalCtx, this, 1, 0x64, 50.0f, 10.0f, 5, 10.0f, 0);
        }
    }

    this->unk_1B0 += 0xCE4;
    this->unk_1AE = (s16)(Math_Sins(this->unk_1B0) * 50.0f) + 0x96;
    if ((D_8095C23C != 0) && (D_809668D2 < 0xB)) {
        Math_SmoothScaleMaxMinF(&D_809668D8.x, D_809668F8.x, 0.3f, D_80966918.x, 0.075f);
        Math_SmoothScaleMaxMinF(&D_809668D8.y, D_809668F8.y, 0.3f, D_80966918.y, 0.075f);
        Math_SmoothScaleMaxMinF(&D_809668D8.z, D_809668F8.z, 0.3f, D_80966918.z, 0.075f);
        Math_SmoothScaleMaxMinF(&D_809668E8.x, D_80966908.x, 0.3f, D_80966928.x, 0.075f);
        Math_SmoothScaleMaxMinF(&D_809668E8.y, D_80966908.y, 0.3f, D_80966928.y, 0.075f);
        Math_SmoothScaleMaxMinF(&D_809668E8.z, D_80966908.z, 0.3f, D_80966928.z, 0.075f);
        func_800C04D8(globalCtx, D_8095C23C, &D_809668E8, &D_809668D8);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80950780.s")
#endif

void func_809517A0(BossVa* this) {
    f32 frames = SkelAnime_GetFrameCount(&D_06005184.genericHeader);

    SkelAnime_ChangeAnim(&this->skelAnime, &D_06005184, 1.0f, frames, frames, 2, 0.0f);
    this->actor.shape.unk_08 = -450.0f;
    this->actor.flags = this->actor.flags & -2;
    this->unk_198 = 0x19;
    D_809668D0 = 0x80;
    func_8094F2C0(this, func_80951844);
}

void func_80951844(BossVa* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->unk_1B0 += 0xCE4;
    this->unk_1AE = (s16)(Math_Sins(this->unk_1B0) * 50.0f) + 0x96;
    if (this->unk_198 != 0) {
        this->unk_198--;
        if (this->unk_198 == 0) {
            D_809668D0 &= 0x7F;
        }
    }

    if (this->collider1.base.atFlags & 2) {
        this->collider1.base.atFlags &= ~2;
        if (this->collider1.base.at == &player->actor) {
            func_8002F71C(globalCtx, &this->actor, 8.0f, this->actor.yawTowardsLink, 8.0f);
        }
    }

    if ((D_809668D0 % 128) != 0) {
        this->skelAnime.animCurrentFrame = 0.0f;
        func_8003426C(&this->actor, 0, 0xFF, 0, 0xC);
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_DAMAGE);
    }

    if ((SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) && (D_809668D1 >= 3)) {
        func_80951AD8(this, globalCtx);
    }

    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.x, this->actor.posRot.rot.x, 1, 0xC8, 0);
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.z, this->actor.posRot.rot.z, 1, 0xC8, 0);
    this->unk_1AC += 0xC31;
    this->unk_1A0 = (Math_Coss(this->unk_1AC) * 0.1f) + 1.0f;
    this->unk_1A4 = (Math_Sins(this->unk_1AC) * 0.05f) + 1.0f;
    if ((globalCtx->gameplayFrames % 4) == 0) {
        func_8094F864(globalCtx, this, 1, 0x64, 50.0f, 10.0f, 2, 10.0f, 0);
    }

    if (Math_Rand_ZeroOne() < 0.1f) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
    }

    Collider_CylinderUpdate(&this->actor, &this->collider1);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    func_800F436C(&this->actor.projectedPos, 0x313C, 1.0f);
}

void func_80951AD8(BossVa* this, GlobalContext* globalCtx) {
    s32 i;

    D_809668D1++;
    for (i = 10; i > 5; i--) {
        Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_VA,
                            D_8095C044[i].x + this->actor.posRot.pos.x, D_8095C044[i].y + this->actor.posRot.pos.y,
                            D_8095C044[i].z + this->actor.posRot.pos.z, D_8095C17C[i].x + this->actor.posRot.rot.x,
                            D_8095C17C[i].y + this->actor.posRot.rot.y, D_8095C17C[i].z + this->actor.posRot.rot.z, i);
    }

    this->unk_196 = 0;
    this->actor.flags |= 1;
    func_8094F2C0(this, func_80951C04);
}

// Warning on 196 comparison due to data type
void func_80951C04(BossVa* this, GlobalContext* globalCtx) {
    Player* player = PLAYER; // sp54
    Vec3f sp48;

    if (this->actor.dmgEffectTimer == 0) {
        D_8096693E++;
        if ((this->unk_196 != 0) && (this->actor.dmgEffectParams & 0x4000)) {
            func_8003426C(&this->actor, 0, 0xFF, 0, 0xA0);
            this->actor.dmgEffectTimer = this->unk_196;
        } else {
            this->collider1.body.bumper.flags = 0x10;
        }
    }

    if (this->collider1.base.acFlags & 2) {
        this->collider1.base.acFlags &= ~2;

        if (this->collider1.base.ac->id == ACTOR_EN_BOOM) {
            D_8096693E &= 0xFE00;
            func_8003426C(&this->actor, 0, 0xFF, 0, 0xA0);
            this->collider1.body.bumper.flags = 0xFC00712;
        } else {
            D_8095C22C++;
            if ((this->actor.dmgEffectTimer != 0) && !(this->actor.dmgEffectParams & 0x4000)) {
                this->unk_196 = this->actor.dmgEffectTimer - 5;
                if (this->unk_196 >= 0xA1) {
                    this->unk_196 = 0;
                }
            }

            func_8003426C(&this->actor, 0x4000, 0xFF, 0, 0xC);
        }

        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_FAINT);
    }

    if (this->collider1.base.atFlags & 2) {
        this->collider1.base.atFlags &= ~2;

        D_8096693E = (D_8096693E + 0x18) & 0xFFF0;
        if (this->collider1.base.at == &player->actor) {
            func_8002F71C(globalCtx, &this->actor, 8.0f, this->actor.yawTowardsLink, 8.0f);
            Audio_PlayActorSound2(&player->actor, NA_SE_PL_BODY_HIT);
        }
    }

    if ((D_8096693E >= 0xB) && !(D_8096693E & 7) && (1.0f == this->actor.speedXZ)) {
        sp48 = this->actor.posRot.pos;
        sp48.y += 310.0f + (this->actor.shape.unk_08 * this->actor.scale.y);
        sp48.x += -10.0f;
        sp48.z += 220.0f;
        func_8095B318(globalCtx, D_8095DF50, this, &sp48, 4, 0);
    }

    if (Math_Rand_ZeroOne() < 0.1f) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
    }

    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.x, this->actor.posRot.rot.x, 1, 0xC8, 0);
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.z, this->actor.posRot.rot.z, 1, 0xC8, 0);
    Math_SmoothScaleMaxMinF(&this->actor.shape.unk_08, -1000.0f, 1.0f, 20.0f, 0.0f);
    if (!(D_8096693E & 0x100)) {
        this->actor.flags |= 1;
        this->actor.speedXZ = 1.0f;
    } else {
        this->actor.flags &= ~1;
        this->actor.speedXZ = 0.0f;
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) && (D_809668D1 >= 9)) {
        func_80952100(this);
    }

    this->unk_1AC += 0xC31;
    this->unk_1A0 = (Math_Coss(this->unk_1AC) * 0.1f) + 1.0f;
    this->unk_1A4 = (Math_Sins(this->unk_1AC) * 0.05f) + 1.0f;
    if ((globalCtx->gameplayFrames % 4) == 0) {
        func_8094F864(globalCtx, this, 1, 0x64, 50.0f, 10.0f, 5, 10.0f, 0);
    }

    this->actor.posRot2.pos = this->actor.posRot.pos;
    this->actor.posRot2.pos.y += 45.0f;

    Collider_CylinderUpdate(&this->actor, &this->collider1);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    if (this->actor.dmgEffectTimer == 0) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    }

    if ((this->actor.dmgEffectTimer == 0) || !(this->actor.dmgEffectParams & 0x4000)) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    }

    func_800F436C(&this->actor.projectedPos, 0x313C, (this->unk_1F6.y * 0.00025f) + 1.0f);
}

void func_80952100(BossVa* this) {
    this->collider1.body.bumper.flags = 0x10;
    this->actor.speedXZ = 0.0f;
    D_80966936 = 0;
    func_8094F2C0(this, func_8095213C);
}

void func_8095213C(BossVa* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = PLAYER;
    s32 i;
    s16 sp62;

    sp62 = Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.initPosRot.pos);
    this->unk_1B0 += 0xCE4;
    this->unk_1AE = (s16)(Math_Sins(this->unk_1B0) * 50.0f) + 0x96;
    if (this->collider1.base.atFlags & 2) {
        this->collider1.base.atFlags &= ~2;
        if (this->collider1.base.at == &player->actor) {
            func_8002F71C(globalCtx, &this->actor, 8.0f, this->actor.yawTowardsLink, 8.0f);
            this->actor.posRot.rot.y += (s16)Math_Rand_CenteredFloat(12000.0f) + 0x8000;
            Audio_PlayActorSound2(&player->actor, NA_SE_PL_BODY_HIT);
        }
    }

    if (this->collider1.base.acFlags & 2) {
        this->skelAnime.animCurrentFrame = 0.0f;
        func_8003426C(&this->actor, 0, 0xFF, 0, 0xC);
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_FAINT);
        D_809668D0 = 1;
        this->unk_198 = 0x83;
        this->actor.flags &= ~1;
    } else {
        D_809668D0 = 0;
        if (this->unk_198 == 0) {
            if (Math_SmoothScaleMaxMinS(&this->unk_1F6.y, 0xFA0, 1, 0x12C, 0) == 0) {
                if (this->actor.speedXZ == 0.0f) {
                    this->actor.posRot.rot.y = this->actor.yawTowardsLink;
                }
                Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 3.0f, 1.0f, 0.15f, 0.0f);
            }
            this->actor.flags |= 1;
        } else {
            this->unk_198--;
            if (this->unk_198 < 0x23) {
                D_809668D0 = 0x80;
            }
            Math_SmoothScaleMaxMinS(&this->unk_1F6.y, 0, 1, 0x12C, 0);
            Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 1.0f, 0.2f, 0.0f);
            Math_SmoothScaleMaxMinF(&this->actor.shape.unk_08, -1420.0f, 1.0f, 30.0f, 0.0f);
        }
    }

    if (Math_Vec3f_DistXZ(&this->actor.posRot.pos, &this->actor.initPosRot.pos) >= 400.0f) {
        Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, sp62, 1, 0x3E8, 0);
    } else if (player->invincibilityTimer != 0) {
        Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, this->actor.yawTowardsLink + 0x8000, 1, 0x12C, 0);
    } else if ((globalCtx->gameplayFrames & 0x80) == 0) {
        Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, this->actor.yawTowardsLink, 1, 0x12C, 0);
    } else {
        Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, sp62, 1, 0x258, 0);
    }

    if (D_80966936 != 0) {
        this->actor.speedXZ = 0.0f;
    }

    Actor_MoveForward(&this->actor);
    if ((SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) && (D_809668D1 >= 0xF)) {
        func_809527A4(this, globalCtx);
    }

    this->actor.shape.rot.y += this->unk_1F6.y;
    if (D_809668D1 == 9) {
        Math_SmoothScaleMaxMinF(&this->actor.shape.unk_08, -450.0f, 1.0f, 15.0f, 0.0f);
    } else {
        Math_SmoothScaleMaxMinF(&this->actor.shape.unk_08, -810.0f, 1.0f, 15.0f, 0.0f);
    }

    if ((this->actor.shape.unk_08 >= -500.0f) && (D_809668D1 == 9)) {
        for (i = 15; i > 10; i--) {
            Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_BOSS_VA,
                                D_8095C044[i].x + this->actor.posRot.pos.x, D_8095C044[i].y + this->actor.posRot.pos.y,
                                D_8095C044[i].z + this->actor.posRot.pos.z, D_8095C17C[i].x + this->actor.posRot.rot.x,
                                D_8095C17C[i].y + this->actor.posRot.rot.y, D_8095C17C[i].z + this->actor.posRot.rot.z,
                                i);
        }
        D_809668D1++;
    }

    this->unk_1AC += 0xC31;
    this->unk_1A0 = (Math_Coss(this->unk_1AC) * 0.1f) + 1.0f;
    this->unk_1A4 = (Math_Sins(this->unk_1AC) * 0.05f) + 1.0f;
    if ((globalCtx->gameplayFrames % 4) == 0) {
        func_8094F864(globalCtx, this, 1, 0x64, 50.0f, 10.0f, 5, 10.0f, 0);
    }

    this->actor.posRot2.pos = this->actor.posRot.pos;
    this->actor.posRot2.pos.y += 20.0f;
    if (Math_Rand_ZeroOne() < 0.1f) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
    }

    Collider_CylinderUpdate(&this->actor, &this->collider1);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    if (this->unk_198 == 0) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    }

    func_800F436C(&this->actor.projectedPos, 0x313C, (this->unk_1F6.y * 0.00025f) + 1.0f);
}

void func_809527A4(BossVa* this, GlobalContext* globalCtx) {
    this->unk_1AC = 0;
    this->actor.flags |= 1;
    this->unk_1F6.y = this->unk_1AC;
    this->actor.posRot.rot.y = this->actor.yawTowardsLink;
    this->unk_19C = (s16)(Math_Rand_ZeroOne() * 150.0f) + 0x12C;
    D_809668D0 = 1;
    D_80966940 = 4;
    if (this->actor.shape.unk_08 != 0.0f) {
        this->unk_198 = -0x1E;
    }

    this->collider1.dim.radius = 55;
    func_8094F2C0(this, func_80952858);
}

void func_80952858(BossVa* this, GlobalContext* globalCtx) {
    Player* player = PLAYER; // sp54
    f32 tmpf1;
    EnBoom* refActor;

    this->unk_1B0 = (this->unk_1B0 + (s16)((D_809668D1 - 0xE) * 1000.0f)) + 0xCE4;
    this->unk_1AE = (s16)(Math_Sins(this->unk_1B0) * 50.0f) + 0x96;
    if (this->collider1.base.atFlags & 2) {
        this->collider1.base.atFlags &= ~2;
        if (this->collider1.base.at == &player->actor) {
            func_8002F71C(globalCtx, &this->actor, 8.0f, this->actor.yawTowardsLink, 8.0f);
            this->actor.posRot.rot.y += (s16)Math_Rand_CenteredFloat(12000.0f) + 0x8000;
            Audio_PlayActorSound2(&player->actor, NA_SE_PL_BODY_HIT);
        }
    }
    if (Math_Rand_ZeroOne() < 0.1f) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
    }

    if ((this->collider1.base.acFlags & 2) != 0) {
        this->collider1.base.acFlags &= ~2;
        this->skelAnime.animCurrentFrame = 0.0f;
        if (this->unk_198 >= 0) {
            if (this->unk_196 == 0) {
                this->unk_196 = 8;
                if (this->actor.colChkInfo.damageEffect != 1) {
                    this->actor.posRot.rot.y = this->actor.yawTowardsLink;
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_DAMAGE);
                    func_8003426C(&this->actor, 0x4000, 0xFF, 0, 0xC);
                    D_80966940 -= this->actor.colChkInfo.damage;
                    if (D_80966940 <= 0) {
                        this->unk_198 = 0;
                        D_809668D1++;
                        D_80966940 += 3;
                        if (D_809668D1 >= 0x12) {
                            func_8095335C(this, globalCtx);
                            func_80032C7C(globalCtx, &this->actor);
                            return;
                        }

                        this->actor.speedXZ = -10.0f;
                        this->unk_198 = -0xAA - (s16)(Math_Rand_ZeroOne() * 150.0f);
                    }
                } else {
                    this->unk_198 = (s16)Math_Rand_CenteredFloat(40.0f) + 0xA0;
                    this->unk_1F6.y = 0;
                    this->actor.speedXZ = 0.0f;
                    func_8003426C(&this->actor, 0, 0x7D, 0, 0xFF);
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_FAINT);
                }
            }
        } else if (this->collider1.base.ac->id == ACTOR_EN_BOOM) {
            refActor = (EnBoom*)this->collider1.base.ac;
            refActor->returnTimer = 0;
            refActor->moveTo = &player->actor;
            refActor->actor.posRot.rot.y = refActor->actor.yawTowardsLink;
            Audio_PlayActorSound2(&this->actor, NA_SE_IT_SHIELD_REFLECT_SW);
        }
    } else if ((this->unk_19C == 0) && (0.0f == this->actor.shape.unk_08)) {
        this->unk_198 = -0xDC - (s16)(Math_Rand_ZeroOne() * 200.0f);
    } else if (this->unk_19C != 0) {
        this->unk_19C--;
    }

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_198 == 0) {
        Math_SmoothScaleMaxMinF(&this->actor.shape.unk_08, 0.0f, 1.0f, ((D_809668D1 - 0xE) * 5.0f) + 10.0f, 0.0f);
        if (Math_SmoothScaleMaxMinS(&this->unk_1F6.y, (s16)((D_809668D1 - 0xE) * 500.0f) + 0xFA0, 1, 0x12C, 0) == 0) {
            if (this->actor.speedXZ == 0.0f) {
                this->actor.dmgEffectTimer = 0;
                this->actor.posRot.rot.y = this->actor.yawTowardsLink;
                this->unk_19C = (s16)(Math_Rand_ZeroOne() * 150.0f) + 0x12C;
            }
            Math_SmoothScaleMaxMinF(&this->actor.speedXZ, ((D_809668D1 - 0xE) * 1.5f) + 4.0f, 1.0f, 0.25f, 0.0f);
        }
        this->collider1.body.bumper.flags = 0x10;
    } else {
        Math_SmoothScaleMaxMinS(&this->unk_1F6.y, 0, 1, 0x96, 0);
        if (this->unk_198 > 0) {
            if ((player->stateFlags1 & 0x4000000) && (this->unk_198 >= 0x24)) {
                this->unk_198 = 0x23;
            }

            Math_SmoothScaleMaxMinF(&this->actor.shape.unk_08, -480.0f, 1.0f, 30.0f, 0.0f);
            this->collider1.body.bumper.flags = 0xFC00712;
            this->unk_198--;
        } else {
            if ((player->stateFlags1 & 0x4000000) && (this->unk_198 < -0x3C)) {
                this->unk_198 = -0x3B;
            }

            if ((globalCtx->gameplayFrames % 4) == 0) {
                func_8094F864(globalCtx, this, 2, 0x64, 220.0f, 5.0f, 5, 12.0f, 1);
            }

            if (this->unk_198 < -0x1E) {
                if (this->actor.speedXZ > 0.0f) {
                    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 1.0f, 0.5f, 0.0f);
                }

                Math_SmoothScaleMaxMinF(&this->actor.shape.unk_08, -1400.0f, 1.0f, 60.0f, 0.0f);
            } else {
                if (this->actor.speedXZ == 0.0f) {
                    this->actor.posRot.rot.y = this->actor.yawTowardsLink + 0x8000;
                    this->unk_19C = (s16)(Math_Rand_ZeroOne() * 150.0f) + 0x14A;
                }

                Math_SmoothScaleMaxMinS(&this->unk_1F6.y, 0xFA0, 1, 0x1F4, 0);
                tmpf1 = D_809668D1 - 0xE;
                Math_SmoothScaleMaxMinF(&this->actor.speedXZ, (tmpf1 + tmpf1) + 4.0f, 1.0f, 0.25f, 0.0f);
                Math_SmoothScaleMaxMinF(&this->actor.shape.unk_08, 0.0f, 1.0f, 20.0f, 0.0f);
            }
            this->unk_198++;
        }
    }

    this->actor.shape.rot.y = this->actor.shape.rot.y + this->unk_1F6.y;
    if (this->actor.speedXZ < 0.0f) {
        Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 1.0f, 0.5f, 0.0f);
    }

    this->unk_1AC += 0xC31;
    this->unk_1A0 = (Math_Coss(this->unk_1AC) * 0.1f) + 1.0f;
    this->unk_1A4 = (Math_Sins(this->unk_1AC) * 0.05f) + 1.0f;
    if (this->actor.bgCheckFlags & 8) {
        this->actor.bgCheckFlags &= ~8;
        this->actor.posRot.rot.y = (s16)Math_Rand_CenteredFloat(5460.0f) + this->actor.wallPolyRot;
    }

    if (D_809668D1 < 0x10) {
        if (Math_Vec3f_DistXZ(&this->actor.posRot.pos, &this->actor.initPosRot.pos) >= 400.0f) {
            Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y,
                                    Math_Vec3f_Yaw(&this->actor.posRot.pos, &this->actor.initPosRot.pos), 1, 0x5DC, 0);
        } else if (player->invincibilityTimer != 0) {
            Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, this->actor.yawTowardsLink + 0x8000, 1, 0x12C, 0);
        } else if ((globalCtx->gameplayFrames & 0x80) == 0) {
            Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, this->actor.yawTowardsLink, 1,
                                    (s16)((D_809668D1 - 0xE) * 100.0f) + 0x64, 0);
        }
    }

    Actor_MoveForward(&this->actor);
    this->actor.posRot2.pos = this->actor.posRot.pos;
    this->actor.posRot2.pos.y += 60.0f;
    if (((globalCtx->gameplayFrames % 2) == 0) && (this->unk_198 == 0)) {
        func_8094F864(globalCtx, this, 2, 0x7D, 40.0f, 10.0f, 5, 10.0f, 0);
        func_8094F864(globalCtx, this, 1, 0x64, 15.0f, 10.0f, 2, 11.0f, 1);
    }

    func_8002E4B4(globalCtx, &this->actor, 30.0f, 70.0f, 0.0f, 1);
    Collider_CylinderUpdate(&this->actor, &this->collider1);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    if (this->unk_196 == 0) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    }

    if ((this->unk_1F6.y >= 0x3E9) || (this->actor.shape.unk_08 < -1200.0f)) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    }

    func_800F436C(&this->actor.projectedPos, 0x313C, (this->unk_1F6.y * 0.00025f) + 1.0f);
    if (this->unk_196 != 0) {
        this->unk_196--;
        D_809668D0 = (D_809668D0 & 0x80) | 2;
    } else {
        D_809668D0 = (D_809668D0 & 0x80) | 1;
    }
}

void func_8095335C(BossVa* this, GlobalContext* globalCtx) {
    func_800F436C(&this->actor.projectedPos, 0x313C, 1.0f);
    this->actor.flags &= ~5;
    Audio_SetBGM(0x100100FF);
    this->unk_1F6.x = 0xC31;
    D_809668D2 = 0xE;
    this->actor.speedXZ = 0.0f;
    this->unk_1A8 = 0.0f;
    Flags_SetClear(globalCtx, globalCtx->roomCtx.curRoom.num);
    func_8094F2C0(this, func_809533F4);
}

#ifdef NON_MATCHING
// sp68 struct copy regalloc
void func_809533F4(BossVa* this, GlobalContext* globalCtx) {
    s32 sp7C;
    s32 i;
    Camera* camera = Gameplay_GetCamera(globalCtx, 0);
    Player* player = PLAYER; // sp78
    s16 tmp16;
    Vec3f sp68;

    switch (D_809668D2 - 0xE) {
        case 0:
            func_8002DF54(globalCtx, &this->actor, 1);
            func_80064520(globalCtx, &globalCtx->csCtx);
            D_8095C23C = Gameplay_CreateSubCamera(globalCtx);
            Gameplay_ChangeCameraStatus(globalCtx, 0, 1);
            Gameplay_ChangeCameraStatus(globalCtx, D_8095C23C, 7);

            D_80966908.x = this->actor.posRot.pos.x;
            D_80966908.y = this->actor.posRot.pos.y;
            D_80966908.z = this->actor.posRot.pos.z;

            D_809668E8 = camera->at;

            sp68 = camera->eye;
            D_809668D8 = sp68;
            D_809668F8 = sp68;

            D_809668F8.y = 40.0f;
            D_80966908.y = 140.0f;

            sp68 = D_8095C220;
            D_80966918 = sp68;
            D_80966928 = sp68;

            this->unk_1AC = Math_Vec3f_Yaw(&D_809668D8, &D_80966908) - 0x100;
            this->unk_1B0 = 0xF;
            globalCtx->envCtx.unk_E2[0] = globalCtx->envCtx.unk_E2[1] = globalCtx->envCtx.unk_E2[2] = 0xFF;
            globalCtx->envCtx.unk_E2[3] = 0;
            globalCtx->envCtx.unk_E1 = 1;
            D_809668D2++;

        case 1:
            this->unk_1AC += 0x100;
            D_809668F8.x = (Math_Sins(this->unk_1AC) * (160.0f + this->unk_1A8)) + D_80966908.x;
            D_809668F8.z = (Math_Coss(this->unk_1AC) * (160.0f + this->unk_1A8)) + D_80966908.z;
            Math_SmoothScaleMaxMinF(&D_80966918.x, 16.0f, 0.4f, 1.5f, 0.5f);
            D_80966918.z = D_80966918.x;
            D_80966918.y = D_80966918.x * 0.5f;
            D_80966928 = D_80966918;
            tmp16 = Math_Rand_CenteredFloat(0.5f) + ((D_80966918.x * 0.5f) + 0.6f);
            if (((globalCtx->gameplayFrames % 4) == 0) && (this->unk_1B0 != 0)) {
                for (i = 6; i > 1; i--) {
                    func_8094F9E8(globalCtx, this, 1, tmp16, 0.0f, 0.0f, 1, i, 1);
                }

                func_8094F9E8(globalCtx, this, 1, tmp16, 0.0f, 0.0f, 1, 11.0f, 1);
                this->unk_1B0--;
            }

            if (this->unk_1B0 == 0) {
                D_809668D2++;

                sp68 = D_8095C220;
                D_80966918 = sp68;
                D_80966928 = sp68;
            }
            break;

        case 7:
            this->unk_1AC += 0x1862;
            this->unk_1A0 = (Math_Coss(this->unk_1AC) * 0.12f) + 1.0f;
            this->unk_1A4 = (Math_Sins(this->unk_1AC) * 0.075f) + 1.0f;
            if (this->unk_197 == 0) {
                this->unk_195++;
                this->unk_197++;
                this->unk_198 = 0x1E;
                D_809668D2++;
                EffectSsDeadSound_SpawnStationary(globalCtx, &this->actor.projectedPos, 0x3940, 1, 1, 0x28);
                this->unk_194 = 2;
                func_8094FBB4(globalCtx);
                func_8002DF54(globalCtx, &this->actor, 8);
            }
            break;

        case 8:
            if (this->unk_198 == 0xD) {
                Audio_SetBGM(0x21);
            }

            this->unk_198--;
            if (this->unk_198 == 0) {
                D_80966908.x = this->actor.posRot.pos.x;
                D_80966908.y = this->actor.posRot.pos.y + 30.0f;
                D_80966908.z = this->actor.posRot.pos.z;

                D_809668F8.x = (Math_Sins(player->actor.shape.rot.y) * -130.0f) + player->actor.posRot.pos.x;
                D_809668F8.z = (Math_Coss(player->actor.shape.rot.y) * -130.0f) + player->actor.posRot.pos.z;
                D_809668F8.y = player->actor.posRot.pos.y + 55.0f;

                sp68 = D_8095C220;
                D_80966918 = sp68;
                D_80966928 = sp68;

                D_809668D2++;
                this->unk_198 = 0x85;
            }
            break;

        case 9:
            Math_SmoothScaleMaxMinF(&D_80966918.x, 1.5f, 0.3f, 0.05f, 0.015f);
            D_80966918.z = D_80966918.x;
            D_80966918.y = D_80966918.z;
            D_80966928 = D_80966918;

            this->unk_198--;
            if (this->unk_198 == 0) {
                Gameplay_ClearCamera(globalCtx, D_8095C23C);
                D_8095C23C = 0;
                func_80064534(globalCtx, &globalCtx->csCtx);
                Gameplay_ChangeCameraStatus(globalCtx, 0, 7);

                sp68 = D_809668D8;
                camera->eye = sp68;
                camera->eyeNext = sp68;

                camera->at = D_809668E8;

                func_8002DF54(globalCtx, &this->actor, 7);
                D_809668D2++;

                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_ITEM_B_HEART, this->actor.posRot.pos.x,
                            this->actor.posRot.pos.y, this->actor.posRot.pos.z, 0, 0, 0, 0);

                for (i = 2, sp7C = 2; i > 0; i--) {
                    if (Math_Vec3f_DistXYZ(&D_8095C1DC[i], &player->actor.posRot.pos) <
                        Math_Vec3f_DistXYZ(&D_8095C1DC[i - 1], &player->actor.posRot.pos)) {
                        sp7C = i - 1;
                    }
                }

                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_RU1, D_8095C1DC[sp7C].x, D_8095C1DC[sp7C].y,
                            D_8095C1DC[sp7C].z, 0, 0, 0, 0);
            }

        case 10:
            Math_Rand_CenteredFloat(0.5f);
            globalCtx->envCtx.unk_E1 = 0;
            break;
    }

    if (D_8095C23C != 0) {
        Math_SmoothScaleMaxMinF(&D_809668D8.x, D_809668F8.x, 0.3f, D_80966918.x, 0.15f);
        Math_SmoothScaleMaxMinF(&D_809668D8.y, D_809668F8.y, 0.3f, D_80966918.y, 0.15f);
        Math_SmoothScaleMaxMinF(&D_809668D8.z, D_809668F8.z, 0.3f, D_80966918.z, 0.15f);
        Math_SmoothScaleMaxMinF(&D_809668E8.x, D_80966908.x, 0.3f, D_80966928.x, 0.15f);
        Math_SmoothScaleMaxMinF(&D_809668E8.y, D_80966908.y, 0.3f, D_80966928.y, 0.15f);
        Math_SmoothScaleMaxMinF(&D_809668E8.z, D_80966908.z, 0.3f, D_80966928.z, 0.15f);
        func_800C04D8(globalCtx, D_8095C23C, &D_809668E8, &D_809668D8);
    }

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothScaleMaxMinF(&this->actor.shape.unk_08, -480.0f, 1.0f, 30.0f, 0.0f);
    Math_SmoothScaleMaxMinS(&this->unk_1F6.y, 0, 1, 0xC8, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1F6.x, 0, 1, 0xC8, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1AE, 0xC8, 1, 0xA, 0);
    if (globalCtx->envCtx.unk_E2[3] != 0) {
        globalCtx->envCtx.unk_E2[3] -= 50;
    }

    Math_SmoothScaleMaxMinF(&this->actor.speedXZ, 0.0f, 1.0f, 0.5f, 0.0f);
    this->actor.shape.rot.y += this->unk_1F6.y;
    this->unk_1AC += this->unk_1F6.x;

    this->unk_1A0 = (Math_Coss(this->unk_1AC) * 0.1f) + 1.0f;
    this->unk_1A4 = (Math_Sins(this->unk_1AC) * 0.05f) + 1.0f;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809533F4.s")
#endif

void func_80953F4C(BossVa* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_060166A8, 0.0f, 0.0f, SkelAnime_GetFrameCount(&D_060166A8.genericHeader),
                         1, 0.0f);
    this->unk_198 = 0;
    func_8094F2C0(this, func_80953FC4);
}

void func_80953FC4(BossVa* this, GlobalContext* globalCtx) {
    func_8094F2C8(this);
    if (D_809668D2 == 0xD) {
        func_809540E4(this, globalCtx);
    } else if (D_809668D2 >= 3) {
        this->unk_198++;
        if ((this->unk_198 % 2) == 0) {
            func_8094F864(globalCtx, this, 2, 0x5A, 5.0f, 0.0f, 5, ((this->unk_198 & 0x20) >> 5) + 1, 1);
        }

        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        Math_SmoothScaleMaxMinF(&this->skelAnime.animPlaybackSpeed, 1.0f, 1.0f, 0.05f, 0.0f);
        if (Math_Rand_ZeroOne() < 0.1f) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
        }
    }
}

void func_809540E4(BossVa* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_060166A8, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_060166A8.genericHeader),
                         0, 0.0f);
    this->unk_198 = (this->actor.params * 0xA);
    func_8094F2C0(this, func_80954168);
}

void func_80954168(BossVa* this, GlobalContext* globalCtx) {
    this->unk_198++;
    if ((D_809668D0 % 128) != 0) {
        func_8003426C(&this->actor, 0, 0xFF, 0, 0xC);
        if (Math_Rand_ZeroOne() > 0.5f) {
            SkelAnime_ChangeAnim(&this->skelAnime, &D_060162AC, 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_060162AC.genericHeader), 2, 0.0f);
        } else {
            SkelAnime_ChangeAnim(&this->skelAnime, &D_060164B0, 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&D_060164B0.genericHeader), 2, 0.0f);
        }
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        SkelAnime_ChangeAnim(&this->skelAnime, &D_060166A8, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_060166A8.genericHeader), 0, 0.0f);
    }

    func_8094F2C8(this);
    if (Math_Rand_ZeroOne() < 0.1f) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
    }

    if (this->collider2.base.acFlags & 2) {
        func_8095438C(this, globalCtx);
    } else {
        if (this->actor.dmgEffectTimer == 0) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        }

        if ((this->unk_198 & 1) == 0) {
            func_8094F864(globalCtx, this, 1, 0x64, 5.0f, 0.0f, 5, ((this->unk_198 & 0x20) >> 5) + 1, 1);
        }
    }
}

void func_8095438C(BossVa* this, GlobalContext* globalCtx) {
    s32 params = this->actor.params + 16;

    D_809668D0++;
    D_809668D1++;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_BOSS_VA, this->unk_1B4.x, this->unk_1B4.y + 20.0f,
                this->unk_1B4.z, 0, this->actor.shape.rot.y, 0, params);
    func_8005AA1C(&globalCtx->cameras[0], 2, 0xB, 8);
    this->unk_195 = 0;
    this->unk_19C = 0;
    func_8094F2C0(this, func_80954454);
}

#ifdef NON_MATCHING
// Stack, something optimised away at 0x38
void func_80954454(BossVa* this, GlobalContext* globalCtx) {
    BossVa* refActor = (BossVa*)this->actor.attachedA;
    f32 frames;

    func_8094F2C8(this);

    if (this->unk_194 != 0) {
        frames = SkelAnime_GetFrameCount(&D_06017694.genericHeader);
        this->unk_194 = 0;
        this->unk_198 = (s32)(Math_Rand_ZeroOne() * 10.0f) + 5;
        SkelAnime_Free(&this->skelAnime, globalCtx);
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06017FC8, &D_06017694, 0, 0, 0);
        SkelAnime_ChangeAnim(&this->skelAnime, &D_06017694, 1.0f, 0.0f, frames, 2, 0.0f);
        D_809668D0 = 0;
        this->actor.attachedA->shape.unk_08 -= 60.0f;

        switch (this->actor.params) {
            case 0:
                this->actor.attachedA->posRot.rot.x += 0x4B0;
                break;

            case 1:
                this->actor.attachedA->posRot.rot.x -= 0x258;
                this->actor.attachedA->posRot.rot.z -= 0x4E2;
                break;

            case 2:
                this->actor.attachedA->posRot.rot.x -= 0x258;
                this->actor.attachedA->posRot.rot.z += 0x4E2;
                break;
        }
    }

    Math_SmoothScaleMaxMinS(&this->unk_1F6.x, refActor->unk_1F6.y * -3, 1, 0x4B0, 0);
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        SkelAnime_ChangeAnim(&this->skelAnime, &D_060177F4, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&D_060177F4.genericHeader), 1, 0.0f);
        this->actor.flags &= ~1;
    }

    if ((this->unk_198 == 0) && (D_809668D2 < 0xE)) {
        this->unk_198 = (s32)(Math_Rand_ZeroOne() * 10.0f) + 0xA;
        func_8094F50C(globalCtx, &this->unk_1B4, this->unk_1F6.x, this->actor.shape.rot.y);
    }

    if (D_809668D2 >= 0xE) {
        Math_SmoothScaleMaxMinF(&this->skelAnime.animPlaybackSpeed, 0.0f, 0.3f, 0.25f, 0.125f);
    }

    switch (D_809668D2) {
        case 19:
            D_809668D8 = D_809668F8;
            D_809668E8 = D_80966908;
            Math_SmoothScaleMaxMinF(&D_809668D8.x, D_80966908.x, 1.0f, 10.0f, 0.0f);
            Math_SmoothScaleMaxMinF(&D_809668D8.z, D_80966908.z, 1.0f, 10.0f, 0.0f);
            D_809668D8.y += 20.0f;
            D_809668D2++;

        case 20:
        case 21:
        case 22:
            if (this->unk_195 == 0) {
                if ((globalCtx->gameplayFrames % 2) != 0) {
                    func_8094F9E8(globalCtx, this, 1, (s16)Math_Rand_CenteredFloat(5.0f) + 6, 7.0f, 5.0f, 2,
                                  (this->unk_19C >> 3) + 1, 1);
                }

                this->unk_19C++;
                if (this->unk_19C >= 0x20) {
                    this->unk_195++;
                    this->unk_197 = 1;
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BREAK2);
                    if (this->actor.params == 2) {
                        D_809668D2++;
                    }
                }
            } else {
                this->unk_19C--;
                if (this->unk_19C == 0) {
                    Actor_Kill(&this->actor);
                }
            }
            break;
    }

    this->unk_198--;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80954454.s")
#endif

void func_80954924(BossVa* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06018150, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06018150.genericHeader),
                         2, 0.0f);
    this->actor.flags &= ~1;
    func_8094F2C0(this, func_809549A8);
}

void func_809549A8(BossVa* this, GlobalContext* globalCtx) {
    if ((SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) && (Math_Rand_ZeroOne() < 0.3f)) {
        this->skelAnime.animCurrentFrame -= Math_Rand_ZeroOne() * 3.0f;
    }

    if (D_809668D2 >= 0xE) {
        Actor_Kill(&this->actor);
    }
}

void func_80954A3C(BossVa* this, GlobalContext* globalCtx) {
    f32 frames = SkelAnime_GetFrameCount(&D_06018D18.genericHeader);

    SkelAnime_ChangeAnim(&this->skelAnime, &D_06018D18, 1.0f, frames - 1.0f, frames, 1, -6.0f);
    this->actor.flags &= ~1;
    func_8094F2C0(this, func_80954AD0);
}

void func_80954AD0(BossVa* this, GlobalContext* globalCtx) {
    func_8094F2C8(this);

    switch (D_809668D2) {
        case 10:
        case 11:
        case 12:
            SkelAnime_FrameUpdateMatrix(&this->skelAnime);
            break;

        case 13:
            func_80954B8C(this, globalCtx);
            break;
    }

    Math_SmoothScaleMaxMinS(&this->unk_1F2, this->actor.shape.rot.y - this->actor.shape.rot.x, 1, 0x2EE, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1F0, this->skelAnime.limbDrawTbl[7].z, 1, 0x2EE, 0);
}

void func_80954B8C(BossVa* this, GlobalContext* globalCtx) {
    f32 frames = SkelAnime_GetFrameCount(&D_06018D18.genericHeader);

    SkelAnime_ChangeAnim(&this->skelAnime, &D_06018D18, 1.0f, frames - 1.0f, frames, 1, -6.0f);
    this->actor.flags &= ~1;
    func_8094F2C0(this, func_80954C20);
}

#ifdef NON_MATCHING
// Stack, refActor stuff at the top is screwy and the cause I think
// sp88 < sp90 line gives a type warning, but can't figure out how to fix
void func_80954C20(BossVa* this, GlobalContext* globalCtx) {
    Player* player = PLAYER; // spA4
    EnBoom* refActor;        // spA0
    Actor* movingActor;      // sp9C
    s16 sp9A_pad;
    s16 sp98;
    s16 sp96;
    s16 sp94;
    s16 sp92_pad;
    s16 sp90 = 0x1F4;
    s16 sp8E;
    s16 tmp17;
    u32 sp88;
    Vec3f sp7C;
    s32 sp78_pad;
    f32 sp74;
    s32 i; // sp70
    s16 sp6E;
    s16 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    s16 sp5A;
    s16 sp58;
    s16 sp56;
    s16 sp54;
    f32 sp50;
    Vec3f sp44;
    // 0x10 bytes added here, stuff below should be done by compiler
    s32 sp40_pad;
    Collider* collider;            // sp3C
    CollisionCheckContext* colCtx; // sp40

    refActor = func_8094FC30(globalCtx);

    if ((refActor == NULL) || (refActor->moveTo == NULL) || (refActor->moveTo == &player->actor)) {
        sp7C = player->actor.posRot.pos;
        sp7C.y += 10.0f;
        sp8E = 0x3E80;
    } else {

        sp74 = R_UPDATE_RATE * 0.5f;
        sp8E = 0x4650;

        movingActor = refActor->moveTo;
        sp7C = refActor->actor.posRot.pos;
        sp6C = refActor->actor.posRot.rot.y;
        sp56 = refActor->actor.posRot.rot.x;

        for (i = refActor->returnTimer; i >= 3; i--) {
            sp6E = Math_Vec3f_Yaw(&sp7C, &movingActor->posRot2.pos);
            sp5A = sp6C - sp6E;
            sp58 = Math_Vec3f_Pitch(&sp7C, &movingActor->posRot2.pos);
            sp54 = sp56 - sp58;

            sp50 = (200.0f - Math_Vec3f_DistXYZ(&sp7C, &movingActor->posRot2.pos)) * 0.005f;
            if (sp50 < 0.12f) {
                sp50 = 0.12f;
            }

            if (sp5A < 0) {
                sp5A = -sp5A;
            }

            if (sp54 < 0) {
                sp54 = -sp54;
            }

            Math_ApproxUpdateScaledS(&sp6C, sp6E, sp5A * sp50);
            Math_ApproxUpdateScaledS(&sp56, sp58, sp54 * sp50);

            sp68 = -Math_Sins(sp56) * 12.0f;
            sp5C = Math_Coss(sp56) * 12.0f;
            sp64 = Math_Sins(sp6C) * sp5C;
            sp60 = Math_Coss(sp6C);
            sp7C.x += sp64 * sp74;
            sp7C.y += sp68 * sp74;
            sp7C.z += (sp60 * sp5C) * sp74;
        }
        sp90 = 0x3E80;
    }

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_8094F2C8(this);
    if (D_809668D1 >= 0xF) {
        func_80955E64(this, globalCtx);
        return;
    }

    if ((D_809668D0 % 128) != 0) {
        func_80955658(this, globalCtx);
        return;
    }

    if ((D_809668D1 < 0xF) && (0.0f != this->actor.attachedA->speedXZ)) {
        func_80956644(this, globalCtx);
        return;
    }

    sp98 = Math_Vec3f_Yaw(&sp7C, &this->unk_1B4);
    tmp17 = sp98 - this->actor.shape.rot.y;

    if (((sp8E >= ABS(tmp17)) || (this->unk_195 != 0)) &&
        (!(D_809668D0 & 0x80) && !(player->stateFlags1 & 0x4000000))) {

        if (this->unk_195 == 0) {

            sp94 = sp98 - this->actor.shape.rot.y;

            if (ABS(sp94) >= 0x1771) {
                if (sp94 > 0) {
                    sp94 = 0x1770;
                } else {
                    sp94 = -0x1770;
                }
            }

            tmp17 = Math_SmoothScaleMaxMinS(&this->unk_1E6, sp94, 1, 0x6D6, 0);
            sp88 = ABS(tmp17);

            sp94 = sp98 - sp94;

            if (ABS(sp94) >= 0x1771) {
                if (sp94 > 0) {
                    sp94 = 0x1770;
                } else {
                    sp94 = -0x1770;
                }
            }

            tmp17 = Math_SmoothScaleMaxMinS(&this->unk_1EC, sp94, 1, 0x6D6, 0);
            sp88 += ABS(tmp17);

            tmp17 =
                Math_SmoothScaleMaxMinS(&this->unk_1F2, Math_Vec3f_Yaw(&this->unk_1CC, &sp7C) - 0x4000, 1, 0x9C4, 0);
            sp88 += ABS(tmp17);

            sp96 = this->actor.shape.rot.x + this->skelAnime.limbDrawTbl[1].z + this->skelAnime.limbDrawTbl[2].z +
                   this->skelAnime.limbDrawTbl[3].z + this->skelAnime.limbDrawTbl[4].z +
                   this->skelAnime.limbDrawTbl[5].z;

            tmp17 =
                Math_SmoothScaleMaxMinS(&this->unk_1EA, Math_Vec3f_Pitch(&sp7C, &this->unk_1C0) - sp96, 1, 0xFA0, 0);
            sp88 += ABS(tmp17);

            tmp17 = Math_SmoothScaleMaxMinS(&this->unk_1F0, -Math_Vec3f_Pitch(&this->unk_1CC, &sp7C), 1, 0xFA0, 0);
            sp88 += ABS(tmp17);

            this->skelAnime.animPlaybackSpeed = 0.0f;
            if (Math_SmoothScaleMaxMinF(&this->skelAnime.animCurrentFrame, 0.0f, 1.0f, 2.0f, 0.0f) == 0.0f) {
                if (sp88 < sp90) {
                    this->unk_19C = 0;
                    this->unk_195++;
                    this->unk_1D8 = sp7C;
                }

                if (Math_Rand_ZeroOne() < 0.1f) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
                }
            }
        }
    } else {
        if ((this->unk_195 != 0) || (this->unk_19C < 0)) {
            if (this->collider3.base.atFlags & 2) {
                if (this->unk_19C > 0) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_HIT_RINK);
                    func_8094FB6C(globalCtx);
                    this->unk_19C = -1;
                    ((BossVa*)this->actor.attachedA)->unk_194 = 6;
                }
            } else if (this->unk_19C > 0) {
                this->unk_19C = 0;
            }

            if ((this->unk_19C < 0) && (player->stateFlags1 & 0x4000000)) {
                func_8094F864(globalCtx, this, 1, 0x1E, 0.0f, 0.0f, 6, 0.0f, 1);
            }
        }

        Math_SmoothScaleMaxMinS(&this->unk_1E6, 0, 1, 0x6D6, 0);
        Math_SmoothScaleMaxMinS(&this->unk_1EC, 0, 1, 0x6D6, 0);
        Math_SmoothScaleMaxMinS(&this->unk_1EA, 0, 1, 0x6D6, 0);
        Math_SmoothScaleMaxMinS(&this->unk_1F2, this->actor.shape.rot.y - this->actor.shape.rot.x, 1, 0x6D6, 0);
        Math_SmoothScaleMaxMinS(&this->unk_1F0, this->skelAnime.limbDrawTbl[7].z, 1, 0x6D6, 0);
        Math_SmoothScaleMaxMinF(&this->skelAnime.animPlaybackSpeed, 1.0f, 1.0f, 0.05f, 0.0f);
        this->unk_195 = 0;
    }

    if ((this->unk_195 != 0) && (this->unk_195 != 2)) {
        if (this->unk_19C >= 0x20) {
            if (this->unk_19C == 0x20) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_THUNDER);
            }
            func_8094F864(globalCtx, this, 2, 0x6E, 15.0f, 15.0f, 3, 5.0f, 1);
            func_8094F864(globalCtx, this, 2, 0x6E, 15.0f, 15.0f, 3, 6.0f, 1);
            func_8094F864(globalCtx, this, 2, 0x6E, 15.0f, 15.0f, 3, 7.0f, 1);
            colCtx = &globalCtx->colChkCtx;
            collider = &this->collider3.base;
            CollisionCheck_SetAT(globalCtx, colCtx, collider);
            CollisionCheck_SetAC(globalCtx, colCtx, collider);
        } else {
            func_8094F864(globalCtx, this, 2, 0x32, 15.0f, 0.0f, 5, (this->unk_19C >> 3) + 1, 1);
            if (this->unk_19C == 0x1E) {
                func_8094FB6C(globalCtx);
            }

            if (this->unk_19C == 0x14) {
                sp44 = this->unk_1CC;
                func_8095BBD0(globalCtx, D_8095DF50, this, &sp44, &this->unk_1F6, 0x64, 0);
            }
        }

        this->unk_19C++;
        if (this->unk_19C >= 0x28) {
            this->unk_195 = 0;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80954C20.s")
#endif

void func_80955658(BossVa* this, GlobalContext* globalCtx) {
    if (Math_Rand_ZeroOne() > 0.5f) {
        SkelAnime_ChangeAnim(&this->skelAnime, &D_06018A68, 0.5f, 0.0f,
                             SkelAnime_GetFrameCount(&D_06018A68.genericHeader), 3, 4.0f);
    } else {
        SkelAnime_ChangeAnim(&this->skelAnime, &D_06018B90, 0.5f, 0.0f,
                             SkelAnime_GetFrameCount(&D_06018B90.genericHeader), 3, 4.0f);
    }

    func_8003426C(&this->actor, 0, 0xFF, 0, 0xC);
    this->unk_195 = 0;
    func_8094F2C0(this, func_8095575C);
}

void func_8095575C(BossVa* this, GlobalContext* globalCtx) {
    func_8094F2C8(this);
    Math_SmoothScaleMaxMinS(&this->unk_1E6, 0, 1, 0xFA0, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1E4, 0, 1, 0xFA0, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1EC, 0, 1, 0xFA0, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1EA, 0, 1, 0xFA0, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1F2, this->actor.shape.rot.y - this->actor.shape.rot.x, 1, 0x2EE, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1F0, this->skelAnime.limbDrawTbl[7].z, 1, 0x2EE, 0);
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        if (D_809668D1 >= 0xF) {
            func_80955E64(this, globalCtx);
        } else {
            func_80954B8C(this, globalCtx);
        }
    }
}

void func_8095586C(BossVa* this, GlobalContext* globalCtx) {
    f32 frames = SkelAnime_GetFrameCount(&D_06018D18.genericHeader);

    SkelAnime_ChangeAnim(&this->skelAnime, &D_06018D18, Math_Rand_ZeroOne() + 0.25f, Math_Rand_ZeroOne() * 3.0f, frames,
                         1, -6.0f);
    this->unk_195 = 0;
    this->unk_19C = (this->actor.params * -6) + 0x12;
    this->unk_1B0 = 0;
    func_8094F2C0(this, func_80955940);
}

void func_80955940(BossVa* this, GlobalContext* globalCtx) {
    f32 sp3C = 55.0f;
    f32 tmpf1;
    f32 tmpf2;

    func_8094F2C8(this);
    if (((globalCtx->gameplayFrames % 32) == 0) && (D_809668D2 < 0x10)) {
        this->unk_1E8 = Math_Rand_CenteredFloat(16384.0f);
        this->unk_1EE = Math_Rand_CenteredFloat(16384.0f);
        this->unk_1F4 = ((s16)Math_Rand_CenteredFloat(16384.0f) + this->actor.shape.rot.y) - this->actor.shape.rot.x;
    } else {
        Math_SmoothScaleMaxMinF(&this->skelAnime.animPlaybackSpeed, 0.0f, 1.0f, 0.025f, 0.0f);
    }

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothScaleMaxMinS(&this->unk_1E6, this->unk_1E8, 1, (s16)Math_Rand_CenteredFloat(500.0f) + 0x1F4, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1E4, 0, 1, 0x1F4, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1EC, this->unk_1EE, 1, (s16)Math_Rand_CenteredFloat(500.0f) + 0x1F4, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1EA, 0, 1, 0x1F4, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1F2, this->unk_1F4, 1, (s16)Math_Rand_CenteredFloat(500.0f) + 0x1F4, 0);

    switch (D_809668D2) {
        case 0x11:
            sp3C = -55.0f;
        case 0x10:
        case 0x12:
            if (this->unk_195 == 0) {
                if (((this->actor.params == 3) && (this->unk_19C < 0x10)) ||
                    ((this->actor.params == 4) && (this->unk_19C < 0x18)) || (this->actor.params == 5)) {

                    if (!(this->unk_19C & 1) && (this->unk_19C >= 0)) {
                        if (this->unk_19C < 8) {
                            func_8094F9E8(globalCtx, this, 1, (s16)Math_Rand_CenteredFloat(5.0f) + 0xD, 0.0f, 0.0f, 2,
                                          0.6f, 1);
                        } else {
                            func_8094F9E8(globalCtx, this, 1, (s16)Math_Rand_CenteredFloat(5.0f) + 6, 0.0f, 7.0f, 2,
                                          (this->unk_19C >> 3) + 1, 1);
                        }

                        func_8094F864(globalCtx, this, 2, 0x32, 15.0f, 0.0f, 5, (this->unk_19C >> 3) + 1, 1);
                    }

                    this->unk_19C++;
                    if (this->unk_19C >= 0x20) {
                        this->unk_195++;
                        this->unk_197 = 1;
                        func_8094FBB4(globalCtx);
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BREAK2);
                    }
                } else {
                    this->unk_195++;
                    this->unk_197 = 1;
                    this->unk_19C = 0x20;
                    D_809668D2++;
                }

                if ((this->actor.params + 0xD) == D_809668D2) {
                    D_809668E8.x = this->unk_1C0.x;
                    D_809668D8.y = D_809668E8.y = this->unk_1C0.y;
                    D_809668E8.z = this->unk_1C0.z;
                    D_809668D8.x = (Math_Coss(-(this->actor.shape.rot.y + this->unk_1B0)) * sp3C) + this->unk_1C0.x;
                    D_809668D8.z = (Math_Sins(-(this->actor.shape.rot.y + this->unk_1B0)) * sp3C) + this->unk_1C0.z;
                    this->unk_1B0 += 0x15E;
                }
            } else {
                this->unk_19C--;
                if (this->unk_19C == 0) {
                    if (this->actor.params == 5) {
                        D_809668D2++;
                    }
                    Actor_Kill(&this->actor);
                }
            }
            break;
    }
}

void func_80955E64(BossVa* this, GlobalContext* globalCtx) {
    f32 frames = SkelAnime_GetFrameCount(&D_06018D18.genericHeader);

    SkelAnime_ChangeAnim(&this->skelAnime, &D_06018D18, 1.0f, frames - 1.0f, frames, 1, -6.0f);
    this->unk_195 = 0;
    func_8094F2C0(this, func_80955EEC);
}

#ifdef NON_MATCHING
// Stack
void func_80955EEC(BossVa* this, GlobalContext* globalCtx) {
    Player* player = PLAYER; // sp74;
    s32 sp70_pad;
    s16 tmp16;
    s16 sp6C;
    s16 sp6A;
    s16 sp68;
    s32 sp64_pad;
    u32 sp60;
    Vec3f sp54 = player->actor.posRot.pos;
    Vec3f sp48;

    sp54.y += 10.0f;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_8094F2C8(this);
    if (D_809668D1 >= 0x12) {
        func_8095586C(this, globalCtx);
        return;
    }

    if ((D_809668D0 & 0x7E) != 0) {
        func_80955658(this, globalCtx);
        return;
    }

    sp54.y += 25.0;

    sp6C = Math_Vec3f_Yaw(&sp54, &this->unk_1B4);
    tmp16 = sp6C - this->actor.shape.rot.y;

    if (((ABS(tmp16) < 0x4651) || (this->unk_195 != 0)) &&
        (!(D_809668D0 & 0x80) && !(player->stateFlags1 & 0x4000000))) {
        if (this->unk_195 == 0) {

            sp68 = sp6C - this->actor.shape.rot.y;
            if (ABS(sp68) >= 0x1771) {
                if (sp68 > 0) {
                    sp68 = 0x1770;
                } else {
                    sp68 = -0x1770;
                }
            }

            tmp16 = Math_SmoothScaleMaxMinS(&this->unk_1E6, sp68, 1, 0xDAC, 0);
            sp60 = ABS(tmp16);

            sp68 = sp6C - sp68;
            if (ABS(sp68) >= 0x1771) {
                if (sp68 > 0) {
                    sp68 = 0x1770;
                } else {
                    sp68 = -0x1770;
                }
            }

            tmp16 = Math_SmoothScaleMaxMinS(&this->unk_1EC, sp68, 1, 0xDAC, 0);
            sp60 += ABS(tmp16);

            tmp16 =
                Math_SmoothScaleMaxMinS(&this->unk_1F2, Math_Vec3f_Yaw(&this->unk_1CC, &sp54) - 0x4000, 1, 0xEA6, 0);
            sp60 += ABS(tmp16);

            sp6A = this->actor.shape.rot.x + this->skelAnime.limbDrawTbl[1].x + this->skelAnime.limbDrawTbl[2].x +
                   this->skelAnime.limbDrawTbl[3].x + this->skelAnime.limbDrawTbl[4].x +
                   this->skelAnime.limbDrawTbl[5].x;

            tmp16 =
                Math_SmoothScaleMaxMinS(&this->unk_1EA, Math_Vec3f_Pitch(&sp54, &this->unk_1C0) - sp6A, 1, 0x1B58, 0);
            sp60 += ABS(tmp16);

            tmp16 = Math_SmoothScaleMaxMinS(&this->unk_1F0, -Math_Vec3f_Pitch(&this->unk_1CC, &sp54), 1, 0x1B58, 0);
            sp60 += ABS(tmp16);

            this->skelAnime.animPlaybackSpeed = 0.0f;
            if ((Math_SmoothScaleMaxMinF(&this->skelAnime.animCurrentFrame, 0.0f, 1.0f, 3.0f, 0.0f) == 0.0f) &&
                (sp60 < 0x258)) {
                this->unk_19C = 0;
                this->unk_195++;
                this->unk_1D8 = sp54;
                if (Math_Rand_ZeroOne() < 0.1f) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
                }
            }
        }
    } else {
        if ((this->unk_195 != 0) || (this->unk_19C < 0)) {
            if (this->collider3.base.atFlags & 2) {
                if (this->unk_19C > 0) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_HIT_RINK);
                    func_8094FB6C(globalCtx);
                    this->unk_19C = -1;
                    ((BossVa*)this->actor.attachedA)->unk_194 = 6;
                }
            } else if (this->unk_19C > 0) {
                this->unk_19C = 0;
            }

            if ((this->unk_19C < 0) && (player->stateFlags1 & 0x4000000)) {
                func_8094F864(globalCtx, this, 1, 0x1E, 0.0f, 0, 6, 0.0f, 1);
            }
        }

        Math_SmoothScaleMaxMinS(&this->unk_1E6, 0, 1, 0xEA6, 0);
        Math_SmoothScaleMaxMinS(&this->unk_1EC, 0, 1, 0xEA6, 0);
        Math_SmoothScaleMaxMinS(&this->unk_1EA, 0, 1, 0xEA6, 0);
        Math_SmoothScaleMaxMinS(&this->unk_1F2, this->actor.shape.rot.y - this->actor.shape.rot.x, 1, 0xEA6, 0);
        Math_SmoothScaleMaxMinS(&this->unk_1F0, this->skelAnime.limbDrawTbl[7].z, 1, 0xEA6, 0);
        Math_SmoothScaleMaxMinF(&this->skelAnime.animPlaybackSpeed, 1.0f, 1.0f, 0.05f, 0.0f);
        this->unk_195 = 0;
    }

    if ((this->unk_195 != 0) && (this->unk_195 != 2)) {
        if (this->unk_19C >= 0x10) {
            if (this->unk_19C == 0x12) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_THUNDER);
            }

            func_8094F864(globalCtx, this, 2, 0x6E, 15.0f, 15.0f, 3, 5.0f, 1);
            func_8094F864(globalCtx, this, 2, 0x6E, 15.0f, 15.0f, 3, 6.0f, 1);
            func_8094F864(globalCtx, this, 2, 0x6E, 15.0f, 15.0f, 3, 7.0f, 1);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
        } else {
            func_8094F864(globalCtx, this, 2, 0x32, 15.0f, 0.0f, 5, (this->unk_19C >> 1) + 1, 1);
            if (this->unk_19C == 0xE) {
                func_8094FB6C(globalCtx);
            }

            if (this->unk_19C == 4) {
                sp48 = this->unk_1CC;
                func_8095BBD0(globalCtx, D_8095DF50, this, &sp48, &this->unk_1F6, 0x64, 0);
            }
        }

        this->unk_19C++;
        if (this->unk_19C >= 0x18) {
            this->unk_195 = 0;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80955EEC.s")
#endif

void func_80956644(BossVa* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06018B90, 0.0f, 0.0f, SkelAnime_GetFrameCount(&D_06018B90.genericHeader),
                         3, -6.0f);
    this->unk_195 = 0;
    func_8094F2C0(this, func_809566C4);
}

void func_809566C4(BossVa* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_8094F2C8(this);
    Math_SmoothScaleMaxMinS(&this->unk_1E6, 0, 1, 0x1770, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1E4, 0, 1, 0x1770, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1EC, 0, 1, 0x1770, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1EA, 0, 1, 0x1770, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1F2, this->actor.shape.rot.y - 0x4000, 1, 0x2710, 0);
    Math_SmoothScaleMaxMinS(&this->unk_1F0, this->skelAnime.limbDrawTbl[7].z - 0x1388, 1, 0x1770, 0);
    if (((BossVa*)this->actor.attachedA)->actor.speedXZ == 0.0f) {
        func_80954B8C(this, globalCtx);
    }
}

void func_809567D0(BossVa* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000024, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06000024.genericHeader),
                         0, 0.0f);
    this->unk_1A0 = 60.0f;
    this->unk_1A4 = Math_Rand_ZeroOne() * 360.0f;
    this->unk_19C = 0x40;
    this->unk_1F0 = 0x78;
    this->unk_1A8 = 0.0f;
    this->actor.posRot.pos.x = D_8095C044[this->actor.params + 10].x + this->actor.initPosRot.pos.x;
    this->actor.posRot.pos.y = D_8095C044[this->actor.params + 10].y + this->actor.initPosRot.pos.y;
    this->actor.posRot.pos.z = D_8095C044[this->actor.params + 10].z + this->actor.initPosRot.pos.z;
    this->unk_198 = 0x2D;
    this->actor.flags &= ~1;
    func_8094F2C0(this, func_809568E0);
}

void func_809568E0(BossVa* this, GlobalContext* globalCtx) {
    Vec3f sp54 = this->actor.initPosRot.pos;
    f32 sp50 = 40.0f;
    s16 sp4E;
    s16 tmp;

    if (this->actor.initPosRot.pos.y >= 0.0f) {
        sp54.y += 25.0f;
    }

    this->unk_1A4 += Math_Rand_ZeroOne() * 0.25f;

    switch (D_809668D2) {
        case 2:
            if (this->actor.params == 6) {
                func_8002DF54(globalCtx, &this->actor, 1);
                if (Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.y, 60.0f, 0.3f, 1.0f, 0.15f) == 0.0f) {
                    this->unk_198--;
                    if (this->unk_198 == 0) {
                        D_809668D2++;
                    }
                }
            }
            this->actor.shape.rot.x = 0;
            break;

        case 3:
        case 4:
        case 5:
        case 6:
            if (this->actor.params != 6) {
                Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.y,
                                        D_8095C044[this->actor.params + 10].y + this->actor.initPosRot.pos.y, 0.3f,
                                        1.0f, 0.15f);
                this->actor.posRot.pos.x += (func_800CA720(this->unk_1A4 * 0.25f) * 0.5f);
            } else {
                Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.y, 60.0f, 0.3f, 1.0f, 0.15f);
            }
            this->actor.posRot.pos.y += func_800CA720(this->unk_1A4) * (2.0f - func_800CA720(this->unk_1A4));
            break;

        case 8:
        case 9:
            if ((this->unk_19C >= 0x10) && (this->unk_198 < 0)) {
                Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.x, sp54.x, 1.0f, 6.5f, 0.0f);
                Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.y, sp54.y, 1.0f, 6.5f, 0.0f);
                Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.z, sp54.z, 1.0f, 6.5f, 0.0f);

                sp50 = Math_Vec3f_DistXYZ(&sp54, &this->actor.posRot.pos);
                if (sp50 <= 60.0f) {
                    tmp = Math_SmoothScaleMaxMinS(&this->actor.shape.rot.x, this->actor.initPosRot.rot.x, 1, 0x7D0, 0);
                    sp4E = ABS(tmp);

                    tmp = Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.initPosRot.rot.y, 1, 0x7D0, 0);
                    sp4E += ABS(tmp);

                    if ((sp50 == 0.0f) && (sp4E == 0)) {
                        if (this->unk_197 == 0) {
                            if (this->actor.params >= 0xB) {
                                if (this->actor.params == 0xB) {
                                    D_8095C230[0]++;
                                } else {
                                    D_8095C230[this->actor.params - 6]++;
                                }
                            } else {
                                D_8095C230[this->actor.params - 5]++;
                            }
                            this->unk_198 = -0x1E;
                            this->unk_197++;
                        } else {
                            this->unk_198++;
                            if (this->unk_198 == 0) {
                                Actor_Kill(&this->actor);
                                return;
                            }
                        }
                        return;
                    }
                }
            }

        case 7:
            this->unk_198--;
            if (this->unk_198 == 0) {
                this->unk_19C = 0;
            } else {
                func_80035844(&this->actor.attachedA->posRot.pos, &this->actor.posRot.pos, &this->actor.posRot.rot.x,
                              0);
                this->unk_1A0 = Math_Vec3f_DistXYZ(&this->actor.attachedA->posRot.pos, &this->actor.posRot.pos);
                if (sp50 > 30.0f) {
                    func_8094F864(globalCtx, this, 1, 0x50, 15.0f, 0.0f, 2, 1.0f, 1);
                }
            }
            break;

        case 13:
            this->unk_198++;
            if (this->unk_198 == 0) {
                Actor_Kill(&this->actor);
                return;
            }
            return;

        case 10:
        case 11:
        case 12:
            break;
    }

    if (((globalCtx->gameplayFrames % 4) == 0) && (D_809668D2 < 9)) {
        func_8094F864(globalCtx, this, 1, 0x46, 25.0f, 20.0f, 2, 2.0f, 1);
    }

    if (Math_Rand_ZeroOne() < 0.1f) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
    }
}

void func_80956E38(BossVa* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000024, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06000024.genericHeader),
                         0, 0.0f);
    this->unk_19C = 0x80;
    this->unk_1F0 = 0x78;
    this->unk_1A0 = 60.0f;
    this->unk_1A8 = 0.0f;
    this->actor.flags &= ~1;
    func_8094F2C0(this, func_80956EE0);
}

void func_80956EE0(BossVa* this, GlobalContext* globalCtx) {
    Player* player = PLAYER; // sp64
    EnBoom* australianFrisbee;
    Vec3f sp54 = ((BossVa*)this->actor.attachedA)->unk_1D8;
    s16 sp52;
    f32 tmpf1;

    this->unk_1A4 += Math_Rand_ZeroOne() * 0.5f;
    sp52 = this->unk_19C & 0x1FF;

    if ((globalCtx->gameplayFrames % 128) == 0) {
        this->unk_1F6.x = (s16)(Math_Rand_ZeroOne() * 100.0f) + 0x64;
    }

    Math_SmoothScaleMaxMinS(&this->unk_1F6.z, this->unk_1F6.x, 1, 0x1E, 0);
    this->unk_1F6.y += this->unk_1F6.z;
    if ((this->collider3.base.atFlags & 2) || (this->collider2.base.atFlags & 2)) {
        if ((this->collider3.base.at == &player->actor) || (this->collider2.base.at == &player->actor)) {
            func_8002F71C(globalCtx, &this->actor, 8.0f, this->actor.attachedA->yawTowardsLink, 8.0f);
            Audio_PlayActorSound2(&player->actor, NA_SE_PL_BODY_HIT);
            this->collider2.base.at = NULL;
            this->collider3.base.at = NULL;
        }

        this->collider3.base.atFlags &= ~2;
        this->collider2.base.atFlags &= ~2;
    }

    if (this->collider2.base.acFlags & 2) {
        this->collider2.base.acFlags &= ~2;
        if ((this->collider2.base.ac->id == ACTOR_EN_BOOM) && (sp52 >= 0x80)) {
            australianFrisbee = (EnBoom*)this->collider2.base.ac;
            australianFrisbee->returnTimer = 0;
            australianFrisbee->moveTo = &player->actor;
            australianFrisbee->actor.posRot.rot.y = australianFrisbee->actor.yawTowardsLink;
            Audio_PlayActorSound2(&this->actor, NA_SE_IT_SHIELD_REFLECT_SW);
        }
    }

    this->actor.posRot.pos.x = (Math_Sins(this->actor.posRot.rot.y) * this->unk_1A0) + sp54.x;
    this->actor.posRot.pos.z = (Math_Coss(this->actor.posRot.rot.y) * this->unk_1A0) + sp54.z;
    Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.y, 4.0f, 1.0f, 2.0f, 0.0f);
    tmpf1 = func_800CA720(this->unk_1A4);
    this->actor.posRot.pos.y += tmpf1 + tmpf1;
    this->actor.posRot.rot.x = Math_Vec3f_Pitch(&sp54, &this->actor.posRot.pos);
    Math_SmoothScaleMaxMinF(&this->unk_1A0, 160.0f, 1.0f, 2.0f, 0.0f);
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.x, 0, 1, 0x5DC, 0);
    if (!(this->unk_19C & 0x200)) {
        this->unk_1AC = 0xBB8;
    } else {
        this->unk_1AC = -0xBB8;
    }

    if (sp52 >= 0x80) {
        func_8094F864(globalCtx, this, 1, 0x4B, 15.0f, 7.0f, 1, 1.0f, 1);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        D_80966936 = 0;
    } else {
        D_80966936 = 1;
    }

    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    if ((globalCtx->gameplayFrames % 4) == 0) {
        Math_SmoothScaleMaxMinS(&this->unk_1F0, 0x78, 1, 0xA, 0);
    }

    if (Math_Rand_ZeroOne() < 0.1f) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
    }

    this->actor.posRot.rot.y += this->unk_1AC;
    if ((D_809668D0 % 128) != 0) {
        func_80957998(this, globalCtx);
    }
}

void func_809572DC(BossVa* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06000024, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06000024.genericHeader),
                         0, 0.0f);
    this->unk_19C = 0x40;
    this->unk_1F0 = 0x78;
    this->unk_1A0 = 60.0f;
    this->unk_1A8 = 0.0f;
    this->actor.flags &= ~1;
    func_8094F2C0(this, func_80957384);
}

void func_80957384(BossVa* this, GlobalContext* globalCtx) {
    Player* player = PLAYER; // sp64
    EnBoom* refThrowingStick;
    Vec3f sp54 = ((BossVa*)this->actor.attachedA)->unk_1D8;
    s16 sp52;
    s16 sp50;
    f32 sp4C;

    f32 tmpf1;

    this->unk_1A4 += Math_Rand_ZeroOne() * 0.5f;
    sp52 = this->unk_19C & 0x1FF;
    if ((globalCtx->gameplayFrames % 128) == 0) {
        this->unk_1F6.x = (s16)(Math_Rand_ZeroOne() * 100.0f) + 0x64;
    }

    sp50 = (D_809668D1 * 0x46) - 0x118;
    Math_SmoothScaleMaxMinS(&this->unk_1F6.z, this->unk_1F6.x, 1, 0x1E, 0);
    this->unk_1F6.y += this->unk_1F6.z;
    if (D_8095C22C != 0) {
        D_8095C22C--;
        func_8094FC70(this, globalCtx);
        return;
    }

    if ((this->collider3.base.atFlags & 2) || (this->collider2.base.atFlags & 2)) {
        if ((this->collider3.base.at == &player->actor) || (this->collider2.base.at == &player->actor)) {
            func_8002F71C(globalCtx, &this->actor, 8.0f, this->actor.attachedA->yawTowardsLink, 8.0f);
            Audio_PlayActorSound2(&player->actor, NA_SE_PL_BODY_HIT);
            this->collider2.base.at = NULL;
            this->collider3.base.at = NULL;
        }

        this->collider3.base.atFlags &= ~2;
        this->collider2.base.atFlags &= ~2;
    }

    Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.y, 4.0f, 1.0f, 2.0f, 0.0f);
    this->actor.posRot.rot.x = Math_Vec3f_Pitch(&sp54, &this->actor.posRot.pos);
    if ((globalCtx->gameplayFrames % 8) == 0) {
        Math_SmoothScaleMaxMinS(&this->unk_1F0, 0x28, 1, 0xA, 0);
        func_8094F864(globalCtx, this, 1, this->unk_1F0, 25.0f, 20.0f, 2, 2.0f, 1);
    }

    if (!(D_8096693E & 0x100) && (this->actor.attachedA->dmgEffectTimer == 0)) {
        sp4C = 200.0f;
        func_8094F864(globalCtx, this, 1, 0x7D, 15.0f, 7.0f, 1, 1.0f, 1);
        this->actor.flags &= ~1;
        if (this->actor.params & 1) {
            sp4C = -200.0f;
        }

        Math_SmoothScaleMaxMinF(&this->unk_1A0, (Math_Sins(D_8096693E * 400) * sp4C) + 320.0f, 1.0f, 10.0f, 0.0f);
        Math_SmoothScaleMaxMinS(&this->unk_1AC, sp50 + 0x1F4, 1, 0x3C, 0);
        tmpf1 = func_800CA720(this->unk_1A4);
        this->actor.posRot.pos.y += (tmpf1 + tmpf1);
        if (this->collider2.base.acFlags & 2) {
            this->collider2.base.acFlags &= ~2;

            if ((this->collider2.base.ac->id == ACTOR_EN_BOOM) && (sp52 >= 0x40)) {
                refThrowingStick = (EnBoom*)this->collider2.base.ac;
                refThrowingStick->returnTimer = 0;
                refThrowingStick->moveTo = &player->actor;
                refThrowingStick->actor.posRot.rot.y = refThrowingStick->actor.yawTowardsLink;
                Audio_PlayActorSound2(&this->actor, NA_SE_IT_SHIELD_REFLECT_SW);
            }
        }

        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    } else {
        this->actor.flags |= 1;
        Math_SmoothScaleMaxMinS(&this->unk_1AC, sp50 + 0x96, 1, 0x3C, 0);
        if (this->actor.attachedA->dmgEffectTimer == 0) {
            Math_SmoothScaleMaxMinF(&this->unk_1A0, 180.0f, 1.0f, 1.5f, 0.0f);
        } else {
            this->unk_1AC = 0;
            if (this->actor.dmgEffectTimer == 0) {
                func_8003426C(&this->actor, 0, 0xFF, 0x2000, this->actor.attachedA->dmgEffectTimer);
            }
        }

        this->actor.posRot.pos.y += func_800CA720(this->unk_1A4) * 4.0f;
        if (this->collider2.base.acFlags & 2) {
            func_8094FC70(this, globalCtx);
        }
    }

    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.x, 0, 1, 0x5DC, 0);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    if ((globalCtx->gameplayFrames % 4) == 0) {
        Math_SmoothScaleMaxMinS(&this->unk_1F0, 0x78, 1, 0xA, 0);
    }

    if (Math_Rand_ZeroOne() < 0.1f) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_SPARK - SFX_FLAG);
    }

    if (this->actor.attachedA->dmgEffectTimer == 0) {
        if (!(this->unk_19C & 0x400)) {
            this->actor.posRot.rot.y += this->unk_1AC;
        } else {
            this->actor.posRot.rot.y -= this->unk_1AC;
        }

        this->actor.posRot.pos.x = (Math_Sins(this->actor.posRot.rot.y) * this->unk_1A0) + sp54.x;
        this->actor.posRot.pos.z = (Math_Coss(this->actor.posRot.rot.y) * this->unk_1A0) + sp54.z;
    }
}

void func_80957998(BossVa* this, GlobalContext* globalCtx) {
    this->actor.flags |= 1;
    this->unk_198 = ((BossVa*)this->actor.attachedA)->unk_198;
    func_8003426C(&this->actor, 0, 0xFF, 0x2000, this->unk_198);
    func_8094F2C0(this, func_809579F4);
}

void func_809579F4(BossVa* this, GlobalContext* globalCtx) {
    s32 sp44_pad;
    Vec3f sp40 = ((BossVa*)this->actor.attachedA)->unk_1D8;

    this->actor.posRot.rot.x =
        Math_Vec3f_Pitch(&((BossVa*)this->actor.attachedA)->actor.posRot.pos, &this->actor.posRot.pos);
    if (this->collider2.base.acFlags & 2) {
        func_8094FC70(this, globalCtx);
        return;
    }

    this->unk_1A4 += (Math_Rand_ZeroOne() * 0.5f);
    Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.y, 4.0f, 1.0f, 2.0f, 0.0f);
    this->actor.posRot.pos.y += func_800CA720(this->unk_1A4) * 3.0f;
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    if ((globalCtx->gameplayFrames % 4) == 0) {
        Math_SmoothScaleMaxMinS(&this->unk_1F0, 0x28, 1, 0xA, 0);
        func_8094F864(globalCtx, this, 1, this->unk_1F0, 25.0f, 20.0f, 2, 2.0f, 1);
    }

    this->unk_198--;
    this->actor.posRot.rot.x = Math_Vec3f_Pitch(&sp40, &this->actor.posRot.pos);
    if (this->unk_198 <= 0) {
        if (this->unk_198 == 0) {
            this->unk_19C = 0;
        } else {
            func_8094F864(globalCtx, this, 1, 0x55, 15.0f, 0.0f, 1, 1.0f, 1);
            if (this->unk_19C >= 0x10) {
                this->actor.flags &= ~1;
                this->unk_19C = 0x80;
                func_8094F2C0(this, func_80956EE0);
            }
        }
    }
}

void func_80957C10(BossVa* this) {
    this->actor.flags &= ~1;
    this->unk_198 = 0x1E;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BALINADE_BL_DEAD);
    this->unk_197++;
    func_8094F2C0(this, func_80957C68);
}

void func_80957C68(BossVa* this, GlobalContext* globalCtx) {
    this->unk_198--;
    if (this->unk_198 == 0) {
        Actor_Kill(&this->actor);
    }
}

void func_80957C9C(BossVa* this, GlobalContext* globalCtx) {
    if (D_809668D2 > 0) {
        D_80966934 = 100;
    }
    this->actor.flags &= ~1;
    func_8094F2C0(this, func_80957CEC);
}

void func_80957CEC(BossVa* this, GlobalContext* globalCtx) {
    if (D_80966934 == 0x1D) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_BUYODOOR_CLOSE);
    }

    if (D_809668D2 < 0) {
        if (D_80966934 < 100) {
            D_80966934 += 8;
        } else {
            D_80966934 = 100;
        }
    }
}

void BossVa_Update(Actor* thisx, GlobalContext* globalCtx) {
    BossVa* this = THIS;
    EnBoom* refActor;
    GlobalContext* globalCtx2 = globalCtx;
    s32 i;

    this->actionFunc(this, globalCtx);

    switch (this->actor.params) {
        case -1:
            if (((BossVa*)thisx)->collider1.base.acFlags & 2) {
                this->collider1.base.acFlags &= ~2;

                refActor = (EnBoom*)this->collider1.base.ac;
                if (refActor->actor.id == ACTOR_EN_BOOM) {
                    refActor->returnTimer = 0;
                }
            }

            func_809597F4(globalCtx);

            for (i = 2; i >= 0; i--) {
                if ((globalCtx2->envCtx.unk_8C[i] - 1) > 0) {
                    globalCtx2->envCtx.unk_8C[i] -= 1;
                } else {
                    globalCtx2->envCtx.unk_8C[i] = 0;
                }

                if ((globalCtx2->envCtx.unk_8C[i + 3] - 10) > 0) {
                    globalCtx2->envCtx.unk_8C[i + 3] -= 10;
                } else {
                    globalCtx2->envCtx.unk_8C[i + 3] = 0;
                }

                if ((globalCtx2->envCtx.unk_8C[i + 6] - 10) > 0) {
                    globalCtx2->envCtx.unk_8C[i + 6] -= 10;
                } else {
                    globalCtx2->envCtx.unk_8C[i + 6] = 0;
                }
            }

            if (this->unk_194 > 0) {
                this->unk_194--;
            }
            break;

        default:
            this->unk_19C++;
            this->actor.posRot2.pos = this->actor.posRot.pos;
            this->actor.posRot2.pos.y += 45.0f;
            this->unk_1D8.y = (Math_Coss(this->unk_19C * 4004) * 0.24f) + 0.76f;
            this->unk_1D8.x = (Math_Sins(this->unk_19C * 4004) * 0.2f) + 1.0f;
            break;

        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 19:
            break;
    }
}

#ifdef NON_MATCHING
// 2Tex
s32 func_80957F60(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    BossVa* this = THIS;
    s32 pad;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x103C);

        if (limbIndex == 0x14) {
            gDPPipeSync(gfxCtx->polyOpa.p++);
            gSPSegment(gfxCtx->polyOpa.p++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 8, 0x10, 1, 0,
                                        (-globalCtx->gameplayFrames * 2) % 64, 0x10, 0x10));
            gDPSetEnvColor(gfxCtx->polyOpa.p++, 0x00, 0x00, 0x00, this->unk_1AE);
            Matrix_RotateX(-1.5707964f, MTXMODE_APPLY);
        } else if ((limbIndex >= 0xA) && (limbIndex < 0x14)) {
            rot->x -= 0x4000;
            *dList = NULL;
        } else if (limbIndex == 6) {
            Matrix_Scale(this->unk_1A4, this->unk_1A4, this->unk_1A4, MTXMODE_APPLY);
        } else if (limbIndex == 0x3D) {
            Matrix_Scale(this->unk_1A0, this->unk_1A0, this->unk_1A0, MTXMODE_APPLY);
        } else if (limbIndex == 7) {
            rot->x -= 0xCCC;
        }

        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1057);
    }
    return 0;
}
#else
s32 func_80957F60(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_80957F60.s")
#endif

void func_80958150(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    BossVa* this = THIS;
    Vec3f sp78 = D_8095C258;
    s32 pad;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1060);
        if (limbIndex == 6) {
            if (D_809668D1 < 9) {
                sp78.x = -1000.0f;
            } else {
                sp78.x = 200.0f;
            }
            Matrix_MultVec3f(&sp78, &this->unk_1D8);
        } else if ((limbIndex >= 0xA) && (limbIndex < 0x14) && (D_8095C226[limbIndex] != 0)) {
            if (((limbIndex >= 0x10) || (limbIndex == 0xA)) && (D_809668D1 < 0xA)) {
                gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1070),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gfxCtx->polyXlu.p++, &D_06008BB8);
            } else if ((limbIndex >= 0xB) && (D_809668D1 < 4)) {
                gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1074),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gfxCtx->polyXlu.p++, &D_06008BB8);
            }

            if (D_809668D2 >= 0xE) {
                sp78.x = Math_Rand_CenteredFloat(530.0f);
                sp78.y = Math_Rand_CenteredFloat(530.0f);
                sp78.z = -60.0f;
            }
            Matrix_MultVec3f(&sp78, &this->unk_1FC[limbIndex - 10]);
        } else if (limbIndex == 0x19) {
            gSPSegment(gfxCtx->polyXlu.p++, 0x09,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0U, (globalCtx->gameplayFrames * 10) % 128, 0x10,
                                        0x20, 1, 0, (globalCtx->gameplayFrames * 5) % 128, 0x10, 0x20));
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1088),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, &D_06008D70);
        } else if ((*dList != NULL) && (limbIndex >= 0x1D) && (limbIndex < 0x38)) {
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x108C),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, *dList);
        } else if ((limbIndex == 0x18) && (D_809668D2 < 0xE)) {
            sp78.x = (thisx->shape.unk_08 + 450.0f) + -140.0f;
            Matrix_MultVec3f(&sp78, &this->unk_280);
            sp78.x = 200.0f;
            Matrix_MultVec3f(&sp78, &this->unk_274);
        }

        if ((limbIndex == 7) && (D_809668D2 >= 0xE)) {
            sp78.x = Math_Rand_CenteredFloat(320.0f) + -250.0f;
            sp78.y = Math_Rand_CenteredFloat(320.0f);
            sp78.z = Math_Rand_CenteredFloat(320.0f);

            if (sp78.y < 0.0f) {
                sp78.y -= 150.0f;
            } else {
                sp78.y += 150.0f;
            }

            if (sp78.z < 0.0f) {
                sp78.z -= 150.0f;
            } else {
                sp78.z += 150.0f;
            }
            Matrix_MultVec3f(&sp78, &this->unk_274);
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x10A8);
    }
}

s32 func_809586A4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    BossVa* this = THIS;

    if ((this->unk_194 == 0) && (limbIndex == 4)) {
        rot->z += this->unk_1F6.x;
    }
    return 0;
}

void func_809586E4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    BossVa* this = THIS;
    Vec3f sp20 = D_8095C264;
    s32 pad;

    if (this->unk_194 != 0) {
        switch (limbIndex) {
            case 4:
                Matrix_MultVec3f(&D_8095C220, &this->actor.posRot2.pos);
                func_800628A4(0, &this->collider2);
                break;
            case 7:
                Matrix_MultVec3f(&D_8095C220, &this->unk_1B4);
                sp20.x = ((this->unk_198 & 0x1F) >> 1) * -40.0f;
                sp20.y = ((this->unk_198 & 0x1F) >> 1) * -7.0f;
                Matrix_MultVec3f(&sp20, &this->unk_1FC[0]);
                break;
            case 9:
                sp20.x = ((this->unk_198 & 0x1F) >> 1) * -60.0f;
                sp20.y = ((this->unk_198 & 0x1F) >> 1) * -45.0f;
                Matrix_MultVec3f(&sp20, &this->unk_1FC[1]);
                break;
        }
    } else {
        switch (limbIndex) {
            case 5:
                Matrix_MultVec3f(&D_8095C220, &this->unk_1B4);
                break;
            case 8:
                sp20.x = (this->unk_19C & 7) * 90.0f;
                Matrix_MultVec3f(&sp20, &this->unk_1FC[2]);
                break;
            case 9:
                sp20.x = (this->unk_19C & 7) * 50.0f;
                Matrix_MultVec3f(&sp20, &this->unk_1FC[1]);
                break;
            case 10:
                sp20.x = (this->unk_19C & 7) * 46.0f;
                Matrix_MultVec3f(&sp20, &this->unk_1FC[0]);
                break;
        }
    }
}

s32 func_80958934(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    BossVa* this = THIS;
    MtxF sp2C;
    s32 pad;

    switch (limbIndex) {
        case 4:
            rot->y += this->unk_1E6;
            rot->z += this->unk_1E4;
            break;

        case 5:
            rot->y += this->unk_1EC;
            rot->z += this->unk_1EA;
            break;

        case 7:
            Matrix_Translate(pos->x, pos->y, pos->z, 1);
            Matrix_Get(&sp2C);
            func_800D2264(&sp2C, &D_80966938, 0);
            Matrix_RotateX(-D_80966938.x * 0.0000958738f, 1);
            Matrix_RotateY(-D_80966938.y * 0.0000958738f, 1);
            Matrix_RotateZ(-D_80966938.z * 0.0000958738f, 1);
            Matrix_RotateY(this->unk_1F2 * 0.0000958738f, 1);
            Matrix_RotateZ(this->unk_1F0 * 0.0000958738f, 1);
            pos->z = 0.0f;
            pos->y = 0.0f;
            pos->x = 0.0f;
            rot->z = 0;
            rot->y = rot->z;
            rot->x = rot->z;
            break;
    }
    return 0;
}

void func_80958B0C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    BossVa* this = THIS;
    Vec3f sp70 = D_8095C270;
    Vec3f sp64 = D_8095C27C;
    Vec3f sp58 = D_8095C288;
    Vec3f sp4C = D_8095C294;
    Vec3f sp40 = D_8095C2A0;
    s16 sp3E;
    s16 sp3C;

    switch (limbIndex) {
        case 3:
            sp70.x = (this->unk_19C & 7) * 30.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[0]);
            break;

        case 4:
            Matrix_MultVec3f(&D_8095C220, &this->unk_1B4);
            sp70.x = (this->unk_19C & 7) * 30.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[1]);
            break;

        case 5:
            Matrix_MultVec3f(&D_8095C220, &this->unk_1C0);
            sp70.x = (this->unk_19C & 7) * 46.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[2]);
            break;

        case 7:
            Matrix_MultVec3f(&D_8095C220, &this->unk_1CC);
            sp70.x = (this->unk_19C & 7) * 46.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[3]);
            sp70.x = 20.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[9]);
            func_80035844(&this->unk_1FC[9], &this->unk_1D8, &this->unk_1F6.x, 0);
            sp3E = this->unk_1F6.x;
            sp3C = this->unk_1F6.y;
            Matrix_Push();
            Matrix_Translate(this->unk_1FC[9].x, this->unk_1FC[9].y, this->unk_1FC[9].z, 0);
            Matrix_RotateRPY(sp3E, sp3C, 0, 1);
            sp70.x = 0.0f;
            if (D_809668D1 >= 0xF) {
                sp70.z = ((this->unk_19C - 0x10) & 7) * 120.0f;
            } else {
                sp70.z = ((this->unk_19C - 0x20) & 0xF) * 80.0f;
            }
            sp70.z += 40.0f;
            sp40.z = sp70.z;
            sp4C.z = sp70.z;
            sp70.z += 50.0f;
            Matrix_MultVec3f(&sp70, &this->unk_1FC[4]);
            if (D_809668D1 >= 0xF) {
                sp70.z -= 33.0f;
                if (sp70.z < 0.0f) {
                    sp70.z = 0.0f;
                }
                Matrix_MultVec3f(&sp70, &this->unk_1FC[6]);
                sp70.z -= 33.0f;
                if (sp70.z < 0.0f) {
                    sp70.z = 0.0f;
                }
            } else {
                sp70.z -= 22.0f;
                if (sp70.z < 0.0f) {
                    sp70.z = 0.0f;
                }
                Matrix_MultVec3f(&sp70, &this->unk_1FC[6]);
                sp70.z -= 22.0f;
                if (sp70.z < 0.0f) {
                    sp70.z = 0.0f;
                }
            }
            Matrix_MultVec3f(&sp70, &this->unk_1FC[5]);
            Matrix_MultVec3f(&sp64, &this->collider3.dim.quad[1]);
            Matrix_MultVec3f(&sp58, &this->collider3.dim.quad[0]);
            Matrix_MultVec3f(&sp4C, &this->collider3.dim.quad[3]);
            Matrix_MultVec3f(&sp40, &this->collider3.dim.quad[2]);
            func_80062734(&this->collider3, &this->collider3.dim.quad[0], &this->collider3.dim.quad[1],
                          &this->collider3.dim.quad[2], &this->collider3.dim.quad[3]);
            Matrix_Pull();
            break;
    }
}

s32 func_80958F6C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    BossVa* this = THIS;

    switch (limbIndex) {
        case 2:
            *dList = NULL;
            break;
        case 3:
            Matrix_Scale(this->unk_1D8.x, 1.0f, this->unk_1D8.x, 1);
            break;
        case 4:
            Matrix_Scale(1.0f, this->unk_1D8.y, 1.0f, 1);
            break;
    }
    return 0;
}

void func_80958FFC(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    BossVa* this = THIS;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x118E);
        if (limbIndex == 2) {
            gSPSegment(gfxCtx->polyXlu.p++, 0x0A,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, (globalCtx->gameplayFrames * 10) % 32, 0x10,
                                        0x20, 1, 0, (-globalCtx->gameplayFrames * 5) % 32, 0x10, 0x20));
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x119C),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06000FA0);
        } else if ((limbIndex == 3) || (limbIndex == 4)) {
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x11A0),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, *dList);
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x11A5);
    }
}

#ifdef NON_MATCHING
// 2Tex, regalloc, wrong jump location for case 0
void BossVa_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BossVa* this = THIS;
    s32 pad;
    Vec3f spBC;
    Vec3f spB0 = D_8095C2AC;
    Vec3f spA4 = D_8095C2B8;
    Vec3f sp98 = D_8095C2C4;
    Vec3f sp8C = D_8095C2D0;
    Vec3f sp80 = D_8095C2DC;
    Vec3f sp74 = D_8095C2E8;
    Color_RGBA8 sp70 = D_8095C2F4;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x11BE);
        func_80093D18(globalCtx->state.gfxCtx);
        func_80093D84(globalCtx->state.gfxCtx);

        switch (this->actor.params) {
            case -1:
                if (globalCtx->envCtx.unk_9E != 0) {
                    globalCtx->envCtx.unk_9E += 0x15E;
                    if (globalCtx->envCtx.unk_9E > 0) {
                        globalCtx->envCtx.unk_9E = 0;
                    }
                }

                if (globalCtx->envCtx.unk_A0 != 0) {
                    globalCtx->envCtx.unk_A0 += 0x15E;
                    if (globalCtx->envCtx.unk_A0 > 0) {
                        globalCtx->envCtx.unk_A0 = 0;
                    }
                }

                if (this->unk_197 == 0) {
                    gSPSegment(gfxCtx->polyOpa.p++, 0x08,
                               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 8, 0x10, 1, 0,
                                                (-globalCtx->gameplayFrames * 10) % 16, 0x10, 0x10));
                    gSPSegment(gfxCtx->polyOpa.p++, 0x09,
                               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0,
                                                ((-globalCtx->gameplayFrames * 1) * 10) % 32, 0x10, 0x20, 1, 0,
                                                ((-globalCtx->gameplayFrames * 1) * 5) % 32, 0x10, 0x20));
                    SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, func_80957F60,
                                   func_80958150, &this->actor);
                }
                break;

            case 0:
            case 1:
            case 2:
                if (this->unk_197 == 0) {
                    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                     this->skelAnime.dListCount, func_809586A4, func_809586E4, &this->actor);
                }
                break;

            case 3:
            case 4:
            case 5:
                if (this->unk_197 == 0) {
                    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                     this->skelAnime.dListCount, func_80958934, func_80958B0C, &this->actor);
                }
                break;

            case 16:
            case 17:
            case 18:
                SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                 this->skelAnime.dListCount, NULL, NULL, NULL);
                break;

            default:
                if (this->unk_197 == 0) {
                    SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, func_80958F6C,
                                   func_80958FFC, &this->actor);
                    func_800628A4(0, &this->collider2);
                    if (D_809668D2 < 0xD) {
                        spBC = this->actor.attachedA->posRot.pos;
                    } else {
                        spBC = ((BossVa*)this->actor.attachedA)->unk_1D8;
                    }
                    Matrix_MultVec3f(&D_8095C220, &this->unk_1FC[1]);
                    Matrix_Push();
                    Matrix_Translate(spBC.x, spBC.y, spBC.z, 0);
                    Matrix_RotateRPY(this->actor.posRot.rot.x, this->actor.posRot.rot.y, 0, 1);
                    sp80.z = sp74.z = this->unk_1A0;
                    spB0.z = (this->unk_19C & 0xF) * (this->unk_1A0 * 0.0625f);
                    Matrix_MultVec3f(&spB0, &this->unk_1FC[0]);
                    Matrix_MultVec3f(&sp98, &this->collider3.dim.quad[1]);
                    Matrix_MultVec3f(&sp8C, &this->collider3.dim.quad[0]);
                    Matrix_MultVec3f(&sp80, &this->collider3.dim.quad[3]);
                    Matrix_MultVec3f(&sp74, &this->collider3.dim.quad[2]);
                    func_80062734(&this->collider3, &this->collider3.dim.quad[0], &this->collider3.dim.quad[1],
                                  &this->collider3.dim.quad[2], &this->collider3.dim.quad[3]);
                    Matrix_Pull();
                    spBC = this->actor.posRot.pos;
                    spBC.y += 9.0f;
                    if (this->actor.dmgEffectTimer != 0) {
                        func_80026A6C(globalCtx);
                    }
                    func_80033C30(&spBC, &spA4, 0xFF, globalCtx);
                    if (this->actor.dmgEffectTimer != 0) {
                        Color_RGBA8 sp50 = D_8095C2F8;
                        func_80026860(globalCtx, &sp50, this->actor.dmgEffectTimer, this->actor.dmgEffectParams & 0xFF);
                    }
                }
                break;

            case 19:
                break;
        }

        if (this->actor.params == -1) {
            func_8095A188(D_8095DF50, globalCtx);
        } else if (this->actor.params == 0x13) {
            func_8095BD24(globalCtx, D_80966934);
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x1241);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/BossVa_Draw.s")
#endif

#ifdef NON_MATCHING
// Regalloc, wrong data accesses/types
void func_809597F4(GlobalContext* globalCtx) {
    Player* player = PLAYER; // spB8
    s16 spB6;
    s16 i;
    BossVaEffect* ptr = D_8095DF50;
    f32 tmpf1;
    s16 tmp16;
    s16 spAA;
    BossVa* refActor; // spA4
    s32 pad;
    Vec3f sp94;
    CollisionPoly* sp90;
    s32 pad2;
    Vec3f sp80;
    CollisionPoly* sp7C;

    Vec3f sp64;

    for (i = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 != 0) {
            ptr->unk_00.x += ptr->unk_0C.x;
            ptr->unk_00.y += ptr->unk_0C.y;
            ptr->unk_00.z += ptr->unk_0C.z;
            ptr->unk_26--;
            ptr->unk_0C.x += ptr->unk_18.x;
            ptr->unk_0C.y += ptr->unk_18.y;
            ptr->unk_0C.z += ptr->unk_18.z;
            if ((ptr->unk_24 == 1) || (ptr->unk_24 == 3)) {
                refActor = ptr->unk_54;

                ptr->unk_2E += (s16)(Math_Rand_ZeroOne() * 20000.0f) + 0x2000;
                ptr->unk_2C += (s16)(Math_Rand_ZeroOne() * 10000.0f) + 0x2000;

                if ((ptr->unk_28 == 1) || (ptr->unk_28 == 4)) {
                    spAA = ptr->unk_2A - Math_Vec3f_Pitch(&refActor->actor.posRot.pos,
                                                          &((BossVa*)refActor->actor.attachedA)->unk_1D8);
                    ptr->unk_00.x =
                        refActor->actor.posRot.pos.x - (Math_Sins(refActor->actor.posRot.rot.y) * ptr->unk_44[1]);
                    ptr->unk_00.z =
                        refActor->actor.posRot.pos.z - (Math_Coss(refActor->actor.posRot.rot.y) * ptr->unk_44[1]);
                    ptr->unk_00.y = (Math_Coss(-spAA) * ptr->unk_44[2]) + refActor->actor.posRot.pos.y;
                } else if ((ptr->unk_28 == 2) || (ptr->unk_28 == 5)) {
                    ptr->unk_00.x = ptr->unk_44[1] + refActor->actor.posRot.pos.x;
                    ptr->unk_00.y = ptr->unk_44[2] + refActor->actor.posRot.pos.y;
                    ptr->unk_00.z = ptr->unk_44[3] + refActor->actor.posRot.pos.z;
                } else {
                    spB6 = Math_Rand_ZeroFloat(17.9f);
                    ptr->unk_00.x = Math_Rand_CenteredFloat(10.0f) + player->unk_908[spB6].x;
                    ptr->unk_00.y = Math_Rand_CenteredFloat(15.0f) + player->unk_908[spB6].y;
                    ptr->unk_00.z = Math_Rand_CenteredFloat(10.0f) + player->unk_908[spB6].z;
                }

                if (ptr->unk_26 < 100) {
                    ptr->unk_30[3] -= 50;
                    if (ptr->unk_30[3] < 0) {
                        ptr->unk_30[3] = 0;
                        ptr->unk_26 = 0;
                        ptr->unk_24 = 0;
                    }
                }
            }

            if (ptr->unk_24 == 2) {
                ptr->unk_2E += (s16)(Math_Rand_ZeroOne() * 20000.0f) + 0x4000;
                if (ptr->unk_26 < 100) {
                    ptr->unk_30[3] -= 50;
                    if (ptr->unk_30[3] < 0) {
                        ptr->unk_30[3] = 0;
                        ptr->unk_26 = 0;
                        ptr->unk_24 = 0;
                    }
                }
            }

            if (ptr->unk_24 == 4) {
                refActor = ptr->unk_54;

                ptr->unk_2E += (s16)(Math_Rand_ZeroOne() * 10000.0f) + 0x24A8;
                ptr->unk_00.x = ptr->unk_44[1] + refActor->actor.posRot.pos.x;
                ptr->unk_00.y =
                    (refActor->actor.posRot.pos.y + 310.0f) + (refActor->actor.shape.unk_08 * refActor->actor.scale.y);
                ptr->unk_00.z = ptr->unk_44[3] + refActor->actor.posRot.pos.z;
                ptr->unk_28 = (ptr->unk_28 + 1) & 7;

                if (ptr->unk_26 < 100) {
                    ptr->unk_30[3] -= 50;
                    if (ptr->unk_30[3] < 0) {
                        ptr->unk_30[3] = 0;
                        ptr->unk_26 = 0;
                        ptr->unk_24 = 0;
                    }
                }
            }

            if (ptr->unk_24 == 5) {
                ptr->unk_30[3] -= 20;
                ptr->unk_28 = (ptr->unk_28 + 1) & 7;
                if (ptr->unk_30[3] <= 0) {
                    ptr->unk_30[3] = 0;
                    ptr->unk_26 = 0;
                    ptr->unk_24 = 0;
                }
            }

            if (ptr->unk_24 == 6) {
                if (ptr->unk_28 < 2) {
                    sp94 = ptr->unk_00;
                    sp94.y = sp94.y - (ptr->unk_0C.y + 4.0f);
                    tmpf1 = func_8003C890(&globalCtx->colCtx, &sp90, &sp94);
                    if (sp90 != NULL) {
                        if (ptr->unk_00.y <= tmpf1) {
                            ptr->unk_28 = 2;
                            ptr->unk_00.y = tmpf1 + 1.0f;
                            if (D_809668D2 < 20) {
                                ptr->unk_26 = 0x50;
                            } else {
                                ptr->unk_26 = 0xEA60;
                            }

                            sp64 = D_8095C220;
                            ptr->unk_0C = sp64;
                            ptr->unk_18 = sp64;
                        }
                    }

                    if (ptr->unk_26 == 0) {
                        ptr->unk_24 = 0;
                    }

                } else if (ptr->unk_26 < 0x14) {
                    ptr->unk_30[3] = ptr->unk_26 * 10;
                    ptr->unk_38[3] = ptr->unk_26 * 5;
                } else if (ptr->unk_26 >= 0xC351) {
                    ptr->unk_26++;
                }

                if (ptr->unk_26 == 0) {
                    ptr->unk_24 = 0;
                }
            }

            if (ptr->unk_24 == 8) {
                if (ptr->unk_28 == 0) {
                    sp80 = ptr->unk_00;
                    sp80.y = sp80.y - (ptr->unk_0C.y + 4.0f);
                    ptr->unk_2A += 0x1770;
                    tmpf1 = func_8003C890(&globalCtx->colCtx, &sp7C, &sp80);
                    if ((sp7C != NULL) && (ptr->unk_00.y <= tmpf1)) {
                        ptr->unk_28 = 1;
                        ptr->unk_26 = 0x1E;
                        ptr->unk_00.y = tmpf1 + 1.0f;

                        sp64 = D_8095C220;
                        ptr->unk_0C = sp64;
                        ptr->unk_18 = sp64;
                        ptr->unk_2A = -0x4000;
                    }

                    if (ptr->unk_26 == 0) {
                        ptr->unk_24 = 0;
                    }

                } else if (ptr->unk_28 == 2) {
                    if (ptr->unk_26 == 0) {
                        ptr->unk_24 = 0;
                    }

                } else {
                    Math_SmoothScaleMaxMinF(&ptr->unk_44[0], 0.075f, 1.0f, 0.005f, 0.0f);
                    Math_SmoothScaleMaxMinF(&ptr->unk_44[2], 0.0f, 0.6f, 0.005f, 0.0013f);
                    if ((globalCtx->gameplayFrames % 4) == 0) {
                        Math_SmoothScaleMaxMinS(&ptr->unk_30[0], 0x5F, 1, 1, 0);
                    }
                }
                ptr->unk_44[1] += ptr->unk_44[2];
            }

            if (ptr->unk_24 == 7) {
                refActor = ptr->unk_54;

                ptr->unk_2E += 0x157C;
                ptr->unk_38[3] = (s16)(Math_Sins(ptr->unk_2E) * 50.0f) + 0x50;
                Math_SmoothScaleMaxMinF(&ptr->unk_40[0], ptr->unk_44[0], 1.0f, 0.01f, 0.005f);
                ptr->unk_00.x = ptr->unk_44[1] + refActor->actor.posRot.pos.x;
                ptr->unk_00.y = ptr->unk_44[2] + refActor->actor.posRot.pos.y;
                ptr->unk_00.z = ptr->unk_44[3] + refActor->actor.posRot.pos.z;

                switch (ptr->unk_28) {
                    case 0:
                        if (ptr->unk_26 == 0) {
                            tmp16 = Math_Vec3f_Yaw(&refActor->actor.posRot.pos, &ptr->unk_00);
                            ptr->unk_24 = 0;
                            func_8094F60C(globalCtx, ptr, tmp16, ptr->unk_40[0] * 4500.0f, 1);
                            func_8094F734(globalCtx, ptr, tmp16, ptr->unk_40[0] * 1.2f);
                        }
                        break;

                    case 1:
                    case 2:
                        if (refActor->unk_195 != 0) {
                            ptr->unk_24 = 0;
                            tmp16 = Math_Vec3f_Yaw(&refActor->actor.posRot.pos, &ptr->unk_00);
                            func_8094F60C(globalCtx, ptr, tmp16, ptr->unk_40[0] * 4500.0f, 1);
                            func_8094F734(globalCtx, ptr, tmp16, ptr->unk_40[0] * 1.2f);
                        }
                        break;
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Boss_Va/func_809597F4.s")
#endif

void func_8095A188(BossVaEffect* ptr, GlobalContext* globalCtx) {
    GraphicsContext* localGfx = globalCtx->state.gfxCtx;
    BossVa* refActor;
    s16 i;
    u8 flag = 0;
    BossVaEffect* ptrHead = ptr;
    Camera* camera = Gameplay_GetCamera(globalCtx, D_8095C23C);

    GraphicsContext* gfxCtx = localGfx;
    Gfx* dispRefs[4];

    Graph_OpenDisps(dispRefs, localGfx, "../z_boss_va.c", 0x1359);

    for (i = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 1) {
            if (!flag) {
                func_80093D84(globalCtx->state.gfxCtx);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x82, 0x82, 0x1E, 0x00);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_060156A0);
                flag += 1;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xE6, 0xE6, 0xE6, ptr->unk_30[3]);
            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_RotateZ((ptr->unk_2E / 32768.0f) * 3.1416f, 1);
            Matrix_Scale(ptr->unk_40[0] * 0.0185f, ptr->unk_40[0] * 0.0185f, 1.0f, 1);
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(localGfx, "../z_boss_va.c", 0x1370),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06015710);
        }
    }

    ptr = ptrHead;
    for (i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 4) {
            if (!flag) {
                func_80093D84(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_06011738);
                flag += 1;
            }
            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_Scale(ptr->unk_40[0], ptr->unk_40[0], ptr->unk_40[0], 1);
            Matrix_RotateZ((ptr->unk_2E / 32768.0f) * M_PI, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(localGfx, "../z_boss_va.c", 0x138A),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPPipeSync(gfxCtx->polyXlu.p++);
            gSPSegment(gfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(D_8095C300[ptr->unk_28]));
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, ptr->unk_30[0], ptr->unk_30[1], ptr->unk_30[2], ptr->unk_30[3]);
            gDPPipeSync(gfxCtx->polyXlu.p++);
            gDPSetEnvColor(gfxCtx->polyXlu.p++, ptr->unk_38[0], ptr->unk_38[1], ptr->unk_38[2], ptr->unk_38[3]);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06011768);
        }
    }

    ptr = ptrHead;
    for (i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 6) {
            if (!flag) {
                func_80093D84(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_06009430);
                gSPSegment(gfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(&D_04055DB0));
                flag += 1;
            }

            gDPPipeSync(gfxCtx->polyXlu.p++);
            gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x00, 0x64, 0x00, ptr->unk_38[3]);
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x00, 0x96, 0x00, ptr->unk_30[3]);

            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            if (ptr->unk_28 == 2) {
                Matrix_RotateX(1.5707964f, 1);
            } else {
                func_800D1FD4(&globalCtx->mf_11DA0);
            }

            Matrix_Scale(ptr->unk_40[0], ptr->unk_40[0], 1.0f, 1);

            gDPPipeSync(gfxCtx->polyXlu.p++);
            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(localGfx, "../z_boss_va.c", 0x13BC),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06009468);
        }
    }

    { s32 someBullshit; }

    ptr = ptrHead;
    for (i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 7) {
            refActor = ptr->unk_54;
            if (!flag) {
                func_80093D18(globalCtx->state.gfxCtx);
                gDPSetEnvColor(gfxCtx->polyOpa.p++, 0x00, 0x00, 0x00, ptr->unk_38[3]);
                gSPDisplayList(gfxCtx->polyOpa.p++, D_060128B8);
                flag += 1;
            }

            if ((ptr->unk_28 != 1) || ((Math_Vec3f_DistXZ(&camera->eye, &ptr->unk_00) -
                                        Math_Vec3f_DistXZ(&camera->eye, &refActor->actor.posRot.pos)) < 10.0f)) {
                Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
                Matrix_Scale(ptr->unk_40[0], ptr->unk_40[0], ptr->unk_40[0], 1);

                gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(localGfx, "../z_boss_va.c", 0x13D8),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gfxCtx->polyOpa.p++, D_06012948);
            }
        }
    }

    ptr = ptrHead;
    for (i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 8) {
            if (!flag) {
                func_80093D18(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyOpa.p++, D_06012BA0);
                flag += 1;
            }

            gDPPipeSync(gfxCtx->polyOpa.p++);
            gDPSetEnvColor(gfxCtx->polyOpa.p++, 0xFF, 0xFF, 0xFF, ptr->unk_30[3]);
            gDPSetPrimColor(gfxCtx->polyOpa.p++, 0, 0, ptr->unk_30[0], ptr->unk_30[1], ptr->unk_30[2], ptr->unk_30[3]);

            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            Matrix_RotateRPY(ptr->unk_2A, ptr->unk_2C, 0, 1);
            Matrix_Scale(ptr->unk_40[0], ptr->unk_40[0], ptr->unk_40[0], 1);
            Matrix_RotateX(ptr->unk_44[1] * 0.115f, 1);
            Matrix_RotateY(ptr->unk_44[1] * 0.13f, 1);
            Matrix_RotateZ(ptr->unk_44[1] * 0.1f, 1);
            Matrix_Scale(1.0f - ptr->unk_44[0], ptr->unk_44[0] + 1.0f, 1.0f - ptr->unk_44[0], 1);
            Matrix_RotateZ(-(ptr->unk_44[1] * 0.1f), 1);
            Matrix_RotateY(-(ptr->unk_44[1] * 0.13f), 1);
            Matrix_RotateX(-(ptr->unk_44[1] * 0.115f), 1);

            gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(localGfx, "../z_boss_va.c", 0x1404),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyOpa.p++, D_06012C50);
        }
    }

    ptr = ptrHead;
    for (i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 5) {
            if (!flag) {
                func_80093D84(globalCtx->state.gfxCtx);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_060135B0);
                flag += 1;
            }

            gDPPipeSync(gfxCtx->polyXlu.p++);
            gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xFF, 0x32, ptr->unk_30[3]);
            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, ptr->unk_30[3]);

            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            Matrix_RotateRPY(ptr->unk_2A, ptr->unk_2C, 0, 1);
            Matrix_Scale(ptr->unk_40[0], ptr->unk_40[0], ptr->unk_40[0], 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(localGfx, "../z_boss_va.c", 0x1420),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06013638);
        }
    }

    ptr = ptrHead;
    for (i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 2) {
            if (!flag) {
                func_80093C14(globalCtx->state.gfxCtx);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x82, 0x82, 0x1E, 0x00);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_060156A0);
                flag += 1;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xE6, 0xE6, 0xE6, ptr->unk_30[3]);
            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            func_800D1FD4(&globalCtx->mf_11DA0);
            Matrix_RotateZ((ptr->unk_2E / 32768.0f) * M_PI, 1);
            Matrix_Scale(ptr->unk_40[0] * 0.02f, ptr->unk_40[0] * 0.02f, 1.0f, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(localGfx, "../z_boss_va.c", 0x143C),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06015710);
        }
    }

    ptr = ptrHead;
    for (i = 0, flag = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 3) {
            if (!flag) {
                func_80093D84(globalCtx->state.gfxCtx);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xFF, 0x64, 0x00);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_06008F08);
                flag += 1;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, ptr->unk_30[3]);
            Matrix_Translate(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, 0);
            Matrix_RotateZ((ptr->unk_2E / 32768.0f) * M_PI, 1);
            Matrix_RotateY((ptr->unk_2C / 32768.0f) * M_PI, 1);
            Matrix_Scale(ptr->unk_40[0], ptr->unk_40[0], 1.0f, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(localGfx, "../z_boss_va.c", 0x1458),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfxCtx->polyXlu.p++, D_06008F70);
        }
    }

    Graph_CloseDisps(dispRefs, localGfx, "../z_boss_va.c", 0x145F);
}

void func_8095B028(GlobalContext* globalCtx, BossVaEffect* ptr, BossVa* this, Vec3f* arg3, s16 arg4, u8 arg5) {
    Player* player = PLAYER;
    s16 sp52;
    Vec3f sp44 = D_8095C320;
    Vec3f sp38;
    s16 i;

    for (i = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 0) {
            ptr->unk_24 = 1;
            ptr->unk_54 = this;
            ptr->unk_00 = sp44;
            ptr->unk_26 = (s16)(Math_Rand_ZeroOne() * 10.0f) + 0x6F;
            ptr->unk_0C = ptr->unk_18 = D_8095C220;
            ptr->unk_28 = arg5;

            switch (arg5) {
                case 4:
                    ptr->unk_24 = 3;

                case 1:
                    sp38 = *arg3;
                    sp38.x += this->actor.posRot.pos.x;
                    sp38.z += this->actor.posRot.pos.z;
                    ptr->unk_44[1] = Math_Vec3f_DistXZ(&this->actor.posRot.pos, &sp38);
                    ptr->unk_2A = Math_Vec3f_Pitch(&this->actor.posRot.pos, &((BossVa*)this->actor.attachedA)->unk_1D8);
                    break;

                case 5:
                    ptr->unk_24 = 3;

                case 2:
                    ptr->unk_44[1] = arg3->x;
                    ptr->unk_44[3] = arg3->z;
                    break;

                case 3:
                    ptr->unk_24 = 2;
                    ptr->unk_00.x = arg3->x + this->actor.posRot.pos.x;
                    ptr->unk_00.y = arg3->y + this->actor.posRot.pos.y;
                    ptr->unk_00.z = arg3->z + this->actor.posRot.pos.z;
                    ptr->unk_26 = 0x6F;
                    break;

                case 6:
                    ptr->unk_24 = 3;
                    sp52 = Math_Rand_ZeroFloat(17.9f);
                    ptr->unk_00.x = player->unk_908[sp52].x + Math_Rand_CenteredFloat(10.0f);
                    ptr->unk_00.y = player->unk_908[sp52].y + Math_Rand_CenteredFloat(15.0f);
                    ptr->unk_00.z = player->unk_908[sp52].z + Math_Rand_CenteredFloat(10.0f);
            }

            ptr->unk_44[2] = arg3->y;
            ptr->unk_40[0] = (Math_Rand_ZeroFloat(arg4) + arg4) * 0.01f;
            ptr->unk_30[3] = 0xFF;
            break;
        }
    }
}

void func_8095B318(GlobalContext* globalCtx, BossVaEffect* ptr, BossVa* this, Vec3f* arg3, s16 arg4, u8 arg5) {
    Vec3f sp34 = D_8095C32C;
    s16 i;
    Vec3f sp24;

    for (i = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 0) {
            ptr->unk_24 = 4;
            ptr->unk_54 = this;

            ptr->unk_00 = sp34;

            sp24 = D_8095C220;
            ptr->unk_18 = sp24;
            ptr->unk_0C = sp24;

            ptr->unk_28 = 0;
            ptr->unk_44[1] = arg3->x;
            ptr->unk_44[3] = arg3->z;
            ptr->unk_44[2] = arg3->y;
            ptr->unk_26 = (s16)(Math_Rand_ZeroOne() * 10.0f) + 0x6F;
            ptr->unk_30[0] = ptr->unk_30[1] = ptr->unk_30[2] = ptr->unk_30[3] = 0xE6;
            ptr->unk_38[0] = 0;
            ptr->unk_38[1] = 0x64;
            ptr->unk_38[2] = 0xDC;
            ptr->unk_38[3] = 0xA0;

            ptr->unk_40[0] = (Math_Rand_ZeroFloat(arg4) + arg4) * 0.01f;
            return;
        }
    }
}

void func_8095B4A4(GlobalContext* globalCtx, BossVaEffect* ptr, Vec3f* arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 i;
    Vec3f sp38 = D_8095C338;
    Vec3f sp2C = D_8095C344;
    f32 sp28;
    f32 sp24;

    for (i = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 0) {
            ptr->unk_24 = 6;
            ptr->unk_00 = *arg2;
            ptr->unk_28 = 0;

            sp28 = Math_Sins(arg4) * 6.0f;
            sp24 = Math_Rand_CenteredFloat(1.0f);
            sp2C.x = (-Math_Sins(arg5) * sp28) + sp24;
            sp24 = Math_Rand_CenteredFloat(1.0f);
            sp2C.z = (-Math_Coss(arg5) * sp28) + sp24;

            ptr->unk_0C = sp2C;

            sp38.y = Math_Rand_CenteredFloat(0.3f) - 1.0f;
            ptr->unk_18 = sp38;

            ptr->unk_26 = 0x14;
            ptr->unk_38[3] = 0x64;
            ptr->unk_30[3] = 0xC8;
            ptr->unk_40[0] = (Math_Rand_ZeroFloat(arg3) + arg3) * 0.01f;
            break;
        }
    }
}

void func_8095B670(GlobalContext* globalCtx, BossVaEffect* ptr, Vec3f* arg2, s16 arg3, s16 arg4) {
    s32 i;
    f32 sp38;
    Vec3f sp2C = D_8095C350;
    Vec3f sp20;

    for (i = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 0) {
            ptr->unk_24 = 6;
            ptr->unk_00 = *arg2;

            ptr->unk_28 = 1;

            sp38 = Math_Rand_ZeroOne() * 7.0f;
            sp20.x = Math_Sins(arg3) * sp38;
            sp20.y = Math_Rand_CenteredFloat(4.0f) + 4.0f;
            sp20.z = Math_Coss(arg3) * sp38;
            ptr->unk_0C = sp20;

            sp2C.y = Math_Rand_CenteredFloat(0.3f) - 1.0f;
            ptr->unk_18 = sp2C;

            if (D_809668D2 < 0x14) {
                ptr->unk_26 = 0x14;
            } else {
                ptr->unk_26 = 0x3C;
            }
            ptr->unk_38[3] = 0x64;
            ptr->unk_30[3] = 0xC8;
            ptr->unk_40[0] = arg4 * 0.01f;
            break;
        }
    }
}

void func_8095B80C(GlobalContext* globalCtx, BossVaEffect* ptr, BossVa* this, Vec3f* arg3, s16 arg4, u8 arg5) {
    Vec3f sp34 = D_8095C35C;
    s16 i;
    Vec3f sp24;

    for (i = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 0) {
            ptr->unk_24 = 7;
            ptr->unk_54 = this;
            ptr->unk_00 = sp34;

            sp24 = D_8095C220;
            ptr->unk_18 = sp24;
            ptr->unk_0C = sp24;

            ptr->unk_28 = arg5;
            ptr->unk_2E = 0;

            ptr->unk_44[1] = arg3->x;
            ptr->unk_44[3] = arg3->z;
            ptr->unk_44[2] = arg3->y;

            ptr->unk_26 = (s16)(Math_Rand_ZeroOne() * 10.0f) + 0xA;
            ptr->unk_38[3] = 0x64;
            ptr->unk_44[0] = arg4 * 0.01f;
            ptr->unk_40[0] = 0.0f;

            if (((i & 3) == 0) || (arg5 == 2)) {
                Audio_PlaySoundGeneral(NA_SE_EN_BALINADE_BREAK, &ptr->unk_00, 4, &D_801333E0, &D_801333E0, &D_801333E8);
            }
            break;
        }
    }
}

void func_8095B9B0(GlobalContext* globalCtx, BossVaEffect* ptr, Vec3f* arg2, s16 arg3, s16 arg4) {
    s32 i;
    f32 sp48;
    Vec3f sp3C = D_8095C368;
    Vec3f sp30;

    for (i = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 0) {
            ptr->unk_24 = 8;
            ptr->unk_00 = *arg2;
            ptr->unk_44[0] = 0.0f;

            sp48 = (Math_Rand_ZeroOne() * 4.0f) + 4.0f;
            sp30.x = Math_Sins(arg3) * sp48;
            sp30.y = Math_Rand_CenteredFloat(8.0f);
            sp30.z = Math_Coss(arg3) * sp48;
            ptr->unk_0C = sp30;

            sp3C.y = Math_Rand_CenteredFloat(0.3f) - 1.0f;
            ptr->unk_18 = sp3C;

            ptr->unk_26 = 0x14;
            if (D_809668D2 < 0x14) {
                ptr->unk_28 = 2;
            } else {
                ptr->unk_28 = 0;
            }

            ptr->unk_30[3] = ptr->unk_38[0] = ptr->unk_38[1] = ptr->unk_38[2] = ptr->unk_38[3] = 0xFF;

            ptr->unk_30[0] = 0x9B;
            ptr->unk_30[1] = ptr->unk_30[2] = 0x37;

            ptr->unk_2A = Math_Rand_CenteredFloat(65536.0f);
            ptr->unk_2C = Math_Rand_CenteredFloat(65536.0f);
            ptr->unk_40[0] = (Math_Rand_ZeroFloat(arg4) + arg4) * 0.01f;
            ptr->unk_44[2] = (Math_Rand_ZeroOne() * 0.25f) + 0.9f;
            break;
        }
    }
}

void func_8095BBD0(GlobalContext* globalCtx, BossVaEffect* ptr, BossVa* this, Vec3f* arg3, Vec3s* arg4, s16 arg5,
                   u8 arg6) {
    Vec3f sp2C = D_8095C374;
    s16 i;
    Vec3f sp1C;

    for (i = 0; i < 400; i++, ptr++) {
        if (ptr->unk_24 == 0) {
            ptr->unk_24 = 5;
            ptr->unk_54 = this;
            ptr->unk_00 = *arg3;

            sp1C = D_8095C220;
            ptr->unk_18 = sp1C;
            ptr->unk_0C = sp1C;

            ptr->unk_28 = arg6;
            ptr->unk_2A = arg4->x + 0x4000;
            ptr->unk_2C = arg4->y;
            ptr->unk_26 = (s16)(Math_Rand_ZeroOne() * 10.0f) + 0xA;
            ptr->unk_30[3] = 0xF0;
            ptr->unk_40[0] = arg5 * 0.01f;
            break;
        }
    }
}

void func_8095BD24(GlobalContext* globalCtx, s16 arg1) {
    MtxF sp98;
    f32 tmpf1;
    f32 tmpf2 = 0.0f;
    f32 tmpf3;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Gfx* dispRefs[4];
    s32 i;

    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x15E0);
    Matrix_Translate(0.0f, 80.0f, 400.0f, 0);
    Matrix_RotateY(M_PI, 1);
    tmpf3 = (arg1 * 0.01f) * 0.1f;
    Matrix_Scale(0.1f, tmpf3, 0.1f, 1);

    if (tmpf3 != 0.0f) {
        tmpf1 = 0.1f / tmpf3;
    } else {
        tmpf1 = 0.0f;
    }

    Matrix_Get(&sp98);

    for (i = 0; i < 8; i++, tmpf2 -= 0.7853982f) {
        Matrix_Put(&sp98);
        Matrix_RotateZ(tmpf2, 1);
        Matrix_Translate(0.0f, D_8095C3A0[i] * tmpf1, 0.0f, 1);

        gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_boss_va.c", 0x15F5),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxCtx->polyOpa.p++, D_8095C380[i]);
    }

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_boss_va.c", 0x15FD);
}
