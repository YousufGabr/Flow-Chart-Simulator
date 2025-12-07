#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "GUI\UI_Info.h"
#include "GUI\output.h"
#include "Statements\Statement.h"
#include <fstream>
class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	bool Selected; //true if the connector is selected
	int con_id; //connector ID
public:
	Connector(Statement* Src, Statement* Dst);

	void SetSelected(bool s);
	bool IsSelected() const;
	void setID(int id);
	int getID() const;

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();
	bool ifclicked(Point P) const; //check if the connector is clicked
	void Save(ofstream& OutFile) const;	//Save the Connector parameters to a file

	void Draw(Output* pOut) const;
	

};

#endif