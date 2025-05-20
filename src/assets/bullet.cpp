#include "bullet.hpp"
#include <SDL2/SDL.h>

Bullet::Bullet(SDL_Texture* texture, int x, int y, Vector2 velocity) : GameObject(texture), pos(Vector2(x,y)), vel(velocity) {
    angle = vel.angle() * 180/M_PI;
}
void Bullet::handleEvent(SDL_Event &e, double dt) { }

void Bullet::render(SDL_Renderer *gRenderer) const {
    SDL_FRect body = {this->pos.x, this->pos.y, w, h};
    SDL_Surface *surface = SDL_CreateRGBSurface(0, 100, 50, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 0));
    SDL_RenderCopyExF(gRenderer, getTexture(), nullptr, &body, angle, nullptr, SDL_FLIP_NONE) != 0;
    SDL_FreeSurface(surface); 
}

// Move the bullet
void Bullet::move(double dt) {
    pos += vel * (-speed) * dt;
}

void Bullet::update(double dt) {
    move(dt);
}

