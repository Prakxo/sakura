#define MINIAUDIO_IMPLEMENTATION
#include "lib/miniaudio.h"

#ifdef TARGET_PC
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#endif

#include "audio.h"
#include "data.h"

#define VN_AUDIO_SAMPLE_RATE 44100
#define VN_AUDIO_CHANNEL_COUNT 4

#define VN_AUDIO_BGM_BUF 4096
#define VN_AUDIO_SFX_BUF 1024
#define VN_AUDIO_VOICE_BUF 2048

#define VN_AUDIO_HEAP_SIZE VN_AUDIO_BGM_BUF + VN_AUDIO_SFX_BUF + VN_AUDIO_VOICE_BUF

typedef struct audio_heap_s {
    u8 audio_bgm_buf[VN_AUDIO_BGM_BUF];
    u8 audio_sfx_buf[VN_AUDIO_SFX_BUF];
    u8 audio_voice_buf[VN_AUDIO_VOICE_BUF];
} Audio_Heap;

Audio_Heap heap;
ma_decoder_config decoder_conf;
ma_device_config device_conf;
ma_decoder* decoders;
ma_device device;

ma_event stop_event;

#define AUDIO_ERR_DECODER_ALL(result)              \
    {                                              \
        if ((result) != MA_SUCCESS) {              \
            int i;                                 \
            for (i = 0; i < AUDIO_TYPE_NUM; i++) { \
                ma_decoder_uninit(&decoders[i]);   \
            }                                      \
            free(decoders);                        \
        }                                          \
    }

void Audio_Load_Buf(u8* ptr, u32 size, u8 type) {
    ma_result res = ma_decoder_init_memory(ptr, size, &decoder_conf, &decoders[type]);

    AUDIO_ERR_DECODER_ALL(res);
}

void Audio_Init_Device() {
    int i;
    ma_result res;

    device_conf = ma_device_config_init(ma_device_type_playback);
    device_conf.playback.format = ma_format_f32;
    device_conf.playback.channels = VN_AUDIO_CHANNEL_COUNT;
    device_conf.sampleRate = VN_AUDIO_SAMPLE_RATE;
    device_conf.dataCallback = NULL;
    device_conf.pUserData = NULL;

    res = ma_device_init(NULL, &device_conf, &device);

    AUDIO_ERR_DECODER_ALL(res);
}

void Audio_Init() {
    bzero(&heap, sizeof(Audio_Heap));
    decoders = malloc(sizeof(ma_decoder) * AUDIO_TYPE_NUM);

    decoder_conf = ma_decoder_config_init(ma_format_f32, VN_AUDIO_CHANNEL_COUNT, VN_AUDIO_SAMPLE_RATE);
}

void Audio_Play() {
    int i;
    ma_result res;

    ma_event_init(&stop_event);

    res = ma_device_start(&device);

    AUDIO_ERR_DECODER_ALL(res);

    ma_event_wait(&stop_event);
}

void Audio_LoadAudio(u8 type, u16 resourceId) {
    u8* data = NULL;
    u8* buf;
    u32 size;
    int i = 0;

    GET_DMA_RES((void**)&data, NULL, resourceId);

    switch(type){
        case AUDIO_TYPE_BGM:
            buf = heap.audio_bgm_buf; 
            size = VN_AUDIO_BGM_BUF;
            break;
        case AUDIO_TYPE_SFX:
            buf = heap.audio_sfx_buf; 
            size = VN_AUDIO_SFX_BUF;
            break;
        case AUDIO_TYPE_VOICE:
            buf = heap.audio_voice_buf; 
            size = VN_AUDIO_VOICE_BUF;
            break;
        
        default:
            buf = NULL;
            size = 0;
            break;
    }

    if(data != NULL && buf != NULL){
        while(*data != '\0'){
            buf[i++] = *data++;
        }
        Audio_Load_Buf(buf, size, type);
    }
    else{
        #ifdef TARGET_PC
        #ifdef DEBUG
        puts("DMA DATA is NULL\tNot Loading!!");
        #endif
        #endif
    }

}