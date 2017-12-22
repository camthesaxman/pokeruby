#include "global.h"
#include "rom_8077ABC.h"
#include "trig.h"
#include "battle_anim.h"
#include "sound.h"

extern s16 gBattleAnimArgs[];
extern u8 gBattleAnimBankAttacker;
extern u8 gBattleAnimBankTarget;

// heart_1 (a floating heart in a wave pattern upward.)
// Used in Charm, Covet, and when a Pokemon is infatuated.

void sub_80D1C80(struct Sprite* sprite)
{
    if (++sprite->data[0] == 1)
        sub_80787B0(sprite, 0);

    sprite->pos2.x = Sin(sprite->data[1], 8);
    sprite->pos2.y = sprite->data[2] >> 8;
    sprite->data[1] = (sprite->data[1] + 7) & 0xFF;
    sprite->data[2] -= 0x80;
    if (sprite->data[0] == 0x3C)
        move_anim_8072740(sprite);
}
