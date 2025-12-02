#pragma once
#include "Statement.h"
class Read : public Statement
{
private:
	string Variable;	//Variable to be written

	Connector* pOutConn;
	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Read(Point Lcorner, string Var = "");

	void setVar(const string& L);

	virtual void Draw(Output* pOut) const;
	virtual bool ifclicked(Point P) const;
};

