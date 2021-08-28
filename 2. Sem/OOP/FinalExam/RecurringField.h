#pragma once
#include "Field.h"

class RecurringField : public Field {

private:


public:

	RecurringField();
	virtual bool execute() override;
};