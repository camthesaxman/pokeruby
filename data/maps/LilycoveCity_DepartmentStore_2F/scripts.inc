LilycoveCity_DepartmentStore_2F_MapScripts:: @ 8159F0E
	.byte 0

LilycoveCity_DepartmentStore_2F_EventScript_159F0F:: @ 8159F0F
	msgbox LilycoveCity_DepartmentStore_2F_Text_18C162, 2
	end

LilycoveCity_DepartmentStore_2F_EventScript_159F18:: @ 8159F18
	msgbox LilycoveCity_DepartmentStore_2F_Text_18C195, 2
	end

LilycoveCity_DepartmentStore_2F_EventScript_159F21:: @ 8159F21
	msgbox LilycoveCity_DepartmentStore_2F_Text_18C1D9, 2
	end

LilycoveCity_DepartmentStore_2F_EventScript_159F2A:: @ 8159F2A
	lock
	faceplayer
	message LilycoveCity_DepartmentStore_2F_Text_1A0BE4
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Items1
	msgbox LilycoveCity_DepartmentStore_2F_Text_1A0C02, 4
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Items1:: @ 8159F44
	.short ITEM_POKE_BALL
	.short ITEM_GREAT_BALL
	.short ITEM_ULTRA_BALL
	.short ITEM_ESCAPE_ROPE
	.short ITEM_FULL_HEAL
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_BURN_HEAL
	.short ITEM_ICE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_FLUFFY_TAIL
	.short ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_2F_EventScript_159F5E:: @ 8159F5E
	lock
	faceplayer
	message LilycoveCity_DepartmentStore_2F_Text_1A0BE4
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Items2
	msgbox LilycoveCity_DepartmentStore_2F_Text_1A0C02, 4
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Items2:: @ 8159F78
	.short ITEM_POTION
	.short ITEM_SUPER_POTION
	.short ITEM_HYPER_POTION
	.short ITEM_MAX_POTION
	.short ITEM_REVIVE
	.short ITEM_REPEL
	.short ITEM_SUPER_REPEL
	.short ITEM_MAX_REPEL
	.short ITEM_WAVE_MAIL
	.short ITEM_MECH_MAIL
	.short ITEM_NONE
	release
	end
