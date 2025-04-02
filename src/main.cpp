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
GameManager gameManager;

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
        SDL_Texture *bulletTexture = windowManager.loadTexture(gRenderer, "ressources/bullet.png");

        auto p1 = std::make_unique<Player>(&gameManager, charTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, bulletTexture);
        gameManager.addGameObject(std::move(p1));

        //Player *p2 = new Player(&gameManager, charTexture, SCREEN_WIDTH , SCREEN_HEIGHT / 2, bulletTexture);
        //gameManager.addGameObject(p2);

        auto b = std::make_unique<Bullet>(bulletTexture, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Vector2(0,1));
        gameManager.addGameObject(std::move(b));

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
                gameManager.handleEvent(e, dt);
            }
            // Render background
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            // Update all gameobjects
            gameManager.update(dt);

            // Render all gameobjects
            gameManager.render(gRenderer);
            
            // render buffer
            SDL_RenderPresent(gRenderer);
            
            // Compute Delta time
            auto t2 = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration<double, std::chrono::milliseconds::period>(t2 - t1).count();
        }
    }

    windowManager.close(gWindow, gRenderer, gFont);
    return 0;
}