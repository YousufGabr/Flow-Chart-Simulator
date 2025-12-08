#include "AddRead.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddRead::AddRead(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddRead::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Read Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	if (Position.y < UI.ToolBarHeight || Position.y > UI.height - UI.StatusBarHeight || Position.x > UI.DrawingAreaWidth)
	{
		pOut->PrintMessage("Aborted: Cannot place statement here!");
		return;
	}
	pOut->ClearStatusBar();
	Variable = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
}

void AddRead::Execute()
{
	ReadActionParameters();
	if (Position.y < UI.ToolBarHeight || Position.y > UI.height - UI.StatusBarHeight || Position.x > UI.DrawingAreaWidth) return;


	//Calculating left corner of Write statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	Read* pAssign = new Read(Corner, Variable);

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}


