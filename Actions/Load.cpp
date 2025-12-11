#include "Load.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Statements\Start.h"
#include "..\Statements\End.h"
#include "..\Statements\OpAssign.h"
#include "..\Statements\Condition.h"
#include "..\Statements\VarAssign.h"
#include "..\Statements\ValueAssign.h"
#include "..\Statements\Read.h"
#include "..\Statements\Write.h"
#include "..\Statements\Declare.h"

#include <sstream>
#include <fstream>
using namespace std;

Load::Load(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Load::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Enter a File Name To Load FlowChart From ");
	filename = pIn->GetString(pOut);
	if (IsVariable(filename))
	{
		filename += ".txt";
	}
	else
	{
		pOut->PrintMessage("Invalid File Name! File name should start with an alphabet or underscore and contain only alphanumeric characters and underscores.");
		filename = "";
	}
}

void Load::Execute() {

	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (filename == "")
	{
		return;
	}
	ifstream InFile(filename);
	if (!InFile)
	{
		pOut->PrintMessage("Error: Could not open file " + filename);
		return;
	}
	pManager->clearall();

	int num1, num2;
	InFile >> num1;
	while (num1 > 0) {

		InFile >> type;

		if (type == "START")
			loadedstat = new Start(Corner);
		else if (type == "END")
			loadedstat = new End(Corner);
		else if (type == "VAL_ASSIGN")
			loadedstat = new ValueAssign(Corner);
		else if (type == "VAR_ASSIGN")
			loadedstat = new VarAssign(Corner);
		else if (type == "OP_ASSIGN")
			loadedstat = new OpAssign(Corner);
		else if (type == "DECLARE")
			loadedstat = new Declare(Corner);
		else if (type == "READ")
			loadedstat = new Read(Corner);
		else if (type == "WRITE")
			loadedstat = new Write(Corner);
		else if (type == "CONDITION")
			loadedstat = new Condition(Corner);

		loadedstat->Load(InFile);
		pManager->AddStatement(loadedstat);
		num1--;
	}
	InFile >> num2;
	while (num2 > 0)
	{
		int srcid, dstid, conid;
		InFile >> srcid >> dstid >> conid;
		start = pManager->SearchStatementByID(srcid);
		end = pManager->SearchStatementByID(dstid);
		if (dynamic_cast<Condition*>(start))
		{
			Condition* cond = dynamic_cast<Condition*>(start);
			if (conid==1)
			{
				loadedcon = new Connector(start, end);
				cond->setTOutConn(loadedcon);
				loadedcon->setStartPoint(cond->GetTOutlet());
				loadedcon->setEndPoint(end->GetInlet());
				loadedcon->setID(1); // to identify true branch
				pManager->AddConnector(loadedcon);
				num2--;
				continue;
			}
			else if (conid == 2)
			{
				loadedcon = new Connector(start, end);
				cond->setFOutConn(loadedcon);
				loadedcon->setStartPoint(cond->GetFOutlet());
				loadedcon->setEndPoint(end->GetInlet());
				loadedcon->setID(2); // to identify false branch
				pManager->AddConnector(loadedcon);
				num2--;
				continue;
			}
		}
		else
		{
			loadedcon = new Connector(start, end);
			loadedcon->setStartPoint(start->GetOutlet());
			loadedcon->setEndPoint(end->GetInlet());
			start->setOutConnector(loadedcon);
			pManager->AddConnector(loadedcon);
			num2--;
		}
	}
	pManager->ArrangeStatementIDs();
}



