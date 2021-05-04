#include "Bot.h"

BotOne::BotOne() {

}

BotOne::~BotOne() {

	delete this;
}

void BotOne::mine(vector<int> depth) {

	int value = 0;

	sort(depth.begin(), depth.end());
	depth.pop_back();
	value = depth.back();
	addScore(value);
}
