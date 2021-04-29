#include "Bot.h"

BotOne::BotOne() {

}

BotOne::~BotOne() {

	delete this;
}

void BotOne::mine(vector<int> depth) {

	sort(depth.begin(), depth.end());
	depth.pop_back();
	addScore(depth.back());
}
