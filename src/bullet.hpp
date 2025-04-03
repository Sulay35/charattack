#include "gameobject.hpp"
#include "vector2.hpp"
#include "window_manager.hpp"
#include <stdio.h>
#include <iostream>

class Bullet: public GameObject
{
public:
    Bullet() = default;
    ~Bullet() {}
    Bullet(SDL_Texture* texture, int x, int y, Vector2 velocity);
    Bullet(const Bullet &) = default;

    virtual void handleEvent(SDL_Event &e, double dt);
    virtual void update(double dt);
    virtual void render(SDL_Renderer *gRenderer) const;

    // Move the bullet
    void move(double dt);

private:
    Vector2 pos;
    Vector2 vel;
    double speed = 0.5f;
    int angle = 0;
    int w = 20, h = 20;
};