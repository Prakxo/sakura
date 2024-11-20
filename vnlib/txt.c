#include "txt.h"
#include "sprite.h"
#include "audio.h"

#ifdef TARGET_PC
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <termios.h>
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

#define TXT_TXTBOX_MAX_LINE 4

#define TXT_TXTBOX_MAXCHAR_LINE 60

#define TXT_TXTBOX_BUFFER TXT_TXTBOX_MAX_LINE * TXT_TXTBOX_MAXCHAR_LINE

typedef struct txt_txtbox_current_s {
    char data[TXT_TXTBOX_BUFFER];
    u32 current_line;
    u32 txtbox_id;
    BOOL exists;
}Txt_TxtBox;

Txt_TxtBox txt_txtbox_current= {{0}, 0,0,FALSE};
Txt_TxtBox txt_txtbox_old = {{0}, 0,0,FALSE};

Txt_Script* txt_scripts;
BOOL txt_initialised = FALSE;
u32 txt_num;
u32 current_txt_script;
u32 current_txt_script_len;
u32 current_txt_script_txtbox_ctr;

Txt_TxtBox_Status txt_txtbox_current_status = TXT_TXTBOX_NONE;

void Txt_Init() {
    txt_scripts = (Txt_Script*)malloc(txt_num * sizeof(Txt_Script));
    current_txt_script = 0;
    current_txt_script_len = 0;
    current_txt_script_txtbox_ctr = 0; // Invalid txtbox_id
}

void Txt_Add(u8* script, u32 len) {
    ASSERT(current_txt_script == txt_num);

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

static inline void Txt_ExecuteCommon(char* buf, u8* arg1, u16* arg2) {
    int i = 1;

    *arg1 = buf[i++];

#ifdef DEBUG
    printf("arg1 : %d\n", *arg1);
#endif

    i++; // skip delim

    Txt_ReadUnsignedShort(buf, i, arg2);

#ifdef DEBUG
    printf("arg2 : %d\n", *arg2);
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

            Txt_ExecuteCommon(buf, &id, &x);

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

            Txt_ExecuteCommon(buf, &id, &x);

            // offs = value (1 char) + comma count (argc-1) + type sizes
            fadeRate = buf[i + LOADSP_ARGC - 1 + sizeof(u8) + sizeof(u16)];

#ifdef DEBUG
            printf("fadeRate : %d\n", fadeRate);
#endif

            Sprite_LoadSprite(id, x, fadeRate);

        } break;
        case AUDIO_TXT_COMMAND: {
            u16 audioId;
            u8 type;

#ifdef DEBUG
            puts("AUDIO Command!");
#endif

            Txt_ExecuteCommon(buf, &type, &audioId);

            Audio_LoadAudio(type, audioId);

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

static struct termios inline Txt_BlockUserInput(){
    struct termios pre;
    struct termios new;
    int ret = tcgetattr(STDIN_FILENO, &pre);

    ASSERT(ret == -1);

    new = pre;

    // disable echoing user input get fetching
    new.c_lflag &= ~ECHO;

    ret = tcsetattr(STDIN_FILENO, TCSAFLUSH, &new);

    ASSERT(ret == -1);

    return pre;
}

static void inline Txt_ReleaseUserInput(struct termios* t){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, t);
}

void Txt_txtbox_wait_Input() {
#ifdef TARGET_PC
    char* ch = malloc(sizeof(char*));
    int num = 0;
    struct termios t = Txt_BlockUserInput();
    
    while (num != 1 && *ch != '\n') {
        num = fscanf(stdin, "%c", ch);
        putchar('\n');
    }

    Txt_ReleaseUserInput(&t);
    free(ch);
#endif
}

Txt_TxtBox* Txt_GetCurrentTxtBox(){
    return &txt_txtbox_current;
}

void Txt_txtbox_init(){
    bzero(txt_txtbox_current.data, TXT_TXTBOX_BUFFER);
    txt_txtbox_current.current_line = 0;
    txt_txtbox_current.exists = TRUE;
    txt_txtbox_current.txtbox_id = ++current_txt_script_txtbox_ctr;
}

void Txt_txtbox_clear(){
    txt_txtbox_old = txt_txtbox_current;
    bzero(txt_txtbox_current.data, TXT_TXTBOX_BUFFER);
    txt_txtbox_current.exists = FALSE;
}

void Txt_txtbox_write_data(char c, int pos){
    if(Txt_GetCurrentTxtBox()->exists == FALSE){
        Txt_txtbox_init();
    }

    if(c == '\n'){
        txt_txtbox_current.current_line++;
    }

    ASSERT(txt_txtbox_current.current_line == TXT_TXTBOX_MAX_LINE && c == '\n');

    txt_txtbox_current.data[pos] = c;
}

void Txt_txtbox_display(){
    int i = 0;
    char c = txt_txtbox_current.data[i];

    #ifdef DEBUG
    printf("textbox id : %ld\n", Txt_GetCurrentTxtBox()->txtbox_id);
    #endif

    for(;c != '\0'; i++){
        c = txt_txtbox_current.data[i];
        #ifdef TARGET_PC
        putchar(c);
        usleep(50000);
        #endif
        
    }
}


int Txt_Play(u8* script) {
    int i = 0;
    int txtboxPos = 0;
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
            Txt_txtbox_write_data(c, txtboxPos);
            i++;
            txtboxPos++;
        }

        if (txt_txtbox_current_status == TXT_TXTBOX_WAIT) {
#ifdef TARGET_PC
            struct termios t = Txt_BlockUserInput();
#endif
            Txt_txtbox_display();
#ifdef TARGET_PC
            Txt_ReleaseUserInput(&t);
#endif

            Txt_txtbox_wait_Input();

            txt_txtbox_current_status = TXT_TXTBOX_NONE;
            txtboxPos = 0;
            Txt_txtbox_clear();
        }
    }

    return TXT_STATUS_END;
}

void Txt_Start(u8 txtId) {
    u8* script;

    ASSERT(txtId > txt_num);

    script = txt_scripts[txtId].txt_script;
    current_txt_script_len = txt_scripts[txtId].len;

    while (Txt_Play(script) != TXT_STATUS_END)
        ;
}
