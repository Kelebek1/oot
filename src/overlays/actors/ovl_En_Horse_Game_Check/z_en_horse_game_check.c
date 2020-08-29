/*
 * File: z_en_horse_game_check.c
 * Overlay: ovl_En_Horse_Game_Check
 * Description: Horseback Minigames
 */

#include "overlays/actors/ovl_En_Horse/z_en_horse.h"
#include "z_en_horse_game_check.h"

#define FLAGS 0x00000010

#define THIS ((EnHorseGameCheck*)thisx)

void EnHorseGameCheck_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Draw(Actor* thisx, GlobalContext* globalCtx);


s32 func_80A67550(EnHorseGameCheck *this, GlobalContext *globalCtx);
s32 func_80A67BDC(EnHorseGameCheck *this, GlobalContext *globalCtx);
s32 func_80A67C50(EnHorseGameCheck *this, GlobalContext *globalCtx);
s32 func_80A67C88(EnHorseGameCheck *this, GlobalContext *globalCtx);

void func_80A67608(EnHorseGameCheck *this, GlobalContext *globalCtx);
void func_80A67BF8(EnHorseGameCheck *this, GlobalContext *globalCtx);
void func_80A67C68(EnHorseGameCheck *this, GlobalContext *globalCtx);
void func_80A67CD4(EnHorseGameCheck *this, GlobalContext *globalCtx);

void func_80A67764(EnHorseGameCheck *this, GlobalContext *globalCtx);
void func_80A67C08(EnHorseGameCheck *this, GlobalContext *globalCtx);
void func_80A67C78(EnHorseGameCheck *this, GlobalContext *globalCtx);
void func_80A67DFC(EnHorseGameCheck *this, GlobalContext *globalCtx);


const ActorInit En_Horse_Game_Check_InitVars = {
    ACTOR_EN_HORSE_GAME_CHECK,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnHorseGameCheck),
    (ActorFunc)EnHorseGameCheck_Init,
    (ActorFunc)EnHorseGameCheck_Destroy,
    (ActorFunc)EnHorseGameCheck_Update,
    (ActorFunc)EnHorseGameCheck_Draw,
};

Vec3f D_80A68440[] = {
    { 1700.0f, 1.0f, -540.0f },
    { 117.0f, 1.0f, 488.0f },
    { -1700.0f, 1.0f, -540.0f },
};

EnHorseGameCheckFuncs D_80A684F0[] = {
    NULL,
    func_80A67550,
    func_80A67BDC,
    func_80A67C50,
    func_80A67C88,
};

EnHorseGameCheckActionFunc D_80A68504[] = {
    NULL,
    func_80A67608,
    func_80A67BF8,
    func_80A67C68,
    func_80A67CD4,
};

EnHorseGameCheckActionFunc D_80A68518[] = {
    NULL,
    func_80A67764,
    func_80A67C08,
    func_80A67C78,
    func_80A67DFC,
};

s32 func_80A67550(EnHorseGameCheck *this, GlobalContext *globalCtx) {
    EnHorse *horse;
    s32 i;

    this->unk_14C = 1;
    this->unk_150[0] = 0;
    for (i = 0; i < 3; i++) {
        this->unk_150[i + 1] = 0;
    }

    horse = (EnHorse*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HORSE, -250.0f, 1.0f, -1650.0f, 0, 0x4000, 0, -0x7FFD);
    this->unk_16C = horse;
    if (horse == NULL) {
        LogUtils_HungupThread("../z_en_horse_game_check.c", 0x181);
    }

    this->unk_170 = 0;
    this->unk_178 = 0;
    this->unk_174 = 0;
    this->unk_17C = 0;
    this->unk_180 = 0;
    return 1;
}

void func_80A67608(EnHorseGameCheck *this, GlobalContext *globalCtx) {

}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Horse_Game_Check/func_80A67618.s")

