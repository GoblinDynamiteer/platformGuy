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
	//Render bomb image
	//Create rectangle to hold bomb image, same size as image: 250 x 250px
	SDL_Rect bombRect = { 50, 50, 250, 250 };
	SDL_RenderCopy(renderer, game -> bomb.texture, NULL, &bombRect);
	
	//Render "Player" rectangle

	SDL_Rect rect = { game -> player.position.x, game ->player.position.y, 200, 200 };
	SDL_RenderFillRect(renderer, &rect); 
	
	SDL_RenderPresent(renderer);
}

//Shuts down game, destroys windows, textures, renderer
void shutdownGame(SDL_Window *window, SDL_Renderer *renderer, game * game){
	SDL_DestroyTexture(game -> bomb.texture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//Quit SDL
	SDL_Quit();
}

//Loads game window, renderer
int loadGame(SDL_Renderer *renderer, game * game){

	//Player starting coordinates
	game -> player.position.x = WINDOW_WIDTH / 2;
	game -> player.position.y = WINDOW_HEIGHT / 2;

	SDL_Surface *surface = NULL; //For holding image
	//Loads image
	surface = IMG_Load("art/enemies/bomb.png");
	if(surface == NULL){
		printf("Can't load bomb.png");
		SDL_Quit();
		return 0;
	}
	//Sets image to SDL_Texture "bomb" in game struct
	game -> bomb.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface); //Unload, not needed anymore
	return 1;
}