#include "AddEnd.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddEnd::AddEnd(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddEnd::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (End::getExists())
	{
		pOut->PrintMessage("Aborted: End statement already exists!");
		return;
	}

	//Read the (Position) parameter
	pOut->PrintMessage("End Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	if (Position.y < UI.ToolBarHeight || Position.y > UI.height - UI.StatusBarHeight || Position.x > UI.DrawingAreaWidth)
	{
		pOut->PrintMessage("Aborted: Cannot place statement here!");
		return;
	}
	pOut->ClearStatusBar();
}

void AddEnd::Execute()
{
	ReadActionParameters();
	if (End::getExists()) return;
	if (Position.y < UI.ToolBarHeight || Position.y > UI.height - UI.StatusBarHeight || Position.x > UI.DrawingAreaWidth) return;

	if (pManager->getIscut())
	{
		if (dynamic_cast<End*>(pManager->GetClipboard()))
		{
			delete pManager->GetClipboard();
			pManager->SetClipboard(NULL);
			pManager->setIscut(false);
		}
	}


	//Calculating left corner of Write statement block
	Point Corner;
	Corner.x = Position.x - 50;
	Corner.y = Position.y;

	End* pAssign = new End(Corner);

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}