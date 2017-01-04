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