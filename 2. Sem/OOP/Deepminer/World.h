#pragma once
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class World {

private:

	int worldArray[5][5][10];
	int sizeX;
	int sizeY;
	int sizeZ;

public:
	World();
	~World();
	void whichPlain();
	void printLayer(int k);
	void printWorld(int n);
};