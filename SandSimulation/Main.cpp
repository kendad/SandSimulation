#include<iostream>
#include<SDL.h>
#include "particle.h"
#include "particle_type.h"
#include "basic_constants.h"
#include "world_matrix.h"

#undef main

//SCREEN CONSTANTS
int PARTICLE_ID = 1;

//functions
bool init();//initializes SDL for use
void close();//close the program
void handelUserInput(SDL_Event* e);

//GLOBAL VARIABLES
SDL_Window* gWindow=NULL;
SDL_Renderer* gRenderer = NULL;
WorldMatrix gameWorld;

void main() {
	if (!init()) {
		std::cout << "SDL Intilization failed"<< std::endl;
		return;
	}
	bool quit = false;
	SDL_Event e;

	//game loop
	while (!quit) {
		//handel user input
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) quit = true;
			handelUserInput(&e);
		}
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0,0,0,0);
		SDL_RenderClear(gRenderer);

		//draw stuff here
		gameWorld.worldChecker();
		gameWorld.worldRenderer(gRenderer);
		if (gameWorld.mShouldGeneratePixel) {
			gameWorld.generatePixel(PARTICLE_ID);
		}

		//Update screen
		SDL_RenderPresent(gRenderer);
	}
}


bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}
	gWindow = SDL_CreateWindow("SandSimulations",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		std::cout << "Window creation Error: " << SDL_GetError() << std::endl;
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL) {
		std::cout << "Renderer creation Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}

void handelUserInput(SDL_Event* e) {
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		gameWorld.mShouldGeneratePixel = true;
	}
	if (e->type == SDL_MOUSEBUTTONUP) {
		gameWorld.mShouldGeneratePixel = false;
	}
	if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
		switch (e->key.keysym.sym) {
			case SDLK_1:PARTICLE_ID = SAND_ID; break;
			case SDLK_2:PARTICLE_ID = WATER_ID; break;
		}
	}
}