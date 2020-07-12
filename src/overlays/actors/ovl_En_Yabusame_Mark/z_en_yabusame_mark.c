/*
 * File: z_en_yabusame_mark.c
 * Overlay: ovl_En_Yabusame_Mark
 * Description: Horseback Archery Target (arrow hitbox)
 */

#include "z_en_yabusame_mark.h"
#include <vt.h>

#define FLAGS 0x00000000

#define THIS ((EnYabusameMark*)thisx)

void EnYabusameMark_Init(Actor* thisx, GlobalContext* globalCtx);
void EnYabusameMark_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnYabusameMark_Update(Actor* thisx, GlobalContext* globalCtx);
void func_80B42F74(EnYabusameMark* this, GlobalContext* globalCtx);

const ActorInit En_Yabusame_Mark_InitVars = {
    ACTOR_EN_YABUSAME_MARK,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnYabusameMark),
    (ActorFunc)EnYabusameMark_Init,
    (ActorFunc)EnYabusameMark_Destroy,
    (ActorFunc)EnYabusameMark_Update,
    NULL,
};

static ColliderQuadInit D_80B434F0 =
{
    { COLTYPE_UNK1, 0x2F, 0x06, 0x00, 0x00, COLSHAPE_JNTSPH },
    { 0x00, { 0x00000210, 0x80, 0xB4 }, { 0x80B42DC0, 0x80, 0xB4 }, 0x00, 0x00, 0x00 },
    { { { 70.0f, 70.0f, 0.0f }, { 70.0f, -70.0f, 0.0f }, { -70.0f, 70.0f, 0.0f }, { -70.0f, -70.0f, 0.0f } } },
};


Vec3f D_80B43560[][4] = {
    {
       { 70.0f,  70.0f, 0.0f}, 
       { 70.0f, -70.0f, 0.0f}, 
       {-70.0f,  70.0f, 0.0f}, 
       {-70.0f, -70.0f, 0.0f}, 
    },
    {
       { 90.0f, 130.0f, -120.0f}, 
       {-25.0f, -80.0f, -130.0f}, 
       { 90.0f, 130.0f,  120.0f}, 
       {-25.0f, -80.0f,  130.0f}, 
    },
    {
       {115.0f,  160.0f, -150.0f}, 
       {-50.0f, -140.0f, -160.0f}, 
       {115.0f,  160.0f,  150.0f}, 
       {-50.0f, -140.0f,  160.0f}, 
    }
};

Vec3f D_80B435F0[] = {
    {3382.0f, 1734.0f, -4946.0f}, 
    {3360.0f, 1734.0f,   495.0f}, 
    {4517.0f, 1682.0f, -1779.0f}, 
    {4517.0f, 1682.0f, -2813.0f}, 
    {4522.0f, 1727.0f, -2296.0f}, 
};

f32 D_80B4362C[][4] = {
    {20.0f,  40.0f,  60.0f, 777.0f},  
    {40.0f,  80.0f, 120.0f, 777.0f},
    {40.0f, 120.0f, 160.0f, 777.0f}, 
};

Vec3f D_80B4365C = {
    0.0f, 0.0f, 0.0f
};

Vec3f D_80B43668 = {
    0.0f, 0.0f, 0.0f
};

void EnYabusameMark_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnYabusameMark* this = THIS;
    Collider_DestroyQuad(globalCtx, &this->unk_190);
}

void EnYabusameMark_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnYabusameMark* this = THIS;

    osSyncPrintf("\n\n");
    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ やぶさめまと ☆☆☆☆☆ %x\n" VT_RST, this->actor.params);
    this->actor.flags &= -2;
    this->unk_150 = this->actor.params;
    this->actor.unk_1F = 5;
    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 種類インデックス \t   ☆☆☆☆☆ %d\n" VT_RST, this->unk_150);

    switch (this->unk_150) {
        case 0:
            this->unk_152 = 0;
            if (0.0f < this->actor.posRot.pos.z) {
                this->unk_152 = 1;
            }
            break;
        case 1:
            this->unk_152 = 2;
            if (this->actor.posRot.pos.z < -2000.0f) {
                this->unk_152 = 3;
            }
            break;
        case 2:
            this->unk_152 = 4;
            break;
    }

    Collider_InitQuad(globalCtx, &this->unk_190);
    Collider_SetQuad(globalCtx, &this->unk_190, &this->actor, &D_80B434F0);
    this->unk_154 = this->actor.posRot.pos;
    this->actor.flags |= 0x10;
    if (gSaveContext.sceneSetupIndex != 4) {
        Actor_Kill(&this->actor);
        return;
    }
    osSyncPrintf(VT_FGCOL(PURPLE) "☆☆☆☆☆ 種類       ☆☆☆☆☆ %d\n" VT_RST, this->unk_150);
    osSyncPrintf(VT_FGCOL(CYAN) "☆☆☆☆☆ さらに分類 ☆☆☆☆☆ %d\n" VT_RST, this->unk_152);
    this->actionFunc = func_80B42F74;
}

