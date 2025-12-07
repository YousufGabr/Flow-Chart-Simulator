#pragma once
#include "Action.h"
#include "..\Statements\Condition.h"
class AddCondition : public Action
{
private:

	Point Position;	//Position where the user clicks to add the stat.
	string LHS;	//Left Handside
	string Op;   //Operator of the operation assignment
	string RHS; //Right Handside
	//DONE: you should add LHS and RHS of the assignment statement as parameters

public:
	AddCondition(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};

