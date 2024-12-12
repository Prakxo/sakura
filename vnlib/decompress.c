#include "decompress.h"
#include "lib/lz4.h"
#include <string.h>

#ifdef TARGET_PC
#include <stdlib.h>
#endif

u32 Data_DecompressData(void** dst, void* src, u32 preSize){
    void* buf = malloc(16 * (1 << 10));
    void* out;
    u32 size = LZ4_decompress_safe(src, buf, preSize, 16 * (1 << 10));

    out = malloc(size);

    memcpy(out, buf, size);

    *dst = out;

    free(buf);

    return size;
}