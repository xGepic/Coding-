#ifndef MINLIST_H
#define MINLIST_H
#include <string>

using namespace std;

// ein eigener MinHeap
class MinList {

public:
    MinList(string station, int kosten);
    virtual ~MinList();

    // name der Station
    string station;
    // kosten von Start zu diesem Punkt
    int kosten;
    // das nächst teurere Element im Heap
    MinList* next;

    // das Element wird richtig eingeordnet beim einfügen
    MinList* insertInto(MinList* root, string station, int kosten);

    // gibt den Stationsnamen zurück
    string top_element();
    // gibt den Kopf des nächsten Elements zurück
    MinList* pop_top();
    // ob die Station mit Namen staionx bereits in der Liste existiert
    bool exists(string stationX);
    // entfernt Station mit Namen staionx aus Liste (kettet um)
    MinList* entfernen(string stationX);

protected:

private:
};

#endif // MINLIST_H