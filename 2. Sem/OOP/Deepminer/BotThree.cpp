#include "Bot.h"

BotThree::BotThree() {

}

BotThree::~BotThree() {

	delete this;
}

void BotThree::mine(vector<int> depth) {

	int value = 0;

	reverse(depth.begin(), depth.end());

	value += depth.front();
	depth.erase(depth.begin());
	value += depth.front();

	addScore(value);
}
