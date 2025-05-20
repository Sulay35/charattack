#pragma once
#include "tank.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <random>

class QLearningBot : public Tank {
public:
    QLearningBot(GameManager* gameManager, SDL_Texture* texture, int x, int y, SDL_Texture* bulletTexture);

    void handleEvent(SDL_Event& e, double dt) override;
    void update(double dt) override;

private:
    std::unordered_map<std::string, std::vector<double>> qTable;
    double alpha = 0.1; // Learning rate
    double gamma = 0.9; // Discount factor
    double epsilon = 0.1; // Exploration rate

    std::string getState();
    int chooseAction(const std::string& state);
    void updateQTable(const std::string& state, int action, double reward, const std::string& nextState);

    std::mt19937 rng;
};