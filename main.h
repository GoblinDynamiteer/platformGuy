#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define LANDLINE 1080-300
#define MOVE_SPEED 8
#define JUMP_SPEED 20
#define GRAVITY 7
#define BOMBS 10

//Positions for player and monsters etc
typedef struct{
	int x,y;
}position;

typedef struct{
	//short life;
	short airborne;
	short jumpHeight;
	//char *name;
	position position;
	SDL_Texture *texture;
}player;

typedef struct{
	//short fallfactor;
	SDL_Texture *texture;
	//char *name;
	position position;
}enemy;

typedef struct{
	player player;
	enemy bomb[BOMBS];
	SDL_Renderer *renderer;
	SDL_Window *window;
}game;

#include "event.h"
#include "lib/random.h"
#include "lib/debug.h"

#define gRen game -> renderer
#define gWin game -> window
#define gPlayer game -> player
#define X .position.x
#define Y .position.y
#define gBomb(VAR) game -> bomb[VAR]


