#include "z_en_kanban.h"
#include <vt.h>

#define FLAGS 0x00000019

#define THIS ((EnKanban*)thisx)

void EnKanban_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKanban_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKanban_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKanban_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A91FA0(EnKanban* this);

extern Gfx D_0403C050[];
extern Gfx D_06000C30[];
extern Gfx D_06001630[];

const ActorInit En_Kanban_InitVars = {
    ACTOR_EN_KANBAN,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_KANBAN,
    sizeof(EnKanban),
    (ActorFunc)EnKanban_Init,
    (ActorFunc)EnKanban_Destroy,
    (ActorFunc)EnKanban_Update,
    (ActorFunc)EnKanban_Draw,
};

static ColliderCylinderInit D_80A94490 =
{
    { COLTYPE_UNK10, 0x11, 0x09, 0x39, 0x10, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x00 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
    { 20, 50, 5, { 0, 0, 0 } },
};

u16 D_80A944BC[] = {
    0x0001, 0x0002, 0x0004, 0x0008, 
    0x0010, 0x0020, 0x0040, 0x0080, 
    0x0100, 0x0200, 0x0400
};

Vec3f D_80A944D4[] = {
    {  0.0f, 44.0f, 0.0f}, 
    {  0.0f, 50.0f, 0.0f}, 
    {  0.0f, 38.0f, 0.0f}, 
    { 10.0f, 44.0f, 0.0f}, 
    {-10.0f, 44.0f, 0.0f}, 
    {-10.0f, 50.0f, 0.0f}, 
    { 10.0f, 50.0f, 0.0f}, 
    {-10.0f, 38.0f, 0.0f}, 
    { 10.0f, 38.0f, 0.0f}, 
    { -7.5f, 51.0f, 0.0f}, 
    {-12.5f, 48.0f, 0.0f}, 
    {-12.5f, 40.0f, 0.0f}, 
    { -7.5f, 37.0f, 0.0f}, 
    {  7.5f, 51.0f, 0.0f}, 
    { 12.5f, 48.0f, 0.0f}, 
    { 12.5f, 40.0f, 0.0f}, 
    {  7.5f, 37.0f, 0.0f}, 
    {  0.0f, 50.0f, 0.0f}, 
    {  0.0f, 38.0f, 0.0f}
};

Vec3f D_80A945B8[] = {
    {1500.0f, 1000.0f, 0.0f}, 
    {1500.0f,  500.0f, 0.0f}, 
    {1500.0f,  500.0f, 0.0f}, 
    { 700.0f, 1000.0f, 0.0f}, 
    { 700.0f, 1000.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 700.0f,  500.0f, 0.0f}, 
    { 200.0f,  500.0f, 0.0f}, 
    { 200.0f,  500.0f, 0.0f}
};

u8 D_80A9469C[] = {
    0x01, 0x01, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x00, 0x00, 
    0x00
};

u16 D_80A946B8[] = {
    0x03FF, 0x0027, 0x014B, 0x0147, 0x0159, 0x00D8
};

Vec3f D_80A946C4 = {
    0.0f, 0.0f, 0.0f
};

u32 D_80A946D0[] = {
    0x06000CB0, 0x06000DB8, 0x06000E78, 
    0x06000F38, 0x06000FF8, 0x060010B8, 
    0x060011C0, 0x060012C8, 0x060013D0, 
    0x06001488, 0x06001540
};

u16 D_80A946FC[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0100, 
    0x0100, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0100, 0x0100, 
    0x0100, 0x0100, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0100, 0x0100, 
    0x0100, 0x0100, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0100, 0x0100, 
    0x0100, 0x0100, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0101, 0x0101, 
    0x0140, 0x0140, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 
    0x0002, 0x0002, 0x0002, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0101, 0x0101, 
    0x0140, 0x0140, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0008, 0x0008, 0x0008, 
    0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0101, 0x0101, 
    0x0140, 0x0140, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 
    0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0101, 0x0101, 
    0x0140, 0x0140, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 
    0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0001, 0x0101, 0x0101, 
    0x0140, 0x0140, 0x0040, 0x0040, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 
    0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0102, 0x0301, 
    0x0340, 0x0108, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 
    0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0204, 0x0220, 
    0x0280, 0x0210, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 
    0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0020, 0x0020, 0x0220, 0x0220, 
    0x0280, 0x0280, 0x0080, 0x0080, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 
    0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0220, 0x0220, 
    0x0280, 0x0280, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 
    0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0220, 0x0220, 
    0x0280, 0x0280, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 
    0x0004, 0x0004, 0x0004, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0220, 0x0220, 
    0x0280, 0x0280, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0010, 0x0010, 0x0010, 
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0220, 0x0620, 
    0x0680, 0x0280, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 
    0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

f32 D_80A94EFC[] = {
    1.5707963705062866f, 0.0f, 
    1.5707963705062866f, 2.073451280593872f, 
    1.0681415796279907f, 0.0f, 
    0.0f, 0.0f, 0.0f, 
};

Vtx D_80A94F20[] = {
    VTX(0xF830, 0x0000, 0x0000, 0x0000, 0x0400, 0xFF, 0xFF, 0xFF, 0xFF), 
    VTX(0x07D0, 0x0000, 0x0000, 0x0400, 0x0400, 0xFF, 0xFF, 0xFF, 0xFF), 
    VTX(0x07D0, 0x1770, 0x0000, 0x0400, 0x0000, 0xFF, 0xFF, 0xFF, 0xFF), 
    VTX(0xF830, 0x1770, 0x0000, 0x0000, 0x0000, 0xFF, 0xFF, 0xFF, 0xFF)
};

Gfx D_80A94F60[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, 0x08000000),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 4, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x007C),
    gsDPSetCombineLERP(PRIMITIVE, 0, TEXEL0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_OVL_SURF2),
    gsSPClearGeometryMode(G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPVertex(D_80A94F20, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

void func_80A91FA0(EnKanban* this) {
    f32 sp1C;
    f32 sp18;
    f32 sp14;

    if (this->actor.floorPoly != 0) {
        sp1C = this->actor.floorPoly->norm.x * 0.00003051851f;
        sp18 = this->actor.floorPoly->norm.y * 0.00003051851f;
        sp14 = this->actor.floorPoly->norm.z * 0.00003051851f;
        this->unk_188.x = -Math_atan2f(-sp14 * sp18, 1.0f);
        this->unk_188.z = Math_atan2f(-sp1C * sp18, 1.0f);
    }
}

void EnKanban_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnKanban* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    if (this->actor.params != -0x23) {
        this->actor.unk_1F = 0;
        this->actor.flags |= 1;
        Collider_InitCylinder(globalCtx, &this->unk_1A0);
        Collider_SetCylinder(globalCtx, &this->unk_1A0, &this->actor, &D_80A94490);
        osSyncPrintf("KANBAN ARG    %x\n", this->actor.params);
        if (this->actor.params == 0x300) {
            if (gSaveContext.linkAge == 1) {
                this->actor.textId = 0x409DU;
            } else {
                this->actor.textId = 0x4090U;
            }
        } else {
            this->actor.textId = this->actor.params | 0x300;
        }
        this->unk_176 = 1;
        this->unk_156 = 0xFFFF;
        func_8002E4B4(globalCtx, &this->actor, 10.0f, 10.0f, 50.0f, 4);
        func_80A91FA0(this);
        if (gSaveContext.linkAge == 1) {
            this->actor.posRot.pos.y -= 15.0f;
        }
    }
}

void EnKanban_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnKanban* this = THIS;

    if (this->unk_154 == 0) {
        Collider_DestroyCylinder(globalCtx, &this->unk_1A0);
    }
}

void func_80A921C0(EnKanban* this, GlobalContext* globalCtx) {
    s16 tmp16;

    if (this->unk_19C == 0) {
        if (this->unk_19D == 0) {
            tmp16 = this->actor.yawTowardsLink - this->actor.shape.rot.y;
            if (ABS(tmp16) < 0x2800) {
                if (func_8002F194(&this->actor, globalCtx)) {
                    this->unk_19C = 1;
                } else {
                    func_8002F2CC(&this->actor, globalCtx, 68.0f);
                }
            }
        } else {
            this->unk_19D--;
        }
    } else if (func_8002F334(&this->actor, globalCtx) != 0) {
        this->unk_19C = 0;
        this->unk_19D = 0x14;
    }
}

#ifdef NON_MATCHING
// j loop, and the part with sp74 broken
void EnKanban_Update(Actor* thisx, GlobalContext* globalCtx) {
    u8 spFF = 0;
    EnKanban* this = THIS;
    EnKanban* actor;
    Player* player = PLAYER;
    Actor* EXPLOOOOOOSION;

    Vec3f spDC;
    Vec3f spC4;
    f32 spC0;
    Vec3f spAC;
    Vec3f spA0;
    Vec3f sp94;
    volatile f32 sp74;
    PosRot sp68;

    f32 tmpf1;
    f32 tmpf2;
    f32 tmpf3;
    f32 tmpf4;
    f32 tmpf5;
    f32 tmpf6;
    u16 tmpu16;
    u16 tmpu17;
    s16 tmp16;

    u8  tmpu8;
    s32 tmp;
    s32 tmp2;
    s32 tmp3;
    s16 i;
    u8 j;

    this->unk_150++;
    switch (this->unk_154) {
        case 0:
            if (this->unk_15A != 0) {
                this->unk_15A--;
            }
            if (this->unk_19A != 0) {
                this->unk_19A--;
            }
            if (this->unk_19A == 1) {
                this->actor.flags &= -2;
            }
            if (this->unk_156 == 0xFFFF) {
                func_80A921C0(this, globalCtx);
            }
            if ((this->unk_15A == 0) && (this->unk_1A0.base.acFlags & 2)) {
                this->unk_1A0.base.acFlags &= 0xFFFD;
                this->unk_15A = 6;

                actor = (EnKanban*)Actor_SpawnAttached(&globalCtx->actorCtx, &this->actor, globalCtx, 0x141, 
                    this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z, 
                    this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z, -0x23);
            
                if (actor != NULL) {
                    tmp = (s16)(this->actor.yawTowardsLink - this->actor.shape.rot.y);
                    if (this->unk_1A0.body.acHitItem->toucher.flags & 0x700) {
                        this->unk_194 = D_80A9469C[player->swordAnimation];
                    } else {
                        this->unk_194 = 0;
                    }

                    if (ABS(tmp) >= 0x4001) {
                        if (this->unk_194 == 4) {
                            this->unk_194 = 3;
                        } else if (this->unk_194 == 1) {
                            this->unk_194 = 5;
                        }
                    }

                    actor->unk_156 &= D_80A946B8[this->unk_194];
                    if (actor->unk_156 == 0) {
                        Actor_Kill(&actor->actor);
                        return;
                    }

                    //actor->unk_158 = 0;
                    for (actor->unk_158 = 0, j = 0; j < 11; j++) {
                        if (this->unk_156 & D_80A944BC[j]) {
                            actor->unk_158 += 1;
                        }
                    }

                    this->unk_156 &= ~D_80A946B8[this->unk_194];
                    if ((this->unk_156 & 0x3FF) == 0) {
                        this->unk_19A = 10;
                    }

                    if        ((actor->unk_156 &    1) && (actor->unk_156 & 0x80)) {
                        actor->unk_195 = 0;
                    } else if ((actor->unk_156 &    2) && (actor->unk_156 &    8)) {
                        actor->unk_195 = 1;
                    } else if ((actor->unk_156 &    4) && (actor->unk_156 & 0x10)) {
                        actor->unk_195 = 2;
                    } else if ((actor->unk_156 & 0x40) && (actor->unk_156 & 0x80)) {
                        actor->unk_195 = 3;
                    } else if ((actor->unk_156 &    1) && (actor->unk_156 & 0x20)) {
                        actor->unk_195 = 4;
                    } else if ((actor->unk_156 &    1) && (actor->unk_156 &    2)) {
                        actor->unk_195 = 5;
                    } else if ((actor->unk_156 & 0x40) && (actor->unk_156 &    8)) {
                        actor->unk_195 = 6;
                    } else if ((actor->unk_156 &    4) && (actor->unk_156 & 0x20)) {
                        actor->unk_195 = 7;
                    } else if ((actor->unk_156 & 0x10) && (actor->unk_156 & 0x80)) {
                        actor->unk_195 = 8;
                    } else if (actor->unk_156 &    1) {
                        actor->unk_195 = 9U;
                    } else if (actor->unk_156 &    2) {
                        actor->unk_195 = 10;
                    } else if (actor->unk_156 &    4) {
                        actor->unk_195 = 11;
                    } else if (actor->unk_156 & 0x20) {
                        actor->unk_195 = 12;
                    } else if (actor->unk_156 & 0x40) {
                        actor->unk_195 = 13;
                    } else if (actor->unk_156 &    8) {
                        actor->unk_195 = 14;
                    } else if (actor->unk_156 & 0x10) {
                        actor->unk_195 = 15;
                    } else if (actor->unk_156 & 0x80) {
                        actor->unk_195 = 16;
                    } else if (actor->unk_156 & 0x100) {
                        actor->unk_195 = 17;
                    } else if (actor->unk_156 & 0x200) {
                        actor->unk_195 = 18;
                    } else {
                        actor->unk_195 = 100;
                    }

                    if (actor->unk_195 == 100) {
                        actor->unk_195 = 0;
                    }

                    Matrix_RotateY((this->actor.shape.rot.y / 32768.0f) * M_PI, 0);
                    Matrix_MultVec3f(&D_80A944D4[actor->unk_195], &spDC);
                    actor->actor.posRot.pos.x += spDC.x;
                    actor->actor.posRot.pos.y += spDC.y;
                    actor->actor.posRot.pos.z += spDC.z;
                   
                    actor->unk_15C.x = -D_80A944D4[actor->unk_195].x / this->actor.scale.x;
                    actor->unk_15C.y = -D_80A944D4[actor->unk_195].y / this->actor.scale.x;
                    actor->unk_15C.z = -D_80A944D4[actor->unk_195].z / this->actor.scale.x;

                    actor->unk_17C = D_80A945B8[actor->unk_195].x;
                    actor->unk_180 = D_80A945B8[actor->unk_195].y;

                    actor->unk_154 = 1;
                    actor->actor.gravity = -1.0f;
                    
                    actor->actor.posRot.rot.y = (s32)Math_Rand_CenteredFloat(12288.0f) + this->actor.yawTowardsLink + 0x8000;
                    actor->actor.velocity.y = Math_Rand_ZeroFloat(2.0f) + 3.0f;
                    actor->actor.speedXZ = Math_Rand_ZeroFloat(2.0f) + 3.0f;
                    if (actor->unk_158 >= 4) {
                        actor->unk_176 = (s32)Math_Rand_ZeroFloat(10.0f) + 6;
                        actor->unk_178 = (s32)Math_Rand_ZeroFloat(10.0f) + 6;
                    } else {
                        actor->unk_176 = (s32)Math_Rand_ZeroFloat(7.0f) + 3;
                        actor->unk_178 = (s32)Math_Rand_ZeroFloat(7.0f) + 3;
                    }
                    actor->unk_170 = Math_Rand_CenteredFloat(6144.0f);
                    if (Math_Rand_ZeroOne() < 0.5f) {
                        actor->unk_184 = 1;
                    } else {
                        actor->unk_184 = -1;
                    }
                    actor->unk_152 = 0x64;
                    actor->actor.flags &= -2;
                    actor->actor.flags |= 0x2000000;
                    this->unk_196 = 5;
                    Audio_PlayActorSound2(&this->actor, NA_SE_IT_SWORD_STRIKE);

                }

            }
            this->actor.posRot2.pos = this->actor.posRot.pos;
            this->actor.posRot2.pos.y += 44.0f;
            Collider_CylinderUpdate(&this->actor, &this->unk_1A0);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_1A0.base);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->unk_1A0.base);
            if (this->actor.xzDistFromLink > 500.0f) {
                this->unk_156 = 0xFFFFU;
                this->actor.flags |= 1;
            }
            if (this->unk_196 != 0) {
                if (this->unk_196 >= 5) {
                    this->unk_198 += 0xFF;
                    if (this->unk_198 >= 0x100) {
                        this->unk_198 = 0xFF;
                    }
                } else {
                    this->unk_198 -= 0x41;
                    if (this->unk_198 < 0) {
                        this->unk_198 = 0;
                    }
                }
                this->unk_196--;
            }
            break;

        case 1:
        case 2:
            Actor_MoveForward(&this->actor);
            func_8002E4B4(globalCtx, &this->actor, 30.0f, 30.0f, 50.0f, 5);

            
            
            spC4.x = this->actor.posRot.pos.x;
            spC4.y = this->actor.posRot.pos.y;
            spC4.z = this->actor.posRot.pos.z;
            
            tmpu16 = this->actor.bgCheckFlags;
            spC0 = this->actor.waterY;

            this->actor.posRot.pos.z += ((this->actor.posRot.pos.y - this->actor.groundY) * -50.0f) / 100.0f;
            
            func_8002E4B4(globalCtx, &this->actor, 10.0f, 10.0f, 50.0f, 4);
            func_80A91FA0(this);
            
            this->actor.posRot.pos.z = spC4.z;
            this->actor.posRot.pos.y = spC4.y;
            this->actor.posRot.pos.x = spC4.x;
            
            this->actor.bgCheckFlags = tmpu16;
            this->actor.waterY = spC0;

            osSyncPrintf(VT_RST);
            tmpu8 = this->actor.bgCheckFlags & 1;
            if (this->unk_174 != 0) {
                this->unk_168 = (s16) (this->unk_168 + this->unk_16E);
                this->unk_16E -= 0x800;
                if ((this->unk_168 <= 0) && (tmpu8 != 0)) {
                    this->unk_168 = 0;
                    this->unk_16E = 0;
                }
            } else {
                this->unk_168 -= this->unk_16E;
                this->unk_16E = this->unk_16E - 0x800;
                if ((this->unk_168 >= 0) && (tmpu8 != 0)) {
                    this->unk_168 = 0;
                    this->unk_16E = 0;
                }
            }
            if (this->unk_16E < -0xC00) {
                this->unk_16E = -0xC00;
            }
            if (this->unk_175 != 0) {
                this->unk_16C = this->unk_16C + this->unk_172;
                this->unk_172 = this->unk_172 - 0x800;
                if ((this->unk_16C <= 0) && (tmpu8 != 0)) {
                    this->unk_16C = 0;
                    this->unk_172 = 0;
                }
            } else {
                this->unk_16C = this->unk_16C - this->unk_172;
                this->unk_172 = this->unk_172 - 0x800;
                if ((this->unk_16C >= 0) && (tmpu8 != 0)) {
                    this->unk_16C = 0;
                    this->unk_172 = 0;
                }
            }
            if (this->unk_172 < -0xC00) {
                this->unk_172 = -0xC00;
            }
            if (this->actor.bgCheckFlags & 8) {
                this->actor.speedXZ *= -0.5f;
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_WOODPLATE_BOUND);
            }
            if (this->actor.bgCheckFlags & 0x40) {
                this->unk_154 = 4;
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_BOMB_DROP_WATER);
                this->unk_178 = 0;
                this->unk_176 = this->unk_178;
                this->actor.posRot.pos.y += this->actor.waterY;
                func_8002949C(globalCtx, &this->actor.posRot, 0, 0, 0, (this->unk_158 * 0x14) + 0x12C);
                func_80029444(globalCtx, &this->actor.posRot, 0x96, 0x28A, 0);
                func_80029444(globalCtx, &this->actor.posRot, 0x12C, 0x320, 5);
                this->actor.velocity.y = 0.0f;
                this->actor.gravity = 0.0f;
                osSyncPrintf(" WAT  Y  = %f\n",   this->actor.waterY);
                osSyncPrintf(" POS  Y  = %f\n",   this->actor.posRot.pos.y);
                osSyncPrintf(" GROUND Y  = %f\n", this->actor.groundY);
                return;
            }
            if (tmpu8 != 0) {
                if (this->unk_17A <= 0) {
                    this->unk_17A++;
                    this->actor.velocity.y *= -0.3f;
                    this->actor.posRot.rot.y += (s16)Math_Rand_CenteredFloat(16384.0f);
                } else {
                    this->actor.velocity.y = 0.0f;
                }
                this->actor.speedXZ *= 0.7f;
                if (this->unk_168 == 0) {
                    if (this->unk_176 != 0) {
                        this->unk_16E = this->unk_176 * 512;
                        if (this->unk_176 != 0) {
                            this->unk_176 -= 5;
                            if (this->unk_176 <= 0) {
                                this->unk_176 = 0;
                            }
                        }
                        if (Math_Rand_ZeroOne() < 0.5f) {
                            this->unk_174 = 1;
                        } else {
                            this->unk_174 = 0;
                        }
                        spFF = 1;
                    }
                }
                if (this->unk_16C == 0) {
                    if (this->unk_178 != 0) {
                        this->unk_172 = this->unk_178 * 512;
                        spFF = 1;
                        if (this->unk_178 != 0) {
                            this->unk_178 -= 5;
                            if (this->unk_178 <= 0) {
                                this->unk_178 = 0;
                            }
                        }
                        if (Math_Rand_ZeroOne() < 0.5f) {
                            this->unk_175 = 1;
                        } else {
                            this->unk_175 = 0;
                        }
                    }
                }
                Math_SmoothScaleMaxS(&this->actor.shape.rot.x, this->unk_184 * 16384, 1, 0x2000);
            } else {
                this->actor.shape.rot.y += this->unk_170;
                this->actor.shape.rot.x += this->unk_184 * 0x7D0;
            }
            if (spFF != 0) {
                spAC = D_80A946C4;
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_WOODPLATE_BOUND);
                spA0.x = 0.0f;
                spA0.y = 0.1f;
                spA0.z = 0.0f;
                sp94.y = this->actor.groundY + 3.0f;

                tmp2 = (s16)(this->unk_158 * 0.5f) + 3;
                for (i = 0; i < tmp2; i++) {
                    sp94.x = Math_Rand_CenteredFloat((this->unk_158 * 0.5f) + 20.0f) + this->actor.posRot.pos.x;
                    sp94.z = Math_Rand_CenteredFloat((this->unk_158 * 0.5f) + 20.0f) + this->actor.posRot.pos.z;
                    func_800286CC(globalCtx, &sp94, &spAC, &spA0, 0x64, 5);
                }
            }



            if (((this->unk_152 == 0) ? 0 : --this->unk_152) == 0) {
                this->unk_154 = 3;
            }


        
        case 3:
        case 4:
            if (((EnKanban*)this->actor.attachedA)->unk_156 == 0xFFFF) {
                Actor_Kill(&this->actor);
            }
            Math_SmoothScaleMaxF(&this->actor.shape.unk_08, 100.0f, 1.0f, 5.0f);
            if (this->unk_154 == 4) {
                if ((player->actor.speedXZ > 0.0f) && (player->actor.posRot.pos.y < this->actor.posRot.pos.y) && (this->actor.xyzDistFromLinkSq < 2500.0f)) {
                    Math_SmoothScaleMaxF(&this->actor.speedXZ, player->actor.speedXZ, 1.0f, 0.2f);
                    if (this->actor.speedXZ > 1.0f) {
                        this->actor.speedXZ = 1.0f;
                    }
                    if (Math_SmoothScaleMaxMinS(&this->actor.posRot.rot.y, this->actor.yawTowardsLink + 0x8000, 1, 0x1000, 0) > 0) {
                        this->unk_170 = this->actor.speedXZ * 1000.0f;
                    } else {
                        this->unk_170 = this->actor.speedXZ * -1000.0f;
                    }
                }
                if (this->actor.bgCheckFlags & 1) {
                    this->actor.speedXZ = 0.0f;
                }
                Actor_MoveForward(&this->actor);
                if (this->actor.speedXZ != 0.0f) {
                    func_8002E4B4(globalCtx, &this->actor, 10.0f, 10.0f, 50.0f, 5);
                    if (this->actor.bgCheckFlags & 8) {
                        this->actor.speedXZ *= -0.5f;
                        if (this->unk_170 > 0) {
                            this->unk_170 = -0x7D0;
                        } else {
                            this->unk_170 = 0x7D0;
                        }
                    }
                    Math_SmoothDownscaleMaxF(&this->actor.speedXZ, 1.0f, 0.15f);
                }
                this->actor.shape.rot.y += this->unk_170;
                Math_SmoothScaleMaxS(&this->unk_170, 0, 1, 0x3A);
                Math_SmoothScaleMaxS(&this->actor.shape.rot.x, this->unk_184 * 16384, 2, 0x1000);
                Math_SmoothScaleMaxS(&this->unk_168, Math_Sins(this->unk_150 * 2500) * 500.0f, 2, 0x1000);
                Math_SmoothScaleMaxS(&this->unk_16C, Math_Coss(this->unk_150 * 3000) * 500.0f, 2, 0x1000);
                Math_SmoothDownscaleMaxF(&this->unk_188.x, 0.5f, 0.2f);
                Math_SmoothDownscaleMaxF(&this->unk_188.z, 0.5f, 0.2f);

                tmpf1 = fabsf(this->actor.speedXZ);
                if (1.0f < tmpf1) {
                    tmp3 = 0;
                } else {
                    tmp3 = (0.5f < tmpf1) ? 3 : 7;
                }
                if ((this->unk_150 & tmp3) == 0) {
                    if (this->unk_158 < 3) {
                        tmp = 0;
                    } else {
                        tmp = (this->unk_158 < 6) ? 0x64 : 0xC8;
                    }
                    func_80029444(globalCtx, &this->actor.posRot.pos, (s16)tmp, (s16)(tmp + 0x1F4), 0);
                }
            } else {
                if ((globalCtx->actorCtx.unk_02 != 0) && (this->actor.xyzDistFromLinkSq < 10000.0f)) {
                    
                    tmpf6 = (100.0f - sqrtf(this->actor.xyzDistFromLinkSq)) * 0.05f;
                    this->unk_154 = 1;
                    this->actor.gravity = -1.0f;

                    this->actor.posRot.rot.y = Math_Rand_CenteredFloat(65536.0f);

                    if (this->unk_158 >= 4) {
                        this->unk_176 = (s32)Math_Rand_ZeroFloat(10.0f) + 6;
                        this->unk_178 = (s32)Math_Rand_ZeroFloat(10.0f) + 6;
                        this->actor.velocity.y = 2.0f + tmpf6;
                        this->actor.speedXZ = Math_Rand_ZeroFloat(1.0f);
                    } else {
                        this->unk_176 = (s32)Math_Rand_ZeroFloat(7.0f) + 3;
                        this->unk_178 = (s32)Math_Rand_ZeroFloat(7.0f) + 3;
                        this->actor.velocity.y = 3.0f + tmpf6;
                        this->actor.speedXZ = Math_Rand_ZeroFloat(1.5f);
                    }
                    this->unk_170 = Math_Rand_CenteredFloat(6144.0f);
                    if (Math_Rand_ZeroOne() < 0.5f) {
                        this->unk_184 = 1;
                    } else {
                        this->unk_184 = -1;
                    }
                    this->unk_152 = 0x46;
                }
            }
            if (this->unk_176 == 0) {
                EXPLOOOOOOSION = globalCtx->actorCtx.actorList[ACTORTYPE_EXPLOSIVES].first;
                
                while (EXPLOOOOOOSION != NULL) {
                    if (EXPLOOOOOOSION->params != 1) {
                        EXPLOOOOOOSION = EXPLOOOOOOSION->next;
                        continue;
                    }
                    
                    tmpf2 = this->actor.posRot.pos.x - EXPLOOOOOOSION->posRot.pos.x;
                    tmpf3 = this->actor.posRot.pos.y - EXPLOOOOOOSION->posRot.pos.y;
                    tmpf4 = this->actor.posRot.pos.z - EXPLOOOOOOSION->posRot.pos.z;
                    tmpf5 = sqrtf(SQ(tmpf2) + SQ(tmpf3) + SQ(tmpf4));

                    if (tmpf5 < 100.0f) {
                        sp74 = (100.0f - tmpf5) * 0.05f;
                        this->unk_154 = 1;
                        this->actor.gravity = -1.0f;
                        this->actor.posRot.rot.y = (s32)(Math_atan2f(tmpf2, tmpf4) * 10430.378f);
                        if (this->unk_158 >= 4) {
                            tmpf1 = sp74;
                            this->unk_176 = (s32)Math_Rand_ZeroFloat(10.0f) + 6;
                            this->unk_178 = (s32)Math_Rand_ZeroFloat(10.0f) + 6;
                            this->actor.velocity.y = 2.5f + tmpf1;
                            this->actor.speedXZ = 3.0f + tmpf1;
                        } else {
                            tmpf1 = sp74;
                            this->unk_176 = (s32)Math_Rand_ZeroFloat(7.0f) + 3;
                            this->unk_178 = (s32)Math_Rand_ZeroFloat(7.0f) + 3;
                            this->actor.velocity.y = 5.0f + tmpf1;
                            this->actor.speedXZ = 4.0f + tmpf1;
                            
                            if (!tmpf1){};
                        }

                        this->unk_170 = Math_Rand_CenteredFloat(6144.0f);
                        if (Math_Rand_ZeroOne() < 0.5f) {
                            this->unk_184 = 1;
                        } else {
                            this->unk_184 = -1;
                        }
                        this->unk_152 = 0x46;
                    }
                    EXPLOOOOOOSION = EXPLOOOOOOSION->next;
                }
            }
            osSyncPrintf(VT_FGCOL(GREEN));
            osSyncPrintf("OCARINA_MODE %d\n", globalCtx->msgCtx.unk_E3EE);
            osSyncPrintf(VT_RST);

            switch (this->unk_19E) {
                case 0:
                    if (globalCtx->msgCtx.unk_E3EE == 1) {
                        this->unk_19E = 1;
                    }
                    break;
                case 1:
                    if ((globalCtx->msgCtx.unk_E3EE == 4) && (globalCtx->msgCtx.unk_E3F2 == 8)) {
                        this->unk_154 = 5;
                        this->unk_176 = 1;
                        Audio_PlaySoundGeneral(NA_SE_SY_TRE_BOX_APPEAR, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
                    }
                    break;
            }
            break;
        case 5:
            actor = (EnKanban*)this->actor.attachedA;
            if (actor->unk_156 == 0xFFFF) {
                Actor_Kill(&this->actor);
            }
            Matrix_RotateY((actor->actor.shape.rot.y / 32768.0f) * 3.1415927f, MTXMODE_NEW);
            Matrix_MultVec3f(&D_80A944D4[this->unk_195], &spDC);
            
            sp68.pos.x = Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.x, actor->actor.posRot.pos.x + spDC.x, 1.0f, 3.0f, 0.0f);
            sp68.pos.y = Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.y, actor->actor.posRot.pos.y + spDC.y, 1.0f, 3.0f, 0.0f);
            sp68.pos.z = Math_SmoothScaleMaxMinF(&this->actor.posRot.pos.z, actor->actor.posRot.pos.z + spDC.z, 1.0f, 3.0f, 0.0f);
            
            sp68.rot.x = Math_SmoothScaleMaxMinS(&this->actor.shape.rot.x, actor->actor.shape.rot.x, 1, 0x200, 0);
            sp68.rot.y = Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, actor->actor.shape.rot.y, 1, 0x200, 0);
            sp68.rot.z = Math_SmoothScaleMaxMinS(&this->actor.shape.rot.z, actor->actor.shape.rot.z, 1, 0x200, 0);
            
            Math_SmoothScaleMaxS(&this->unk_168, 0, 1, 0x200);
            Math_SmoothScaleMaxS(&this->unk_16C, 0, 1, 0x200);
            Math_SmoothDownscaleMaxF(&this->unk_188.x, 1.0f, 0.05f);
            Math_SmoothDownscaleMaxF(&this->unk_188.z, 1.0f, 0.05f);
            Math_SmoothDownscaleMaxF(&this->actor.shape.unk_08, 1.0f, 2.0f);
            if (0.0f == (sp68.pos.x + sp68.pos.y + sp68.pos.z)) {
                if (((((sp68.rot.x + sp68.rot.y) + sp68.rot.z) + this->unk_168) + this->unk_16C) == 0) {
                    if (0.0f == this->unk_188.x) {
                        if (0.0f == this->unk_188.z) {
                            actor->unk_156 |= this->unk_156;
                            actor->actor.flags |= 1;
                            Actor_Kill(&this->actor);
                        }
                    }
                }
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Kanban/EnKanban_Update.s")
#endif

#ifdef NON_MATCHING
// Regalloc
void EnKanban_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnKanban* this = THIS;
    
    f32 tmpf1;
    f32 tmpf2;
    f32 tmpf3;
    f32 tmpf4;
    f32 projPosZ;
    u8* sp8C = (u8*)Graph_Alloc(globalCtx->state.gfxCtx, 0x400);

    s16 i;

    u16 tmp16;
    s32 pad2;
    
    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dispRefs[4];

        Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_kanban.c", 0x67B);
        func_80093D18(globalCtx->state.gfxCtx);
        func_80093D84(globalCtx->state.gfxCtx);

        gSPDisplayList(gfxCtx->polyOpa.p++, D_06000C30);

        if (this->unk_154 != 0) {
            Matrix_Translate(this->actor.posRot.pos.x, this->actor.posRot.pos.y, this->actor.posRot.pos.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateX(this->unk_188.x, MTXMODE_APPLY);
            Matrix_RotateZ(this->unk_188.z, MTXMODE_APPLY);
            Matrix_Translate(0.0f, this->actor.shape.unk_08, 0.0f, MTXMODE_APPLY);
            Matrix_RotateY((this->actor.shape.rot.y / 32768.0f) * M_PI, MTXMODE_APPLY);
            Matrix_RotateX((this->actor.shape.rot.x / 32768.0f) * M_PI, MTXMODE_APPLY);
            tmpf1 = fabsf(Math_Sins(this->unk_168) * this->unk_180);
            tmpf2 = fabsf(Math_Sins(this->unk_16C) * this->unk_17C);
            
            if (tmpf1 < tmpf2) {
                tmpf1 = tmpf2;
            }
            
            tmpf1 *= -(f32)this->unk_184;
            Matrix_Translate(0.0f, 0.0f, tmpf1, MTXMODE_APPLY);
            Matrix_RotateX((this->unk_168 / 32768.0f) * M_PI, MTXMODE_APPLY);
            Matrix_RotateY((this->unk_16C / 32768.0f) * M_PI, MTXMODE_APPLY);
            Matrix_Translate(this->unk_15C.x, this->unk_15C.y, this->unk_15C.z - 100.0f, MTXMODE_APPLY);

            gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_kanban.c", 0x6B3), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            for (i = 0; i < 11; i++) {
                if ((D_80A944BC[i] & this->unk_156) != 0) {
                    gSPDisplayList(gfxCtx->polyOpa.p++, D_80A946D0[i]);
                }
            }
        } else {
            Matrix_Translate(0.0f, 0.0f, -100.0f, MTXMODE_APPLY);

            gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_kanban.c", 0x6BD), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            if (this->unk_156 == 0xFFFF) {
                gSPDisplayList(gfxCtx->polyOpa.p++, D_0403C050);
            } else {
                for (i = 0; i < 11; i++) {
                    if ((D_80A944BC[i] & this->unk_156) != 0) {
                        gSPDisplayList(gfxCtx->polyOpa.p++, D_80A946D0[i]);
                    }
                }
            }
            if (this->unk_198 != 0) {
                tmpf3 = (this->unk_194 == 0) ? -1200.0f : 0.0f;

                Matrix_Translate(0.0f, 4400.0f + tmpf3, 200.0f, MTXMODE_APPLY);
                Matrix_RotateZ(D_80A94EFC[this->unk_194], MTXMODE_APPLY);
                Matrix_Scale(0.0f, 10.0f, 2.0f, MTXMODE_APPLY);

                gDPPipeSync(gfxCtx->polyXlu.p++);
                gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, this->unk_198);
                gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xFF, 0x96, 0x00);
                gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_kanban.c", 0x6ED), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gfxCtx->polyXlu.p++, D_06001630);
            }
        }

        projPosZ = this->actor.projectedPos.z;
        if ((projPosZ <= 400.0f) && 
            (projPosZ > 0.0f) && 
            (this->actor.groundY > -3000.0f) && 
           ((this->unk_176 != 0) || (this->unk_178 != 0))) {

            tmp16 = gSaveContext.dayTime;
            if (tmp16 >= 0x8000) {
                tmp16 = 0xFFFF - tmp16;
            }

            tmpf1 = (tmp16 * 0.00275f) + 10.0f;
            if (projPosZ > 300.0f) {
                tmpf1 *= (400.0f - projPosZ) * 0.01f;
            }

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0x00, 0x00, 0x00, (s32)tmpf1);

            if ((this->unk_154 == 0) && (gSaveContext.linkAge == 1)) {
                tmpf1 = 0.0f;
            } else {
                tmpf1 = ((this->actor.posRot.pos.y - this->actor.groundY) * -50.0f) / 100.0f;
            }
            Matrix_Translate(this->actor.posRot.pos.x, this->actor.groundY, this->actor.posRot.pos.z + tmpf1, 0);
            Matrix_RotateX(this->unk_188.x, MTXMODE_APPLY);
            Matrix_RotateZ(this->unk_188.z, MTXMODE_APPLY);
            Matrix_Scale(this->actor.scale.x, 0.0f, this->actor.scale.z, MTXMODE_APPLY);
            if (this->unk_154 == 0) {
                Matrix_RotateX(-0.62831855f, MTXMODE_APPLY);
            }
            Matrix_RotateY((this->actor.shape.rot.y / 32768.0f) * M_PI, MTXMODE_APPLY);
            Matrix_RotateX((this->actor.shape.rot.x / 32768.0f) * M_PI, MTXMODE_APPLY);
            Matrix_RotateX((this->unk_168 / 32768.0f) * M_PI, MTXMODE_APPLY);
            Matrix_RotateY((this->unk_16C / 32768.0f) * M_PI, MTXMODE_APPLY);
            Matrix_Translate(this->unk_15C.x, this->unk_15C.y, this->unk_15C.z, MTXMODE_APPLY);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_kanban.c", 0x729), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            for (i = 0; i < 0x400; i++) {
                if ((D_80A946FC[i] & this->unk_156) != 0) {
                    (sp8C)[i] = 0xFF;
                } else {
                    (sp8C)[i] = 0;
                }
            }

            gSPSegment(gfxCtx->polyXlu.p++, 0x08, SEGMENTED_TO_VIRTUAL(sp8C));
            gSPDisplayList(gfxCtx->polyXlu.p++, D_80A94F60);
        }
        Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_en_kanban.c", 0x741);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/actors/ovl_En_Kanban/EnKanban_Draw.s")
#endif
