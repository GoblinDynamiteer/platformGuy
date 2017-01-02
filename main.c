#include "main.h"
#include "event.h"

int main(int argc, char* args[]){
	//Declare window and renderer
	SDL_Window *window;
	SDL_Renderer *renderer;

	//Start SDL system
	SDL_Init(SDL_INIT_VIDEO);
	
	//Creates the window
	window = SDL_CreateWindow("PlatformGuy", 
					SDL_WINDOWPOS_UNDEFINED, 
					SDL_WINDOWPOS_UNDEFINED, 
					WINDOW_WIDTH, 
					WINDOW_HEIGHT, 
					0);

	// character | combines flags SDL_RENDERER_PRESENTVSYNC = VSYNC, SDL_RENDERER_ACCELERATED = GPU ACC
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Starts game struct
	game game;

	if(!loadGame(renderer, &game)){
		shutdownGame(window, renderer, &game);
		return 0;
	}

	//game loop
	while(processEvent(window, &game)){
		renderGame(renderer, &game);
	} //End while !done loop

	shutdownGame(window, renderer, &game);
	return 0;
}