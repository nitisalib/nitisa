#include "Platform/Core/Application.h" // Include application manager

#include "Forms/Splash/FormSplash.h" // Include splash form
#include "Forms/Main/FormMain.h" // Include main form

#include <Windows.h> // Include windows declarations

// Import libraries
#pragma comment(lib, "Nitisa.lib") // Nitisa core. Required
#pragma comment(lib, "Standard.lib") // Standard widgets library
#pragma comment(lib, "Platform.lib") // Platform dependent classes implementations (CApplication, CRenderer, CWindow)
#pragma comment(lib, "opengl32.lib") // Renderer uses OpenGL graphics, so OpenGL library is required

int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, INT)
{
	nitisa::CApplication app; // Create application
	app.CreateForm(&nitisa::app::FormSplash); // Create splash form. It will be shown immediately as its state was left as Normal
	app.CreateForm(&nitisa::app::FormMain); // Create main form. It won't be visible as its state was changed to Hidden. It simulates long loading in constructor
	app.setMainForm(nitisa::app::FormMain); // Tell application which form is the main one
	nitisa::app::FormSplash->Release(); // Release splash form
	nitisa::app::FormMain->Show(); // Show main form
	app.Run(); // Run application
	return 0;
}