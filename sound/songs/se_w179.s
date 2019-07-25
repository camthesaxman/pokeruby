	.include "MPlayDef.s"

	.equ	se_w179_grp, voicegroup111
	.equ	se_w179_pri, 4
	.equ	se_w179_rev, reverb_set+50
	.equ	se_w179_mvl, 127
	.equ	se_w179_key, 0
	.equ	se_w179_tbs, 1
	.equ	se_w179_exg, 0
	.equ	se_w179_cmp, 1

	.section .rodata
	.global	se_w179
	.align	2

@********************** Track  1 **********************@

se_w179_1:
	.byte	KEYSH , se_w179_key+0
	.byte	TEMPO , 150*se_w179_tbs/2
	.byte		VOICE , 19
	.byte		BENDR , 24
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		N03   , Cn5 , v092
	.byte	W01
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W01
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W01
	.byte		VOICE , 22
	.byte		PAN   , c_v-10
	.byte		BEND  , c_v+0
	.byte		N01   , Gn4 , v127
	.byte	W01
	.byte		VOICE , 19
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v-1
	.byte		BEND  , c_v-33
	.byte		N03   , Cs5 , v092
	.byte	W02
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W01
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W01
	.byte		VOICE , 22
	.byte		PAN   , c_v+10
	.byte		BEND  , c_v+0
	.byte		N01   , Gs4 , v127
	.byte	W01
	.byte		VOICE , 19
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		BEND  , c_v-33
	.byte		N03   , Dn5 , v092
	.byte	W01
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W02
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W01
	.byte		VOICE , 22
	.byte		PAN   , c_v-14
	.byte		BEND  , c_v+0
	.byte		N01   , An4 , v127
	.byte	W01
	.byte		VOICE , 19
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v-1
	.byte		BEND  , c_v-33
	.byte		N03   , Ds5 , v092
	.byte	W01
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W01
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W02
	.byte		VOICE , 22
	.byte		PAN   , c_v+14
	.byte		BEND  , c_v+0
	.byte		N01   , As4 , v127
	.byte	W01
	.byte		VOICE , 19
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		BEND  , c_v-33
	.byte		N03   , En5 , v092
	.byte	W01
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W01
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W01
	.byte		VOICE , 22
	.byte		PAN   , c_v-18
	.byte		BEND  , c_v+0
	.byte		N01   , Bn4 , v127
	.byte	W02
	.byte		VOICE , 19
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v-1
	.byte		BEND  , c_v-33
	.byte		N03   , Fn5 , v092
	.byte	W01
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W01
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W01
	.byte		VOICE , 22
	.byte		PAN   , c_v+18
	.byte		BEND  , c_v+0
	.byte		N01   , Cn5 , v127
	.byte	W01
	.byte		VOICE , 19
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		BEND  , c_v-33
	.byte		N03   , Fs5 , v092
	.byte	W02
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W01
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W01
	.byte		VOICE , 22
	.byte		PAN   , c_v-14
	.byte		BEND  , c_v+0
	.byte		N01   , Cs5 , v127
	.byte	W01
	.byte		VOICE , 19
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v-1
	.byte		BEND  , c_v-33
	.byte		N03   , Gn5 , v092
	.byte	W01
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W02
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W01
	.byte		VOICE , 22
	.byte		PAN   , c_v+14
	.byte		BEND  , c_v+0
	.byte		N01   , Dn5 , v127
	.byte	W01
	.byte		VOICE , 19
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		BEND  , c_v-33
	.byte		N03   , Gs5 , v092
	.byte	W01
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W01
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W02
	.byte		VOICE , 22
	.byte		PAN   , c_v-10
	.byte		BEND  , c_v+0
	.byte		N01   , Ds5 , v127
	.byte	W01
	.byte		VOICE , 19
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v-1
	.byte		BEND  , c_v-33
	.byte		N03   , An5 , v092
	.byte	W01
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W01
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W01
	.byte		VOICE , 22
	.byte		PAN   , c_v+10
	.byte		BEND  , c_v+0
	.byte		N01   , En5 , v127
	.byte	W02
	.byte		VOICE , 19
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		BEND  , c_v-33
	.byte		N03   , As5 , v092
	.byte	W01
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W01
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W01
	.byte		VOICE , 22
	.byte		PAN   , c_v-10
	.byte		BEND  , c_v+0
	.byte		N01   , Fn5 , v127
	.byte	W01
	.byte		VOICE , 19
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte		PAN   , c_v-1
	.byte		BEND  , c_v-33
	.byte		N03   , Bn5 , v092
	.byte	W02
	.byte		VOL   , 72*se_w179_mvl/mxv
	.byte	W01
	.byte		        40*se_w179_mvl/mxv
	.byte		BEND  , c_v+31
	.byte	W01
	.byte		VOICE , 22
	.byte		PAN   , c_v+10
	.byte		BEND  , c_v+0
	.byte		N01   , Fs5 , v127
	.byte	W01
	.byte		BEND  , c_v-33
	.byte	W03
	.byte	W06
	.byte	FINE

@********************** Track  2 **********************@

se_w179_2:
	.byte	KEYSH , se_w179_key+0
	.byte		VOICE , 17
	.byte		VOL   , 100*se_w179_mvl/mxv
	.byte	W02
	.byte		BEND  , c_v+31
	.byte		N03   , Cn5 , v040
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W01
	.byte		        c_v-33
	.byte	W02
	.byte	W01
	.byte		        c_v+31
	.byte		N03   , Cs5 
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W01
	.byte		        c_v-33
	.byte	W03
	.byte		        c_v+31
	.byte		N03   , Dn5 
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W01
	.byte		        c_v-33
	.byte	W02
	.byte		        c_v+31
	.byte		N03   , Ds5 
	.byte	W02
	.byte		BEND  , c_v+0
	.byte	W01
	.byte		        c_v-33
	.byte	W02
	.byte		        c_v+31
	.byte		N03   , En5 
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W02
	.byte		        c_v-33
	.byte	W02
	.byte		        c_v+31
	.byte		N03   , Fn5 
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W01
	.byte		        c_v-33
	.byte	W02
	.byte	W01
	.byte		        c_v+31
	.byte		N03   , Fs5 
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W01
	.byte		        c_v-33
	.byte	W03
	.byte		        c_v+31
	.byte		N03   , Gn5 
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W01
	.byte		        c_v-33
	.byte	W02
	.byte		        c_v+31
	.byte		N03   , Gs5 
	.byte	W02
	.byte		BEND  , c_v+0
	.byte	W01
	.byte		        c_v-33
	.byte	W02
	.byte		        c_v+31
	.byte		N03   , An5 
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W02
	.byte		        c_v-33
	.byte	W02
	.byte		        c_v+31
	.byte		N03   , As5 
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W01
	.byte		        c_v-33
	.byte	W02
	.byte	W01
	.byte		        c_v+31
	.byte		N03   , Bn5 
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W01
	.byte		        c_v-33
	.byte	W03
	.byte		        c_v+31
	.byte		N03   , Bn5 , v020
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W01
	.byte		        c_v-33
	.byte	W04
	.byte	FINE

@******************************************************@
	.align	2

se_w179:
	.byte	2	@ NumTrks
	.byte	0	@ NumBlks
	.byte	se_w179_pri	@ Priority
	.byte	se_w179_rev	@ Reverb.

	.int	se_w179_grp

	.int	se_w179_1
	.int	se_w179_2

	.end