//#define A
#ifdef A
void func_80B42F74(EnYabusameMark* this, GlobalContext* globalCtx) {
    

    Vec3f sp5C = D_80B4365C;
    Vec3f sp50 = D_80B43668;
    Vec3f sp44;

    f32 a;
    f32 b;
    f32 c;

    f32* p1;
    Vec3f* p2;

    s32 tmp;
    
    if (this->unk_190.base.acFlags & 2) {
        this->unk_190.base.acFlags &= 0xFFFD;

        sp44.x = this->unk_190.body.bumper.unk_06.x;
        sp44.y = this->unk_190.body.bumper.unk_06.y;
        sp44.z = this->unk_190.body.bumper.unk_06.z;

        sp50.y = 15.0f;
    
        func_80029CC8(globalCtx, 0, 0x2BC, &sp44);

        p1 = &D_80B435F0[this->unk_152].x;
        p2 = &D_80B4362C[this->unk_150];

        a = fabsf(D_80B435F0[this->unk_152].x - sp44.x);
        b = fabsf(p2->y - sp44.y);
        c = fabsf(p2->z - sp44.z);

        tmp = 2;
        if ((D_80B4362C[this->unk_150][0] < a) || (D_80B4362C[this->unk_150][0] < b) || (D_80B4362C[this->unk_150][0] < c)) { 
            tmp = 1;
            if ((D_80B4362C[this->unk_150][1] < a) || (D_80B4362C[this->unk_150][1] < b) || (D_80B4362C[this->unk_150][1] < c)) {
                tmp = 0;
                if ((D_80B4362C[this->unk_150][2] < a) || (D_80B4362C[this->unk_150][2] < b) || (D_80B4362C[this->unk_150][2] < c)) {
                    return;
                }
            }
        }

        osSyncPrintf("\n\n");
        osSyncPrintf(VT_FGCOL(GREEN)  "☆☆☆☆☆ posＸ ☆☆☆☆☆ %f\n" VT_RST, sp44.x);
        osSyncPrintf(VT_FGCOL(GREEN)  "☆☆☆☆☆ posＹ ☆☆☆☆☆ %f\n" VT_RST, sp44.y);
        osSyncPrintf(VT_FGCOL(GREEN)  "☆☆☆☆☆ posＺ ☆☆☆☆☆ %f\n" VT_RST, sp44.z);
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ hitＸ ☆☆☆☆☆ %f\n" VT_RST, D_80B435F0[this->unk_152].x);
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ hitＹ ☆☆☆☆☆ %f\n" VT_RST, D_80B435F0[this->unk_152].y);
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ hitＺ ☆☆☆☆☆ %f\n" VT_RST, D_80B435F0[this->unk_152].z);
        osSyncPrintf(VT_FGCOL(PURPLE) "☆☆☆☆☆ 小    ☆☆☆☆☆ %f\n" VT_RST, p2->x);
        osSyncPrintf(VT_FGCOL(PURPLE) "☆☆☆☆☆ 大    ☆☆☆☆☆ %f\n" VT_RST, p2->z);
        osSyncPrintf(VT_FGCOL(PURPLE) "☆☆☆☆☆ point ☆☆☆☆☆ %d\n" VT_RST, tmp);
        osSyncPrintf("\n\n");

        if (tmp == 2) {
            func_800F5C64(0x922);
        }
        if (tmp == 1) {
            func_800F8D04(0x4807U);
            func_80078884(0x4807U);
        }
        if (tmp == 0) {
            func_80078884(0x4808U);
        }
        func_8002A5F4(globalCtx, &sp44, &sp50, &sp5C, 5, tmp);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Yabusame_Mark/func_80B42F74.s")
#endif
#undef A

//#define A
#ifdef A
void EnYabusameMark_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnYabusameMark* this = THIS;

    this->actionFunc(this, globalCtx);

    this->unk_160.x = D_80B43560[this->unk_150][0].x + this->actor.posRot.pos.x;
    this->unk_160.y = D_80B43560[this->unk_150][0].y + this->actor.posRot.pos.y;
    this->unk_160.z = D_80B43560[this->unk_150][0].z + this->actor.posRot.pos.z;
    this->unk_16C.x = D_80B43560[this->unk_150][1].x + this->actor.posRot.pos.x;
    this->unk_16C.y = D_80B43560[this->unk_150][1].y + this->actor.posRot.pos.y;
    this->unk_16C.z = D_80B43560[this->unk_150][1].z + this->actor.posRot.pos.z;
    this->unk_178.x = D_80B43560[this->unk_150][2].x + this->actor.posRot.pos.x;
    this->unk_178.y = D_80B43560[this->unk_150][2].y + this->actor.posRot.pos.y;
    this->unk_178.z = D_80B43560[this->unk_150][2].z + this->actor.posRot.pos.z;
    this->unk_184.x = D_80B43560[this->unk_150][3].x + this->actor.posRot.pos.x;
    this->unk_184.y = D_80B43560[this->unk_150][3].y + this->actor.posRot.pos.y;
    this->unk_184.z = D_80B43560[this->unk_150][3].z + this->actor.posRot.pos.z;

    func_80062734(&this->unk_190, &this->unk_160, &this->unk_16C, &this->unk_178, &this->unk_184);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_190.base);
    if (BREG(0) != 0) {
        DebugDisplay_AddObject(this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z, 
            this->actor.posRot.rot.x, this->actor.posRot.rot.y, this->actor.posRot.rot.z, 
            1.0f, 1.0f, 1.0f, 0, 0xFF, 0, 0xFF, 4, globalCtx->state.gfxCtx);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Yabusame_Mark/EnYabusameMark_Update.s")
#endif
#undef A