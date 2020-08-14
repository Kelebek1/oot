#include "overlays/actors/ovl_En_Reeba/z_en_reeba.h"
#include "z_en_encount1.h"
#include "vt.h"

#define FLAGS 0x08000010

#define THIS ((EnEncount1*)thisx)

void EnEncount1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEncount1_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A0693C(EnEncount1 *this, GlobalContext* globalCtx);
void func_80A06CD0(EnEncount1 *this, GlobalContext* globalCtx);
void func_80A06E88(EnEncount1 *this, GlobalContext* globalCtx);

const ActorInit En_Encount1_InitVars = {
    ACTOR_EN_ENCOUNT1,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnEncount1),
    (ActorFunc)EnEncount1_Init,
    NULL,
    (ActorFunc)EnEncount1_Update,
    NULL,
};

s16 D_80A07450[] = {
    0x0000, 0x2710, 0x7148, 0x8EB8, 0xD8F0
};

f32 D_80A0745C[] = {
    200.0f, 170.0f, 120.0f, 120.0f, 170.0f
};

void EnEncount1_Init(Actor* thisx, GlobalContext *globalCtx) {
    EnEncount1 *this = THIS;
    f32 tmpf1;

    if (this->actor.params <= 0) {
        osSyncPrintf("\n\n");
        // input error
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 入力エラーデッス！ ☆☆☆☆☆ \n" VT_RST);
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 入力エラーデッス！ ☆☆☆☆☆ \n" VT_RST);
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 入力エラーデッス！ ☆☆☆☆☆ \n" VT_RST);
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 入力エラーデッス！ ☆☆☆☆☆ \n" VT_RST);
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 入力エラーデッス！ ☆☆☆☆☆ \n" VT_RST);
        osSyncPrintf("\n\n");
        Actor_Kill(&this->actor);
        return;
    }

    this->unk_158 = 0;
    this->unk_154 = (this->actor.params >> 0xB) & 0x1F;
    this->unk_150 = (this->actor.params >> 6) & 0x1F;
    this->unk_156 = this->actor.params & 0x3F;
    this->unk_152 = this->unk_158;
    tmpf1 = (this->actor.posRot.rot.z * 40.0f) + 120.0f;
    this->unk_168 = tmpf1;

    osSyncPrintf("\n\n");
    // left the enemy spawn zone
    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 敵発生ゾーンでた！ ☆☆☆☆☆ %x\n" VT_RST, this->actor.params);
    // type
    osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ 種類\t\t   ☆☆☆☆☆ %d\n" VT_RST, this->unk_154);
    // most that can spawn at once
    osSyncPrintf(VT_FGCOL(PURPLE) "☆☆☆☆☆ 最大同時発生数     ☆☆☆☆☆ %d\n" VT_RST, this->unk_150);
    // most that can spawn total
    osSyncPrintf(VT_FGCOL(CYAN) "☆☆☆☆☆ 最大発生数  \t   ☆☆☆☆☆ %d\n" VT_RST, this->unk_156);
    // spawn check range
    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 発生チェック範囲   ☆☆☆☆☆ %f\n" VT_RST, this->unk_168);
    osSyncPrintf("\n\n");
    this->actor.flags &= ~1;

    switch (this->unk_154) {
        case 0:
            this->unk_164 = 0x1E;
            this->unk_150 = 5;
            if (globalCtx->sceneNum == 0x5E) {
                this->unk_166 = 1;
                this->unk_150 = 3;
            }

            this->actionFunc = func_80A0693C;
            break;

        case 1:
            this->unk_150 = 2;
            this->actionFunc = func_80A06CD0;
            break;

        case 2:
        case 3:
            if (globalCtx->sceneNum == 0x51) {
                this->unk_156 = 10000;
            }
            this->actionFunc = func_80A06E88;
            break;
    }
}

