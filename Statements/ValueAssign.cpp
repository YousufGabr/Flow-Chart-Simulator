#include "ValueAssign.h"
#include <sstream>

using namespace std;

ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;
	
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
}

void ValueAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
	
}

bool ValueAssign::ifclicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}

Point ValueAssign::GetInlet() const
{
	return Inlet;
}
Point ValueAssign::GetOutlet() const
{
	return Outlet;
}
void ValueAssign::setOutConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* ValueAssign::getOutConnector() const
{
	return pOutConn;
}

void ValueAssign::getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2)
{
	lhs = LHS;
	drhs = RHS;
}

void ValueAssign::Edit(ApplicationManager* pManager)
{
	//Get a pointer to the Input / Output interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//Read the new LHS and RHS
	LHS = pIn->GetVariable(pOut);
	RHS = pIn->GetValue(pOut);
	pOut->ClearStatusBar();
	UpdateStatementText();
}

void ValueAssign::Save(ofstream& OutFile)
{
	//StatementType  ID  LHS  RHS  LeftCorner.x  LeftCorner.y
	OutFile << "VAL_ASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS << endl;
}

void ValueAssign::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	UpdateStatementText();
}


//This function should be called when LHS or RHS changes
void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<LHS<<" = "<<RHS;	
	Text = T.str();	 
}