#ifndef _Z_EN_HORSE_H_
#define _Z_EN_HORSE_H_

#include <ultra64.h>
#include <global.h>

struct EnHorse;

typedef void (*EnHorseActionFunc)(struct EnHorse*, GlobalContext*);
typedef void (*EnHorseFuncs1)(struct EnHorse*, GlobalContext*, CsCmdActorAction*);

typedef struct {
    f32 x;
    f32 y;
} EnHorsePadXY;

typedef struct EnHorse {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ s32 unk_14C;
    /* 0x0150 */ s32 unk_150;
    /* 0x0154 */ s32 unk_154;
    /* 0x0158 */ s32 unk_158;
    /* 0x015C */ s8 unk_15C;
    /* 0x0160 */ PSkinAwb unk_160;
    /* 0x01F0 */ s32 unk_1F0;
    /* 0x01F4 */ Vec3f unk_1F4;
    /* 0x0200 */ s16 unk_200;
    /* 0x0202 */ char unk_202[0x2];
    /* 0x0204 */ s32 unk_204;
    /* 0x0208 */ s32 unk_208;
    /* 0x020C */ s32 unk_20C;
    /* 0x0210 */ s32 unk_210;
    /* 0x0214 */ f32 unk_214;
    /* 0x0218 */ s32 unk_218;
    /* 0x021C */ Vec3f unk_21C;
    /* 0x0228 */ Vec3f unk_228;
    /* 0x0234 */ s32 unk_234;
    /* 0x0238 */ u8 unk_238;
    /* 0x0239 */ char unk_239[0x3];
    /* 0x023C */ s32 unk_23C;
    /* 0x0240 */ s32 unk_240;
    /* 0x0244 */ EnHorseActionFunc actionFunc;
    /* 0x0248 */ f32 unk_248;
    /* 0x024C */ f32 unk_24C;
    /* 0x0250 */ s16 unk_250;
    /* 0x0252 */ char unk_252[0x2];
    /* 0x0254 */ s32 unk_254;
    /* 0x0258 */ Vec3f unk_258;
    /* 0x0264 */ EnHorsePadXY pad1;
    /* 0x026C */ EnHorsePadXY pad2;
    /* 0x0274 */ f32 unk_274;
    /* 0x0278 */ ColliderCylinder collider1;
    /* 0x02C4 */ ColliderCylinder collider2;
    /* 0x0310 */ ColliderJntSph collider3;
    /* 0x0330 */ ColliderJntSphItem collider3Items[1];
    /* 0x0370 */ s32 unk_370;
    /* 0x0374 */ char unk_374[0x2];
    /* 0x0376 */ s16 unk_376;
    /* 0x0378 */ s16 unk_378;
    /* 0x037A */ u8 unk_37A;
    /* 0x037C */ s16 unk_37C;
    /* 0x0380 */ s32 unk_380;
    /* 0x0384 */ u16 unk_384;
    /* 0x0386 */ char unk_386[0x2];
    /* 0x0388 */ s32 unk_388;
    /* 0x038C */ EnIn* unk_38C; //race.rider
    /* 0x0390 */ char unk_390[0x4];
    /* 0x0394 */ u16 unk_394;
    /* 0x0398 */ f32 unk_398;
    /* 0x039C */ s32 unk_39C;
    /* 0x03A0 */ s32 unk_3A0;
    /* 0x03A4 */ s32 unk_3A4;
    /* 0x03A8 */ s32 unk_3A8;
    /* 0x03AC */ u8 unk_3AC;
    /* 0x03B0 */ Vec3f unk_3B0;
    /* 0x03BC */ s32 unk_3BC;
    /* 0x03C0 */ f32 unk_3C0;
    /* 0x03C4 */ s16 unk_3C4;
    /* 0x03C6 */ char unk_3C6[0x2];
    /* 0x03C8 */ u16 unk_3C8;
    /* 0x03CC */ Vec3f unk_3CC;
    /* 0x03D8 */ Vec3f unk_3D8;
    /* 0x03E4 */ Vec3f unk_3E4;
    /* 0x03F0 */ Vec3f unk_3F0;
} EnHorse; // size = 0x03FC

extern const ActorInit En_Horse_InitVars;

#endif
