#include "command.h"
#include "__macros.h"

#include <stdlib.h>
#include "script.h"
#include <stdio.h>

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
    #ifdef DEBUG
    ASSERT(scriptId > scriptAmount);
    #endif

    u32 size = scriptCommandsSizes[scriptId];
    u32* script = scripts[scriptId];
    s32 i;
    #ifdef DEBUG
    ASSERT(script == NULL);
    #endif
    
    for(i = 0; i < size; i++){
        char buf[20];

        sprintf(buf, "Script %ld : %lx", scriptId, *script);
        puts(buf);

        script++;
    }

}