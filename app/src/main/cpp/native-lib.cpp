#include <jni.h>
#include <string>
#include "SDL.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_org_libsdl_app_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

struct SBMPInfo
{
    SDL_Texture* texture;
    Uint16 w;
    Uint16 h;
} ;

/* Adapted from SDL's testspriteminimal.c */
SBMPInfo LoadBMP(const char* file, SDL_Renderer* renderer)
{
    SBMPInfo result;
    result.texture = NULL;
    result.w = 0;
    result.h = 0;

    SDL_Surface* temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(file);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return result;
    }
    result.w = temp->w;
    result.h = temp->h;

    /* Create texture from the image */
    result.texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!result.texture) {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return result;
    }
    SDL_FreeSurface(temp);

    return result;
}

void draw(SDL_Window* window, SDL_Renderer* renderer, const SBMPInfo tagBMP)
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect destRect = {w/2 - tagBMP.w/2, h/2 - tagBMP.h/2, tagBMP.w, tagBMP.h};
    /* Blit the sprite onto the screen */
    SDL_RenderCopy(renderer, tagBMP.texture, NULL, &destRect);
}

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
        exit(2);

    SBMPInfo tagBMP = LoadBMP("logo.bmp", renderer);
    if(tagBMP.texture == NULL)
        exit(2);

    /* Main render loop */
    Uint8 done = 0;
    SDL_Event event;
    while(!done)
    {
        /* Check for events */
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN)
            {
                done = 1;
            }
        }


        /* Draw a gray background */
        SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderClear(renderer);

        draw(window, renderer, tagBMP);

        /* Update the screen! */
        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    exit(0);
}