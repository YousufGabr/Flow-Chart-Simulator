#include "Condition.h"
#include <sstream>

using namespace std;

Condition::Condition(Point Lcorner, string LeftHS, string Operator, string RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddVarAssign) action
	//       before passing it to the constructor of VarAssign
	LHS = LeftHS;
	RHS = RightHS;
	Op = Operator;

	UpdateStatementText();

	LeftCorner = Lcorner;

	TOutConn = NULL;	//No connectors yet
	FOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y - UI.ASSGN_HI/2;

	TOutlet = LeftCorner;
	FOutlet.x = TOutlet.x + UI.ASSGN_WDTH;
	FOutlet.y = TOutlet.y;
}

void Condition::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void Condition::setRHS(const string& R)
{
	RHS = R;
	UpdateStatementText();
}


void Condition::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawCondition(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

bool Condition::ifclicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y - UI.ASSGN_HI/2 && P.y <= LeftCorner.y + UI.ASSGN_HI /2)
		return true;
	else
		return false;
}

Point Condition::GetInlet() const
{
	return Inlet;
}
Point Condition::GetOutlet() const
{
	//Condition statement has two outlets
	return Point(-1, -1);
}
Point Condition::GetTOutlet() const
{
	return TOutlet;
}
Point Condition::GetFOutlet() const
{
	return FOutlet;
}
void Condition::setTOutConn(Connector* pConn)
{
	TOutConn = pConn;
}
void Condition::setFOutConn(Connector* pConn)
{
	FOutConn = pConn;
}
Connector* Condition::getTOutConn() const
{
	return TOutConn;
}
Connector* Condition::getFOutConn() const
{
	return FOutConn;
}

void Condition::getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2)
{
	lhs = LHS;
	srhs = RHS;
	op = Op;
}

void Condition::Edit(ApplicationManager* pManager)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	LHS = pIn->GetVariable(pOut);
	Op = pIn->GetCompOperator(pOut);

	pOut->PrintMessage("Enter Right Hand Side value:");
	do {
		RHS = pIn->GetString(pOut);
		if (ValueOrVariable(RHS) != INVALID_OP) break;
		pOut->PrintMessage("Invalid Input, Try Again");
	} while (true);

	pOut->ClearStatusBar();
	UpdateStatementText();
}

void Condition::Save(ofstream& OutFile)
{
	//Assignment  ID  LeftCorner.x  LeftCorner.y  LHS  RHS
	OutFile << "CONDITION " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << Op << " " << RHS << endl;
}

void Condition::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> Op >> RHS;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y - UI.ASSGN_HI / 2;
	TOutlet = LeftCorner;
	FOutlet.x = TOutlet.x + UI.ASSGN_WDTH;
	FOutlet.y = TOutlet.y;
	UpdateStatementText();
}


//This function should be called when LHS or RHS changes
void Condition::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << Op << RHS;
	Text = T.str();
}

