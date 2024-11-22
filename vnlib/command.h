#ifndef VN_COMMAND_H
#define VN_COMMAND_H

#include "__selftypes.h"

#define SK_COMMAND_BG_MAX 255

#define SK_COMMAND_START 0
#define SK_COMMAND_BG 1 << 28
#define SK_COMMAND_BGM 1 << 29
#define SK_COMMAND_TXT 1 << 30

#define SK_COMMAND_END 255

#define SK_COMMAND_SET_BG(bgId) (SK_COMMAND_BG | (bgId)) 
#define SK_COMMAND_SET_BGM(bgmId) (SK_COMMAND_BGM | (bgmId))
#define SK_COMMAND_SET_TXT(txtId) (SK_COMMAND_TXT | (txtId))

extern void Command_Process(u32 command);

#endif