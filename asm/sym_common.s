	.section bss

.macro SYMBOL name, size
        .align 4
        .global \name
    \name:
        .space \size;
	.endm


// main.c
SYMBOL gKeyRepeatStartDelay, 4
SYMBOL gLinkTransferringData, 4

SYMBOL gMain, 1088
SYMBOL gKeyRepeatContinueDelay, 4
SYMBOL gSoftResetDisabled, 4
SYMBOL gIntrTable, 56
SYMBOL gLinkVSyncDisabled, 4
SYMBOL IntrMain_Buffer, 2048
SYMBOL gPcmDmaCounter, 4

// sprite.c
SYMBOL gSpriteOrder, 64
SYMBOL gSpriteTileAllocBitmap, 128
SYMBOL gSpriteCoordOffsetX, 4
SYMBOL gOamLimit, 4
SYMBOL gReservedSpriteTileCount, 4
SYMBOL gSpriteCopyRequestCount, 4
SYMBOL gSpriteCopyRequests, 768
SYMBOL gSpriteCoordOffsetY, 4
SYMBOL gOamMatrices, 256
SYMBOL gShouldProcessSpriteCopyRequests, 4
SYMBOL gOamMatrixAllocBitmap, 4
SYMBOL gReservedSpritePaletteCount, 4

// string_util.c
SYMBOL gUnknownStringVar, 16

// link.c
SYMBOL word_3002910, 8
SYMBOL gLinkDebugValue1, 4
SYMBOL localLinkPlayerBlock, 60
SYMBOL gLinkErrorOccurred, 4
SYMBOL gLinkDebugValue2, 4
.ifdef GERMAN
SYMBOL deUnkValue1, 4
SYMBOL deUnkValue2, 4
.endif
SYMBOL gLinkPlayerPending, 4
SYMBOL gLinkPlayers, 112
SYMBOL gBlockReceived, 4
SYMBOL gLinkHeldKeys, 4
SYMBOL gLinkTimeOutCounter, 4
SYMBOL localLinkPlayer, 28
SYMBOL gRecvCmds, 64
SYMBOL gLinkStatus, 4
SYMBOL gLinkDummyBool, 4
SYMBOL byte_3002A68, 4
SYMBOL gBlockSendBuffer, 256
SYMBOL u8_array_3002B70, 4
SYMBOL gLinkType, 4
SYMBOL u8_array_3002B78, 4
SYMBOL gBlockRecvBuffer, 1024
SYMBOL gSuppressLinkErrorMessage, 4
SYMBOL gSavedLinkPlayerCount, 4
SYMBOL gSendCmd, 16
SYMBOL gSavedMultiplayerId, 4
SYMBOL gReceivedRemoteLinkPlayers, 4
SYMBOL gLinkTestBGInfo, 16
SYMBOL gLinkCallback, 4
SYMBOL gSavedLinkPlayers, 112
SYMBOL gShouldAdvanceLinkState, 4
SYMBOL gLinkTestBlockChecksums, 8
SYMBOL gUnknown_Debug_30030E0, 4
SYMBOL gBlockRequestType, 4
SYMBOL gLastSendQueueCount, 4
SYMBOL gLink, 4032
SYMBOL gLastRecvQueueCount, 4
SYMBOL gLinkSavedIme, 4

// rtc.c
SYMBOL gLocalTime, 8

// battle
SYMBOL gBattleBuffersTransferData, 368
SYMBOL gBattle_BG3_X, 4
SYMBOL gBattle_BG1_Y, 4
SYMBOL gBattle_BG3_Y, 4
SYMBOL gBattleTextBuff1, 16
SYMBOL gUnknown_030041D0, 48
SYMBOL gBattle_WIN1H, 4
SYMBOL gUnknown_03004210, 48
SYMBOL gBattle_WIN0V, 4
SYMBOL gBattle_WIN1V, 4
SYMBOL gUnknown_03004250, 48
SYMBOL gBattle_BG2_Y, 4
SYMBOL gUnknown_03004284, 4
SYMBOL gBattle_BG2_X, 4
SYMBOL gBattleTerrain, 4
SYMBOL gBattleTextBuff2, 16
SYMBOL gBattle_BG0_Y, 4
SYMBOL gBattle_BG0_X, 4
SYMBOL gBattleTextBuff3, 16
SYMBOL gBattle_BG1_X, 4
SYMBOL gBattle_WIN0H, 4

