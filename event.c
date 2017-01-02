#include "main.h"
#include "event.h"

/* Macros:
	gRen				game -> renderer
	gWin				game -> window
	gPlayer			game -> player
	gBomb(VAR)	game -> bomb[VAR]
	X .position.x
	Y .position.y
*/

int processEvent(game *game){
	SDL_Event event;
	int keepPlaying = 1;
	while(SDL_PollEvent(&event)){ //SDL_PollEvent returns true if an event shall be processed
		switch(event.type){
			case SDL_WINDOWEVENT_CLOSE:
				if(gWin){
					SDL_DestroyWindow(gWin);
					gWin = NULL;
				}
				break;
			//Key has been pressed:
			case SDL_KEYDOWN:
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

	debugInfo(game);
	
	//For moving by holding key down.
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if(state[SDL_SCANCODE_LEFT]){
		gPlayer X -= MOVE_SPEED;
	}
	if(state[SDL_SCANCODE_RIGHT]){
		gPlayer X += MOVE_SPEED;
	}
	if(state[SDL_SCANCODE_UP]){
		gPlayer Y -= MOVE_SPEED;
	}
	if(state[SDL_SCANCODE_DOWN]){
		gPlayer Y += MOVE_SPEED;
	}
	
	//Check bomb collision
	for(int i=0;i<BOMBS;i++){
		SDL_Rect bombRect = {gBomb(i) X, gBomb(i) Y, 250/2, 250/2 };
		SDL_RenderCopy(gRen, gBomb(i).texture, NULL, &bombRect);
	}
	
	return keepPlaying;
}

void renderGame(game * game){
	//Draws a white rectangle on blue backgtound
	//RGB + ALPHA
	SDL_SetRenderDrawColor(gRen, 0, 0, 255, 255);
	SDL_RenderClear(gRen);
	SDL_SetRenderDrawColor(gRen, 255, 255, 255, 255);
	
	//Render bomb images
	//Create rectangles to hold bombs image, same size as image: 250 x 250px
	for(int i=0;i<BOMBS;i++){
		SDL_Rect bombRect = { gBomb(i) X, gBomb(i) Y, 250/2, 250/2 };
		SDL_RenderCopy(gRen, gBomb(i).texture, NULL, &bombRect);
	}
	//Render "Player" rectangle
	SDL_Rect playerRect = {gPlayer X, gPlayer Y, 150, 220};
	SDL_RenderCopy(gRen, gPlayer.texture, NULL, &playerRect);
	
	SDL_RenderPresent(gRen);
}

//Shuts down game, destroys windows, textures, renderer
void shutdownGame(game * game){
	for(int i=0;i<BOMBS;i++){
		SDL_DestroyTexture(gBomb(i).texture);
	}
	SDL_DestroyWindow(gWin);
	SDL_DestroyRenderer(gRen);
	//Quit SDL
	SDL_Quit();
}


int loadGame(game * game){

	//Player starting coordinates
	gPlayer X = 12;
	gPlayer Y = WINDOW_HEIGHT / 2;

	SDL_Surface *surface = NULL; //For holding image
	//Loads images
	surface = IMG_Load("art/player/guy.png");
	if(surface == NULL){
		printf("Can't load guy.png");
		SDL_Quit();
		return 0;
	}
	gPlayer.texture = SDL_CreateTextureFromSurface(gRen, surface);
	
	surface = IMG_Load("art/enemies/bomb.png");
	if(surface == NULL){
		printf("Can't load bomb.png");
		SDL_Quit();
		return 0;
	}
	/* Sets image to SDL_Texture "bomb" in game struct
		Might be bad idea to set texture to every bomb/enemy in array... */
	for(int i=0;i<BOMBS;i++){
		gBomb(i).texture = SDL_CreateTextureFromSurface(gRen, surface);
		gBomb(i) X = getRandomWidth();
		gBomb(i) Y = getRandomHeight();
	}
	SDL_FreeSurface(surface); //Unload, not needed anymore
	return 1;
}