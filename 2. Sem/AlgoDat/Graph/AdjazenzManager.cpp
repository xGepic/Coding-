#include "AdjazenzManager.h"
#include "AdjazenzListe.h"
#include "MinList.h"
#include <fstream>
#include <set>
#include <list>
#include<algorithm>

AdjazenzManager::AdjazenzManager() {

	root = NULL;
	anzahlStationen = 0;
}

AdjazenzManager::~AdjazenzManager() {

}

bool AdjazenzManager::readFile(string fileName) {

	fileName += ".txt";

	// helfer variablen
	ifstream textread(fileName);
	string line;
	unsigned int i = 0;
	string linieNeu = "";
	string kostenLesen = "";
	int kostenNeu = 0;
	string stationNeu = "";

	AdjazenzListe* vorherigeStation = NULL;
	AdjazenzListe* steheIn = root;

	// zeile pro zeile (und linie)
	while (getline(textread, line)) {

		linieNeu = "";

		// zuerst name der linie einlesen
		while (i < line.size() && line[i] != ':') {

			linieNeu += line[i++];
		}
		i += 3; // doppelpunkt, abstang und " überspringen

		// und den ersten stationsnamen
		while (i < line.size() && line[i] != '"') {

			stationNeu += line[i++];
		}
		i += 2; // " und abstand überspringen

		// falls es die station in der liste noch nicht gibt wird er eingefügt
		if (root == NULL || (!root->inListe(stationNeu))) {

			if (root == NULL) {

				root = root->addToListe(root, stationNeu, 0, "");
				anzahlStationen++;
				steheIn = root;
			}
			else {

				steheIn = root->addToListe(root, stationNeu, 0, "");
				anzahlStationen++;
			}
		}
		// ansonsten "stellt" man sich in die aktuelle Station rein weil nun ein neuer nachbar hinzukommt
		else {

			steheIn = root->findInListe(stationNeu);
		}
		stationNeu = "";

		//rest einlesen
		while (i < line.size()) {

			// kosten einlesen, aus string zu int
			while (i < line.size() && line[i] != ' ') {

				kostenLesen += line[i++];
			}
			i += 2; // abstand und " überspringen
			int kostenNeu = stoi(kostenLesen);

			// station name einlesen
			while (i < line.size() && line[i] != '"') {

				stationNeu += line[i++];
			}
			i += 2; // " und abstand überspringen

			vorherigeStation = steheIn;

			// falls die neue station noch nicht exisitert wir ein neueer knoten angefügt
			if (!root->inListe(stationNeu)) {

				steheIn = steheIn->addToListe(steheIn, stationNeu, 0, "");
				anzahlStationen++;
			}
			// ansonsten stellt man sich nur in die neue aktuelle station
			else {
				steheIn = root->findInListe(stationNeu);
			}

			// für die letzten zwei statioenn werden die sich nun gegenseitig als nachbarn eingetragen
			vorherigeStation->addNeighbour(stationNeu, kostenNeu, linieNeu);
			vorherigeStation->incAnzNachbarn();
			steheIn->addNeighbour(vorherigeStation->getStation(), kostenNeu, linieNeu);
			steheIn->incAnzNachbarn();
			kostenLesen = "";
			stationNeu = "";
		}

		i = 0;
	}
	textread.close();

	return true;
}

void AdjazenzManager::printAdjazentListe() {

	AdjazenzListe* helper = root;
	AdjazenzListe* nachbarn = NULL;

	while (helper != NULL) {

		cout << "Station:" << helper->getStation() << endl;
		cout << "Nachbarn (Anzahl: " << helper->getAnzNachbarn() << "): " << endl;
		nachbarn = helper->nachbar;

		while (nachbarn != NULL) {

			cout << nachbarn->getStation() << " mit kosten " << nachbarn->getKosten() << endl;
			nachbarn = nachbarn->nachbar;
		}
		cout << endl << endl;
		helper = helper->next;
	}
}

