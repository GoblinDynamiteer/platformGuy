#include "main.h"
#include "event.h"

int processEvent(SDL_Window *window){
	SDL_Event event;
	int keepPlaying = 1;
	while(SDL_PollEvent(&event)){ //SDL_PollEvent returns true if an event shall be processed
		switch(event.type){
			case SDL_WINDOWEVENT_CLOSE:
				printf("Closing window\n");
				if(window){
					
					SDL_DestroyWindow(window);
					window = NULL;
				}
				break;
			//Key has been pressed:
			case SDL_KEYDOWN:
				printf("Key down: %c\n", event.key.keysym.sym);
				switch(event.key.keysym.sym){
					//ESCAPE PRESSED
					case SDLK_ESCAPE:
						printf("Escape Key Down\n");
						keepPlaying = 0;
						break;
				}
				break;
			case SDL_QUIT:
				keepPlaying = 0;
				break;
		} //End switch-statements
	} //End while event loop
	return keepPlaying;
}


void renderGame(SDL_Renderer *renderer){
	//Draws a white rectangle on blue backgtound
	//RGB + ALPHA
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect = { 220, 140, 200, 200 };
	SDL_RenderFillRect(renderer, &rect); 
	SDL_RenderPresent(renderer);
}