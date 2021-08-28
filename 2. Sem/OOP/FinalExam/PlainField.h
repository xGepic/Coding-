#pragma once
#include "Field.h"

class PlainField : public Field {

private:


public:

	PlainField();
	virtual bool execute() override;
};