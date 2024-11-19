#ifndef VNLIB_DATA_H
#define VNLIB_DATA_H

#include "__selftypes.h"

typedef struct dma_data_s{
    u8* ptr;
    u32 len;
}Dmadata;

#define ENTRY_DMA(name) \
    (#name)_data, (#name)_len, \


extern Dmadata dmadata[];

#endif