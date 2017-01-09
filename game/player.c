/*
 * player.c
 *
 *  Created on: 9 jan. 2017
 *      Author: kampe_000
 */

#include "..\def.h"

void playerSpeed(game * game, bool direction){
	if(direction == LEFT){
		game->player.speed.x -= RUN_ACC;
		if(fabs(game->player.speed.x) >= MAX_SPEED){
			game->player.speed.x = MAX_SPEED * -1;
		}
	}
	else{
		game->player.speed.x += RUN_ACC;
		if(fabs(game->player.speed.x) >= MAX_SPEED){
			game->player.speed.x = MAX_SPEED;
		}
	}
}

void movePlayer(game * game){
	game->player.rect.x += game->player.speed.x;
}
