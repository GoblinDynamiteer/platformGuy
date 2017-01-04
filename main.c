#include "def.h"

int main(int argc, char* args[]){
	//Seed random
	srand((int)time(NULL)); 
	
/* 	for(int i = 0; i<300;i++){
		printf("Wrand %d \n", rand() % WINDOW_WIDTH);
		printf("Hrand %d \n", rand() % WINDOW_HEIGHT);
	} */
	
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

	// character '|' combines flags SDL_RENDERER_PRESENTVSYNC = VSYNC, SDL_RENDERER_ACCELERATED = GPU ACC
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Starts game struct
	game game;
	game.renderer = renderer;
	game.window = window;

	if(!loadGame(&game)){
		shutdownGame(&game);
		return 0;
	}

	//game loop
	while(processEvent(&game)){
		renderGame(&game);
	}

	shutdownGame(&game);
	return 0;
}
