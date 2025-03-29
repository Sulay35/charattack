#include <stdio.h>
#include "window_manager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstdlib>
#include <chrono>

enum action
{
    UP,
    DOWN,
    TURN_L,
    TURN_R,
};

class Vector2{
	public:
		Vector2()
			: x(0.0f), y(0.0f)
		{}
		Vector2(double x, double y)
			: x(x), y(y)
		{}

        Vector2 rotate(double angle){
            double x2 =  cos(angle) - sin(angle);
            double y2 =  sin(angle) + sin(angle);
            return Vector2(x2, y2);
        }

		Vector2 operator+(Vector2 const& rhs)
		{
			return Vector2(x+rhs.x, y+rhs.y);
		}	
		Vector2& operator +=(Vector2 const& rhs)
		{
			x+=rhs.x;
			y+=rhs.y;
			return *this;
		}
		Vector2 operator*(double rhs)
		{
			return Vector2(x*rhs, y*rhs);
		}	
        
		double x,y;
};

class Player
{
public:
    Player() = default;
    ~Player() = default;
    Player(int x, int y);
    Player(const Player &) = default;
    void handleEvent(SDL_Event &e);
    void move(float dt, action a);
    void update();
    void render(SDL_Renderer *gRenderer);

private:
    int posX, posY;
    int angle;
    int rotationSpeed = 5;
    int speed = 5;
    int velY;
    int accX = 1, accY = 1;

    int w = 20,h =20;
};

Player::Player(int x, int y) : posX(x), posY(y) { }

void Player::move(float dt, action a)
{
    switch (a)
    {
    case UP:
        velY = -speed;
        posY += velY*dt;
        break;
    case DOWN:
        velY = speed;
        posY += velY*dt;
        break;
    case TURN_L:
        angle += rotationSpeed;
        break;
    case TURN_R:
        angle -= rotationSpeed;
        //angle %= 360;
        break;
    }
}

void Player::render(SDL_Renderer *gRenderer)
{

    SDL_Rect body = {this->posX, this->posY, w, h};
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 50, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 0)); // Fill with red
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface); // No longer needed
    SDL_RenderCopyEx(gRenderer, texture, nullptr, &body, angle, nullptr, SDL_FLIP_NONE);

    SDL_Point center = {w/2, h/2};

    SDL_Rect barrel = {this->posX+w/2-w/8, this->posY-h/2, w/4, h/2};
    surface = SDL_CreateRGBSurface(0, 100, 50, 32, 0x000, 0xFFF, 0x000, 0xFFF);
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 0)); // Fill with red
    texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface); // No longer needed
    SDL_RenderCopyEx(gRenderer, texture, nullptr, &barrel, angle, &center, SDL_FLIP_NONE);
}

int main()
{
    SDL_Window *gWindow = NULL;
    SDL_Renderer *gRenderer = NULL;
    SDL_Surface *gScreenSurface = NULL;
    TTF_Font *gFont = NULL;

    WindowManager windowManager;

    Player p1(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    // Delta time between two frames 
    float dt=0.0f;
    
    if (!windowManager.init(gWindow, gRenderer, gScreenSurface))
    {
        printf("Failed to initialize SDL!\n");
    }
    else
    {
        bool quit = false;
        SDL_Event e;

        while (!quit)
        {
            auto t1 = std::chrono::high_resolution_clock::now();
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                    quit = true;
                else if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        quit = true;
                        break;
                        case SDLK_UP:
                        p1.move(dt, UP);
                        break;
                        case SDLK_DOWN:
                        p1.move(dt, DOWN);
                        break;
                        case SDLK_LEFT:
                        p1.move(dt, TURN_L);
                        break;
                        case SDLK_RIGHT:
                        p1.move(dt, TURN_R);
                        break;
                    }
                }
            }

            p1.render(gRenderer);

            // Render background
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderPresent(gRenderer);
            SDL_RenderClear(gRenderer);

            auto t2 = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration<float, std::chrono::milliseconds::period>(t2 - t1).count();
        }
    }

    windowManager.close(gWindow, gRenderer, gFont);
    return 0;
}