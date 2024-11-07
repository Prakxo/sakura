#ifndef VN_SCRIPT_H
#define VN_SCRIPT_H

#include "__selftypes.h"

extern void Script_Init(u32 amount);
extern void Script_Add(u32* scriptPtr, u32 size);
extern void Script_Start(u32 scriptId);
extern void Script_PrintComm(u32 scriptId);


#endif
