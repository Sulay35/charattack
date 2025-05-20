#include "q_learning_bot.hpp"
#include <algorithm>
#include <iostream>

QLearningBot::QLearningBot(GameManager* gameManager, SDL_Texture* texture, int x, int y, SDL_Texture* bulletTexture)
    : Tank(gameManager, texture, x, y, bulletTexture), rng(std::random_device{}()) {}

void QLearningBot::handleEvent(SDL_Event& e, double dt) {
    // No event for the bot
}

void QLearningBot::update(double dt) {
    Tank::update(dt);

    // Get the current state
    std::string state = getState();

    // Choose an action
    int action = chooseAction(state);

    // Perform the action
    switch (action) {
        case UP: act(dt, UP); break;
        case DOWN: act(dt, DOWN); break;
        case TURN_L: act(dt, TURN_L); break;
        case TURN_R: act(dt, TURN_R); break;
        case SHOOT: shoot(); break;
    }

    // Get the next state and reward
    std::string nextState = getState();
    double reward = 0.0; // TODO: Implement reward calculation based on game events.

    // Update the Q-table
    //updateQTable(state, action, reward, nextState);
}

std::string QLearningBot::getState() {
    // Discretize the state into a string representation
    int x_bin = static_cast<int>(pos.x / 40); 
    int y_bin = static_cast<int>(pos.y / 40);
    int angle_bin = angle / 6; 
    return std::to_string(x_bin) + "_" + std::to_string(y_bin) + "_" + std::to_string(angle_bin);
}

int QLearningBot::chooseAction(const std::string& state) {
    // choose random action
    std::uniform_int_distribution<int> actionDist(0, 4);
    std::cout << "State: " << state << std::endl;
    std::cout << "Action: " << actionDist(rng) << std::endl;
    return actionDist(rng);



    // if (qTable.find(state) == qTable.end()) {
    //     qTable[state] = std::vector<double>(5, 0.0); // Initialize Q-values for all actions
    // }

    // std::uniform_real_distribution<double> dist(0.0, 1.0);
    // if (dist(rng) < epsilon) {
    //     std::uniform_int_distribution<int> actionDist(0, 4);
    //     return actionDist(rng);
    // } else {
    //     return std::distance(qTable[state].begin(), std::max_element(qTable[state].begin(), qTable[state].end()));
    // }
}

void QLearningBot::updateQTable(const std::string& state, int action, double reward, const std::string& nextState) {
    if (qTable.find(nextState) == qTable.end()) {
        qTable[nextState] = std::vector<double>(5, 0.0); // Initialize Q-values for all actions
    }

    double maxNextQ = *std::max_element(qTable[nextState].begin(), qTable[nextState].end());
    qTable[state][action] += alpha * (reward + gamma * maxNextQ - qTable[state][action]);
}