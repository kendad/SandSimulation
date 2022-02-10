#include "particle.h"
#include "particle_type.h"

Particle::Particle() {
	mWidth = PARTICLE_WIDTH;
	mHeight = PARTICLE_HEIGHT;

	mXPos = 0;
	mYPos = 0;

	mFillRect = { mXPos,mYPos,mWidth,mHeight };
}

void Particle::render(const Uint8 rgba[4], SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, rgba[0],rgba[1],rgba[2],rgba[3]);
	mFillRect.x = mXPos;
	mFillRect.y = mYPos;
	SDL_RenderFillRect(renderer, &mFillRect);
}

int* Particle::getXPos() { return &mXPos; }
int* Particle::getYPos() { return &mYPos; }