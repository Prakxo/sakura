#include "txt.h"
#include "sprite.h"
#include "audio.h"

#ifdef TARGET_PC
#include <stdlib.h>
#include <stdio.h>
#endif

#include "__macros.h"

typedef enum txt_play_status {
    TXT_STATUS_ERROR = -1,
    TXT_STATUS_END,
    TXT_STATUS_PLAY,
    TXT_STATUS_NUM,
} Txt_Play_Status;

typedef enum txt_textbox_status {
    TXT_TXTBOX_NONE,
    TXT_TXTBOX_WAIT,
    TXT_TXTBOX_CONTINUTE,
    TXT_TXTBOX_END,
    TXT_TXTBOX_NUM,
} Txt_TxtBox_Status;

typedef enum _txt_command {
    _TXT_COMMAND_LOADSPC,
    _TXT_COMMAND_LOADSP,
    _TXT_COMMAND_AUDIO,
    _TXT_COMMAND_END,
    _TXT_COMMAND_ENDTXT,
    _TXT_COMMAND_NUM,
} _Txt_Command;

typedef struct txt_script_s {
    u8* txt_script;
    u32 len;
} Txt_Script;

typedef struct txt_command_arg_s {
    u32 value;
    u8* sizes;
    u8 argc;
} Txt_Command_Arg;

Txt_Script* txt_scripts;
int txt_initialised = FALSE;
u32 txt_num;
u32 current_txt_script;
u32 current_txt_script_len;

u32 txt_txtbox_current_status = TXT_TXTBOX_NONE;

void Txt_Init() {
    txt_scripts = (Txt_Script*)malloc(txt_num * sizeof(Txt_Script));
    current_txt_script = 0;
    current_txt_script_len = 0;
}

void Txt_Add(u8* script, u32 len) {
    #ifdef DEBUG
    ASSERT(current_txt_script == txt_num);
    #endif
    
    txt_scripts[current_txt_script].txt_script = script;
    txt_scripts[current_txt_script].len = len;

    current_txt_script++;
}

static inline void Txt_ReadUnsignedShort(char* buf, int pos, u16* value) {
    if (buf[pos] != 0) {
        *value = buf[pos++] << 2;
        *value |= buf[pos];
    } else {
        *value = buf[++pos];
    }
}

static inline void Txt_ExecuteLOADSPCommon(char* buf, u8* id, u16* x) {
    int i = 1;

    *id = buf[i++];

#ifdef DEBUG
    printf("sprite ID : %d\n", *id);
#endif

    i++; // skip delim

    Txt_ReadUnsignedShort(buf, i, x);

#ifdef DEBUG
    printf("x : %d\n", *x);
#endif
}

#define LOADSP_ARGC 3

int Txt_ExecuteCommand(char* buf) {
    char c = *buf;

    switch (c) {
        case LOADSPC_TXT_COMMAND: {

#ifdef DEBUG
            puts("LOADSPC Command!");
#endif
            u8 id;
            u16 x;

            Txt_ExecuteLOADSPCommon(buf, &id, &x);

            Sprite_LoadSpriteContinuous(id, x);

        } break;
        case LOADSP_TXT_COMMAND: {
#ifdef DEBUG
            puts("LOADSP Command!");
#endif
            u8 id;
            u16 x;
            u8 fadeRate;
            int i = 1;

            Txt_ExecuteLOADSPCommon(buf, &id, &x);

            // offs = value (1 char) + comma count (argc-1) + type sizes
            fadeRate = buf[i + LOADSP_ARGC - 1 + sizeof(u8) + sizeof(u16)];

#ifdef DEBUG
            printf("fadeRate : %d\n", fadeRate);
#endif

            Sprite_LoadSprite(id, x, fadeRate);

        } break;
        case AUDIO_TXT_COMMAND: {
            int i = 1;
            u16 audioId;

#ifdef DEBUG
            puts("AUDIO Command!");
#endif

            Txt_ReadUnsignedShort(buf, i, &audioId);

#ifdef DEBUG
            printf("audioId : %d\n", audioId);
#endif

            Audio_LoadAudio(audioId);

        } break;
        case END_TXT_COMMAND:
            txt_txtbox_current_status = TXT_TXTBOX_WAIT;
            break;
        case ENDTXT_TXT_COMMAND:
            return TXT_STATUS_END;
            break;

        default:
#ifdef DEBUG
            puts("Invalid Command!");
#endif
            return TXT_STATUS_ERROR;
    }

    return TXT_STATUS_PLAY;
}

int Txt_Play(u8* script) {
    int i = 0;
    int status;

    while (i <= current_txt_script_len) {
        char c = script[i];

        if (c == CONTROL_CHAR_TXT_COMMAND) {
            char* buf = calloc(0, TXT_COMMAND_MAX_LEN);
            int j = 0;

            c = script[++i];

            while (c != CONTROL_CHAR_TXT_COMMAND) {
                buf[j++] = script[i];
                c = script[++i];
            }

            status = Txt_ExecuteCommand(buf);

            i++;
        } else {
            #ifdef TARGET_PC
            putchar(c);
            #endif
            i++;
        }

        if(txt_txtbox_current_status == TXT_TXTBOX_WAIT){
            char* ch = malloc(sizeof(char*));

            #ifdef TARGET_PC
            int num = 0;

            while(num != 1){
                num = fscanf(stdin, "%c", ch);
            }

            #endif
            free(ch);
            txt_txtbox_current_status = TXT_TXTBOX_NONE;
        }
    }

    return TXT_STATUS_END;
}

void Txt_Start(u8 txtId) {
    u8* script;

    #ifdef DEBUG
    ASSERT(txtId > txt_num);
    #endif

    script = txt_scripts[txtId].txt_script;
    current_txt_script_len = txt_scripts[txtId].len;

    while (Txt_Play(script) != TXT_STATUS_END)
        ;
}
