	.include "MPlayDef.s"

	.equ	se_z_page_grp, voicegroup110
	.equ	se_z_page_pri, 5
	.equ	se_z_page_rev, reverb_set+50
	.equ	se_z_page_mvl, 127
	.equ	se_z_page_key, 0
	.equ	se_z_page_tbs, 1
	.equ	se_z_page_exg, 0
	.equ	se_z_page_cmp, 1

	.section .rodata
	.global	se_z_page
	.align	2

@********************** Track  1 **********************@

se_z_page_1:
	.byte	KEYSH , se_z_page_key+0
	.byte	TEMPO , 100*se_z_page_tbs/2
	.byte		VOICE , 4
	.byte		BENDR , 12
	.byte		XCMD  , xIECV , 10
	.byte		        xIECL , 8
	.byte		VOL   , 90*se_z_page_mvl/mxv
	.byte		BEND  , c_v+4
	.byte		N01   , Cn5 , v064
	.byte	W01
	.byte		        Cn5 , v020
	.byte	W01
	.byte		        Cn5 , v064
	.byte	W01
	.byte		        Cn5 , v020
	.byte	W01
	.byte		        Cn6 , v064
	.byte	W02
	.byte		        Cn6 , v020
	.byte	W03
	.byte	FINE

@******************************************************@
	.align	2

se_z_page:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	se_z_page_pri	@ Priority
	.byte	se_z_page_rev	@ Reverb.

	.int	se_z_page_grp

	.int	se_z_page_1

	.end
