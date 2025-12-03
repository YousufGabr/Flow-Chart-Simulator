#pragma once
#include "Statement.h"
class End : public Statement
{
private:
	Connector* pOutConn;

	Point Inlet;	//A point where connections enters this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	End(Point Lcorner);

	virtual void Draw(Output* pOut) const;
	virtual bool ifclicked(Point P) const;
	virtual Point GetInlet() const;
	virtual Point GetOutlet() const;
};

