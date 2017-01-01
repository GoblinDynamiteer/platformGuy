#include "main.h"
#include "event.h"

int processEvent(SDL_Window *window, guy *player){
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
					case SDLK_RIGHT:
						player->x += MOVE_SPEED;
						break;
					case SDLK_LEFT:
						player->x -= MOVE_SPEED;
						break;
					case SDLK_DOWN:
						player->y += MOVE_SPEED;
						break;
					case SDLK_UP:
						player->y -= MOVE_SPEED;
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


void renderGame(SDL_Renderer *renderer, guy *player){
	//Draws a white rectangle on blue backgtound
	//RGB + ALPHA
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect = { player->x, player->y, 200, 200 };
	SDL_RenderFillRect(renderer, &rect); 
	SDL_RenderPresent(renderer);
}