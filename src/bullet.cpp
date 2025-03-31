#include "bullet.hpp"
#include <SDL2/SDL.h>

Bullet::Bullet(int x, int y) : GameObject(), pos(Vector2(x,y)) {}
Bullet::Bullet(SDL_Texture* texture, int x, int y) : GameObject(texture), pos(Vector2(x,y)) {}
void Bullet::handleEvent(SDL_Event &e, double dt) {}
void Bullet::update(double dt) {}

void Bullet::render(SDL_Renderer *gRenderer) const {
    SDL_Rect body = {this->pos.x, this->pos.y, w, h};
    SDL_Surface *surface = SDL_CreateRGBSurface(0, 100, 50, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 0)); // Fill with red
    SDL_RenderCopyEx(gRenderer, getTexture(), nullptr, &body, angle, nullptr, SDL_FLIP_NONE) != 0;
    SDL_FreeSurface(surface); // No longer needed
}

// Move the bullet
void Bullet::move(double dt) {
    pos += vel * speed * dt;
}