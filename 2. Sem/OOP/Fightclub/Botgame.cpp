#include <Game.h>

Fighter* Game::chooseBot() {

	srand((unsigned int)time(NULL));
	int temp = rand() % 4;

	if (temp == 1) {

		cout << "Bot chose the Warrior!" << endl << endl << endl;
		return new Warrior();
	}
	if (temp == 2) {

		cout << "Bot chose the Hunter!" << endl << endl << endl;
		return new Hunter();
	}
	if (temp == 3) {

		cout << "Bot chose the Mage!" << endl << endl << endl;
		return new Mage();
	}
	else {

		cout << "Bot chose the Rogue!" << endl << endl << endl;
		return new Rogue();
	}
}

void Game::botAbility(Fighter* bot, Fighter* second, int botLvl) {

	srand((unsigned int)time(NULL));
	int temp1 = rand() % 4 + 1;
	int temp2 = rand() % 2 + 1;

	if (bot->isOnline == false) {

		cout << "Bot skippes a move!" << endl << endl;
		bot->setOnline();
		return;
	}

	if (bot->nullify == true) {

		cout << "Bots move has been nullified!" << endl << endl;
		bot->unNullify();
		return;
	}

	if (bot->dodge == true) {

		cout << "Bots move has been dodged!" << endl << endl;
		bot->unDodge();
		return;
	}

	if (botLvl == 1) {
		if (temp1 == 4) {
			if (temp2 == 1) {
				bot->useAbility(3, second, 6);
				cout << endl << endl;
			}
			if (temp2 == 2) {
				bot->useAbility(4, second, 6);
				cout << endl << endl;
			}
		}
		else {
			if (temp2 == 1) {
				bot->useAbility(1, second, 6);
				cout << endl << endl;
			}
			if (temp2 == 2) {
				bot->useAbility(2, second, 6);
				cout << endl << endl;
			}
		}
	}
	if (botLvl == 2) {
		if (temp1 == 4) {
			if (temp2 == 1) {
				bot->useAbility(1, second, 6);
				cout << endl << endl;
			}
			if (temp2 == 2) {
				bot->useAbility(2, second, 6);
				cout << endl << endl;
			}
		}
		else {
			if (temp2 == 1) {
				bot->useAbility(3, second, 6);
				cout << endl << endl;
			}
			if (temp2 == 2) {
				bot->useAbility(4, second, 6);
				cout << endl << endl;
			}
		}
	}
}

void Game::botGame(Fighter* p1, Fighter* bot, int botLvl) {

	int temp = 1;

	cout << "Loading...";
	this_thread::sleep_for(chrono::seconds(5));
	system("CLS");

	begin();

	while (true) {

		printStats(p1, 1);
		printStats(bot, 6);

		if (p1->getSpeed() > bot->getSpeed()) {

			chooseAbility(p1, bot, 1);
			temp = gameOver(bot->getLifepoints(), 1, 2);
			if (temp == 0) {

				break;
			}

			botAbility(bot, p1, botLvl);
			temp = gameOver(p1->getLifepoints(), 6, 2);
			if (temp == 0) {

				break;
			}

			cout << "Next Round...";
			this_thread::sleep_for(chrono::milliseconds(2500));
			system("CLS");
		}

		if (p1->getSpeed() < bot->getSpeed()) {

			botAbility(bot, p1, botLvl);
			temp = gameOver(p1->getLifepoints(), 6, 2);
			if (temp == 0) {

				break;
			}

			chooseAbility(p1, bot, 1);
			temp = gameOver(bot->getLifepoints(), 1, 2);
			if (temp == 0) {

				break;
			}

			cout << "Next Round...";
			this_thread::sleep_for(chrono::milliseconds(2500));
			system("CLS");
		}

		if (p1->getSpeed() == bot->getSpeed()) {

			srand((unsigned int)time(NULL));
			int n = rand() % 2;

			if (n == 0) {

				chooseAbility(p1, bot, 1);
				temp = gameOver(bot->getLifepoints(), 1, 2);
				if (temp == 0) {

					break;
				}

				botAbility(bot, p1, botLvl);
				temp = gameOver(p1->getLifepoints(), 6, 2);
				if (temp == 0) {

					break;
				}

				cout << "Next Round...";
				this_thread::sleep_for(chrono::milliseconds(2500));
				system("CLS");
			}

			if (n == 1) {
				botAbility(bot, p1, botLvl);
				temp = gameOver(p1->getLifepoints(), 6, 2);
				if (temp == 0) {

					break;
				}

				chooseAbility(p1, bot, 1);
				temp = gameOver(bot->getLifepoints(), 1, 2);
				if (temp == 0) {

					break;
				}

				cout << "Next Round...";
				this_thread::sleep_for(chrono::milliseconds(2500));
				system("CLS");
			}
		}
	}
}