.if DEBUG
SYMBOL gUnknown_Debug_03004360, 0x10
SYMBOL gUnknown_Debug_03004370, 0x30
SYMBOL gUnknown_Debug_030043A0, 0x4
SYMBOL gUnknown_Debug_030043A4, 0x4
SYMBOL gUnknown_Debug_030043A8, 0x8
.endif

SYMBOL gPreBattleCallback1, 4
SYMBOL gBattleMainFunc, 4
SYMBOL gBattleResults, 68
SYMBOL gLeveledUpInBattle, 4
SYMBOL gBattleBankFunc, 16
SYMBOL gHealthboxIDs, 4
SYMBOL gUnknown_03004344, 4
SYMBOL gUnknown_03004348, 4
SYMBOL gUnknown_0300434C, 4

// pokemon_1.c
SYMBOL gPlayerPartyCount, 4
SYMBOL gPlayerParty, 600
SYMBOL gEnemyPartyCount, 4
SYMBOL gEnemyParty, 600

// random.c
SYMBOL gRngValue, 4

// egg_hatch.c
SYMBOL gEggHatchData, 4

// load_save.c
SYMBOL gFlashMemoryPresent, 4

// trade.c
SYMBOL gUnknown_03004824, 4
SYMBOL gUnknown_03004828, 4

// berry_blender.c
SYMBOL gUnknown_03004830, 4
SYMBOL gInGameOpponentsNo, 4
SYMBOL gUnknown_03004840, 20
SYMBOL gBerryBlenderData, 4

// overworld.c
SYMBOL word_3004858, 4
SYMBOL gFieldCallback, 4
SYMBOL gUnknown_03004860, 4
SYMBOL gFieldLinkPlayerCount, 4

// fieldmap.c
SYMBOL gUnknown_03004870, 0xC

// field_camera.c
SYMBOL gFieldCamera, 24
SYMBOL gTotalCameraPixelOffsetY, 4
SYMBOL gTotalCameraPixelOffsetX, 4

// event_object_movement.c
SYMBOL gEventObjects, 576

#if DEBUG
SYMBOL gUnknown_Debug_03004BC0, 0x4
#endif

// field_control_avatar.c
SYMBOL gSelectedEventObject, 4

// ???
SYMBOL gPokemonItemUseCallback, 4

// start_menu.c
SYMBOL gMenuCallback, 4

#if DEBUG
SYMBOL gUnknown_Debug_03004BD0, 4
#endif

// sound.c
SYMBOL gDisableMusic, 4

#if DEBUG
SYMBOL unk_debug_common_2, 0x8
#endif

// battle_anim.c
SYMBOL gSoundAnimFramesToWait, 4
SYMBOL gBattleAnimArgs, 16
SYMBOL gAnimSpriteIndexArray, 16

// task.c
SYMBOL gTasks, 640

.if DEBUG
SYMBOL unk_debug_common_1, 0x4
SYMBOL unk_3004E94, 0x4
SYMBOL unk_3004E98, 0x8
.endif

// mori_debug_menu.c
SYMBOL gUnknown_03004DA0, 32

// scanline_effect.c
SYMBOL gScanlineEffect, 32
SYMBOL gScanlineEffectRegBuffers, 3840

// pokemon_menu.c
SYMBOL gLastFieldPokeMenuOpened, 4
SYMBOL gPostMenuFieldCallback, 4

// pokedex.c
SYMBOL gUnknown_03005CE8, 4
SYMBOL gUnknown_03005CEC, 4

// pokemon_summary_screen.o
SYMBOL gUnknown_03005CF0, 4


// item_menu.c
SYMBOL gBagPocketScrollStates, 0x14
SYMBOL gCurrentBagPocketItemSlots, 4

// contest.c
SYMBOL gContestRngValue, 4

.if DEBUG
SYMBOL unk_debug_common_0, 0x4

// watanabe_debug_menu.c
SYMBOL byte_3005E30, 0x20

