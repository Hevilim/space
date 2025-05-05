#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <iostream>
#include <cstring>
#include <string>

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if (!TTF_Init()) {
        SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (!SDL_CreateWindowAndRenderer("Space", 320, 240, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf", 24);
    if (!font) {
        SDL_Log("Failed to load font: %s", SDL_GetError());
        return 1;
    }

    SDL_Texture* texture = nullptr;
    SDL_Texture* text_texture = nullptr;
    SDL_FRect text_rect{};

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_DROP_FILE) {
                const char* path = (const char*)event.drop.data;
                SDL_Log("Dropped file: %s", path);

                SDL_Surface* surface = IMG_Load(path);
                if (!surface) {
                    SDL_Log("Failed to load image: %s", SDL_GetError());
                    continue;
                }

                if (texture) SDL_DestroyTexture(texture);
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_DestroySurface(surface);

                if (!texture) {
                    SDL_Log("Failed to create texture: %s", SDL_GetError());
                }

                // Извлекаем имя файла
                size_t len = std::strlen(path), i;
                for (i = len - 1; i > 0; --i) {
                    if (path[i - 1] == '/') break;
                }
                std::string name = std::string(path + i);

                // Рендерим текст
                if (text_texture) SDL_DestroyTexture(text_texture);

                SDL_Color yellow = {255, 255, 0, 255};
                SDL_Surface* text_surface = TTF_RenderText_Blended(font, name.c_str(), len - i, yellow);
                if (!text_surface) {
                    SDL_Log("Failed to render text: %s", SDL_GetError());
                    continue;
                }

                text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
                text_rect = {10.0f, 10.0f, (float)text_surface->w, (float)text_surface->h};
                SDL_DestroySurface(text_surface);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (texture) {
            SDL_RenderTexture(renderer, texture, NULL, NULL);
        }

        // Рисуем текст поверх квадрата
        if (text_texture) {
            // Рисуем синий квадрат
            float text_w, text_h;
            SDL_GetTextureSize(text_texture, &text_w, &text_h);

            SDL_FRect rect = {10, 10, text_w, text_h};
            SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
            SDL_RenderFillRect(renderer, &rect);

            SDL_RenderTexture(renderer, text_texture, NULL, &text_rect);
        }

        SDL_RenderPresent(renderer);
    }

    if (text_texture) SDL_DestroyTexture(text_texture);
    if (texture) SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
