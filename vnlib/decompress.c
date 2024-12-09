#include "decompress.h"
#include "lib/lz4.h"

#ifdef TARGET_PC
#include <stdlib.h>
#endif

u32 Data_DecompressData(void** dst, void* src, u32 preSize){
    void* buf = calloc(0, 16 * (1 << 10));
    u32 size = LZ4_decompress_safe(src, buf, preSize, 16 * (1 << 10));

    *dst = realloc(buf, size);

    free(buf);

    return size;
}