#include "global.h"
#include "constants/songs.h"
#include "constants/region_map_sections.h"
#include "decompress.h"
#include "ewram.h"
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
#include "constants/field_effects.h"

#define NOCASH_BREAKPOINT asm("mov r11, r11")

// VRAM memory layout
// Contains 256 8x8 tiles with 8-bit color (0x4000 bytes)
#define BG2_IMAGE_OFFSET 0
// 128x128 map with 1 byte per entry (0x4000 bytes)
#define BG2_TILEMAP_OFFSET 0xC000

// Not sure how much space this takes
#define BG0_IMAGE_OFFSET 0x4000
// 32x32 map with 2 bytes per entry (0x800 bytes)
#define BG0_TILEMAP_OFFSET 0xB800

static void CB2_LoadSoarGraphics(void);
//static void DoSoarFieldEffectsCB2(void);
static void SoarVBlankCallback(void);
static void SoarHBlankCallback(void);
static void CB2_HandleInput(void);
static void PromptLandCB2(void);
static void ProcessYesNoCB2(void);
static void WarpCB2(void);
//static void FadeOutVBlankCallback(void);
static void CB2_FadeOut(void);

extern const u8 sUnknown_083E7920[][3];

static const struct WindowTemplate sPopupWindowTemplate =
{
    0, // BG number
    BG0_IMAGE_OFFSET / 0x4000, // BG character base block
    BG0_TILEMAP_OFFSET / 0x800, // BG screen base block
    0, // BG priority
    15, // palette number
    1, // foreground color
    15, // background color
    8, // shadow color
    3, // font
    2, // text mode
    0, // spacing
    0, // tilemap left coordinate
    0, // tilemap top coordinate
    30, // width
    20, // height
    (void *)(VRAM + BG0_IMAGE_OFFSET), // tile data
    (void *)(VRAM + BG0_TILEMAP_OFFSET), // tilemap
};

// For now, steal the region map graphics. Maybe we can create prettier graphics in the future.
extern const u16 sRegionMapBkgnd_Pal[];
extern const u8 sRegionMapBkgnd_ImageLZ[];
extern const u8 sRegionMapBkgnd_TilemapLZ[];

extern const u8 sMapHealLocations[][3];

//
// Eon sprite data
//

#define GFX_TAG_EON 9999

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
    .y = 0,
    .affineMode = 3,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 1,
    .x = 0,
    .matrixNum = 0,
    .size = 3,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sEonSpriteTemplate =
{
    .tileTag = GFX_TAG_EON,
    .paletteTag = GFX_TAG_EON,
    .oam = &sEonSpriteOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = NULL,
    .callback = SpriteCallbackDummy,
};

//
// Shadow sprite data
//

#define GFX_TAG_SHADOW 9998

static const u8 sShadowSpriteTiles[] = INCBIN_U8("graphics/soar/shadow.4bpp.lz");
static const struct CompressedSpriteSheet sShadowSpriteSheet = {sShadowSpriteTiles, 1024, GFX_TAG_SHADOW};

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
    .tileTag = GFX_TAG_SHADOW,
    .paletteTag = GFX_TAG_SHADOW,
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
//static u8 sShadowSpriteId;

#define Q_8_8(iPart, fPart) (((iPart) << 8) | (fPart))
#define IPART(n) ((n) >> 8)
#define FPART(n) ((n) & 0xFFFF)

static const u8 sEonFluteUseMessage[] = _("{PLAYER} used the EON FLUTE.{PAUSE_UNTIL_PRESS}");

void CB2_InitSoar(void)
{
    switch (gMain.state)
    {
    case 0:
        StringExpandPlaceholders(gStringVar4, sEonFluteUseMessage);
        Menu_DisplayDialogueFrame();
        MenuPrintMessageDefaultCoords(gStringVar4);
        gMain.state++;
        break;
    case 1:
        if (Menu_UpdateWindowText())
        {
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
            gMain.state++;
        }
        break;
    case 2:
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

            SetMainCallback2(CB2_LoadSoarGraphics);
        }
        break;
    }
}

static void LoadEonGraphics(void)
{
    struct CompressedSpriteSheet sEonSpriteSheet = {.size = 1024, .tag = GFX_TAG_EON};
    struct CompressedSpritePalette sEonSpritePalette = {.tag = GFX_TAG_EON};

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
    sEonSpriteId = CreateSprite(&sEonSpriteTemplate, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, 0);
    gSprites[sEonSpriteId].data[0] = 0;
    gSprites[sEonSpriteId].data[1] = 0;
    gSprites[sEonSpriteId].data[2] = 0;
}

#define HORIZON 34  // scanline to begin drawing land

static u8 fogLevels[160];  // fog levels (0-16) for each scanline

