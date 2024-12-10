#include "data.h"
#include "decompress.h"

#ifdef TARGET_PC
#include <stdlib.h>
#include <stdio.h>
#endif

void Data_DMAGetRes(void** ptr, u32* size, u16 resourceId){
    Dmadata* data = &dmadata[resourceId];

    if(size != NULL){
        *size = data->len;
    }

    #ifdef DEBUG
    {
        char buf[20];

        snprintf(buf, 20, "%d compressed", data->compressed); 

        puts(buf);
    }
    #endif

    if(data->compressed == TRUE){
        void* out;
        u32 size = Data_DecompressData(&out, data->ptr, data->len);

        #ifdef DEBUG
            {
                char buf[20];

                snprintf(buf, 20, "%ld size decomp", size);

                puts(buf);
            }
        #endif

        *ptr = out;
    }
    else{
        *ptr = data->ptr;
    }
}