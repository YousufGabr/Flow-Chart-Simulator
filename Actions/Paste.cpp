#include "Paste.h"
#include "..\ApplicationManager.h"
#include "..\Statements\ValueAssign.h"
#include "..\Statements\VarAssign.h"
#include "..\Statements\Start.h"
#include "..\Statements\End.h"
#include "..\Statements\Read.h"
#include "..\Statements\Write.h"
#include "..\Statements\Declare.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

Paste::Paste(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Paste::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	copiedstat = pManager->GetClipboard();
	if (copiedstat == NULL) return;

	cut = pManager->getIscut();
	pOut->PrintMessage("Click to Paste the Copied Statement");
	pIn->GetPointClicked(p);
	copiedstat->getdata(LHS, OP, SRHS, DRHS);
	

}

void Paste::Execute() {

	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (copiedstat == NULL)
	{
		pOut->PrintMessage("No Copied/Cut Statement to Paste");
		return;
	}
	if (dynamic_cast <ValueAssign*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - UI.ASSGN_WDTH / 2;
		Corner.y = p.y;
		newstat = new ValueAssign(Corner, LHS, DRHS);
	}
	else if (dynamic_cast <VarAssign*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - UI.ASSGN_WDTH / 2;
		Corner.y = p.y;
		newstat = new VarAssign(Corner, LHS, SRHS);
		
	}
	else if (dynamic_cast <Start*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - 50;
		Corner.y = p.y;
		newstat = new Start(Corner);
	}
	else if (dynamic_cast <End*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - 50;
		Corner.y = p.y;
		newstat = new End(Corner);
	}
	else if (dynamic_cast <Read*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - UI.ASSGN_WDTH / 2;
		Corner.y = p.y;
		newstat = new Read(Corner, SRHS);
	}
	else if (dynamic_cast <Write*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - UI.ASSGN_WDTH / 2;
		Corner.y = p.y;
		newstat = new Write(Corner, SRHS);
	}
	else if (dynamic_cast <Declare*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - UI.ASSGN_WDTH / 2;
		Corner.y = p.y;
		newstat = new Declare(Corner, SRHS);
	}
	
	if (cut) {
		pManager->SetSelectedStatement(NULL);
		pManager->setIscut(false);
		delete copiedstat;
		pManager->SetClipboard(newstat);
	}
	pOut->PrintMessage("Statement Pasted Successfully");
	pManager->AddStatement(newstat); // Adds the created statement to application manger's statement list
}