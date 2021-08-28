#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <stdlib.h>

class Field {

public:

	Field();
	virtual ~Field();
	void displayField();
	int getPoints();
	void setPoints(int x);
	virtual bool execute() = 0;

protected:

	int points;   //The remaining points of the field
	char display; //The character used to display the field in the world

private:

};
#endif // FIELD_H