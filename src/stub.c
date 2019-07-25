#include "global.h"

#include <stdio.h>

#define STUB_FUNC(func) func { puts("function \"" #func "\" is a stub"); }
#define STUB_FUNC_QUIET(func) func {}

extern struct Unk03005E20;
extern struct UnkPokenav11;

STUB_FUNC(void sub_80D3B60(u8 taskId))
STUB_FUNC(void AnimTask_CreateSurfWave(u8 taskId))
STUB_FUNC(void sub_80D3D68(u8 taskId))
STUB_FUNC(void sub_8106630(u32 arg0))
STUB_FUNC(void sub_80FD1C8(u16 arg0))
STUB_FUNC(void sub_80FD8CC(struct Unk03005E20 * a0))
STUB_FUNC(void unref_sub_8113B50(u8 *a, u8 *b))
STUB_FUNC(void unref_sub_81143CC())
STUB_FUNC(void sub_8114E48())
STUB_FUNC(void Draw10000Sprite(u8 var1, u8 var2, int var3))
STUB_FUNC(void sub_80F5688(u16 r6[66][2], struct UnkPokenav11 * r5, struct UnkPokenav11 * sp0, u8 r9, u16 r7[66][2]))
STUB_FUNC(void sub_80ED858())
STUB_FUNC(void sub_80B9C6C(u8 *a, u32 b, u8 c, void *d))
STUB_FUNC(bool8 TrainerCard_ScaleDownFlipAnimation(struct Task *task))
STUB_FUNC(bool8 TrainerCard_ScaleUpFlipAnimation(struct Task *task))


// Stuff that really needs to be implemented
STUB_FUNC(void MusicPlayerJumpTableCopy(void))
STUB_FUNC(void TrackStop())
STUB_FUNC(void MPlayMain())
STUB_FUNC(void umul3232H32())
STUB_FUNC(void gNumMusicPlayers())
STUB_FUNC(void gMaxLines())
STUB_FUNC(void ply_lfos())
STUB_FUNC(void ply_mod())
STUB_FUNC(void ply_endtie())
STUB_FUNC(void ply_note())
STUB_FUNC(void MPlayJumpTableCopy())
STUB_FUNC(void ply_fine())
STUB_FUNC(void ply_goto())
STUB_FUNC(void ply_patt())
STUB_FUNC(void ply_pend())
STUB_FUNC(void ply_rept())
STUB_FUNC(void ply_prio())
STUB_FUNC(void ply_tempo())
STUB_FUNC(void ply_keysh())
STUB_FUNC(void ply_voice())
STUB_FUNC(void ply_vol())
STUB_FUNC(void ply_pan())
STUB_FUNC(void ply_bend())
STUB_FUNC(void ply_bendr())
STUB_FUNC(void ply_lfodl())
STUB_FUNC(void ply_modt())
STUB_FUNC(void ply_tune())
STUB_FUNC(void ply_port())
STUB_FUNC(void RealClearChain())
STUB_FUNC(void SoundMainBTM())
STUB_FUNC(void SoundMainRAM())

STUB_FUNC(void BgAffineSet(struct BgAffineSrcData *src, struct BgAffineDstData *dest, s32 count))
STUB_FUNC(void ObjAffineSet(struct ObjAffineSrcData *src, void *dest, s32 count, s32 offset))
STUB_FUNC(void RegisterRamReset(u32 resetFlags))
STUB_FUNC(void IntrMain())
STUB_FUNC(u16 ArcTan2(s16 x, s16 y))
STUB_FUNC(void Start())


// Stuff that really needs to be implemented
STUB_FUNC(void CpuFastSet(const void *src, void *dest, u32 control))
STUB_FUNC(void RLUnCompWram(const void *src, void *dest))
STUB_FUNC(void RLUnCompVram(const void *src, void *dest))
//STUB_FUNC(void DmaSet())
STUB_FUNC(u16 Sqrt(u32 num))
STUB_FUNC(void DmaSet(int dmaNum, const void *src, void *dest, u32 control))

// Stuff that I don't care about right now.
STUB_FUNC_QUIET(void m4aSoundVSync())
STUB_FUNC_QUIET(void SoundMain())
STUB_FUNC_QUIET(void GameCubeMultiBoot_HandleSerialInterrupt())
STUB_FUNC_QUIET(void GameCubeMultiBoot_Main())
STUB_FUNC_QUIET(void GameCubeMultiBoot_Init())
STUB_FUNC_QUIET(void GameCubeMultiBoot_Quit())
STUB_FUNC_QUIET(void GameCubeMultiBoot_ExecuteProgram())
