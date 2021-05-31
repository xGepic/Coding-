#include "AdjazenzListe.h"

AdjazenzListe::AdjazenzListe(string station, int kosten, string linie) {

	this->station = station;
	this->linie = linie;
	this->kosten = kosten;
	this->anzahlNachbarn = 0;
	nachbar = NULL;
	next = NULL;
}

AdjazenzListe::~AdjazenzListe() {

}

string AdjazenzListe::getStation() {

	return station;
}

string AdjazenzListe::getLinie() {

	return linie;
}

int AdjazenzListe::getKosten() {

	return kosten;
}

void AdjazenzListe::incAnzNachbarn() {

	anzahlNachbarn++;
}

int AdjazenzListe::getAnzNachbarn() {

	return anzahlNachbarn;
}

bool AdjazenzListe::inListe(string name) {

	if (station == name) {

		return true;
	}
	else {

		if (next == NULL) {

			return false;
		}
		else {

			return next->inListe(name);
		}
	}
}

AdjazenzListe* AdjazenzListe::addToListe(AdjazenzListe* root, string stationN, int kostenN, string linieN) {
	// falls liste noch leer
	if (!root) {

		return new AdjazenzListe(stationN, kostenN, linieN);
	}

	// sucht das ende der liste
	while (root->next != NULL) {

		root = root->next;
	}
	// ans ende anhängen
	root->next = new AdjazenzListe(stationN, kostenN, linieN);

	// gibt neuen knoten zurück
	return root->next;
}

void AdjazenzListe::addNeighbour(string stationN, int kostenN, string linieN) {
	// am ende der nachbarlsite einfügen
	if (nachbar != NULL) {

		nachbar->addNeighbour(stationN, kostenN, linieN);
	}
	else {

		nachbar = new AdjazenzListe(stationN, kostenN, linieN);
	}
}

AdjazenzListe* AdjazenzListe::findInListe(string name)
{
	// gesuchten knoten zurückgeben
	if (station == name) {

		return this;
	}
	else {

		if (next == NULL) {

			return NULL;
		}
		else {
			return next->findInListe(name);
		}
	}
}