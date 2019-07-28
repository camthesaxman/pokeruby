	.section .bss

	.align 4
    .global gUnknown_020238C8
gUnknown_020238C8:   # /* 20238C8 */
	.space 0x4;

    .align 4
    .global gDisplayedStringBattle
gDisplayedStringBattle:   # /* 20238CC */
	.space 0x12C;

    .align 4
    .global gBattleTypeFlags
gBattleTypeFlags:   # /* 20239F8 */
	.space 0x4;

    .align 4
    .global gUnknown_020239FC
gUnknown_020239FC:   # /* 20239FC */
	.space 0x4;

    .align 4
    .global gMultiPartnerParty
gMultiPartnerParty:   # /* 2023A00 */
	.space 0x4;

    .align 4
    .global gUnknown_02023A04
gUnknown_02023A04:   # /* 2023A04 */
	.space 0x10;

    .align 4
    .global gUnknown_02023A14
gUnknown_02023A14:   # /* 2023A14 */
	.space 0x4C;

.if DEBUG

    .align 4
    .global gUnknown_02023A14_4C
gUnknown_02023A14_4C:
	.space 0x4;

    .align 4
    .global gUnknown_02023A14_50
gUnknown_02023A14_50:
	.space 0x2;

    .align 4
    .global gUnknown_Debug_2023A76
    .global gUnknown_Debug_2023A76_
gUnknown_Debug_2023A76:
gUnknown_Debug_2023A76_:
	.space 0x8C;

    .align 4
    .global gUnknown_Debug_2023B02
gUnknown_Debug_2023B02:
	.space 0x60;

    .align 4
    .global gUnknown_Debug_2023B62
gUnknown_Debug_2023B62:
	.space 0x1A2;

.endif

    .align 4
    .global gBattleBufferA
gBattleBufferA:   # /* 2023A60 */
	.space 0x800;

    .align 4
    .global gBattleBufferB
gBattleBufferB:   # /* 2024260 */
	.space 0x800;

    .align 4
    .global gActiveBattler
gActiveBattler:   # /* 2024A60 */
	.space 0x4;

    .align 4
    .global gBattleExecBuffer
gBattleExecBuffer:   # /* 2024A64 */
	.space 0x4;

    .align 4
    .global gBattlersCount
gBattlersCount:   # /* 2024A68 */
	.space 0x2;

    .align 4
    .global gBattlerPartyIndexes
gBattlerPartyIndexes:   # /* 2024A6A */
	.space 0x8;

    .align 4
    .global gBanksBySide
gBanksBySide:   # /* 2024A72 */
	.space 0x4;

    .align 4
    .global gActionsByTurnOrder
gActionsByTurnOrder:   # /* 2024A76 */
	.space 0x4;

    .align 4
    .global gBanksByTurnOrder
gBanksByTurnOrder:   # /* 2024A7A */
	.space 0x4;

    .align 4
    .global gCurrentTurnActionNumber
gCurrentTurnActionNumber:   # /* 2024A7E */
	.space 0x1;

    .align 4
    .global gCurrentActionFuncId
gCurrentActionFuncId:   # /* 2024A7F */
	.space 0x1;

    .align 4
    .global gBattleMons
gBattleMons:   # /* 2024A80 */
	.space 0x160;

    .align 4
    .global gBankSpriteIds
gBankSpriteIds:   # /* 2024BE0 */
	.space 0x4;

    .align 4
    .global gCurrMovePos
gCurrMovePos:   # /* 2024BE4 */
	.space 0x1;

    .align 4
    .global gUnknown_02024BE5
gUnknown_02024BE5:   # /* 2024BE5 */
	.space 0x1;

    .align 4
    .global gCurrentMove
gCurrentMove:   # /* 2024BE6 */
	.space 0x2;

    .align 4
    .global gChosenMove
gChosenMove:   # /* 2024BE8 */
	.space 0x2;

    .align 4
    .global gRandomMove
