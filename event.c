#include "def.h"

int processEvent(game *game){
	SDL_Event event;
	int keepPlaying = 1;
	while(SDL_PollEvent(&event)){ //SDL_PollEvent returns true if an event shall be processed
		switch(event.type){
			case SDL_WINDOWEVENT_CLOSE:
				if(gWin){
					SDL_DestroyWindow(gWin);
					gWin = NULL;
				}
				break;
			//Key has been pressed:
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					//ESCAPE PRESSED
					case SDLK_ESCAPE:
						printf("Escape Key Down\n");
						keepPlaying = 0;
						break;
					case SDLK_UP:
						if(!getPlayerStatus(game, STATUS_AIRBORNE)){
							setPlayerStatus(game, STATUS_AIRBORNE, TRUE);
							gPlayer.velocity.up = gPlayer.velocity.maxUp - 15;
							gPlayer.velocity.down = 0;
							gKey.upKeyReleased = 0;	
						}
						break;
				}
				break;
			case SDL_QUIT:
				keepPlaying = 0;
				break;
		} //End switch-statements
	} //End while event loop

	//For moving by holding key down.
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	
	/*  For "long jump".  */
	if(state[SDL_SCANCODE_UP] && getPlayerStatus(game, STATUS_AIRBORNE)){
		gPlayer.velocity.up += 0.8f;
	}
	
	/*  Left movement, accelerates until max speed.  */
	if(state[SDL_SCANCODE_LEFT]){
		gPlayer.velocity.left+=1.5f;
		setPlayerStatus(game, STATUS_FACINGLEFT, TRUE);
		if(gPlayer.velocity.left > gPlayer.velocity.maxLeft){
			gPlayer.velocity.left = gPlayer.velocity.maxLeft;
		}
	}
	
	/*  Right movement, accelerates until max speed.  */
	if(state[SDL_SCANCODE_RIGHT]){
		gPlayer.velocity.right+=1.5f;
		setPlayerStatus(game, STATUS_FACINGLEFT, FALSE);
		if(gPlayer.velocity.right > gPlayer.velocity.maxRight){
			gPlayer.velocity.right = gPlayer.velocity.maxRight;
		}
	}
	
	/*  Ducking, not working as intended  */
	gPlayer.hitbox.y = 220;
	if(state[SDL_SCANCODE_DOWN]){
		gPlayer.hitbox.y = 220/2;
		debugInfo(game);
	}
	
	/*		Affect bombs with gravity.		*/
	for(int i=0;i<BOMBS;i++){
		if(gBomb(i) Y < LANDLINE){
			gBomb(i) Y += gGravity;
		}
	}
	
	/*		Affect player with gravity.		*/
	gPlayer Y += gGravity - gPlayer.velocity.up + gPlayer.velocity.down;
	
	/*		Move player.		*/
	gPlayer X += gPlayer.velocity.right - gPlayer.velocity.left;
	
	/*		Makes player falling faster each game loop.		*/
	if(gPlayer.velocity.down < gPlayer.velocity.maxDown){
		gPlayer.velocity.down++;
	}

	/*		Decrease jump strenght.		*/
	if(gPlayer.velocity.up > 0){
		gPlayer.velocity.up--;
	}
	
	/*		Set status and texture for running.	*/
	if(gPlayer.velocity.left > 0){
		printf("RUNNING LEFT \n");
		setPlayerStatus(game, STATUS_RUNNING, TRUE);
		gPlayer.drawTexture = TEXTURE_RUNNING;
		gPlayer.velocity.left -= 0.2f;
		/*		Stops player if running speed is negative  */
		if(gPlayer.velocity.left < 0){
			gPlayer.velocity.left = 0.0f;
		}
	}
	
	/*		Set status and texture for running.	*/
	if(gPlayer.velocity.right > 0){
		printf("RUNNING RIGHT \n");
		setPlayerStatus(game, STATUS_RUNNING, TRUE);
		gPlayer.drawTexture = TEXTURE_RUNNING;
		gPlayer.velocity.right -= 0.2f;
		/*		Stops player if running speed is negative  */
		if(gPlayer.velocity.right < 0){
			gPlayer.velocity.right = 0.0f;
		}
	}
	
	/*		If player has stopped.	*/
	if(!gPlayer.velocity.right && !gPlayer.velocity.left){
		setPlayerStatus(game, STATUS_RUNNING, FALSE);
	}
	
	/*		If player is airborne.	*/
	if(getPlayerStatus(game, STATUS_AIRBORNE)){
		gPlayer.drawTexture = TEXTURE_JUMP;
		//gPlayer.angle = (double)getRandomAngle();
	}
	
	/*		If player is on or below (temporary) ground level	*/
	if(gPlayer Y >= LANDLINE){
		if(!getPlayerStatus(game, STATUS_RUNNING)){
			printf("NOT RUNNING & ON GROUND LEVEL!\n");
			gPlayer.drawTexture = TEXTURE_IDLE;
		}
		setPlayerStatus(game, STATUS_AIRBORNE, FALSE);
		gPlayer.angle = 0.0;
		gPlayer Y = LANDLINE;
	}
	else{
		/*		For debugging	*/
		printf("IN AIR!!\n");
	}
	gTimer++;
	
	/*		For debugging	*/
	if(gTimer % 20 == 0){
		printf("[ TIMER TICK!!! ]\n");
	}
	return keepPlaying;
}

