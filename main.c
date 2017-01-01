#include "main.h"
#include "event.h"

int main(int argc, char* args[]){
	
	//Declare window and renderer
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	//Start SDL system
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("PlatformGuy", 
					SDL_WINDOWPOS_UNDEFINED, 
					SDL_WINDOWPOS_UNDEFINED, 
					WINDOW_WIDTH, 
					WINDOW_HEIGHT, 
					0);
					
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	player player;
	player.position.x = WINDOW_WIDTH / 2;
	player.position.y = WINDOW_HEIGHT / 2;
	
	//game loop
	while(processEvent(window, &player)){
		renderGame(renderer, &player);
		//Delay 10 msec
		SDL_Delay(5);
	} //End while !done loop
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//Quit SDL
	SDL_Quit();
	return 0;
}