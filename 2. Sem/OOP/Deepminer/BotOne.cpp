#include "Bot.h"

BotOne::BotOne() {

}

BotOne::~BotOne() {

	delete this;
}

void BotOne::mine(vector<int> depth) {

	int value = 0;
	int counter = count(depth.begin(), depth.end(), 4);

	sort(depth.begin(), depth.end());
	depth.pop_back();
	value = depth.back();

	if (counter > 0) {
		
		addExtra(counter);
	}

	addScore(value);
}
