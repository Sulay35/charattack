#pragma once

#include "../utils/gameobject.hpp"
#include "../utils/vector2.hpp"
#include "../utils/window_manager.hpp"
#include <stdio.h>
#include <iostream>
#include "bullet.hpp"
#include "../utils/game_manager.hpp"
#include "../utils/boxCollider.hpp"

enum action
{
    UP,
    DOWN,
    TURN_L,
    TURN_R,
    SHOOT,
};

class Tank: public GameObject
{
public:
    Tank() = default;
    ~Tank() = default;
    Tank(int x, int y);
    Tank(GameManager* gameManager, SDL_Texture *texture, int x, int y, SDL_Texture* bulletTexture);
    Tank(const Tank &) = default;

    virtual void handleEvent(SDL_Event &e, double dt);
    virtual void update(double dt);
    virtual void render(SDL_Renderer *gRenderer) const;

protected:
    // Move the player according to actions
    void act(double dt, action a);

    // Shoot a bullet
    void shoot();
    GameManager* gameManager;   

    BoxCollider *boxCollider;

    Vector2 pos;
    Vector2 vel = Vector2(0, 1);
    int speed = 5;
    int angle = 0;
    int rotationSpeed = 8;

    int w = 30, h = 30;
    SDL_Texture* bulletTexture;
};