#include "world_matrix.h"
#include "particle.h"
#include "particle_type.h"
#include "partilce_logic.h"
#include <iostream>

WorldMatrix::WorldMatrix() {
	mXSize = SCREEN_WIDTH / divide_world_factor;
	mYSize = SCREEN_HEIGHT / divide_world_factor;
	mShouldGeneratePixel = false;
	//intiliaze the matrix with 0s
	for (int y = 0; y < mYSize; y++) {
		for (int x = 0; x < mXSize; x++) {
			mWorldMatrix[y][x] = 0;
		}
	}
}

void WorldMatrix::worldChecker() {
	for (int y = mYSize - 1; y >= 0; y--) {
		for (int x = 0; x < mXSize; x++) {
			if (mWorldMatrix[y][x] == 1) sandChecker(x, y,&mWorldMatrix,&mXSize,&mYSize);//check if the grid world has sand
			if (mWorldMatrix[y][x] == 2) waterChecker(x, y,&mWorldMatrix,&mXSize,&mYSize);//check if the grid world has water
		}
	}
}

void WorldMatrix::worldRenderer(SDL_Renderer* renderer) {
	for (int y = 0; y < mYSize; y++) {
		for (int x = 0; x < mXSize; x++) {
			if (mWorldMatrix[y][x] == 1) {//render sand
				Particle sandObject;
				*sandObject.getXPos() = (x * divide_world_factor);
				*sandObject.getYPos() = (y * divide_world_factor);
				sandObject.render(SAND_COLOR, renderer);
			}
			if (mWorldMatrix[y][x] == 2) {//render water
				Particle waterObject;
				*waterObject.getXPos() = (x * divide_world_factor);
				*waterObject.getYPos() = (y * divide_world_factor);
				waterObject.render(WATER_COLOR, renderer);
			}
		}
	}
}

void WorldMatrix::generatePixel(int particle_id) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	mWorldMatrix[y / divide_world_factor][x / divide_world_factor] = particle_id;
}