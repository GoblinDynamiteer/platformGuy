/*
 * world.c
 *
 *  Created on: 10 jan. 2017
 *      Author: kampe
 */

#include "..\def.h"

bool checkCollision(game * game){
	if(game->player.rect.y > 600){
		return 0;
	}
	return 1;
}
