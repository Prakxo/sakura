#include "gfx_pc.h"
#include "gfx.h"
#include "vnlib/data.h"
#include "__macros.h"
#include "lib/stb_image.h"
#include <SDL2/SDL_error.h>


SDL_Renderer* renderer;
SDL_Window* window;

static u8* __load_image(u8* src, u32 len){
    int x;
    int y;
    int ch;

    return stbi_load_from_memory(src, len, &x, &y, &ch, 4);
}


u8* load_image(u16 resourceId, u32* size){
    u8* data;
    u32 len;

    GET_DMA_RES((void**)&data, &len, resourceId);
    
    if(size != NULL){
        *size = len;
    }

    return __load_image(data, len);
}   

void render_bg(){
    SDL_Texture* bgTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, SCREEN_HEIGHT, SCREEN_WIDTH);

    if(bgTex == NULL){
        puts("bgTex null!");
        return;
    }


    {
        s32 err = SDL_UpdateTexture(bgTex, NULL, bgBuffer, SCREEN_WIDTH * 4);

        err != 0 ? puts(SDL_GetError()) : 0;
    }


    SDL_RenderCopy(renderer, bgTex, NULL,NULL);

}

void Graph_Init(){
    SDL_Event e;
    u8 exit = TRUE;
    
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(SCREEN_HEIGHT,SCREEN_WIDTH, 0, &window, &renderer);

    while(exit){
        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    exit = 0;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);

        SDL_RenderClear(renderer);

        render_bg();

        SDL_RenderPresent(renderer);

    }
}