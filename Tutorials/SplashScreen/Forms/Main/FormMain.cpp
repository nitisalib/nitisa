// Include platform window implementation
#include "Platform/Core/Window.h"

// Include platform OpenGL renderer implementation
#include "Platform/Core/Renderer.h"

// Include main form declaration
#include "FormMain.h"

// Include splash form declaration
#include "../Splash/FormSplash.h"

// Include windows functions
#include <Windows.h>

namespace nitisa
{
	namespace app
	{
		CFormMain *FormMain{ nullptr };

		// Main form constructor
		CFormMain::CFormMain() :
			IFormMain(CWindow::Create(), CRenderer::Create())
		{
			for (int i = 1; i < 100; i++)
			{
				FormSplash->setProgress((float)i); // Update progress on the splash form
				Application->ProcessMessages(); // Allow other forms to do something (in this case splash form will be able to repaint itself)
				Sleep(50); // Simulate hard work by waiting for 50 milliseconds before next iteration
			}
		}
	}
}