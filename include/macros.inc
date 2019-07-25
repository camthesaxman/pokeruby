	.include "include/macros/asm.inc"
	.include "include/macros/function.inc"
	.include "include/macros/movement.inc"
	.include "include/macros/pokemon_data.inc"
	.include "include/macros/map.inc"
	.include "include/macros/mystery_event_script.inc"

	.macro region_map_location x, y, width, height, name
	.byte \x
	.byte \y
	.byte \width
	.byte \height
	.int gMapName_\name
	.endm

	.macro obj_tiles address, uncompressed_size, tag
	.int \address
	.short \uncompressed_size
	.short \tag
	.endm

	.macro null_obj_tiles
	obj_tiles 0, 0, 0
	.endm

	.macro obj_pal address, tag
	.int \address
	.short \tag
	.short 0 @ padding
	.endm

	.macro null_obj_pal
	obj_pal 0, 0
	.endm

	.macro paired_pals tag, address
	.short \tag
	.short 0 @ padding
	.int \address
	.endm

@ For object animation frames.
	.macro obj_frame_tiles address, uncompressed_size
	.int \address
	.short \uncompressed_size
	.short 0 @ padding
	.endm

	.macro spr_template tile_tag, pal_tag, oam, anims, images, affine_anims, callback
	.short \tile_tag
	.short \pal_tag
	.int \oam
	.int \anims
	.int \images
	.int \affine_anims
	.int \callback
	.endm

@ Berry trees have a table defining the palette slot used for each of their 5
@ stages. However, the first 2 stages always use the same slots regardless of
@ the type of tree and the slots of the last 3 stages always equal each other.
	.macro berry_tree_palette_slot_table slot
	.byte 3, 4, \slot, \slot, \slot
	.endm

	.macro subsprite x, y, priority, tile_num_offset, size
	.short \x
	.short \y
	.short ((\priority) << 14) | ((\tile_num_offset) << 4) | SPRITE_SIZE_\size
	.short 0 @ padding
	.endm

	.macro obj_image_anim_frame pic_id, duration, flags = 0
	.short \pic_id
	.byte (\flags) | (\duration)
	.byte 0 @ padding
	.endm

	.macro obj_image_anim_loop count
	.short 0xfffd
	.byte \count
	.byte 0 @ padding
	.endm

	.macro obj_image_anim_jump target_index
	.short 0xfffe
	.byte \target_index
	.byte 0 @ padding
	.endm

	.macro obj_image_anim_end
	.short 0xffff
	.short 0 @ padding
	.endm

	.macro obj_rot_scal_anim_frame delta_x_scale, delta_y_scale, delta_angle, duration
	.short \delta_x_scale
	.short \delta_y_scale
	.byte \delta_angle
	.byte \duration
	.short 0 @ padding
	.endm

	.macro obj_rot_scal_anim_loop count
	.short 0x7ffd
	.short \count
	.int 0 @ padding
	.endm

	.macro obj_rot_scal_anim_jump target_index
	.short 0x7ffe
	.short \target_index
	.int 0 @ padding
	.endm

	.macro obj_rot_scal_anim_end unknown=0
	.short 0x7fff
	.short \unknown
	.fill 4 @ padding
	.endm

	.macro credits_entry number, text
	.int \number
	.int \text
	.endm

	.macro door_anim_frame unknown, offset
	.byte \unknown
	.byte 0 @ padding
	.short \offset
	.endm

	.macro door_anim_gfx metatile_num, unknown, tile_addr, palette_addr
	.short \metatile_num
	.short \unknown
	.int \tile_addr
	.int \palette_addr
	.endm

	.macro trainer_eye_trainer opp_1, opp_2, opp_3, opp_4, opp_5, map_name
	.short OPPONENT_\opp_1
	.short OPPONENT_\opp_2
	.short OPPONENT_\opp_3
	.short OPPONENT_\opp_4
	.short OPPONENT_\opp_5
	.short GROUP_\map_name
	.short MAP_\map_name
	.space 2
	.endm
