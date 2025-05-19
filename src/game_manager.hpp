#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>    

#include "gameobject.hpp"
#include "vector2.hpp"
#include "wall.hpp"
#include "window_manager.hpp"

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
    void removeGameObject(std::unique_ptr<GameObject> gameObject);
    
    /// @brief Loads the stage gameObjects from a string or a file
    /// @details The string must be of SCREEN_WIDTH/mod x * SCREEN_HEIGHT/mod size
    /// @return 0 if failed to load the stage
    void loadStage(std::string s);

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
};
