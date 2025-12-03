#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\Connector.h"
class AddConnect : public Action
{
private:
	// in the data members of the actions
	// we put the paramaters of the action
	// to be set in ReadActionParameters() then used in Execute()
	Point Position;	//Position where the user clicks to add the stat.
	Connector* con;
	Statement* src;
	Statement* dst;


public:
	AddConnect(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

