#include "data.h"
#include "decompress.h"

#ifdef TARGET_PC
#include <stdlib.h>
#endif

void Data_DMAGetRes(void** ptr, u32* size, u16 resourceId){
    Dmadata* data = &dmadata[resourceId];

    if(size != NULL){
        *size = data->len;
    }

    if(data->compressed == TRUE){
        void* out;
        u32 size = Data_DecompressData(&out, data->ptr, data->len);

        #ifdef DEBUG
            {
                char buf[20];

                snprintf(buf, "%s size decomp", size);

                puts(buf);
            }
        #endif
    }
    else{
        *ptr = data->ptr;
    }
}