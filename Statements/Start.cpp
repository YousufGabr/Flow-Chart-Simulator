#include "Start.h"
#include <sstream>

using namespace std;

Start::Start(Point Lcorner)
{
	exists = true;
	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Outlet.x = LeftCorner.x + 50;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}
bool Start::exists = false;
void Start::setExists(bool ex)
{
	//Set the static variable exists to ex
	exists = ex;
}
bool Start::getExists()
{
	//Return the static variable exists
	return exists;
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
void Start::setOutConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* Start::getOutConnector() const
{
	return pOutConn;
}

void Start::getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2)
{
	//Start statement has no data
}

void Start::Edit(ApplicationManager* pManager)
{
	//Start statement has no editable data
}

void Start::Save(ofstream& OutFile)
{
	OutFile << "START " << ID << " " << LeftCorner.x << " " << LeftCorner.y << endl;
}

void Start::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y;
	Outlet.x = LeftCorner.x + 50;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void Start::ValidateStat(ApplicationManager* pManager)
{
}

void Start::Simulate(ApplicationManager* pManager)
{
}

void Start::UpdateStatementText() {}

