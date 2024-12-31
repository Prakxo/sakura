#include "macros.h"
#include "vnlib/VNLIB.h"

#include "main.h"

u8 script1_txt[] = {
    #include "example/data/script1_proc.txt.bin"
};

u8 script1_txt_compressed[] = {
    #include "example/data/script1.txt.comp.bin"
};

u8 bg_test_comp[] = {
    #include "example/data/chisburgirwhat.png.bin"
};

u32 SK_script_test0[] = {
    SK_COMMAND_START,
    SK_COMMAND_END
};

u32 SK_script_test1[] = {
    SK_COMMAND_START,
    SK_COMMAND_SET_BG(BG_TEST),
    SK_COMMAND_SET_BGM(NULL_DATA),
    SK_COMMAND_SET_TXT(TXT_SCRIPT_TEST_COMPRESSED),
    SK_COMMAND_END,
}; 


Dmadata dmadata[] = {
    {NULL},
    ENTRY_DMA(script1_txt, ARRAY_COUNTU(script1_txt), FALSE),
    ENTRY_DMA(script1_txt_compressed, ARRAY_COUNTU(script1_txt_compressed), TRUE),
    ENTRY_DMA((u8*)SK_script_test0, ARRAY_COUNTU(SK_script_test0), FALSE),
    ENTRY_DMA((u8*)SK_script_test1, ARRAY_COUNTU(SK_script_test1), FALSE),
    ENTRY_DMA((u8*)bg_test_comp, ARRAY_COUNTU(bg_test_comp), FALSE),
};