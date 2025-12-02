#include "Select.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

Select::Select(ApplicationManager* pAppManager) :Action(pAppManager)
{}

void Select::ReadActionParameters() {

	Point p;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Click to Select a statement or connector");
	pIn->GetPointClicked(p);
	ptr = pManager->GetStatement(p);
}

void Select::Execute() {
	ReadActionParameters();
	if (ptr != NULL) {
		if (ptr->IsSelected()) {
			ptr->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
		}
		else {
			if (pManager->GetSelectedStatement() != NULL) 
			{
				pManager->GetSelectedStatement()->SetSelected(false);
			}
			ptr->SetSelected(true);
			pManager->SetSelectedStatement(ptr);
		}
	}
}
