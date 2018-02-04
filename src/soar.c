#include "global.h"
#include "constants/songs.h"
#include "decompress.h"
#include "field_effect.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "region_map.h"
#include "scanline_effect.h"
#include "script.h"
#include "soar.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "trig.h"
#include "random.h"

#define DEBUG 1

#define NOCASH_BREAKPOINT asm("mov r11, r11")

static void CB2_LoadSoarGraphics(void);
static void DoSoarFieldEffectsCB2(void);
static void SoarVBlankCallback(void);
static void SoarHBlankCallback(void);
static void CB2_HandleInput(void);
static void PromptLandCB2(void);
static void ProcessYesNoCB2(void);
static void WarpCB2(void);
static void FadeOutVBlankCallback(void);
static void CB2_FadeOut(void);

extern const u8 sUnknown_083E7920[][3];

// For now, just use the region map graphics
extern const u16 sRegionMapBkgnd_Pal[];
extern const u8 sRegionMapBkgnd_ImageLZ[];
extern const u8 sRegionMapBkgnd_TilemapLZ[];

#if SAPPHIRE
static const u8 sEonBrendanSpriteTiles[]       = INCBIN_U8("graphics/soar/latias_brendan.4bpp.lz");
static const u8 sEonBrendanSpritePaletteData[] = INCBIN_U8("graphics/soar/latias_brendan.gbapal.lz");
static const u8 sEonMaySpriteTiles[]           = INCBIN_U8("graphics/soar/latias_may.4bpp.lz");
static const u8 sEonMaySpritePaletteData[]     = INCBIN_U8("graphics/soar/latias_may.gbapal.lz");
#else
static const u8 sEonBrendanSpriteTiles[]       = INCBIN_U8("graphics/soar/latios_brendan.4bpp.lz");
static const u8 sEonBrendanSpritePaletteData[] = INCBIN_U8("graphics/soar/latios_brendan.gbapal.lz");
static const u8 sEonMaySpriteTiles[]           = INCBIN_U8("graphics/soar/latios_may.4bpp.lz");
static const u8 sEonMaySpritePaletteData[]     = INCBIN_U8("graphics/soar/latios_may.gbapal.lz");
#endif

