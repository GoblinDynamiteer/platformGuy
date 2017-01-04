#include "..\def.h"

bool getStatus(game * game, int check){
	if(gPlayer.status & check){
		return 1;
	}
	return 0;
}