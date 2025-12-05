#include "Start.h"
#include <sstream>

using namespace std;

Start::Start(Point Lcorner)
{

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Outlet.x = LeftCorner.x + 50;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void Start::Draw(Output* pOut) const
{
	//Call Output::DrawStart function to draw Start statement 	
	pOut->DrawStart(LeftCorner, 100, UI.ASSGN_HI,Selected);

}

bool Start::ifclicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + 100 &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}

Point Start::GetInlet() const
{
	//Start statement has no inlet
	return Point(-1, -1);
}
Point Start::GetOutlet() const
{
	return Outlet;
}

void Start::getdata(string& lhs, string& op, string& srhs, double& drhs)
{
	//Start statement has no data
}

void Start::Edit(ApplicationManager* pManager)
{
	//Start statement has no editable data
}

void Start::UpdateStatementText() {}

