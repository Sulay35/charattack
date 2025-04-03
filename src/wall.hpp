#pragma once

#include "gameobject.hpp"
#include "vector2.hpp"

class Wall : public GameObject{
public:
    Wall() = default;
    ~Wall() {}
    Wall(Vector2 position);
    Wall(SDL_Texture* texture, Vector2 position);
    Wall(const Wall &) = default;

    virtual void handleEvent(SDL_Event &e, double dt) {}
    virtual void update(double dt) {}
    virtual void render(SDL_Renderer *gRenderer) const;

    private:
        Vector2 pos;
        int w = 40, h = 40;
};