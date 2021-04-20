#include <Game.h>

int Game::gameOverTeam(int lp, int w) {

	if (lp <= 0) {
		cout << "Game Over" << endl;

		if ((w == 1) || (w == 2)) {

			cout << "Team 1 won!" << endl << endl;
			return 0;
		}
		else {

			cout << "Team 2 won!" << endl << endl;
			return 0;

		}
	}
	else {
		return 1;
	}
}

void Game::teamGame(Fighter* p1, Fighter* p2, Fighter* p3, Fighter* p4) {

	int win = 1;
	int temp1 = 0;

	cout << "Loading...";
	this_thread::sleep_for(chrono::seconds(5));
	system("CLS");

	begin();

	while (true) {

		cout << "Team 1" << endl;
		printStats(p1, 1);
		printStats(p2, 2);
		cout << "Team 2" << endl;
		printStats(p3, 3);
		printStats(p4, 4);

		if (p1->getSpeed() < p2->getSpeed()) {

			cout << "[Player2] Who do you want to attack? Player3 (1) or Player4 (2)?";
			cin >> temp1;

			if (temp1 > 2) {

				cout << "Error" << endl;
			}
			if (temp1 == 1) {

				chooseAbility(p2, p3, 2);
				win = gameOverTeam(p3->getLifepoints(), 2);
				if (win == 0) {
					break;
				}
			}
			if (temp1 == 2) {

				chooseAbility(p2, p4, 2);
				win = gameOverTeam(p4->getLifepoints(), 2);
				if (win == 0) {
					break;
				}
			}

			if (p3->getSpeed() < p4->getSpeed()) {

				cout << "[Player4] Who do you want to attack? Player1 (1) or Player2 (2)?" << endl;
				cin >> temp1;

				if (temp1 > 2) {
					cout << "Error" << endl;
				}
				if (temp1 == 1) {

					chooseAbility(p4, p1, 4);
					win = gameOverTeam(p1->getLifepoints(), 4);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 2) {

					chooseAbility(p4, p2, 4);
					win = gameOverTeam(p2->getLifepoints(), 4);
					if (win == 0) {
						break;
					}
				}

				cout << "[Player1] Who do you want to attack? Player3 (1) or Player4 (2)?" << endl;
				cin >> temp1;

				if (temp1 > 2) {

					cout << "Error" << endl;
				}
				if (temp1 == 1) {

					chooseAbility(p1, p3, 1);
					win = gameOverTeam(p3->getLifepoints(), 1);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 2) {

					chooseAbility(p1, p4, 1);
					win = gameOverTeam(p4->getLifepoints(), 1);
					if (win == 0) {
						break;
					}
				}

				cout << "[Player3] Who do you want to attack? Player1 (1) or Player2 (2)?" << endl;
				cin >> temp1;
				if (temp1 > 2) {

					cout << "Error" << endl;
				}
				if (temp1 == 1) {

					chooseAbility(p3, p1, 3);
					win = gameOverTeam(p1->getLifepoints(), 3);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 2) {

					chooseAbility(p3, p2, 3);
					win = gameOverTeam(p2->getLifepoints(), 3);
					if (win == 0) {
						break;
					}
				}
				cout << "Next Round...";
				this_thread::sleep_for(chrono::milliseconds(2500));
				system("CLS");
			}
			if (p3->getSpeed() > p4->getSpeed()) {

				cout << "[Player3] Who do you want to attack? Player1 (1) or Player2 (2)?" << endl;
				cin >> temp1;

				if (temp1 > 2) {

					cout << "Error" << endl;
				}
				if (temp1 == 1) {

					chooseAbility(p3, p1, 3);
					win = gameOverTeam(p1->getLifepoints(), 3);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 2) {

					chooseAbility(p3, p2, 3);
					win = gameOverTeam(p2->getLifepoints(), 3);
					if (win == 0) {
						break;
					}
				}

				cout << "[Player1] Who do you want to attack? Player3 (1) or Player4 (2)?" << endl;
				cin >> temp1;

				if (temp1 > 2) {

					cout << "Error" << endl;
				}
				if (temp1 == 1) {

					chooseAbility(p1, p3, 1);
					win = gameOverTeam(p3->getLifepoints(), 1);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 2) {

					chooseAbility(p1, p4, 1);
					win = gameOverTeam(p4->getLifepoints(), 1);
					if (win == 0) {
						break;
					}
				}

				cout << "[Player4] Who do you want to attack? Player1 (1) or Player2 (2)?" << endl;
				cin >> temp1;
				if (temp1 > 2) {

					cout << "Error" << endl;
				}
				if (temp1 == 1) {

					chooseAbility(p4, p1, 4);
					win = gameOverTeam(p1->getLifepoints(), 4);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 1) {

					chooseAbility(p4, p2, 4);
					win = gameOverTeam(p2->getLifepoints(), 4);
					if (win == 0) {
						break;
					}
				}
				cout << "Next Round...";
				this_thread::sleep_for(chrono::milliseconds(2500));
				system("CLS");
			}
		}
		if (p1->getSpeed() > p2->getSpeed()) {

			cout << "[Player1] Who do you want to attack? Player3 (1) or Player4 (2)?";
			cin >> temp1;

			if (temp1 > 2) {

				cout << "Error" << endl;
			}
			if (temp1 == 1) {

				chooseAbility(p1, p3, 1);
				win = gameOverTeam(p3->getLifepoints(), 1);
				if (win == 0) {
					break;
				}
			}
			if (temp1 == 2) {

				chooseAbility(p1, p4, 1);
				win = gameOverTeam(p4->getLifepoints(), 1);
				if (win == 0) {
					break;
				}
			}

			if (p3->getSpeed() < p4->getSpeed()) {

				cout << "[Player4] Who do you want to attack? Player1 (1) or Player2 (2)?" << endl;
				cin >> temp1;

				if (temp1 > 2) {

					cout << "Error" << endl;
				}
				if (temp1 == 1) {

					chooseAbility(p4, p1, 4);
					win = gameOverTeam(p1->getLifepoints(), 4);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 2) {

					chooseAbility(p4, p2, 4);
					win = gameOverTeam(p2->getLifepoints(), 4);
					if (win == 0) {
						break;
					}
				}

				cout << "[Player2] Who do you want to attack? Player3 (1) or Player4 (2)?" << endl;
				cin >> temp1;

				if (temp1 > 2) {

					cout << "Error" << endl;
				}
				if (temp1 == 1) {

					chooseAbility(p2, p3, 2);
					win = gameOverTeam(p3->getLifepoints(), 2);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 2) {

					chooseAbility(p2, p4, 2);
					win = gameOverTeam(p4->getLifepoints(), 2);
					if (win == 0) {
						break;
					}
				}

				cout << "[Player3] Who do you want to attack? Player1 (1) or Player2 (2)?" << endl;
				cin >> temp1;
				if (temp1 > 2) {

					cout << "Error" << endl;
				}
				if (temp1 == 1) {
					chooseAbility(p3, p1, 3);
					win = gameOverTeam(p1->getLifepoints(), 3);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 1) {
					chooseAbility(p3, p2, 3);
					win = gameOverTeam(p1->getLifepoints(), 3);
					if (win == 0) {
						break;
					}
				}
				cout << "Next Round...";
				this_thread::sleep_for(chrono::milliseconds(2500));
				system("CLS");
			}
			if (p3->getSpeed() > p4->getSpeed()) {

				cout << "[Player3] Who do you want to attack? Player1 (1) or Player2 (2)?" << endl;
				cin >> temp1;

				if (temp1 > 2) {

					cout << "Error" << endl;
				}
				if (temp1 == 1) {

					chooseAbility(p3, p1, 3);
					win = gameOverTeam(p1->getLifepoints(), 3);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 2) {

					chooseAbility(p3, p2, 3);
					win = gameOverTeam(p2->getLifepoints(), 3);
					if (win == 0) {
						break;
					}
				}
				cout << "[Player2] Who do you want to attack? Player3 (1) or Player4 (2)?" << endl;
				cin >> temp1;
				if (temp1 > 2) {

					cout << "Error" << endl;
				}
				if (temp1 == 1) {

					chooseAbility(p2, p3, 2);
					win = gameOverTeam(p3->getLifepoints(), 2);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 2) {

					chooseAbility(p2, p4, 2);
					win = gameOverTeam(p4->getLifepoints(), 2);
					if (win == 0) {
						break;
					}
				}
				cout << "[Player4] Who do you want to attack? Player1 (1) or Player2 (2)?" << endl;
				cin >> temp1;
				if (temp1 > 2) {

					cout << "Error" << endl;
				}
				if (temp1 == 1) {
					chooseAbility(p4, p1, 4);
					win = gameOverTeam(p1->getLifepoints(), 4);
					if (win == 0) {
						break;
					}
				}
				if (temp1 == 1) {
					chooseAbility(p4, p2, 4);
					win = gameOverTeam(p2->getLifepoints(), 4);
					if (win == 0) {
						break;
					}
				}
				cout << "Next Round...";
				this_thread::sleep_for(chrono::milliseconds(2500));
				system("CLS");
			}
		}
	}
}
