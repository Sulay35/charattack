#include "game_manager.hpp"

GameManager::~GameManager(){
    std::vector<std::unique_ptr<GameObject>>::iterator it;
    for(it = gameObjects.begin(); it != gameObjects.end(); it++){
        (*it).release();
    }
}

void GameManager::addGameObject(std::unique_ptr<GameObject> gameObject){
    gameObjects.push_back(std::move(gameObject));
}

void GameManager::removeGameObject(std::unique_ptr<GameObject> gameObject) {
    std::vector<std::unique_ptr<GameObject>>::iterator foundGameObject = std::find(
        gameObjects.begin(),
        gameObjects.end(),
        gameObject
    );
    // dunno if its necessary since its uniqueptr
    //(*foundGameObject).release();
    gameObjects.erase(foundGameObject);
}


void GameManager::handleEvent(SDL_Event &e, double dt){
    // std::vector<std::unique_ptr<GameObject>>::iterator it;
    // std::cout << "AVANT size: " << gameObjects.size() << std::endl;
    
    // int i = 0;
    // for(it = gameObjects.begin(); it != gameObjects.end(); it++){
    //     std::cout << (*it).get() << std::endl;
    //     std::cout << "APRES size: " << gameObjects.size() << std::endl;
    //     (*it)->handleEvent(e, dt);
    // }
    std::vector<std::unique_ptr<GameObject>>::iterator it;
    size_t size = gameObjects.size();
    for(size_t i = 0; i < size; i++){
        gameObjects[i]->handleEvent(e,dt);
    }
}

void GameManager::update(double dt) {
    std::vector<std::unique_ptr<GameObject>>::iterator it;
    for(it = gameObjects.begin(); it != gameObjects.end(); it++){
        (*it)->update(dt);
    }
}

void GameManager::render(SDL_Renderer *gRenderer) const {
    std::vector<std::unique_ptr<GameObject>>::const_iterator it;
    for(it = gameObjects.begin(); it != gameObjects.end(); it++){
        (*it)->render(gRenderer);
    }
}

void GameManager::loadStage(std::string s, int mod){
    // TODO : check length
    for(size_t i = 0; i < SCREEN_WIDTH; i+=40){
        for(size_t j = 0; j < SCREEN_HEIGHT; j+=40){
            if(random()%5 == 0){
                Vector2 objectPos(i,j);
                std::cout << "at : " << objectPos << std::endl;
                auto wall = std::make_unique<Wall>(objectPos);
                addGameObject(std::move(wall));
            }
        }
    }
}