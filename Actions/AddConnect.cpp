#include "AddConnect.h"
#include "..\ApplicationManager.h"
#include "..\Statements\End.h"
#include "..\Statements\Start.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddConnect::AddConnect(ApplicationManager* pAppManager) :Action(pAppManager)
{
	con = NULL;
	src = NULL;
	dst = NULL;
}

void AddConnect::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Adding Connector: Click to Select Source statement");

	pIn->GetPointClicked(Position);
	src = pManager->GetStatement(Position);

	if (src == NULL)
	{
		pOut->PrintMessage("Aborted: No Source Statement Selected");
		src = NULL;
		dst = NULL;
		return;
	}
	if (dynamic_cast<End*>(src))
	{
		pOut->PrintMessage("Aborted: Can't Make END Statement The Source Statement");
		src = NULL;
		dst = NULL;
		return;
	}

	pOut->PrintMessage("Adding Connector: Click to Select Destination statement");
	pIn->GetPointClicked(Position);
	dst = pManager->GetStatement(Position);

	if (dst == NULL)
	{
		pOut->PrintMessage("Aborted: No Destination Statement Selected");
		src = NULL;
		dst = NULL;
		return;
	}
	if (dynamic_cast<Start*>(dst))
	{
		pOut->PrintMessage("Aborted: Can't Make Start Statement The Destination Statement");
		src = NULL;
		dst = NULL;
		return;
	}
	if(src==dst)
	{
		pOut->PrintMessage("Aborted: Source and Destination Statements Can't Be The Same");
		src = NULL;
		dst = NULL;
		return;
	}
	
	pOut->ClearStatusBar();
}

void AddConnect::Execute()
{
	ReadActionParameters();
	if (src == NULL || dst == NULL)
		return;


	//Calculating left corner of Declare statement block
	

	Connector* pConn = new Connector(src, dst);
	pConn->setStartPoint(src->GetOutlet());
	pConn->setEndPoint(dst->GetInlet());

	pManager->AddConnector(pConn); // Adds the created statement to application manger's statement list
}