#include <iostream>
#include <thread>
#include <chrono>
#include <Game.h>

using namespace std;

int main() {

	Game G;
	int gameMode = 0;
	int temp = 2;

	while (true) {

		G.getMenu();
		gameMode = G.chooseGameMode();

		if (gameMode == 1) {

			int soloTeam = 0;

			cout << "1vs1 (1) or 2vs2 (2)?";
			cin >> soloTeam;
			cout << endl;

			if (soloTeam == 1) {

				Fighter* Player1 = G.chooseHero(1);
				Fighter* Player2 = G.chooseHero(2);

				G.startGame(Player1, Player2);

				while (true) {
					cout << "Would you like to play another Game ? yes(0) | no(1)" << endl;
					cin >> temp;

					if ((temp != 0) && (temp != 1)) {

						cout << "Error" << endl << endl;
					}
					if (temp == 0) {

						cout << endl << endl << "Clearing the Screen...";
						this_thread::sleep_for(chrono::milliseconds(2500));
						system("CLS");
						break;
					}
					else {

						return 0;
					}
				}
			}
			if (soloTeam == 2) {

				Fighter* Player1 = G.chooseHero(1);
				Fighter* Player2 = G.chooseHero(2);
				Fighter* Player3 = G.chooseHero(3);
				Fighter* Player4 = G.chooseHero(4);

				G.teamGame(Player1, Player2, Player3, Player4);

				while (true) {
					cout << "Would you like to play another Game ? yes(0) | no(1)" << endl;
					cin >> temp;

					if ((temp != 0) && (temp != 1)) {

						cout << "Error" << endl << endl;
					}
					if (temp == 0) {

						cout << endl << endl << "Clearing the Screen...";
						this_thread::sleep_for(chrono::milliseconds(2500));
						system("CLS");
						break;
					}
					else {

						return 0;
					}
				}
			}
		}
		if (gameMode == 2) {

			int temp = 2;
			int botLvl = 0;

			cout << "[BOT LEVEL] Aggressive(1) or Defensive(2)?";
			cin >> botLvl;

			if ((botLvl != 1) && (botLvl != 2)) {

				cout << "Error" << endl << endl;
			}

			cout << endl;
			Fighter* Player1 = G.chooseHero(1);
			Fighter* Bot = G.chooseBot();

			G.botGame(Player1, Bot, botLvl);

			while (true) {
				cout << endl << "Would you like to play another Game ? yes(0) | no(1)" << endl;
				cin >> temp;

				if ((temp != 0) && (temp != 1)) {

					cout << "Error" << endl << endl;
				}
				if (temp == 0) {

					cout << endl << endl << "Clearing the Screen...";
					this_thread::sleep_for(chrono::milliseconds(2500));
					system("CLS");
					break;
				}
				else {

					return 0;
				}
			}
		}
	}
}
