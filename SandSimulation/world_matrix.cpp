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
			if (mWorldMatrix[y][x] == SAND_ID) sandChecker(x, y,&mWorldMatrix,&mXSize,&mYSize);//check if the grid world has sand
			if (mWorldMatrix[y][x] == WATER_ID) waterChecker(x, y, &mWorldMatrix, &mXSize, &mYSize);//check if the grid world has water
			if (mWorldMatrix[y][x] == FIRE_ID_2) fireChecker(x, y, &mWorldMatrix, &mXSize, &mYSize);//check if the grid world has fire_2
		}
	}

	for (int y = 0; y < mYSize; y++) {
		for (int x = 0; x < mXSize; x++) {
			if (mWorldMatrix[y][x] == SMOKE_ID) smokeChecker(x, y, &mWorldMatrix, &mXSize, &mYSize);//check if the grid world has smoke
			if (mWorldMatrix[y][x] == FIRE_ID_1) fireChecker(x, y, &mWorldMatrix, &mXSize, &mYSize);//check if the grid world has fire_1
		}
	}
}

void WorldMatrix::worldRenderer(SDL_Renderer* renderer) {
	for (int y = 0; y < mYSize; y++) {
		for (int x = 0; x < mXSize; x++) {
			if (mWorldMatrix[y][x] == SAND_ID) {//render sand
				Particle sandObject;
				*sandObject.getXPos() = (x * divide_world_factor);
				*sandObject.getYPos() = (y * divide_world_factor);
				sandObject.render(SAND_COLOR, renderer);
			}
			if (mWorldMatrix[y][x] == WATER_ID) {//render water
				Particle waterObject;
				*waterObject.getXPos() = (x * divide_world_factor);
				*waterObject.getYPos() = (y * divide_world_factor);
				waterObject.render(WATER_COLOR, renderer);
			}
			if (mWorldMatrix[y][x] == WOOD_ID) {//render WOOD
				Particle sandObject;
				*sandObject.getXPos() = (x * divide_world_factor);
				*sandObject.getYPos() = (y * divide_world_factor);
				sandObject.render(WOOD_COLOR, renderer);
			}
			if (mWorldMatrix[y][x] == SMOKE_ID) {//render smoke
				Particle smokeObject;
				*smokeObject.getXPos() = (x * divide_world_factor);
				*smokeObject.getYPos() = (y * divide_world_factor);
				smokeObject.render(SMOKE_COLOR, renderer);
			}
			if (mWorldMatrix[y][x] == FIRE_ID_1) {//render fire type-1
				Particle fireObject;
				*fireObject.getXPos() = (x * divide_world_factor);
				*fireObject.getYPos() = (y * divide_world_factor);
				fireObject.render(FIRE_COLOR_1, renderer);
			}
			if (mWorldMatrix[y][x] == FIRE_ID_2) {//render fire type-2
				Particle fireObject;
				*fireObject.getXPos() = (x * divide_world_factor);
				*fireObject.getYPos() = (y * divide_world_factor);
				fireObject.render(FIRE_COLOR_2, renderer);
			}
		}
	}
}

void WorldMatrix::generatePixel(int particle_id) {
	int x, y;
	int volume = divide_world_factor+7;
	SDL_GetMouseState(&x, &y);
	//render less smoke
	if (particle_id == SMOKE_ID || particle_id==FIRE_ID_1) {
		volume = 1;
	}
	for (int i = 1; i <= volume; i++) {
		for (int j = 1; j <= volume; j++) {
			mWorldMatrix[(y / divide_world_factor)+i][(x / divide_world_factor)+j] = particle_id;
		}
	}
}