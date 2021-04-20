#pragma once
#include <Fighter.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

class Game {

private:
	int wins;
	int wins2;
	int botWins;

public:
	
	Game();
	~Game();

	void getMenu();
	void begin();
	void printStats(Fighter* F, int i);

	void startGame(Fighter* p1, Fighter* p2);
	Fighter* chooseHero(int i);
	int chooseGameMode();
	void chooseAbility(Fighter* first, Fighter* second, int i);

	void botGame(Fighter* p1, Fighter* bot, int botLvl);
	Fighter* chooseBot();
	void botAbility(Fighter* bot, Fighter* second, int botLvl);

	void teamGame(Fighter* p1, Fighter* p2, Fighter* p3, Fighter* p4);

	int gameOver(int lp, int w, int mode);
	int gameOverTeam(int lp, int w);
};
