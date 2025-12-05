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
	pManager->SetClipboard(cutstat);
	pManager->RemoveStatement(cutstat);
	pManager->setIscut(true);
	pOut->PrintMessage("Statement Cut Successfully");
}


