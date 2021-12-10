
//Main 
#include "myform1.h"


using namespace System;
using namespace System::Windows::Forms;
[STAThread]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	contact::myform1 form;
	Application::Run(%form);
	return 0;
}

