#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cstdio>

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;

    // convert -size 100x100 xc:gray sample.bmp
    SDL_Texture *texture;
    
    SDL_Event event;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (!SDL_CreateWindowAndRenderer("Hello SDL", 320, 240, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    // surface = SDL_LoadBMP(path);
    // if (!surface) {
    //     SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
    //     return 3;
    // }
    // texture = SDL_CreateTextureFromSurface(renderer, surface);
    // if (!texture) {
    //     SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
    //     return 3;
    // }
    // SDL_DestroySurface(surface);

    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            break;
        } else if (event.type == SDL_EVENT_DROP_FILE) {
            const char* path = (const char*)event.drop.data;
            SDL_Log("Dropped file: %s", path);

            SDL_Surface* surface = SDL_LoadBMP(path);
            if (!surface) {
                SDL_Log("Failed to load BMP: %s", SDL_GetError());
                continue;
            }

            if (texture) SDL_DestroyTexture(texture);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_DestroySurface(surface);

            if (!texture) {
                SDL_Log("Failed to create texture: %s", SDL_GetError());
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        // SDL_RenderTexture(renderer, texture, NULL, NULL);
        if (texture) {
            SDL_RenderTexture(renderer, texture, NULL, NULL);
        }
        SDL_RenderPresent(renderer);
    }

    if (texture) SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
