	.macro map map_id
	.byte \map_id >> 8    @ map group
	.byte \map_id & 0xFF  @ map num
	.endm

	.macro map_script type, address
	.byte \type
	.int \address
	.endm

	.macro map_script_2 word1, word2, address
	.short \word1
	.short \word2
	.int \address
	.endm

	.macro object_event index, gfx, replacement, x, y, elevation, movement_type, x_radius, y_radius, trainer_type, sight_radius_tree_etc, script, event_flag
	.byte \index, \gfx, \replacement, 0
	.short \x
	.short \y
	.byte \elevation, \movement_type, ((\y_radius << 4) | \x_radius), 0
    .short \trainer_type, \sight_radius_tree_etc
	.int \script
	.short \event_flag
	.short 0
	inc _num_npcs
	.endm

	.macro warp_def x, y, elevation, warp, map_id
	.short \x, \y
	.byte \elevation, \warp
	.byte \map_id & 0xFF  @ map num
	.byte \map_id >> 8    @ map group
	inc _num_warps
	.endm

	.macro coord_event x, y, elevation, trigger, index, script
	.short \x, \y
	.byte \elevation, 0
	.short \trigger, \index, 0
	.int \script
	inc _num_traps
	.endm

	.macro coord_weather_event x, y, elevation, weather
	.short \x, \y
	.byte \elevation, 0
	.short \weather
	.short 0, 0
	.int 0
	inc _num_traps
	.endm

	.macro bg_event x, y, elevation, kind, arg6, arg7, arg8
	.short \x, \y
	.byte \elevation, \kind
	.short 0
	.if \kind < 5
	.int \arg6
	.else
	.short \arg6
	.byte \arg7, \arg8
	.endif
	inc _num_signs
	.endm

	.macro bg_hidden_item_event x, y, height, item, flag
	bg_event \x, \y, \height, 7, \item, ((\flag) - FLAG_HIDDEN_ITEMS_START), 0
	.endm

	.macro bg_secret_base_event x, y, height, secret_base_id
	bg_event \x, \y, \height, 8, \secret_base_id, 0, 0
	.endm	

	.macro map_events npcs, warps, traps, signs
	.byte _num_npcs, _num_warps, _num_traps, _num_signs
	.int \npcs, \warps, \traps, \signs
	reset_map_events
	.endm

	.macro reset_map_events
	.set _num_npcs, 0
	.set _num_warps, 0
	.set _num_traps, 0
	.set _num_signs, 0
	.endm

	reset_map_events


	.equiv connection_down, 1
	.equiv connection_up, 2
	.equiv connection_left, 3
	.equiv connection_right, 4
	.equiv connection_dive, 5
	.equiv connection_emerge, 6

	.macro connection direction, offset, map, filler
	.int connection_\direction
	.int \offset
	map \map
	.space 2
	.endm
