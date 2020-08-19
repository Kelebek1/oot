#ifndef _Z_EN_FZ_H_
#define _Z_EN_FZ_H_

#include <ultra64.h>
#include <global.h>

struct EnFz;

typedef void (*EnFzActionFunc)(struct EnFz*, GlobalContext*);

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ char unk_28[0x4];
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ u8 unk_38;
    /* 0x39 */ char alignment[0x3];
} EnFzStruct1; // size = 0x3C

typedef struct EnFz {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ EnFzActionFunc actionFunc;
    /* 0x0150 */ ColliderCylinder collider1;
    /* 0x019C */ ColliderCylinder collider2;
    /* 0x01E8 */ ColliderCylinder collider3;
    /* 0x0234 */ Vec3f unk_234;
    /* 0x0240 */ s16 unk_240;
    /* 0x0242 */ s16 unk_242;
    /* 0x0244 */ s16 unk_244;
    /* 0x0246 */ u8 unk_246;
    /* 0x0247 */ u8 unk_247;
    /* 0x0248 */ u8 unk_248;
    /* 0x0249 */ u8 unk_249;
    /* 0x024C */ f32 unk_24C;
    /* 0x0250 */ f32 unk_250;
    /* 0x0254 */ f32 unk_254;
    /* 0x0258 */ u32 unk_258;
    /* 0x025C */ s16 unk_25C;
    /* 0x025E */ s16 unk_25E;
    /* 0x0260 */ u8 unk_260;
    /* 0x0261 */ u8 unk_261;
    /* 0x0262 */ u8 unk_262;
    /* 0x0263 */ u8 unk_263;
    /* 0x0264 */ Vec3f unk_264;
    /* 0x0270 */ f32 unk_270;
    /* 0x0274 */ EnFzStruct1 unk_274[40];
} EnFz; // size = 0x0BD4

extern const ActorInit En_Fz_InitVars;

#endif
