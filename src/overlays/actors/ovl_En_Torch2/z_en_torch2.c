/*
 * File: z_en_torch2.c
 * Overlay: ovl_En_Torch2
 * Description: Dark Link
 */

#include "z_en_torch2.h"
#include "code/z_actor.c"

#define FLAGS 0x00000035

#define THIS ((EnTorch2*)thisx)

void EnTorch2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTorch2_Destroy(Actor* thisx, GlobalContext* globalCtx);
//void EnTorch2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTorch2_Update(EnTorch2* this, GlobalContext* globalCtx);
void EnTorch2_Draw(Actor* thisx, GlobalContext* globalCtx);
s32 func_8008FCC8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor);
Actor_80033780* func_80033780(GlobalContext* globalCtx, Actor* refActor, f32 arg2);

extern UNK_PTR D_06004764;

const ActorInit En_Torch2_InitVars = {
    ACTOR_EN_TORCH2,
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_TORCH2,
    sizeof(EnTorch2),
    (ActorFunc)EnTorch2_Init,
    (ActorFunc)EnTorch2_Destroy,
    (ActorFunc)EnTorch2_Update,
    (ActorFunc)EnTorch2_Draw,
};

f32 D_80B1F9F0 = 0.0f;
s16 D_80B1F9F4 = 0;
s8 D_80B1FA00 = 0;

DamageTable D_80B1FA08[] = {
    0x10, 0x02, 0x01, 0x02, 
    0x10, 0x02, 0x02, 0x10, 
    0x01, 0x02, 0x04, 0x02, 
    0x02, 0x02, 0x02, 0x02, 
    0x02, 0xE2, 0x60, 0xD3, 
    0x00, 0x00, 0x01, 0x04, 
    0x02, 0x02, 0x08, 0x04, 
    0x00, 0x00, 0x04, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00
};

typedef struct {
    u16 unk_00;
    s8  unk_02;
    s8  unk_03;
    char unk_04[0x8];
    s16 unk_0C;
    char unk_0E[0x4];
    s16 unk_12;
} Torch2Struct1;

Torch2Struct1 D_80B20130;
s8 D_80B2015E;
s8 D_80B20161;
f32 D_80B1F9F8;
s8 D_80B20132;
s8 D_80B20133;
u8 D_80B20148;
f32 D_80B20154;
s8 D_80B2015C;
s8 D_80B2015D;
s8* D_80B20162;
s8* D_80B20163;
s8 D_80B20160;
s8 D_80B20164;
u8 D_80B20165;
Vec3f D_80B20150;

#ifdef NON_MATCHING
void EnTorch2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTorch2* this = THIS;

    D_80B20130.unk_02 = D_80B20130.unk_03 = 0;
    D_80B20130.unk_12 = 0;
    D_80B20130.unk_0C = 0;
    D_80B20130.unk_00 = 0;

    this->player.currentShield = 2;
    this->player.unk_152 = 3;
    this->player.heldItemActionParam = 3;

    func_8008EC04(2);
    globalCtx->unk_11D3C(&this->player.actor, globalCtx, &D_06004764);
    this->player.actor.naviEnemyId = 0x26;
    this->player.unk_498.base.acFlags = 9;
    this->player.unk_564.base.atFlags = 0x11;
    this->player.unk_4E4.base.atFlags = 0x11;
    this->player.unk_564.base.acFlags = 0xD;
    this->player.unk_4E4.base.acFlags = 0xD;
    this->player.unk_564.base.type = 9;
    this->player.unk_4E4.base.type = 9;
    this->player.unk_564.body.toucher.damage = 8;
    this->player.unk_4E4.body.toucher.damage = 8;
    this->player.unk_564.body.bumperFlags = 1;
    this->player.unk_4E4.body.bumperFlags = 1;
    this->player.unk_5E4.base.atFlags = 0x11;
    this->player.unk_5E4.base.acFlags = 0xD;
    this->player.actor.colChkInfo.damageTable = D_80B1FA08;
    this->player.actor.colChkInfo.health = gSaveContext.healthCapacity >> 3;
    this->player.actor.colChkInfo.unk_10 = 0x3C;
    this->player.actor.colChkInfo.unk_12 = 0x64;
    if (globalCtx){};
    globalCtx->unk_11D54(&this->player.actor, globalCtx);

    D_80B2015E = 0;
    D_80B20161 = 0;
    D_80B1F9F8 = 0.0f;

    D_80B20148 = 0;

    D_80B2015C = 0;
    D_80B2015D = 0;
    
    *D_80B20162 = *D_80B20163 = 0;

    D_80B20160 = 0;
    D_80B20164 = 0;
    
    D_80B20165 = 0x5F;
    D_80B20150 = this->player.actor.initPosRot.pos;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Torch2/EnTorch2_Init.s")
#endif

void func_800F5B58(void);

void EnTorch2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTorch2* this = THIS;

    Effect_Delete(globalCtx, this->player.swordEffectId);
    func_800F5B58();
    Collider_DestroyCylinder(globalCtx, &this->player.unk_498);
    Collider_DestroyQuad(globalCtx, &this->player.unk_4E4);
    Collider_DestroyQuad(globalCtx, &this->player.unk_564);
    Collider_DestroyQuad(globalCtx, &this->player.unk_5E4);
}

