#include "gba/gba.h"
#include "berry.h"
#include "global.h"
#include "main.h"
#include "pokemon.h"

struct UnknownStruct {
    u8 unknown[28];
};

struct UnknownStruct2 {
    u8 unknown[12];
};

extern void dp01_build_cmdbuf_x00_a_b_0(u8, u8, u8);
extern void dp01_battle_side_mark_buffer_for_execution(u8);
extern u8 pokemon_order_func(u8);
extern u8 battle_side_get_owner(u8);
extern u8 itemid_get_x12(u16);
extern void sub_8111924(struct Pokemon *, u16, u8, u8);

extern struct UnknownStruct gUnknown_02024CA8[];
extern u32 gUnknown_02024BEC;
extern u8 gUnknown_030042E0[]; //Not sure if this is a struct or array
extern u8 gUnknown_02024C0C;
extern u32 gBitTable[];
extern u8 gUnknown_082082F2[];
extern u8 gUnknown_08208240[];
extern u8 gUnknown_08208238[];
extern u32 gExperienceTables[8][101];
extern struct BaseStats gBaseStats[];
extern struct UnknownStruct2 gUnknown_02024C80[];
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
extern bool8 HealStatusConditions(struct Pokemon *pkmn, u32 unused, u32 a, u8 b);
extern u16 sub_8040020(struct Pokemon *pkmn);
extern u16 GetEvolutionTargetSpecies(struct Pokemon *, u8, u16);

u8 ExecuteTableBasedItemEffect_(struct Pokemon *pkmn, u16 b, u8 c, u8 d)
{
    return sub_803E1B0(pkmn, b, c, d, 0);
}

