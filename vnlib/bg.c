#include "bg.h"
#include "gfx.h"
#include "__macros.h"

#ifdef TARGET_PC
#include "string.h"
#endif

BOOL bgChanged = FALSE;

void Bg_Add(u16 resourceId){
    u32 size; 
    u8* bg = load_image(resourceId, &size);
    
    bgChanged = TRUE;

    ASSERT(size >= ARRAY_COUNTU(bgBuffer));

    memcpy(bgBuffer, bg, size);

    free(bg);
}
