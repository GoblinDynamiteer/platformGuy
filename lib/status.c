#include "..\def.h"

//gets player status for CHECK
bool getPlayerStatus(game * game, int check){
	if(gPlayer.status & check){
		return 1;
	}
	return 0;
}

//Sets/unsets player status
void setPlayerStatus(game * game, int status, bool onOff){
	if(onOff){
		gPlayer.status |= status; //Bitwise OR
	}
	else{
		gPlayer.status &= (~status); //Bitwise NOT
	}
}

/*		Figures out current status of player and sets it to variable.	*/
void determinePlayerStatus(game * game, const Uint8 *state){
	/*		If player has stopped.	*/
	if(!gPlayer.velocity.right && !gPlayer.velocity.left){
		setPlayerStatus(game, STATUS_RUNNING, FALSE);
		setPlayerStatus(game, STATUS_SKIDDING, FALSE);
	}
	
	/*  Ducking  */
	if(state[SDL_SCANCODE_DOWN]){
		setPlayerStatus(game, STATUS_DUCKING, TRUE);
	}
	else{
		setPlayerStatus(game, STATUS_DUCKING, FALSE);
	}

	
	/*		Keypad Right is held down.	*/
	if(state[SDL_SCANCODE_RIGHT]){
		setPlayerStatus(game, STATUS_FACINGLEFT, FALSE);
		setPlayerStatus(game, STATUS_SKIDDING, FALSE);
	}
	
	/*		Keypad Left is held down.	*/
	if(state[SDL_SCANCODE_LEFT]){
		setPlayerStatus(game, STATUS_FACINGLEFT, TRUE);
		setPlayerStatus(game, STATUS_SKIDDING, FALSE);
	}
	
	/*		Player is moving right.	*/
	if(gPlayer.velocity.right > 0){
		setPlayerStatus(game, STATUS_RUNNING, TRUE);
		/*		If player has let go of button.	*/
		if(!state[SDL_SCANCODE_RIGHT] && !gPlayer.velocity.left){
			setPlayerStatus(game, STATUS_SKIDDING, TRUE);
		}
	}

	/*		Player is moving left.	*/
	if(gPlayer.velocity.left > 0){
		setPlayerStatus(game, STATUS_RUNNING, TRUE);
		/*		If player has let go of button.	*/
		if(!state[SDL_SCANCODE_LEFT] && !gPlayer.velocity.right){
			setPlayerStatus(game, STATUS_SKIDDING, TRUE);
		}
	}
	
	/*		PlayerFeet is lowest pixel to the left.	Hitbox varies. */
	int playerFeet = gPlayer Y + gPlayer.hitbox.h;
	/*		If player is on or below (temporary) ground level	*/
	if(playerFeet >= LANDLINE){
		setPlayerStatus(game, STATUS_AIRBORNE, FALSE);
	}
	/*		Player is in the air.	*/
	else{
		setPlayerStatus(game, STATUS_AIRBORNE, TRUE);
		setPlayerStatus(game, STATUS_SKIDDING, FALSE);
		setPlayerStatus(game, STATUS_DUCKING, FALSE);
	}
}


/*		Gets player status and returns appropriate texture to render.	*/
int determinePlayerTexture(game * game){
	int texture = TEXTURE_IDLE;

	if(getPlayerStatus(game, STATUS_RUNNING)){
		texture = TEXTURE_RUNNING;
	}
	
	if(getPlayerStatus(game, STATUS_SKIDDING)){
		texture = TEXTURE_SKIDDING;
	}
	
	if(getPlayerStatus(game, STATUS_DUCKING)){
		texture = TEXTURE_DUCKING;
	}
	
	if(getPlayerStatus(game, STATUS_AIRBORNE)){
		texture = TEXTURE_JUMP_CLIPPED;
	}

	return texture;
}