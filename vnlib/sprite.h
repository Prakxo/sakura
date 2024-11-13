#ifndef VN_SPRITE_H
#define VN_SPRITE_H

#include "__selftypes.h"

extern void Sprite_LoadSpriteContinuous(u8 spriteID, u16 x);
extern void Sprite_LoadSprite(u8 spriteID, u16 x, u8 fadeRate);

#endif