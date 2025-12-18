#include "End.h"
#include <sstream>

using namespace std;

End::End(Point Lcorner)
{
	exists = true;
	LeftCorner = Lcorner;

	Inlet.x = LeftCorner.x + 50;
	Inlet.y = LeftCorner.y;
}
bool End::exists = false;
void End::setExists(bool ex)
{
	//Set the static variable exists to ex
	exists = ex;
}
bool End::getExists()
{
	//Return the static variable exists
	return exists;
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

void End::getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2)
{
	//End statement has no data
}

void End::Edit(ApplicationManager* pManager)
{
	//End statement has no editable data
}

void End::Save(ofstream& OutFile)
{
	OutFile << "END " << ID << " " << LeftCorner.x << " " << LeftCorner.y << endl;
}

void End::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y;
	Inlet.x = LeftCorner.x + 50;
	Inlet.y = LeftCorner.y;
}

void End::ValidateStat(ApplicationManager* pManager)
{
	if (!pManager->getvalid()) return;
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("FlowChart is Valid!");
	pManager->setvalid(true);
}

void End::Simulate(ApplicationManager* pManager)
{
}

void End::UpdateStatementText() {}


