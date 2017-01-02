#include "main.h"
#include "event.h"

int processEvent(game *game){
	SDL_Event event;
	int keepPlaying = 1;
	while(SDL_PollEvent(&event)){ //SDL_PollEvent returns true if an event shall be processed
		switch(event.type){
			case SDL_WINDOWEVENT_CLOSE:
				if(game -> window){
					SDL_DestroyWindow(game -> window);
					game -> window = NULL;
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

void renderGame(game * game){
	//Draws a white rectangle on blue backgtound
	//RGB + ALPHA
	SDL_SetRenderDrawColor(game -> renderer, 0, 0, 255, 255);
	SDL_RenderClear(game -> renderer);
	SDL_SetRenderDrawColor(game -> renderer, 255, 255, 255, 255);
	
	//Render bomb images
	//Create rectangles to hold bombs image, same size as image: 250 x 250px
	for(int i=0;i<BOMBS;i++){
		SDL_Rect bombRect = { game -> bomb[i].position.x, game -> bomb[i].position.y, 250/2, 250/2 };
		SDL_RenderCopy(game -> renderer, game -> bomb[i].texture, NULL, &bombRect);
	}
	//Render "Player" rectangle
	SDL_Rect rect = { game -> player.position.x, game ->player.position.y, 200, 200 };
	SDL_RenderFillRect(game -> renderer, &rect); 
	
	SDL_RenderPresent(game -> renderer);
}

//Shuts down game, destroys windows, textures, renderer
void shutdownGame(game * game){
	SDL_DestroyTexture(game -> bomb[0].texture);
	SDL_DestroyWindow(game -> window);
	SDL_DestroyRenderer(game -> renderer);
	//Quit SDL
	SDL_Quit();
}


int loadGame(game * game){

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
	for(int i=0;i<BOMBS;i++){
		game -> bomb[i].texture = SDL_CreateTextureFromSurface(game -> renderer, surface);
		game -> bomb[i].position.x = i * 100 + 10;
		game -> bomb[i].position.y = i * 50 + 10; 
	}
	SDL_FreeSurface(surface); //Unload, not needed anymore
	return 1;
}