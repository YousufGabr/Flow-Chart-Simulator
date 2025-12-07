#include "AddCondition.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddCondition::AddCondition(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddCondition::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Conditional Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	LHS = pIn->GetVariable(pOut);
	Op = pIn->GetCompOperator(pOut);

	pOut->PrintMessage("Enter Right Hand Side value:");
	do {
		RHS = pIn->GetString(pOut);
		if (ValueOrVariable(RHS) != INVALID_OP) break;
		pOut->PrintMessage("Invalid Input, Try Again");
	} while (true);
	pOut->ClearStatusBar();
	//DONE: Ask the user in the status bar to enter the LHS and RHS set the data member

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddCondition::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	Condition* pAssign = new Condition(Corner, LHS, Op, RHS);
	//DONE: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}


