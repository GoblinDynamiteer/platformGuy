#include "SDL.h"
#include <stdio.h>

typedef struct{
	int x,y;
	short life;
	char *name;
}guy;

int main(int argc, char* args[]){
	
	//Declare window and renderer
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	//Start SDL system
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("PlatformGuy", 
					SDL_WINDOWPOS_UNDEFINED, 
					SDL_WINDOWPOS_UNDEFINED, 
					640, 
					480, 
					0);
					
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	//RGB + ALPHA
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	SDL_Rect rect = { 220, 140, 200, 200 };
	SDL_RenderFillRect(renderer, &rect);
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(10000);
	
	SDL_DestroyWindow(window);
	//Quit SDL
	SDL_Quit();
	return 0;
}