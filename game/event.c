/*
 * event.c
 *
 *  Created on: 9 jan. 2017
 *      Author: kampe_000
 */

#include "..\def.h"

bool getEvents(game * game){
	game->timer++;
	SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				/*	 Exit button pressed on window	*/
				case SDL_WINDOWEVENT_CLOSE:
					SDL_DestroyWindow(game->window);
					game->window = NULL;
					return 0;
					break;
				/*	 A key has been pressed down	*/
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						/*	 Escape button	*/
						case SDLK_ESCAPE:
							return 0;
						/*	 Up arrow key, jumps	*/
						case SDLK_UP:
							playerJump(game);
							break;
						/*	 Down arrow key, ducks	*/
						case SDLK_DOWN:
							game->player.status[DUCK] = TRUE;
							break;
						case SDLK_LEFT:
						case SDLK_RIGHT:
							setRunStatus(game);
							break;
						}

					break;
				/*	 A key has been released	*/
				case SDL_KEYUP:
					switch(event.key.keysym.sym){
						case SDLK_DOWN:
							game->player.status[DUCK] = FALSE;
							break;
						case SDLK_LEFT:
						case SDLK_RIGHT:
							game->player.status[RUN] = FALSE;
							if(fabs(game->player.speed.x) > MAX_SPEED - 1){
								game->player.status[SKID] = TRUE;
							}
							break;
					}
			}
		}

	/*	 Gets key states	*/
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if(!game->player.status[DUCK]){
		if(state[SDL_SCANCODE_RIGHT]){
			setRunStatus(game);
			playerSetSpeed(game, RIGHT);
			game->player.direction = RIGHT;
		}

		if(state[SDL_SCANCODE_LEFT]){
			setRunStatus(game);
			playerSetSpeed(game, LEFT);
			game->player.direction = LEFT;
		}
	}

	if(state[SDL_SCANCODE_UP] &&
			game->player.status[AIR]){
		playerJump(game);
	}

	playerSlow(game);
	playerMove(game);

	return 1;
}

