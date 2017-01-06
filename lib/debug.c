#include "..\def.h"

void debugInfo(game * game){
	if(gTimer % DEBUG_OUTPUT_SPEED == 0){
		int playerFeet = gPlayer Y + gPlayer.hitbox.h;
		if(DEBUG_MOVEMENT){
			if(getStatus(game, ST_RUN)){
				printf("[ Running ");
				if(getStatus(game, ST_LEFT)){
					printf("Left ]");
				}
				else{
					printf("Right ]");
				}
				printf(" [Velocity L/R: %g/%g ] [Player X: %d ]\n", 
					gPlayer.velocity.left, gPlayer.velocity.right, gPlayer X);
			}
			if(getStatus(game, ST_SKID)){
				printf(" [ Skidding! ] \n");
			}
		}
		if(DEBUG_JUMPING){
			if(getStatus(game, ST_AIR)){
				printf("[ Jumping ] [Velocity: %g ] [Player Y: %d ] ", 
					gPlayer.velocity.up, gPlayer Y);
			}
			printf("[ Feet Y: %d ] \n", playerFeet);
		}
		if(DEBUG_HITBOX){
			printf("[ Player Hitbox H/W: %d/%d ]\n",
				gPlayer.hitbox.h, gPlayer.hitbox.w);
		}
		if(playerFeet>LANDLINE){
		printf("[ Under Landline! ] \n");
		}
		if(DEBUG_ATTACK){
			if(getStatus(game, ST_ATK_T)){
				printf("[ Attacking: Thrust ]\n");
			}
			if(getStatus(game, ST_ATK_S)){
				printf("[ Attacking: Swing ]\n");
			}
		}
	}
}
