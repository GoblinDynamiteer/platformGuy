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
#define PLAYER_FRAME_HEIGHT 279
#define PLAYER_FRAME_WIDTH 197
#define LANDLINE 900
#define JUMP_SPEED 20
#define BOMBS 10
#define gRen game -> renderer
#define gWin game -> window
#define gKey game -> keys
#define gPlayer game -> player
#define gGravity game -> gravity
#define gTimer game -> timer
#define X .position.x
#define Y .position.y
#define gBomb(VAR) game -> bomb[VAR]

/* Player Status flags */
#define STATUS_AIRBORNE 1		// 0001
#define STATUS_FACINGLEFT 2	// 0010
#define STATUS_ALIVE 4			// 0100
#define STATUS_RUNNING 8			// 1000
#define STATUS_SKIDDING 16			// 1 0000
#define STARTINGSTATUS 0

#define DEBUG_OUTPUT_SPEED 20
#define DEBUG_MOVEMENT 0
#define DEBUG_JUMPING 0
#define DEBUG_HITBOX 1

enum {FALSE, TRUE};
enum {OFF, ON};

//Player textures
enum {TEXTURE_IDLE, TEXTURE_RUNNING, TEXTURE_JUMP, TEXTURE_SKIDDING};

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
	short textureFrameSize[4];
	SDL_Texture *texture[4];
	short frame;
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
	U64 timer;
	keys keys;
}game;


/* FUNCTION DEFINITIONS */

//status.c
bool getPlayerStatus(game * game, int check);
void setPlayerStatus(game * game, int status, bool onOff);

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
void animatePlayer(game * game);

//load.c
bool loadGame(game * game);
bool loadTextures(game * game);


/* END GUARD */
#endif