.endif

// record_mixing.c
SYMBOL gUnknown_03005D2C, 4

// sound_check_menu.c
SYMBOL gUnknown_03005D30, 4
SYMBOL gSoundTestCryNum, 4

// tv.c
SYMBOL gUnknown_03005D38, 4

// mauville_man.c
SYMBOL gUnknown_03005DA0, 0x48

// contest_painting_effects.c
SYMBOL gUnknown_03005DE8, 4
SYMBOL gUnknown_03005DEC, 4
SYMBOL gUnknown_03005DF0, 4
SYMBOL gUnknown_03005DF4, 4
SYMBOL gUnknown_03005DF8, 4
SYMBOL gUnknown_03005DFC, 4
SYMBOL gUnknown_03005E00, 4
SYMBOL gUnknown_03005E04, 4
SYMBOL gUnknown_03005E08, 4
SYMBOL gUnknown_03005E0C, 4

// contest_painting.c
SYMBOL gUnknown_03005E10, 4
SYMBOL gUnknown_03005E20, 32
SYMBOL gUnknown_03005E40, 76
SYMBOL gUnknown_03005E8C, 4
SYMBOL gUnknown_03005E90, 4

// evolution_scene.c
SYMBOL gCB2_AfterEvolution, 4

.if DEBUG
SYMBOL gUnknown_Debug_03005FB8, 0x4
.endif

// pokedex_cry_screen.c
SYMBOL gUnknown_03005E98, 4

// save.c
SYMBOL gFirstSaveSector, 4
SYMBOL gPrevSaveCounter, 4
SYMBOL gLastKnownGoodSector, 4
SYMBOL gDamagedSaveSectors, 4
SYMBOL gSaveCounter, 4
SYMBOL gFastSaveSection, 4
SYMBOL gUnknown_03005EB4, 4
SYMBOL gSaveFileStatus, 4
SYMBOL gGameContinueCallback, 4

// intro.c
SYMBOL gIntroFrameCounter, 4
SYMBOL gMultibootProgramStruct, 44

// battle_anim_813F0F4.c
SYMBOL gUnknown_03005F0C, 4
SYMBOL gUnknown_03005F10, 4
SYMBOL gUnknown_03005F14, 0xC

// pokeblock_feed.c
SYMBOL gPokeblockFeedPokeSprite, 4
SYMBOL gPokeblockFeedMonSpecies, 4
SYMBOL gPokeblockMonNotFlipped, 4
SYMBOL gPokeblockFeedMonSpriteID, 4
SYMBOL gPokeblockFeedMonNature, 4
SYMBOL gUnknown_03005F34, 4
SYMBOL gPokeblockFeedUnused0, 4
SYMBOL gUnknown_03005F3C, 4
SYMBOL gUnknown_03005F40, 4
SYMBOL gPokeblockFeedPokeSpriteCopy, 68
SYMBOL gUnknown_03005F94, 4
.if DEBUG
SYMBOL gUnknown_03005FA0, 32
.else
SYMBOL gUnknown_03005FA0, 48
.endif

// m4a_2.c
SYMBOL gSoundInfo, 4016
SYMBOL gPokemonCrySongs, 104
SYMBOL gPokemonCryMusicPlayers, 128
SYMBOL gMPlayJumpTable, 144
SYMBOL gCgbChans, 256
SYMBOL gPokemonCryTracks, 320
SYMBOL gPokemonCrySong, 52
SYMBOL gMPlay_BGM, 64
SYMBOL gMPlay_SE1, 64
SYMBOL gMPlay_SE2, 64
SYMBOL gMPlayMemAccArea, 16
SYMBOL gMPlay_SE3, 64

// agb_flash.c
SYMBOL gFlashTimeoutFlag, 4
SYMBOL PollFlashStatus, 4
SYMBOL WaitForFlashWrite, 4
SYMBOL ProgramFlashSector, 4
SYMBOL gFlash, 4
SYMBOL ProgramFlashByte, 4
SYMBOL gFlashNumRemainingBytes, 4
SYMBOL EraseFlashChip, 4
SYMBOL EraseFlashSector, 4
SYMBOL gFlashMaxTime, 4

