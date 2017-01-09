/*
 * draw.c
 *
 *  Created on: 9 jan. 2017
 *      Author: kampe_000
 */

#include "..\def.h"

void renderGame(game * game){
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
	SDL_RenderClear(game->renderer);

	drawPlayer(game);

	/*	 Presents render	*/
	SDL_RenderPresent(game->renderer);
}

void drawPlayer(game * game){

	SDL_Rect src = {0,0,0,0};

	SDL_QueryTexture(game->player.texture[IDLE], NULL, NULL, &src.w, &src.h);

	src.w /= game->player.maxFrames[IDLE];
	src.x = game->player.rect.x;
	src.x = src.w * 1;

	SDL_RenderCopyEx(
			game->renderer,
			game->player.texture[IDLE],
			&src,
			&game->player.rect,
			0.0,
			NULL,
			SDL_FLIP_NONE
	);

}

