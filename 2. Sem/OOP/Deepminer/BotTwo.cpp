#include "Bot.h"

BotTwo::BotTwo() {

}

BotTwo::~BotTwo() {

	delete this;
}

void BotTwo::mine(vector<int> depth) {
	
	int value = 0;
	int counter = count(depth.begin(), depth.end(), 4);

	depth.erase(depth.begin());
	value += depth.front(); 

	depth.erase(depth.begin());
	value += depth.front(); 

	depth.erase(depth.begin());
	value += depth.front();  

	if (counter > 0) {

		addExtra(counter);
	}

	addScore(value);
}
