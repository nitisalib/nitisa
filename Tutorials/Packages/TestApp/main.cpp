#include "Platform/Core/Application.h" // Include application manager

#include "FormMain.h" // Include main form

#include <Windows.h> // Include windows declarations

// Import libraries
#pragma comment(lib, "Nitisa.lib") // Nitisa core. Required
#pragma comment(lib, "Standard.lib") // Standard widgets library
#pragma comment(lib, "Platform.lib") // Platform dependent classes implementations (CApplication, CRenderer, CWindow)
#pragma comment(lib, "opengl32.lib") // Renderer uses OpenGL graphics, so OpenGL library is required

#pragma comment(lib, "CoolWidgets.lib") // Link with CoolWidgets package library we are working on

using namespace nitisa;

int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, INT)
{
	CApplication app; // Create application
	app.CreateForm(&FormMain); // Create main form
	app.setMainForm(FormMain); // Tell application which form is the main one
	app.Run(); // Run application
	return 0;
}