void renderGame(game * game){
	//Draws a white rectangle on blue backgtound
	//RGB + ALPHA
	SDL_SetRenderDrawColor(gRen, 0, 0, 255, 255);
	SDL_RenderClear(gRen);
	SDL_SetRenderDrawColor(gRen, 255, 255, 255, 255);
	
	//Render bomb images
	//Create rectangles to hold bombs image, same size as image: 250 x 250px
	for(int i=0;i<BOMBS;i++){
		SDL_Rect bombRect = {gBomb(i) X, gBomb(i) Y, 250/2, 250/2 };
		SDL_RenderCopy(gRen, gBomb(i).texture, NULL, &bombRect);
	}
	animatePlayer(game);
	SDL_RenderPresent(gRen);
}

void animatePlayer(game * game){
	int width = gPlayer.hitbox.x;
	int height = gPlayer.hitbox.y;
	if(gTimer % 100 == 0){
		; //For cycling trought texture animation frames..
	}
	int direction = !getPlayerStatus(game, STATUS_FACINGLEFT);
	//Render "Player" rectangle
	SDL_Rect playerRect = {gPlayer X + width, gPlayer Y, width, height};
	SDL_RenderCopyEx(gRen, gPlayer.texture[gPlayer.drawTexture], NULL, &playerRect, gPlayer.angle, NULL, direction);
}

//Shuts down game, destroys windows, textures, renderer
void shutdownGame(game * game){
	for(int i=0;i<BOMBS;i++){
		SDL_DestroyTexture(gBomb(i).texture);
	}
	SDL_DestroyWindow(gWin);
	SDL_DestroyRenderer(gRen);
	//Quit SDL
	SDL_Quit();
}


int loadGame(game * game){

	gPlayer.status = 0;
	gPlayer.status |= STATUS_ALIVE;
	//Player starting coordinates
	gPlayer X = 12;
	gPlayer Y = LANDLINE;
	gPlayer.hitbox.x = 150;
	gPlayer.hitbox.y = 220;
	gPlayer.angle = 0.0f;
	gGravity = 4;
	gPlayer.velocity.up = 0.0f;
	gPlayer.velocity.down = 30.0f;
	gPlayer.velocity.left = 0.0f;
	gPlayer.velocity.right = 0.0f;
	gPlayer.velocity.maxUp = 45.0f;
	gPlayer.velocity.maxDown = 40.0f;
	gPlayer.velocity.maxLeft = 8.0f;
	gPlayer.velocity.maxRight = 8.0f;
	gKey.upKeyReleased = 1;
	gPlayer.drawTexture = TEXTURE_IDLE;
	gTimer = 1ULL; //UNSIGNED LONG LONG
	
	//gPlayer.texture = {NULL};
	
	SDL_Surface *surface = NULL; //For holding image
	//Loads images
	surface = IMG_Load("art/player/guy.png");
	if(surface == NULL){
		printf("Can't load guy.png");
		SDL_Quit();
		return 0;
	}
	gPlayer.texture[TEXTURE_IDLE] = SDL_CreateTextureFromSurface(gRen, surface);
	
	surface = IMG_Load("art/player/guy_jump.png");
	if(surface == NULL){
		printf("Can't load guy_jump.png");
		SDL_Quit();
		return 0;
	}
	gPlayer.texture[TEXTURE_JUMP] = SDL_CreateTextureFromSurface(gRen, surface);

	surface = IMG_Load("art/player/guy_running.png");
	if(surface == NULL){
		printf("Can't load guy_jump.png");
		SDL_Quit();
		return 0;
	}
	gPlayer.texture[TEXTURE_RUNNING] = SDL_CreateTextureFromSurface(gRen, surface);
	
	surface = IMG_Load("art/enemies/bomb.png");
	if(surface == NULL){
		printf("Can't load bomb.png");
		SDL_Quit();
		return 0;
	}
	/* Sets image to SDL_Texture "bomb" in game struct
		Might be bad idea to set texture to every bomb/enemy in array... */
	for(int i=0;i<BOMBS;i++){
		gBomb(i).texture = SDL_CreateTextureFromSurface(gRen, surface);
		gBomb(i) X = getRandomWidth();
		gBomb(i) Y = getRandomHeight() - WINDOW_HEIGHT / 2;;
	}
	
	SDL_FreeSurface(surface); //Unload, not needed anymore
	
}