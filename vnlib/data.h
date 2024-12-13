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

#ifndef DEBUG
extern void Data_DMAGetRes(void** ptr, u32* size, u16 resourceId);
#define GET_DMA_RES(ptr, size, resourceId) \
    Data_DMAGetRes(ptr, size, resourceId)
#else
extern void Data_DMAGetRes(void** ptr, u32* size, u16 resourceId, const char* file, u32 line);
#define GET_DMA_RES(ptr, size, resourceId) \
    Data_DMAGetRes(ptr, size, resourceId, __FILE__, __LINE__)
#endif

#endif