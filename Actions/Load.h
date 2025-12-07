#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
class Load : public Action
{
private:
	string filename, type;
	Statement* loadedstat;
	Connector* loadedcon;
	Statement* start;
	Statement* end;
	Point Corner;

public:
	Load(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

