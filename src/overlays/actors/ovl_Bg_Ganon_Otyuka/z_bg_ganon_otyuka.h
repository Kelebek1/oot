#ifndef _Z_BG_GANON_OTYUKA_H_
#define _Z_BG_GANON_OTYUKA_H_

#include <ultra64.h>
#include <global.h>

struct BgGanonOtyuka;

typedef void (*BgGanonOtyukaActionFunc)(struct BgGanonOtyuka*, GlobalContext*);

typedef struct BgGanonOtyuka {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x0164 */ BgGanonOtyukaActionFunc actionFunc;
    /* 0x0168 */ char unk_168[0x2];
    /* 0x016A */ s8 unk_16A;
    /* 0x016B */ char unk_16B[0x1];
    /* 0x016C */ s8 unk_16C;
    /* 0x016D */ char unk_16D[0x1];
    /* 0x016E */ u8 unk_16E;
    /* 0x0170 */ char unk_170[0x1C];
} BgGanonOtyuka; // size = 0x018C

extern const ActorInit Bg_Ganon_Otyuka_InitVars;

#endif
