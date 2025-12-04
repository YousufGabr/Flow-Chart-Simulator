#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
class Copy : public Action
{
private:
	Statement* copiedstat;

public:
	Copy(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

