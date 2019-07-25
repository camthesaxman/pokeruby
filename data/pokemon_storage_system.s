	.include "include/macros.inc"
	.include "constants/constants.inc"

	.section .rodata

	.align 2

gUnknown_083BBBD4:: @ 83BBBD4
	.int sub_809C464, 0
	.int sub_809C664, 1
	.int sub_809C85C, 2
	.int sub_809C944, 3
	.int NULL, 0

	.align 2
gHandCursorSpriteSheets:: @ 83BBBFC
	obj_tiles HandCursorTiles, 0x800, 0
	obj_tiles HandCursorShadowTiles, 0x80, 1
	null_obj_tiles

	.align 2
gHandCursorSpritePalettes:: @ 83BBC14
	obj_pal HandCursorPalette, 56006
	obj_pal HandCursorAltPalette, 56017
	null_obj_pal

	.align 2
gOamData_83BBC2C:: @ 83BBC2C
	.short 0x0000
	.short 0x8000
	.short 0x0400

	.align 2
gOamData_83BBC34:: @ 83BBC34
	.short 0x0000
	.short 0x4000
	.short 0x0800

	.align 2
gSpriteAnim_83BBC3C:: @ 83BBC3C
	obj_image_anim_frame 0, 30
	obj_image_anim_frame 16, 30
	obj_image_anim_jump 0

	.align 2
gSpriteAnim_83BBC48:: @ 83BBC48
	obj_image_anim_frame 0, 5
	obj_image_anim_end

	.align 2
gSpriteAnim_83BBC50:: @ 83BBC50
	obj_image_anim_frame 32, 5
	obj_image_anim_end

	.align 2
gSpriteAnim_83BBC58:: @ 83BBC58
	obj_image_anim_frame 48, 5
	obj_image_anim_end

	.align 2
gSpriteAnimTable_83BBC60:: @ 83BBC60
	.int gSpriteAnim_83BBC3C
	.int gSpriteAnim_83BBC48
	.int gSpriteAnim_83BBC50
	.int gSpriteAnim_83BBC58

	.align 2
gSpriteTemplate_83BBC70:: @ 83BBC70
	spr_template 0, 56006, gOamData_83BBC2C, gSpriteAnimTable_83BBC60, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

	.align 2
gSpriteTemplate_83BBC88:: @ 83BBC88
	spr_template 1, 56006, gOamData_83BBC34, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, sub_809CB74

.if DEBUG
gUnknown_Debug_0x83E6268:: @ 0x83E6268
	.string "セットする$"
.endif

	.align 2
gUnknown_083BBCA0:: @ 83BBCA0
	.int PCText_Cancel2
	.int PCText_Deposit
	.int PCText_Withdraw
	.int PCText_Move
	.int PCText_Switch
	.int PCText_Place
	.int PCText_Summary
	.int PCText_Release
	.int PCText_Mark
	.int PCText_Jump
	.int PCText_Wallpaper
	.int PCText_Name
	.int PCText_Scenery1
	.int PCText_Scenery2
	.int PCText_Scenery3
	.int PCText_Etc
	.int PCText_Forest
	.int PCText_City
	.int PCText_Desert
	.int PCText_Savanna
	.int PCText_Crag
	.int PCText_Volcano
	.int PCText_Snow
	.int PCText_Cave
	.int PCText_Beach
	.int PCText_Seafloor
	.int PCText_River
	.int PCText_Sky
	.int PCText_Polka
	.int PCText_PokeCenter
	.int PCText_Machine
	.int PCText_Plain
.if DEBUG
	.int gUnknown_Debug_0x83E6268
.endif
