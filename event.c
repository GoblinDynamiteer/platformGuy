#include "main.h"
#include "event.h"

int processEvent(SDL_Window *window, game *game){
	SDL_Event event;
	int keepPlaying = 1;
	while(SDL_PollEvent(&event)){ //SDL_PollEvent returns true if an event shall be processed
		switch(event.type){
			case SDL_WINDOWEVENT_CLOSE:
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
	
	//For moving by holding key down.
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if(state[SDL_SCANCODE_LEFT]){
		game -> player.position.x -= MOVE_SPEED;
	}
	if(state[SDL_SCANCODE_RIGHT]){
		game -> player.position.x += MOVE_SPEED;
	}
	
	return keepPlaying;
}


void renderGame(SDL_Renderer *renderer, game * game){
	//Draws a white rectangle on blue backgtound
	//RGB + ALPHA
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect = { game -> player.position.x, game ->player.position.y, 200, 200 };
	SDL_RenderFillRect(renderer, &rect); 
	SDL_RenderPresent(renderer);
}