#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define MOVE_SPEED 5

typedef struct{
	int x,y;
}position;

typedef struct{
	short life;
	char *name;
	position position;
}player;

typedef struct{
	player player;
	SDL_Texture *bomb;
}game;


 