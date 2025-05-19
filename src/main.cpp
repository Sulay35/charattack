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
#include "q_learning_bot.hpp"

using namespace std;

// TODO : REMOVE this shit
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

        // TODO : put this in a class 
        // T = Tank 
        // A = Agent 
        // X = Mine
        gameManager.loadStage(
            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
            "W T                            W"
            "W    W     W  WW     WW        W"
            "W W  W               W         W"
            "W                    W   WWWWWWW"
            "W    W   W       W   W     W   W"
            "W        W   W   W   WW        W"
            "W            W   W       W W   W"
            "W     W   W             WW     W"
            "W                          W   W"
            "W W      W            WWWWWW   W"
            "W                              W"
            "W   W       WW           W     W"
            "W   W                    W     W"
            "W   WW    WW    WWWW           W"
            "W       W         B    W       W"
            "W       W              W       W"
            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
            );

        // Need to use a controller class to distinguish between the two players controls (and the bot)
        //Player *p2 = new Player(&gameManager, charTexture, SCREEN_WIDTH , SCREEN_HEIGHT / 2, bulletTexture);
        //gameManager.addGameObject(p2);

        // Create the player
        auto p1 = std::make_unique<Player>(&gameManager, charTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, bulletTexture);
        gameManager.addGameObject(std::move(p1));
        // Create the bot
        auto p2 = std::make_unique<QLearningBot>(&gameManager, charTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, bulletTexture);
        gameManager.addGameObject(std::move(p2));

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