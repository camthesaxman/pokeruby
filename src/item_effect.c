#include "gba/gba.h"
#include "berry.h"
#include "global.h"
#include "main.h"
#include "pokemon.h"

extern u8 battle_side_get_owner(u8);
extern u8 itemid_get_x12(u16);

extern u32 gItemEffectTable[];
extern u8 gUnknown_02024A60;
extern u8 gUnknown_02024A68;
extern u8 gUnknown_02024C0B;
extern u8 gUnknown_02024E6C;
extern u16 gUnknown_02024A6A[];
extern u8 gUnknown_02024E6C;
extern struct EnigmaBerry gEnigmaBerries[];

u32 sub_803E1B0(struct Pokemon *, u16 b, u8 c, u8 d, u8 e);

u8 ExecuteTableBasedItemEffect_(struct Pokemon *pkmn, u16 b, u8 c, u8 d)
{
    return sub_803E1B0(pkmn, b, c, d, 0);
}

u32 sub_803E1B0(struct Pokemon *pkmn, u16 b, u8 c, u8 d, u8 e)
{
    volatile u8 sp30;
    u8 sp18;
    u16 r4var1;
    
    u8 sp34 = 4;
    u16 heldItem = GetMonData(pkmn, MON_DATA_HELD_ITEM, NULL);
    if(heldItem == 0xAF)
    {
        if(gMain.unk1)
        {
            sp30 = gEnigmaBerries[gUnknown_02024E6C].holdEffect;
        }
        else
        {
            //_0803E22C
            sp30 = gSaveBlock1.filler_2F9C[0x6EC];
        }
    }
    else
    {
        //_0803E240
        sp30 = itemid_get_x12(heldItem);
    }
    //_0803E248
    gUnknown_02024C0B = gUnknown_02024E6C;
    
    if(gMain.unk1)
    {
        gUnknown_02024A60 = gUnknown_02024E6C;
        sp18 = (battle_side_get_owner(gUnknown_02024A60) == 0) ? 0 : 1;
        r4var1 = b - 0xD;
        if(sp18 < gUnknown_02024A68)
        {
            //This might be a problem spot
            while(gUnknown_02024A6A[sp18] != c)
                sp18++;
            sp34 = sp18;
        }
    }
    else
    {
        //_0803E2E8
        gUnknown_02024A60 = 0;
        sp34 = 4;
        r4var1 = b - 0xD;
    }
    //_0803E2F4
    return 0;
}