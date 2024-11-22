#ifndef VN_AUDIO_H
#define VN_AUDIO_H

#include "__selftypes.h"

typedef enum audio_type {
    AUDIO_TYPE_BGM,
    AUDIO_TYPE_SFX,
    AUDIO_TYPE_VOICE,
    AUDIO_TYPE_NUM,
} Audio_Type;

extern void Audio_Init();
extern void Audio_LoadAudio(u8 type, u16 resourceId);

#endif