#include "main.h"
#include "event.h"

int processEvent(SDL_Window *window){
	SDL_Event event;
	int done = 0;
	while(SDL_PollEvent(&event)){ //SDL_PollEvent returns true if an event shall be processed
		switch(event.type){
			case SDL_WINDOWEVENT_CLOSE: /**< The window manager requests that the window be closed */
				if(window){
					SDL_DestroyWindow(window);
					window = NULL;
				}
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						done = 1;
						break;
				}
				break;
			case SDL_QUIT:
				done = 1;
				break;
		} //End switch-statements
	} //End while event loop
	return done;
}