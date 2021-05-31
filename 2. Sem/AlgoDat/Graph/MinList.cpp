#include "MinList.h"

MinList::MinList(string station, int kosten) {

	this->kosten = kosten;
	this->station = station;
	next = NULL;
}

MinList::~MinList(){

}

MinList* MinList::insertInto(MinList* root, string station, int kosten) {

	if (!root) {

		return new MinList(station, kosten);
	}

	// falls es die Station gibt, dann wird sie zuerst entfernt und dann wieder richtig eingefügt
	// das ist damit es nicht doppelt exisitert oder verschoben/verändert werden muss
	if (root->exists(station)) {

		root->entfernen(station);
	}

	MinList* newElement = new MinList(station, kosten);
	MinList* previous = root;
	MinList* current = root->next;

	// das kleinste -> neues Anfangselement
	if (kosten < root->kosten) {

		newElement->next = root;
		return newElement;
	}

	// Stelle zum einfügen suchen
	while (current != NULL) {

		if (kosten < current->kosten) {

			newElement->next = current;
			previous->next = newElement;
			return root;
		}
		previous = current;
		current = current->next;
	}

	//current == NULL, größtes element ans ende
	previous->next = newElement;
	return root;
}

string MinList::top_element() {

	return station;
}

MinList* MinList::pop_top() {

	if (this == NULL) {

		return NULL;
	}
	return this->next;
}

bool MinList::exists(string stationX) {

	MinList* helper = this;

	while (helper != NULL) {

		if (helper->station == stationX) {

			return true;
		}
		helper = helper->next;
	}
	return false;
}

MinList* MinList::entfernen(string stationX) {

	MinList* root = this;
	MinList* previous = root;
	MinList* current = root->next;

	// neues Anfangselement
	if (previous->station == stationX) {

		return current;
	}

	// richtig umketten
	while (current != NULL) {

		if (current->station == stationX) {

			previous->next = current->next;
			return root;
		}
		previous = current;
		current = current->next;
	}
	return root;
}