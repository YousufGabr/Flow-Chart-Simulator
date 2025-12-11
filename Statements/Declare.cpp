#include "Declare.h"
#include <sstream>

using namespace std;

Declare::Declare(Point Lcorner, string Var)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	Variable = Var;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void Declare::setVar(const string& V)
{
	Variable = V;
	UpdateStatementText();
}


void Declare::Draw(Output* pOut) const
{
	//Call Output::DrawDeclare function to draw Declare statement 	
	pOut->DrawDeclare(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

bool Declare::ifclicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}

Point Declare::GetInlet() const
{
	return Inlet;
}
Point Declare::GetOutlet() const
{
	return Outlet;
}
void Declare::setOutConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* Declare::getOutConnector() const
{
	return pOutConn;
}

void Declare::getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2)
{
	srhs = Variable;
}

void Declare::Edit(ApplicationManager* pManager)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Variable = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
	UpdateStatementText();
}

void Declare::Save(ofstream& OutFile)
{
	OutFile << "DECLARE " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << Variable << endl;
}

void Declare::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> Variable;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	UpdateStatementText();
}

void Declare::ValidateStat(ApplicationManager* pManager)
{
	pManager->addVariable(Variable, 0);
	pOutConn->getDstStat()->ValidateStat(pManager);
}

void Declare::Simulate(ApplicationManager* pManager)
{
	pManager->addVariable(Variable, 0);
	pOutConn->getDstStat()->Simulate(pManager);
}

//This function should be called when Variable changes
void Declare::UpdateStatementText()
{
	ostringstream T;
	T << "Double " << Variable;
	Text = T.str();
}

