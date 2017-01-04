#include "..\def.h"

int getRandomHeight(){
	return rand() % WINDOW_HEIGHT;
}

int getRandomWidth(){
	return rand() % WINDOW_WIDTH;
}

int getRandomAngle(){
	return rand() % 360;
}