#include "Delete.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

Delete::Delete(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Delete::ReadActionParameters() 
{
	selectedstat = pManager->GetSelectedStatement();
	selectedcon = pManager->GetSelectedConnector();
}

void Delete::Execute() {
	
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (selectedcon == NULL && selectedstat == NULL)
	{
		pOut->PrintMessage("No Statement or Connector is Selected to Delete");
	}
	else if (selectedstat != NULL) {
		pManager->RemoveStatement(selectedstat);
		delete selectedstat;
		pManager->SetSelectedStatement(NULL);
		pOut->PrintMessage("Statement and Its Connectors Deleted Successfully");
	}
	else if (selectedcon != NULL) {
		pManager->RemoveConnector(selectedcon);
		pManager->SetSelectedConnector(NULL);
		pOut->PrintMessage("Connector Deleted Successfully");
	}

}
