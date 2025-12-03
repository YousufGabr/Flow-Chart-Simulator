#include "End.h"
#include <sstream>

using namespace std;

End::End(Point Lcorner)
{

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + 50;
	Inlet.y = LeftCorner.y;
}

void End::Draw(Output* pOut) const
{
	//Call Output::DrawEnd function to draw End statement 	
	pOut->DrawEnd(LeftCorner, 100, UI.ASSGN_HI, Selected);

}

bool End::ifclicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + 100 &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}

Point End::GetInlet() const
{
	return Inlet;
}
Point End::GetOutlet() const
{
	//End statement has no outlet
	return Point(-1, -1);
}

void End::UpdateStatementText() {}


