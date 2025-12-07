#pragma once
#include "Statement.h"
class Write : public Statement
{

private:
	string Variable;	//Variable to be written

	Connector* pOutConn;
	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Write(Point Lcorner, string Var="");

	void setVar(const string& L);

	virtual void Draw(Output* pOut) const;
	virtual bool ifclicked(Point P) const;
	virtual Point GetInlet() const;
	virtual Point GetOutlet() const;
	void setOutConnector(Connector* pConn) override; //sets the outgoing connector of the statement
	Connector* getOutConnector() const override; //returns the outgoing connector of the statement 
	virtual void getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2);
	virtual void Edit(ApplicationManager* pManager);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);

};

