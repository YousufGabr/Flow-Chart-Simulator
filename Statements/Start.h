#pragma once
#include "Statement.h"
class Start : public Statement
{
private:
	static bool exists;
	Connector* pOutConn;
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Start(Point Lcorner);
	static void setExists(bool ex);
	static  bool getExists();

	virtual void Draw(Output* pOut) const;
	virtual bool ifclicked(Point P) const;
	virtual Point GetInlet() const;
	virtual Point GetOutlet() const;
	void setOutConnector(Connector* pConn) override;
	Connector* getOutConnector() const override;
	virtual void getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2);
	virtual void Edit(ApplicationManager* pManager);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
};

