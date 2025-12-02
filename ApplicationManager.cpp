#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "Actions\AddVarAssign.h"
#include "Actions\AddOpAssign.h"
#include "Actions\AddDeclare.h"
#include "Actions\AddCondition.h"
#include "Actions\AddStart.h"
#include "Actions\AddEnd.h"
#include "Actions\AddRead.h"
#include "Actions\AddWrite.h"
#include "Actions\Select.h"
#include "GUI\Input.h"
#include "GUI\Output.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pClipboard = NULL;
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//


ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
			// --- ADD STATEMENTS ---
		case ADD_START:
			pOut->PrintMessage("Action: add START statement, Click anywhere");
			break;

		case ADD_END:
			pOut->PrintMessage("Action: add END statement, Click anywhere");
			break;

		case ADD_DECLARE_VARIABLE:
			pOut->PrintMessage("Action: add DECLARE VARIABLE statement, Click anywhere");
			break;

		case ADD_VALUE_ASSIGN:
			pAct = new AddValueAssign(this);
			break;

		case ADD_VAR_ASSIGN:
			pAct = new AddVarAssign(this);
			break;

		case ADD_OPER_ASSIGN:
			pOut->PrintMessage("Action: add OPERATOR ASSIGNMENT statement, Click anywhere");
			break;

		case ADD_CONDITION:
			pOut->PrintMessage("Action: add CONDITIONAL statement (IF / WHILE), Click anywhere");
			break;

		case ADD_READ:
			pOut->PrintMessage("Action: add READ (input) statement, Click anywhere");
			break;

		case ADD_WRITE:
			pOut->PrintMessage("Action: add WRITE (output) statement, Click anywhere");
			break;

		case ADD_CONNECTOR:
			pOut->PrintMessage("Action: add CONNECTOR, Click on source then destination");
			break;


			// --- EDITING / MANIPULATION ---
		case SELECT:
			pAct = new Select(this);
			break;

		case EDIT_STAT:
			pOut->PrintMessage("Action: EDIT selected statement, Click anywhere");
			break;

		case DEL:
			pOut->PrintMessage("Action: DELETE selected figure");
			break;

		case COPY:
			pOut->PrintMessage("Action: COPY selected figure");
			break;

		case CUT:
			pOut->PrintMessage("Action: CUT selected figure");
			break;

		case PASTE:
			pOut->PrintMessage("Action: PASTE copied/cut figure, Click anywhere");
			break;

			// --- UNDO / REDO ---
		case UNDO:
			pOut->PrintMessage("Action: UNDO last action");
			break;

		case REDO:
			pOut->PrintMessage("Action: REDO last undone action");
			break;

			// --- FILE OPERATIONS ---
		case SAVE:
			pOut->PrintMessage("Action: SAVE graph to file");
			break;

		case LOAD:
			pOut->PrintMessage("Action: LOAD graph from file");
			break;


			// --- MODE SWITCHING ---
		case SWITCH_SIM_MODE:
			pOut->PrintMessage("Action: Switch to SIMULATION Mode, creating Simulation Tool Bar");
			pOut->CreateSimulationToolBar();
			break;

		case SWITCH_DSN_MODE:
			pOut->PrintMessage("Action: Switch to DESIGN Mode, creating Design Tool Bar");
			pOut->CreateDesignToolBar();
			break;


			// --- CLICK AREAS ---
		case DRAWING_AREA:
			pOut->PrintMessage("Action: Click on the DRAWING area");
			break;

		case OUTPUT_AREA:
			pOut->PrintMessage("Action: Click on the OUTPUT area");
			break;

		case DSN_TOOL:
			pOut->PrintMessage("Action: Click on the DESIGN Tool Bar");
			break;

		case STATUS:
			pOut->PrintMessage("Action: Click on the STATUS Bar");
			break;

			// --- SIMULATION ACTIONS ---
		case VALIDATE:
			pOut->PrintMessage("Action: VALIDATE the flowchart");
			break;

		case RUN:
			pOut->PrintMessage("Action: RUN the flowchart");
			break;

		case DEBUG:
			pOut->PrintMessage("Action: DEBUG the flowchart");
			break;

		case GENERATE:
			pOut->PrintMessage("Action: GENERATE the flowchart code");
			break;

		case SIM_TOOL:
			pOut->PrintMessage("Action: Click on the SIMULATION Tool Bar");
			break;

		case EXIT:
			///create Exit Action here
			
			break;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//


//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL
	for (int i = 0; i < StatCount; i++) {
		if (StatList[i]->ifclicked(P))
			return StatList[i];
	}
	return NULL;

	///Add your code here to search for a statement given a point P(x,y)	
	///WITHOUT breaking class responsibilities

	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	pSelectedStat = pStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement *ApplicationManager::GetClipboard() const
{	return pClipboard;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement *pStat)
{	pClipboard = pStat;	}


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//


//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw(pOut);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<ConnCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	
}
