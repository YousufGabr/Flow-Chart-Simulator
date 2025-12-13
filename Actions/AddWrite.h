#pragma once
#include "Action.h"
#include "..\Statements\Write.h"
class AddWrite : public Action
{
private:
	// in the data members of the actions
	// we put the paramaters of the action
	// to be set in ReadActionParameters() then used in Execute()

	Point Position;	//Position where the user clicks to add the stat.
	string input;	//Variable to be written
	bool ismsg;

public:
	AddWrite(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};

