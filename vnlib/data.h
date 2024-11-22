#ifndef VNLIB_DATA_H
#define VNLIB_DATA_H

#include "__selftypes.h"

typedef struct dma_data_s{
    u8* ptr;
    u32 len;
    u8 compressed;
}Dmadata;

#define ENTRY_DMA(name, len, compressed) \
    {name, len, compressed}\


extern Dmadata dmadata[];

extern void Data_DMAGetRes(void** ptr, u32* size, u16 resourceId);

#endif