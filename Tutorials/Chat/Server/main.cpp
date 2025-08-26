#include <Windows.h>
#include "Platform/Core/Application.h" // Application implementation is here
#include "FormMain.h" // Our form is here

#pragma comment(lib, "Nitisa.lib") // Add linking of Nitisa core library
#pragma comment(lib, "Standard.lib") // Add linking of Standard Package library(here are all the controls located)
#pragma comment(lib, "Platform.lib") // Add linking of platform-dependent code library

#pragma comment(lib, "opengl32.lib") // Add linking with OpenGL library

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int) // Main function
{
	// Declare variables for our form and application
	nitisa::app::CFormMain *form;
	nitisa::CApplication app;
	
	// Create form, set it as a main one, and run the application
	app.CreateForm(&form);
	app.setMainForm(form);
	app.Run();

	return 0;
}