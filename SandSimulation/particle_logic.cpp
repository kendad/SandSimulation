#include "partilce_logic.h"

void sandChecker(int xPos,int yPos, int (*worldMatrix)[SCREEN_HEIGHT / divide_world_factor][SCREEN_WIDTH / divide_world_factor],int* worldXSize,int* worldYSize) {
	if ((*worldMatrix)[yPos + 1][xPos] == 0 && yPos + 1 < *worldYSize) {
		(*worldMatrix)[yPos + 1][xPos] = 1;
		(*worldMatrix)[yPos][xPos] = 0;
	}
	else if ((*worldMatrix)[yPos + 1][xPos + 1] == 0 && yPos + 1 < *worldYSize && xPos + 1 < *worldXSize) {
		(*worldMatrix)[yPos + 1][xPos + 1] = 1;
		(*worldMatrix)[yPos][xPos] = 0;
	}
	else if ((*worldMatrix)[yPos + 1][xPos - 1] == 0 && yPos + 1 < *worldYSize && xPos - 1 >= 0) {
		(*worldMatrix)[yPos + 1][xPos - 1] = 1;
		(*worldMatrix)[yPos][xPos] = 0;
	}
	else if ((*worldMatrix)[yPos + 1][xPos] == 2 && yPos + 1 < *worldYSize) {
		(*worldMatrix)[yPos + 1][xPos] = 1;
		(*worldMatrix)[yPos][xPos] = 2;
	}
}

void waterChecker(int xPos, int yPos, int (*worldMatrix)[SCREEN_HEIGHT / divide_world_factor][SCREEN_WIDTH / divide_world_factor],int* worldXSize, int* worldYSize) {
	if ((*worldMatrix)[yPos + 1][xPos] == 0 && yPos + 1 < *worldYSize) {
		(*worldMatrix)[yPos + 1][xPos] = 2;
		(*worldMatrix)[yPos][xPos] = 0;
	}
	else if ((*worldMatrix)[yPos][xPos + 1] == 0 && xPos + 1 < *worldXSize) {
		(*worldMatrix)[yPos][xPos + 1] = 2;
		(*worldMatrix)[yPos][xPos] = 0;
	}
	else if ((*worldMatrix)[yPos][xPos - 1] == 0 && xPos - 1 >= 0) {
		(*worldMatrix)[yPos][xPos - 1] = 2;
		(*worldMatrix)[yPos][xPos] = 0;
	}
}