#include "..\def.h"

bool loadGame(game * game){
	gPlayer.status = 0;
	gPlayer.status |= STATUS_ALIVE;
	//Player starting coordinates
	gPlayer.hitbox.w = PLAYER_FRAME_WIDTH;
	gPlayer.hitbox.h = PLAYER_FRAME_HEIGHT;
	gPlayer X = 12;
	gPlayer Y = LANDLINE - gPlayer.hitbox.h;
	gPlayer.angle = 0.0f;
	gPlayer.frame = 0;
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
	return 1;
}


bool loadTextures(game * game){
		


	
	SDL_Surface *surface = NULL; //For holding image
	//Loads images
	surface = IMG_Load("art/player/girl.png");
	if(surface == NULL){
		printf("Can't load guy.png");
		SDL_Quit();
		return 0;
	}
	gPlayer.texture[TEXTURE_IDLE] = SDL_CreateTextureFromSurface(gRen, surface);
	gPlayer.textureFrameSize[TEXTURE_IDLE] = 17;
	
	surface = IMG_Load("art/player/girl_airborne.png");
	if(surface == NULL){
		printf("Can't load guy_jump.png");
		SDL_Quit();
		return 0;
	}
	
	gPlayer.texture[TEXTURE_JUMP] = SDL_CreateTextureFromSurface(gRen, surface);
	gPlayer.textureFrameSize[TEXTURE_JUMP] = 2;

	surface = IMG_Load("art/player/girl_running.png");
	if(surface == NULL){
		printf("Can't load guy_jump.png");
		SDL_Quit();
		return 0;
	}
	gPlayer.texture[TEXTURE_RUNNING] = SDL_CreateTextureFromSurface(gRen, surface);
	gPlayer.textureFrameSize[TEXTURE_RUNNING] = 14;
	
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
	return 1;
}