#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define MOVE_SPEED 5
#define BOMBS 10



//Positions for player and monsters etc
typedef struct{
	int x,y;
}position;

typedef struct{
	short life;
	char *name;
	position position;
}player;

typedef struct{
	SDL_Texture *texture;
	char *name;
	position position;
}enemy;

typedef struct{
	player player;
	enemy bomb[BOMBS];
	SDL_Renderer *renderer;
	SDL_Window *window;
}game;

#define gRen game -> renderer
#define gWin game -> window
#define gPlayer game -> player
#define X .position.x
#define Y .position.y
#define gBomb(VAR) game -> bomb[VAR]