gRandomMove:   # /* 2024BEA */
	.space 0x2;

    .align 4
    .global gBattleMoveDamage
gBattleMoveDamage:   # /* 2024BEC */
	.space 0x4;

    .align 4
    .global gHpDealt
gHpDealt:   # /* 2024BF0 */
	.space 0x4;

    .align 4
    .global gTakenDmg
gTakenDmg:   # /* 2024BF4 */
	.space 0x10;

    .align 4
    .global gLastUsedItem
gLastUsedItem:   # /* 2024C04 */
	.space 0x2;

    .align 4
    .global gLastUsedAbility
gLastUsedAbility:   # /* 2024C06 */
	.space 0x1;

    .align 4
    .global gBankAttacker
gBankAttacker:   # /* 2024C07 */
	.space 0x1;

    .align 4
    .global gBankTarget
gBankTarget:   # /* 2024C08 */
	.space 0x1;

    .align 4
    .global gBank1
gBank1:   # /* 2024C09 */
	.space 0x1;

    .align 4
    .global gEffectBank
gEffectBank:   # /* 2024C0A */
	.space 0x1;

    .align 4
    .global gStringBank
gStringBank:   # /* 2024C0B */
	.space 0x1;

    .align 4
    .global gAbsentBattlerFlags
gAbsentBattlerFlags:   # /* 2024C0C */
	.space 0x1;

    .align 4
    .global gCritMultiplier
gCritMultiplier:   # /* 2024C0D */
	.space 0x1;

    .align 4
    .global gMultiHitCounter
gMultiHitCounter:   # /* 2024C0E */
	.space 0x2;

    .align 4
    .global gBattlescriptCurrInstr
gBattlescriptCurrInstr:   # /* 2024C10 */
	.space 0x8;

    .align 4
    .global gActionForBanks
gActionForBanks:   # /* 2024C18 */
	.space 0x4;

    .align 4
    .global gSelectionBattleScripts
gSelectionBattleScripts:   # /* 2024C1C */
	.space 0x10;

    .align 4
    .global gUnknown_02024C2C
gUnknown_02024C2C:   # /* 2024C2C */
	.space 0x8;

    .align 4
    .global gLastUsedMove
gLastUsedMove:   # /* 2024C34 */
	.space 0x8;

    .align 4
    .global gLastLandedMoves
gLastLandedMoves:   # /* 2024C3C */
	.space 0x8;

    .align 4
    .global gLastHitByType
gLastHitByType:   # /* 2024C44 */
	.space 0x8;

    .align 4
    .global gUnknown_02024C4C
gUnknown_02024C4C:   # /* 2024C4C */
	.space 0x8;

    .align 4
    .global gLockedMoves
gLockedMoves:   # /* 2024C54 */
	.space 0x8;

    .align 4
    .global gLastHitBy
gLastHitBy:   # /* 2024C5C */
	.space 0x4;

    .align 4
    .global gChosenMovesByBanks
gChosenMovesByBanks:   # /* 2024C60 */
	.space 0x8;

    .align 4
    .global gMoveResultFlags
gMoveResultFlags:   # /* 2024C68 */
	.space 0x4;

    .align 4
    .global gHitMarker
gHitMarker:   # /* 2024C6C */
	.space 0x4;

    .align 4
    .global gUnknown_02024C70
gUnknown_02024C70:   # /* 2024C70 */
	.space 0x4;

    .align 4
    .global gTakenDmgBanks
gTakenDmgBanks:   # /* 2024C74 */
	.space 0x4;

    .align 4
    .global gUnknown_02024C78
gUnknown_02024C78:   # /* 2024C78 */
	.space 0x2;

    .align 4
    .global gSideAffecting
gSideAffecting:   # /* 2024C7A */
	.space 0x6;

    .align 4
    .global gSideTimers
