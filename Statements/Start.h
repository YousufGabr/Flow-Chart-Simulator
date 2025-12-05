#pragma once
#include "Statement.h"
class Start : public Statement
{
private:
	Connector* pOutConn;
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Start(Point Lcorner);

	virtual void Draw(Output* pOut) const;
	virtual bool ifclicked(Point P) const;
	virtual Point GetInlet() const;
	virtual Point GetOutlet() const;
	virtual void getdata(string& lhs, string& op, string& srhs, double& drhs);
};

