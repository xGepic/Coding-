#include "Bot.h"

BotTwo::BotTwo() {

}

BotTwo::~BotTwo() {

	delete this;
}

void BotTwo::mine(vector<int> depth) {
	
	int value = 0;

	depth.erase(depth.begin());
	value += depth.front(); 

	depth.erase(depth.begin());
	value += depth.front(); 

	depth.erase(depth.begin());
	value += depth.front();  

	addScore(value);
}
