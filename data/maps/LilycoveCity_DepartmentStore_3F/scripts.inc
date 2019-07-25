LilycoveCity_DepartmentStore_3F_MapScripts:: @ 8159F90
	.byte 0

LilycoveCity_DepartmentStore_3F_EventScript_159F91:: @ 8159F91
	lock
	faceplayer
	message LilycoveCity_DepartmentStore_3F_Text_1A0BE4
	waitmessage
	pokemart LilycoveCity_DepartmentStore_3F_Items1
	msgbox LilycoveCity_DepartmentStore_3F_Text_1A0C02, 4
	release
	end

	.align 2
LilycoveCity_DepartmentStore_3F_Items1:: @ 8159FA8
	.short ITEM_PROTEIN
	.short ITEM_CALCIUM
	.short ITEM_IRON
	.short ITEM_ZINC
	.short ITEM_CARBOS
	.short ITEM_HP_UP
	.short ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_3F_EventScript_159FB8:: @ 8159FB8
	lock
	faceplayer
	message LilycoveCity_DepartmentStore_3F_Text_1A0BE4
	waitmessage
	pokemart LilycoveCity_DepartmentStore_3F_Items2
	msgbox LilycoveCity_DepartmentStore_3F_Text_1A0C02, 4
	release
	end


	.align 2
LilycoveCity_DepartmentStore_3F_Items2:: @ 8159FD0
	.short ITEM_X_SPEED
	.short ITEM_X_SPECIAL
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_DIRE_HIT
	.short ITEM_GUARD_SPEC
	.short ITEM_X_ACCURACY
	.short ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_3F_EventScript_159FE2:: @ 8159FE2
	msgbox LilycoveCity_DepartmentStore_3F_Text_18C24B, 2
	end

LilycoveCity_DepartmentStore_3F_EventScript_159FEB:: @ 8159FEB
	msgbox LilycoveCity_DepartmentStore_3F_Text_18C2B5, 2
	end

LilycoveCity_DepartmentStore_3F_EventScript_159FF4:: @ 8159FF4
	msgbox LilycoveCity_DepartmentStore_3F_Text_18C32E, 2
	end
