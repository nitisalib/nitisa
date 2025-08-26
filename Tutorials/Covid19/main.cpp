#include "Platform/Core/Application.h" // Include application manager

#include "Forms/Main/FormMain.h" // Include main form

#include <Windows.h> // Include windows declarations

// Import libraries
#pragma comment(lib, "Nitisa.lib") // Nitisa core. Required
#pragma comment(lib, "Standard.lib") // Standard widgets library. We use Label and ProgressBar widgets from it
#pragma comment(lib, "Platform.lib") // Platform dependent classes implementations (CApplication, CRenderer, CWindow)
#pragma comment(lib, "Charts.lib") // Charts widgets library. We use several charts widgets from it
#pragma comment(lib, "opengl32.lib") // Renderer uses OpenGL graphics, so OpenGL library is required

int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, INT)
{
	nitisa::CApplication app; // Create application
	app.CreateForm(&nitisa::app::FormMain); // Create main form. It won't be visible as its state was changed to Hidden. It simulates long loading in constructor
	app.setMainForm(nitisa::app::FormMain); // Tell application which form is the main one
	app.Run(); // Run application
	return 0;
}