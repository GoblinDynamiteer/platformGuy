#include "def.h"

int main(int argc, char* args[]) {

	/*	 Start SDL Systems	*/
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	/*	 Declare window and renderer	*/
	SDL_Window *window;
	SDL_Renderer *renderer;

	/*	 Create window	*/
	window = SDL_CreateWindow("PlatformGuy",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	WINDOW_WIDTH,
	WINDOW_HEIGHT, 0);

	/*	 Create renderer	*/
	renderer = SDL_CreateRenderer(window, -1,
	RENDERER_FLAGS);

	/*	 Game struct	*/
	game game;
	game.renderer = renderer;
	game.window = window;

	/*	 Load art, set starting status	*/
	if (loadGame(&game) && loadTextures(&game)) {
		/*	 Game loop	*/
		while (getEvents(&game)) {
			renderGame(&game);
			/*	 60 fps	*/
			SDL_Delay(1000 / 60);
		}
	}

	//shutdownGame(&game);
	return 0;
}
