#include "global.h"
#include "gba/gba.h"
#include "gba/flash_internal.h"
#include <stdio.h>

#define fopen         _fopen
#define fseek         _fseek
#define fclose        _fclose
#define fread         _fread
#define fwrite        _fwrite

const u16 dummyMaxTime[] =
{
      10, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
      10, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
    2000, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
    2000, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
};

const struct FlashSetupInfo DUMMY_SAVE =
{
    ProgramFlashByte_DUMMY,
    ProgramFlashSector_DUMMY,
    EraseFlashChip_DUMMY,
    EraseFlashSector_DUMMY,
    WaitForFlashWrite_DUMMY,
    dummyMaxTime,
    {
        131072, // ROM size
        {
            4096, // sector size
              12, // bit shift to multiply by sector size (4096 == 1 << 12)
              32, // number of sectors
               0  // appears to be unused
        },
        { 3, 1 }, // wait state setup data
        { { 0xCC, 0xCC } } // ID
    }
};

u16 WaitForFlashWrite_DUMMY(u8 phase, u8 *addr, u8 lastData)
{
    puts("function WaitForFlashWrite_DUMMY is a stub");
    return 0;
}

u16 EraseFlashChip_DUMMY(void)
{
    puts("function EraseFlashChip_DUMMY is a stub");
    return 0;
}

u16 EraseFlashSector_DUMMY(u16 sectorNum)
{
    puts("function EraseFlashSector_DUMMY is a stub");
    return 0;
}

u16 ProgramFlashByte_DUMMY(u16 sectorNum, u32 offset, u8 data)
{
    u8 val = data;
    FILE * savefile = fopen("pokeruby.sav", "r+b");
    if (savefile == NULL)
    {
        return 1;
    }
    if (fseek(savefile, 0x1000 * sectorNum + offset, SEEK_SET))
    {
        fclose(savefile);
        return 1;
    }
    if (fwrite(&val, 1, 1, savefile) != 1)
    {
        fclose(savefile);
        return 1;
    }
    fclose(savefile);
    return 0;
}


u16 ProgramFlashSector_DUMMY(u16 sectorNum, void *src)
{
    FILE * savefile = fopen("pokeruby.sav", "r+b");
    if (savefile == NULL)
    {
        return 1;
    }
    if (fseek(savefile, 0x1000 * sectorNum, SEEK_SET))
    {
        fclose(savefile);
        return 1;
    }
    if (fwrite(src, 1, 0x1000, savefile) != 0x1000)
    {
        fclose(savefile);
        return 1;
    }
    fclose(savefile);
    return 0;
}

