#include "AddWrite.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddWrite::AddWrite(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddWrite::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Write Statement: Click to add the statement");

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
	pOut->PrintMessage("Enter a Variable or Message");
	do {
		input = pIn->GetString(pOut);
		if (input.front() == '"' && input.back() == '"')
		{
			ismsg = true;
			break;
		}
		else if (IsVariable(input))
		{
			ismsg = false;
			break;
		}
		pOut->PrintMessage("invalid Input, try again:");
	} while (true);
	
	pOut->ClearStatusBar();
}

void AddWrite::Execute()
{
	ReadActionParameters();
	if (Position.y < UI.ToolBarHeight || Position.y > UI.height - UI.StatusBarHeight || Position.x > UI.DrawingAreaWidth || pManager->GetStatement(Position)) return;

	//Calculating left corner of Write statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	Write* pAssign = new Write(Corner, input);
	pAssign->setMSG(ismsg);

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

