#include "main.h"
#include "vnlib/VNLIB.h"
#include "macros.h"
#include <stdio.h> 

u32 SK_script_test0[] = {
    SK_COMMAND_START,
    SK_COMMAND_END
};

u32 SK_script_test1[] = {
    SK_COMMAND_START,
    SK_COMMAND_SET_BG(2),
    SK_COMMAND_SET_BGM(0),
    SK_COMMAND_SET_TXT(0),
    SK_COMMAND_END,
}; 


#ifdef DEBUG
BOOL debug = TRUE;
#else
BOOL debug = FALSE;
#endif


void debug_infoScript(u32* script, u32 size){
    #ifdef DEBUG
    char buf[100];
    
    sprintf(buf, "script = %p\tsize=%ld", script, size);

    puts(buf);
    #endif
}

int main(int argc, char** argv){

    Script_Init(SK_TEST_NUM);

    Script_Add(SK_script_test0, ARRAY_COUNT(SK_script_test0));
    Script_Add(SK_script_test1, ARRAY_COUNT(SK_script_test1));

    if(debug == TRUE){
        debug_infoScript(SK_script_test0, ARRAY_COUNT(SK_script_test0));
        debug_infoScript(SK_script_test1, ARRAY_COUNT(SK_script_test1)); 

        Script_PrintComm(SK_TEST_0);
        Script_PrintComm(SK_TEST_1);
    }


    Script_Start(SK_TEST_1);
}