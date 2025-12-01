#include "Statement.h"

Statement::Statement()	
{ 
	//DONE: set the ID with a unique value
	ID = NextID++;
	Text = "";
	Selected = false;		
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

