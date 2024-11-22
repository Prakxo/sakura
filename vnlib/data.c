#include "data.h"

#ifdef TARGET_PC
#include <stdlib.h>
#endif

extern u32 Data_DecompressData(void** dst, void* src, u32 preSize);


void Data_DMAGetRes(void** ptr, u32* size, u16 resourceId){
    Dmadata* data = &dmadata[resourceId];

    if(size != NULL){
        *size = data->len;
    }

    if(data->compressed == TRUE){
        void* out;
        //u32 size = Data_DecompressData(&out, data->ptr, data->len);

    }
    else{
        *ptr = data->ptr;
    }
}