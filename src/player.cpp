#include "player.hpp"

Player::Player(GameManager* gameManager, SDL_Texture* texture, int x, int y, SDL_Texture* bulletTexture)
    : Tank(gameManager, texture, x, y, bulletTexture) {}


void Player::update(double dt)
{
    // TODO : check if the tank is in the wall
    // TODO : check if the tank is out of the screen
    // TODO : check if the tank is out of the map
    // TODO : check if the tank is in a mine
}

void Player::handleEvent(SDL_Event &e, double dt)
{
    // MOVE
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            act(dt, UP);
            break;
        case SDLK_DOWN:
            act(dt, DOWN);
            break;
        case SDLK_LEFT:
            act(dt, TURN_L);
            break;
        case SDLK_RIGHT:
            act(dt, TURN_R);
            break;
        case SDLK_SPACE:
            shoot();
            break;
        }
    }
}