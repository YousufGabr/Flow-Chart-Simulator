#pragma once
#include "Action.h"
#include "..\Statements\OpAssign.h"

class AddOpAssign : public Action
{
private:

	Point Position;	//Position where the user clicks to add the stat.
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS1; //Right Handside of the assignment (Value) 
	string Op;   //Operator of the operation assignment
	string RHS2; //Second Right Handside of the operation assignment (Value)
	//DONE: you should add LHS and RHS of the assignment statement as parameters

public:
	AddOpAssign(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};

