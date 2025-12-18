#pragma once
#include "Statement.h"
class Condition : public Statement
{
private:
	bool condcheck, visited;
	string LHS;	//Left Handside of the assignment (name of a variable)
	string Op;    //Operator
	string RHS;  //Second Right Handside (Value)

	Connector* TOutConn;
	Connector* FOutConn;
	Point Inlet;	//A point where connections enters this statement 
	Point TOutlet;	//A point a connection leaves this statement
	Point FOutlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Condition(Point Lcorner, string LeftHS = "", string Opertator = "", string RightHS = "");

	void setLHS(const string& L);
	void setRHS(const string& R);
	void setcondcheck(bool c);
	bool getcondcheck();
	void setvisited(bool c);
	bool getvisited();

	virtual void Draw(Output* pOut) const;
	virtual bool ifclicked(Point P) const;
	virtual Point GetInlet() const;
	virtual Point GetOutlet() const;
	virtual Point GetTOutlet() const;
	virtual Point GetFOutlet() const;
	void setTOutConn(Connector* pConn);
	void setFOutConn(Connector* pConn);
	Connector* getTOutConn() const;
	Connector* getFOutConn() const;
	virtual void getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2);
	virtual void Edit(ApplicationManager* pManager);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void ValidateStat(ApplicationManager* pManager);
	virtual void Simulate(ApplicationManager* pManager);
};

