LavaridgeTown_Mart_MapScripts:: @ 81538CA
	.byte 0

LavaridgeTown_Mart_EventScript_1538CB:: @ 81538CB
	lock
	faceplayer
	message LavaridgeTown_Mart_Text_1A0BE4
	waitmessage
	pokemart LavaridgeTown_Mart_Items
	msgbox LavaridgeTown_Mart_Text_1A0C02, 4
	release
	end

	.align 2
LavaridgeTown_Mart_Items:: @ 81538E4
	.short ITEM_GREAT_BALL
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_BURN_HEAL
	.short ITEM_REVIVE
	.short ITEM_SUPER_REPEL
	.short ITEM_X_SPEED
	.short ITEM_NONE
	release
	end

LavaridgeTown_Mart_EventScript_1538FA:: @ 81538FA
	msgbox LavaridgeTown_Mart_Text_176DA6, 2
	end

LavaridgeTown_Mart_EventScript_153903:: @ 8153903
	msgbox LavaridgeTown_Mart_Text_176E1A, 2
	end
