
#include "Input.h"
#include "Output.h"
#include <string>

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

string Input::GetString(Output *pO) const 
{
	string Label;
	char Key;
	while(true)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			break;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.pop_back();	
		//else if (Key < 32 || Key > 126 || ((Key == 8) && (Label.size() == 0))) continue; //Skip invalid ASCII key (currently not quite working)
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
	return Label;
}


double Input::GetValue(Output* pO) const
{
	pO->PrintMessage("Please enter a value");
	string StringVal; // string type then convert to double

	do {
		StringVal = GetString(pO);
		if (IsValue(StringVal)) return stod(StringVal);
		pO->PrintMessage("invalid Double, try again:");
	} while (true);
}

string Input::GetVariable(Output* pO) const
{
	pO->PrintMessage("Please enter a variable name");
	string VarName;

	do{
		VarName = GetString(pO);
		if (IsVariable(VarName)) return VarName;
		pO->PrintMessage("invalid Variable Name, try again:");
	} while (true);
	
}

string Input::GetArithOperator(Output* pO) const
{
	pO->PrintMessage("Enter an arithmetic operator (+, -, *, /):");
	string Op = "";

	do {
		Op = GetString(pO);
		if (Op == "+" || Op == "-" || Op == "*" || Op == "/") return Op;
		pO->PrintMessage("Invalid Operator, try again:");
	} while (true);
}

string Input::GetCompOperator(Output* pO) const
{
	pO->PrintMessage("Enter a comparison operator (==, !=, <, <=, >, >=):");
	string Op;

	do {
		Op = GetString(pO);
		if (Op == "==" || Op == "!=" || Op == "<" || Op == "<=" || Op == ">" || Op == ">=") return Op;
		pO->PrintMessage("Invalid Operator, try again:");
	} while (true);
}


ActionType Input::GetUserAction() const
{	
	//This function reads the position where the user clicks to determine the desired action

	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//This assumes that menu items are lined up horizontally
			int ClickedItem = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItem)
			{
			case ITM_START:            return ADD_START;
			case ITM_END:              return ADD_END;
			case ITM_DECLARE:          return ADD_DECLARE_VARIABLE;
			case ITM_VALUE_ASSIGN:     return ADD_VALUE_ASSIGN;
			case ITM_VARIABLE_ASSIGN:  return ADD_VAR_ASSIGN;
			case ITM_OPERATOR_ASSIGN:  return ADD_OPER_ASSIGN;
			case ITM_COND:             return ADD_CONDITION;
			case ITM_INPUT:            return ADD_READ;
			case ITM_OUTPUT:           return ADD_WRITE;
			case ITM_CONNECTOR:        return ADD_CONNECTOR;
			case ITM_SELECT:           return SELECT;
			case ITM_EDIT:             return EDIT_STAT;
			case ITM_DELETE:           return DEL;
			case ITM_COPY:             return COPY;
			case ITM_CUT:              return CUT;
			case ITM_PASTE:            return PASTE;
			case ITM_UNDO:             return UNDO;
			case ITM_REDO:             return REDO;
			case ITM_SAVE:             return SAVE;
			case ITM_LOAD:             return LOAD;
			case ITM_SWITCH_TO_SIM:    return SWITCH_SIM_MODE;
			case ITM_EXIT:             return EXIT;
			default:                   return DSN_TOOL;
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;	
			else
				return OUTPUT_AREA;
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//Application is in Simulation mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//This assumes that menu items are lined up horizontally
			int ClickedItem = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItem)
			{
			case ITM_VALIDATE:              return VALIDATE;
			case ITM_RUN:            return RUN;
			case ITM_DEBUG:          return DEBUG;
			case ITM_GENERATE:      return GENERATE;
			case ITM_UNDO_SIM:             return UNDO;
			case ITM_REDO_SIM:             return REDO;
			case ITM_SAVE_SIM:             return SAVE;
			case ITM_LOAD_SIM:             return LOAD;
			case ITM_SWITCH_TO_DES:    return SWITCH_DSN_MODE;
			case ITM_EXIT_SIM:             return EXIT;
			default:                   return SIM_TOOL;
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;
			else
				return OUTPUT_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}

}


Input::~Input()
{
}
