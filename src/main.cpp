#include <stdio.h>
#include "window_manager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <chrono>
#include <iostream>
#include "vector2.hpp"
#include "player.hpp"

using namespace std;


WindowManager windowManager;

int main()
{
    SDL_Window *gWindow = NULL;
    SDL_Renderer *gRenderer = NULL;
    SDL_Surface *gScreenSurface = NULL;
    TTF_Font *gFont = NULL;


    // Delta time between two frames
    double dt = 0.0f;
    if (!windowManager.init(gWindow, gRenderer, gScreenSurface))
    {
        printf("Failed to initialize SDL!\n");
    }
    else
    {
        bool quit = false;
        SDL_Event e;

        SDL_Texture *charTexture = windowManager.loadTexture(gRenderer, "ressources/char.png");

        Player p1(charTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

        Player p2(charTexture, SCREEN_WIDTH , SCREEN_HEIGHT / 2);

        // MAIN LOOP
        while (!quit)
        {
            auto t1 = std::chrono::high_resolution_clock::now();

            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                    quit = true;
                else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                    }
                }

                p1.handleEvent(e, dt);
                p2.handleEvent(e, dt);
            }


            // Render background
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            p1.render(gRenderer);
            p2.render(gRenderer);

            SDL_RenderPresent(gRenderer);
            auto t2 = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration<double, std::chrono::milliseconds::period>(t2 - t1).count();
        }
    }

    windowManager.close(gWindow, gRenderer, gFont);
    return 0;
}