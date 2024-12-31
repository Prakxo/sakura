#include "bg.h"
#include "gfx.h"

#ifdef TARGET_PC
#include "string.h"
#endif

void Bg_Add(u16 resourceId){
    u32 size; 
    u8* bg = load_image(resourceId, &size);

    memcpy(bgBuffer, bg, size);

    free(bg);
}
