#include "partilce_logic.h"

//EMPTY_ID=0
//SAND_ID=1
//WATER_ID=2

const int WATER_DISPERSION_RATE = 5;
const int GRAVITY = 3;

void sandChecker(int xPos,int yPos, int (*worldMatrix)[SCREEN_HEIGHT / divide_world_factor][SCREEN_WIDTH / divide_world_factor],int* worldXSize,int* worldYSize) {
	//partice falls down with gravity if bottom space is empty
	if ((*worldMatrix)[yPos + 1][xPos] == 0 && yPos + 1 < *worldYSize) {
		for (int i = 1; i <= GRAVITY; i++) {
			if ((*worldMatrix)[yPos + i][xPos] == 0 && yPos + i < *worldYSize) {
				(*worldMatrix)[yPos + i][xPos] = 1;
				(*worldMatrix)[yPos+(i-1)][xPos] = 0;
			}
		}
	}
	//check if right side is empty and move right
	else if ((*worldMatrix)[yPos + 1][xPos + 1] == 0 && yPos + 1 < *worldYSize && xPos + 1 < *worldXSize) {
		(*worldMatrix)[yPos + 1][xPos + 1] = 1;
		(*worldMatrix)[yPos][xPos] = 0;
	}
	//check if left side is empty and move left
	else if ((*worldMatrix)[yPos + 1][xPos - 1] == 0 && yPos + 1 < *worldYSize && xPos - 1 >= 0) {
		(*worldMatrix)[yPos + 1][xPos - 1] = 1;
		(*worldMatrix)[yPos][xPos] = 0;
	}
	//If bottom is water then swap water with sand
	else if ((*worldMatrix)[yPos + 1][xPos] == 2 && yPos + 1 < *worldYSize) {
		(*worldMatrix)[yPos + 1][xPos] = 1;
		(*worldMatrix)[yPos][xPos] = 2;
	}
}

void waterChecker(int xPos, int yPos, int (*worldMatrix)[SCREEN_HEIGHT / divide_world_factor][SCREEN_WIDTH / divide_world_factor],int* worldXSize, int* worldYSize) {
	//partice falls down with gravity if bottom space is empty
	if ((*worldMatrix)[yPos + 1][xPos] == 0 && yPos + 1 < *worldYSize) {
		for (int i = 1; i <= GRAVITY; i++) {
			if ((*worldMatrix)[yPos + i][xPos] == 0 && yPos + i < *worldYSize) {
				(*worldMatrix)[yPos + i][xPos] = 2;
				(*worldMatrix)[yPos + (i - 1)][xPos] = 0;
			}
		}
	}
	//check if RIGHT side is empty and move with dispersion rate
	else if ((*worldMatrix)[yPos][xPos + 1] == 0 && xPos + 1 < *worldXSize) {
		for (int i = 1; i <= WATER_DISPERSION_RATE; i++) {
			if ((*worldMatrix)[yPos][xPos + i] == 0 && xPos + i < *worldXSize) {
				(*worldMatrix)[yPos][xPos + i] = 2;
				(*worldMatrix)[yPos][xPos+(i-1)] = 0;
			}
		}
	}
	//check if LEFT side is empty and move with dispersion_rate
	else if ((*worldMatrix)[yPos][xPos - 1] == 0 && xPos - 1 >= 0) {
		for (int i = 1; i <= WATER_DISPERSION_RATE; i++) {
			if ((*worldMatrix)[yPos][xPos - i] == 0 && xPos - i >= 0) {
				(*worldMatrix)[yPos][xPos - i] = 2;
				(*worldMatrix)[yPos][xPos-(i-1)] = 0;
			}
		}
	}
}