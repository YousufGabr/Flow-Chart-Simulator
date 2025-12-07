#include "Statement.h"

Statement::Statement()	
{ 
	//DONE: set the ID with a unique value
	ID = NextID++;
	Text = "";
	Selected = false;		
}

int Statement::NextID = 1; //Initialize static variable

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

int Statement::GetID() const
{	return ID; }

void Statement::setID(int id)
{
	ID = id;
}
void Statement::setOutConnector(Connector* pConn)
{
	//Default implementation (for statements with no outgoing connectors)
}
Connector* Statement::getOutConnector() const
{
	//Default implementation (for statements with no outgoing connectors)
	return nullptr;
}

