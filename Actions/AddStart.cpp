#include "AddStart.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddStart::AddStart(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddStart::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Start Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();
}

void AddStart::Execute()
{
	ReadActionParameters();


	//Calculating left corner of Write statement block
	Point Corner;
	Corner.x = Position.x - 50;
	Corner.y = Position.y;

	Start* pAssign = new Start(Corner);

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}


