/* GUARD */
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
#define PLAYER_FRAME_HEIGHT 280
#define PLAYER_FRAME_WIDTH 197
#define LANDLINE 900
#define JUMP_SPEED 20
#define BOMBS 10

#define gRen game -> renderer
#define gWin game -> window
#define gKey game -> keys
#define gPlayer game -> player
#define gLevel game -> level
#define gGravity game -> gravity
#define gTimer game -> timer
#define X .position.x
#define Y .position.y
#define W .hitbox.w
#define H .hitbox.h
#define gBomb game -> bomb

/*	 "Get Texture Dimensions"	*/
#define gtd(t,w,h) SDL_QueryTexture(t, NULL, NULL, w, h)



/* Player Status flags */
#define ST_AIR 1		// 0001
#define ST_LEFT 2	// 0010
#define ST_ALIVE 4			// 0100
#define ST_RUN 8			// 1000
#define ST_SKID 16			// 1 0000
#define ST_DUCK 32			// 10 0000
#define ST_ATK_T 64			// 100 0000
#define ST_ATK_S 128			// 1000 0000
#define ST_INIT 0

#define DEBUG_OUTPUT_SPEED 5
#define DEBUG_MOVEMENT 0
#define DEBUG_JUMPING 0
#define DEBUG_HITBOX 0
#define DEBUG_ATTACK 1

#define RKEY SDL_SCANCODE_RIGHT
#define LKEY SDL_SCANCODE_LEFT
#define DKEY SDL_SCANCODE_DOWN
#define UKEY SDL_SCANCODE_UP

enum {FALSE, TRUE};
enum {OFF, ON};

//Player textures
enum {TE_IDLE, TE_RUN, TE_AIR, TE_SKID, TE_DUCK, TE_NULL, TE_ATK_T, TE_ATK_S};

typedef unsigned long long U64;

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
	int w, h;
}hitbox;

typedef struct{
	//short life;
	double angle;
	U64 status; //Airborne, facing, alive etc
	velocity velocity;
	//char *name;
	position position;
	hitbox hitbox;
	short drawTexture;
	short textureFrameSize[20];
	SDL_Texture *texture[20];
	short frame;
}player;

typedef struct{
	//short fallfactor;
	SDL_Texture *texture;
	//char *name;
	position position;
}enemy;

typedef struct{
	SDL_Texture *texture;
	SDL_Rect rect;
	position position;
	hitbox hitbox;
}level;

typedef struct{
	player player;
	enemy bomb[BOMBS];
	SDL_Renderer *renderer;
	SDL_Window *window;
	int gravity;
	U64 timer;
	keys keys;
	level level;
}game;


/* FUNCTION DEFINITIONS */

//status.c
bool getStatus(game * game, int check);
void setStatus(game * game, int status, bool onOff);
int determinePlayerTexture(game * game);
void determinePlayerStatus(game * game, const Uint8 *state);

//random.c
int getRandomHeight();
int getRandomWidth();
int getRandomAngle();

//debug.c
void debugInfo(game * game);

//event.c
int processEvent(game *game);
void renderGame(game * game);
void shutdownGame(game * game);
void renderPlayer(game * game);

//load.c
bool loadGame(game * game);
bool loadTextures(game * game);


/* END GUARD */
#endif

