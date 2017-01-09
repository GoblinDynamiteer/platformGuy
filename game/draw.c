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

	/*	 Source and destination rectangles	*/
	SDL_Rect src = {0,0,0,0};
	SDL_Rect dest = {0,0,0,0};

	/*	 Gets height and width from image	*/
	SDL_QueryTexture(game->player.texture[AIR], NULL, NULL, &src.w, &src.h);

	/*	 Get correct frame in sprite sheet	*/
	src.w /= game->player.maxFrames[AIR];
	src.x = game->player.rect.x;
	src.x = src.w * 1;

	/*	 Set destination rectangle values, middle of player rectangle	*/
	dest.w = src.w;
	dest.h = src.h;
	dest.x = game->player.rect.x - game->player.rect.w /2;
	dest.y = game->player.rect.y - game->player.rect.h /2;

	/*	 Draw part of texture in src rectangle to dest rectangle	*/
	SDL_RenderCopyEx(
			game->renderer,
			game->player.texture[AIR],
			&src,
			&dest,
			0.0,
			NULL,
			game->player.direction
	);

}

