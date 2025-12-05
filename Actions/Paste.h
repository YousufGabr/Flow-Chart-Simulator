#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
class Paste : public Action
{
private:
	Statement* copiedstat;
	Statement* newstat;
	Point p,Corner;
	string LHS,SRHS,OP;
	double DRHS;
	bool cut;

public:
	Paste(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

