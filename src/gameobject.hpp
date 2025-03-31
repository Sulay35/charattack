// Abstract Class representing any object interacting or being drawn 
#include <SDL2/SDL.h>

class GameObject{
    public:
        GameObject() = default;
        GameObject(SDL_Texture* t) : texture(t){}
        virtual ~GameObject() {
            SDL_DestroyTexture(texture);
        };

        /**
         * Handle events
         * 
         * @param e a reference to an event that occured
        */
        virtual void handleEvent(SDL_Event &e, double dt) = 0;

        /**
         *  Update the gameObject attributes
         * @param dt Delta time between the last two frames
        */
        virtual void update(double dt) = 0 ;

        /**
         *  Render the gameobject on the renderer
         * 
         * @param gR a pointer to the Renderer 
        */
        virtual void render(SDL_Renderer *gRenderer) const = 0;

        inline SDL_Texture* getTexture() const {
            return texture;
        }
    private: 
        SDL_Texture* texture = NULL;
};
