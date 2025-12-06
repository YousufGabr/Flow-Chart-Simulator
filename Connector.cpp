#include "Connector.h"

Connector::Connector(Statement* Src, Statement* Dst)	
//When a connector is created, it must have a source statement and a destination statement
//There are NO FREE connectors in the flowchart
{
	
	SrcStat = Src;
	DstStat = Dst;
	Selected = false;
}

void Connector::SetSelected(bool s)
{
	Selected = s;
}

bool Connector::IsSelected() const
{
	return Selected;
}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}


bool Connector::ifclicked(Point P) const
{
	//A simple implementation to check if the point P is close to the line formed by Start and End points
	//Calculate the distance from P to the line Start-End
	//If the distance is less than a threshold value, return true
	//Otherwise, return false

	// Case 1 : vertical line Downward Connector
	if (Start.y < End.y)
	{
		double A = End.y - Start.y;
		double B = Start.x - End.x;
		double C = End.x * Start.y - Start.x * End.y;
		double distance = abs(A * P.x + B * P.y + C) / sqrt(A * A + B * B);
		return distance <= 5;
	}

	// Case 2 : 3-line Connector Upward Connector
	else
	{
		// Segment 1: horizontal from Start.x,Start.y to (Start.x-100, Start.y)
		if (abs(P.y - Start.y) <= 5 &&
			P.x >= min(Start.x, Start.x - 100) &&
			P.x <= max(Start.x, Start.x - 100))
			return true;

		// Segment 2: vertical from (Start.x-100, Start.y) to (Start.x-100, End.y)
		if (abs(P.x - (Start.x - 100)) <= 5 &&
			P.y >= min(Start.y, End.y) &&
			P.y <= max(Start.y, End.y))
			return true;

		// Segment 3: horizontal from (Start.x-100, End.y) to End.x,End.y
		if (abs(P.y - End.y) <= 5 &&
			P.x >= min(Start.x - 100, End.x) &&
			P.x <= max(Start.x - 100, End.x))
			return true;

		return false;
	}
}

void Connector::Save(ofstream& OutFile) const
{
	//You should save the source and destination statement IDs to be able to reload them later
	OutFile << SrcStat->GetID() << " " << DstStat->GetID() << " 0" << endl;
}


void Connector::Draw(Output* pOut) const
{
	pOut->DrawConnector(Start, End, Selected);
	///DONE: Call Output to draw a connector from SrcStat to DstStat on the output window
}