static void CB2_LoadSoarGraphics(void)
{
    unsigned int i;
    u8 *src;
    u8 *dest;

    switch (gMain.state)
    {
    case 0:
        REG_DISPCNT = 0;

        DmaClearLarge32(3, (void *)(VRAM), VRAM_SIZE, 0x1000);

        SetVBlankCallback(SoarVBlankCallback);
        SetHBlankCallback(SoarHBlankCallback);

        // Load image data
        LZ77UnCompVram(sRegionMapBkgnd_ImageLZ, (void *)(VRAM + BG2_IMAGE_OFFSET));
        
        // Load tilemap
        LZ77UnCompVram(sRegionMapBkgnd_TilemapLZ, gSharedMem);
        src = gSharedMem;
        dest = (void *)(VRAM + BG2_TILEMAP_OFFSET);
        // Copy each row to VRAM
        for (i = 0; i < 64; i++)
        {
            DmaCopy32(3, src, dest, 64);
            src += 64;
            dest += 128;
        }

        // load palette
        LoadPalette(sRegionMapBkgnd_Pal, 0x70, 64);

        // Create sprites
        LoadEonGraphics();
        //LoadCompressedObjectPic(&sShadowSpriteSheet);
        //sShadowSpriteId = CreateSprite(&sShadowSpriteTemplate, DISPLAY_WIDTH / 2, 3 * DISPLAY_HEIGHT / 4, 0);

        gPlttBufferUnfaded[0] = RGB(16, 16, 31);  // backdrop color (for sky)

        // Calculate fog levels
        for (i = 0; i < 160; i++)
        {
            int fog;
            if (i < HORIZON)
                fog = 14 - (HORIZON - i);
            else
                fog = 14 - (i - HORIZON) / 3;
            fogLevels[i] = max(fog, 0);
        }

        gMain.state++;
        break;
    case 1:
        // initialize text window
        Text_LoadWindowTemplate(&sPopupWindowTemplate);
        InitMenuWindow(&sPopupWindowTemplate);
        Menu_DrawStdWindowFrame(sPopupWindowRect.left, sPopupWindowRect.top, sPopupWindowRect.right, sPopupWindowRect.bottom);
        gMain.state++;
        break;
    case 2:
        // Enable hblank and vblank interrupts
        REG_IME = 0;
        REG_IE |= INTR_FLAG_VBLANK | INTR_FLAG_HBLANK;
        REG_IME = 1;
        REG_DISPSTAT |= DISPSTAT_VBLANK_INTR | DISPSTAT_HBLANK_INTR;

        // Set up video regs
        REG_DISPCNT = DISPCNT_MODE_1 | DISPCNT_BG2_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP;
        REG_BG2CNT = BGCNT_PRIORITY(0)
                   | BGCNT_256COLOR
                   | BGCNT_CHARBASE(BG2_IMAGE_OFFSET / 0x4000)
                   | BGCNT_SCREENBASE(BG2_TILEMAP_OFFSET / 0x800)
                   | BGCNT_AFF1024x1024
                   | BGCNT_WRAP;

        // Start palette fade
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0);
        gMain.state++;
        break;
    case 3:
        // Wait for fade to finish palette fade
        if (!gPaletteFade.active)
        {
            SetMainCallback2(CB2_HandleInput);
        }
        break;
    }
    BuildOamBuffer();
}

static void SoarVBlankCallback(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    UpdatePaletteFade();

    REG_BG2X = 0;
    REG_BG2Y = 0;
    REG_BG2PA = 0;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 0;

    // Turn on lighten effect for fog
    REG_BLDCNT = BLDCNT_EFFECT_LIGHTEN | BLDCNT_TGT1_BD | BLDCNT_TGT1_BG2;

    // OBJWIN gets enabled when the YES/NO menu is opened, and it interferes with the BLDCNT fog effects.
    REG_DISPCNT &= ~DISPCNT_OBJWIN_ON;

    // Turn off BG for first scanlines
    REG_DISPCNT &= ~DISPCNT_BG2_ON;

    REG_BLDY = 0;
    TransferPlttBuffer();
}

#define M7_D 128

static void SoarHBlankCallback(void)
{
    int sinYaw = gSineTable[sPlayerYaw];
    int cosYaw = gSineTable[sPlayerYaw + 64];

    int lam, lcf, lsf, lxr, lyr;
    u32 currScanline = REG_VCOUNT;

    if (currScanline > 159)  // We're in vblank. Nothing to do.
        return;

    REG_BLDY = fogLevels[currScanline];

    if (currScanline < HORIZON)
        return;

    if (currScanline == HORIZON)
        REG_DISPCNT |= DISPCNT_BG2_ON;

    lam= sPlayerPosZ * ((1 << 16) / (currScanline - HORIZON))>>12;  // .8*.16 /.12 = 20.12
    lcf= lam*cosYaw>>8;                     // .12*.8 /.8 = .12
    lsf= lam*sinYaw>>8;                     // .12*.8 /.8 = .12

    REG_BG2PA= lcf>>4;
    REG_BG2PC= lsf>>4;

    // Offsets
    // Note that the lxr shifts down first! 

    // horizontal offset
    lxr= 120*(lcf>>4);
    lyr= (M7_D*lsf)>>4;
    REG_BG2X= sPlayerPosX - lxr + lyr;

    // vertical offset
    lxr= 120*(lsf>>4);
    lyr= (M7_D*lcf)>>4; 
    REG_BG2Y= sPlayerPosY - lxr - lyr;
}

