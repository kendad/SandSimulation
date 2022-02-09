#include<iostream>
#include<SDL.h>
#undef main

//SCREEN CONSTANTS
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

//functions
bool init();//initializes SDL for use
void close();//close the program
void handelUserInput(SDL_Event* e);

//class
//_id:1
class Sand {
public:
	Sand();
	void render();
	int* getXPos();
	int* getYPos();
private:
	int mWidth;
	int mHeight;
	
	int mXPos;
	int mYPos;

	SDL_Rect mFillRect;
};

class CellularMatrix {
public:
	CellularMatrix();
	void worldChecker();//check the Cellular Matrix
	void sandChecker(int xPos, int yPos);//Sand Particle Logic
	void worldRenderer();//render the different particles
	void generatePixel();//generate pixel at mouse position

	int mWorldMatrix[SCREEN_HEIGHT / 10][SCREEN_WIDTH / 10];
	bool mShouldGeneratePixel;
private:
	int mXSize;
	int mYSize;
};

//GLOBAL VARIABLES
SDL_Window* gWindow=NULL;
SDL_Renderer* gRenderer = NULL;
CellularMatrix gameWorld;

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
		gameWorld.worldRenderer();
		if (gameWorld.mShouldGeneratePixel) {
			gameWorld.generatePixel();
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
}


//SAND
Sand::Sand() {
	mWidth = 10;
	mHeight = 10;
	mXPos = 10;
	mYPos = 10;
	mFillRect = {mXPos,mYPos,mWidth,mHeight};
}
void Sand::render() {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	mFillRect.x = mXPos;
	mFillRect.y = mYPos;
	SDL_RenderFillRect(gRenderer, &mFillRect);
}
int* Sand::getXPos() {
	return &mXPos;
}

int* Sand::getYPos() {
	return &mYPos;
}

//CELLULAR MATRIX
CellularMatrix::CellularMatrix() {
	mXSize = SCREEN_WIDTH / 10;
	mYSize = SCREEN_HEIGHT / 10;
	mShouldGeneratePixel = false;
	//intiliaze the matrix with 0s
	for (int y = 0; y < mYSize; y++) {
		for (int x = 0; x < mXSize; x++) {
			mWorldMatrix[y][x] =0;
		}
	}
}


void CellularMatrix::worldChecker() {
	for (int y = mYSize-1; y >=0; y--) {
		for (int x = 0; x < mXSize; x++) {
			if (mWorldMatrix[y][x] == 1) sandChecker(x,y);
		}
	}
}

void CellularMatrix::sandChecker(int xPos, int yPos) {
	if (mWorldMatrix[yPos + 1][xPos] == 0 && yPos+1<mYSize) {
		mWorldMatrix[yPos + 1][xPos] = 1;
		mWorldMatrix[yPos][xPos] = 0;
	}
	else if (mWorldMatrix[yPos + 1][xPos + 1] == 0 && yPos + 1 < mYSize && xPos + 1 < mXSize) {
		mWorldMatrix[yPos + 1][xPos+1] = 1;
		mWorldMatrix[yPos][xPos] = 0;
	}
	else if (mWorldMatrix[yPos + 1][xPos - 1] == 0 && yPos + 1 < mYSize && xPos - 1 >= 0) {
		mWorldMatrix[yPos + 1][xPos - 1] = 1;
		mWorldMatrix[yPos][xPos] = 0;
	}
}

void CellularMatrix::worldRenderer() {
	for (int y = 0; y < mYSize; y++) {
		for (int x = 0; x < mXSize; x++) {
			if (mWorldMatrix[y][x] == 1) {//render sand
				Sand sandObject;
				*sandObject.getXPos() = x * 10;
				*sandObject.getYPos() = y * 10;
				sandObject.render();
			}
		}
	}
}

void CellularMatrix::generatePixel() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	gameWorld.mWorldMatrix[y / 10][x / 10] = 1;
}