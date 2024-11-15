#include "example/include/main.h"
#include "vnlib/VNLIB.h"
#include "example/include/macros.h"
#ifdef TARGET_PC
#include <stdio.h> 
#endif

u8 script1_txt[] = {
    #include "example/data/script1_proc.txt.bin"
};

const u32 script1_txt_len = ARRAY_COUNTU(script1_txt);

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
    #ifdef TARGET_PC
    char buf[100];
    
    sprintf(buf, "script = %p\tsize=%ld", script, size);

    puts(buf);
    #endif
    #endif
}

void Add_TxtScripts(){
    static u8* txtscript[] = {
        script1_txt,
    };
    static u32 txtsizes[] = {
        script1_txt_len,
    };

    int i;

    for(i = 0; i < SK_TXT_MAX; i++){
        Txt_Add(txtscript[i], txtsizes[i]);
    }

}

int main(int argc, char** argv){

    #ifdef TARGET_PC
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    #endif


    txt_num = SK_TXT_MAX;

    Txt_Init();

    Script_Init(SK_TEST_NUM);

    Add_TxtScripts();

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