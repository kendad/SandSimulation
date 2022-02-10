#pragma once
#include <SDL.h>
#include "basic_constants.h"

class WorldMatrix {
public:
	WorldMatrix();
	void worldChecker();
	void worldRenderer(SDL_Renderer* renderer);
	void generatePixel(int particle_id);

	int mWorldMatrix[SCREEN_HEIGHT / divide_world_factor][SCREEN_WIDTH / divide_world_factor];
	bool mShouldGeneratePixel;
	int mXSize;
	int mYSize;
};
