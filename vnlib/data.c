#include "__macros.h"
#include "data.h"
#include "decompress.h"

#ifdef TARGET_PC
#include <stdlib.h>
#include <stdio.h>
#endif

#ifndef DEBUG
void Data_DMAGetRes(void** ptr, u32* size, u16 resourceId){
#else
void Data_DMAGetRes(void** ptr, u32* size, u16 resourceId, const char* file, u32 line){
#endif
    Dmadata* data = &dmadata[resourceId];

    if(data == NULL){
        *ptr = NULL;
        return;
    }

    if(size != NULL){
        *size = data->len;
    }

    #ifdef DEBUG
    {
        char buf[50];

        snprintf(buf, ARRAY_COUNT(buf), "compressed %s @ %s L. %ld", data->compressed == TRUE ? "TRUE" : "FALSE", file, line); 

        puts(buf);
    }
    #endif

    if(data->compressed == TRUE){
        void* out;
        u32 decompSize = Data_DecompressData(&out, data->ptr, data->len);

        #ifdef DEBUG
            {
                char buf[20];

                snprintf(buf, ARRAY_COUNT(buf), "%ld size decomp", decompSize);

                puts(buf);
            }
        #endif

        if(size != NULL){
            *size = decompSize;
        }

        *ptr = out;
    }
    else{
        *ptr = data->ptr;
    }
}