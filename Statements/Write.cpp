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

void Write::setVar(const string& V)
{
	Variable = V;
	UpdateStatementText();
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


//This function should be called when Variable changes
void Write::UpdateStatementText()
{
	ostringstream T;
	T << "Write " << Variable;
	Text = T.str();
}
