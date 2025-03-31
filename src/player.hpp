#include "gameobject.hpp"
#include "vector2.hpp"
#include "window_manager.hpp"
#include <stdio.h>
#include <iostream>

enum action
{
    UP,
    DOWN,
    TURN_L,
    TURN_R,
};

class Player: public GameObject
{
public:
    Player() = default;
    ~Player() {}
    Player(int x, int y);
    Player(SDL_Texture* texture, int x, int y);
    Player(const Player &) = default;
    virtual void handleEvent(SDL_Event &e, double dt) ;
    virtual void update(double dt) {}
    virtual void render(SDL_Renderer *gRenderer) const;

    // Move the player according to actions
    void move(double dt, action a);

    // Shoot a bullet
    void shoot(double dt);

private:
    Vector2 pos;
    Vector2 vel = Vector2(0, 1);
    int speed = 5;

    int angle = 0;
    int rotationSpeed = 5;

    int w = 20, h = 20;
};