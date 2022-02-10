#pragma once
#include <SDL.h>


class Particle {
public:
	Particle();
	void render(const Uint8 rgba[4],SDL_Renderer* renderer);
	int* getXPos();
	int* getYPos();
private:
	int mWidth;
	int mHeight;

	int mXPos;
	int mYPos;

	SDL_Rect mFillRect;
};