static const struct OamData sEonSpriteOamData =
{
    .y = 100,
    .affineMode = 3,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 1,
    .x = DISPLAY_WIDTH / 2,
    .matrixNum = 0,
    .size = 3,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sEonSpriteTemplate =
{
    .tileTag = 9999,
    .paletteTag = 9999,
    .oam = &sEonSpriteOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = NULL,
    .callback = SpriteCallbackDummy,
};

static const u8 sShadowSpriteTiles[] = INCBIN_U8("graphics/soar/shadow.4bpp.lz");
static const struct CompressedSpriteSheet sShadowSpriteSheet = {sShadowSpriteTiles, 1024, 9999};

static const struct OamData sShadowSpriteOamData =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 2,
    .mosaic = 0,
    .bpp = 0,
    .shape = 1,
    .x = 0,
    .matrixNum = 0,
    .size = 3,
    .tileNum = 16,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sShadowSpriteTemplate =
{
    .tileTag = 9998,
    .paletteTag = 9998,
    .oam = &sShadowSpriteOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = NULL,
    .callback = SpriteCallbackDummy,
};

static const struct {u8 left; u8 top; u8 right; u8 bottom;} sPopupWindowRect = {0, 0, 15, 3};

static s32 sPlayerPosX;
static s32 sPlayerPosY;
static s32 sPlayerPosZ;
static u8 sPlayerYaw;
static u8 sPlayerPitch;
static u16 sPrevMapSection;

static u8 sEonSpriteId;
static u8 sShadowSpriteId;

#define Q_8_8(iPart, fPart) (((iPart) << 8) | (fPart))

static const u8 sEonFluteUseMessage[] = _("{PLAYER} used the EON FLUTE.{PAUSE_UNTIL_PRESS}");

void CB2_InitSoar(void)
{
    switch (gMain.state)
    {
    case 0:
        // Can't get this to work
        //gFieldEffectArguments[0] = 0;
        //FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
        gMain.state++;
        break;
    case 1:
        Menu_DisplayDialogueFrame();
        MenuPrintMessageDefaultCoords(sEonFluteUseMessage);
        gMain.state++;
        break;
    case 2:
        if (Menu_UpdateWindowText())
        {
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
            gMain.state++;
        }
        break;
    case 3:
        if (!UpdatePaletteFade())
        {
            u16 cursorX, cursorY;
            bool8 inCave;

            RegionMap_GetSectionCoordsFromCurrFieldPos(&sPrevMapSection, &cursorX, &cursorY, &inCave);

            sPlayerPosX = Q_8_8(cursorX * 8, 0);
            sPlayerPosY = Q_8_8(cursorY * 8, 0);
            sPlayerPosZ = Q_8_8(4, 0);
            sPlayerYaw = 0;
            sPlayerPitch = 0;

            // some of these may not be necessary, but I'm just being safe
            ScanlineEffect_Stop();
            ResetTasks();
            ResetSpriteData();
            ResetPaletteFade();
            FreeAllSpritePalettes();

            gMain.state = 0;
            SetMainCallback2(CB2_LoadSoarGraphics);
        }
        break;
    }
    /*
    RunTasks();
    AnimateSprites();
    CameraUpdate();
    UpdateCameraPanning();
    BuildOamBuffer();
    UpdatePaletteFade();
    */
}

void ItemUseOnFieldCB_EonFlute(u8 taskId)
{
    ScriptContext2_Enable();
    FreezeMapObjects();
    SetMainCallback2(CB2_InitSoar);
}

static void LoadEonGraphics(void)
{
    struct CompressedSpriteSheet sEonSpriteSheet = {.size = 1024, .tag = 9999};
    struct CompressedSpritePalette sEonSpritePalette = {.tag = 9999};

    if (gSaveBlock2.playerGender == MALE)
    {
        sEonSpriteSheet.data = sEonBrendanSpriteTiles;
        sEonSpritePalette.data = sEonBrendanSpritePaletteData;
    }
    else
    {
        sEonSpriteSheet.data = sEonMaySpriteTiles;
        sEonSpritePalette.data = sEonMaySpritePaletteData;
    }

    LoadCompressedObjectPic(&sEonSpriteSheet);
    LoadCompressedObjectPalette(&sEonSpritePalette);
    sEonSpriteId = CreateSprite(&sEonSpriteTemplate, DISPLAY_WIDTH / 2, 100, 0);
    gSprites[sEonSpriteId].data[0] = 0;
    gSprites[sEonSpriteId].data[1] = 0;
    gSprites[sEonSpriteId].data[2] = 0;
}

static void CB2_LoadSoarGraphics(void)
{
    //const struct WindowTemplate *winTemplate = &gWindowTemplate_81E7224;

    switch (gMain.state)
    {
    case 0:
        // continue fade out
        //if (!UpdatePaletteFade())
            gMain.state++;
        break;
    case 1:
        SetVBlankCallback(SoarVBlankCallback);
        SetHBlankCallback(SoarHBlankCallback);
        // Load graphics
        REG_DISPCNT = 0;
        DmaClearLarge32(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        LZ77UnCompVram(sRegionMapBkgnd_ImageLZ, (void *)(VRAM + 2 * 0x4000));
        LZ77UnCompVram(sRegionMapBkgnd_TilemapLZ, (void *)(VRAM + 2 * 0x800));
        LoadPalette(sRegionMapBkgnd_Pal, 0x70, 64);

        LoadEonGraphics();

        gPlttBufferUnfaded[0] = RGB(8, 8, 20);

        //LZ77UnCompVram(sEonSpriteTiles, (void *)(VRAM + 0x10000));
        //LZ77UnCompVram(sShadowSpriteTiles, (void *)(VRAM + 0x10000 + 0x400));
        // Set up video regs
        REG_DISPCNT = DISPCNT_MODE_1 | DISPCNT_BG2_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP;
        //REG_BG0CNT = BGCNT_PRIORITY(0)
        //           | BGCNT_16COLOR
        //           | BGCNT_CHARBASE(2);
        REG_BG2CNT = BGCNT_PRIORITY(0)
                   | BGCNT_256COLOR
                   | BGCNT_CHARBASE(2)
                   | BGCNT_SCREENBASE(2)
                   | BGCNT_AFF512x512
                   | BGCNT_WRAP;
        gMain.state++;
        break;
    case 2:
        Text_LoadWindowTemplate(&gWindowTemplate_81E7224);
        InitMenuWindow(&gWindowTemplate_81E7224);
        Menu_DrawStdWindowFrame(sPopupWindowRect.left, sPopupWindowRect.top, sPopupWindowRect.right, sPopupWindowRect.bottom);
        gMain.state++;
        break;
    case 3:
        //break;
        // continue fade in
        //if (!UpdatePaletteFade())
        //DmaClear32(3, (void *)(VRAM + 0x6000), 0x2000);

        REG_IME = 0;
        REG_IE |= INTR_FLAG_VBLANK | INTR_FLAG_HBLANK;
        REG_IME = 1;
        REG_DISPSTAT |= DISPSTAT_VBLANK_INTR | DISPSTAT_HBLANK_INTR;

        LoadCompressedObjectPic(&sShadowSpriteSheet);
        sShadowSpriteId = CreateSprite(&sShadowSpriteTemplate, DISPLAY_WIDTH / 2, 3 * DISPLAY_HEIGHT / 4, 0);

        // HACK! Please use the right palette
        //gSprites[sEonSpriteId].oam.paletteNum = 0;
        //((u16 *)PLTT)[0x100 + 1] = RGB(4, 4, 16);

        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0);
        gMain.state++;
        break;
    case 4:
        if (!UpdatePaletteFade())
            SetMainCallback2(CB2_HandleInput);
        break;
    }
    BuildOamBuffer();
}

static void SoarVBlankCallback(void)
{
    LoadOam();
    //ProcessSpriteCopyRequests();
    UpdatePaletteFade();

    REG_BG2X = 0;
    REG_BG2Y = 0;
    REG_BG2PA = 0;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 0;

    // Turn off BG for first scanline
    REG_DISPCNT &= ~DISPCNT_BG2_ON;

    TransferPlttBuffer();
}

#define M7_D 128
#define bldcntShadow BLDCNT_EFFECT_DARKEN | BLDCNT_TGT1_BG2
#define bldcntFog BLDCNT_EFFECT_LIGHTEN | BLDCNT_TGT1_BD | BLDCNT_TGT1_BG2

static void SoarHBlankCallback(void)
{
    s16 sinYaw = gSineTable[sPlayerYaw];
    s16 cosYaw = gSineTable[sPlayerYaw + 64];

    s32 lam, lcf, lsf, lxr, lyr;
    s32 currScanline = REG_VCOUNT - 1;

    if (currScanline > 159)  // We're in vblank. Nothing to do.
        return;
    if (currScanline < 32)  // draw gradient for sky
    {
        REG_DISPCNT &= ~DISPCNT_BG2_ON;
        REG_BLDCNT = bldcntFog;
        REG_BLDY = currScanline >> 1;
        return;
    }

    if (currScanline == 32)
        REG_DISPCNT |= DISPCNT_BG2_ON;

    if (currScanline <= 96)
    {
        REG_BLDCNT = bldcntFog;
        REG_BLDY = 16 - (currScanline / 6);
    }
    else
    {
        // TODO: get shadows working
        /*
        REG_WININ |= 1 << 5;
        REG_DISPCNT |= DISPCNT_OBJWIN_ON;
        REG_BLDCNT = bldcntShadow;
        REG_BLDY = 8;
        */
        REG_BLDCNT = 0;
    }

    lam= sPlayerPosZ * ((1 << 16) / (currScanline - 32))>>12;  // .8*.16 /.12 = 20.12
    lcf= lam*cosYaw>>8;                     // .12*.8 /.8 = .12
    lsf= lam*sinYaw>>8;                     // .12*.8 /.8 = .12

    REG_BG2PA= lcf>>4;
    REG_BG2PC= lsf>>4;

    // Offsets
    // Note that the lxr shifts down first!

    // horizontal offset
    lxr= 120 * (lsf>>4);
    lyr= lsf<<3;
    REG_BG2X= sPlayerPosX - lxr + lyr;

    // vertical offset
    lxr= 120 * (lsf>>4);
    lyr= lcf<<3;
    REG_BG2Y= sPlayerPosY - lxr - lyr;
}

#define spTiltAngle data[0]
#define spBarrelRollDir data[1]
#define spDestAngle data[2]
#define spFlipped data[3]

#define TILT_MAX 0x1000
#define TILT_MIN -0x1000
#define TILT_STEP 0x100

static void UpdateEonSpriteRotation(struct Sprite *sprite)
{
    switch (sprite->spBarrelRollDir)
    {
    case 0:  // no barrel roll
        if (sprite->spTiltAngle < sprite->spDestAngle)
            sprite->spTiltAngle += TILT_STEP;
        else if (sprite->spTiltAngle > sprite->spDestAngle)
            sprite->spTiltAngle -= TILT_STEP;
        break;
    default:
        if (sprite->spBarrelRollDir > 0)  // increase angle
        {
            if (sprite->spTiltAngle < TILT_MIN)
            {
                sprite->spTiltAngle += TILT_STEP << 3;
                if (sprite->spTiltAngle >= TILT_MIN)
                    sprite->spBarrelRollDir = 0;
                break;
            }
            sprite->spTiltAngle += TILT_STEP << 3;
        }
        else  // decrease angle
        {
            if (sprite->spTiltAngle > TILT_MAX)
            {
                sprite->spTiltAngle -= TILT_STEP << 3;
                if (sprite->spTiltAngle <= TILT_MAX)
                    sprite->spBarrelRollDir = 0;
                break;
            }
            sprite->spTiltAngle -= TILT_STEP << 3;
        }
        break;
    }

    SetOamMatrixRotationScaling(sprite->oam.matrixNum, 1 << 8, 1 << 8, -sprite->spTiltAngle);
}

static void StartBarrelRoll(void)
{
    struct Sprite *sprite = &gSprites[sEonSpriteId];

    if (sprite->spBarrelRollDir == 0)
    {
        sprite->spFlipped = 0;
        if (sprite->spDestAngle > 0 || (sprite->spDestAngle == 0 && Random() & 1))
            sprite->spBarrelRollDir = 1;
        else
            sprite->spBarrelRollDir = -1;
    }
}

static void UpdateMapSectionPopup(void)
{
    u16 mapSection = GetRegionMapSectionAt_(sPlayerPosX >> 11, sPlayerPosY >> 11;

    if (mapSection != sPrevMapSection)
    {
        if (mapSection == MAPSEC_NONE)
        {
            REG_DISPCNT &= ~DISPCNT_BG0_ON;
        }
        else
        {
            REG_DISPCNT |= DISPCNT_BG0_ON;
            GetMapSectionName(gStringVar4, mapSection, 50);
            Menu_BlankWindowRect(sPopupWindowRect.left + 1, sPopupWindowRect.top + 1, sPopupWindowRect.right - 1, sPopupWindowRect.bottom - 1);
            Menu_PrintText(gStringVar4, 1, 1);
        }
        sPrevMapSection = mapSection;
    }
}

static const u8 sText_LandHere[] = _("Land here?\nA: Land    B: Cancel");

static void ExitSoar(void)
{
    PlaySE(SE_PC_OFF);
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
    SetMainCallback2(CB2_FadeOut);
}

// movement limits
#define MIN_Z 5
#define MAX_Z 20
#define MIN_X 0
#define MAX_X (30 << 3)
#define MIN_Y 0
#define MAX_Y (20 << 3)

static void CB2_HandleInput(void)
{
    s16 sinYaw;
    s16 cosYaw;

    if ((gMain.newKeys & A_BUTTON) && sPrevMapSection != MAPSEC_NONE)
    {
        Menu_DisplayDialogueFrame();
        MenuPrintMessageDefaultCoords(sText_LandHere);
        SetMainCallback2(PromptLandCB2);
        return;
    }

    if (gMain.newKeys & START_BUTTON)
    {
        ExitSoar();
        return;
    }

    if (gMain.newKeys & R_BUTTON)
        StartBarrelRoll();

    gSprites[sEonSpriteId].spDestAngle = 0;

    if (gMain.heldKeys & DPAD_LEFT)
    {
        sPlayerYaw--;
        gSprites[sEonSpriteId].spDestAngle = TILT_MIN;
    }
    if (gMain.heldKeys & DPAD_RIGHT)
    {
        sPlayerYaw++;
        gSprites[sEonSpriteId].spDestAngle = TILT_MAX;
    }
    if (gMain.heldKeys & DPAD_UP)
    {
        sPlayerPosZ += 0x10;
        if (sPlayerPosZ > (MAX_Z << 8))
            sPlayerPosZ = (MAX_Z << 8);
    }
    if (gMain.heldKeys & DPAD_DOWN)
    {
        sPlayerPosZ -= 0x10;
        if (sPlayerPosZ < (MIN_Z << 8))
            sPlayerPosZ = (MIN_Z << 8);
    }

    UpdateEonSpriteRotation(&gSprites[sEonSpriteId]);

    sinYaw = gSineTable[sPlayerYaw];
    cosYaw = gSineTable[sPlayerYaw + 64];
    if (gMain.heldKeys & L_BUTTON)
    {
        sPlayerPosX += sinYaw >> 2;
        sPlayerPosY -= cosYaw >> 2;
    }
    else
    {
        sPlayerPosX += sinYaw >> 3;
        sPlayerPosY -= cosYaw >> 3;
    }

    if (sPlayerPosX < Q_8_8(MIN_X, 0))
        sPlayerPosX = Q_8_8(MIN_X, 0);
    else if (sPlayerPosX > Q_8_8(MAX_X, 0))
        sPlayerPosX = Q_8_8(MAX_X, 0);

    if (sPlayerPosY < Q_8_8(MIN_Y, 0))
        sPlayerPosY = Q_8_8(MIN_Y, 0);
    else if (sPlayerPosY > Q_8_8(MAX_Y, 0))
        sPlayerPosY = Q_8_8(MAX_Y, 0);

    UpdateMapSectionPopup();

    BuildOamBuffer();
    //AnimateSprites();
}

static void PromptLandCB2(void)
{
    if (Menu_UpdateWindowText())
    {
        // TODO: Why does this yes/no menu screw everything up?
        //DisplayYesNoMenu(20, 8, 1);
        SetMainCallback2(ProcessYesNoCB2);
    }
    UpdateEonSpriteRotation(&gSprites[sEonSpriteId]);
    BuildOamBuffer();
    //AnimateSprites();
}

static void ErasePrompt(void)
{
    Menu_EraseWindowRect(0, 8, 29, 19);
}

static void ProcessYesNoCB2(void)
{
    switch (Menu_ProcessInputNoWrap_())
    {
    case 0:
        ErasePrompt();
        SetMainCallback2(WarpCB2);
        break;
    case -1:
    case 1:
        ErasePrompt();
        SetMainCallback2(CB2_HandleInput);
        break;
    }
    BuildOamBuffer();
}

static void WarpCB2(void)
{
    if (sUnknown_083E7920[sPrevMapSection][2] != 0)
        sub_8053538(sUnknown_083E7920[sPrevMapSection][2]);
    else
        warp1_set_2(sUnknown_083E7920[sPrevMapSection][0], sUnknown_083E7920[sPrevMapSection][1], -1);
    //ExitSoar();
    //sub_80865BC();
    Fldeff_FlyLand();
}

static void CB2_FadeOut(void)
{
    if (!gPaletteFade.active)
    {
        REG_IME = 0;
        REG_IE &= ~(INTR_FLAG_HBLANK);
        REG_IME = 1;
        REG_DISPSTAT &= ~(DISPSTAT_HBLANK_INTR);

        SetHBlankCallback(NULL);
        SetMainCallback2(sub_805469C);
    }
}
