#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1774;
	UI.height = 950;
	UI.wx = 15;
	UI.wy =15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 80;
	UI.DrawingAreaWidth = 0.75 * UI.width;

	UI.DrawColor = BLUE;
	UI.HighlightColor = RED;
	UI.MsgColor = RED;

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");
	
	pWind->SetPen(RED,3);

	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
	ClearOutputBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateDesignToolBar() //Draws the Design Menu
{
	UI.AppMode = DESIGN;	//Design Mode
	ClearToolBar(); // clears the tool bar area first
	
	//fill the tool bar
	string MenuItemImages[DSN_ITM_CNT];
	MenuItemImages[ITM_START] = "images\\Start.jpg";        // ADD_START
	MenuItemImages[ITM_END] = "images\\End.jpg";          // ADD_END
	MenuItemImages[ITM_DECLARE] = "images\\Declare.jpg";      // ADD_DECLARE_VARIABLE
	MenuItemImages[ITM_VALUE_ASSIGN] = "images\\VALAssign.jpg";    // ADD_VALUE_ASSIGN
	MenuItemImages[ITM_VARIABLE_ASSIGN] = "images\\VARAssign.jpg";    // ADD_VAR_ASSIGN
	MenuItemImages[ITM_OPERATOR_ASSIGN] = "images\\OPAssign.jpg";     // ADD_OPER_ASSIGN
	MenuItemImages[ITM_COND] = "images\\Condition.jpg";    // ADD_CONDITION
	MenuItemImages[ITM_INPUT] = "images\\Input.jpg";        // ADD_READ
	MenuItemImages[ITM_OUTPUT] = "images\\Output.jpg";       // ADD_WRITE
	MenuItemImages[ITM_CONNECTOR] = "images\\Connector.jpg";    // ADD_CONNECTOR
	MenuItemImages[ITM_SELECT] = "images\\Select.jpg";       // SELECT
	MenuItemImages[ITM_EDIT] = "images\\Edit.jpg";         // EDIT_STAT
	MenuItemImages[ITM_DELETE] = "images\\Delete.jpg";       // DEL
	MenuItemImages[ITM_COPY] = "images\\Copy.jpg";         // COPY
	MenuItemImages[ITM_CUT] = "images\\Cut.jpg";          // CUT
	MenuItemImages[ITM_UNDO] = "images\\Undo.jpg";         // UNDO
	MenuItemImages[ITM_REDO] = "images\\Redo.jpg";         // REDO
	MenuItemImages[ITM_PASTE] = "images\\Paste.jpg";        // PASTE
	MenuItemImages[ITM_SAVE] = "images\\Save.jpg";         // SAVE
	MenuItemImages[ITM_LOAD] = "images\\Load.jpg";         // LOAD
	MenuItemImages[ITM_SWITCH_TO_SIM] = "images\\SwitchToSim.jpg";  // SWITCH_SIM_MODE
	MenuItemImages[ITM_EXIT] = "images\\Exit.jpg";         // EXIT


	//Draw menu item one image at a time
	for(int i=0; i<DSN_ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateSimulationToolBar() //Draws the Simulation Menu
{
	UI.AppMode = SIMULATION;	//Simulation Mode
	ClearToolBar(); // clears the tool bar area first
	string MenuItemImages[SIM_ITM_CNT];
	MenuItemImages[ITM_VALIDATE] = "images\\Validate.jpg";          // VALIDATE
	MenuItemImages[ITM_RUN] = "images\\Run.jpg";        // RUN
	MenuItemImages[ITM_DEBUG] = "images\\Debug.jpg";      // DEBUG
	MenuItemImages[ITM_GENERATE] = "images\\Generate.jpg";   // GENERATE_CODE
	MenuItemImages[ITM_UNDO_SIM] = "images\\Undo.jpg";         // UNDO
	MenuItemImages[ITM_REDO_SIM] = "images\\Redo.jpg";         // REDO
	MenuItemImages[ITM_SAVE_SIM] = "images\\Save.jpg";         // SAVE
	MenuItemImages[ITM_LOAD_SIM] = "images\\Load.jpg";         // LOAD
	MenuItemImages[ITM_SWITCH_TO_DES] = "images\\SwitchToDes.jpg";  // SWITCH_SIM_MODE
	MenuItemImages[ITM_EXIT_SIM] = "images\\Exit.jpg";         // EXIT

	for (int i = 0; i < SIM_ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearToolBar()
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
void Output::ClearDrawArea()
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int) (UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor,3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);
		
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x+width/8, Left.y + height/4, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawDeclare(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 8, Left.y + height / 4, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawCondition(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the Condition block Rhombus
	int px[4] = { Left.x, Left.x + width/2, Left.x + width, Left.x + width/2 };
	int py[4] = { Left.y, Left.y - height/2, Left.y, Left.y + height/2 };
	pWind->DrawPolygon(px, py, 4); // or FRAME or INVERTED

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x+width/8, Left.y-height/5, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawRead(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the Condition block Rhombus
	int px[4] = { Left.x + width / 4, Left.x + 5 * width / 4, Left.x + width, Left.x};
	int py[4] = { Left.y, Left.y, Left.y + height, Left.y + height};
	pWind->DrawPolygon(px, py, 4); // or FRAME or INVERTED

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width/4, Left.y+ height/4, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawWrite(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the Condition block Rhombus
	int px[4] = { Left.x + width / 4, Left.x + 5 * width / 4, Left.x + width, Left.x };
	int py[4] = { Left.y, Left.y, Left.y + height, Left.y + height };
	pWind->DrawPolygon(px, py, 4); // or FRAME or INVERTED

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawStart(Point Left, int width, int height, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the Start block Ellipse
	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height);

	//Write Start text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 3, Left.y + height / 4, "Start");
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawEnd(Point Left, int width, int height, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the End block Ellipse
	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height);

	//Write End text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 3, Left.y + height / 4, "End");
}
//////////////////////////////////////////////////////////////////////////////////////////	
void Output::DrawConnector(Point start, Point end, bool Selected)
{
	// Line color
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	if (end.y < start.y)
	{
		pWind->DrawLine(start.x, start.y, start.x - 50, start.y);
		pWind->DrawLine(start.x - 50, start.y, start.x - 50, end.y);
		pWind->DrawLine(start.x - 50, end.y, end.x, end.y);
		pWind->DrawTriangle(end.x, end.y + 5, end.x, end.y -5, end.x + 10 , end.y);
		return;
	}
	pWind->DrawLine(start.x, start.y, end.x, end.y);
	pWind->DrawTriangle(end.x + 5,end.y , end.x -5 , end.y , end.x , end.y + 10);
}
//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}
