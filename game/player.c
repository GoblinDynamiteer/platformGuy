/*
 * player.c
 *
 *  Created on: 9 jan. 2017
 *      Author: kampe_000
 */

#include "..\def.h"

void playerSetSpeed(game * game, bool direction){
	game->player.status[RUN] = 1;

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

void playerMove(game * game){
	game->player.rect.x += game->player.speed.x;
	if(checkCollision(game)){
		game->player.speed.x = 0;
		setIdleStatus(game);
		while(checkCollision(game)){
			if(game->player.direction == RIGHT){
				game->player.rect.x--;
			}
			else{
				game->player.rect.x++;
			}

		}
	}

	game->player.rect.y += game->player.speed.y;
	if(checkCollision(game)){
		game->player.status[AIR] = FALSE;
		while(checkCollision(game)){
			game->player.rect.y--;
		}
	}
}

void playerSlow(game * game){

	/*	 Affect player with gravity	*/
	game->player.speed.y += GRAV;

	/*	 Limit falling speed	*/
	if(game->player.speed.y > MAX_FALL_SPEED){
		game->player.speed.y = MAX_FALL_SPEED;
	}

	/*	 Slow down running	*/
	if(game->player.speed.x > 0){
		game->player.speed.x -= RUN_FRIC;
	}
	else if(game->player.speed.x < 0){
		game->player.speed.x += RUN_FRIC;
	}

	/*	 Stop player	*/
	if((game->player.speed.x <= 0 && game->player.direction == RIGHT) ||
			(game->player.speed.x >= 0 && game->player.direction == LEFT)){
				game->player.speed.x = 0.0;
				setIdleStatus(game);
	}
}

void playerJump(game * game){
	if(!game->player.status[AIR]){
		/*	 Default jump strength	*/
		game->player.speed.y = JUMP_STR * -1;

		/*	 Set AIR status ON	*/
		game->player.status[AIR] = 1;
	}

	if(game->timer % 4 == 0){
		printf("Acc speed Up: %g\n");
	}
	game->player.speed.y -= JUMP_ACC;
	if(game->player.speed.y >= MAX_JUMP_SPEED){
		game->player.speed.y = MAX_JUMP_SPEED;
	}

}

void setIdleStatus(game * game){
	game->player.status[RUN] = 0;
	game->player.status[SKID] = 0;
	game->player.status[IDLE] = 1;
}

