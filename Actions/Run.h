#pragma once
#include "Action.h"
class Run : public Action
{
private:


public:
	Run(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

