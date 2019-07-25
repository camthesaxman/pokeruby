	.macro me_nop
	.byte 0
	.endm

	.macro me_checkcompat word, v1, v2, v3, v4
	.byte 1
	.int \word
	.short \v1
	.int \v2
	.short \v3
	.int \v4
	.endm

	.macro me_end
	.byte 2
	.endm

	.macro me_setmsg value, str
	.byte 3
	.byte \value
	.int \str
	.endm

	.macro me_setstatus value
	.byte 4
	.byte \value
	.endm

	.macro me_runscript script
	.byte 5
	.int \script
	.endm

	.macro me_initramscript mapId, objId, script, end
	.byte 6
	map \mapId
	.byte \objId
	.int \script, \end
	.endm

	.macro me_setenigmaberry berry
	.byte 7
	.int \berry
	.endm

	.macro me_giveribbon index, ribbonId
	.byte 8
	.byte \index, \ribbonId
	.endm

	.macro me_givenationaldex
	.byte 9
	.endm

	.macro me_addrareword word
	.byte 10
	.byte \word
	.endm

	.macro me_setrecordmixinggift unk, quantity, itemId
	.byte 11
	.byte \unk, \quantity
	.short \itemId
	.endm

	.macro me_givepokemon data
	.byte 12
	.int \data
	.endm

	.macro me_addtrainer data
	.byte 13
	.int \data
	.endm

	.macro me_enableresetrtc
	.byte 14
	.endm

	.macro me_checksum checksum, data, dataEnd
	.byte 15
	.int \checksum, \data, \dataEnd
	.endm

	.macro me_crc crc, data, dataEnd
	.byte 16
	.int \crc, \data, \dataEnd
	.endm
