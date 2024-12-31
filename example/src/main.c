#include "example/include/main.h"
#include "example/include/macros.h"

#include "vnlib/VNLIB.h"

#ifdef TARGET_PC
#include <stdio.h> 
#include <unistd.h>
#include <signal.h>
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
    Gfx_Init();
    Txt_Init();
    Script_Init();

    #ifdef TARGET_PC
    {
        pid_t pid = fork();

    if(pid == 0){
        Graph_Init();
    }
    else{
    #endif

    Script_Add(TEST_SCRIPT_1);

    Script_Start();

    #ifdef TARGET_PC
    }

        kill(pid, 9);
    }
    #endif
}
