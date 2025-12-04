#include "Copy.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

Copy::Copy(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Copy::ReadActionParameters()
{
	copiedstat = pManager->GetSelectedStatement();
}

void Copy::Execute() {

	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if(copiedstat==NULL)
	{
		pOut->PrintMessage("No Statement is Selected to Copy");
		return;
	}
	pManager->SetClipboard(copiedstat);
	pOut->PrintMessage("Statement Copied to Clipboard");
}

