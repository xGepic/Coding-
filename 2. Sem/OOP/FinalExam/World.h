#pragma once
#include <vector>
#include <typeinfo>
#include <iostream>
#include "Field.h"
#include "RecurringField.h"
#include "PlainField.h"

using namespace std;

class World {

private:
	 Field* worldArr[3][3];

public:
	World();
	~World();
	void printWorld();
	void executeField(int x, int y);
	bool isEmpty();
	int rng();
};