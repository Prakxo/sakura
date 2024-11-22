#include "command.h"
#include "script.h"
#include "data.h"

#ifdef TARGET_PC
#include <stdlib.h>
#include <stdio.h>
#endif

u32* currentScript;

void Script_Init(){
    currentScript = malloc(sizeof(u32*));
}

void Script_Add(u16 resourceId){
    Data_DMAGetRes((void**)&currentScript, NULL, resourceId);
}

void Script_Dt(){
    free(currentScript);
}

void Script_Start(){
    u32* script = currentScript;

    while(*script != SK_COMMAND_END){

        Command_Process(*script);

        script++;
    }
}
