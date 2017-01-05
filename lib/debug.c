#include "..\def.h"

void debugInfo(game * game){
	if(gTimer % DEBUG_OUTPUT_SPEED == 0){
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
		}
		if(DEBUG_JUMPING){
			if(getPlayerStatus(game, STATUS_AIRBORNE)){
				printf("[ Jumping ] [Velocity: %g ] [Player Y: %d ]\n", 
					gPlayer.velocity.up, gPlayer Y);
			}
		}
		if(DEBUG_HITBOX){
			printf("[ Player Hitbox H/W: %d/%d ]\n",
				gPlayer.hitbox.h, gPlayer.hitbox.w);
		}
	}
}
