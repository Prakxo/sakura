#include "command.h"
#include <stdio.h>
#include "txt.h"

void Command_Process(u32 command){

    if(command & SK_COMMAND_BG){
        char buf[8];
        u8 bgNo = command & 0xFF;

        #ifdef DEBUG
        #ifdef TARGET_PC
        sprintf(buf, "BG=%d", bgNo);

        puts(buf);
        #endif
        #endif
    }

    if(command & SK_COMMAND_BGM){
        char buf[8];
        u8 bgmNo = command & 0xFF;

        #ifdef DEBUG
        #ifdef TARGET_PC
        sprintf(buf, "BGM=%d", bgmNo);

        puts(buf);
        #endif
        #endif
    }

    if(command & SK_COMMAND_TXT){
        char buf[8];
        u8 txtNo = command & 0xFF;

        #ifdef DEBUG
        #ifdef TARGET_PC
        sprintf(buf, "TXT=%d", txtNo);

        puts(buf);
        #endif
        #endif

        Txt_Start(txtNo);
    }
}