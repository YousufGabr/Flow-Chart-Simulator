#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
class Cut : public Action
{
private:
	Statement* cutstat;

public:
	Cut(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

