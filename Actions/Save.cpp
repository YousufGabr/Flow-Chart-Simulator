#include "Save.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
#include <fstream>
using namespace std;

Save::Save(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Save::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Enter a File Name To Save FlowChart in ");
	filename = pIn->GetString(pOut);
	if(IsVariable(filename))
	{
		filename += ".txt";
	}
	else
	{
		pOut->PrintMessage("Invalid File Name! File name should start with an alphabet or underscore and contain only alphanumeric characters and underscores.");
		filename = "";
	}
}

void Save::Execute() {

	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (filename == "")
	{
		return;
	}
	ofstream OutFile(filename);
	pManager->SaveAll(OutFile);
	OutFile.close();
	pOut->PrintMessage("Flowchart saved to " + filename);
}