Actor* func_80B1DB98(GlobalContext* globalCtx, EnTorch2* this) {
    Actor_80033780* ret = func_80033780(globalCtx, &this->player.actor, 4000.0f);
    if (ret != NULL) {
        return &ret->actor;
    } else {
        return func_80033684(globalCtx, &this->player.actor);
    }
}

s32 func_80B1DBD8(GlobalContext *globalCtx, Torch2Struct1 *arg1, EnTorch2 *this) {
    f32 temp = 0.0f;
    s32 mask = 7;
    Player* player = PLAYER;
    s32 temp2;

    if ((this->player.linearVelocity < 0.0f) || (player->linearVelocity < 0.0f)) {
        return 0;
    }

    if (gSaveContext.health < 0x50) {
        mask = 0xF;
        temp += 0.3f;
    }

    if (D_80B20165 != 0xFF) {
        temp += 2.0f;
    }

    if ((!(globalCtx->gameplayFrames & mask) || (D_80B20148 != 0)) && 
         (temp <= Math_Rand_ZeroOne())) {
        if (D_80B20148 == 0) {
            switch ((s32)(Math_Rand_ZeroOne() * 7.0f)) {
                case 1:
                case 5:
                    D_80B1F9F4 += 0x4000;
                    D_80B1F9F0 = 127.0f;
                    break;
                case 2:
                case 6:
                    D_80B1F9F4 -= 0x4000;
                    D_80B1F9F0 = 127.0f;
                    break;
            }
        }
        arg1->unk_00 = 0x4000;
        return 1;
    }
    return 0;
}

void func_80B1DD70(EnTorch2* this, Torch2Struct1* arg1, Actor* actor) {
    actor->shape.rot.y = actor->yawTowardsLink;
    actor->posRot.rot.y = actor->yawTowardsLink;
    D_80B1F9F4 = actor->yawTowardsLink + 0x8000;
    D_80B1F9F0 = 127.0f;
    D_80B1FA00 = 1;
    arg1->unk_00 = 0x8000;
    this->player.invincibilityTimer = 10;
    D_80B20160 = 0;
}

