#pragma once

#include "gameobject.hpp"
#include "vector2.hpp"
#include "window_manager.hpp"
#include <stdio.h>
#include <iostream>
#include "bullet.hpp"
#include "game_manager.hpp"

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
    Player(GameManager* gameManager, SDL_Texture *texture, int x, int y, SDL_Texture* bulletTexture);
    Player(const Player &) = default;

    virtual void handleEvent(SDL_Event &e, double dt) ;
    virtual void update(double dt) {}
    virtual void render(SDL_Renderer *gRenderer) const;

    // Move the player according to actions
    void move(double dt, action a);

    // Shoot a bullet
    void shoot();

private:
    GameManager* gameManager;   

    Vector2 pos;
    Vector2 vel = Vector2(0, 1);
    int speed = 10;

    int angle = 0;
    int rotationSpeed = 8;

    int w = 40, h = 40;

    SDL_Texture* bulletTexture;
};