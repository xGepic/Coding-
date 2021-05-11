#include "Bot.h"

BotThree::BotThree() {

}

BotThree::~BotThree() {

	delete this;
}

void BotThree::mine(vector<int> depth) {

	int value = 0;
	int counter = count(depth.begin(), depth.end(), 4);

	reverse(depth.begin(), depth.end());

	value += depth.front();
	depth.erase(depth.begin());
	value += depth.front();

	if (counter > 0) {

		addExtra(counter);
	}

	addScore(value);
}
