#include "..\def.h"

//gets player status for CHECK
bool getStatus(game * game, int check){
	if(gPlayer.status & check){
		return 1;
	}
	return 0;
}

//Sets/unsets player status
void setStatus(game * game, int status, bool onOff){
	if(onOff){
		gPlayer.status |= status; //Bitwise OR
	}
	else{
		gPlayer.status &= (~status); //Bitwise NOT
	}
}

/*		Figures out current status of player and sets it to variable.	*/
void determinePlayerStatus(game * game, const Uint8 *state){
	/* If attack-animation has cycled */
	if(gPlayer.drawTexture == TE_ATK_T 
		&& gPlayer.frame == gPlayer.textureFrameSize[TE_ATK_T] -1){
			setStatus(game, ST_ATK_T, FALSE);
	}
	
	if(gPlayer.drawTexture == TE_ATK_S 
		&& gPlayer.frame == gPlayer.textureFrameSize[TE_ATK_S] -1){
			setStatus(game, ST_ATK_S, FALSE);
	}
	
	/*		If player has stopped.	*/
	if(!gPlayer.velocity.right && !gPlayer.velocity.left){
		setStatus(game, ST_RUN, FALSE);
		setStatus(game, ST_SKID, FALSE);
	}
	
	/*  Ducking  */
	if(state[DKEY]){
		setStatus(game, ST_DUCK, TRUE);
	}
	else{
		setStatus(game, ST_DUCK, FALSE);
	}

	
	/*		Keypad Right is held down.	*/
	if(state[RKEY]){
		setStatus(game, ST_LEFT, FALSE);
		setStatus(game, ST_SKID, FALSE);
	}
	
	/*		Keypad Left is held down.	*/
	if(state[LKEY]){
		setStatus(game, ST_LEFT, TRUE);
		setStatus(game, ST_SKID, FALSE);
	}
	
	/*		Player is moving right.	*/
	if(gPlayer.velocity.right > 0){
		setStatus(game, ST_RUN, TRUE);
		/*		If player has let go of button.	*/
		if(!state[RKEY] && !gPlayer.velocity.left){
			setStatus(game, ST_SKID, TRUE);
		}
	}

	/*		Player is moving left.	*/
	if(gPlayer.velocity.left > 0){
		setStatus(game, ST_RUN, TRUE);
		/*		If player has let go of button.	*/
		if(!state[SDL_SCANCODE_LEFT] && !gPlayer.velocity.right){
			setStatus(game, ST_SKID, TRUE);
		}
	}
	
	/*		event.c sets air status.	*/
	if(getStatus(game, ST_AIR)){
		setStatus(game, ST_SKID, FALSE);
		setStatus(game, ST_DUCK, FALSE);
	}
}


/*		Gets player status and returns appropriate texture to render.	*/
int determinePlayerTexture(game * game){
	int texture = TE_IDLE;

	/*		Makes sure no other animation will play when attacking.	*/
	if(getStatus(game, ST_ATK_T)){
		texture = TE_ATK_T;
	}
	
	else if(getStatus(game, ST_ATK_S)){
		texture = TE_ATK_S;
	}
	
	/*		If not attacking.	*/
	else{
		if(getStatus(game, ST_RUN)){
		texture = TE_RUN;
		}
		
		if(getStatus(game, ST_SKID)){
			texture = TE_SKID;
		}
		
		if(getStatus(game, ST_DUCK)){
			texture = TE_DUCK;
		}
		
		if(getStatus(game, ST_AIR)){
			texture = TE_AIR;
		}
	}

	return texture;
}