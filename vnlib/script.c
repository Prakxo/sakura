#include "command.h"
#include "script.h"

#ifdef TARGET_PC
#include <stdlib.h>
#include <stdio.h>
#endif

#include "__macros.h"

u32** scripts;
u32 scriptAmount;
u32* scriptCommandsSizes;
u32 currentScript;

void Script_Init(u32 amount){
    scripts = (u32**)malloc(sizeof(u32*) * amount);
    scriptCommandsSizes = (u32*)malloc(sizeof(u32*) * amount);

    scriptAmount = amount;
    currentScript = 0;
}

void Script_Add(u32* scriptPtr, u32 size){
    scripts[currentScript] = scriptPtr;
    scriptCommandsSizes[currentScript] = size;

    currentScript++;
}

void Script_Start(u32 scriptId){
    u32* script = scripts[scriptId];


    while(*script != SK_COMMAND_END){

        Command_Process(*script);

        script++;
    }
}

void Script_PrintComm(u32 scriptId){
    ASSERT(scriptId > scriptAmount);

    u32 size = scriptCommandsSizes[scriptId];
    u32* script = scripts[scriptId];
    s32 i;
    ASSERT(script == NULL);
    
    for(i = 0; i < size; i++){
        #ifdef TARGET_PC
        char buf[20];

        sprintf(buf, "Script %ld : %lx", scriptId, *script);
        puts(buf);

        script++;
        #endif
    }

}