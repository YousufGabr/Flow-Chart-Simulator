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


//This function should be called when Variable changes
void Declare::UpdateStatementText()
{
	ostringstream T;
	T << "Double " << Variable;
	Text = T.str();
}

