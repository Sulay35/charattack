#include "wall.hpp"

Wall::Wall(Vector2 pos) : GameObject(), pos(pos) {}
Wall::Wall(SDL_Texture* texture, Vector2 pos) : GameObject(texture), pos(pos) {}

void Wall::render(SDL_Renderer *gRenderer) const {
    SDL_Rect body = {this->pos.x, this->pos.y, w, h};
    // SDL_Surface *surface = SDL_CreateRGBSurface(0, 100, 50, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    // SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 0));
    // SDL_RenderCopy(gRenderer, getTexture(), nullptr, &body);
    // SDL_FreeSurface(surface); 

    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &body);
}
