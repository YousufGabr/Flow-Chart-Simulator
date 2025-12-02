#include "AddDeclare.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddDeclare::AddDeclare(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddDeclare::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Declare Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();
	Variable = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
}

void AddDeclare::Execute()
{
	ReadActionParameters();


	//Calculating left corner of Declare statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	Declare* pAssign = new Declare(Corner, Variable);

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}