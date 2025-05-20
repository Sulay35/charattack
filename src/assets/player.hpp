#pragma once   
#include "tank.hpp"

class Player : public Tank {
public:
    Player(GameManager* gameManager, SDL_Texture* texture, int x, int y, SDL_Texture* bulletTexture);

    void handleEvent(SDL_Event& e, double dt) override;
    void update(double dt);
};