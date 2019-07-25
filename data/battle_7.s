	.include "include/macros.inc"
	.include "constants/constants.inc"

	.section .rodata

	.align 2
gUnknown_081FAF24:: @ 81FAF24
	obj_tiles gEnemyMonShadow_Gfx, 128, 0xD759

	.align 2
gOamData_81FAF2C:: @ 81FAF2C
	.short 0x4000
	.short 0x4000
	.short 0x0C00

	.align 2
gSpriteTemplate_81FAF34:: @ 81FAF34
	spr_template 55129, 55039, gOamData_81FAF2C, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, sub_8032978

	.align 2
gUnknown_081FAF4C:: @ 81FAF4C
	.int gSharedMem + 0x8000
	.int gSharedMem + 0xA000
	.int gSharedMem + 0xC000
	.int gSharedMem + 0xE000
