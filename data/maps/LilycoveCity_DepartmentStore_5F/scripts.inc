LilycoveCity_DepartmentStore_5F_MapScripts:: @ 815A060
	.byte 0

LilycoveCity_DepartmentStore_5F_EventScript_15A061:: @ 815A061
	lock
	faceplayer
	message LilycoveCity_DepartmentStore_5F_Text_1A0BE4
	waitmessage
	pokemartdecoration2 LilycoveCity_DepartmentStore_5F_Items1
	msgbox LilycoveCity_DepartmentStore_5F_Text_1A0C02, 4
	release
	end

	.align 2
LilycoveCity_DepartmentStore_5F_Items1:: @ 815A078
	.short ITEM_X_DEFEND
	.short ITEM_X_SPEED
	.short ITEM_X_ACCURACY
	.short ITEM_SUPER_REPEL
	.short 91
	.short 92
	.short ITEM_SUN_STONE
	.short ITEM_MOON_STONE
	.short ITEM_FIRE_STONE
	.short ITEM_THUNDER_STONE
	.short ITEM_WATER_STONE
	.short ITEM_LEAF_STONE
	.short ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_5F_EventScript_15A094:: @ 815A094
	lock
	faceplayer
	message LilycoveCity_DepartmentStore_5F_Text_1A0BE4
	waitmessage
	pokemartdecoration2 LilycoveCity_DepartmentStore_5F_Items2
	msgbox LilycoveCity_DepartmentStore_5F_Text_1A0C02, 4
	release
	end

	.align 2
LilycoveCity_DepartmentStore_5F_Items2:: @ 815A0AC
	.short 101
	.short 102
	.short ITEM_BIG_MUSHROOM
	.short 105
	.short ITEM_PEARL
	.short ITEM_BIG_PEARL
	.short ITEM_STARDUST
	.short ITEM_STAR_PIECE
	.short ITEM_NUGGET
	.short ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_5F_EventScript_15A0C2:: @ 815A0C2
	lock
	faceplayer
	message LilycoveCity_DepartmentStore_5F_Text_1A0BE4
	waitmessage
	pokemartdecoration2 LilycoveCity_DepartmentStore_5F_Items3
	msgbox LilycoveCity_DepartmentStore_5F_Text_1A0C02, 4
	release
	end

	.align 2
LilycoveCity_DepartmentStore_5F_Items3:: @ 815A0DC
	.short ITEM_CARBOS
	.short ITEM_CALCIUM
	.short ITEM_RARE_CANDY
	.short ITEM_PP_UP
	.short ITEM_ZINC
	.short ITEM_PP_MAX
	.short 72
	.short ITEM_GUARD_SPEC
	.short ITEM_DIRE_HIT
	.short ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_5F_EventScript_15A0F2:: @ 815A0F2
	lock
	faceplayer
	message LilycoveCity_DepartmentStore_5F_Text_1A0BE4
	waitmessage
	pokemartdecoration2 LilycoveCity_DepartmentStore_5F_Items4
	msgbox LilycoveCity_DepartmentStore_5F_Text_1A0C02, 4
	release
	end

	.align 2
LilycoveCity_DepartmentStore_5F_Items4:: @ 815A10C
	.short 59
	.short 60
	.short 61
	.short 62
	.short ITEM_HP_UP
	.short ITEM_PROTEIN
	.short ITEM_IRON
	.short ITEM_RED_SHARD
	.short ITEM_BLUE_SHARD
	.short ITEM_YELLOW_SHARD
	.short ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_5F_EventScript_15A124:: @ 815A124
	msgbox LilycoveCity_DepartmentStore_5F_Text_18C4F9, 2
	end

LilycoveCity_DepartmentStore_5F_EventScript_15A12D:: @ 815A12D
	msgbox LilycoveCity_DepartmentStore_5F_Text_18C59F, 2
	end

LilycoveCity_DepartmentStore_5F_EventScript_15A136:: @ 815A136
	msgbox LilycoveCity_DepartmentStore_5F_Text_18C556, 2
	end
