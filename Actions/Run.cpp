#include "Run.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
#include <fstream>
using namespace std;

Run::Run(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Run::ReadActionParameters()
{
}

void Run::Execute() {

	ReadActionParameters();
	pManager->RunChart();
}




