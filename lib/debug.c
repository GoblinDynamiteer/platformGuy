#include "..\def.h"

void debugInfo(game * game){
	if(gTimer % DEBUG_OUTPUT_SPEED == 0){
		int playerFeet = gPlayer Y + gPlayer.hitbox.h;
		if(DEBUG_MOVEMENT){
			if(getPlayerStatus(game, STATUS_RUNNING)){
				printf("[ Running ");
				if(getPlayerStatus(game, STATUS_FACINGLEFT)){
					printf("Left ]");
				}
				else{
					printf("Right ]");
				}
				printf(" [Velocity L/R: %g/%g ] [Player X: %d ]\n", 
					gPlayer.velocity.left, gPlayer.velocity.right, gPlayer X);
			}
			if(getPlayerStatus(game, STATUS_SKIDDING)){
				printf(" [ Skidding! ] \n");
			}
		}
		if(DEBUG_JUMPING){
			if(getPlayerStatus(game, STATUS_AIRBORNE)){
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
	}
}
