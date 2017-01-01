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
	
	int done = 0;
	SDL_Event event;
	
	while(!done){
		while(SDL_PollEvent(&event)){ //SDL_PollEvent returns true if an event shall be processed
			switch(event.type){
				case SDL_WINDOWEVENT_CLOSE: /**< The window manager requests that the window be closed */
					if(window){
						SDL_DestroyWindow(window);
						window = NULL;
					}
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							done = 1;
							break;
					}
					break;
				case SDL_QUIT:
					done = 1;
					break;
			} //End switch-statements
		} //End while event loop
		
		//RGB + ALPHA
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		
		SDL_Rect rect = { 220, 140, 200, 200 };
		SDL_RenderFillRect(renderer, &rect); 
		
		SDL_RenderPresent(renderer);
		
		//Delay 10 msec
		SDL_Delay(10);
	} //End while !done loop

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//Quit SDL
	SDL_Quit();
	return 0;
}