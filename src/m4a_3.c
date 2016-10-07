#include "gba/m4a_internal.h"

extern const u8 gCgb3Vol[];

void CgbModVol(struct CgbChannel *chan);

void CgbSound(void)
{
    struct SoundInfo *soundInfo = SOUND_INFO_PTR;
    struct CgbChannel *chan;
    register int chanNum asm("r6");
    register u8 r8 asm("r8");
    //int chanNum;
    
    if(soundInfo->c15)
        soundInfo->c15--;
    else
        soundInfo->c15 = 14;
    
    chan = soundInfo->cgbChans;
    for(chanNum = 1; chanNum <= 4; chanNum++)
    { 
        vu8 *_r2;
        vu8 *_r7;
        vu8 *_s8;
        vu8 *_s12;
        vu8 *_s16;
        u8 c15;
        //u8 r8;
        
        if(chan->sf & 0xC7)
        {
            switch(chanNum)
            {
                case 1:
                    _s8 = (vu8 *)REG_ADDR_NR10;
                    _r7 = (vu8 *)REG_ADDR_NR11;
                    _s12 = (vu8 *)REG_ADDR_NR12;
                    _s16 = (vu8 *)REG_ADDR_NR13;
                    _r2 = (vu8 *)REG_ADDR_NR14;
                    break;
                case 2:
                    _s8 = (vu8 *)REG_ADDR_NR10 + 1;
                    _r7 = (vu8 *)REG_ADDR_NR21;
                    _s12 = (vu8 *)REG_ADDR_NR22;
                    _s16 = (vu8 *)REG_ADDR_NR23;
                    _r2 = (vu8 *)REG_ADDR_NR24;
                    break;
                case 3:
                    _s8 = (vu8 *)REG_ADDR_NR30;
                    _r7 = (vu8 *)REG_ADDR_NR31;
                    _s12 = (vu8 *)REG_ADDR_NR32;
                    _s16 = (vu8 *)REG_ADDR_NR33;
                    _r2 = (vu8 *)REG_ADDR_NR34;
                    break;
                default:
                    _s8 = (vu8 *)REG_ADDR_NR30 + 1;
                    _r7 = (vu8 *)REG_ADDR_NR41;
                    _s12 = (vu8 *)REG_ADDR_NR42;
                    _s16 = (vu8 *)REG_ADDR_NR43;
                    _r2 = (vu8 *)REG_ADDR_NR44;
                    break;
            }
            //_081DEB30
            c15 = soundInfo->c15;
            
            if(chan->sf & 0x80)
            {
                if(chan->sf & 0x40)
                    goto _081DEC4A;
                
                chan->sf = 3;
                chan->mo = 3;
                CgbModVol(chan);
                switch(chanNum)
                {
                    case 1:
                        *_s8 = chan->sw;
                    case 2:
                        *_r7 = (chan->wp << 6) + (chan->le);
                        //went to _081DEBF8
                        if(chan->le)
                            chan->n4 = 0x40;
                        else
                            chan->n4 = 0;
                        break;
                    case 3:
                        if(chan->wp != chan->cp)
                        {
                            u32 *wavePattern;
                            
                            *_s8 = 0x40;
                            wavePattern = (u32 *)chan->wp;
                            REG_WAVE_RAM0 = wavePattern[0];
                            REG_WAVE_RAM1 = wavePattern[1];
                            REG_WAVE_RAM2 = wavePattern[2];
                            REG_WAVE_RAM3 = wavePattern[3];
                            chan->cp = (u32)wavePattern;
                        }
                        *_s8 = chan->sf & 0x40;
                        *_r7 = chan->le;
                        if(chan->le)
                            chan->n4 = 0xC0;
                        else
                            chan->n4 = -0x80;
                        break;
                    default:
                        *_r7 = chan->le;
                        *_s16 = chan->wp * 8;
                        if(chan->le)
                            chan->n4 = 0x40;
                        else
                            chan->n4 = 0;
                        //break;
                }
                chan->ec = chan->at;
                //more stuff here
                //jump to other places
            }
            
            //Well, here's a big ball of spaghetti!
            
            //_081DEC26
            if(!(chan->sf & 4))
                goto _081DEC58;
            chan->echoLength--;
            
            
            //more stuff here
          _081DEC4A:
            CgbOscOff(chanNum);
            chan->sf = 0;
            goto _081DEE9C;
            
          _081DEC58:
            //_081DEC58
            if((chan->sf & 0x40) && (chan->sf & 0x3))
            {
                chan->sf &= 0xFC;
                chan->ec = chan->re;
                if(chan->ec & 0xFF)
                {
                    chan->mo |= 1;
                }
            }
            //_081DEC98
            for(; c15 == 0; c15--)
            {
                if(chan->ec == 0)
                {
                    if(chanNum == 3)
                    {
                        chan->mo |= 1;
                    }
                    //_081DECAA
                    CgbModVol(chan);
                    if(!(chan->sf & 3))
                    {
                        chan->ev--;
                        if(chan->ev <= 0)
                        {
                            //_081DECCA
                          _081DECCA:
                            chan->ev = (chan->echoVolume * chan->eg) / 256;
                            if(!chan->ev)
                                goto _081DEC4A;
                            chan->sf |= 4;
                            chan->mo |= 1;
                            if(chanNum == 3)
                                break;
                            else
                            {
                                r8 = 8;
                                break;
                            }
                        }
                        //_081DECFA
                        //goto _081DED8A
                        chan->ec = chan->re;
                        continue;
                    }
                    //_081DECFE
                    if(chan->sf == 1)
                    {
                        //_081DED02
                        chan->ev = chan->sg;
                        continue;
                    }
                    else if(chan->sf == 2)
                    {
                        chan->ev--;
                        if(chan->ev <= chan->sg)
                        {
                            //_081DED22
                          _081DED22:
                            if(chan->su == 0)
                            {
                                chan->sf &= 0xFC;
                                goto _081DECCA;
                            }
                            else
                            {
                                //_081DED32
                                chan->sf--;
                                chan->mo |= 1;
                                if(chanNum == 3)
                                    continue;   //goto _081DED02
                                else
                                {
                                    r8 = 8;
                                    continue;   //r8 = 8, goto _081DED02
                                }
                            }
                        }
                        else
                        {
                            //_081DED4A
                            chan->ec = chan->de;    //goto _081DED8A
                        }
                    }
                    //_081DED4E
                    chan->ev++;
                    //Not exactly sure how BCC behaves with CMP
                    if(chan->ev < chan->eg)
                    {
                        //_081DED5E
                        chan->sf--;
                        chan->ec = chan->de;
                        if(chan->de == 0)
                            goto _081DED22;
                        chan->mo |= 1;
                        chan->ev = chan->eg;
                        if(chanNum != 3)
                            r8 = chan->de;
                        //Hmm...
                    }
                    //_081DED88
                }
                //_081DED8C
                /*
                chan->ec--;
                if(c15)
                    break;
                c15--;
                */
            }
            
          _081DED9E:
            //_081DED9E
            if(chan->mo & 2)
            {
                if(chanNum <= 3 && (chan->ty & 8))
                {
                    int regSoundBiasH = REG_SOUNDBIAS_H;
                    
                    if(regSoundBiasH <= 0x3F)
                    {
                        chan->fr = (chan->fr + 2) & 0x000007fc;
                    }
                    else
                    {
                        //_081DEDD0
                        if(regSoundBiasH <= 0x7F)
                            chan->fr = (chan->fr + 1) & 0x000007fe;
                    }
                    //_081DEDDA
                    //str r0, chan-fr
                }
                
                //_081DEDDE
                if(chanNum != 4)
                {
                    *_s16 = chan->fr;
                }
                else
                {
                    *_s16 = chan->fr | (*_s16 & 8);
                }
                //_081DEDFE
                
                //Umm, what the hell?
                chan->n4 = (chan->n4 & 0xC0) + ((u8 *)chan)[0x21];
                *_r2 = chan->n4;
                
            }
            //_081DEE16
            if(chan->mo & 1)
            {
                u8 unk = (REG_NR51 & ~chan->panMask) | chan->pan;
                
                REG_NR51 = unk;
                if(unk == 3)
                {
                    *_s12 = gCgb3Vol[chan->ev];
                    if(chan->n4 & 0x80)
                    {
                        *_s8 = 0x80;
                        *_r2 = chan->n4;
                        chan->n4 &= 0x7F;
                    }
                }
                else
                {
                    //_081DEE68
                    *_s12 = (chan->ev << 4) + (r8 & 0xF);
                    *_r2 = chan->n4 | 0x80;
                    if(chanNum == 1 && (*_s8 & 8))
                        *_r2 = chan->n4 | 0x80;
                }
            }
            //_081DEE9C
            _081DEE9C:
            chan->mo = 0;
        }
        //_081DEEA0
        chan++;
    }
    //_081DEEAA
}