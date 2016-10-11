#include "gba/gba.h"
#include "berry.h"
#include "global.h"
#include "main.h"
#include "pokemon.h"

struct UnknownStruct {
    u8 unknown[28];
};

extern u8 battle_side_get_owner(u8);
extern u8 itemid_get_x12(u16);
extern void sub_8111924(struct Pokemon *, u16, u8, u8);

extern struct UnknownStruct gUnknown_02024DF8[];
extern u32 gItemEffectTable[];
extern u8 gUnknown_02024A60;
extern u8 gUnknown_02024A68;
extern u8 gUnknown_02024C0B;
extern u8 gUnknown_02024E6C;
extern u16 gUnknown_02024A6A[];
extern u8 gUnknown_02024E6C;
extern struct EnigmaBerry gEnigmaBerries[];
extern struct BattlePokemon gBattleMons[];

u32 sub_803E1B0(struct Pokemon *, u16 b, u8 c, u8 d, u8 e);

u8 ExecuteTableBasedItemEffect_(struct Pokemon *pkmn, u16 b, u8 c, u8 d)
{
    return sub_803E1B0(pkmn, b, c, d, 0);
}

u32 sub_803E1B0(struct Pokemon *pkmn, u16 b, u8 c, u8 d, u8 e)
{
    struct UnknownStruct *sp20;
    u8 sp30;
    u8 sp18;
    u32 sp1C;
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
    
    //Not sure what to do about this spot, yet
    
    
    if(r4var1 > 0xA5)
        return 1;
    if(gItemEffectTable[r4var1] == 0)
    {
        if(b != 0xAF)
            return 1;
    }
    else
    {
        //Hmm... fix later
        //_0803E318
        if(b != 0xAF)
        {
            goto label1;
        }
    }
    //_0803E31E
    
    if(gMain.unk1)
    {
        sp20 = &gUnknown_02024DF8[gUnknown_02024A60];
        goto label1;
    }
    //_0803E350
    sp20 = (struct UnknownStruct *)&gSaveBlock1.filler_2F9C[0x6DA];
    goto label1;
    
    //_0803E35C - branch from below - fix later
    /*
    sub_8111924(pkmn, )
    return 0;
    */
    
    //_0803E36C - branch from below - fix later
    /*
    return 1;
    */
    
  label1:   //_0803E372
    //str r0, [sp, 0x20] (cross-jump optimization)    
    //_0803E378
    for(sp18 = 0; sp18 < 5; sp18++)
    {
        switch(sp18)
        {
            case 0: //_0803E3A8
                //Cure some status contition, probably
                if((sp20->unknown[sp18] & 0x80) &&
                   gMain.unk1 && sp34 != 4 &&
                   (gBattleMons[sp34].status2 & 0xF0000))
                {
                    gBattleMons[sp34].status2 &= 0xFFF0FFFF;
                    sp1C = 0;
                }
                if((sp20->unknown[sp18] & 0x30) &&
                   !(gBattleMons[gUnknown_02024A60].status2 & 0x100000))
                {
                    gBattleMons[gUnknown_02024A60].status2 &= 0x100000;
                    sp1C = 0;
                }
                if(!(sp20->unknown[sp18] & 0xF))
                    continue;
                if(gBattleMons[gUnknown_02024A60].statStages[1] > 0)
                    continue;
                gBattleMons[gUnknown_02024A60].statStages[1] += sp20->unknown[sp18] & 0xF;
                if(gBattleMons[gUnknown_02024A60].statStages[1] > 12)
                    gBattleMons[gUnknown_02024A60].statStages[1] = 12;
                sp1C = 0;
                continue;
                break;
            case 1: //_0803E474
            case 2: //_0803E508
            case 3: //_0803E59C
            case 4: //_0803E77C
            case 5: //_0803EE1E
        }
        
      loop_end:
    }
    
    return 0;
}