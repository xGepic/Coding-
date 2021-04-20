#include <Game.h>

Game::Game() {

	wins = 0;
	wins2 = 0;
	botWins = 0;
}

Game::~Game() {

	delete this;
}

void Game::getMenu() {

	cout << "--| FightClub 1.0 by Stefan Simanek |--" << endl << endl;
	cout << "Welcome to the FightClub!" << endl << endl;
	cout << "WARRIOR | Sword and Shield" << endl;
	cout << "HUNTER  | Bow and Arrow" << endl;
	cout << "MAGE    | Spellbook and Fireballs" << endl;
	cout << "ROGUE   | Cloak and Dagger" << endl;
	cout << "CUSTOM  | Choose your Fate" << endl;
	cout << "___________________________________" << endl << endl;
}

void Game::begin() {

	cout << "Let the Game begin!" << endl;
	cout << "___________________" << endl << endl;
}

int Game::chooseGameMode() {

	int temp = 0;

	while (true) {

		cout << "Would you like to play against another Player (1) or the Computer (2) ?";
		cin >> temp;

		if ((temp != 1) && (temp != 2)) {

			cout << "Error!" << endl << endl;
		}
		else {

			cout << endl << endl;
			return temp;
		}
	}
}

Fighter* Game::chooseHero(int i) {

	int temp;

	while (true) {

		cout << "Choose A Hero for Player " << i << " | Warrior(1) - Hunter(2) - Mage(3) - Rogue(4) - Custom(5)";
		cin >> temp;

		if ((temp < 1) || (temp > 5)) {

			cout << endl << "Error!" << endl << endl;
		}
		else {

			if (temp == 1) {

				cout << endl << "Player " << i << " chose the Warrior!" << endl << endl << endl;
				return new Warrior();
			}
			if (temp == 2) {

				cout << endl << "Player " << i << " chose the Hunter!" << endl << endl << endl;
				return new Hunter();
			}
			if (temp == 3) {

				cout << endl << "Player " << i << " chose the Mage!" << endl << endl << endl;
				return new Mage();
			}
			if (temp == 4) {

				cout << endl << "Player " << i << " chose the Rogue!" << endl << endl << endl;
				return new Rogue();
			}
			if (temp == 5) {

				cout << endl << "Player " << i << " chose the Custom!" << endl << endl << endl;
				return new Custom();
			}
		}
	}
}

void Game::printStats(Fighter* F, int i) {

	if (i == 6) {

		cout << "Bot - " << F->getName();
		cout << " | " << "Lifepoints: " << F->getLifepoints() << " | ";
		cout << "Speed: " << F->getSpeed() << endl << endl << endl;
	}
	else {

		cout << "Player " << i << " - " << F->getName() << " | ";
		cout << "Lifepoints: " << F->getLifepoints() << " | ";
		cout << "Speed: " << F->getSpeed() << endl << endl;
	}
}

void Game::chooseAbility(Fighter* first, Fighter* second, int i) {

	int temp = 0;

	if (first->isOnline == false) {

		cout << "You skip a move!" << endl << endl;
		first->setOnline();
		return;
	}

	if (first->nullify == true) {

		cout << "Your move has been nullified!" << endl << endl;
		first->unNullify();
		return;
	}

	if (first->dodge == true) {

		cout << "Your move has been dodged!" << endl << endl;
		first->unDodge();
		return;
	}

	while (true) {

		cout << endl << "Player " << i << " | Which Ability would you like to use?" << endl;
		first->printAbilities();
		cin >> temp;

		if ((temp < 1) || (temp > 16)) {

			cout << endl << "Error!" << endl << endl;
		}
		else {

			cout << endl;
			first->useAbility(temp, second, i);
			cout << endl << endl;
			break;
		}
	}
}

void Game::startGame(Fighter* p1, Fighter* p2) {

	int temp = 1;

	cout << "Loading...";
	this_thread::sleep_for(chrono::seconds(5));
	system("CLS");

	begin();

	while (true) {

		printStats(p1, 1);
		printStats(p2, 2);

		if (p1->getSpeed() == p2->getSpeed()) {

			srand((unsigned int)time(NULL));
			int n = rand() % 2;

			if (n == 0) {

				chooseAbility(p1, p2, 1);
				temp = gameOver(p2->getLifepoints(), 1, 1);
				if (temp == 0) {

					break;
				}

				chooseAbility(p2, p1, 2);
				temp = gameOver(p1->getLifepoints(), 2, 1);
				if (temp == 0) {

					break;
				}

				cout << "Next Round...";
				this_thread::sleep_for(chrono::milliseconds(2500));
				system("CLS");
			}
			if (n == 1) {

				chooseAbility(p2, p1, 2);
				temp = gameOver(p1->getLifepoints(), 2, 1);
				if (temp == 0) {

					break;
				}

				chooseAbility(p1, p2, 1);
				temp = gameOver(p2->getLifepoints(), 1, 1);
				if (temp == 0) {

					break;
				}

				cout << "Next Round...";
				this_thread::sleep_for(chrono::milliseconds(2500));
				system("CLS");
			}
		}

		if (p1->getSpeed() < p2->getSpeed()) {

			chooseAbility(p2, p1, 2);
			temp = gameOver(p1->getLifepoints(), 2, 1);
			if (temp == 0) {

				break;
			}

			chooseAbility(p1, p2, 1);
			temp = gameOver(p2->getLifepoints(), 1, 1);
			if (temp == 0) {

				break;
			}

			cout << "Next Round...";
			this_thread::sleep_for(chrono::milliseconds(2500));
			system("CLS");
		}

		if (p1->getSpeed() > p2->getSpeed()) {

			chooseAbility(p1, p2, 1);
			temp = gameOver(p2->getLifepoints(), 1, 1);
			if (temp == 0) {

				break;
			}

			chooseAbility(p2, p1, 2);
			temp = gameOver(p1->getLifepoints(), 2, 1);
			if (temp == 0) {

				break;
			}

			cout << "Next Round...";
			this_thread::sleep_for(chrono::milliseconds(2500));
			system("CLS");
		}
	}
}

int Game::gameOver(int lp, int w, int mode) {

	if (lp <= 0) {

		cout << "Game Over" << endl;

		if (mode == 2) {
			if (w == 6) {
				cout << "Bot Won!" << endl;
				botWins += 1;
				cout << "Bot Wins: " << botWins << " | Player " << w << " Wins: " << wins << endl << endl;
				return 0;
			}
			else {
				cout << "Player 1 Won!" << endl;
				wins += 1;
				cout << "Bot Wins: " << botWins << " | Player " << w << " Wins: " << wins << endl << endl;
				return 0;
			}
		}
		if (mode == 1) {
			cout << "Player " << w << " won!" << endl << endl;
			if (w == 1) {
				wins += 1;
			}
			if (w == 2) {
				wins2 += 1;
			}
			cout << "Player 1 Wins: " << wins << " | Player 2 Wins: " << wins2 << endl << endl;
			return 0;
		}
	}
	else {

		return 1;
	}
}
