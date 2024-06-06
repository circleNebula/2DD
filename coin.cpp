#include "coin.h"
#include <iostream>
#include <algorithm>

int* coins;
bool* coinsB;
bool* coinsPlayed;
float* increaseC;

void coin::init(){
	coinsB = (bool*)malloc(5 * sizeof(bool));
	coinsPlayed = (bool*)malloc(5*sizeof(bool));
	increaseC = (float*)malloc(5 *sizeof(float));
	for(int i = 0; i < 5; i++){
		coinsB[i] = false;
		coinsPlayed[i] = false;
		increaseC[i] = 0;
	}
}