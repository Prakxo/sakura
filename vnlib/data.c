#include "data.h"

#ifdef TARGET_PC
#include <stdlib.h>
#endif

#include "__macros.h"

extern u32 Data_DecompressData(void** dst, void* src, u32 preSize);


void Data_DMAGetRes(void** ptr, u8 resourceType){
    Dmadata* data = &dmadata[resourceType];

    if(data->compressed == TRUE){
        void* out;
        //u32 size = Data_DecompressData(&out, data->ptr, data->len);

    }
    else{
        *ptr = data->ptr;
    }
}