#include "game_manager.hpp"

// TODO : 
// - add a function to load the stage from a file
// - add texture loader class 
// - use pooling for bullets

GameManager::~GameManager(){
    std::vector<std::unique_ptr<GameObject>>::iterator it;
    for(it = gameObjects.begin(); it != gameObjects.end(); it++){
        (*it).release();
    }
    gameObjects.clear();
}

void GameManager::addGameObject(std::unique_ptr<GameObject> gameObject){
    toAddGameObjects.push_back(std::move(gameObject));
}

void GameManager::removeGameObject(std::unique_ptr<GameObject> gameObject) {
    

    std::vector<std::unique_ptr<GameObject>>::iterator foundGameObject = std::find(
        gameObjects.begin(),
        gameObjects.end(),
        gameObject
    );
    toRemove.push_back(std::distance(gameObjects.begin(), foundGameObject));
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
    for(auto &obj : gameObjects){
        obj->handleEvent(e,dt);
    }
}

void GameManager::update(double dt) {
    printf("Number of gameObjects: %zu\n", gameObjects.size());

    for(auto it = toAddGameObjects.begin(); it != toAddGameObjects.end(); it++){
        gameObjects.push_back(std::move(*it));
    }   
    toAddGameObjects.clear();

    // Remove gameObjects
    for(auto it = toRemove.begin(); it != toRemove.end(); it++){
        gameObjects.erase(gameObjects.begin() + *it);
    }
    toRemove.clear();

    std::vector<std::unique_ptr<GameObject>>::iterator it;
    for(auto &obj : gameObjects){
        obj->update(dt);
    }

    // Collision detection
    // for(it = gameObjects.begin(); it != gameObjects.end(); it++){
    //     for(auto it2 = gameObjects.begin(); it2 != gameObjects.end(); it2++){
    //         if(it != it2){
    //             if((*it)->getBoxCollider()->collide((*it2)->getBoxCollider())){
    //                 std::cout << "Collision between " << (*it)->getBoxCollider()->getTag() << " and " << (*it2)->getBoxCollider()->getTag() << std::endl;
    //                 (*it)->handleEvent(e, dt);
    //             }
    //         }
    //     }
    // }
}

void GameManager::render(SDL_Renderer *gRenderer) const {
    std::vector<std::unique_ptr<GameObject>>::const_iterator it;
    for(it = gameObjects.begin(); it != gameObjects.end(); it++){
        (*it)->render(gRenderer);
    }
}

void GameManager::loadStage(std::string s){
    // TODO : check length
    std::string::iterator sit = s.begin();
    for(size_t j = 0; j < SCREEN_HEIGHT && sit != s.end(); j+=40){
    for(size_t i = 0; i < SCREEN_WIDTH; i+=40){
            if((*sit) == 'W'){ // WALL
                Vector2 objectPos(i,j);
                //std::cout << "at : " << objectPos << std::endl;
                auto wall = std::make_unique<Wall>(objectPos);
                addGameObject(std::move(wall));
            }
            sit++;
        }
    }
}
