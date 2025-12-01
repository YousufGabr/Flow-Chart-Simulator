#pragma once
#include "Action.h"
#include "..\Statements\VarAssign.h"

class AddVarAssign : public Action
{
private:
	// in the data members of the actions
	// we put the paramaters of the action
	// to be set in ReadActionParameters() then used in Execute()

	Point Position;	//Position where the user clicks to add the stat.
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS; //Right Handside of the assignment (Value) 
	//DONE: you should add LHS and RHS of the assignment statement as parameters

public:
	AddVarAssign(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};

