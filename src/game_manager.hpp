#pragma once

#include "gameobject.hpp"
#include "vector2.hpp"
#include "window_manager.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>

// Holds and manages all gameObjects : 
// - calls function for each stored object

class GameManager: public GameObject
{
public:
    GameManager() = default;
    ~GameManager();
    GameManager(const GameManager &) = default;

    virtual void handleEvent(SDL_Event &e, double dt) ;
    virtual void update(double dt);
    virtual void render(SDL_Renderer *gRenderer) const;

    void addGameObject(std::unique_ptr<GameObject> gameObject);
    void removeGameObject(std::unique_ptr<GameObject> gameObject) {
        std::cerr << "removeGameObject isn't implemented" << std::endl;
    }

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
};
