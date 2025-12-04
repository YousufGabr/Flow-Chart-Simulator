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
	stat = pManager->GetStatement(p);
	con = pManager->GetConnector(p);
	pOut->ClearStatusBar();
	if (stat == NULL && con == NULL) {
		pOut->PrintMessage("No Statement or Connector Selected");
	}
}

void Select::Execute() {
	ReadActionParameters();
	if (stat != NULL) {
		if (pManager->GetSelectedConnector() != NULL)
		{
			pManager->GetSelectedConnector()->SetSelected(false);
			pManager->SetSelectedConnector(NULL);
		}
		if (stat->IsSelected()) {
			stat->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
		}
		else {
			if (pManager->GetSelectedStatement() != NULL) 
			{
				pManager->GetSelectedStatement()->SetSelected(false);
			}
			stat->SetSelected(true);
			pManager->SetSelectedStatement(stat);
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