#define spTiltAngle data[0]
#define spBarrelRollDir data[1]
#define spDestAngle data[2]
#define spFlipped data[3]

#define TILT_MAX 0x1000
#define TILT_MIN -0x1000
#define TILT_STEP 0x100
#define ROLL_TILT_STEP (TILT_STEP * 8)

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
    case 1:  // increase angle
        if (sprite->spTiltAngle < TILT_MIN)  // rotation is past 180 degrees
        {
            sprite->spTiltAngle += ROLL_TILT_STEP;
            if (sprite->spTiltAngle >= TILT_MIN)
                sprite->spBarrelRollDir = 0;
            break;
        }
        sprite->spTiltAngle += ROLL_TILT_STEP;
        break;
    case -1:  // decrease angle
        if (sprite->spTiltAngle > TILT_MAX)  // rotation is past 180 degrees
        {
            sprite->spTiltAngle -= ROLL_TILT_STEP;
            if (sprite->spTiltAngle <= TILT_MAX)
                sprite->spBarrelRollDir = 0;
            break;
        }
        sprite->spTiltAngle -= ROLL_TILT_STEP;
        break;
    }

    SetOamMatrixRotationScaling(sprite->oam.matrixNum, 1 << 8, 1 << 8, -sprite->spTiltAngle);
}

static void StartBarrelRoll(void)
{
    struct Sprite *sprite = &gSprites[sEonSpriteId];

    if (sprite->spBarrelRollDir == 0)
    {
        PlaySE(SE_W016B);
        sprite->spFlipped = 0;
        if (sprite->spDestAngle >= 0)
            sprite->spBarrelRollDir = 1;
        else
            sprite->spBarrelRollDir = -1;
    }
}

static void UpdateMapSectionPopup(void)
{
    unsigned int mapSection = GetRegionMapSectionAt_(IPART(sPlayerPosX) / 8, IPART(sPlayerPosY) / 8);

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

static const u8 sText_LandHere[] = _("Land here?");

static void ExitSoar(void)
{
    PlaySE(SE_PC_OFF);
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
    SetMainCallback2(CB2_FadeOut);
}

// movement limits
#define MIN_Z Q_8_8(4, 0)
#define MAX_Z Q_8_8(50, 0)
#define MIN_X Q_8_8(0, 0)
#define MAX_X Q_8_8(30*8, 0)
#define MIN_Y Q_8_8(0, 0)
#define MAX_Y Q_8_8(20*8, 0)

static void CB2_HandleInput(void)
{
    int sinYaw;
    int cosYaw;

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
        if (sPlayerPosZ > MAX_Z)
            sPlayerPosZ = MAX_Z;
    }
    if (gMain.heldKeys & DPAD_DOWN)
    {
        sPlayerPosZ -= 0x10;
        if (sPlayerPosZ < MIN_Z)
            sPlayerPosZ = MIN_Z;
    }

    UpdateEonSpriteRotation(&gSprites[sEonSpriteId]);

    sinYaw = gSineTable[sPlayerYaw];
    cosYaw = gSineTable[sPlayerYaw + 64];

    sPlayerPosX += sinYaw / 8;
    sPlayerPosY -= cosYaw / 8;
    
    if (gMain.heldKeys & L_BUTTON)  // boost
    {
        sPlayerPosX += sinYaw / 4;
        sPlayerPosY -= cosYaw / 4;
    }

    if (sPlayerPosX < MIN_X)
        sPlayerPosX = MIN_X;
    else if (sPlayerPosX > MAX_X)
        sPlayerPosX = MAX_X;

    if (sPlayerPosY < MIN_Y)
        sPlayerPosY = MIN_Y;
    else if (sPlayerPosY > MAX_Y)
        sPlayerPosY = MAX_Y;

    UpdateMapSectionPopup();

    BuildOamBuffer();
}

static void PromptLandCB2(void)
{
    if (Menu_UpdateWindowText())
    {
        DisplayYesNoMenu(20, 8, 1);
        SetMainCallback2(ProcessYesNoCB2);
    }
    UpdateEonSpriteRotation(&gSprites[sEonSpriteId]);
    BuildOamBuffer();
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
    if (sMapHealLocations[sPrevMapSection][2] != 0)
        sub_8053538(sMapHealLocations[sPrevMapSection][2]);
    else
        warp1_set_2(sMapHealLocations[sPrevMapSection][0], sMapHealLocations[sPrevMapSection][1], -1);
    sub_80865BC_SoarLand();
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
        SetMainCallback2(c2_exit_to_overworld_1_sub_8080DEC);
    }
}

