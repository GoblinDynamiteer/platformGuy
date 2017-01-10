/*
 * event.c
 *
 *  Created on: 9 jan. 2017
 *      Author: kampe_000
 */

#include "..\def.h"

bool getEvents(game * game){

	SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				/*	 Exit button pressed on window	*/
				case SDL_WINDOWEVENT_CLOSE:
					if(game->window){
						SDL_DestroyWindow(game->window);
						game->window = NULL;
						return 0;
					}
					break;
				/*	 A key has been pressed down	*/
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						/*	 Escape button	*/
						case SDLK_ESCAPE:
							return 0;
						case SDLK_UP:
							playerJump(game);
							break;
					}
					break;
			}
		}

	/*	 Gets key states	*/
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if(state[SDL_SCANCODE_RIGHT]){
		playerSetSpeed(game, RIGHT);
		game->player.direction = RIGHT;
	}

	if(state[SDL_SCANCODE_LEFT]){
		playerSetSpeed(game, LEFT);
		game->player.direction = LEFT;
	}

	if(state[SDL_SCANCODE_UP] &&
			game->player.status[AIR]){
		playerJump(game);
	}

	playerMove(game);
	playerSlow(game);
	// SDL_HasIntersection
	return 1;
}

