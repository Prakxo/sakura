#include "command.h"
#include <stdio.h>
#include "txt.h"

void Command_Process(u32 command){

    if(command & SK_COMMAND_BG){
        char buf[8];
        u8 bgNo = command & 0xFF;

        sprintf(buf, "BG=%d", bgNo);

        puts(buf);
    }

    if(command & SK_COMMAND_BGM){
        char buf[8];
        u8 bgmNo = command & 0xFF;

        sprintf(buf, "BGM=%d", bgmNo);

        puts(buf);
    }

    if(command & SK_COMMAND_TXT){
        char buf[8];
        u8 txtNo = command & 0xFF;

        #ifdef DEBUG
        sprintf(buf, "TXT=%d", txtNo);

        puts(buf);
        #endif

        Txt_Start(txtNo);
    }
}