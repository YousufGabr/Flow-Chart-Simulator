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
		ValueAssign* pAssign = new ValueAssign(Corner, LHS, DRHS);
		if (cut) {
			pManager->setIscut(false);
			delete copiedstat;
			pManager->SetClipboard(pAssign);
		}
		pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
	}
	else if (dynamic_cast <VarAssign*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - UI.ASSGN_WDTH / 2;
		Corner.y = p.y;
		VarAssign* pAssign = new VarAssign(Corner, LHS, SRHS);
		if (cut) {
			pManager->setIscut(false);
			delete copiedstat;
			pManager->SetClipboard(pAssign);
		}
		pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
	}
	else if (dynamic_cast <Start*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - 50;
		Corner.y = p.y;
		Start* pStart = new Start(Corner);
		if (cut) {
			pManager->setIscut(false);
			delete copiedstat;
			pManager->SetClipboard(pStart);
		}
		pManager->AddStatement(pStart); // Adds the created statement to application manger's statement list
	}
	else if (dynamic_cast <End*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - 50;
		Corner.y = p.y;
		End* pEnd = new End(Corner);
		if (cut) {
			pManager->setIscut(false);
			delete copiedstat;
			pManager->SetClipboard(pEnd);
		}
		pManager->AddStatement(pEnd); // Adds the created statement to application manger's statement list
	}
	else if (dynamic_cast <Read*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - UI.ASSGN_WDTH / 2;
		Corner.y = p.y;
		Read* pRead = new Read(Corner, SRHS);
		if (cut) {
			pManager->setIscut(false);
			delete copiedstat;
			pManager->SetClipboard(pRead);
		}
		pManager->AddStatement(pRead); // Adds the created statement to application manger's statement list
	}
	else if (dynamic_cast <Write*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - UI.ASSGN_WDTH / 2;
		Corner.y = p.y;
		Write* pWrite = new Write(Corner, SRHS);
		if (cut) {
			pManager->setIscut(false);
			delete copiedstat;
			pManager->SetClipboard(pWrite);
		}
		pManager->AddStatement(pWrite); // Adds the created statement to application manger's statement list
	}
	else if (dynamic_cast <Declare*>(copiedstat)) {
		//Calculating left corner of assignement statement block
		Corner.x = p.x - UI.ASSGN_WDTH / 2;
		Corner.y = p.y;
		Declare* pDeclare = new Declare(Corner, SRHS);
		if (cut) {
			pManager->setIscut(false);
			delete copiedstat;
			pManager->SetClipboard(pDeclare);
		}
		pManager->AddStatement(pDeclare); // Adds the created statement to application manger's statement list
	}
	pOut->PrintMessage("Statement Pasted Successfully");
}


