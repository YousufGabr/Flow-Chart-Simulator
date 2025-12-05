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
#include "Actions\AddConnect.h"
#include "Actions\Select.h"
#include "Actions\Edit.h"
#include "Actions\Delete.h"
#include "Actions\Copy.h"
#include "Actions\Cut.h"
#include "Actions\Paste.h"
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
	iscut = false;
	pSelectedStat = NULL;	//no Statement is selected yet
	pSelectedConn = NULL;	//no Connector is selected yet
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
			pAct = new AddStart(this);
			break;

		case ADD_END:
			pAct = new AddEnd(this);
			break;

		case ADD_DECLARE_VARIABLE:
			pAct = new AddDeclare(this);
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
			pAct = new AddRead(this);
			break;

		case ADD_WRITE:
			pAct = new AddWrite(this);
			break;

		case ADD_CONNECTOR:
			pAct = new AddConnect(this);
			break;


			// --- EDITING / MANIPULATION ---
		case SELECT:
			pAct = new Select(this);
			break;

		case EDIT_STAT:
			pAct = new Edit(this);
			break;

		case DEL:
			pAct = new Delete(this);
			break;

		case COPY:
			pAct = new Copy(this);
			break;

		case CUT:
			pAct = new Cut(this);
			break;

		case PASTE:
			pAct = new Paste(this);
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

void ApplicationManager::RemoveStatement(Statement* pStat)
{
	//Find and remove the statement from the list
	for (int i = 0; i < StatCount; i++) {
		if (StatList[i] == pStat) {
			//Shift the remaining statements to fill the gap
			for (int j = i; j < StatCount - 1; j++) {
				StatList[j] = StatList[j + 1];
			}
			StatList[StatCount - 1] = NULL; // Optional: Clear the last pointer
			StatCount--;
			//delete corresponding connectors if any
			for (int k = 0; k < ConnCount; k++) {
				if (ConnList[k]->getSrcStat() == pStat || ConnList[k]->getDstStat() == pStat) {
					RemoveConnector(ConnList[k]);
					k--; // Adjust index after removal
				}
			}
			return;
		}
	}
}

bool ApplicationManager::getIscut() const
{
	return iscut;
}
void ApplicationManager::setIscut(bool c)
{
	iscut = c;
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
//						Connectors Management Functions								//
//==================================================================================//


//Add a statement to the list of Connectors
void ApplicationManager::AddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;

}

void ApplicationManager::RemoveConnector(Connector* pConn)
{
	//Find and remove the connector from the list
	for (int i = 0; i < ConnCount; i++) {
		if (ConnList[i] == pConn) {
			//Shift the remaining connectors to fill the gap
			for (int j = i; j < ConnCount - 1; j++) {
				ConnList[j] = ConnList[j + 1];
			}
			ConnList[ConnCount - 1] = NULL; // Optional: Clear the last pointer
			ConnCount--;
			delete pConn; // Free the memory allocated for the connector
			return;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
Connector* ApplicationManager::GetConnector(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL
	for (int i = 0; i < ConnCount; i++) {
		if (ConnList[i]->ifclicked(P))
			return ConnList[i];
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected Connector
Connector* ApplicationManager::GetSelectedConnector() const
{
	return pSelectedConn;
}
////////////////////////////////////////////////////////////////////////////////////
//Set the Connector selected by the user
void ApplicationManager::SetSelectedConnector(Connector* pCon)
{
	pSelectedConn = pCon;
}


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
	if (iscut && pClipboard != NULL) delete pClipboard;
	delete pIn;
	delete pOut;
	
}
