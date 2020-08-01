#include "z_en_dh.h"

#define FLAGS 0x00000415

#define THIS ((EnDh*)thisx)

void EnDh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDh_Draw(Actor* thisx, GlobalContext* globalCtx);

extern AnimationHeader D_06003A8C;
/*
const ActorInit En_Dh_InitVars = {
    ACTOR_EN_DH,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_DH,
    sizeof(EnDh),
    (ActorFunc)EnDh_Init,
    (ActorFunc)EnDh_Destroy,
    (ActorFunc)EnDh_Update,
    (ActorFunc)EnDh_Draw,
};
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EAD40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/EnDh_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/EnDh_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EAEC4.s")

void func_809EB110(EnDh* this, GlobalContext* globalCtx);
void func_809EAD40(EnDh* this, void (*funcPtr)(EnDh*, GlobalContext*));

void func_809EB05C(EnDh *this) {
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06003A8C);
    this->unk_25B = 0;
    this->actor.posRot.pos.x = Math_Rand_CenteredFloat(600.0f) + this->actor.initPosRot.pos.x;
    this->actor.posRot.pos.z = Math_Rand_CenteredFloat(600.0f) + this->actor.initPosRot.pos.z;
    this->actor.shape.unk_08 = -15000.0f;
    this->unk_318 = this->actor.speedXZ = 0.0f;
    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    this->unk_25E = this->unk_250 = this->actor.params = 0;
    this->actor.flags |= 0x80;
    func_809EAD40(this, func_809EB110);
} 

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EB110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EB334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EB3D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EB4D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EB53C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EB5C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EB624.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EB934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EB9B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EBB48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EBBC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EBCF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EBD78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EBEA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/EnDh_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/func_809EC1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Dh/EnDh_Draw.s")
