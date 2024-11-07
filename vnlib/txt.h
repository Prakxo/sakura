#ifndef TXT_H
#define TXT_H

#include "__selftypes.h"

#define CONTROL_CHAR_TXT_COMMAND '\x7C'

// Admits 2 arguments (spriteID, x)
#define LOADSPC_TXT_COMMAND 0x21

// Admits 3 arguments (spriteID, x, fadeRate)
#define LOADSP_TXT_COMMAND 0x22

// No arguments
#define END_TXT_COMMAND 0x43

// No arguments
#define ENDTXT_TXT_COMMAND 0x72

#endif