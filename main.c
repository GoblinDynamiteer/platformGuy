#include "main.h"
#include "event.h"

int main(int argc, char* args[]){
	
	//Declare window and renderer
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *bombSurface = NULL;
	
	//Start SDL system
	SDL_Init(SDL_INIT_VIDEO);
	
	
	window = SDL_CreateWindow("PlatformGuy", 
					SDL_WINDOWPOS_UNDEFINED, 
					SDL_WINDOWPOS_UNDEFINED, 
					WINDOW_WIDTH, 
					WINDOW_HEIGHT, 
					0);
	
	// character | combines flags SDL_RENDERER_PRESENTVSYNC = VSYNC, SDL_RENDERER_ACCELERATED = GPU ACC
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	bombSurface = IMG_Load("art/enemies/bomb.png");
	if(bombSurface == NULL){
		printf("Cant load bomb.png");
		SDL_Quit();
		return 1;
	}
	else{
		printf("Image load successful!");
	}
	
	game game;
	game.player.position.x = WINDOW_WIDTH / 2;
	game.player.position.y = WINDOW_HEIGHT / 2;
	
	//game loop
	while(processEvent(window, &game)){
		renderGame(renderer, &game);
	} //End while !done loop
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//Quit SDL
	SDL_Quit();
	return 0;
}