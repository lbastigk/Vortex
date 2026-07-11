#include <cstdint>
#include <print>

#include <SDL3/SDL.h>

int main() {
    std::println("Hello, Client!");

    //------------------------------------------
    // Super basic SDL3 window creation

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Window and renderer
    std::uint32_t const flags = SDL_WINDOW_HIGH_PIXEL_DENSITY;

    if (!SDL_CreateWindowAndRenderer("Vortex", 600, 400, flags, &window, &renderer)) {
        std::println("SDL_CreateWindowAndRenderer Error: {}", SDL_GetError());
        std::abort();
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    // Run
    SDL_Event event;
    bool running = true;
    while (running) {
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // RGB values (black)
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(10);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}