void func_80A67764(EnHorseGameCheck *this, GlobalContext *globalCtx) {
    Player* player = PLAYER;
    s32 i;

    if ((this->unk_170 >= 0x33) && (this->unk_150.unk_00 & 2) == 0) {
        this->unk_150.unk_00 |= 2;
        func_80088B34(0);
    } else if ((this->unk_170 >= 0x51) && (player->rideActor != NULL) && ((this->unk_150.unk_00 & 1) == 0)) {
        this->unk_150.unk_00 |= 1;
        ((EnHorse*)player->rideActor)->unk_388 = 1;
    } else if ((this->unk_170 >= 0x52) && ((this->unk_150.unk_00 & 4) == 0)) {
        this->unk_16C->unk_388 = 1;
        this->unk_150.unk_00 |= 4;
        Audio_PlaySoundGeneral(NA_SE_SY_START_SHOT, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
    }

    this->unk_170++;

    for (i = 0; i < 3; i++) {
        if (player->rideActor != NULL) {
            if (Math3D_Vec3f_DistXYZ(&D_80A68440[i], &player->rideActor->posRot.pos) < 400.0f) {
                if ((i > 0) && (1 == this->unk_150[i])) {
                    this->unk_150[i].unk_04 = 1;
                } else if (i == 0) {
                    this->unk_150[i].unk_04 = 1;
                }
            }
        }

        if (Math3D_Vec3f_DistXYZ(&D_80A68440[i], &this->unk_16C->actor.posRot.pos) < 400.0f) {
            if ((i > 0) && (this->unk_150.unk_C[i] == 1)) {
                this->unk_150.unk_C[i+1] = 1;
            } else if (i == 0) {
                this->unk_150.unk_C[i+1] = 1;
            }
        }
    }

    if (this->unk_174 == 0) {
        temp_v0_4 = player->->unk440;
        if (temp_v0_4 != 0) {
            if (1 == this->unk15C) {
                if (Math3D_PointInSquare2D(D_80A68464.unk0, D_80A68464.unk4, (bitwise f32) D_80A68464.unk8, (bitwise f32) D_80A68464.unkC, temp_v0_4->unk24, temp_v0_4->unk2C) != 0) {
                    temp_t0 = this->unk_17C + 1;
                    this->unk_17C = temp_t0;
                    if (temp_t0 > 0) {
                        this->unk_174 = 1;
                        this->unk_178 = 0x37;
                        Audio_SetBGM(0x41);
                        Audio_PlaySoundGeneral(0x4835, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
                    }
                    phi_v0 = this;
                    phi_s0_2 = 0;
loop_33:
                    temp_s0_2 = phi_s0_2 + 1;
                    temp_v0_5 = phi_v0 + 4;
                    temp_v0_5->unk_150 = 0;
                    phi_v0 = temp_v0_5;
                    phi_s0_2 = temp_s0_2;
                    if (temp_s0_2 != 3) {
                        goto loop_33;
                    }
                }
            }
        }
        temp_v0_6 = this->unk_16C;
        if (temp_v0_6 != 0) {
            if (1 == this->unk168) {
                if (Math3D_PointInSquare2D(D_80A68464.unk0, D_80A68464.unk4, (bitwise f32) D_80A68464.unk8, (bitwise f32) D_80A68464.unkC, temp_v0_6->actor.posRot.pos.x, temp_v0_6->actor.posRot.pos.z) != 0) {
                    temp_t6 = this->unk_180 + 1;
                    this->unk_180 = temp_t6;
                    if (temp_t6 > 0) {
                        temp_v0_7 = this->unk_16C;
                        this->unk_174 = 2;
                        this->unk_178 = 0x46;
                        temp_v0_7->unk1F0 = temp_v0_7->unk1F0 | 0x800000;
                        Audio_SetBGM(0x41);
                        Audio_PlaySoundGeneral(0x4835, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
                    }
                    phi_v0_2 = this;
                    phi_s0_3 = 0;
loop_40:
                    temp_s0_3 = phi_s0_3 + 1;
                    temp_v0_8 = phi_v0_2 + 4;
                    temp_v0_8->unk15C = 0;
                    phi_v0_2 = temp_v0_8;
                    phi_s0_3 = temp_s0_3;
                    if (temp_s0_3 != 3) {
                        goto loop_40;
                    }
                }
            }
        }
        temp_v0_9 = player->->unk440;
        if ((temp_v0_9 == 0) || (Math3D_PointInSquare2D(D_80A68474.unk0, D_80A68474.unk4, (bitwise f32) D_80A68474.unk8, (bitwise f32) D_80A68474.unkC, temp_v0_9->unk24, temp_v0_9->unk2C) == 0)) {
            if (Math3D_PointInSquare2D(D_80A68474.unk0, D_80A68474.unk4, (bitwise f32) D_80A68474.unk8, (bitwise f32) D_80A68474.unkC, player->->unk24, player->->unk2C) != 0) {
block_44:
                Audio_SetBGM(0x41);
                this->unk_174 = 2;
                this->unk_178 = 0x14;
            }
        } else {
            goto block_44;
        }
        if (gSaveContext.timer1Value >= 0xB4) {
            if ((this->unk_150 & 2) != 0) {
                Audio_SetBGM(0x41);
                this->unk_174 = 3;
                this->unk_178 = 0x14;
            }
        }
    } else {
        temp_v0_10 = this->unk_178;
        if (temp_v0_10 > 0) {
            this->unk_178 = temp_v0_10 - 1;
        } else {
            func_80A67618(this, globalCtx);
        }
    }
}

s32 func_80A67BDC(EnHorseGameCheck *this, GlobalContext *globalCtx) {
    this->unk_14C = 2;
    this->unk_150[0] = 0;
    this->unk_150[1] = 0;
    return 1;
}

void func_80A67BF8(EnHorseGameCheck *this, GlobalContext *globalCtx) {

}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Horse_Game_Check/func_80A67C08.s")

s32 func_80A67C50(EnHorseGameCheck *this, GlobalContext *globalCtx) {
    this->unk_14C = 3;
    this->unk_150[0] = 0;
    return 1;
}

void func_80A67C68(EnHorseGameCheck *this, GlobalContext *globalCtx) {

}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Horse_Game_Check/func_80A67C78.s")

#ifdef NON_MATCHING
s32 func_80A67C88(EnHorseGameCheck *this, GlobalContext *globalCtx) {
    s32 i;

    this->unk_14C = 4;
    this->unk_150[1] = 0;
    this->unk_198 = 0;
    this->unk_19C = 0;
    for (i = 0; i < 4; i++) {
        this->unk_158[i][0] = this->unk_158[i][1] = this->unk_158[i][2] = this->unk_158[i][3] = 0;
    }

    this->unk_1A0 = 0;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Horse_Game_Check/func_80A67C88.s")
#endif

void func_80A67CD4(EnHorseGameCheck *this, GlobalContext *globalCtx) {

}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Horse_Game_Check/func_80A67CE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Horse_Game_Check/func_80A67DFC.s")

void EnHorseGameCheck_Init(Actor* thisx, GlobalContext *globalCtx) {
    EnHorseGameCheck *this = THIS;

    if ((globalCtx->sceneNum == SCENE_SPOT20) &&
        (Flags_GetEventChkInf(0x18) || (DREG(1) != 0))) {
        this->actor.params = 4;
    }

    if (D_80A684F0[this->actor.params] != NULL) {
        D_80A684F0[this->actor.params](this, globalCtx);
    }
}

void EnHorseGameCheck_Destroy(Actor* thisx, GlobalContext *globalCtx) {
    EnHorseGameCheck *this = THIS;

    if (D_80A68504[this->actor.params] != NULL) {
        D_80A68504[this->actor.params](this, globalCtx);
    }
}

void EnHorseGameCheck_Update(Actor* thisx, GlobalContext *globalCtx) {
    EnHorseGameCheck *this = THIS;

    if (D_80A68518[this->unk_14C] != NULL) {
        D_80A68518[this->unk_14C](this, globalCtx);
    }
}

void EnHorseGameCheck_Draw(Actor* thisx, GlobalContext *globalCtx) {

}
