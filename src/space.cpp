#include "../include/space.hpp"

void RenderSpace(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    int width, height;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_GetRenderOutputSize(renderer, &width, &height);

    for (int i = 0; i < width / 2; i += 100) {
        SDL_RenderLine(renderer, width / 2 - i, 0, width / 2 - i, height);
        SDL_RenderLine(renderer, width / 2 + 100 + i, 0, width / 2 + 100 + i, height);
    }

    for (int i = 0; i < height / 2; i += 100) {
        SDL_RenderLine(renderer, 0, height / 2 - i, width, height / 2 - i);
        SDL_RenderLine(renderer, 0, height / 2 + 100 + i, width, height / 2 + 100 + i);
    }
}
