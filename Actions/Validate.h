#pragma once
#include "Action.h"

class Validate : public Action
{
private:


public:
	Validate(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

