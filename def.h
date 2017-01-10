
#ifndef DEF_H
#define DEF_H

#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

/*	 Window dimensions	*/
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

/*	 Renderer flags	*/
#define RENDERER_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

/*	 Player statuses	*/
enum {IDLE, AIR, RUN, SKID, DUCK, ATK1, ATK2};
#define STATUS_MAX 7

#define FRAME_UPDATE_SPEED 4

/*	 Movement	*/
enum {RIGHT, LEFT};
#define RUN_ACC 0.85
#define RUN_FRIC 0.25
#define JUMP_ACC 0.6

/*	 Min/Max values	*/
#define MAX_SPEED 9.5
#define MAX_FALL_SPEED 18.0
#define MIN_SPEED 0.0
#define MAX_JUMP_SPEED 25.0
#define JUMP_STR 19.5
#define GRAV 1.2

enum {FALSE, TRUE};

/*	 Structs	*/
typedef struct xy{
	double x;
	double y;
}xy;

typedef struct player{
	bool status[STATUS_MAX];
	SDL_Texture * texture[STATUS_MAX];
	int maxFrames[STATUS_MAX];
	int currentFrame[STATUS_MAX];
	SDL_Rect rect;
	xy speed;
	bool direction;
}player;

typedef struct worldPieces{
	SDL_Rect rect;
	bool obstacle;
	SDL_Texture * texture;
}world;


typedef struct game{
	SDL_Renderer * renderer;
	SDL_Window * window;
	player player;
	Uint64 timer;
	world ground;
}game;

/*	 Functions	*/
/*	 load.c	*/
bool loadGame(game * game);
bool loadTextures(game * game);
void loadWorld(game * game);

/*	 event.c	*/
bool getEvents(game * game);

/*	 draw.c	*/
void renderGame(game * game);
void drawPlayer(game * game);
void drawWorld(game * game);
int determineTexture(game * game);
int getFrame(game * game, int texture);

/*	 player.c	*/
void playerSetSpeed(game * game, bool direction);
void playerMove(game * game);
void playerSlow(game * game);
void playerJump(game * game);

/*	 world.c	*/
bool checkCollision(game * game);

#endif