void func_80A0693C(EnEncount1 *this, GlobalContext *globalCtx) {
    f32 tmpf1;
    f32 var1;
    s16 var2;
    s16 var3;
    u32 tmp;
    s16 sp86;
    Vec3f sp78;
    CollisionPoly* sp74;
    UNK_PTR sp70;
    EnReeba* reeba;
    Player* player = PLAYER;
    

    this->unk_15A = 0;
    sp78 = this->actor.posRot.pos;
    if ((this->unk_164 == 0) && (globalCtx->csCtx.state == 0) && 
        (this->unk_150 >= this->unk_152) && (this->unk_152 < 5)) {
        tmp = func_80041D4C(&globalCtx->colCtx, player->actor.floorPoly, player->actor.floorPolySource);
        if ((tmp != 4) && (tmp != 7) && (tmp != 0xC)) {
            this->unk_160 = 0;
            return;
        }

        if ((this->unk_166 == 0) || !(this->actor.xzDistFromLink > 1300.0f)) {
            sp86 = 5;
            if (this->unk_166 != 0) {
                sp86 = 3;
            }

            while ((this->unk_152 < this->unk_150) && (this->unk_152 < sp86) && (this->unk_164 == 0)) {
                var1 = D_80A0745C[this->unk_162];
                var2 = D_80A07450[this->unk_162] + player->actor.shape.rot.y;
                var3 = 0;
                if ((this->unk_15E >= 0xA) && (this->unk_16C == NULL)) {
                    this->unk_15E = this->unk_160 = 0;
                    var2 = D_80A07450[0];
                    var1 = D_80A0745C[2];
                    var3 = 1;
                }

                sp78.x = (Math_Sins(var2) * var1) + player->actor.posRot.pos.x;
                sp78.y = player->actor.groundY + 120.0f;
                sp78.z = (Math_Coss(var2) * var1) + player->actor.posRot.pos.z;
                tmpf1 = func_8003C9A4(&globalCtx->colCtx, &sp74, &sp70, &this->actor, &sp78);
                if (tmpf1 <= -32000.0f) {
                    break;
                }

                sp78.y = tmpf1;
                reeba = (EnReeba*)Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_REEBA, sp78.x, sp78.y, sp78.z, 0, 0, 0, var3);
                if (reeba != NULL) {
                    this->unk_152++;
                    reeba->unk_280 = this->unk_162;
                    this->unk_162++;
                    if (this->unk_162 >= 5) {
                        this->unk_162 = 0;
                    }

                    this->unk_160++;
                    if (this->unk_160 >= 0xC) {
                        this->unk_164 = 0x96;
                        this->unk_160 = 0;
                    }

                    if (var3 != 0) {
                        this->unk_164 = 0x12C;
                        this->unk_16C = reeba;
                    }

                    if (this->unk_166 == 0) {
                        this->unk_150 = (s16)Math_Rand_ZeroFloat(3.99f) + 2;
                    } else {
                        this->unk_150 = (s16)Math_Rand_ZeroFloat(2.99f) + 1;
                    }
                } else {
                    // Couldn't spawn!
                    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n" VT_RST);
                    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n" VT_RST);
                    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n" VT_RST);
                    break;
                }
            }
        }
    }
    if (sp86) {};
}

void func_80A06CD0(EnEncount1 *this, GlobalContext *globalCtx) {
    s32 pad;
    UNK_PTR sp58;
    CollisionPoly* sp54;
    Vec3f sp48;
    f32 tmpf1;
    Player* player = PLAYER;

    if (this->unk_164 == 0) {
        this->unk_164 = 10;
        if ((fabsf(player->actor.posRot.pos.y - this->actor.posRot.pos.y) > 100.0f) || 
            (this->actor.xzDistFromLink > this->unk_168)) {
            this->unk_15A++;
            return;
        }

        this->unk_15A = 0;
        if ((this->unk_152 < this->unk_150) && (this->unk_158 < this->unk_156)) {
            sp48.x = Math_Rand_CenteredFloat(50.0f) + this->actor.posRot.pos.x;
            sp48.y = this->actor.posRot.pos.y + 120.0f;
            sp48.z = Math_Rand_CenteredFloat(50.0f) + this->actor.posRot.pos.z;
            tmpf1 = func_8003C9A4(&globalCtx->colCtx, &sp54, &sp58, &this->actor, &sp48);
            if (tmpf1 <= -32000.0f) {
                return;
            }
            sp48.y = tmpf1;
            if (Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_TITE, sp48.x, sp48.y, sp48.z, 0, 0, 0, -1) != NULL) {
                this->unk_152++;
                this->unk_158++;
            } else {
                osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n" VT_RST);
                osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n" VT_RST);
                osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n" VT_RST);
            }
        }
    }
}