void AdjazenzManager::shortestPath(string start, string finish) {


	list<string> nachbarnListe;
	list<string>::iterator it;
	list<string>::iterator del;

	AdjazenzListe* anfang = root;
	AdjazenzListe* ende = root;
	AdjazenzListe* nachbarnBeginLinks = NULL;
	AdjazenzListe* nachbarnBeginRechts = NULL;
	AdjazenzListe* nachbarnEndLinks = NULL;
	AdjazenzListe* nachbarnEndRechts = NULL;

	anfang = anfang->findInListe(start);
	ende = ende->findInListe(finish);

	cout << "Found!" << endl;
	cout << "Starting search from " << anfang->getStation() << " to " << ende->getStation() << " via" << endl;

	while (true) {

		nachbarnBeginLinks = anfang->nachbar;
		nachbarnBeginRechts = nachbarnBeginLinks->nachbar;
		nachbarnEndLinks = ende->nachbar;
		nachbarnEndRechts = nachbarnEndLinks->nachbar;
		anfang = anfang->next;


		if (nachbarnBeginLinks->getStation() == nachbarnEndLinks->getStation()) {

			del = --nachbarnListe.end();
			nachbarnListe.erase(del);
			nachbarnListe.push_back("Umsteigen!");
			nachbarnListe.push_back(nachbarnEndRechts->getStation());
			nachbarnListe.push_back(ende->getStation());
			break;
		}
		else if (nachbarnBeginLinks->getStation() == nachbarnEndRechts->getStation()) {

			del = --nachbarnListe.end();
			nachbarnListe.erase(del);
			nachbarnListe.push_back("Umsteigen!");
			nachbarnListe.push_back(nachbarnBeginLinks->getStation());
			nachbarnListe.push_back(ende->getStation());
			break;
		}
		else if (nachbarnBeginRechts->getStation() == nachbarnEndRechts->getStation()) {

			del = --nachbarnListe.end();
			nachbarnListe.erase(del);
			nachbarnListe.push_back("Umsteigen!");
			nachbarnListe.push_back(nachbarnBeginLinks->getStation());
			nachbarnListe.push_back(ende->getStation());
			break;
		}
		nachbarnListe.push_back(nachbarnBeginRechts->getStation());
	}
	for (it = nachbarnListe.begin(); it != nachbarnListe.end(); ++it) {
		cout << *it << " ";
	}
}

int AdjazenzManager::getIndexAt(string warteschlange[], string station) {

	for (int i = 0; i < anzahlStationen; i++) {

		if (warteschlange[i] == station) {

			return i;
		}
	}
	return 1;
}

