#include "Read.h"
#include <sstream>

using namespace std;

Read::Read(Point Lcorner, string Var)
{
	Variable = Var;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void Read::setVar(const string& V)
{
	Variable = V;
	UpdateStatementText();
}


void Read::Draw(Output* pOut) const
{
	//Call Output::DrawWrite function to draw Write statement 	
	pOut->DrawRead(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

bool Read::ifclicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + 5 * UI.ASSGN_WDTH / 4 &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}

Point Read::GetInlet() const
{
	return Inlet;
}
Point Read::GetOutlet() const
{
	return Outlet;
}

void Read::getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2)
{
	srhs = Variable;
}

void Read::Edit(ApplicationManager* pManager)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Variable = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
	UpdateStatementText();
}

void Read::Save(ofstream& OutFile)
{
	OutFile << "READ " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << Variable << endl;
}

void Read::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> Variable;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	UpdateStatementText();
}


//This function should be called when Variable changes
void Read::UpdateStatementText()
{
	ostringstream T;
	T << "Read " << Variable;
	Text = T.str();
}
