#include "Edit.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

Edit::Edit(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Edit::ReadActionParameters()
{
	Editstat = pManager->GetSelectedStatement();
}

void Edit::Execute() {

	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (Editstat == NULL)
	{
		pOut->PrintMessage("No Statement is Selected to Edit");
		return;
	}
	Editstat->Edit(pManager);
	pOut->PrintMessage("Statement Edited Successfully");
}


