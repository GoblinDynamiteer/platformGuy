#ifndef DEF_H
#define DEF_H

/* INCLUDES */
#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


/* MACROS */
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define LANDLINE 1080-300
#define JUMP_SPEED 20
#define BOMBS 10
#define gRen game -> renderer
#define gWin game -> window
#define gKey game -> keys
#define gPlayer game -> player
#define gGravity game -> gravity
#define timerStart game -> timer
#define X .position.x
#define Y .position.y
#define gBomb(VAR) game -> bomb[VAR]

/* STRUCTS */

//Positions for player and monsters etc
typedef struct{
	int x,y;
}position;

typedef struct{
	bool upKeyReleased;
}keys;

typedef struct{
	float left, right, up, down;
	float maxUp, maxDown, maxLeft, maxRight;
}velocity;

typedef struct{
	int x, y;
}hitbox;

typedef struct{
	//short life;
	short flip;
	double angle;
	bool airborne;
	velocity velocity;
	//char *name;
	position position;
	hitbox hitbox;
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
	int gravity;
	Uint32 timer;
	keys keys;
}game;


/* FUNCTION DEFINITIONS */

//random.c
int getRandomHeight();
int getRandomWidth();
int getRandomAngle();

//debug.c
void debugInfo(game * game);

//event.c
int loadGame(game * game);
int processEvent(game *game);
void renderGame(game * game);
void shutdownGame(game * game);

#endif

