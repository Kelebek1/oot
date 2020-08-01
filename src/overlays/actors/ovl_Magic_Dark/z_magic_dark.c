/*
 * File: z_magic_dark.c
 * Overlay: ovl_Magic_Dark
 * Description: Nayru's Love
 */

#include "z_magic_dark.h"

#define FLAGS 0x02000010

#define THIS ((MagicDark*)thisx)

void MagicDark_Init(Actor* thisx, GlobalContext* globalCtx);
void MagicDark_Destroy(Actor* thisx, GlobalContext* globalCtx);
void MagicDark_Update(Actor* thisx, GlobalContext* globalCtx);
void MagicDark_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Magic_Dark_InitVars = {
    ACTOR_MAGIC_DARK,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(MagicDark),
    (ActorFunc)MagicDark_Init,
    (ActorFunc)MagicDark_Destroy,
    (ActorFunc)MagicDark_Update,
    (ActorFunc)MagicDark_Draw,
};
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Magic_Dark/MagicDark_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Magic_Dark/MagicDark_Destroy.s")

void func_80B874E4(MagicDark* this, GlobalContext* globalCtx) {
    MagicDark* this2 = this;
    Player* player = PLAYER;
    s32 temp_t2;
    u8 phi_a0;
    f32 tmpf1;
    s16 nayru = gSaveContext.nayrusLoveTimer;
 
    if (globalCtx->msgCtx.msgMode == 0xD || globalCtx->msgCtx.msgMode == 0x11) {
        Actor_Kill(&this->actor);
        return;
    }
    if (nayru >= 1200) {
        player->invincibilityTimer = 0;
        gSaveContext.nayrusLoveTimer = 0;
        Actor_Kill(&this->actor);
        return;
    }
    player->invincibilityTimer = -100;
    this->actor.scale.x = this->actor.scale.z = this2->unk_15C;
    if (this->unk_14C < 20) {
        this->actor.scale.x = this->actor.scale.z = (1.6f - (this->unk_14C * 0.03f)) * this2->unk_15C;
        this->actor.scale.y = ((this2->unk_14C * 0.01f) + 0.8f) * this->unk_15C;
    } else {
        this->actor.scale.x = this->actor.scale.z = this->unk_15C;
        this->actor.scale.y = this2->unk_15C;
    }
    this->actor.scale.x *= 1.3f;
    this->actor.scale.z *= 1.3f;

    if (this2->unk_14C < 20) {
        phi_a0 = this->unk_14C * 12;
    } else {
        phi_a0 = 0xFF;
    }
    //phi_a0 = this->unk_14C < 20 ?  : 255;

    if (nayru >= 1180) {
        temp_t2 = 0x3CEB - (nayru * 0xD);
        this->unk_14E = temp_t2;
        if ((nayru & 1) != 0) {
            this->unk_14E = (temp_t2 & 0xFF) >> 1;
        }
    } else if (nayru >= 1100) {
        this->unk_14E = (nayru * 128) + 127;
    } else {
        this->unk_14E = 0xFF;
    }
    if (phi_a0 < this->unk_14E) {
        this->unk_14E = phi_a0;
    }
    this->actor.posRot.rot.y += 1000;
    this->actor.shape.rot.y = func_8005A9F4(ACTIVE_CAM) + this->actor.posRot.rot.y;
    this->unk_14C += 1;
    gSaveContext.nayrusLoveTimer = nayru + 1;
    if (nayru < 1100) {
        func_8002F974(&this->actor, NA_SE_PL_MAGIC_SOUL_NORMAL - SFX_FLAG);
    } else {
        func_8002F974(&this->actor, NA_SE_PL_MAGIC_SOUL_FLASH - SFX_FLAG);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Magic_Dark/func_80B8772C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Magic_Dark/MagicDark_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Magic_Dark/func_80B87A18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_Magic_Dark/MagicDark_Draw.s")
