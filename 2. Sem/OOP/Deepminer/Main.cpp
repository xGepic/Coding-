#include <iostream>
#include <time.h>
#include "World.h"

using namespace std;

int main() {

	srand((unsigned int)time(NULL));

	World* myWorld = new World();




	delete myWorld;
}
