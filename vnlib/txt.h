#ifndef VN_TXT_H
#define VN_TXT_H

#include "__selftypes.h"

#define CONTROL_CHAR_TXT_COMMAND '\x7C'

// Admits 2 arguments (resourceID, x)
#define LOADSPC_TXT_COMMAND 0x21

// Admits 3 arguments (resourceID, x, fadeRate)
#define LOADSP_TXT_COMMAND 0x22

// Admits 1 argument (type, resourceID)
#define AUDIO_TXT_COMMAND 0x23

// No arguments
#define END_TXT_COMMAND 0x43

// No arguments
#define ENDTXT_TXT_COMMAND 0x72

#define TXT_COMMAND_MAX_LEN 20

extern u32 txt_num;

extern void Txt_Init();
extern void Txt_Add(u16 resourceId);
extern void Txt_Start();

#endif