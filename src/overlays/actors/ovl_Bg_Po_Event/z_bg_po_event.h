#ifndef _Z_BG_PO_EVENT_H_
#define _Z_BG_PO_EVENT_H_

#include <ultra64.h>
#include <global.h>

struct BgPoEvent;

typedef struct BgPoEvent {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x0164 */ void (*actionFunc)(struct BgPoEvent*, GlobalContext*);
    /* 0x0168 */ u8 unk_168;
    /* 0x0169 */ u8 unk_169;
    /* 0x016A */ char unk_16A[2];
    /* 0x016C */ union {
                    struct {
                        u8 b1;
                        u8 b2;
                    };
                    s16 word;
                 } unk_16C;
    /* 0x016D */ char unk_16E[2];
    /* 0x0170 */ ColliderTris unk_170;
    /* 0x0190 */ ColliderTrisItem unk_190[2];
} BgPoEvent; // size = 0x0248

extern const ActorInit Bg_Po_Event_InitVars;

#endif
