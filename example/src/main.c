#include "example/include/main.h"
#include "example/include/macros.h"
#include "vnlib/VNLIB.h"
#ifdef TARGET_PC
#include <stdio.h> 
#endif

#ifdef DEBUG
BOOL debug = TRUE;
#else
BOOL debug = FALSE;
#endif


int main(int argc, char** argv){

    #ifdef TARGET_PC
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    #endif

    Audio_Init();
    Txt_Init();
    Script_Init();

    Script_Add(TEST_SCRIPT_1);

    Script_Start();
}