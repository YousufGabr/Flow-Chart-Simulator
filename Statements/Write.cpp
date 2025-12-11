#include "Write.h"
#include <sstream>

using namespace std;

Write::Write(Point Lcorner, string Var)
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
int Write::yaxis = 70;

void Write::setVar(const string& V)
{
	Variable = V;
	UpdateStatementText();
}

void Write::resetyaxis()
{
	yaxis = 70;
}


void Write::Draw(Output* pOut) const
{
	//Call Output::DrawWrite function to draw Write statement 	
	pOut->DrawWrite(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

bool Write::ifclicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + 5 * UI.ASSGN_WDTH /4 &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}

Point Write::GetInlet() const
{
	return Inlet;
}
Point Write::GetOutlet() const
{
	return Outlet;
}
void Write::setOutConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* Write::getOutConnector() const
{
	return pOutConn;
}

void Write::getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2)
{
	srhs = Variable;
}

void Write::Edit(ApplicationManager* pManager)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Variable = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
	UpdateStatementText();
}

void Write::Save(ofstream& OutFile)
{
	OutFile << "WRITE "<< ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << Variable << endl;
}

void Write:: Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> Variable;
	
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	UpdateStatementText();
}

void Write::ValidateStat(ApplicationManager* pManager)
{
	Output* pOut = pManager->GetOutput();
	if (pManager->findVariable(Variable) == -1)
	{
		pOut->PrintMessage("Error: Variable (" + Variable + ") Not Declared");
		pManager->setvalid(false);
		return;
	}
}

void Write::Simulate(ApplicationManager* pManager)
{
	Output* pOut = pManager->GetOutput();
	pOut->DrawString(UI.DrawingAreaWidth + 20, yaxis, Variable + "=" + doubleToString(pManager->getVarValue(Variable)));
	yaxis += 20;
}


//This function should be called when Variable changes
void Write::UpdateStatementText()
{
	ostringstream T;
	T << "Write " << Variable;
	Text = T.str();
}