#define NON_MATCHING
void EnTorch2_Update(Actor* thisx, GlobalContext* globalCtx) {
    Camera* camera;
    Actor* refActor;
    s32 temp;
    s16 tmp16;
    f32 sp50;
    s16 sp4E;


    Player* player = PLAYER;
    s16 temp_t0 = player->unkB6 - this->player.actor.shape.rot.y;

    D_80B20130.unk_00 = 0;

    camera = Gameplay_GetCamera(globalCtx, 0);
    refActor = func_80B1DB98(globalCtx, this);
    
    switch (D_80B2015E) {
        case 0:
            this->player.actor.posRot.rot.y = this->player.actor.yawTowardsLink;
            this->player.actor.shape.rot.y = this->player.actor.yawTowardsLink;
            this->player.skelAnime.animCurrentFrame = 0.0f;
            this->player.skelAnime.animPlaybackSpeed = 0.0f;
            this->player.actor.posRot.pos.x = (Math_Sins(this->player.actor.posRot.rot.y) * 25.0f) + D_80B20150.x;
            this->player.actor.posRot.pos.z = (Math_Coss(this->player.actor.posRot.rot.y) * 25.0f) + D_80B20150.z;
            if ((this->player.actor.xzDistFromLink <= 120.0f) || 
                (!func_80033A84(globalCtx, &this-.player.actor)) ||
                (refActor != NULL)) {
                if (refActor != NULL) {
                    D_80B20161 = 1;
                    D_80B1F9F4 = this->player.actor.yawTowardsLink;
                    D_80B1F9F0 = 127.0f;
                    D_80B20130.unk_00 = 0x8000U;
                    D_80B1FA00 = 0;
                    D_80B20132 = Math_Sins(sp68->unk_13A.y - D_80B1F9F4) * D_80B1F9F0;
                    D_80B20133 = Math_Coss(sp68->unk_13A.y - D_80B1F9F4) * D_80B1F9F0;
                }
                func_800F5ACC(0x38);
                D_80B2015E = 1;
            }
            break;

        case 1:
            D_80B1F9F0 = 0.0f;
            if ((this->player.unk_4E4.base.acFlags & 0x80) == 0) {
                if ((this->player.unk_564.base.acFlags & 0x80) != 0) {
block_14:
                    this->player.unk_4E4.base.acFlags = (u8) (this->player.unk_4E4.base.acFlags & 0xFF7F);
                    this->player.unk_564.base.acFlags = (u8) (this->player.unk_564.base.acFlags & 0xFF7F);
                    this->player.unk_4E4.base.atFlags = (u8) (this->player.unk_4E4.base.atFlags | 4);
                    this->player.unk_564.base.atFlags = (u8) (this->player.unk_564.base.atFlags | 4);
                    this->player.unk_498.base.acFlags = (u8) (this->player.unk_498.base.acFlags & 0xFFFD);
                    if (this->player.swordAnimation != D_80B20164) {
                        D_80B20162 = (s8) (D_80B20162 + 1);
                        D_80B20164 = (s8) this->player.swordAnimation;
                    }
                    if ((s32) gSaveContext.health < 0x50) {
                        if ((u8) D_80B20160 != 0) {
                            D_80B20160 = (u8)0;
                            D_80B20163 = (u8)0x32;
                        }
                    }
                }
            } else {
                goto block_14;
            }
            if ((u8) D_80B20160 != 0) {
                if (this->player.swordState != 0) {
                    sp38 = (bitwise f32) &globalCtx->colChkCtx;
                    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, (Collider *) &this->player.unk_4E4);
                    CollisionCheck_SetAC(globalCtx, (bitwise CollisionCheckContext *) sp38, (Collider *) &this->player.unk_564);
                }
            }
            if ((s32) this->player.invincibilityTimer < 0) {
                if ((u8) D_80B2015E != 3) {
                    if ((this->player.unk_498.base.acFlags & 2) != 0) {
                        this->player.unk_498.base.acFlags = (u8) (this->player.unk_498.base.acFlags & 0xFFFD);
                    }
                }
            }
            if ((u8) D_80B20161 != 0) {
                D_80B1F9F0 = 127.0f;
            } else {
                if (sp5C != 0) {
                    D_80B20161 = (u8)1;
                    D_80B1F9F4 = (s16) this->player.actor.yawTowardsLink;
                    D_80B1F9F0 = 127.0f;
                    D_80B20130.unk_00 = (u16)0x8000U;
                } else {
                    if ((u8) D_80B2015C == 0) {
                        if (player->unk843 == 0) {
                            if (-3.0f < player->unk60) {
block_33:
                                if (player->unk842 == 0x11) {
                                    this->player.actor.shape.rot.y = (s16) this->player.actor.yawTowardsLink;
                                    this->player.actor.posRot.rot.y = (s16) this->player.actor.yawTowardsLink;
                                    if ((globalCtx->gameplayFrames & 1) != 0) {
                                        D_80B1F9F4 = (s16) (this->player.actor.yawTowardsLink + 0x4000);
                                    } else {
                                        D_80B1F9F4 = (s16) (this->player.actor.yawTowardsLink - 0x4000);
                                    }
                                    D_80B1F9F0 = 127.0f;
                                    D_80B2015C = (u8)0xF;
                                    D_80B2015D = (u8)0;
                                    D_80B20130.unk_00 = (u16) (D_80B20130.unk_00 | 0x8000);
                                } else {
block_38:
                                    if (D_80B20148 != 0) {
                                        D_80B1F9F0 = 0.0f;
                                        player->unk692 = (u8) (player->unk692 | 4);
                                        Math_SmoothScaleMaxMinF((f32 *) &this->player.actor.posRot, (Math_Sins((s16) ((s32) ((player->unkB6 - 0x3E8) << 0x10) >> 0x10)) * 45.0f) + player->unk24, 1.0f, 5.0f, 0.0f);
                                        Math_SmoothScaleMaxMinF(&this->player.actor.posRot.pos.z, (Math_Coss((s16) ((s32) ((player->unkB6 - 0x3E8) << 0x10) >> 0x10)) * 45.0f) + player->unk2C, 1.0f, 5.0f, 0.0f);
                                        temp_t9 = D_80B2015F - 1;
                                        player_4 = temp_t9 & 0xFF;
                                        D_80B2015F = temp_t9;
                                        if (player_4 != 0) {
                                            if ((s32) player->unkA78 > 0) {
                                                if (this->player.swordState == 0) {
block_42:
                                                    this->player.actor.posRot.rot.y = (s16) this->player.actor.yawTowardsLink;
                                                    this->player.actor.shape.rot.y = (s16) this->player.actor.yawTowardsLink;
                                                    D_80B20130.unk_00 = (u16)0x8000U;
                                                    player->unk692 = (u8) (player->unk692 & 0xFFFB);
                                                    D_80B1F9F0 = 127.0f;
                                                    player->unk1CC = 3.0f;
                                                    D_80B1F9F4 = (s16) (this->player.actor.yawTowardsLink + 0x8000);
                                                    D_80B20148 = (u8)0U;
                                                    D_80B2015F = (u8)0U;
                                                    this->player.actor.flags = (u32) (this->player.actor.flags | 1);
                                                } else {
block_43:
                                                    if (D_80B20148 == 1) {
                                                        if (player_4 < 0x10) {
                                                            func_80B1DBD8(globalCtx, &D_80B20130, this);
                                                            D_80B20148 = (u8) (D_80B20148 + 1);
                                                        } else {
                                                            if (player_4 == 0x13) {
                                                                func_800F4190(&this->player.actor.projectedPos, 0x6814, player);
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                goto block_43;
                                            }
                                        } else {
                                            goto block_42;
                                        }
                                    } else {
                                        if (D_80B1F9FC != 0) {
                                            D_80B1F9FC = (s32) (D_80B1F9FC - 1);
                                            D_80B20130.unk_00 = (u16)0x10U;
                                        }

                                        temp_t0_2 = (s16) (temp_t0 >> 0x10);
                                        if (func_800354B4(globalCtx, (Actor *) this, 120.0f, (u16)0x7FFF, 0x7FFF, (?32) this->player.actor.posRot.rot.y) != 0) {
                                            if (0xC == player->unk842) {
                                                if (this->player.actor.xzDistFromLink < 90.0f) {
                                                    if (this->player.swordState == 0) {
                                                        if ((u8) D_80B20160 == 0) {
                                                            if (player->unkA78 == 0) {
                                                                if (0xC == player->unk842) {
                                                                    if (this->player.actor.xzDistFromLink <= 85.0f) {
                                                                        if (func_80033A84(globalCtx, (Actor *) this) != 0) {
                                                                            D_80B1F9F0 = 0.0f;
                                                                            D_80B20148 = (u8)1U;
                                                                            player->unk692 = (u8) (player->unk692 | 4);
                                                                            this->player.actor.flags = (u32) (this->player.actor.flags & -2);
                                                                            D_80B2015F = (u8)0x1B;
                                                                            player->unk843 = (u8)0;
                                                                            player->unk838 = 0.0f;
                                                                            this->player.invincibilityTimer = (u8)-7;
                                                                            this->player.linearVelocity = 0.0f;
                                                                            player->unk1CC = 2.0f;
                                                                            func_800A3BC0(globalCtx, (SkelAnime *) (player + 0x1B4));
                                                                            D_80B1F9FC = 0;
                                                                            D_80B20130.unk_00 = (u16)0x8000U;
                                                                        } else {
block_60:
                                                                            func_80B1DD70(this, &D_80B20130, (Actor *) this);
                                                                        }
                                                                    } else {
                                                                        goto block_60;
                                                                    }
                                                                } else {
                                                                    goto block_60;
                                                                }
                                                            } else {
                                                                goto block_60;
                                                            }
                                                        } else {
                                                            goto block_60;
                                                        }
                                                    } else {
                                                        goto block_60;
                                                    }
                                                } else {
block_62:
                                                    D_80B1F9F4 = (s16) this->player.actor.yawTowardsLink;
                                                    D_80B20130.unk_00 = (u16)0x4000U;
                                                    if ((s32) player->unk842 < 4) {
                                                        D_80B1F9F0 = 0.0f;
                                                    } else {
                                                        if ((s32) player->unk842 < 8) {
                                                            D_80B1F9F0 = 127.0f;
                                                            D_80B1F9F4 = (s16) (D_80B1F9F4 + 0x4000);
                                                        } else {
                                                            if ((s32) player->unk842 < 0xC) {
                                                                D_80B1F9F0 = 127.0f;
                                                                D_80B1F9F4 = (s16) (D_80B1F9F4 - 0x4000);
                                                            } else {
                                                                if ((s32) player->unk842 < 0x18) {
                                                                    D_80B20130.unk_00 = (u16)0x10U;
                                                                } else {
                                                                    if ((s32) player->unk842 < 0x1C) {
                                                                        func_80B1DD70(this, &D_80B20130, (Actor *) this);
                                                                    } else {
                                                                        func_80B1DD70(this, &D_80B20130, (Actor *) this);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                    if ((D_80B20130.unk_00 & 0x8010) == 0) {
                                                        if (this->player.swordState == 0) {
                                                            if (player->unk843 != 0) {
                                                                D_80B20160 = (u8)1;
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                goto block_62;
                                            }
                                        } else {
                                            D_80B1F9F4 = (s16) this->player.actor.yawTowardsLink;
                                            if (this->player.actor.xzDistFromLink <= 90.0f) {
                                                if (70.0f < this->player.actor.xzDistFromLink) {
                                                    phi_v1 = 0 - temp_t0_2;
                                                    if ((s32) temp_t0_2 >= 0) {
                                                        phi_v1 = (s32) temp_t0_2;
                                                    }
                                                    if (phi_v1 >= 0x7800) {
                                                        if (this->player.actor.unk_10C == 0) {
                                                            if ((player->unk67C << 9) >= 0) {
block_85:
                                                                func_80B1DBD8(globalCtx, &D_80B20130, this);
                                                            } else {
block_86:
                                                                if (!(this->player.actor.xzDistFromLink <= 70.0f)) {
                                                                    if (this->player.actor.xzDistFromLink <= (80.0f + 0.0f)) {
                                                                        if (player->unk843 != 0) {
block_89:
                                                                            if (this->player.swordState == 0) {
                                                                                if (func_80B1DBD8(globalCtx, &D_80B20130, this) == 0) {
                                                                                    if (this->player.swordState == 0) {
                                                                                        if ((u8) D_80B20160 == 0) {
                                                                                            func_80B1DD70(this, &D_80B20130, (Actor *) this);
                                                                                        }
                                                                                    }
                                                                                }
                                                                            } else {
block_94:
                                                                                if (this->player.actor.xzDistFromLink <= (50.0f + 0.0f)) {
                                                                                    D_80B1F9F0 = 127.0f;
                                                                                    D_80B1F9F4 = (s16) this->player.actor.yawTowardsLink;
                                                                                    if (this->player.actor.unk_10C == 0) {
                                                                                        Math_SmoothScaleMaxMinS(&D_80B1F9F4, (s16) ((s32) ((player->unkB6 + 0x7FFF) << 0x10) >> 0x10), (u16)1, (u16)0x2328, 0);
                                                                                    }
                                                                                } else {
                                                                                    if ((100.0f + 0.0f) < this->player.actor.xzDistFromLink) {
                                                                                        if (player->unk843 != 0) {
                                                                                            if ((s32) player->unk842 >= 0x18) {
                                                                                                if ((s32) player->unk842 < 0x1C) {
                                                                                                    if (280.0f <= this->player.actor.xzDistFromLink) {
block_102:
                                                                                                        D_80B1F9F0 = 127.0f;
                                                                                                        D_80B1F9F4 = (s16) this->player.actor.yawTowardsLink;
                                                                                                        if (this->player.actor.unk_10C == 0) {
                                                                                                            Math_SmoothScaleMaxMinS(&D_80B1F9F4, (s16) ((s32) ((player->unkB6 + 0x7FFF) << 0x10) >> 0x10), (u16)1, (u16)0x2328, 0);
                                                                                                        }
                                                                                                    } else {
                                                                                                        func_80B1DD70(this, &D_80B20130, (Actor *) this);
                                                                                                    }
                                                                                                } else {
                                                                                                    goto block_102;
                                                                                                }
                                                                                            } else {
                                                                                                goto block_102;
                                                                                            }
                                                                                        } else {
                                                                                            goto block_102;
                                                                                        }
                                                                                    } else {
                                                                                        phi_v1_2 = 0 - temp_t0_2;
                                                                                        if ((s32) temp_t0_2 >= 0) {
                                                                                            phi_v1_2 = (s32) temp_t0_2;
                                                                                        }
                                                                                        if (phi_v1_2 < 0x7800) {
                                                                                            phi_v0 = 0 - temp_t0_2;
                                                                                            if ((s32) temp_t0_2 >= 0) {
                                                                                                phi_v0 = (s32) temp_t0_2;
                                                                                            }
                                                                                            if (phi_v0 < 0x3000) {
block_111:
                                                                                                if (func_80B1DBD8(globalCtx, &D_80B20130, this) == 0) {
block_112:
                                                                                                    D_80B1F9F4 = (s16) this->player.actor.yawTowardsLink;
                                                                                                    D_80B1F9F0 = 127.0f;
                                                                                                    if (this->player.actor.unk_10C == 0) {
                                                                                                        Math_SmoothScaleMaxMinS(&D_80B1F9F4, (s16) ((s32) ((player->unkB6 + 0x7FFF) << 0x10) >> 0x10), (u16)1, (u16)0x2328, 0);
                                                                                                    }
                                                                                                }
                                                                                            } else {
                                                                                                goto block_112;
                                                                                            }
                                                                                        } else {
                                                                                            goto block_111;
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        } else {
                                                                            goto block_94;
                                                                        }
                                                                    } else {
                                                                        goto block_94;
                                                                    }
                                                                } else {
                                                                    goto block_89;
                                                                }
                                                            }
                                                        } else {
                                                            goto block_85;
                                                        }
                                                    } else {
                                                        goto block_86;
                                                    }
                                                } else {
                                                    goto block_86;
                                                }
                                            } else {
                                                goto block_86;
                                            }
                                        }
                                    }
                                }
                            } else {
                                goto block_38;
                            }
                        } else {
                            goto block_33;
                        }
                    } else {
                        player_5 = (u8) D_80B2015D;
                        if (player_5 != 0) {
                            if (D_80B20165 == 0xFF) {
                                if (0.0f < this->player.actor.velocity.y) {
                                    D_80B20130.unk_00 = (u16) (D_80B20130.unk_00 | 0x4000);
                                } else {
block_119:
                                    if (player_5 == 0) {
                                        if ((this->player.actor.bgCheckFlags & 1) != 0) {
                                            this->player.actor.shape.rot.y = (s16) this->player.actor.yawTowardsLink;
                                            this->player.actor.posRot.rot.y = (s16) this->player.actor.yawTowardsLink;
                                            D_80B1F9F4 = (s16) this->player.actor.yawTowardsLink;
                                            if (D_80B20165 != 0xFF) {
                                                D_80B1F9F4 = (s16) (D_80B1F9F4 + 0x8000);
                                                D_80B1F9F0 = 127.0f;
                                                D_80B1FA00 = (u8)1;
                                            }
                                            D_80B20130.unk_00 = (u16) (D_80B20130.unk_00 | 0x8000);
                                            D_80B2015D = (u8)1;
                                            this->player.invincibilityTimer = (u8)0xA;
                                        }
                                    }
                                }
                            } else {
                                goto block_119;
                            }
                        } else {
                            goto block_119;
                        }
                    }
                }
            }
            temp_a0_2 = (s32) ((sp68->unk_13A.y - D_80B1F9F4) << 0x10) >> 0x10;
            sp2C = globalCtx + 0x10000;
            sp34 = &this->player.actor.posRot;
            sp66 = (s16) temp_a0_2;
            D_80B20132 = (s8) (s32) (Math_Sins((s16) temp_a0_2) * D_80B1F9F0);
            D_80B20133 = (s8) ((s32) ((s32) (Math_Coss((s16) temp_a0_2) * D_80B1F9F0) << 0x18) >> 0x18);
            if (D_80B20165 != 0xFF) {
                if ((sp2C->unk1DE4 & 7) == 0) {
                    D_80B20165 = (u8) (D_80B20165 + 1);
                }
            }
            break;

        case 2:
            temp = D_80B20165 - 0xD;
            if (temp <= 0) {
                D_80B20165 = 0;
                Actor_Kill(&this->player.actor);
                return;
            }
            D_80B20165 = temp;
            this->player.actor.shape.unk_14 -= 0xD;
            break;

        case 3:
            this->player.swordState = 0;
            D_80B20133 = 0;
            if ((this->player.invincibilityTimer > 0) && 
                (this->player.actor.posRot.pos.y < (this->player.actor.groundY - 160.0f))) {
                this->player.unk_692 &= ~1;
                this->player.actor.flags |= 1;
                this->player.invincibilityTimer = 0;
                this->player.actor.velocity.y = 0.0f;
                this->player.actor.posRot.pos.y = D_80B20154 + 40.0f;
                this->player.actor.posRot.pos.x = (Math_Sins(player->actor.shape.rot.y) * -120.0f) + player->actor.posRot.pos.x;
                this->player.actor.posRot.pos.z = (Math_Coss(player->actor.shape.rot.y) * -120.0f) + player->actor.posRot.pos.z;
                if (800.0f < func_8002DB6C(&this->player.actor, &D_80B20150)) {
                    sp50 = Math_Rand_ZeroOne() * 20.0f;
                    sp4E = (s16)Math_Rand_CenteredFloat(4000.0f);
                    tmp16 = Math_Vec3f_Yaw(&D_80B20150, &player->actor.posRot.pos);
                    this->player.actor.posRot.rot.y = tmp16;
                    this->player.actor.shape.rot.y = tmp16;
                    sp50 += 25.0f;
                    this->player.actor.posRot.pos.x = Math_Sins((this->player.actor.posRot.rot.y + sp4E) * sp50) + D_80B20150.x;
                    this->player.actor.posRot.pos.z = Math_Coss((this->player.actor.posRot.rot.y + sp4E) * sp50) + D_80B20150.z;
                    this->player.actor.posRot.pos.y = D_80B20154;
                } else {
                    this->player.actor.posRot.pos.y = this->player.actor.groundY;
                }
                Math_Vec3f_Copy(&this->player.actor.initPosRot.pos, &this->player.actor.posRot.pos);
                globalCtx->unk_11D54(this, globalCtx);
                D_80B2015E = 1;
                D_80B1F9F0 = 0.0f;
                if (D_80B20165 != 0xFF) {
                    D_80B20162 = 0;
                    D_80B20163 = 0;
                }
            }
            break;
    }


    if (gSaveContext.unk_13F0 == 3) {
        if (player->unk843 != 0) {
            if ((s32) player->unk842 >= 0x18) {
                if ((s32) player->unk842 >= 0x1C) {
block_142:
                    D_80B1F9F0 = 0.0f;
                    D_80B20132 = (u8)0;
                    D_80B20132 = (u8)0;
                    D_80B20132 = (u16)0x10;
                }
            } else {
                goto block_142;
            }
        } else {
            goto block_142;
        }
    }
    if ((u8) D_80B2015E == 1) {
        if (this->player.actor.xzDistFromLink <= 610.0f) {
            if ((u8) D_80B1FA00 != 0) {
                D_80B20130.unk_00 = (u16) (D_80B20130.unk_00 | 0x2000);
            }
        }
    }
    temp_v1_2 = D_80B20136 ^ D_80B20130.unk_00;
    D_80B2013C = (s16) (D_80B20130.unk_00 & temp_v1_2);
    phi_v0_2 = D_80B20130.unk_00;
    phi_a2 = D_80B20130.unk_00;
    if ((D_80B20130.unk_00 & 0x10) != 0) {
        D_80B20130.unk_00 = (u16) D_80B20130.unk_00;
        if ((u8) D_80B20160 == 0) {
            if (this->player.swordState == 0) {
                phi_v0_2 = (u16)0x10U;
                phi_a2 = (u16)0x10U;
            } else {
block_151:
                temp_a2 = (D_80B20130.unk_00 ^ 0x10) & 0xFFFF;
                phi_v0_2 = temp_a2;
                phi_a2 = temp_a2;
            }
        } else {
            goto block_151;
        }
    }
    D_80B20142 = (s16) (D_80B20136 & temp_v1_2);
    D_80B20136 = (u16) (phi_v0_2 & 0x3FFF);
    D_80B20136 = phi_a2;
    PadUtils_UpdateRelXY((Input *) &D_80B20130);
    D_80B2013E = (s8) (D_80B2013E + (D_80B20132 - D_80B20138));
    D_80B2013E = (s8) (D_80B2013F + (D_80B20133 - D_80B20139));
    if (this->player.actor.colChkInfo.health == 0) {
        if (D_80B1FA04 != 0) {
            this->player.action = (u8)0x18U;
            this->player.unk_46A = (u16)1U;
            this->player.unk_448 = (Actor *) player;
            D_80B1FA04 = (u8)0;
        }
    }
    if (this->player.invincibilityTimer == 0) {
        if (this->player.actor.colChkInfo.health != 0) {
            if ((this->player.unk_498.base.acFlags & 2) != 0) {
                if ((this->player.stateFlags1 << 5) >= 0) {
                    if ((this->player.unk_4E4.base.atFlags & 2) == 0) {
                        if ((this->player.unk_564.base.atFlags & 2) == 0) {
                            if (Actor_ApplyDamage((Actor *) this) == 0) {
                                func_800F5B58();
                                this->player.actor.flags = (u32) (this->player.actor.flags & -6);
                                this->player.unk_8A1 = (u8)2U;
                                this->player.unk_8A2 = (u16) (this->player.actor.yawTowardsLink + 0x8000);
                                this->player.unk_8A4 = 6.0f;
                                this->player.unk_8A8 = 6.0f;
                                this->player.unk_8A0 = (u8) this->player.actor.colChkInfo.damage;
                                D_80B1FA04 = (u8) (D_80B1FA04 + 1);
                                D_80B2015E = (s8) (u8)2U;
                                func_80032C7C(globalCtx, (Actor *) this);
                                Item_DropCollectibleRandom(globalCtx, (Actor *) this, (Vec3f *) sp34, (u16)0xC0);
                                this->player.unk_692 = (u8) (this->player.unk_692 & 0xFFFB);
                            } else {
                                func_800F5ACC(0x38);
                                if (this->player.actor.colChkInfo.damageEffect == 1) {
                                    if (D_80B20165 == 0xFF) {
                                        func_8003426C((Actor *) this, (u16)0, (u16)0xFF, (u16)0, 0x50);
                                    } else {
                                        func_8003426C((Actor *) this, (u16)0, (u16)0xFF, (u16)0x2000, 0x50);
                                    }
                                } else {
                                    this->player.actor.flags = (u32) (this->player.actor.flags & -2);
                                    this->player.unk_8A1 = (u8)1U;
                                    this->player.unk_8A2 = (u16) (this->player.actor.yawTowardsLink + 0x8000);
                                    this->player.unk_8A8 = 6.0f;
                                    this->player.unk_8A0 = (u8) this->player.actor.colChkInfo.damage;
                                    this->player.unk_8A4 = 8.0f;
                                    func_80035650((Actor *) this, &this->player.unk_498.body, 1);
                                    temp_t9_2 = this->player.unk_692 & 0xFFFB;
                                    this->player.unk_692 = temp_t9_2;
                                    this->player.unk_692 = (u8) (temp_t9_2 | 1);
                                    D_80B2015E = (u8)3;
                                    if (D_80B20165 == 0xFF) {
                                        func_8003426C((Actor *) this, (u16)0x4000, (u16)0xFF, (u16)0, 0xC);
                                    } else {
                                        func_8003426C((Actor *) this, (u16)0x4000, (u16)0xFF, (u16)0x2000, 0xC);
                                    }
                                }
                            }
                            this->player.actor.colChkInfo.damage = (u8)0U;
                            this->player.unk_8A0 = (u8)0U;
                        }
                    }
                }
            }
        }
    }
    if (this->player.actor.dmgEffectTimer != 0) {
        if ((this->player.actor.dmgEffectParams & 0x4000) != 0) {
block_173:
            this->player.unk_692 = (u8) (this->player.unk_692 & 0xFFFB);
        } else {
            this->player.invincibilityTimer = (u8)0;
            this->player.unk_692 = (u8) (this->player.unk_692 | 4);
            this->player.stateFlags1 = (u32) (this->player.stateFlags1 & 0xFBFFFFFF);
            D_80B2013F = (u8)0;
            D_80B2013F = (u8)0;
            D_80B20130.unk_00 = (u16)0U;
            D_80B2013C = (u16)0;
            this->player.linearVelocity = 0.0f;
        }
    } else {
        goto block_173;
    }
    sp2C->unk1D40(this, globalCtx, &D_80B20130);
    if (-18.0f == this->player.linearVelocity) {
        phi_v0_3 = (s32) (((u32) Math_Rand_CenteredFloat(2.0f) + 6) & 0xFF);
        if ((s32) gSaveContext.health < 0x50) {
            phi_v0_3 = (s32) (((u32) Math_Rand_CenteredFloat(2.0f) + 3) & 0xFF);
        }
        if (80.0f < this->player.actor.xzDistFromLink) {
            this->player.linearVelocity = 1.2f;
        } else {
            if (this->player.actor.xzDistFromLink < 70.0f) {
                this->player.linearVelocity = -1.5f;
            } else {
                this->player.linearVelocity = 1.0f;
            }
        }
        if (phi_v0_3 < (s32) D_80B20162) {
            this->player.skelAnime.animPlaybackSpeed = (f32) (this->player.skelAnime.animPlaybackSpeed * 0.6f);
            func_800F4190(&this->player.actor.projectedPos, 0x83F);
            D_80B20163 = (u8)0;
            D_80B20162 = (u8)0;
        }
    }
    if (-18.0f == player->unk838) {
        if (80.0f < this->player.actor.xzDistFromLink) {
            player->unk838 = 1.2f;
        } else {
            if (this->player.actor.xzDistFromLink < 70.0f) {
                player->unk838 = -1.5f;
            } else {
                player->unk838 = 1.0f;
            }
        }
    }
    player_6 = (u8) D_80B20160;
    if (player_6 != 0) {
        if (player_6 == 1) {
            if (this->player.swordState == 0) {
                D_80B20160 = (u8)0;
            } else {
                D_80B20160 = (u8)2;
                this->player.swordState = (u8)1;
                this->player.skelAnime.animCurrentFrame = (f32) (player->unk1CC - player->unk1D0);
                this->player.skelAnime.animPlaybackSpeed = (f32) player->unk1D0;
                sp30 = &this->player.unk_4E4;
                sp38 = (bitwise f32) &this->player.unk_564;
                func_800A3BC0(globalCtx, &this->player.skelAnime);
                Collider_QuadSetAT(globalCtx, (Collider *) sp30);
                Collider_QuadSetAT(globalCtx, (bitwise Collider *) sp38);
            }
        }
    }
    player_7 = D_80B20163;
    temp_t3 = player_7 - 1;
    if (player_7 != 0) {
        D_80B20163 = temp_t3;
        if ((temp_t3 & 0xFF) == 0) {
            D_80B20160 = (u8)0;
            D_80B20162 = (u8)0;
        }
    }
    player_8 = (u8) D_80B20161;
    if (player_8 != 0) {
        if (player_8 == 1) {
            this->player.invincibilityTimer = (u8)0x14;
        }
        if ((s32) this->player.invincibilityTimer > 0) {
            D_80B20161 = (u8)2;
        } else {
            D_80B20161 = (u8)0;
        }
    }
    if (this->player.invincibilityTimer != 0) {
        this->player.unk_498.base.type = (u8)0xAU;
        this->player.unk_498.body.flags = (u8)5U;
    } else {
        this->player.unk_498.base.type = (u8)5U;
        this->player.unk_498.body.flags = (u8)1U;
    }
    if (D_80B20148 != 0) {
        Math_SmoothScaleMaxMinF(&D_80B1F9F8, 2630.0f, 1.0f, 2000.0f, 0.0f);
        this->player.actor.velocity.y = (f32) (this->player.actor.velocity.y - 0.6f);
    } else {
        if (0.0f != D_80B1F9F8) {
            this->player.actor.posRot.pos.y = (f32) (this->player.actor.posRot.pos.y + (D_80B1F9F8 * 0.01f));
            D_80B1F9F8 = 0.0f;
        }
    }
    if ((u8) D_80B2015E != 0) {
        if ((s32) this->player.invincibilityTimer < 0) {
block_214:
            D_80B1FA00 = (u8)0;
        } else {
            D_80B1FA00 = (u8)1;
        }
    } else {
        goto block_214;
    }
    player_9 = (u8) D_80B2015C;
    if (player_9 != 0) {
        D_80B2015C = (s8) (player_9 - 1);
    }
    this->player.actor.posRot2.pos.x = (bitwise f32) (bitwise s32) sp34->pos.x;
    this->player.actor.posRot2.pos.y = (bitwise f32) (bitwise s32) sp34->pos.y;
    this->player.actor.posRot2.pos.z = (bitwise f32) (bitwise s32) sp34->pos.z;
    this->player.actor.posRot2.pos.y = (f32) (this->player.actor.posRot2.pos.y + 20.0f);
    this->player.actor.shape.unk_08 = (f32) D_80B1F9F8;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Torch2/EnTorch2_Update.s")
#endif

s32 func_80B1F7A8(GlobalContext* globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *actor, Gfx **gfx) {
    return func_8008FCC8(globalCtx, limbIndex, dList, pos, rot, actor);
}

void func_80B1F7D4(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *actor, Gfx **gfx) {
    func_80090D20(globalCtx, limbIndex, dList, rot, actor);
}

void EnTorch2_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnTorch2* this = THIS;
    s32 pad2;
    s32 pad;

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];
        

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_torch2.c", 0x41A);
        func_80093C80(globalCtx);
        func_80093D84(globalCtx->state.gfxCtx);
        if (D_80B20165 == 0xFF) {
            gDPSetEnvColor(gfxCtx->polyOpa.p++, 0xFF, 0x00, 0x00, D_80B20165);
            gSPSegment(gfxCtx->polyOpa.p++, 0x0C, &D_80116280[2]);
            func_8002EBCC(&this->player.actor, globalCtx, 0);
            func_8002ED80(&this->player.actor, globalCtx, 0);
            gfxCtx->polyOpa.p = SkelAnime_DrawSV2(globalCtx, this->player.skelAnime.skeleton, this->player.skelAnime.limbDrawTbl, this->player.skelAnime.dListCount, func_80B1F7A8, func_80B1F7D4, &this->player.actor, gfxCtx->polyOpa.p);
        } else {
            gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0x00, 0x00, D_80B20165);
            gSPSegment(gfxCtx->polyXlu.p++, 0x0C, &D_80116280[0]);
            func_8002EBCC(&this->player.actor, globalCtx, 0);
            func_8002ED80(&this->player.actor, globalCtx, 0);
            gfxCtx->polyXlu.p = SkelAnime_DrawSV2(globalCtx, this->player.skelAnime.skeleton, this->player.skelAnime.limbDrawTbl, this->player.skelAnime.dListCount, func_80B1F7A8, func_80B1F7D4, &this->player.actor, gfxCtx->polyXlu.p);
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_torch2.c", 0x45A);
    }
}
