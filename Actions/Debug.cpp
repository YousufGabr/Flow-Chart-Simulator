#include "Debug.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
#include <fstream>
using namespace std;

Debug::Debug(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Debug::ReadActionParameters()
{
}

void Debug::Execute() {

	ReadActionParameters();
	pManager->DebugChart();
}





