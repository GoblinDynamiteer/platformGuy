/*
 * draw.c
 *
 *  Created on: 9 jan. 2017
 *      Author: kampe_000
 */

#include "..\def.h"

/*	 Draws the game	*/
void renderGame(game * game){
	/*	 One colour background	*/
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
	SDL_RenderClear(game->renderer);

	drawWorld(game);
	drawPlayer(game);

	/*	 Presents render	*/
	SDL_RenderPresent(game->renderer);
}

/*	 Draws the player	*/
void drawPlayer(game * game){

	/*	 Source and destination rectangles	*/
	SDL_Rect src = {0,0,0,0};
	SDL_Rect dest = {0,0,0,0};

	/*	 Get texture to draw, depending on player activity	*/
	int i = determineTexture(game);

	/*	 Gets height and width from image	*/
	SDL_QueryTexture(game->player.texture[i], NULL, NULL, &src.w, &src.h);

	/*	 Get correct frame in sprite sheet	*/
	src.w /= game->player.maxFrames[i];
	src.x = game->player.rect.x;
	src.x = src.w * getFrame(game, i);

	/*	 Set all textures at same lower position	*/
	int heightDifference = game->player.rect.h - src.h;
	int widthDifference = game->player.rect.w - src.w;

	/*	 Set destination rectangle values	*/
	dest.w = src.w;
	dest.h = src.h;
	dest.x = game->player.rect.x + widthDifference / 2;
	dest.y = game->player.rect.y + heightDifference;

	/*	 Fill player rectangle with white - for debugging	*/
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(game->renderer, &game->player.rect);

	/*	 Draw part of texture in src rectangle to dest rectangle	*/
	SDL_RenderCopyEx(
			game->renderer,
			game->player.texture[i],
			&src,
			&dest,
			0.0,
			NULL,
			game->player.direction
	);

}

/*	 Draws world art	*/
void drawWorld(game * game){
	/*	 White colour	*/
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

	/*	 Height and width for destination rectangle	*/
	int w, h;
	SDL_QueryTexture(game->ground.texture, NULL, NULL, &w, &h);

	/*	 Renders texture over ground rectangle	*/
	for(int x = game->ground.rect.x; x < game->ground.rect.w; x += w){
		SDL_Rect dest = {x, game->ground.rect.y - game->ground.offset ,w ,h};
		SDL_RenderCopy(
				game->renderer,
				game->ground.texture,
				NULL,
				&dest
		);
	}

	/*	 Placeholder 	*/
	SDL_RenderFillRect(game->renderer, &game->pillar.rect);
}

/*	 Determines what player texture to show	*/
int determineTexture(game * game){
	if(game->player.status[ATK1]){
		return ATK1;
	}
	else if(game->player.status[ATK2]){
		return ATK2;
	}
	else if(game->player.status[AIR]){
		return AIR;
	}
	else if(game->player.status[DUCK]){
		return DUCK;
	}
	else if(game->player.status[SKID]){
		return SKID;
	}
	else if(game->player.status[RUN] &&
		!game->player.status[IDLE]){
		return RUN;
	}
	else{
		return IDLE;
	}
	return 0;
}

/*	 Determines what frame in player animation sprite to show	*/
int getFrame(game * game, int texture){
	if(game->timer % FRAME_UPDATE_SPEED == 0){
		game->player.currentFrame[texture]++;
		if(game->player.currentFrame[texture] >
			game->player.maxFrames[texture] - 1){
				game->player.currentFrame[texture] = 0;
		}

	}

	return game->player.currentFrame[texture];
}
