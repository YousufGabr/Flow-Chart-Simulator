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
	if(Start::getExists())
	{
		pOut->PrintMessage("Aborted: Start statement already exists!");
		return;
	}

	//Read the (Position) parameter
	pOut->PrintMessage("Start Statement: Click to add the statement");

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
}

void AddStart::Execute()
{
	ReadActionParameters();
	if (Start::getExists()) return;
	if (Position.y < UI.ToolBarHeight || Position.y > UI.height - UI.StatusBarHeight || Position.x > UI.DrawingAreaWidth || pManager->GetStatement(Position)) return;
	if (pManager->getIscut())
	{
		if (dynamic_cast<Start*>(pManager->GetClipboard()))
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

	Start* pAssign = new Start(Corner);

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}


