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
	pOut->PrintMessage("Click to Select/Unselect a statement or connector");
	pIn->GetPointClicked(p);
	ptr = pManager->GetStatement(p);
	con = pManager->GetConnector(p);
	pOut->ClearStatusBar();
}

void Select::Execute() {
	ReadActionParameters();
	if (ptr != NULL) {
		if (pManager->GetSelectedConnector() != NULL)
		{
			pManager->GetSelectedConnector()->SetSelected(false);
			pManager->SetSelectedConnector(NULL);
		}
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
	else if (con != NULL) {
		if (pManager->GetSelectedStatement() != NULL)
		{
			pManager->GetSelectedStatement()->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
		}
		if (con->IsSelected()) {
			con->SetSelected(false);
			pManager->SetSelectedConnector(NULL);
		}
		else {
			if (pManager->GetSelectedConnector() != NULL)
			{
				pManager->GetSelectedConnector()->SetSelected(false);
			}
			con->SetSelected(true);
			pManager->SetSelectedConnector(con);
		}
	}

}
