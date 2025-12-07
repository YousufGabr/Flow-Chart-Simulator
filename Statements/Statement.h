#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "..\Connector.h"
#include "..\ApplicationManager.h"
//class Output;
#include "..\GUI\Output.h"
class ApplicationManager;

//Base class for all Statements
class Statement
{
protected:
	int ID;			//Each Statement has an ID --> must be unique
	static int NextID; //Static variable to assign unique IDs to each statement
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart


	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

	/// Add more parameters if needed.

public:
	Statement();
	void SetSelected(bool s);
	bool IsSelected() const;
	int GetID() const;
	void setID(int id);

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	virtual bool ifclicked(Point P) const = 0; //check if the statement is clicked
	virtual Point GetInlet() const = 0;	//returns the inlet point of the statement
	virtual Point GetOutlet() const = 0;	//returns the outlet point of the statement
	virtual void getdata(string& lhs, string& op, string& srhs, double& drhs, string& srhs2)=0; //get the statement data from the user
	

	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type

	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &InFile) = 0;	//Load the Statement parameters from a file

	virtual void Edit(ApplicationManager* pManager) = 0;		//Edit the Statement parameter

	//virtual void Simulate();	//Execute the statement in the simulation mode

	//[BONUS] virtual void GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file


	///TODO: Add more functions if needed

};

#endif