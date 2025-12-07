#include "VarAssign.h"
#include <sstream>

using namespace std;

VarAssign::VarAssign(Point Lcorner, string LeftHS, string RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddVarAssign) action
	//       before passing it to the constructor of VarAssign
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void VarAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void VarAssign::setRHS(const string& R)
{
	RHS = R;
	UpdateStatementText();
}


void VarAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

bool VarAssign::ifclicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}

Point VarAssign::GetInlet() const
{
	return Inlet;
}
Point VarAssign::GetOutlet() const
{
	return Outlet;
}
void VarAssign::setOutConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* VarAssign::getOutConnector() const
{
	return pOutConn;
}

void VarAssign::getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2)
{
	lhs = LHS;
	srhs = RHS;
}

void VarAssign::Edit(ApplicationManager* pManager)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	LHS = pIn->GetVariable(pOut);
	RHS = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
	UpdateStatementText();
}

void VarAssign::Save(ofstream& OutFile)
{
	//Assignment  ID  LeftCorner.x  LeftCorner.y  LHS  RHS
	OutFile << "VAR_ASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS << endl;
}

void VarAssign::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	UpdateStatementText();
}


//This function should be called when LHS or RHS changes
void VarAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}