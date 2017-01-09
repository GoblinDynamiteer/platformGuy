
#ifndef DEF_H
#define DEF_H

#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/*	 Window dimensions	*/
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

/*	 Renderer flags	*/
#define RENDERER_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

/*	 Player statuses	*/
enum {IDLE, AIR, RUN, SKID, DUCK, ATK1, ATK2};
#define STATUS_MAX 7

/*	 Movement	*/
enum {LEFT, RIGHT};
#define RUN_ACC 0.15

/*	 Min/Max values	*/
#define MAX_SPEED 25.0
#define MIN_SPEED 0.0

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
}player;

typedef struct game{
	SDL_Renderer * renderer;
	SDL_Window * window;
	player player;
}game;

/*	 Functions	*/
/*	 load.c	*/
bool loadGame(game * game);
bool loadTextures(game * game);

/*	 event.c	*/
bool getEvents(game * game);

/*	 draw.c	*/
void renderGame(game * game);
void drawPlayer(game * game);

/*	 player.c	*/
void playerSpeed(game * game, bool direction);
void movePlayer(game * game);

#endif

