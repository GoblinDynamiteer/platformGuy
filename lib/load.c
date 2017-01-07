#include "..\def.h"

bool loadGame(game * game){
	gPlayer.status = 0;
	gPlayer.status |= ST_ALIVE;
	//Player starting coordinates
	gPlayer W = PLAYER_FRAME_WIDTH;
	gPlayer H = PLAYER_FRAME_HEIGHT;
	gPlayer X = 120;
	gPlayer Y = 60;
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
	gPlayer.drawTexture = TE_IDLE;
	gTimer = 1ULL; //UNSIGNED LONG LONG
	return 1;
}


bool loadTextures(game * game){
	bool success = 1;

	SDL_Surface *surface = NULL; //For holding image
	//Loads images
	surface = IMG_Load("art/player/girl.png");
	if(surface == NULL) success = 0;
	gPlayer.texture[TE_IDLE] = SDL_CreateTextureFromSurface(gRen, surface);
	gPlayer.textureFrameSize[TE_IDLE] = 17;
	
	surface = IMG_Load("art/player/girl_airborne.png");
	if(surface == NULL) success = 0;
	gPlayer.texture[TE_AIR] = SDL_CreateTextureFromSurface(gRen, surface);
	gPlayer.textureFrameSize[TE_AIR] = 2;

	surface = IMG_Load("art/player/girl_running.png");
	if(surface == NULL) success = 0;
	gPlayer.texture[TE_RUN] = SDL_CreateTextureFromSurface(gRen, surface);
	gPlayer.textureFrameSize[TE_RUN] = 14;
	
	surface = IMG_Load("art/player/girl_running_skid.png");
	if(surface == NULL) success = 0;
	gPlayer.texture[TE_SKID] = SDL_CreateTextureFromSurface(gRen, surface);
	gPlayer.textureFrameSize[TE_SKID] = 15;

	surface = IMG_Load("art/player/girl_crouch.png");
	if(surface == NULL) success = 0;
	gPlayer.texture[TE_DUCK] = SDL_CreateTextureFromSurface(gRen, surface);
	gPlayer.textureFrameSize[TE_DUCK] = 7;
	
	surface = IMG_Load("art/player/girl_attack1.png");
	if(surface == NULL) success = 0;
	gPlayer.texture[TE_ATK_T] = SDL_CreateTextureFromSurface(gRen, surface);
	gPlayer.textureFrameSize[TE_ATK_T] = 14;
	
	surface = IMG_Load("art/player/girl_attack2.png");
	if(surface == NULL) success = 0;
	gPlayer.texture[TE_ATK_S] = SDL_CreateTextureFromSurface(gRen, surface);
	gPlayer.textureFrameSize[TE_ATK_S] = 13;
	
	gPlayer.texture[TE_NULL] = NULL;
	gPlayer.textureFrameSize[TE_NULL] = 0;

	//BOMBS
	surface = IMG_Load("art/enemies/bomb.png");
	if(surface == NULL) success = 0;
	
	/* Sets image to SDL_Texture "bomb" in game struct
		Might be bad idea to set texture to every bomb/enemy in array... */
	for(int i=0;i<BOMBS;i++){
		gBomb[i].texture = SDL_CreateTextureFromSurface(gRen, surface);
		gBomb[i] X = getRandomWidth();
		gBomb[i] Y = getRandomHeight() - WINDOW_HEIGHT / 2;;
	}
	
	/*	 Loads and sets texture and rectangle for the ground texture	*/
	surface = IMG_Load("art/levels/ground/grass_stone_small_gradient.png");
	if(surface == NULL) success = 0;
	gLevel[LVL_G].texture = SDL_CreateTextureFromSurface(gRen, surface);
	
	gtd(gLevel[LVL_G].texture, &gLevel[LVL_G] W, &gLevel[LVL_G] H);
	gLevel[LVL_G] X = 0;
	gLevel[LVL_G] Y = LANDLINE-25;
	
	/*	 Loads and sets texture and rectangle for the pillar texture	*/
	surface = IMG_Load("art/levels/obstacles/pillar.png");
	if(surface == NULL) success = 0;
	gLevel[LVL_OB_P].texture = SDL_CreateTextureFromSurface(gRen, surface);
	
	gtd(gLevel[LVL_OB_P].texture, &gLevel[LVL_OB_P] W, &gLevel[LVL_OB_P] H);
	gLevel[LVL_OB_P] X = WINDOW_WIDTH / 2 + 200;
	gLevel[LVL_OB_P] Y = LANDLINE - gLevel[LVL_OB_P] H ;
	

	SDL_FreeSurface(surface); //Unload, not needed anymore
	return success;
}