#include "Platform/Core/Renderer.h" // Include platform window implementation
#include "Platform/Core/Window.h" // Include platform OpenGL renderer implementation

#include "FormSplash.h" // Include splash form declaration

namespace nitisa
{
	namespace app
	{
		CFormSplash *FormSplash{ nullptr };

		// Constructor
		CFormSplash::CFormSplash() :
			IFormSplash(CWindow::Create(), CRenderer::Create())
		{

		}

		// Close event method
		void CFormSplash::FormSplash_OnClose(IForm *sender, CloseAction &action)
		{
			action = CloseAction::None; // Do nothing when user attempts to close the form
		}

		void CFormSplash::setProgress(const float progress)
		{
			m_pProgressBar->setProgress(progress); // Update progress of the progress bar widget
		}
	}
}