/**
 * Se charge de l'affichage graphique sur la fenêtre avec SDL
 * Basé sur SDL2
 */

#include "window_manager.hpp"

bool WindowManager::init(SDL_Window* & gW, SDL_Renderer* & gR, SDL_Surface* & gSS)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gW = SDL_CreateWindow( "CharGPT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gW == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gR = SDL_CreateRenderer(gW, -1,SDL_RENDERER_ACCELERATED);
			if(gR == NULL){
				printf( "Renderer could not be initialized! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else{
				// init TTF 
				if(TTF_Init() < 0){
					printf( "TTF could not be initialized! TTF Error: %s\n", TTF_GetError());
					success = false;
				}else{
					printf("Everything initialized!\n");
					gSS = SDL_GetWindowSurface(gW);
				}
			}
		}
	}

	return success;
}


void WindowManager::close(SDL_Window* & gW, SDL_Renderer* & gR, TTF_Font* & font)
{
	SDL_DestroyRenderer(gR);
	SDL_DestroyWindow( gW );

	gW = NULL;
	gR = NULL;

	//Quit SDL subsystems
	TTF_CloseFont(font);
	font = NULL;
	
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* WindowManager::loadTexture(SDL_Renderer* sR, std::string path )
{
	//The final optimized image
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Convert surface to screen format
		newTexture = SDL_CreateTextureFromSurface( sR, loadedSurface);
		if( newTexture == NULL )
		{
			printf( "Unable to create texture %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}