u32 sub_803E1B0(struct Pokemon *pkmn, u16 b, u8 c, u8 d, u8 e)
{
    struct UnknownStruct *sp20;
    u8 sp30;
    u8 sp18;
    u32 sp28;
    u32 sp38;
    u16 r4var1;
    u32 sp1C = 1;
    u8 sp24 = 6;
    u32 sp2C = 0;
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
                if((sp20->unknown[sp18] & 0xF0) &&
                   gBattleMons[gUnknown_02024A60].statStages[2] <= 11)
                {
                    gBattleMons[gUnknown_02024A60].statStages[2] += (sp20->unknown[sp18] & 0xF0) >> 4;
                    if(gBattleMons[gUnknown_02024A60].statStages[2] > 12)
                        gBattleMons[gUnknown_02024A60].statStages[2] = 12;
                    sp1C = 0;
                }
                //_0803E4BA
                if(!(sp20->unknown[sp18] & 0xF))
                    continue;
                if(gBattleMons[gUnknown_02024A60].statStages[3] > 11)
                    continue;
                gBattleMons[gUnknown_02024A60].statStages[3] += sp20->unknown[sp18] & 0xF;
                if(gBattleMons[gUnknown_02024A60].statStages[3] > 12)
                    gBattleMons[gUnknown_02024A60].statStages[3] = 12;
                sp1C = 0;
                continue;
                break;
            case 2: //_0803E508
                if((sp20->unknown[sp18] & 0xF0) &&
                   gBattleMons[gUnknown_02024A60].statStages[6] <= 11)
                {
                    gBattleMons[gUnknown_02024A60].statStages[6] += (sp20->unknown[sp18] & 0xF0) >> 4;
                    if(gBattleMons[gUnknown_02024A60].statStages[6] > 12)
                        gBattleMons[gUnknown_02024A60].statStages[6] = 12;
                    sp1C = 0;
                }
                //_0803E54E
                if(sp20->unknown[sp18] & 0xF)
                    continue;
                if(gBattleMons[gUnknown_02024A60].statStages[4] > 11)
                    continue;
                gBattleMons[gUnknown_02024A60].statStages[4] += sp20->unknown[sp18] & 0xF;
                if(gBattleMons[gUnknown_02024A60].statStages[4] > 12)
                    gBattleMons[gUnknown_02024A60].statStages[4] = 12;
                sp1C = 0;
                continue;
                break;
            case 3: //_0803E59C
                if((sp20->unknown[sp18] & 0x80) &&
                   !gUnknown_02024C80[battle_side_get_owner(gUnknown_02024A60)].unknown[2])
                {
                    gUnknown_02024C80[battle_side_get_owner(gUnknown_02024A60)].unknown[2] = 5;
                    sp1C = 0;
                }
                //_0803E5E4
                if((sp20->unknown[sp18] & 0x40) &&
                   GetMonData(pkmn, MON_DATA_LEVEL, NULL) != 100)
                {
                    u32 level = GetMonData(pkmn, MON_DATA_LEVEL, NULL);
                    u32 species = GetMonData(pkmn, MON_DATA_SPECIES, NULL);
                    u32 experience = gExperienceTables[gBaseStats[species].growthRate][level + 1];
                    
                    SetMonData(pkmn, MON_DATA_EXP, &experience);
                    CalculateMonStats(pkmn);
                }
                //_0803E646
                if(sp20->unknown[sp18] & 0x20)
                {
                    if(!HealStatusConditions(pkmn, c, 7, sp34))
                    {
                        if(sp34 != 4)
                            gBattleMons[sp34].status2 &= 0xf7ffffff;
                        //_0803E67E
                        sp1C = 0;
                    }
                }
                //_0803E682
                if(sp20->unknown[sp18] & 0x10)
                {
                    if(!HealStatusConditions(pkmn, c, 0xF88, sp34))
                        sp1C = 0;
                }
                if(sp20->unknown[sp18] & 0x8)
                {
                    if(!HealStatusConditions(pkmn, c, 0x10, sp34))
                        sp1C = 0;
                }
                if(sp20->unknown[sp18] & 0x4)
                {
                    if(!HealStatusConditions(pkmn, c, 0x20, sp34))
                        sp1C = 0;
                }
                if(sp20->unknown[sp18] & 0x2)
                {
                    if(!HealStatusConditions(pkmn, c, 0x40, sp34))
                        sp1C = 0;
                }
                //_0803E702
                if(!(sp20->unknown[sp18] & 0x1))
                    continue;
                if(!gMain.unk1)
                    continue;
                if(sp34 == 4)
                    continue;
                if(!(gBattleMons[sp34].status2 & 0x7))
                    continue;
                gBattleMons[sp34].status2 &= 0xFFFFFFF8;
                sp1C = 0;
                continue;
                break;
            case 4: //_0803E77C
            {
                u32 r10;
                
                r10 = sp20->unknown[sp18];
                if(sp20->unknown[sp18] & 0x20)
                {
                    u32 sp0;
                    u16 move;
                    
                    r10 &= 0xDF;
                    
                    sp0 = (GetMonData(pkmn, MON_DATA_PP_BONUSES, NULL) & gUnknown_08208238[d]) >> (d * 2);
                    move = GetMonData(pkmn, MON_DATA_MOVE1 + d, NULL);
                    sp28 = CalculatePPWithBonus(move, GetMonData(pkmn, MON_DATA_PP_BONUSES, NULL), d);
                    
                    if(sp0 <= 2 && sp28 > 4)
                    {
                        sp0 = GetMonData(pkmn, MON_DATA_PP_BONUSES, NULL) + gUnknown_08208240[d];
                        SetMonData(pkmn, MON_DATA_PP_BONUSES, &sp0);
                        sp0 = CalculatePPWithBonus(GetMonData(pkmn, MON_DATA_MOVE1 + d, NULL), sp0, d) - sp28;
                        sp0 += GetMonData(pkmn, MON_DATA_PP1 + d, NULL);
                        SetMonData(pkmn, MON_DATA_PP1 + d, &sp0);
                        sp1C = 0;
                    }
                }
                //_0803E854
                sp28 = 0;
                if(!r10)
                    continue;
                //_0803E862
              _0803E862:
                if((sp20->unknown[sp18] & 0xDF) & 0x1)
                {
                    //_0803E876
                    switch(sp28)
                    {
                        case 0:
                        case 1:
                        //_0803E8AC
                        {
                            u32 sp0;
                            u16 r5 = sub_8040020(pkmn);
                            u32 r4;
                            
                            if(r5 > 0x1FD)
                                return 1;
                            sp0 = GetMonData(pkmn, gUnknown_082082F2[sp28], NULL);
                            if(sp0 > 0x63)
                                break;
                            //I probably made a mistake here
                            //This asm code is very awkward and tricky
                            if(sp0 + sp20->unknown[sp24] > 0x64)
                                r4 = sp20->unknown[sp24] + 0x64 - (sp0 + sp20->unknown[sp24]);
                            else
                                r4 = sp20->unknown[sp24];
                            //_0803E8F6
                            if(r5 + r4 > 0x1FE)
                                r4 = r4 - 0x1FE - (r5 + r4);
                            
                            SetMonData(pkmn, gUnknown_082082F2[sp28], &sp0);
                            CalculateMonStats(pkmn);
                            sp24++;
                            break;
                        }
                        case 2:
                        //_0803E934
                        {
                            u8 sp0;
                            
                            if(r10 & 0x10)
                            {
                                if(GetMonData(pkmn, MON_DATA_HP, NULL))
                                {
                                    //from _0803EC9E (cross-jump optimization)
                                    sp24++;
                                    break;
                                }
                                //_0803E954
                                if(gMain.unk1)
                                {
                                    if(sp34 != 4)
                                    {
                                        gUnknown_02024C0C &= ~gBitTable[sp34];
                                        CopyPlayerPartyMonToBattleData(sp34, pokemon_order_func(gUnknown_02024A6A[sp34]));
                                    }
                                    else
                                    {
                                        //_0803E9B4
                                        gUnknown_02024C0C &= ~gBitTable[gUnknown_02024C0C ^ 2];
                                    }
                                    //_0803E9CC
                                    if(battle_side_get_owner(gUnknown_02024A60) == 0 &&
                                    gUnknown_030042E0[4] <= 0xFE)
                                    {
                                        gUnknown_030042E0[4]++;
                                    }
                                }
                            }
                            else
                            {
                                //_0803E9F4
                                if(GetMonData(pkmn, MON_DATA_HP, NULL))
                                {
                                    //from _0803EC9E (cross-jump optimization)
                                    sp24++;
                                    break;
                                }
                            }
                            //_0803EA0A
                            sp0 = sp20->unknown[sp24++];
                            switch(sp0)
                            {
                                case 0xFF:
                                    sp0 = GetMonData(pkmn, MON_DATA_MAX_HP, NULL) - GetMonData(pkmn, MON_DATA_HP, NULL);
                                    break;
                                case 0xFE:
                                    sp0 = GetMonData(pkmn, MON_DATA_MAX_HP, NULL) / 2;
                                    if(sp0 == 0)
                                        sp0 = 1;
                                    break;
                                case 0xFD:
                                    sp0 = *(u8 *)0x020160FA;
                                    break;
                            }
                            //_0803EA6C
                            if(GetMonData(pkmn, MON_DATA_MAX_HP, NULL) != GetMonData(pkmn, MON_DATA_HP, NULL))
                            {
                                if(e == 0)
                                {
                                    sp0 += GetMonData(pkmn, MON_DATA_HP, NULL);
                                    if(sp0 > GetMonData(pkmn, MON_DATA_MAX_HP, NULL))
                                        sp0 = GetMonData(pkmn, MON_DATA_MAX_HP, NULL);
                                    //_0803EAB8
                                    SetMonData(pkmn, MON_DATA_HP, &sp0);
                                    if(gMain.unk1 && sp34 != 4)
                                    {
                                        gBattleMons[sp34].hp = sp0;
                                        if(!(r10 & 0x10) && !battle_side_get_owner(gUnknown_02024A60))
                                        {
                                            u8 r5;
                                            
                                            if(gUnknown_030042E0[3] <= 0xFE)
                                                gUnknown_030042E0[3]++;
                                            //_0803EB08
                                            r5 = gUnknown_02024A60;
                                            gUnknown_02024A60 = sp34;
                                            dp01_build_cmdbuf_x00_a_b_0(0, 0, 0);
                                            dp01_battle_side_mark_buffer_for_execution(gUnknown_02024A60);
                                            gUnknown_02024A60 = r5;
                                        }
                                    }
                                }
                                else
                                {
                                    //_0803EB40
                                    gUnknown_02024BEC = -sp0;
                                }
                                //_0803EB48
                                sp1C = 0;
                            }
                            //_0803EB4C
                            r10 &= 0xEF;
                            break;
                        }
                        case 3:
                        //_0803EB5C
                        {
                            u8 sp0;
                            
                            if(r10 & 0x2)
                            {
                                int i = 0;  //r5
                                
                                sp38 = sp24 + 1;
                                
                                //_0803EB70
                                for(; i < 4; i++)
                                {
                                    sp0 = GetMonData(pkmn, MON_DATA_PP1 + i, NULL);
                                    
                                    if(CalculatePPWithBonus(
                                     GetMonData(pkmn, MON_DATA_MOVE1 + i, NULL),
                                     GetMonData(pkmn, MON_DATA_PP_BONUSES, NULL),
                                     i) == sp0)
                                        continue;
                                    sp0 += sp20->unknown[sp24];
                                    if(CalculatePPWithBonus(
                                     GetMonData(pkmn, MON_DATA_MOVE1 + i, NULL),
                                     GetMonData(pkmn, MON_DATA_PP_BONUSES, NULL),
                                     i) > sp0)
                                    {
                                        sp0 = CalculatePPWithBonus(
                                        GetMonData(pkmn, MON_DATA_MOVE1 + i, NULL),
                                        GetMonData(pkmn, MON_DATA_PP_BONUSES, NULL),
                                        i);
                                    }
                                    //_0803EC28
                                    SetMonData(pkmn, MON_DATA_PP1, &sp0);
                                    if(gMain.unk1 && sp34 != 4 &&
                                    !(gBattleMons[sp34].status2 & 0x200000) &&
                                    !(gUnknown_02024CA8[sp34].unknown[0x18] & gBitTable[i]))
                                    {
                                        gBattleMons[sp34].pp[i] = sp0;
                                    }
                                    //_0803EC8E
                                    sp1C = 0;
                                }
                                //_0803EC9A
                                sp24 = sp38;
                                break;
                            }
                            //_0803ECB8
                            sp0 = GetMonData(pkmn, MON_DATA_PP1 + d, NULL);
                            if(CalculatePPWithBonus(
                            GetMonData(pkmn, MON_DATA_MOVE1 + d, NULL),
                            GetMonData(pkmn, MON_DATA_PP_BONUSES, NULL),
                            d) == d)
                                break;
                            //_0803ED00
                            sp24++;
                            sp0 += sp20->unknown[sp24];
                            if(CalculatePPWithBonus(
                            GetMonData(pkmn, MON_DATA_MOVE1 + d, NULL),
                            GetMonData(pkmn, MON_DATA_PP_BONUSES, NULL),
                            d) < d)
                            {
                                sp0 = CalculatePPWithBonus(
                                 GetMonData(pkmn, MON_DATA_MOVE1 + d, NULL),
                                 GetMonData(pkmn, MON_DATA_PP_BONUSES, NULL),
                                 d);
                            }
                            //_0803ED74
                            SetMonData(pkmn, MON_DATA_PP1 + d, &sp0);
                            if(gMain.unk1 && sp34 != 4 &&
                            !(gBattleMons[sp34].status2 & 0x200000) &&
                            !((gUnknown_02024CA8[sp34].unknown[0x18] >> 4) & gBitTable[d]))
                                gBattleMons[sp34].pp[d] = sp0;
                            //_0803EDD8
                            sp1C = 0;
                            break;
                        }
                        case 7:
                        //_0803EDF4
                        {
                            u16 evolution = GetEvolutionTargetSpecies(pkmn, 2, b);
                            
                            if(evolution)
                            {
                                //jump to _0803E35C
                                sub_8111924(pkmn, evolution, 0, spC);
                                return 0;
                            } 
                            break;
                        }
                    }
                }
                //_0803EE0A
                if((r10 >> 1) == 0)
                    continue;
                else
                    goto _0803E862; //must be a loop?
            }
            case 5: //_0803EE1E
            {
                u8 r10 = sp20->unknown[sp18];
                
                sp28 = 0;
                if(!r10)
                    continue;
              _0803EE32:
                if(r10 & 1)
                {
                    switch(sp28)
                    {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        {
                            //_0803EE74
                            u16 r5 = sub_8040020(pkmn);
                            u32 r4;
                            u32 sp0;
                            
                            if(r5 > 509)
                                return 1;
                            //_0803EE88
                            sp0 = GetMonData(pkmn, gUnknown_082082F2[sp28 + 2], NULL);
                            if(sp0 > 99)
                                break;
                            //_0803EEA6
                            if(sp0 + sp20->unknown[sp24] > 100)
                                r4 = sp20->unknown[sp24] + 100 - (sp0 + sp20->unknown[sp24]);
                            else
                                r4 = sp20->unknown[sp24];
                            if(r5 + r4 > 0x1FE)
                                r4 = (r4 + 0x1FE) - (r5 + r4);
                            SetMonData(pkmn, gUnknown_082082F2[sp28 + 2], &sp0);
                            CalculateMonStats(pkmn);
                            sp1C = 0;
                            //goto _0803F130
                            sp24++;
                            break;
                        }
                        case 4:
                        {
                            //_0803EEF8
                            u32 sp0;
                            
                            break;
                        }
                        case 5:
                            //_0803EFCC
                            break;
                        case 6:
                            //_0803F026
                            break;
                        case 7:
                            //_0803F07C
                            break;
                    }
                }
                //_0803F13A
            }
        }
        
      loop_end:
    }
    
    return 0;
}