#ifndef VNLIB_GFX_PC_H
#define VNLIB_GFX_PC_H

#include "__selftypes.h"
#include <SDL2/SDL.h>

extern void Graph_Init(void);
extern u8* load_image(u16 resourceId, u32* size);

#endif