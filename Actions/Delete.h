#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
class Delete : public Action
{
private:
	Statement* selectedstat;
	Connector* selectedcon;

public:
	Delete(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

