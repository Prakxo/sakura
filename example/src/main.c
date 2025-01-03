#include "example/include/main.h"
#include "example/include/macros.h"

#include "gfx_pc.h"
#include "vnlib/VNLIB.h"
#include <pthread.h>

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

int engine_proc(void* arg){
    Script_Start();

    return 0;
}

int main(int argc, char** argv){

    #ifdef TARGET_PC
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    #endif

    Audio_Init();
    Gfx_Init();
    Txt_Init();
    Script_Init();
    
    Script_Add(TEST_SCRIPT_1);

    engine_proc(NULL);

    Graph_Init();

}
