#ifndef VAR_ASSIGN_H
#define VAR_ASSIGN_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class VarAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (Value)

	Connector* pOutConn;
	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	VarAssign(Point Lcorner, string LeftHS = "", string RightHS = "");

	void setLHS(const string& L);
	void setRHS(const string& R);

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
	virtual void ValidateStat(ApplicationManager* pManager);
	virtual void Simulate(ApplicationManager* pManager);
};

#endif

