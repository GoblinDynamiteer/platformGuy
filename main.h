#include "SDL.h"
#include <stdio.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define MOVE_SPEED 3

typedef struct{
	int x,y;
	short life;
	char *name;
}guy;


