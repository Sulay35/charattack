#include "player.hpp"
#include <SDL2/SDL.h>

Player::Player(int x, int y) : GameObject(), pos(Vector2(x, y)) {}
Player::Player(GameManager* gameManager, SDL_Texture *texture, int x, int y, SDL_Texture* bulletTexture) :GameObject(texture), pos(Vector2(x, y)), bulletTexture(bulletTexture), gameManager(gameManager)  {}

void Player::handleEvent(SDL_Event &e, double dt)
{
    // MOVE
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            move(dt, UP);
            break;
        case SDLK_DOWN:
            move(dt, DOWN);
            break;
        case SDLK_LEFT:
            move(dt, TURN_L);
            break;
        case SDLK_RIGHT:
            move(dt, TURN_R);
            break;
        case SDLK_SPACE:
            shoot();
            break;
        }
    }
}

/// @brief Move the player according to an action
/// @details Rotate the position and move with a defined speed
/// @param dt Delta time
/// @param a action
void Player::move(double dt, action a)
{
    switch (a)
    {
    case UP:
        pos += vel * (-speed) * dt;
        break;
    case DOWN:
        pos += vel * speed * dt;
        break;
    case TURN_L:
        angle -= rotationSpeed;
        angle %= 360;
        vel.rotate(-rotationSpeed * M_PI / 180);
        break;
    case TURN_R:
        angle += rotationSpeed;
        angle %= 360;
        vel.rotate(rotationSpeed * M_PI / 180);
        break;
    }
}

void Player::render(SDL_Renderer *gRenderer) const
{
    SDL_FRect body = {this->pos.x, this->pos.y, w, h};
    SDL_Surface *surface = SDL_CreateRGBSurface(0, 100, 50, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 0)); // Fill with red
    SDL_RenderCopyExF(gRenderer, getTexture(), nullptr, &body, angle, nullptr, SDL_FLIP_NONE) != 0;
    SDL_FreeSurface(surface); // No longer needed
}

// shoot a bullet
// instantiate a bullet : 
// init velocity = this-> velocity
void Player::shoot() {
    auto b = std::make_unique<Bullet>(bulletTexture, pos.x, pos.y, vel);
    gameManager->addGameObject(std::move(b));
}