void AdjazenzManager::dijkstra(string start, string finish) {

	cout << endl << "A path from " << start << " to " << finish << endl;

	if (root->findInListe(start) == NULL || root->findInListe(finish) == NULL) {

		cout << "Those nodes do not exist!!" << endl;
		return;
	}

	MinList* warteschlange = NULL;
	//nachbarn von x
	list<string> nachfolger;
	list<string>::iterator it;
	AdjazenzListe* helper = root;

	int index;
	int kosten;
	int indexAktuellWo;
	string aktuellWo;

	// array das alle stationen in gespeicherte reihenfolge mit stationsnamen enthält
	string* alleStationen = new string[anzahlStationen];
	// array in dem für alle stationen die kosten von start zu sich selbst gespeichert werden
	int* kostenArray = new int[anzahlStationen];
	// array das für alle stationen die vorgänger bestimmt (dijkstra)
	string* vorgaenger = new string[anzahlStationen];

	// mit "unendlich" initiiert
	for (int i = 0; i < anzahlStationen; i++) {

		kostenArray[i] = 9999;
	}

	for (int i = 0; i < anzahlStationen && helper != NULL; i++) {
		alleStationen[i] = helper->getStation();
		helper = helper->next;
	}

	// den startpunkt direkt in warteliste geben
	indexAktuellWo = getIndexAt(alleStationen, start);
	kostenArray[indexAktuellWo] = 0;
	warteschlange = warteschlange->insertInto(warteschlange, start, 0);

	do {

		// kleinstes element aus warteschalnge nehmen und entfernen
		aktuellWo = warteschlange->top_element();
		indexAktuellWo = getIndexAt(alleStationen, aktuellWo);
		warteschlange = warteschlange->pop_top();
		helper = root->findInListe(aktuellWo);

		// alle nachbarn von aktuellem knoten in nachbar liste geben
		helper = helper->nachbar;
		while (helper != NULL) {

			nachfolger.push_back(helper->getStation());
			helper = helper->nachbar;
		}

		//nachbar liste durchgehen 
		for (it = nachfolger.begin(); it != nachfolger.end(); ++it) {

			// den aktuell anzuschaunden nachbar in dem array finden
			index = getIndexAt(alleStationen, *it);
			// den aktuellen knoten in der adjazenzliste finden
			helper = root->findInListe(alleStationen[indexAktuellWo]);
			helper = helper->nachbar;

			// aus der adjazenzliste den entsprechenden knoten des nachbar suchen, weil dort die kosten stehen
			while (helper->getStation() != alleStationen[index]) {

				helper = helper->nachbar;
			}
			kosten = helper->kosten + kostenArray[indexAktuellWo];

			// falls die neu ausgerechneten kosten besser sind ( am anfang für alle unendlich) dann wird es in das araay überschrieben und der nachbar in die warteschalge gegeben
			if (kosten < kostenArray[index]) {
				// außerdem wird der vogänger natürlcih gespeichert
				vorgaenger[index] = aktuellWo;
				kostenArray[index] = kosten;

				warteschlange = warteschlange->insertInto(warteschlange, alleStationen[index], kostenArray[index]);
			}
		}
		nachfolger.clear();

	} while (warteschlange != NULL);

	// in dem array stehn nun alle kosten von allen knoten, bei finish rauslesen
	index = getIndexAt(alleStationen, finish);
	cout << "Fahrzeit beträgt " << kostenArray[index] << " Minuten" << endl << endl;
	cout << "The path: " << endl;
	// funktion die den fahrplan ausgibt
	print_path(start, finish, alleStationen, vorgaenger, "");
}

void AdjazenzManager::print_path(string start, string finish, string alleStationen[], string vorgaenger[], string gefahren_mit) {

	// wird rekursiv vom ende richtung anfang aufgerufen, wenn am anfang angekommen also vorbei
	if (start == finish) {

		return;
	}

	// index von aktuellem endknoten und vorgänger finden
	int index_finish = getIndexAt(alleStationen, finish);
	int index_vor = getIndexAt(alleStationen, vorgaenger[index_finish]);

	AdjazenzListe* helper = root->findInListe(vorgaenger[index_finish]);
	helper = helper->nachbar;

	// den knoten vom vorgänger finden, der nach finish fährt, weil dort steht mit welcher linie gefahren wird
	while (helper->getStation() != finish) {

		helper = helper->nachbar;
	}

	string fahre_mit = helper->linie;

	// da die aktuelle linie auch in der funktion mitgegebn wird, versuchen wir, nicht unnötig umzusteigen
	while (helper != NULL) {

		if (helper->getStation() == finish && helper->linie == gefahren_mit) {

			fahre_mit = helper->linie;
		}
		helper = helper->nachbar;
	}

	// rekursiver aufruf
	print_path(start, vorgaenger[index_finish], alleStationen, vorgaenger, fahre_mit);

	// erst danach printen weil es ja von hinten aufgerufen wird
	cout << fahre_mit << ": " << vorgaenger[index_finish] << " -> " << finish << endl;

	// falls fahrmittel gewechselt wird
	if (gefahren_mit != fahre_mit && gefahren_mit != "") {

		cout << "Achtung! Umsteigen bei " << finish << " von Linie " << fahre_mit << " zu Linie " << gefahren_mit << endl;
	}
}

bool AdjazenzManager::existsInList(string station) {

	if (root->findInListe(station) != NULL) {

		return true;
	}
	else {
		return false;
	}
}