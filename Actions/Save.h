#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
class Save : public Action
{
private:
	string filename;

public:
	Save(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

