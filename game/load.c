/*
 * load.c
 *
 *  Created on: 9 jan. 2017
 *      Author: kampe_000
 */

#include "..\def.h"

bool loadGame(game * game){
	/*	 Random seed	*/
	srand((int)time(NULL));

	/*	 Sets starting statuses to zero.	*/
	for(int i = 0; i< STATUS_MAX; i++){
		 game->player.currentFrame[i] = 0;
		 game->player.status[i] = 0;
	}

	game->player.status[IDLE] = 1;
	game->player.direction = RIGHT;

	/*	 Frames in each sprite sheet.	*/
	game->player.maxFrames[IDLE] = 17;
	game->player.maxFrames[AIR] = 2;
	game->player.maxFrames[RUN] = 14;
	game->player.maxFrames[SKID] = 15;
	game->player.maxFrames[DUCK] = 7;
	game->player.maxFrames[ATK1] = 14;
	game->player.maxFrames[ATK1] = 13;

	/*	 Player starting coordinates	*/
	game->player.rect.x = WINDOW_WIDTH/2 - 200;
	game->player.rect.y = WINDOW_HEIGHT/2;

	/*	 Player rectangle size	*/
	game->player.rect.w = 130;
	game->player.rect.h = 260;

	/*	 Player velocity	*/
	game->player.speed.x = 0.0;
	game->player.speed.y = 0.0;

	game->timer = 0ull;

	loadWorld(game);

	return 1;
}


bool loadTextures(game * game){

	/*	Load player art.	*/
	/*	index: IDLE, AIR, RUN, SKID, DUCK, ATK1, ATK2 */
	const char * imageFiles[] = {
			"art/player/girl_idle.png",
			"art/player/girl_airborne.png",
			"art/player/girl_running.png",
			"art/player/girl_running_skid.png",
			"art/player/girl_crouch.png",
			"art/player/girl_attack1.png",
			"art/player/girl_attack2.png"
	};

	/*	 Temporary surface	*/
	SDL_Surface * surface = NULL;

	/*	 Player textures	*/
	for(int i = 0; i < STATUS_MAX; i++){
		surface = IMG_Load(imageFiles[i]);
		if(surface == NULL){
			printf("Could not image file for player!\n");
		}
		game->player.texture[i] =
				SDL_CreateTextureFromSurface(game->renderer, surface);
	}

	/*	 World textures	*/
	surface = IMG_Load("art/levels/ground/grass_stone_small_gradient.png");
	if(surface == NULL){
		printf("Could not image file for ground!\n");
	}

	/*	 Set ground texture	*/
	game->ground.texture =
			SDL_CreateTextureFromSurface(game->renderer, surface);
	SDL_FreeSurface(surface);

	SDL_FreeSurface(surface);
	return 1;
}

/*	 Sets data for world	*/
void loadWorld(game * game){
	/*	 Ground rectangle	*/
	game->ground.rect.x = 0;
	game->ground.rect.y = 900;
	game->ground.rect.w = WINDOW_WIDTH;
	game->ground.rect.h = WINDOW_HEIGHT-game->ground.rect.y;

	/*	 Obstacle rectangle	*/
	game->pillar.rect.w = 200;
	game->pillar.rect.h = 300;
	game->pillar.rect.x = WINDOW_WIDTH / 2 + 200;
	game->pillar.rect.y = game->ground.rect.y - game->pillar.rect.h;

	game->ground.offset = 30;

}
