/*
 * world.c
 *
 *  Created on: 10 jan. 2017
 *      Author: kampe
 */

#include "..\def.h"

bool checkCollision(game * game){

	/*	 Checks for intersection between two rectangles.	*/
	if(SDL_HasIntersection(
			&game->player.rect,
			&game->ground.rect) == SDL_TRUE){
		return 1;
	}

	if(SDL_HasIntersection(
			&game->player.rect,
			&game->pillar.rect) == SDL_TRUE){
		return 1;
	}
	return 0;
}
