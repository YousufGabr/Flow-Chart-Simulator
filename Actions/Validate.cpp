#include "Validate.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
#include <fstream>
using namespace std;

Validate::Validate(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Validate::ReadActionParameters()
{
}

void Validate::Execute() {

	ReadActionParameters();
	pManager->ValidateChart();
}