gSideTimers:   # /* 2024C80 */
	.space 0x18;

    .align 4
    .global gStatuses3
gStatuses3:   # /* 2024C98 */
	.space 0x10;

    .align 4
    .global gDisableStructs
gDisableStructs:   # /* 2024CA8 */
	.space 0x70;

    .align 4
    .global gPauseCounterBattle
gPauseCounterBattle:   # /* 2024D18 */
	.space 0x2;

    .align 4
    .global gPaydayMoney
gPaydayMoney:   # /* 2024D1A */
	.space 0x2;

    .align 4
    .global gRandomTurnNumber
gRandomTurnNumber:   # /* 2024D1C */
	.space 0x2;

    .align 4
    .global gBattleCommunication
gBattleCommunication:   # /* 2024D1E */
	.space 0x1;

    .align 4
    .global gUnknown_02024D1F
gUnknown_02024D1F:   # /* 2024D1F */
	.space 0x7;

    .align 4
    .global gBattleOutcome
gBattleOutcome:   # /* 2024D26 */
	.space 0x2;

    .align 4
    .global gProtectStructs
gProtectStructs:   # /* 2024D28 */
	.space 0x40;

    .align 4
    .global gSpecialStatuses
gSpecialStatuses:   # /* 2024D68 */
	.space 0x50;

    .align 4
    .global gBattleWeather
gBattleWeather:   # /* 2024DB8 */
	.space 0x4;

    .align 4
    .global gWishFutureKnock
gWishFutureKnock:   # /* 2024DBC */
	.space 0x20;

    .align 4
    .global gUnknown_02024DDC
gUnknown_02024DDC:   # /* 2024DDC */
	.space 0xC;

    .align 4
    .global gUnknown_02024DE8
gUnknown_02024DE8:   # /* 2024DE8 */
	.space 0x2;

    .align 4
    .global gSentPokesToOpponent
gSentPokesToOpponent:   # /* 2024DEA */
	.space 0x2;

    .align 4
    .global gDynamicBasePower
gDynamicBasePower:   # /* 2024DEC */
	.space 0x2;

    .align 4
    .global gExpShareExp
gExpShareExp:   # /* 2024DEE */
	.space 0x2;

    .align 4
    .global gEnigmaBerries
gEnigmaBerries:   # /* 2024DF0 */
	.space 0x8;

    .align 4
    .global gUnknown_02024DF8
gUnknown_02024DF8:   # /* 2024DF8 */
	.space 0x68;

    .align 4
    .global gActionSelectionCursor
gActionSelectionCursor:   # /* 2024E60 */
	.space 0x4;

    .align 4
    .global gMoveSelectionCursor
gMoveSelectionCursor:   # /* 2024E64 */
	.space 0x4;

    .align 4
    .global gUnknown_02024E68
gUnknown_02024E68:   # /* 2024E68 */
	.space 0x4;

    .align 4
    .global gBankInMenu
gBankInMenu:   # /* 2024E6C */
	.space 0x1;

    .align 4
    .global gDoingBattleAnim
gDoingBattleAnim:   # /* 2024E6D */
	.space 0x3;

    .align 4
    .global gTransformedPersonalities
gTransformedPersonalities:   # /* 2024E70 */
	.space 0x10;

    .align 4
    .global gBattleMovePower
gBattleMovePower:   # /* 2024E80 */
	.space 0x2;

    .align 4
    .global gMoveToLearn
gMoveToLearn:   # /* 2024E82 */
	.space 0x2;

    .align 4
    .global gBattleMonForms
gBattleMonForms:   # /* 2024E84 */
	.space 0x4;

    .align 4
	.global gTileBuffer
gTileBuffer: # 2039360
	.space 0x100

    .align 4
	.global gUnknown_02039460
gUnknown_02039460: # 2039460
	.space 0x300

    .align 4
	.global gUnknown_02039760
gUnknown_02039760: # 2039760
	.space 0xC00


