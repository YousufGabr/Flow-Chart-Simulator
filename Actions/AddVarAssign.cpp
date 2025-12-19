#include "AddVarAssign.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddVarAssign::AddVarAssign(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddVarAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Variable Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	if (Position.y < UI.ToolBarHeight || Position.y > UI.height - UI.StatusBarHeight || Position.x > UI.DrawingAreaWidth)
	{
		pOut->PrintMessage("Aborted: Cannot place statement here!");
		return;
	}
	if (pManager->GetStatement(Position))
	{
		pOut->PrintMessage("Aborted: Cannot place statement on another statement!");
		return;
	}
	pOut->ClearStatusBar();
	LHS = pIn->GetVariable(pOut);
	RHS = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
	//DONE: Ask the user in the status bar to enter the LHS and RHS set the data member

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddVarAssign::Execute()
{
	ReadActionParameters();
	if (Position.y < UI.ToolBarHeight || Position.y > UI.height - UI.StatusBarHeight || Position.x > UI.DrawingAreaWidth || pManager->GetStatement(Position)) return;

	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	VarAssign* pAssign = new VarAssign(Corner, LHS, RHS);
	//DONE: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}
