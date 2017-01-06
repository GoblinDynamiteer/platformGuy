#include "def.h"

int processEvent(game *game){
	SDL_Event event;
	int keepPlaying = 1;
	while(SDL_PollEvent(&event)){
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
						}
						break;
					/* Sword Attack: Thrust  */
					case SDLK_q:
						if(!getPlayerStatus(game, STATUS_ATTACKING_T) &&
								!getPlayerStatus(game, STATUS_ATTACKING_S)){
							setPlayerStatus(game, STATUS_ATTACKING_T, TRUE);
						}
						break;
					/* Sword Attack: Swing  */
					case SDLK_w:
						if(!getPlayerStatus(game, STATUS_ATTACKING_S)
								&& !getPlayerStatus(game, STATUS_ATTACKING_T)){
							setPlayerStatus(game, STATUS_ATTACKING_S, TRUE);
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
	if(state[SDL_SCANCODE_UP] 
		&& getPlayerStatus(game, STATUS_AIRBORNE)){
			gPlayer.velocity.up += 0.8f;
	}
	
	/*  Left movement, accelerates until max speed.  */
	if(state[SDL_SCANCODE_LEFT] 
		&& !getPlayerStatus(game, STATUS_DUCKING)){
			gPlayer.velocity.left+=1.5f;
			setPlayerStatus(game, STATUS_FACINGLEFT, TRUE);
			if(gPlayer.velocity.left > gPlayer.velocity.maxLeft){
				gPlayer.velocity.left = gPlayer.velocity.maxLeft;
			}
	}
	
	/*  Right movement, accelerates until max speed.  */
	if(state[SDL_SCANCODE_RIGHT] 
		&& !getPlayerStatus(game, STATUS_DUCKING)){
			gPlayer.velocity.right+=1.5f;
			if(gPlayer.velocity.right > gPlayer.velocity.maxRight){
				gPlayer.velocity.right = gPlayer.velocity.maxRight;
			}
	}
	

	int bh;
	SDL_QueryTexture(gBomb(0).texture, NULL, NULL, NULL, &bh);
	/*		Affect bombs with gravity.		*/
	for(int i=0;i<BOMBS;i++){
		if(gBomb(i) Y + bh < LANDLINE){
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
		/*		Stops if speed is negative  */
		if(gPlayer.velocity.up < 0){
			gPlayer.velocity.up = 0.0f;
		}
	}
	
	/*		Deacceleration.	*/
	if(gPlayer.velocity.left > 0){
		gPlayer.velocity.left -= 0.2f;
		/*		Stops player if running speed is negative  */
		if(gPlayer.velocity.left < 0){
			gPlayer.velocity.left = 0.0f;
		}
	}
	
	/*		Deacceleration.	*/
	if(gPlayer.velocity.right > 0){
		gPlayer.velocity.right -= 0.2f;
		/*		Stops player if running speed is negative  */
		if(gPlayer.velocity.right < 0){
			gPlayer.velocity.right = 0.0f;
		}
	}

	gTimer++;
	determinePlayerStatus(game, state);
	gPlayer.drawTexture = determinePlayerTexture(game);
	
	/*		Build collision detection instead of this 	*/
	if(gPlayer Y + PLAYER_FRAME_HEIGHT> LANDLINE){
		gPlayer Y = LANDLINE - PLAYER_FRAME_HEIGHT;
	}

	debugInfo(game);
	return keepPlaying;
}

void renderGame(game * game){
	
	SDL_SetRenderDrawColor(gRen, 0, 0, 255, 255);
	SDL_RenderClear(gRen);
	
	SDL_SetRenderDrawColor(gRen, 255, 255, 255, 255);
	SDL_Rect ground = {0, LANDLINE, WINDOW_WIDTH, 200};
	SDL_RenderFillRect(gRen, &ground);
	
	//Render bomb images
	//Create rectangles to hold bombs image, same size as image: 250 x 250px
	for(int i=0;i<BOMBS;i++){
		SDL_Rect bombRect;
		SDL_QueryTexture(gBomb(i).texture, NULL, NULL, &bombRect.w, &bombRect.h);
		bombRect.x = gBomb(i) X;
		bombRect.y = gBomb(i) Y;
		SDL_RenderCopy(gRen, gBomb(i).texture, NULL, &bombRect);
	}


	renderPlayer(game);
	SDL_RenderPresent(gRen);

}

void renderPlayer(game * game){
	SDL_Rect textureRect = {0,0};
	int direction = getPlayerStatus(game, STATUS_FACINGLEFT);
	int drawTexture = gPlayer.drawTexture;
	SDL_Texture * texture = gPlayer.texture[drawTexture];
	SDL_QueryTexture(texture, NULL, NULL, &textureRect.w, &textureRect.h);
	
	int maxFrames = gPlayer.textureFrameSize[drawTexture];
	textureRect.w /= maxFrames;
	
	gPlayer.hitbox.h = textureRect.h;
	
	int width = textureRect.w;
	int height = textureRect.h;
	
	if(gTimer % 4 == 0){
		//For cycling trought texture animation frames..
		gPlayer.frame++;
		if(gPlayer.frame > maxFrames - 1){
			gPlayer.frame = 0;
		}
	}
	
	textureRect.x = textureRect.w * gPlayer.frame;
	
	/*		Difference between texture size and player hitbox	*/
	int tY = textureRect.h - PLAYER_FRAME_HEIGHT;
	int tX = textureRect.w - PLAYER_FRAME_WIDTH;
	
	SDL_Rect playerTextureRect = {gPlayer X - tX/2, gPlayer Y-tY/2, width, height};
	SDL_RenderCopyEx(gRen, texture, &textureRect , &playerTextureRect, gPlayer.angle, NULL, direction);
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
	printf("Shutting down SLD/Game!");
}