#include "Cut.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

Cut::Cut(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Cut::ReadActionParameters()
{
	cutstat = pManager->GetSelectedStatement();
}

void Cut::Execute() {

	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (cutstat == NULL)
	{
		pOut->PrintMessage("No Statement is Selected to Cut");
		return;
	}
	pManager->SetSelectedStatement(NULL);
	pManager->SetClipboard(cutstat);
	pManager->RemoveStatement(cutstat);
	pManager->setIscut(true);
	pOut->PrintMessage("Statement Cut Successfully");
}


