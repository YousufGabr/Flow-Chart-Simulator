#include "OpAssign.h"
#include <sstream>

using namespace std;

OpAssign::OpAssign(Point Lcorner, string LeftHS, string RightHS1, string Operator, string RightHS2)
{
	// Note: The LeftHS and RightHS should be validated inside (AddVarAssign) action
	//       before passing it to the constructor of VarAssign
	LHS = LeftHS;
	RHS1 = RightHS1;
	Op = Operator;
	RHS2 = RightHS2;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void OpAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void OpAssign::setRHS(const string& R)
{
	RHS1 = R;
	UpdateStatementText();
}


void OpAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

bool OpAssign::ifclicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}

Point OpAssign::GetInlet() const
{
	return Inlet;
}
Point OpAssign::GetOutlet() const
{
	return Outlet;
}
void OpAssign::setOutConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* OpAssign::getOutConnector() const
{
	return pOutConn;
}

void OpAssign::getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2)
{
	lhs = LHS;
	srhs = RHS1;
	op = Op;
	srhs2 = RHS2;
}

void OpAssign::Edit(ApplicationManager* pManager)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	LHS = pIn->GetVariable(pOut);
	pOut->PrintMessage("Enter First Right Hand Side value:");
	do{
		RHS1 = pIn->GetString(pOut);
		if (ValueOrVariable(RHS1) != INVALID_OP) break;
		pOut->PrintMessage("Invalid Input, Try Again");
	} while (true);

	Op = pIn->GetArithOperator(pOut);

	pOut->PrintMessage("Enter Second Right Hand Side value:");
	do {
		RHS2 = pIn->GetString(pOut);
		if (ValueOrVariable(RHS2) != INVALID_OP) break;
		pOut->PrintMessage("Invalid Input, Try Again");
	} while (true);
	
	pOut->ClearStatusBar();
	UpdateStatementText();
}

void OpAssign::Save(ofstream& OutFile)
{
	//Assignment  ID  LeftCorner.x  LeftCorner.y  LHS  RHS
	OutFile << "OP_ASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS1 << " " << Op << " " << RHS2 << endl;
}

void OpAssign::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS1 >> Op >> RHS2;
	Outlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	Inlet.x = Outlet.x;
	Inlet.y = LeftCorner.y;
	UpdateStatementText();
}

void OpAssign::ValidateStat(ApplicationManager* pManager)
{
	if (!pManager->getvalid()) return;
	Output* pOut = pManager->GetOutput();
	if (pManager->findVariable(LHS) == -1)
	{
		pOut->PrintMessage("Error: Variable (" + LHS + ") Not Declared");
		pManager->setvalid(false);
		return;
	}
	if (IsVariable(RHS1) && pManager->findVariable(RHS1) == -1)
	{
		pOut->PrintMessage("Error: Variable (" + RHS1 + ") Not Declared");
		pManager->setvalid(false);
		return;
	}
	if (IsVariable(RHS2) && pManager->findVariable(RHS2) == -1)
	{
		pOut->PrintMessage("Error: Variable (" + RHS2 + ") Not Declared");
		pManager->setvalid(false);
		return;
	}
	if (Op=="/" && RHS2 == "0")
	{
		pOut->PrintMessage("Error: Cannot Divide By 0");
		pManager->setvalid(false);
		return;
	}
	pOutConn->getDstStat()->ValidateStat(pManager);
}

void OpAssign::Simulate(ApplicationManager* pManager)
{
	double result = 0;
	if (IsValue(RHS1) && IsValue(RHS2))
	{
		if (Op == "+") result = stod(RHS1) + stod(RHS2);
		if (Op == "-") result = stod(RHS1) - stod(RHS2);
		if (Op == "*") result = stod(RHS1) * stod(RHS2);
		if (Op == "/") result = stod(RHS1) / stod(RHS2);
	}
	else if (IsValue(RHS1) && IsVariable(RHS2))
	{
		if (Op == "+") result = stod(RHS1) + pManager->getVarValue(RHS2);
		if (Op == "-") result = stod(RHS1) - pManager->getVarValue(RHS2);
		if (Op == "*") result = stod(RHS1) * pManager->getVarValue(RHS2);
		if (Op == "/") result = stod(RHS1) / pManager->getVarValue(RHS2);
	}
	else if (IsVariable(RHS1) && IsValue(RHS2))
	{
		if (Op == "+") result = pManager->getVarValue(RHS1) + stod(RHS2);
		if (Op == "-") result = pManager->getVarValue(RHS1) - stod(RHS2);
		if (Op == "*") result = pManager->getVarValue(RHS1) * stod(RHS2);
		if (Op == "/") result = pManager->getVarValue(RHS1) / stod(RHS2);
	}
	else if (IsVariable(RHS1) && IsVariable(RHS2))
	{
		if (Op == "+") result = pManager->getVarValue(RHS1) + pManager->getVarValue(RHS2);
		if (Op == "-") result = pManager->getVarValue(RHS1) - pManager->getVarValue(RHS2);
		if (Op == "*") result = pManager->getVarValue(RHS1) * pManager->getVarValue(RHS2);
		if (Op == "/") result = pManager->getVarValue(RHS1) / pManager->getVarValue(RHS2);
	}
	pManager->setVariable(LHS, result);
}


//This function should be called when LHS or RHS changes
void OpAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS1 << Op << RHS2;
	Text = T.str();
}
