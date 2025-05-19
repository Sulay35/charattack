#include "tank.hpp"
#include <SDL2/SDL.h>

Tank::Tank(int x, int y) : GameObject(), pos(Vector2(x, y)) {}
Tank::Tank(GameManager* gameManager, SDL_Texture *texture, int x, int y, SDL_Texture* bulletTexture) :GameObject(texture), pos(Vector2(x, y)), bulletTexture(bulletTexture), gameManager(gameManager)  {}

void Tank::handleEvent(SDL_Event &e, double dt)
{
    // TODO : check if the tank is in the wall
    // TODO : check if the tank is out of the screen
    // TODO : check if the tank is out of the map
    // TODO : check if the tank is in a mine
}

/// @brief Update the tank
/// @details Update the tank position and check for collisions
/// @param dt Delta time
void Tank::update(double dt)
{
    // TODO : check if the tank is in the wall
    // TODO : check if the tank is out of the screen
    // TODO : check if the tank is out of the map
    // TODO : check if the tank is in a mine
}

/// @brief Render the tank
void Tank::render(SDL_Renderer *gRenderer) const
{
    SDL_FRect body = {this->pos.x, this->pos.y, w, h};
    SDL_Surface *surface = SDL_CreateRGBSurface(0, 100, 50, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 0)); // Fill with red
    SDL_RenderCopyExF(gRenderer, getTexture(), nullptr, &body, angle, nullptr, SDL_FLIP_NONE) != 0;
    SDL_FreeSurface(surface); // No longer needed
}

/// @brief Move the player according to an action
/// @details Rotate the position and move with a defined speed
/// @param dt Delta time
/// @param a action
void Tank::act(double dt, action a)
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
    case SHOOT:
        shoot();
        break;
    }
}

// shoot a bullet
// instantiate a bullet : 
// init velocity = this-> velocity
void Tank::shoot() {
    auto b = std::make_unique<Bullet>(bulletTexture, pos.x, pos.y, vel);
    gameManager->addGameObject(std::move(b));
}


