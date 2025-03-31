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
    Bullet(int x, int y);
    Bullet(SDL_Texture* texture, int x, int y);
    Bullet(const Bullet &) = default;
    virtual void handleEvent(SDL_Event &e, double dt) ;
    virtual void update(double dt);
    virtual void render(SDL_Renderer *gRenderer) const;

    // Move the bullet
    void move(double dt);

private:
    Vector2 pos;
    Vector2 vel;
    int speed = 5;
    int angle;
    int w = 20, h = 20;
};