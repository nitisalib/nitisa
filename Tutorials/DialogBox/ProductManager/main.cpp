#include <Windows.h>

// Include file with platform application manager
#include "Platform/Core/Application.h"

// Include file with main form declaration
#include "FormMain.h"

// Include file with product form declaration
#include "FormProduct.h"

// Include file with confirmation form declaration
#include "FormConfirm.h"

// Tell the linker we want to link with the framework's core library. Mandatory
#pragma comment(lib, "Nitisa.lib")

// Tell the linker we want to link with the Standard package library as we use widgets from this package
// When we use widgets on the form from some package we should link our application with the library of that package
// Libraries for linking can also be specified in the project settings but we preffer doing this in this way as it is more informative
#pragma comment(lib, "Standard.lib")

// Tell the linker we want to link with platform-dependent code library. Required in most cases
#pragma comment(lib, "Platform.lib")

#pragma comment(lib, "opengl32.lib") // Add linking with OpenGL library

// We need to change DialogBoxes property so we must create an application class derived from standard one
class CMyApplication :public nitisa::CApplication
{
public:
	CMyApplication() :
		nitisa::CApplication()
	{
		// We set property value to true in constructor
		m_bDialogBoxes = true;
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, INT)
{
	CMyApplication app; // Create application
	app.CreateForm(&nitisa::app::FormMain); // Create our form. Having variable for it makes it possible to use "CreateForm" but it can also be created as usual with "new" operator
	app.setMainForm(nitisa::app::FormMain); // Tell the application the form is the main form of the application
	if (!app.DialogBoxes) // If regular form mode should be used
	{
		app.CreateForm(&nitisa::app::FormProduct); // Create product adding/editing form
		app.CreateForm(&nitisa::app::FormConfirm); // Create product removing confirmation form
	}
	app.Run(); // Run application
	return 0;
}