#ifdef NON_MATCHING
// temp2 casting
void func_80A06E88(EnEncount1 *this, GlobalContext *globalCtx) {
    f32 tmpf1;
    f32 tmpf2;
    s16 rotY;
    s16 tmp1;
    s16 tmp2;
    Vec3f sp98;
    CollisionPoly *sp94;
    UNK_PTR sp90;
    Actor *refActor;
    Player* player = PLAYER;

    if (globalCtx->sceneNum != 0x51) {
        if ((fabsf(player->actor.posRot.pos.y - this->actor.posRot.pos.y) > 100.0f) || 
            (this->unk_168 < this->actor.xzDistFromLink)) {
            this->unk_15A++;
            return;
        }
    } else if ((gSaveContext.nightFlag == 0) || (func_8008F080(globalCtx) == 4)) {
        this->unk_15E = 0;
        return;
    }

    this->unk_15A = 0;
    sp98 = this->actor.posRot.pos;

    if ((this->unk_152 < this->unk_150) && (this->unk_158 < this->unk_156)) {
        while ((this->unk_152 < this->unk_150) && (this->unk_158 < this->unk_156)) {
            if (0x51 == globalCtx->sceneNum) {
                if ((player->unk_89E == 0) || (player->actor.floorPolySource != 0x32) ||
                    !(player->actor.bgCheckFlags & 1) || (player->stateFlags1 & 0x8000000)) {
                    this->unk_15C = 0x3C;
                    return;
                }

                if (this->unk_15C == 0x3C) {
                    this->unk_150 = 2;
                }

                if (this->unk_15C != 0) {
                    this->unk_15C--;
                    return;
                }

                
                tmpf1 = Math_Rand_CenteredFloat(40.0f) + 200.0f;
                rotY = player->actor.shape.rot.y;
                if (this->unk_152 != 0) {
                    rotY = -rotY;
                    tmpf1 = Math_Rand_CenteredFloat(40.0f) + 100.0f;
                }

                sp98.x = (player->actor.posRot.pos.x + (Math_Sins(rotY) * tmpf1)) + Math_Rand_CenteredFloat(40.0f);
                sp98.y = player->actor.groundY + 120.0f;
                sp98.z = (player->actor.posRot.pos.z + (Math_Coss(rotY) * tmpf1)) + Math_Rand_CenteredFloat(40.0f);
                tmpf2 = func_8003C9A4(&globalCtx->colCtx, &sp94, &sp90, &this->actor, &sp98);
                if ((tmpf2 <= -32000.0f) || 
                    ((-32000.0f != player->actor.waterY) && (tmpf2 < (player->actor.posRot.pos.y - player->actor.waterY)))) {
                    return;
                }
                sp98.y = tmpf2;
            }

            if (this->unk_154 == 3) {
                tmp1 = ACTOR_EN_WF;
                tmp2 = -0x100;
            } else {
                tmp2 = 0;
                //tmp3 = this->unk_15E / 10;
                if ((s16)(this->unk_15E / 10) > 0) {
                    if ((s16)(this->unk_15E % 10) == 0) {
                        tmp2 = (this->unk_15E / 10) * 5;
                    }
                }

                this->unk_15E++;
                tmp1 = ACTOR_EN_SKB;
            }

            refActor = Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, tmp1, 
                sp98.x, sp98.y, sp98.z, 0, 0, 0, tmp2);
            if (refActor != NULL) {
                this->unk_152++;
                if (this->unk_152 >= this->unk_150) {
                    this->unk_15C = 0x64;
                }

                if (0x51 != globalCtx->sceneNum) {
                    this->unk_158++;
                }
            } else {
                // Couldn't spawn!
                osSyncPrintf("\x1b[32m☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n\x1b[m");
                osSyncPrintf("\x1b[32m☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n\x1b[m");
                osSyncPrintf("\x1b[32m☆☆☆☆☆ 発生できません！ ☆☆☆☆☆\n\x1b[m");
                return;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Encount1/func_80A06E88.s")
#endif

void EnEncount1_Update(Actor* thisx, GlobalContext *globalCtx) {
    EnEncount1 *this = THIS;

    if (this->unk_164 != 0) {
        this->unk_164--;
    }

    this->actionFunc(this, globalCtx);
    if (BREG(0) != 0) {
        if (this->unk_15A != 0) {
            if ((this->unk_15A & 1) == 0) {
                DebugDisplay_AddObject(this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z, this->actor.posRot.rot.x, this->actor.posRot.rot.y, this->actor.posRot.rot.z, 1.0f, 1.0f, 1.0f, 0x78, 0x78, 0x78, 0xFF, 4, globalCtx->state.gfxCtx);
            }
        } else {
            DebugDisplay_AddObject(this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z, this->actor.posRot.rot.x, this->actor.posRot.rot.y, this->actor.posRot.rot.z, 1.0f, 1.0f, 1.0f, 0xFF, 0, 0xFF, 0xFF, 4, globalCtx->state.gfxCtx);
        }
    }
}
