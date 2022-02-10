#pragma once
#include "basic_constants.h"

void sandChecker(int xPos,int yPos, int (*worldMatrix)[SCREEN_HEIGHT / divide_world_factor][SCREEN_WIDTH / divide_world_factor],int* worldXSize,int* worldYSize);
void waterChecker(int xPos, int yPos, int(*worldMatrix)[SCREEN_HEIGHT / divide_world_factor][SCREEN_WIDTH / divide_world_factor], int* worldXSize,int* worldYSize);
