#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
class Edit : public Action
{
private:
	Statement* Editstat;

public:
	Edit(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

